#include <stdlib.h>

#include <nvif/device.h>

static void __iomem *map = NULL;
static u64 map_page = ~0ULL;

static CAST
nv_rfb(struct nvif_device *device, u64 offset)
{
	struct nvkm_device *nv = nvxx_device(device);
	u64 page = (offset & ~(PAGE_SIZE - 1));
	u64 addr = (offset &  (PAGE_SIZE - 1));

	if (device->info.family < NV_DEVICE_INFO_V0_TNT ||
	    device->info.family > NV_DEVICE_INFO_V0_VOLTA) {
		printk("unsupported chipset\n");
		exit(1);
	}

	if (map_page != page) {
		if (map)
			iounmap(map);

		map = ioremap(nv->func->resource_addr(nv, 1) + page, PAGE_SIZE);
		if (!map) {
			printk("map failed\n");
			exit(1);
		}

		map_page = page;
	}

	return *(CAST *)(map + addr);
}

#define READ(o) nv_rfb(device, (o))
#define DETECT true
#include "nv_rdfunc.h"
