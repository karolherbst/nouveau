/*
 * Copyright 2014 Red Hat Inc.
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

#include <sys/mman.h>
#include <sys/ioctl.h>

#include <xf86drm.h>

#include <nvif/client.h>
#include <nvif/driver.h>
#include <nvif/notify.h>
#include <nvif/unpack.h>
#include <nvif/event.h>
#include <nvif/ioctl.h>

#include <uapi/drm/nouveau_drm.h>

struct drm_client_priv {
	int fd;
	u32 version;
	pthread_t event;
	bool done;
};

static void
drm_client_unmap(void *priv, void *ptr, u32 size)
{
}

static void *
drm_client_map(void *priv, u64 handle, u32 size)
{
	return NULL;
}

static int
drm_client_ioctl(void *priv, bool super, void *data, u32 size, void **hack)
{
	const unsigned long request = DRM_IOC(DRM_IOC_READWRITE, DRM_IOCTL_BASE,
					      DRM_COMMAND_BASE +
					      DRM_NOUVEAU_NVIF, size);
	struct drm_client_priv *drm = priv;
	int ret = ioctl(drm->fd, request, data);
	if (ret < 0)
		return -errno;
	return ret;
}

static int
drm_client_resume(void *priv)
{
	return -EINVAL;
}

static int
drm_client_suspend(void *priv)
{
	return -ENOSYS;
}

static void
drm_client_notify(void *repv, u32 repc)
{
	union {
		struct nvif_notify_rep_v0 v0;
	} *rep = repv;
	void *data = repv;
	u32 size = repc;
	u64 token;
	u8  route;
	int ret = -ENODEV;

	printf("notify %d\n", repc);

	if (!(ret = nvif_unpack(ret, &data, &size, rep->v0, 0, 0, true))) {
		token = rep->v0.token;
		route = rep->v0.route;
	} else
		assert(0);

	switch (route) {
	case NVIF_NOTIFY_V0_ROUTE_NVIF: {
		struct nvif_notify *notify = (void *)(unsigned long)token;
		assert(notify);
		nvif_notify(repv, sizeof(rep->v0), data, size);
	}
		break;
	default:
		assert(0);
		break;
	}
}

static void *
drm_client_event(void *arg)
{
	struct drm_client_priv *drm = arg;
	struct drm_event *e;
	char data[1024];
	ssize_t size;
	int i;

	while (1) {
		if ((size = read(drm->fd, data, sizeof(data))) <= 0)
			continue;

		for (i = 0; e = (void *)&data[i], i < size; i += e->length) {
			u32 size = e->length - sizeof(*e);
			u8 *data = (u8 *)e + sizeof(*e);
			switch (e->type) {
			case DRM_NOUVEAU_EVENT_NVIF:
				drm_client_notify(data, size);
				continue;
			default:
				break;
			}
			fprintf(stderr, "event %08x, %d\n", e->type, size);
		}
	}

	return NULL;
}

static void
drm_client_fini(void *priv)
{
	struct drm_client_priv *drm = priv;
	if (drm) {
		if (drm->fd >= 0) {
			if (drm->done) {
				pthread_cancel(drm->event);
				pthread_join(drm->event, NULL);
			}
			close(drm->fd);
		}
		free(drm);
	}
}

#define DRM_RENDER_PATH "/dev/dri/renderD"
#define DRM_RENDER_MIN   128
#define DRM_RENDER_MAX  (128 + 63)
static int
drm_client_init(const char *name, u64 device, const char *cfg,
		const char *dbg, void **ppriv)
{
	struct drm_client_priv *drm;
	drmVersionPtr ver;
	int ret, minor;
	char path[128];

	if (!(drm = *ppriv = calloc(1, sizeof(*drm))))
		return -ENOMEM;

	for (minor = DRM_RENDER_MIN; minor <= DRM_RENDER_MAX; minor++) {
		snprintf(path, sizeof(path), "/dev/dri/renderD%d", minor);
		if ((drm->fd = open(path, O_RDWR, 0)) < 0)
			continue;
		if ((ver = drmGetVersion(drm->fd)) == NULL)
			continue;
		if (!strcmp(ver->name, "nouveau"))
			break;
		drmFreeVersion(ver);
	}

	if (minor > DRM_RENDER_MAX)
		return -ENODEV;

	drm->version = (ver->version_major << 24) |
		       (ver->version_minor << 8) |
		        ver->version_patchlevel;
	drmFreeVersion(ver);
	if (drm->version < 0x01000200)
		return -ENOSYS;

	if ((ret = pthread_create(&drm->event, NULL, drm_client_event, drm)))
		return ret;

	drm->done = true;
	return 0;
}

const struct nvif_driver
nvif_driver_drm = {
	.name = "drm",
	.init = drm_client_init,
	.fini = drm_client_fini,
	.suspend = drm_client_suspend,
	.resume = drm_client_resume,
	.ioctl = drm_client_ioctl,
	.map = drm_client_map,
	.unmap = drm_client_unmap,
	.keep = true,
};
