/*
 * Copyright 2018 Red Hat Inc.
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
 */
#include "core.h"
#include "head.h"

#include "nouveau_bo.h"

bool
core907d_caps_parse(struct nv50_disp *disp, struct nv50_core_caps *caps)
{
	struct nv50_core *core = disp->core;
	int i;

	if (core->func->ntfy_wait_done(disp->sync, 0x10,
				       disp->core->chan.base.device))
		return false;

	for (i = 0; i < 8; ++i) {
		uint32_t data = nouveau_bo_rd32(disp->sync, 0x14 + i * 2);
		caps->sor[i].dp.no_interlace |= !(data & (1 << 26));

		data = nouveau_bo_rd32(disp->sync, 0x15 + i * 2);
		caps->sor[i].dp.max_mhz = (data & 0xff) * 10;
		caps->sor[i].tmds.max_mhz = ((data >> 16) & 0xff) * 10;
		caps->sor[i].lvds.max_mhz = caps->sor[i].tmds.max_mhz;
	}

	return true;
}

static const struct nv50_core_func
core907d = {
	.init = core507d_init,
	.ntfy_init = core507d_ntfy_init,
	.ntfy_wait_done = core507d_ntfy_wait_done,
	.update = core507d_update,
	.caps_fetch = core507d_caps_fetch,
	.caps_parse = core907d_caps_parse,
	.head = &head907d,
	.dac = &dac907d,
	.sor = &sor907d,
};

int
core907d_new(struct nouveau_drm *drm, s32 oclass, struct nv50_core **pcore)
{
	return core507d_new_(&core907d, drm, oclass, pcore);
}
