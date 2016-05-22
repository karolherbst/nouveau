/*
 * Copyright 2012 Red Hat Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Ben Skeggs
 */

#include <nvif/client.h>
#include <nvif/driver.h>
#include <nvif/notify.h>
#include <nvif/ioctl.h>
#include <nvif/class.h>
#include <nvif/event.h>

#include <core/pci.h>
#include <core/ioctl.h>
#include <core/event.h>

#include "priv.h"

static DEFINE_MUTEX(os_mutex);
static LIST_HEAD(os_device_list);
static int os_client_nr = 0;

bool os_device_detect = true;
bool os_device_mmio = true;
u64  os_device_subdev = ~0ULL;

/******************************************************************************
 * horrific stuff to implement linux's ioremap interface on top of pciaccess
 *****************************************************************************/
static DEFINE_MUTEX(os_ioremap_mutex);
static struct os_ioremap_info {
       struct pci_device *pdev;
       int refs;
       u64 addr;
       u64 size;
       void *ptr;
} os_ioremap[32];

void __iomem *
nvos_ioremap_bar(struct pci_device *pdev, int bar, u64 addr)
{
	u64 base = pdev->regions[bar].base_addr;
	u64 size = pdev->regions[bar].size;
	u64 offset = addr - base;
	void __iomem *ptr = NULL;
	int i;

	mutex_lock(&os_ioremap_mutex);
	for (i = 0; !ptr && i < ARRAY_SIZE(os_ioremap); i++) {
		if (os_ioremap[i].refs && os_ioremap[i].addr == base) {
			os_ioremap[i].refs++;
			ptr = os_ioremap[i].ptr + offset;
		}
	}

	for (i = 0; !ptr && i < ARRAY_SIZE(os_ioremap); i++) {
		if (!os_ioremap[i].refs &&
		    !pci_device_map_range(pdev, base, size,
					  PCI_DEV_MAP_FLAG_WRITABLE,
					  &os_ioremap[i].ptr)) {
			os_ioremap[i].pdev = pdev;
			os_ioremap[i].refs = 1;
			os_ioremap[i].addr = base;
			os_ioremap[i].size = size;
			ptr = os_ioremap[i].ptr + offset;
		}
	}
	mutex_unlock(&os_ioremap_mutex);

	return ptr;
}

void __iomem *
nvos_ioremap(u64 addr, u64 size)
{
	struct os_device *odev;
	int i;

	list_for_each_entry(odev, &os_device_list, head) {
		struct pci_device *pdev = odev->pdev.pdev;
		for (i = 0; i < ARRAY_SIZE(pdev->regions); i++) {
			if (addr        >= pdev->regions[i].base_addr &&
			    addr + size <= pdev->regions[i].base_addr +
					   pdev->regions[i].size) {
				return nvos_ioremap_bar(pdev, i, addr);
			}
		}
	}

	return NULL;
}

void
nvos_iounmap(void __iomem *ptr)
{
	int i;

	mutex_lock(&os_ioremap_mutex);
	for (i = 0; ptr && i < ARRAY_SIZE(os_ioremap); i++) {
		if (os_ioremap[i].refs &&
		    ptr >= os_ioremap[i].ptr &&
		    ptr <  os_ioremap[i].ptr + os_ioremap[i].size) {
			if (!--os_ioremap[i].refs) {
				pci_device_unmap_range(os_ioremap[i].pdev,
						       os_ioremap[i].ptr,
						       os_ioremap[i].size);
			}
			break;
		}
	}
	mutex_unlock(&os_ioremap_mutex);
}

/******************************************************************************
 * client interfaces
 *****************************************************************************/
static void
os_fini_device(struct os_device *odev)
{
	nvkm_device_del(&odev->device);
	list_del(&odev->head);
	kfree(odev);
}

static int
os_init_device(struct pci_device *pdev, const char *cfg, const char *dbg)
{
	struct os_device *odev;
	int ret;

	ret = pci_device_probe(pdev);
	if (ret) {
		fprintf(stderr, "pci_device_probe failed, %d\n", ret);
		return ret;
	}

	odev = calloc(1, sizeof(*odev));
	if (!odev)
		return -ENOMEM;

	snprintf(odev->pdev.dev.name, sizeof(odev->pdev.dev.name),
		 "%04x:%02x:%02x.%1x",
		 pdev->domain, pdev->bus, pdev->dev, pdev->func);
	odev->pdev.pdev = pdev;
	odev->pdev.vendor = pdev->vendor_id;
	odev->pdev.device = pdev->device_id;
	odev->pdev.subsystem_vendor = pdev->subvendor_id;
	odev->pdev.subsystem_device = pdev->subdevice_id;
	odev->pdev._bus.domain = pdev->domain;
	odev->pdev._bus.number = pdev->bus;
	odev->pdev.bus = &odev->pdev._bus;
	odev->pdev.devfn = PCI_DEVFN(pdev->dev, pdev->func);
	list_add_tail(&odev->head, &os_device_list);

	ret = nvkm_device_pci_new(&odev->pdev, cfg, dbg, os_device_detect,
				  os_device_mmio, os_device_subdev,
				  &odev->device);
	if (ret) {
		fprintf(stderr, "failed to create device, %d\n", ret);
		os_fini_device(odev);
		return ret;
	}

	return 0;
}

static int
os_init(const char *cfg, const char *dbg)
{
	struct pci_device_iterator *iter;
	struct pci_device *pdev;
	int ret;

	ret = pci_system_init();
	if (ret) {
		fprintf(stderr, "pci_system_init failed, %d\n", ret);
		return ret;
	}

	iter = pci_slot_match_iterator_create(NULL);
	while ((pdev = pci_device_next(iter))) {
		if ((pdev->device_class & 0x00ff0000) != 0x00030000)
			continue;
		if (pdev->vendor_id != 0x10de)
			continue;

		os_init_device(pdev, cfg, dbg);
	}
	pci_iterator_destroy(iter);
	return 0;
}

static void
os_fini(void)
{
	struct os_device *odev, *temp;

	list_for_each_entry_safe(odev, temp, &os_device_list, head) {
		os_fini_device(odev);
	}

	pci_system_cleanup();
}

static void
os_client_unmap(void *priv, void *ptr, u32 size)
{
	iounmap(ptr);
}

static void *
os_client_map(void *priv, u64 handle, u32 size)
{
	return ioremap(handle, size);
}

static int
os_client_ioctl(void *priv, bool super, void *data, u32 size, void **hack)
{
	return nvkm_ioctl(priv, super, data, size, hack);
}

static int
os_client_resume(void *priv)
{
	struct nvkm_client *client = priv;
	return nvkm_object_init(&client->object);
}

static int
os_client_suspend(void *priv)
{
	struct nvkm_client *client = priv;
	return nvkm_object_fini(&client->object, true);
}

static void
os_client_fini(void *priv)
{
	struct nvkm_client *client = priv;
	struct nvkm_object *object = &client->object;

	nvkm_object_fini(object, false);
	nvkm_object_del(&object);

	mutex_lock(&os_mutex);
	if (--os_client_nr == 0)
		os_fini();
	mutex_unlock(&os_mutex);
}

static int
os_client_init(const char *name, u64 device, const char *cfg,
	       const char *dbg, void **ppriv)
{
	struct nvkm_client *client;
	int ret;

	mutex_lock(&os_mutex);
	if (os_client_nr++ == 0)
		os_init(cfg, dbg);
	mutex_unlock(&os_mutex);

	ret = nvkm_client_new(name, device, cfg, dbg, &client);
	*ppriv = client;
	if (ret == 0)
		client->ntfy = nvif_notify;
	return ret;
}

const struct nvif_driver
nvif_driver_lib = {
	.name = "lib",
	.init = os_client_init,
	.fini = os_client_fini,
	.suspend = os_client_suspend,
	.resume = os_client_resume,
	.ioctl = os_client_ioctl,
	.map = os_client_map,
	.unmap = os_client_unmap,
	.keep = false,
};
