/*
 * Copyright 2007 Dave Airlied
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */
/*
 * Authors: Dave Airlied <airlied@linux.ie>
 *	    Ben Skeggs   <darktama@iinet.net.au>
 *	    Jeremy Kolb  <jkolb@brandeis.edu>
 */
#include "nouveau_bo.h"
#include "nouveau_dma.h"
#include "nouveau_drv.h"

#include <nvif/push006c.h>

static inline uint32_t
nouveau_bo_mem_ctxdma(struct ttm_buffer_object *bo,
		      struct nouveau_channel *chan, struct ttm_mem_reg *reg)
{
	if (reg->mem_type == TTM_PL_TT)
		return NvDmaTT;
	return chan->vram.handle;
}

int
nv04_bo_move_m2mf(struct nouveau_channel *chan, struct ttm_buffer_object *bo,
		  struct ttm_mem_reg *old_reg, struct ttm_mem_reg *new_reg)
{
	struct nvif_push *push = chan->chan.push;
	u32 src_offset = old_reg->start << PAGE_SHIFT;
	u32 dst_offset = new_reg->start << PAGE_SHIFT;
	u32 page_count = new_reg->num_pages;
	int ret;

	ret = PUSH_WAIT(push, 3);
	if (ret)
		return ret;

	PUSH_NVSQ(push, NV039, 0x0184, nouveau_bo_mem_ctxdma(bo, chan, old_reg),
			       0x0188, nouveau_bo_mem_ctxdma(bo, chan, new_reg));

	page_count = new_reg->num_pages;
	while (page_count) {
		int line_count = (page_count > 2047) ? 2047 : page_count;

		ret = PUSH_WAIT(push, 11);
		if (ret)
			return ret;

		PUSH_NVSQ(push, NV039, 0x030c, src_offset,
				       0x0310, dst_offset,
				       0x0314, PAGE_SIZE, /* src_pitch */
				       0x0318, PAGE_SIZE, /* dst_pitch */
				       0x031c, PAGE_SIZE, /* line_length */
				       0x0320, line_count,
				       0x0324, 0x00000101,
				       0x0328, 0x00000000);
		PUSH_NVSQ(push, NV039, 0x0100, 0x00000000);

		page_count -= line_count;
		src_offset += (PAGE_SIZE * line_count);
		dst_offset += (PAGE_SIZE * line_count);
	}

	return 0;
}

int
nv04_bo_move_init(struct nouveau_channel *chan, u32 handle)
{
	struct nvif_push *push = chan->chan.push;
	int ret;

	ret = PUSH_WAIT(push, 4);
	if (ret)
		return ret;

	PUSH_NVSQ(push, NV039, 0x0000, handle);
	PUSH_NVSQ(push, NV039, 0x0180, chan->drm->ntfy.handle);
	return 0;
}
