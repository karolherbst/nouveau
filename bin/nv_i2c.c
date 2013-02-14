#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

#include <core/os.h>
#include <core/object.h>
#include <core/class.h>

#include <core/device.h>

#include <subdev/i2c.h>

struct nouveau_object *client;
struct nouveau_object *device;

static void
print_port(struct nouveau_i2c_port *port)
{
	printf("port 0x%02x: type %04x\n", port->index, nv_mclass(port));
}

int
main(int argc, char **argv)
{
	struct nouveau_i2c_port *port;
	struct nouveau_i2c *i2c;
	int addr = -1, reg = -1, val = -1;
	int action = -1, index = -1;
	int ret, c;

	while ((c = getopt(argc, argv, "-")) != -1) {
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
		}
	}

	ret = os_client_new(NULL, "error", argc, argv, &client);
	if (ret)
		return ret;

	ret = nouveau_object_new(client, ~0, 0, 0x0080,
				&(struct nv_device_class) {
					.device = ~0ULL,
					.disable = ~(NV_DEVICE_DISABLE_MMIO |
						     NV_DEVICE_DISABLE_IDENTIFY|
						     NV_DEVICE_DISABLE_VBIOS |
						     NV_DEVICE_DISABLE_CORE),
					.debug0 = ~((1 << NVDEV_SUBDEV_VBIOS) |
						    (1 << NVDEV_SUBDEV_I2C)),
				}, sizeof(struct nv_device_class), &device);
	if (ret)
		return ret;

	i2c = nouveau_i2c(device);

	if (action < 0) {
		list_for_each_entry(port, &i2c->ports, head) {
			print_port(port);
		}
	} else {
		port = i2c->find(i2c, index);
		if (!port) {
			ret = -ENOENT;
			goto done;
		}

		print_port(port);
	}

	switch (action) {
	case 0:
		if (addr < 0) {
			for (addr = 0; addr < 128; addr++) {
				if ((addr & 0x0f) == 0x00)
					printf("%02x:", addr);
				if ((val = nv_rdi2cr(port, addr, 0x00)) >= 0)
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
				if ((val = nv_rdi2cr(port, addr, reg)) >= 0)
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
		val = nv_rdi2cr(port, addr, reg);
		printf("%02x[%02x]: ", addr, reg);
		if (val < 0)
			printf("%s\n", strerror(val));
		else
			printf("%02x\n", val);
		break;
	case 3:
		printf("%02x[%02x]: %02x", addr, reg, val);
		ret = nv_wri2cr(port, addr, reg, val);
		if (ret < 0)
			printf("%s", strerror(ret));
		printf("\n");
		break;
	}

done:
	os_client_del(&client);
	return ret;
}
