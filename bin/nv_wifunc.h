#include <stdlib.h>

#include <core/os.h>
#include <core/object.h>
#include <core/device.h>

static void __iomem *map = NULL;
static u64 map_page = ~0ULL;

static void
nv_wfb(struct nouveau_object *device, u64 offset, CAST data)
{
	struct pci_dev *pdev = nv_device(device)->pdev;
	u64 page = (offset & ~(PAGE_SIZE - 1));
	u64 addr = (offset &  (PAGE_SIZE - 1));

	if (nv_device(device)->card_type < NV_40 ||
	    nv_device(device)->card_type > NV_E0) {
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

	*(CAST *)(map + addr) = data;
}

#define WRITE(o,v) nv_wfb(device, (o), (v))
#include "nv_wrfunc.h"
