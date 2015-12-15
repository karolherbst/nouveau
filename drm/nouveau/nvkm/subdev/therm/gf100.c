/*
 * Copyright 2015 The Nouveau community
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
 * Authors: Karol Herbst
 */
#include "priv.h"

void
gf100_print_fsrm_config(struct nvkm_therm *therm)
{
	struct nvkm_device *device = therm->subdev.device;
	int cfg_5, cfg_low, thr_2, thr_6, thr_8, thr_crit;

	cfg_5    = nvkm_rd32(device, 0x020074);
	cfg_low  = nvkm_rd32(device, 0x02010c);
	thr_crit = nvkm_rd32(device, 0x020480);
	thr_2    = nvkm_rd32(device, 0x0204c0);
	thr_6    = nvkm_rd32(device, 0x0204d8);
	thr_8    = nvkm_rd32(device, 0x0204e0);

	nvkm_debug(&therm->subdev, "FSRM config: %i/%i/%i/%i => %x/%x/%x/off\n",
		thr_8, thr_6, thr_2, thr_crit, (cfg_low & 0x38) >> 3, cfg_low & 0x7, 0x8 + (cfg_5 & 0x70 >> 4));
	if (thr_crit < 90 || thr_crit > 115)
		nvkm_error(&therm->subdev, "invalid value for crit threshold: %i\n", thr_crit);
}

static const struct nvkm_therm_func
gf100_therm = {
	.init = gt215_therm_init,
	.fini = g84_therm_fini,
	.pwm_ctrl = nv50_fan_pwm_ctrl,
	.pwm_get = nv50_fan_pwm_get,
	.pwm_set = nv50_fan_pwm_set,
	.pwm_clock = nv50_fan_pwm_clock,
	.temp_get = g84_temp_get,
	.fan_sense = gt215_therm_fan_sense,
	.program_alarms = nvkm_therm_program_alarms_polling,
	.fsrm_verify = gf100_print_fsrm_config,
};

int
gf100_therm_new(struct nvkm_device *device, int index,
	       struct nvkm_therm **ptherm)
{
	return nvkm_therm_new_(&gf100_therm, device, index, ptherm);
}
