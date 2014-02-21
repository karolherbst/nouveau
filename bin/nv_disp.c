#include <stdlib.h>

#include <core/os.h>
#include <core/object.h>
#include <core/device.h>

static unsigned long chan = 0;

static void
nv_disp(struct nouveau_object *device, u16 mthd, u32 data)
{
	if (nv_device(device)->card_type >= NV_50 &&
	    nv_device(device)->card_type <= NV_C0) {
		u32 ctrl = nv_ro32(device, 0x610300 + (chan * 8));
		nv_wo32(device, 0x610300 + (chan * 8), ctrl | 0x00000001);
		nv_wo32(device, 0x610304 + (chan * 8), data);
		nv_wo32(device, 0x610300 + (chan * 8), mthd | 0x80000001);
		while (nv_ro32(device, 0x610300 + (chan * 8)) & 0x80000000) {}
		nv_wo32(device, 0x610300 + (chan * 8), ctrl);
	} else
	if (nv_device(device)->card_type >= NV_D0 &&
	    nv_device(device)->card_type <= NV_E0) {
		u32 ctrl = nv_ro32(device, 0x610700 + (chan * 16));
		nv_wo32(device, 0x610700 + (chan * 16), ctrl | 0x00000001);
		nv_wo32(device, 0x610704 + (chan * 16), data);
		nv_wo32(device, 0x610700 + (chan * 16), mthd | 0x80000001);
		while (nv_ro32(device, 0x610700 + (chan * 16)) & 0x80000000) {}
		nv_wo32(device, 0x610700 + (chan * 16), ctrl);
	} else {
		printk("unsupported chipset\n");
		exit(1);
	}
}

#define FMTADDR    "0x%04lx"
#define FMTDATA    "0x%08x"
#define NAME       "nv_disp"
#define CAST       u32
#define WRITE(o,v) nv_disp(device, (o), (v))
#define MAIN       main_
#define ENABLE     (NV_DEVICE_DISABLE_MMIO | NV_DEVICE_DISABLE_IDENTIFY)
#include "nv_wrfunc.h"

int
main(int argc, char **argv)
{
	if (argc < 2 || ((chan = strtol(argv[1], NULL, 0)) == ULONG_MAX))
		return 0;

	argv[1] = argv[0];
	return main_(argc - 1, argv + 1);
}
