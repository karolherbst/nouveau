#include <stdlib.h>

#include <core/os.h>
#include <core/object.h>
#include <core/device.h>

static void __iomem *map = NULL;
static u64 map_page = ~0ULL;

static void
nv_wfb(struct nouveau_object *device, u64 offset, CAST data)
{
	u64 page = (offset & ~(PAGE_SIZE - 1));
	u64 addr = (offset &  (PAGE_SIZE - 1));

	if (nv_device(device)->card_type < NV_04 ||
	    nv_device(device)->card_type > NV_E0) {
		printk("unsupported chipset\n");
		exit(1);
	}

	if (map_page != page) {
		if (map)
			iounmap(map);

		map = ioremap(pci_resource_start(nv_device(device)->pdev, 1) +
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
#define ENABLE    (NV_DEVICE_DISABLE_MMIO | NV_DEVICE_DISABLE_IDENTIFY)
#include "nv_wrfunc.h"
