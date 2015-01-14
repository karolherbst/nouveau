#ifndef __OS_PRIV_H__
#define __OS_PRIV_H__

#include <core/device.h>

#include <pthread.h>
#include <unistd.h>

struct os_device {
	struct nvkm_device base;
	struct list_head head;
	char *name;
	char *cfg;
	char *dbg;
};

#endif
