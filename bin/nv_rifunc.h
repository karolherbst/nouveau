#include <stdlib.h>

#include <nvif/device.h>

static void __iomem *map = NULL;
static u64 map_page = ~0ULL;

static CAST
nv_rfb(struct nvif_device *device, u64 offset)
{
	struct pci_dev *pdev = nvxx_device(device)->pdev;
	u64 page = (offset & ~(PAGE_SIZE - 1));
	u64 addr = (offset &  (PAGE_SIZE - 1));

	if (device->info.family < NV_DEVICE_INFO_V0_CURIE ||
	    device->info.family > NV_DEVICE_INFO_V0_MAXWELL) {
		printk("unsupported chipset\n");
		exit(1);
	}

	if (map_page != page) {
		if (map)
			iounmap(map);

		if (pci_resource_len(pdev, 2)) {
			map = ioremap(pci_resource_start(pdev, 2) +
				      page, PAGE_SIZE);
		} else {
			map = ioremap(pci_resource_start(pdev, 3) +
				      page, PAGE_SIZE);
		}

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
