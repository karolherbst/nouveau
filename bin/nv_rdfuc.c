#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

#include <core/os.h>
#include <core/object.h>
#include <core/class.h>

int
main(int argc, char **argv)
{
	struct nouveau_object *client;
	struct nouveau_object *device;
	u32 fucbase = ~0;
	int segment = -1;
	int ret, c, i;

	while ((c = getopt(argc, argv, "-cd")) != -1) {
		switch (c) {
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

	ret = os_client_new(NULL, "info", argc, argv, &client);
	if (ret)
		return ret;

	ret = nouveau_object_new(client, ~0, 0, 0x0080,
				&(struct nv_device_class) {
					.device = ~0ULL,
					.disable = ~NV_DEVICE_DISABLE_MMIO,
					.debug0 = 0,
				}, sizeof(struct nv_device_class), &device);
	if (ret)
		return ret;

	if (segment == 0) {
		u32 size = (nv_ro32(device, fucbase + 0x0108) & 0x1ff) << 8;
		nv_wo32(device, fucbase + 0x0180, 0x02000000);
		for (i = 0; i < size; i += 4) {
			if (!(i & 0xff))
				nv_wo32(device, fucbase + 0x0188, i >> 8);
			printf("0x%08x\n", nv_ro32(device, fucbase + 0x0184));
		}
	} else {
		u32 size = (nv_ro32(device, fucbase + 0x0108) & 0x3fe00) >> 1;
		nv_wo32(device, fucbase + 0x01c0, 0x02000000);
		for (i = 0; i < size; i += 4)
			printf("0x%08x\n", nv_ro32(device, fucbase + 0x01c4));
	}


	os_client_del(&client);
	return 0;
}
