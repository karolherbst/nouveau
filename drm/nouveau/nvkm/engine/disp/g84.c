/*
 * Copyright 2012 Red Hat Inc.
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
#include "nv50.h"
#include "head.h"
#include "ior.h"
#include "rootnv50.h"

static const struct nv50_disp_func
g84_disp = {
	.intr = nv50_disp_intr,
	.uevent = &nv50_disp_chan_uevent,
	.super = nv50_disp_super,
	.root = &g84_disp_root_oclass,
	.head.new = nv50_head_new,
	.outp.internal.crt = nv50_dac_output_new,
	.outp.internal.tmds = nv50_sor_output_new,
	.outp.internal.lvds = nv50_sor_output_new,
	.outp.external.tmds = nv50_pior_output_new,
	.outp.external.dp = nv50_pior_dp_new,
	.dac.nr = 3,
	.dac.new = nv50_dac_new,
	.dac.sense = nv50_dac_sense,
	.sor.nr = 2,
	.sor.new = g84_sor_new,
	.sor.hdmi = g84_hdmi_ctrl,
	.pior = { .nr = 3, .new = nv50_pior_new },
};

int
g84_disp_new(struct nvkm_device *device, int index, struct nvkm_disp **pdisp)
{
	return nv50_disp_new_(&g84_disp, device, index, 2, pdisp);
}
