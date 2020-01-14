/*
 * Copyright (c) 2016, NVIDIA CORPORATION. All rights reserved.
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
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */


#include "ls_ucode.h"
#include "acr.h"

#include <core/firmware.h>
#include <core/msgqueue.h>
#include <subdev/pmu.h>
#include <engine/sec2.h>
#include <subdev/mc.h>
#include <subdev/timer.h>

/**
 * acr_ls_ucode_load_msgqueue - load and prepare a ucode img for a msgqueue fw
 *
 * Load the LS microcode, desc and signature and pack them into a single
 * blob.
 */
static int
acr_ls_ucode_load_msgqueue(const struct nvkm_subdev *subdev, const char *name,
			   int maxver, struct ls_ucode_img *img)
{
	const struct firmware *image, *desc, *sig;
	char f[64];
	int ver, ret;

	snprintf(f, sizeof(f), "%s/image", name);
	ver = nvkm_firmware_get_version(subdev, f, 0, maxver, &image);
	if (ver < 0)
		return ver;
	img->ucode_data = kmemdup(image->data, image->size, GFP_KERNEL);
	nvkm_firmware_put(image);
	if (!img->ucode_data)
		return -ENOMEM;

	snprintf(f, sizeof(f), "%s/desc", name);
	ret = nvkm_firmware_get_version(subdev, f, ver, ver, &desc);
	if (ret < 0)
		return ret;
	memcpy(&img->ucode_desc, desc->data, sizeof(img->ucode_desc));
	img->ucode_size = ALIGN(img->ucode_desc.app_start_offset + img->ucode_desc.app_size, 256);
	nvkm_firmware_put(desc);

	snprintf(f, sizeof(f), "%s/sig", name);
	ret = nvkm_firmware_get_version(subdev, f, ver, ver, &sig);
	if (ret < 0)
		return ret;
	img->sig_size = sig->size;
	img->sig = kmemdup(sig->data, sig->size, GFP_KERNEL);
	nvkm_firmware_put(sig);
	if (!img->sig)
		return -ENOMEM;

	return ver;
}

int
acr_ls_ucode_load_pmu(const struct nvkm_secboot *sb, int maxver,
		      struct ls_ucode_img *img)
{
	int ret;

	ret = acr_ls_ucode_load_msgqueue(&sb->subdev, "pmu", maxver, img);
	if (ret)
		return ret;

	return 0;
}

int
acr_ls_ucode_load_sec2(const struct nvkm_secboot *sb, int maxver,
		       struct ls_ucode_img *img)
{
	int ver;

	ver = acr_ls_ucode_load_msgqueue(&sb->subdev, "sec2", maxver, img);
	if (ver < 0)
		return ver;

	return ver;
}
