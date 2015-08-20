/*
 * Copyright 2015 Red Hat Inc.
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
 * Authors: Ben Skeggs <bskeggs@redhat.com>
 */
#include "priv.h"

struct nvos_work {
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	pthread_t thread;
	bool done;

	void (*func)(void *);
	void *priv;
};

static void *
nvos_work(void *data)
{
	struct nvos_work *work = data;

	do {
		pthread_mutex_lock(&work->mutex);
		while (!work->priv && !work->done)
			pthread_cond_wait(&work->cond, &work->mutex);
		if (work->priv) {
			work->func(work->priv);
			work->priv = NULL;
		}
		pthread_mutex_unlock(&work->mutex);
	} while (!work->done);

	return NULL;
}

void
nvos_work_fini(struct nvos_work **pwork)
{
	struct nvos_work *work = *pwork;
	if (work) {
		pthread_mutex_lock(&work->mutex);
		work->done = true;
		pthread_cond_signal(&work->cond);
		pthread_mutex_unlock(&work->mutex);

		pthread_join(work->thread, NULL);
		pthread_cond_destroy(&work->cond);
		pthread_mutex_destroy(&work->mutex);
		free(*pwork);
		*pwork = NULL;
	}
}

bool
nvos_work_init(void (*func)(void *), void *priv, struct nvos_work **pwork)
{
	struct nvos_work *work = *pwork;

	if (unlikely(work == NULL)) {
		if (!(work = calloc(1, sizeof(*work))))
			return false;
		work->func = func;
		work->priv = NULL;
		work->done = false;

		if (pthread_mutex_init(&work->mutex, NULL))
			goto fail_mutex;
		if (pthread_cond_init(&work->cond, NULL))
			goto fail_cond;
		if (pthread_create(&work->thread, NULL, nvos_work, work))
			goto fail_thread;
		*pwork = work;
	}

	pthread_mutex_lock(&work->mutex);
	work->priv = priv;
	pthread_cond_signal(&work->cond);
	pthread_mutex_unlock(&work->mutex);
	return true;

fail_thread:
	pthread_cond_destroy(&work->cond);
fail_cond:
	pthread_mutex_destroy(&work->mutex);
fail_mutex:
	free(work);
	return false;
}
