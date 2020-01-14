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
#include <subdev/acr.h>
#include <subdev/timer.h>

static const struct nvkm_acr_lsf_func
gp102_sec2_acr_0 = {
};

void
gp102_sec2_intr(struct nvkm_sec2 *sec2)
{
	struct nvkm_subdev *subdev = &sec2->engine.subdev;
	struct nvkm_falcon *falcon = &sec2->falcon;
	u32 disp = nvkm_falcon_rd32(falcon, 0x01c);
	u32 intr = nvkm_falcon_rd32(falcon, 0x008) & disp & ~(disp >> 16);

	if (intr & 0x00000040) {
		schedule_work(&sec2->work);
		nvkm_falcon_wr32(falcon, 0x004, 0x00000040);
		intr &= ~0x00000040;
	}

	if (intr) {
		nvkm_error(subdev, "unhandled intr %08x\n", intr);
		nvkm_falcon_wr32(falcon, 0x004, intr);
	}
}

void
gp102_sec2_flcn_bind_context(struct nvkm_falcon *falcon,
			     struct nvkm_memory *ctx)
{
	struct nvkm_device *device = falcon->owner->device;

	nvkm_falcon_v1_bind_context(falcon, ctx);
	if (!ctx)
		return;

	/* Not sure if this is a WAR for a HW issue, or some additional
	 * programming sequence that's needed to properly complete the
	 * context switch we trigger above.
	 *
	 * Fixes unreliability of booting the SEC2 RTOS on Quadro P620,
	 * particularly when resuming from suspend.
	 *
	 * Also removes the need for an odd workaround where we needed
	 * to program SEC2's FALCON_CPUCTL_ALIAS_STARTCPU twice before
	 * the SEC2 RTOS would begin executing.
	 */
	nvkm_msec(device, 10,
		u32 irqstat = nvkm_falcon_rd32(falcon, 0x008);
		u32 flcn0dc = nvkm_falcon_rd32(falcon, 0x0dc);
		if ((irqstat & 0x00000008) &&
		    (flcn0dc & 0x00007000) == 0x00005000)
			break;
	);

	nvkm_falcon_mask(falcon, 0x004, 0x00000008, 0x00000008);
	nvkm_falcon_mask(falcon, 0x058, 0x00000002, 0x00000002);

	nvkm_msec(device, 10,
		u32 flcn0dc = nvkm_falcon_rd32(falcon, 0x0dc);
		if ((flcn0dc & 0x00007000) == 0x00000000)
			break;
	);
}

static const struct nvkm_falcon_func
gp102_sec2_flcn = {
	.debug = 0x408,
	.fbif = 0x600,
	.load_imem = nvkm_falcon_v1_load_imem,
	.load_dmem = nvkm_falcon_v1_load_dmem,
	.read_dmem = nvkm_falcon_v1_read_dmem,
	.emem_addr = 0x01000000,
	.bind_context = gp102_sec2_flcn_bind_context,
	.wait_for_halt = nvkm_falcon_v1_wait_for_halt,
	.clear_interrupt = nvkm_falcon_v1_clear_interrupt,
	.set_start_addr = nvkm_falcon_v1_set_start_addr,
	.start = nvkm_falcon_v1_start,
	.enable = nvkm_falcon_v1_enable,
	.disable = nvkm_falcon_v1_disable,
};

const struct nvkm_sec2_func
gp102_sec2 = {
	.flcn = &gp102_sec2_flcn,
	.intr = gp102_sec2_intr,
};

MODULE_FIRMWARE("nvidia/gp102/sec2/desc.bin");
MODULE_FIRMWARE("nvidia/gp102/sec2/image.bin");
MODULE_FIRMWARE("nvidia/gp102/sec2/sig.bin");
MODULE_FIRMWARE("nvidia/gp104/sec2/desc.bin");
MODULE_FIRMWARE("nvidia/gp104/sec2/image.bin");
MODULE_FIRMWARE("nvidia/gp104/sec2/sig.bin");
MODULE_FIRMWARE("nvidia/gp106/sec2/desc.bin");
MODULE_FIRMWARE("nvidia/gp106/sec2/image.bin");
MODULE_FIRMWARE("nvidia/gp106/sec2/sig.bin");
MODULE_FIRMWARE("nvidia/gp107/sec2/desc.bin");
MODULE_FIRMWARE("nvidia/gp107/sec2/image.bin");
MODULE_FIRMWARE("nvidia/gp107/sec2/sig.bin");

const struct nvkm_acr_lsf_func
gp102_sec2_acr_1 = {
};

int
gp102_sec2_load(struct nvkm_sec2 *sec2, int ver,
		const struct nvkm_sec2_fwif *fwif)
{
	return nvkm_acr_lsfw_load_sig_image_desc_v1(&sec2->engine.subdev,
						    &sec2->falcon,
						    NVKM_ACR_LSF_SEC2, "sec2/",
						    ver, fwif->acr);
}

MODULE_FIRMWARE("nvidia/gp102/sec2/desc-1.bin");
MODULE_FIRMWARE("nvidia/gp102/sec2/image-1.bin");
MODULE_FIRMWARE("nvidia/gp102/sec2/sig-1.bin");
MODULE_FIRMWARE("nvidia/gp104/sec2/desc-1.bin");
MODULE_FIRMWARE("nvidia/gp104/sec2/image-1.bin");
MODULE_FIRMWARE("nvidia/gp104/sec2/sig-1.bin");
MODULE_FIRMWARE("nvidia/gp106/sec2/desc-1.bin");
MODULE_FIRMWARE("nvidia/gp106/sec2/image-1.bin");
MODULE_FIRMWARE("nvidia/gp106/sec2/sig-1.bin");
MODULE_FIRMWARE("nvidia/gp107/sec2/desc-1.bin");
MODULE_FIRMWARE("nvidia/gp107/sec2/image-1.bin");
MODULE_FIRMWARE("nvidia/gp107/sec2/sig-1.bin");

static const struct nvkm_sec2_fwif
gp102_sec2_fwif[] = {
	{ 1, gp102_sec2_load, &gp102_sec2, &gp102_sec2_acr_1 },
	{ 0, gp102_sec2_load, &gp102_sec2, &gp102_sec2_acr_0 },
	{}
};

int
gp102_sec2_new(struct nvkm_device *device, int index, struct nvkm_sec2 **psec2)
{
	return nvkm_sec2_new_(gp102_sec2_fwif, device, index, 0, psec2);
}
