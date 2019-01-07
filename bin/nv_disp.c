#include <stdlib.h>

#include <nvif/device.h>

static unsigned long chan = 0;

static void
nv50_disp_mthd(struct nvif_device *device, u16 mthd, u32 data)
{
	u32 ctrl = nvif_rd32(&device->object, 0x610300 + (chan * 8));
	nvif_wr32(&device->object, 0x610300 + (chan * 8), ctrl | 0x00000001);
	nvif_wr32(&device->object, 0x610304 + (chan * 8), data);
	nvif_wr32(&device->object, 0x610300 + (chan * 8), mthd | 0x80000001);
	while (nvif_rd32(&device->object, 0x610300 + (chan * 8)) & 0x80000000) {}
	nvif_wr32(&device->object, 0x610300 + (chan * 8), ctrl);
}

static void
gf119_disp_mthd(struct nvif_device *device, u16 mthd, u32 data)
{
	u32 ctrl = nvif_rd32(&device->object, 0x610700 + (chan * 16));
	nvif_wr32(&device->object, 0x610700 + (chan * 16), ctrl | 0x00000001);
	nvif_wr32(&device->object, 0x610704 + (chan * 16), data);
	nvif_wr32(&device->object, 0x610700 + (chan * 16), mthd | 0x80000001);
	while (nvif_rd32(&device->object, 0x610700 + (chan * 16)) & 0x80000000) {}
	nvif_wr32(&device->object, 0x610700 + (chan * 16), ctrl);
}

static void
gv100_disp_mthd(struct nvif_device *device, u16 mthd, u32 data)
{
	u32 ctrl = nvif_rd32(&device->object, 0x610800 + (chan * 8));
	nvif_wr32(&device->object, 0x610800 + (chan * 8), ctrl | 0x00000001);
	nvif_wr32(&device->object, 0x610804 + (chan * 8), data);
	nvif_wr32(&device->object, 0x610800 + (chan * 8), mthd | 0x80000001);
	while (nvif_rd32(&device->object, 0x610800 + (chan * 8)) & 0x80000000) {}
	nvif_wr32(&device->object, 0x610800 + (chan * 8), ctrl);
}

static void
nv_disp(struct nvif_device *device, u16 mthd, u32 data)
{
	if (device->info.family >= NV_DEVICE_INFO_V0_VOLTA) {
		gv100_disp_mthd(device, mthd, data);
	} else
	if (device->info.chipset >= 0xd0) {
		gf119_disp_mthd(device, mthd, data);
	} else
	if (device->info.family >= NV_DEVICE_INFO_V0_TESLA) {
		nv50_disp_mthd(device, mthd, data);
	} else {
		printk("unsupported chipset\n");
		exit(1);
	}
}

#define FMTADDR    "0x%04llx"
#define FMTDATA    "0x%08x"
#define NAME       "nv_disp"
#define CAST       u32
#define WRITE(o,v) nv_disp(device, (o), (v))
#define MAIN       main_
#define DETECT     true
#include "nv_wrfunc.h"

int
main(int argc, char **argv)
{
	if (argc < 2 || ((chan = strtol(argv[1], NULL, 0)) == ULONG_MAX))
		return 0;

	argv[1] = argv[0];
	return main_(argc - 1, argv + 1);
}
