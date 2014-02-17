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

#include <core/os.h>

#include <core/object.h>
#include <core/client.h>
#include <core/device.h>
#include <core/intr.h>
#include <core/class.h>

#include <engine/device.h>
#include <subdev/mc.h>

#include "priv.h"

static LIST_HEAD(os_device_list);
static LIST_HEAD(os_client_list);
static int os_client_id = 0;

/******************************************************************************
 * horrific stuff to implement linux's ioremap interface on top of pciaccess
 *****************************************************************************/
static struct os_ioremap_info {
       struct pci_device *pdev;
       int refs;
       u64 addr;
       u64 size;
       void *ptr;
} os_ioremap[32];

void __iomem *
nvos_ioremap(u64 addr, u64 size)
{
	struct pci_device *pdev = NULL;
	struct os_ioremap_info *info;
	struct os_device *odev;
	u64 m_page = addr &  0xfff;
	u64 m_addr = addr & ~0xfff;
	u64 m_size = (size + 0xfff) & ~0xfff;
	int i;

	list_for_each_entry(odev, &os_device_list, head) {
		for (i = 0; i < 6; i++) {
			pdev = odev->base.pdev->pdev;
			if (m_addr          >= pdev->regions[i].base_addr &&
			    m_addr + m_size <= pdev->regions[i].base_addr +
					       pdev->regions[i].size)
				break;
			pdev = NULL;
		}
		if (pdev)
			break;
	}

	for (i = 0, info = NULL; pdev && i < ARRAY_SIZE(os_ioremap); i++) {
		if (os_ioremap[i].refs) {
			if (os_ioremap[i].addr != m_addr ||
			    os_ioremap[i].size != m_size)
				continue;
		} else {
			info = &os_ioremap[i];
			continue;
		}

		os_ioremap[i].refs++;
		return os_ioremap[i].ptr + m_page;
	}

	if (info) {
		if (pci_device_map_range(pdev, m_addr, m_size,
					 PCI_DEV_MAP_FLAG_WRITABLE,
					 &info->ptr))
			return NULL;

		info->pdev = pdev;
		info->refs = 1;
		info->addr = m_addr;
		info->size = m_size;
		return info->ptr + m_page;
	}

	return NULL;
}

void
nvos_iounmap(void __iomem *ptr)
{
	int i;

	for (i = 0; ptr && i < ARRAY_SIZE(os_ioremap); i++) {
		if (os_ioremap[i].refs &&
		    ptr >= os_ioremap[i].ptr &&
		    ptr <  os_ioremap[i].ptr + os_ioremap[i].size) {
			if (!--os_ioremap[i].refs) {
				pci_device_unmap_range(os_ioremap[i].pdev, ptr,
						       os_ioremap[i].size);
			}
			break;
		}
	}
}

/******************************************************************************
 * client interfaces
 *****************************************************************************/
static int
os_init_device(struct pci_device *pdev, u64 handle, char *cfg, char *dbg)
{
	struct os_device *odev;
	struct pci_dev *ldev;
	char *name, _name[64];
	int ret;

	ret = pci_device_probe(pdev);
	if (ret) {
		fprintf(stderr, "pci_device_probe failed, %d\n", ret);
		return ret;
	}

	snprintf(_name, sizeof(_name), "%04x:%02x:%02x.%1x",
		 pdev->domain, pdev->bus, pdev->dev, pdev->func);

	list_for_each_entry(odev, &os_device_list, head) {
		if (odev->base.handle == handle)
			return -EEXIST;
	}

	ldev = malloc(sizeof(*ldev));
	ldev->pdev = pdev;
	ldev->device = pdev->dev;
	ldev->subsystem_vendor = pdev->subvendor_id;
	ldev->subsystem_device = pdev->subdevice_id;

	name = strdup(_name);
	cfg = cfg ? strdup(cfg) : NULL;
	dbg = dbg ? strdup(dbg) : NULL;

	ret = nouveau_device_create(ldev, NOUVEAU_BUS_PCI, handle, name,
				    cfg, dbg, &odev);
	if (ret) {
		fprintf(stderr, "failed to create device, %d\n", ret);
		return ret;
	}

	list_add_tail(&odev->head, &os_device_list);
	odev->name = name;
	odev->cfg = cfg;
	odev->dbg = dbg;
	return 0;
}

static int
os_init(char *cfg, char *dbg, bool init)
{
	struct pci_device_iterator *iter;
	struct pci_device *pdev;
	u64 handle;
	int ret, n = 0;

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

		handle = ((u64)pdev->domain << 32) | (pdev->bus << 16) |
			 (pdev->dev << 8) | pdev->func;

		if (!init) {
			printf("%d: 0x%010"PRIx64" PCI:%04x:%02x:%02x:%02x "
			       "(%04x:%04x)\n", n++, handle, pdev->domain,
			       pdev->bus, pdev->dev, pdev->func,
			       pdev->vendor_id, pdev->device_id);
			continue;
		}

		os_init_device(pdev, handle, cfg, dbg);
	}

	return pthread_create(&os_intr_thread, NULL, os_intr, NULL);
}

static void
os_fini(void)
{
	struct os_device *odev, *temp;

	list_for_each_entry_safe(odev, temp, &os_device_list, head) {
		char *name = odev->name;
		char *cfg  = odev->cfg;
		char *dbg  = odev->dbg;
		list_del(&odev->head);
		nouveau_object_ref(NULL, (struct nouveau_object **)&odev);
		free(dbg); free(cfg); free(name);
	}
}

int
os_client_new(char *cfg, char *dbg, int argc, char **argv,
	      struct nouveau_object **pclient)
{
	struct os_device *device = NULL, *odev;
	struct os_client *client;
	u64 handle = ~0ULL;
	int ret, c;

	while ((c = getopt(argc, argv, "la:i:c:d:")) != -1) {
		switch (c) {
		case 'l':
			return os_init(NULL, NULL, false);
		case 'a':
			handle = strtoull(optarg, NULL, 0);
			break;
		case 'c':
			cfg = optarg;
			break;
		case 'd':
			dbg = optarg;
			break;
		case '?':
			return -EINVAL;
		default:
			break;
		}
	}

	if (list_empty(&os_client_list)) {
		ret = os_init(cfg, dbg, true);
		if (ret)
			return ret;
	}

	c = 0;
	list_for_each_entry(odev, &os_device_list, head) {
		if (handle == ~0ULL || handle == c++ ||
		    handle == odev->base.handle) {
			device = odev;
			break;
		}
	}

	if (device) {
		char name[16];

		snprintf(name, sizeof(name), "CLIENT%2d", os_client_id++);

		ret = nouveau_client_create(name, device->base.handle,
					    cfg, dbg, &client);
		*pclient = nv_object(client);
		if (ret)
			return ret;

		list_add(&client->head, &os_client_list);
		return 0;
	}

	return -ENODEV;
}

void
os_client_del(struct nouveau_object **pclient)
{
	struct nouveau_object *client = *pclient;

	if (client) {
		struct os_client *ocli = (void *)client;

		list_del(&ocli->head);

		nouveau_client_fini(nv_client(client), false);
		atomic_set(&client->refcount, 1);
		nouveau_object_ref(NULL, &client);

		if (list_empty(&os_client_list))
			os_fini();
	}

	*pclient = NULL;
}

void
os_suspend()
{
	struct os_client *client;
	int ret;

	list_for_each_entry(client, &os_client_list, head) {
		ret = nouveau_client_fini(&client->base, true);
		assert(ret == 0);
	}
}

void
os_resume()
{
	struct os_client *client;
	int ret;

	list_for_each_entry(client, &os_client_list, head) {
		ret = nouveau_client_init(&client->base);
		assert(ret == 0);
	}
}
