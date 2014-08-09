#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

#include <nvif/client.h>
#include <nvif/device.h>
#include <nvif/class.h>

int
main(int argc, char **argv)
{
	const char *drv = NULL;
	const char *cfg = NULL;
	const char *dbg = "error";
	u64 dev = ~0ULL;
	struct nvif_client *client;
	struct nvif_device *device;
	u32 fucbase = ~0;
	int segment = -1;
	int ret, c, i;

	while ((c = getopt(argc, argv, "-a:b:cd")) != -1) {
		switch (c) {
		case 'a': dev = strtoull(optarg, NULL, 0); break;
		case 'b': drv = optarg; break;
		case 'c':
			segment = 0;
			break;
		case 'd':
			segment = 1;
			break;
		case 1:
			fucbase = strtol(optarg, NULL, 0);
			break;
		}
	}

	if (fucbase == ~0 || segment < 0 || segment > 1)
		return 1;

	ret = nvif_client_new(drv, argv[0], dev, cfg, dbg, &client);
	if (ret)
		return ret;

	ret = nvif_device_new(nvif_object(client), 0x00000000, NV_DEVICE,
			      &(struct nv_device_v0) {
					.device = ~0ULL,
					.disable = ~NV_DEVICE_V0_DISABLE_MMIO,
					.debug0 = 0,
			      }, sizeof(struct nv_device_v0), &device);
	nvif_client_ref(NULL, &client);
	if (ret)
		return ret;

	if (segment == 0) {
		u32 size = (nvif_rd32(device, fucbase + 0x0108) & 0x1ff) << 8;
		nvif_wr32(device, fucbase + 0x0180, 0x02000000);
		for (i = 0; i < size; i += 4) {
			if (!(i & 0xff))
				nvif_wr32(device, fucbase + 0x0188, i >> 8);
			printf("0x%08x\n", nvif_rd32(device, fucbase + 0x0184));
		}
	} else {
		u32 size = (nvif_rd32(device, fucbase + 0x0108) & 0x3fe00) >> 1;
		nvif_wr32(device, fucbase + 0x01c0, 0x02000000);
		for (i = 0; i < size; i += 4)
			printf("0x%08x\n", nvif_rd32(device, fucbase + 0x01c4));
	}

	nvif_device_ref(NULL, &device);
	return 0;
}
