#include <stdlib.h>

#include <nvif/device.h>

static void __iomem *map = NULL;
static u64 map_page = ~0ULL;

static void
nv_wfb(struct nvif_device *device, u64 offset, CAST data)
{
	struct nvkm_device *nv = nvxx_device(device);
	u64 page = (offset & ~(PAGE_SIZE - 1));
	u64 addr = (offset &  (PAGE_SIZE - 1));

	if (device->info.family < NV_DEVICE_INFO_V0_CURIE ||
	    device->info.family > NV_DEVICE_INFO_V0_PASCAL) {
		printk("unsupported chipset\n");
		exit(1);
	}

	if (map_page != page) {
		if (map)
			iounmap(map);

		if (nv->func->resource_size(nv, 2)) {
			map = ioremap(nv->func->resource_addr(nv, 2) +
				      page, PAGE_SIZE);
		} else {
			map = ioremap(nv->func->resource_addr(nv, 3) +
				      page, PAGE_SIZE);
		}

		if (!map) {
			printk("map failed\n");
			exit(1);
		}

		map_page = page;
	}

	*(CAST *)(map + addr) = data;
}

#define WRITE(o,v) nv_wfb(device, (o), (v))
#define DETECT true
#include "nv_wrfunc.h"
