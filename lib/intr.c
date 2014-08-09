/*
 * Copyright 2013 Red Hat Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Ben Skeggs
 */

#include <core/device.h>
#include <core/client.h>
#include "priv.h"

struct os_intr {
	struct list_head head;
	pthread_t thread;
	irq_handler_t handler;
	int irq;
	void *dev;
};
static DEFINE_MUTEX(os_intr_mutex);
static LIST_HEAD(os_intr_list);

static void *
os_intr(void *arg)
{
	struct os_intr *intr = arg;
	while (1) {
		intr->handler(intr->irq, intr->dev);
		usleep(10000);
	}
	return NULL;
}

int
os_intr_init(unsigned int irq, irq_handler_t handler, unsigned long flags,
	     const char *name, void *dev)
{
	struct os_intr *intr = malloc(sizeof(*intr));
	if (!intr)
		return -ENOMEM;
	intr->handler = handler;
	intr->irq = irq;
	intr->dev = dev;
	mutex_lock(&os_intr_mutex);
	list_add(&intr->head, &os_intr_list);
	mutex_unlock(&os_intr_mutex);
	pthread_create(&intr->thread, NULL, os_intr, intr);
	return 0;
}

void
os_intr_free(unsigned int irq, void *dev)
{
	struct os_intr *intr;

	mutex_lock(&os_intr_mutex);
	list_for_each_entry(intr, &os_intr_list, head) {
		if (intr->irq == irq && intr->dev == dev) {
			pthread_cancel(intr->thread);
			pthread_join(intr->thread, NULL);
			list_del(&intr->head);
			mutex_unlock(&os_intr_mutex);
			free(intr);
			return;
		}
	}
	mutex_unlock(&os_intr_mutex);
}
