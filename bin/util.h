#ifndef __UTIL_H__
#define __UTIL_H__
#include <nvif/client.h>
#include <nvif/device.h>
#include <nvif/if0000.h>

#include <unistd.h>

#include "../lib/priv.h"

#define U_GETOPT "a:b:c:d:"

static const char *u_drv;
static const char *u_cfg;
static const char *u_dbg;
static int u_dev = 0;

static inline bool
u_option(int c)
{
	switch (c) {
	case 'a': u_dev = strtol(optarg, NULL, 0); break;
	case 'b': u_drv = optarg; break;
	case 'c': u_cfg = optarg; break;
	case 'd': u_dbg = optarg; break;
	default:
		return false;
	}
	return true;
}

static inline int
u_client(const char *drv, const char *name, const char *dbg,
	 bool detect, bool mmio, u64 subdev, struct nvif_client *client)
{
	os_device_detect = detect;
	os_device_mmio = mmio;
	os_device_subdev = subdev;
	return nvif_client_init(u_drv ? u_drv : drv, name, ~0ULL, u_cfg,
				u_dbg ? u_dbg : dbg, client);
}

static inline struct nv_client_devlist_v0 *
u_device_list(struct nvif_client *client)
{
	struct nvif_object *object = &client->object;
	struct nv_client_devlist_v0 *args;
	int count = 0;

	for (;;) {
		u32 size = sizeof(*args) + count * sizeof(args->device[0]);
		if (!(args = malloc(size)))
			return NULL;
		args->version = 0;
		args->count = count;

		if (nvif_object_mthd(object, NV_CLIENT_DEVLIST, args, size)) {
			free(args);
			return NULL;
		}

		if (args->count == count)
			return args;
		count = args->count;
		free(args);
	}
}

static inline void
u_device_show(struct nvif_client *client)
{
	struct nv_client_devlist_v0 *args = u_device_list(client);
	int i;
	printf("device(s):\n");
	for (i = 0; args && i < args->count; i++)
		printf("%2d: %016llx\n", i, args->device[i]);
	free(args);
}

static inline u64
u_device_name(struct nvif_client *client, int idx)
{
	struct nv_client_devlist_v0 *args = u_device_list(client);
	u64 device = ~0ULL;
	if (args) {
		if (idx >= 0 && idx < args->count)
			device = args->device[idx];
		else
			u_device_show(client);
		free(args);
	}
	return device;
}

static inline int
u_device(const char *drv, const char *name, const char *dbg,
	 bool detect, bool mmio, u64 subdev, u32 handle,
	 struct nvif_client *client, struct nvif_device *pdevice)
{
	int ret = u_client(drv, name, dbg, detect, mmio, subdev, client);
	if (ret == 0) {
		ret = nvif_device_init(&client->object, handle, NV_DEVICE,
				       &(struct nv_device_v0) {
					.device = u_device_name(client, u_dev),
				       }, sizeof(struct nv_device_v0),
				       pdevice);
		if (ret)
			nvif_client_fini(client);
	}
	return ret;
}
#endif
