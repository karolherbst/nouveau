#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

#include <nvif/client.h>
#include <nvif/device.h>
#include <nvif/class.h>

#include "util.h"

static void
show_adapter(struct i2c_adapter *adap, int adapter)
{
	printf("i2c %d: %s\n", adapter, adap->name);
}

static struct i2c_adapter *
find_adapter(struct nvif_device *device, int adapter)
{
	struct nvkm_i2c *i2c = nvxx_device(device)->i2c;
	struct nvkm_i2c_bus *bus;
	struct nvkm_i2c_aux *aux;
	int i = 0;

	if (i2c) {
		list_for_each_entry(bus, &i2c->bus, head) {
			if (i++ == adapter)
				return &bus->i2c;
		}

		list_for_each_entry(aux, &i2c->aux, head) {
			if (i++ == adapter)
				return &aux->i2c;
		}
	}

	return NULL;
}

int
main(int argc, char **argv)
{
	struct nvif_client client;
	struct nvif_device device;
	struct i2c_adapter *adap;
	int addr = -1, reg = -1, val = -1;
	int action = -1, index = -1;
	int ret, c;

	while ((c = getopt(argc, argv, "-"U_GETOPT)) != -1) {
		switch (c) {
		case 1:
			if (action < 0) {
				if (!strcasecmp(optarg, "scan"))
					action = 0;
				else
				if (!strcasecmp(optarg, "rd"))
					action = 2;
				else
				if (!strcasecmp(optarg, "wr"))
					action = 3;
				else
					return -EINVAL;
			} else
			if (action >= 0 && index < 0) {
				index = strtoul(optarg, NULL, 0);
			} else
			if (action >= 0 && addr < 0) {
				addr = strtoul(optarg, NULL, 0);
				if (addr >= 128)
					return -EINVAL;
			} else
			if (action >= 2 && reg < 0) {
				reg = strtoul(optarg, NULL, 0);
				if (addr >= 256)
					return -EINVAL;
			} else
			if (action >= 3 && val < 0) {
				val = strtoul(optarg, NULL, 0);
				if (addr >= 256)
					return -EINVAL;
			} else
				return -EINVAL;
			break;
		default:
			if (!u_option(c))
				return 1;
			break;
		}
	}

	ret = u_device("lib", argv[0], "error", true, true,
		       (1ULL << NVKM_SUBDEV_PCI) |
		       (1ULL << NVKM_SUBDEV_VBIOS) |
		       (1ULL << NVKM_SUBDEV_I2C),
		       0x00000000, &client, &device);

	if (action < 0) {
		for (index = 0; (adap = find_adapter(&device, index)); index++) {
			show_adapter(adap, index);
		}
	} else {
		adap = find_adapter(&device, index);
		if (!adap) {
			ret = -ENOENT;
			goto done;
		}

		show_adapter(adap, index);
	}

	switch (action) {
	case 0:
		if (addr < 0) {
			for (addr = 0; addr < 128; addr++) {
				if ((addr & 0x0f) == 0x00)
					printf("%02x:", addr);
				if ((val = nvkm_rdi2cr(adap, addr, 0x00)) >= 0)
					printf(" %02x", addr);
				else
					printf(" --");
				if ((addr & 0x0f) == 0x0f)
					printf("\n");
				fflush(stdout);
			}
			break;
		} else {
			for (reg = 0; reg < 256; reg++) {
				if ((reg & 0x0f) == 0x00)
					printf("%02x:", reg);
				if ((val = nvkm_rdi2cr(adap, addr, reg)) >= 0)
					printf(" %02x", val);
				else
					printf(" --");
				if ((reg & 0x0f) == 0x0f)
					printf("\n");
				fflush(stdout);
			}
		}
		break;
	case 2:
		val = nvkm_rdi2cr(adap, addr, reg);
		printf("%02x[%02x]: ", addr, reg);
		if (val < 0)
			printf("%s\n", strerror(val));
		else
			printf("%02x\n", val);
		break;
	case 3:
		printf("%02x[%02x]: %02x", addr, reg, val);
		ret = nvkm_wri2cr(adap, addr, reg, val);
		if (ret < 0)
			printf("%s", strerror(ret));
		printf("\n");
		break;
	}

done:
	nvif_device_fini(&device);
	nvif_client_fini(&client);
	return ret;
}
