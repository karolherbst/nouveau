#ifndef __OS_PRIV_H__
#define __OS_PRIV_H__

#include <core/device.h>

#include <pthread.h>
#include <unistd.h>

struct os_device {
	struct nvkm_device *device;
	struct list_head head;
	char *cfg;
	char *dbg;
	struct pci_dev pdev;
};

extern bool os_device_detect;
extern bool os_device_mmio;
extern u64  os_device_subdev;
#endif
