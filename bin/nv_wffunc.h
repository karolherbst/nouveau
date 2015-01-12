#include <stdlib.h>

#include <nvif/device.h>

static void __iomem *map = NULL;
static u64 map_page = ~0ULL;

static void
nv_wfb(struct nvif_device *device, u64 offset, CAST data)
{
	u64 page = (offset & ~(PAGE_SIZE - 1));
	u64 addr = (offset &  (PAGE_SIZE - 1));

	if (device->info.family < NV_DEVICE_INFO_V0_TNT ||
	    device->info.family > NV_DEVICE_INFO_V0_MAXWELL) {
		printk("unsupported chipset\n");
		exit(1);
	}

	if (map_page != page) {
		if (map)
			iounmap(map);

		map = ioremap(pci_resource_start(nvxx_device(device)->pdev, 1) +
			      page, PAGE_SIZE);
		if (!map) {
			printk("map failed\n");
			exit(1);
		}

		map_page = page;
	}

	*(CAST *)(map + addr) = data;
}

#define WRITE(o,v) nv_wfb(device, (o), (v))
#define ENABLE    (NV_DEVICE_V0_DISABLE_MMIO | NV_DEVICE_V0_DISABLE_IDENTIFY)
#include "nv_wrfunc.h"
