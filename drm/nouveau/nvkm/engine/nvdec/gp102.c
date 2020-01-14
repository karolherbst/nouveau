/*
 * Copyright (c) 2017, NVIDIA CORPORATION. All rights reserved.
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
#include "priv.h"

static const struct nvkm_nvdec_func
gp102_nvdec = {
};

static int
gp102_nvdec_nofw(struct nvkm_nvdec *nvdec, int ver,
		 const struct nvkm_nvdec_fwif *fwif)
{
	return 0;
}

static const struct nvkm_nvdec_fwif
gp102_nvdec_fwif[] = {
	{ -1, gp102_nvdec_nofw, &gp102_nvdec },
	{}
};

int
gp102_nvdec_new(struct nvkm_device *device, int index,
		struct nvkm_nvdec **pnvdec)
{
	return nvkm_nvdec_new_(gp102_nvdec_fwif, device, index, pnvdec);
}
