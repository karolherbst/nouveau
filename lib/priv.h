#ifndef __OS_PRIV_H__
#define __OS_PRIV_H__

#include <core/os.h>
#include <core/client.h>

#include <pthread.h>
#include <unistd.h>

struct os_device {
	struct nouveau_device base;
	struct list_head head;
	char *name;
	char *cfg;
	char *dbg;
};

struct os_client {
	struct nouveau_client base;
	struct list_head head;
};

#endif
