#ifndef __UTIL_H__
#define __UTIL_H__
#include <nvif/client.h>
#include <nvif/device.h>

#include <unistd.h>

#define U_GETOPT "a:b:c:d:"

static const char *u_drv;
static const char *u_cfg;
static const char *u_dbg;
static u64 u_dev = ~0ULL;

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
	 bool detect, bool mmio, u64 subdev,
	 struct nvif_client **pclient)
{
	return nvif_client_new(u_drv ? u_drv : drv, name, u_dev, u_cfg,
			       u_dbg ? u_dbg : dbg, pclient);
}

static inline int
u_device(const char *drv, const char *name, const char *dbg,
	 bool detect, bool mmio, u64 subdev, u32 handle,
	 struct nvif_device **pdevice)
{
	struct nvif_client *client;
	int ret = u_client(drv, name, dbg, detect, mmio, subdev, &client);
	if (ret == 0) {
		ret = nvif_device_new(client->object, handle, NV_DEVICE,
				      &(struct nv_device_v0) {
					.device = ~0ULL,
					.disable = ~(
		(detect ? NV_DEVICE_V0_DISABLE_IDENTIFY : 0) |
		(  mmio ? NV_DEVICE_V0_DISABLE_MMIO : 0) |
		((subdev & (1ULL << NVDEV_SUBDEV_VBIOS)) ?
			NV_DEVICE_V0_DISABLE_VBIOS : 0) |
		(subdev ? NV_DEVICE_V0_DISABLE_CORE : 0)),
					.debug0 = ~subdev,
				      }, sizeof(struct nv_device_v0),
				      pdevice);
		nvif_client_ref(NULL, &client);
	}
	return ret;
}
#endif
