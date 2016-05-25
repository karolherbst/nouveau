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

#include <core/ioctl.h>
#include <core/pci.h>

#include "priv.h"

static DEFINE_MUTEX(null_mutex);
static int null_client_nr = 0;
static struct nvkm_device *null_device;
static struct pci_dev
null_pci_dev = {
	.dev = {
		.name = "0000:00:00.0",
	},
	.pdev = &(struct pci_device) {
	},
	.bus = &null_pci_dev._bus,
};

static void
null_fini(void)
{
	nvkm_device_del(&null_device);
}

static void
null_init(const char *cfg, const char *dbg, bool init)
{
	int ret = nvkm_device_pci_new(&null_pci_dev, cfg, dbg, os_device_detect,
				      os_device_mmio, os_device_subdev,
				      &null_device);
	if (ret)
		null_fini();
}

static void
null_client_unmap(void *priv, void *ptr, u32 size)
{
}

static void *
null_client_map(void *priv, u64 handle, u32 size)
{
	return NULL;
}

static int
null_client_ioctl(void *priv, bool super, void *data, u32 size, void **hack)
{
	return nvkm_ioctl(priv, super, data, size, hack);
}

static int
null_client_resume(void *priv)
{
	struct nvkm_client *client = priv;
	return nvkm_object_init(&client->object);
}

static int
null_client_suspend(void *priv)
{
	struct nvkm_client *client = priv;
	return nvkm_object_fini(&client->object, true);
}

static void
null_client_fini(void *priv)
{
	mutex_lock(&null_mutex);
	if (--null_client_nr == 0)
		null_fini();
	mutex_unlock(&null_mutex);
}

static int
null_client_init(const char *name, u64 device, const char *cfg,
		 const char *dbg, void **ppriv)
{
	struct nvkm_client *client = NULL;
	int ret;

	mutex_lock(&null_mutex);
	if (null_client_nr++ == 0)
		null_init(cfg, dbg, true);
	mutex_unlock(&null_mutex);

	ret = nvkm_client_new(name, ~0ULL, cfg, dbg, nvif_notify, &client);
	*ppriv = client;
	return ret;
}

const struct nvif_driver
nvif_driver_null = {
	.name = "null",
	.init = null_client_init,
	.fini = null_client_fini,
	.suspend = null_client_suspend,
	.resume = null_client_resume,
	.ioctl = null_client_ioctl,
	.map = null_client_map,
	.unmap = null_client_unmap,
	.keep = false,
};
