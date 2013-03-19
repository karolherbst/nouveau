#ifndef __OS_PRIV_H__
#define __OS_PRIV_H__

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

extern pthread_t os_intr_thread;
void *os_intr(void *arg);

#endif
