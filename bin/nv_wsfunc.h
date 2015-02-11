#include <stdlib.h>

#include <nvif/device.h>

static void
nv_wsys(struct nvif_device *device, u64 addr, CAST data)
{
	if (device->info.family >= NV_DEVICE_INFO_V0_TESLA &&
	    device->info.family <= NV_DEVICE_INFO_V0_MAXWELL) {
		u32 pmem = nvif_rd32(device, 0x001700);
		nvif_wr32(device, 0x001700, 0x02000000 | (addr >> 16));
		WSYS(device, 0x700000 + (addr & 0xffffULL), data);
		nvif_wr32(device, 0x001700, pmem);
	} else {
		printk("unsupported chipset\n");
		exit(1);
	}
}

#define WRITE(o,v) nv_wsys(device, (o), (v))
#define ENABLE    (NV_DEVICE_V0_DISABLE_MMIO | NV_DEVICE_V0_DISABLE_IDENTIFY)
#include "nv_wrfunc.h"
