#include <stdlib.h>

#include <nvif/device.h>

static CAST
nv_rsys(struct nvif_device *device, u64 addr)
{
	if (device->info.family >= NV_DEVICE_INFO_V0_TESLA &&
	    device->info.family <= NV_DEVICE_INFO_V0_TURING) {
		CAST data;
		u32 pmem = nvif_rd32(&device->object, 0x001700);
		nvif_wr32(&device->object, 0x001700, 0x02000000 | (addr >> 16));
		data = RSYS(&device->object, 0x700000 + (addr & 0xffffULL));
		nvif_wr32(&device->object, 0x001700, pmem);
		return data;
	} else {
		printk("unsupported chipset\n");
		exit(1);
	}
}

#define READ(o) nv_rsys(device, (o))
#define DETECT true
#include "nv_rdfunc.h"
