#include <stdlib.h>

#include <nvif/device.h>

static void
nv_wvram(struct nvif_device *device, u64 addr, CAST data)
{
	if (device->info.family >= NV_DEVICE_INFO_V0_TESLA &&
	    device->info.family <= NV_DEVICE_INFO_V0_MAXWELL) {
		u32 pmem = nvif_rd32(device, 0x001700);
		nvif_wr32(device, 0x001700, 0x00000000 | (addr >> 16));
		WVRAM(device, 0x700000 + (addr & 0xffffULL), data);
		nvif_wr32(device, 0x001700, pmem);
	} else {
		printk("unsupported chipset\n");
		exit(1);
	}
}

#define WRITE(o,v) nv_wvram(device, (o), (v))
#define DETECT true
#include "nv_wrfunc.h"
