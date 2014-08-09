#include <stdlib.h>

#include <nvif/device.h>

static void
nv_wvram(struct nvif_device *device, u64 addr, CAST data)
{
	if (device->info.family >= NV_DEVICE_INFO_V0_TESLA &&
	    device->info.family <= NV_DEVICE_INFO_V0_MAXWELL) {
		u32 pmem = nv_ro32(device, 0x001700);
		nv_wo32(device, 0x001700, 0x00000000 | (addr >> 16));
		WVRAM(device, 0x700000 + (addr & 0xffffULL), data);
		nv_wo32(device, 0x001700, pmem);
	} else {
		printk("unsupported chipset\n");
		exit(1);
	}
}

#define WRITE(o,v) nv_wvram(device, (o), (v))
#define ENABLE    (NV_DEVICE_DISABLE_MMIO | NV_DEVICE_DISABLE_IDENTIFY)
#include "nv_wrfunc.h"
