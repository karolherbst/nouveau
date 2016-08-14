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

#include <nvkm/subdev/clk.h>

#include <signal.h>
#include <sys/time.h>

#include "util.h"

static uint32_t duration = 1000;
static uint32_t fallTemp = 0;
struct nvkm_device *device = NULL;

uint64_t
get_time(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);

	return ((uint64_t)tv.tv_sec) * 1000 + (tv.tv_usec / 1000);
}

void
fake_temp(struct nvkm_device *device, int t)
{
	printf("faking temp to %i °C\n", t);
	if (t == 0)
		nvkm_mask(device, 0x20008, 0x3fc08000, 0x0);
	else
		nvkm_mask(device, 0x20008, 0x3fc08000, ((t & 0x7f) << 22) | 0x8000);
}

static void check_clocks(struct nvkm_clk* clk, uint64_t start_time)
{
	int old_clock = 0;
	while (get_time() < start_time + duration) {
		int clock = nvkm_clk_read(clk, nv_clk_src_gpc);

		if (clock == old_clock)
			continue;

		old_clock = clock;

		printf("%*li   %i\n", 6, get_time(), clock);
	}
}

void
done(void)
{
	if (device)
		fake_temp(device, 0);
}

void
signalHandler(int signal)
{
	exit(0);
}

int
main(int argc, char **argv)
{
	struct nvif_client if_client;
	struct nvif_device if_device;
	struct nvkm_clk *clk;
	int ret, c, i, t = 0;

	atexit(done);
	for (i = 0; i < 32; ++i)
		signal(i, signalHandler);

	while ((c = getopt(argc, argv, "f:t:T:"U_GETOPT)) != -1) {
		switch (c) {
		case 'T':
			t = atoi(optarg);
			break;
		case 't':
			duration = atoi(optarg);
			break;
		case 'f':
			fallTemp = atoi(optarg);
			break;
		default:
			if (!u_option(c))
				return 1;
			break;
		}
	}

	ret = u_device("lib", argv[0], "error", true, true,
	               (1ULL << NVKM_SUBDEV_CLK) |
//                     (1ULL << NVKM_SUBDEV_FUSE) |
//	               (1ULL << NVKM_SUBDEV_GPIO) |
	               (1ULL << NVKM_SUBDEV_PCI) |
	               (1ULL << NVKM_SUBDEV_VBIOS) |
//	               (1ULL << NVKM_SUBDEV_VOLT) |
                       0,
	               0x00000000, &if_client, &if_device);

	if (ret < 0)
		return ret;

	device = nvxx_device(&if_device);
	clk = device->clk;

	uint64_t start_time = get_time();

	fake_temp(device, t);
	printf("time      gpc_clock\n");

	if (fallTemp > 0) {
		for (; t > 0; t = t - fallTemp) {
			fake_temp(device, t);
			check_clocks(clk, get_time());
		}
	} else {
		fake_temp(device, t);
		check_clocks(clk, start_time);
	}

	fake_temp(device, 0);

	return 0;
}
