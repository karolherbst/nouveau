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
gm200_disp = {
	.intr = gf119_disp_intr,
	.intr_error = gf119_disp_intr_error,
	.uevent = &gf119_disp_chan_uevent,
	.super = gf119_disp_super,
	.root = &gm200_disp_root_oclass,
	.head.new = gf119_head_new,
	.outp.internal.crt = nv50_dac_output_new,
	.outp.internal.tmds = nv50_sor_output_new,
	.outp.internal.lvds = nv50_sor_output_new,
	.outp.internal.dp = gm200_sor_dp_new,
	.dac.nr = 3,
	.dac.new = gf119_dac_new,
	.dac.power = nv50_dac_power,
	.dac.sense = nv50_dac_sense,
	.sor.nr = 4,
	.sor.new = gm200_sor_new,
	.sor.power = nv50_sor_power,
	.sor.hda_eld = gf119_hda_eld,
	.sor.hdmi = gk104_hdmi_ctrl,
	.sor.magic = gm200_sor_magic,
};

int
gm200_disp_new(struct nvkm_device *device, int index, struct nvkm_disp **pdisp)
{
	return gf119_disp_new_(&gm200_disp, device, index, pdisp);
}
