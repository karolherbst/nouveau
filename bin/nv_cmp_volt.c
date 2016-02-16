/*
 * Copyright 2016 Karol Herbst
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

#include <nvif/client.h>
#include <nvif/device.h>
#include <nvif/class.h>

#include <nvkm/subdev/volt.h>

#include "util.h"

int
main(int argc, char **argv)
{
	struct nvif_client if_client;
	struct nvif_device if_device;
	struct nvkm_clk *clk;
	struct nvkm_volt *volt;
	struct nvkm_device *device;
	int ret;
	int old_voltage = 0, old_nouveau_voltage = 0, old_pstate = 0;
	int old_cstate = 0, old_temp = 0;

	ret = u_device("lib", argv[0], "error", true, true,
                       (1ULL << NVKM_SUBDEV_CLK) |
//                       (1ULL << NVKM_SUBDEV_FUSE) |
                       (1ULL << NVKM_SUBDEV_GPIO) |
//                       (1ULL << NVKM_SUBDEV_I2C) |
                       (1ULL << NVKM_SUBDEV_PCI) |
//                       (1ULL << NVKM_SUBDEV_THERM) |
//                       (1ULL << NVKM_SUBDEV_TIMER) |
                       (1ULL << NVKM_SUBDEV_VBIOS) |
                       (1ULL << NVKM_SUBDEV_VOLT),
                       0x00000000, &if_client, &if_device);

	if (ret < 0)
		return ret;

	device = nvxx_device(&if_device);
	clk = device->clk;
//	therm = device->therm;
	volt = device->volt;

	printf("current voltage (µV), expected voltage (µV), abs diff (µV),"
	       "rel diff nouveau/nvidia (%%), pstate, cstate, temperature"
	       "(°C)\n");
	while (true) {
		int gpc_clock = nvkm_clk_read(clk, nv_clk_src_gpc);
		int mem_clock = nvkm_clk_read(clk, nv_clk_src_mem);
		struct nvkm_pstate *pstate = NULL, *best_pstate = NULL;
		struct nvkm_cstate *cstate = NULL, *best_cstate = NULL;
		int mem_err, gpc_err;
		int new_voltage, new_nouveau_voltage, new_pstate, new_cstate;
		int new_temp;

		list_for_each_entry(pstate, &clk->states, head) {
			list_for_each_entry(cstate, &pstate->list, head) {
				if (!best_pstate) {
					best_pstate = pstate;
					best_cstate = cstate;
					gpc_err = abs(cstate->domain[nv_clk_src_gpc] - gpc_clock);
					mem_err = abs(cstate->domain[nv_clk_src_mem] - mem_clock);
					continue;
				}

				if (abs(cstate->domain[nv_clk_src_gpc] - gpc_clock) <= gpc_err &&
				    abs(cstate->domain[nv_clk_src_mem] - mem_clock) <= mem_err) {
					best_pstate = pstate;
					best_cstate = cstate;
					gpc_err = abs(cstate->domain[nv_clk_src_gpc] - gpc_clock);
					mem_err = abs(cstate->domain[nv_clk_src_mem] - mem_clock);
				}
			}

			if (!best_pstate) {
				best_pstate = pstate;
				mem_err = abs(cstate->domain[nv_clk_src_mem] - mem_clock);
				continue;
			} else if (!best_cstate && (pstate->base.domain[nv_clk_src_mem] - mem_clock) <= mem_err) {
				best_pstate = pstate;
				mem_err = abs(cstate->domain[nv_clk_src_mem] - mem_clock);
			}
		}

		if (!best_cstate)
			best_cstate = &best_pstate->base;

		new_voltage = nvkm_volt_get(volt);
		new_temp = nvkm_rd32(device, 0x20400);//nvkm_therm_temp_get(therm);
		new_nouveau_voltage = max(nvkm_volt_map(volt, best_cstate->voltage), nvkm_volt_map(volt, best_pstate->base.voltage));
		new_pstate = best_pstate->pstate;
		new_cstate = best_cstate->cstate;

		if (new_voltage != old_voltage || new_nouveau_voltage != old_nouveau_voltage || new_pstate != old_pstate || new_cstate != old_cstate || new_temp != old_temp) {
			old_voltage = new_voltage;
			old_nouveau_voltage = new_nouveau_voltage;
			old_pstate = new_pstate;
			old_cstate = new_cstate;
			old_temp = new_temp;
			printf("%i, %i, %i, %f, %i, %i, %i\n", new_voltage,
			       new_nouveau_voltage, new_nouveau_voltage - new_voltage,
			       100 * (double)new_nouveau_voltage / new_voltage,
			       new_pstate, new_cstate, new_temp);
		}
		usleep(100000);
	}

	return 0;
}
