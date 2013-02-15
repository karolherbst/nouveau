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
print_chan(struct nouveau_i2c_port *chan)
{
	printf("chan 0x%02x: type %04x\n", chan->index, nv_mclass(chan));
}

int
main(int argc, char **argv)
{
	struct nouveau_i2c_port *chan;
	struct nouveau_i2c *i2c;
	int action = -1, index = -1;
	int addr = -1, val = -1;
	int ret, c;
	u8 data;

	while ((c = getopt(argc, argv, "-")) != -1) {
		switch (c) {
		case 1:
			if (action < 0) {
				if (!strcasecmp(optarg, "rd"))
					action = 0;
				else
				if (!strcasecmp(optarg, "wr"))
					action = 1;
				else
					return -EINVAL;
			} else
			if (action >= 0 && index < 0) {
				index = strtoul(optarg, NULL, 0);
			} else
			if (action >= 0 && addr < 0) {
				addr = strtoul(optarg, NULL, 0);
				if (addr > 0x000fffff)
					return -EINVAL;
			} else
			if (action >= 1 && data < 0) {
				val = strtoul(optarg, NULL, 0);
				if (val > 0xff)
					return -EINVAL;
				data = val;
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
		list_for_each_entry(chan, &i2c->ports, head) {
			if ((nv_mclass(chan) & 0x00ff) == 0x06)
				print_chan(chan);
		}
	} else {
		chan = i2c->find(i2c, index);
		if (!chan || (nv_mclass(chan) & 0x00ff) != 0x06) {
			ret = -ENOENT;
			goto done;
		}

		print_chan(chan);
	}

	switch (action) {
	case 0:
		ret = nv_rdaux(chan, addr, &data, 1);
		printf("%05x: ", addr);
		if (ret < 0)
			printf("%s\n", strerror(ret));
		else
			printf("%02x\n", data);
		break;
	case 1:
		printf("%05x: %02x", addr, data);
		ret = nv_wraux(chan, addr, &data, 1);
		if (ret < 0)
			printf(" - %s", strerror(ret));
		printf("\n");
		break;
	}

done:
	os_client_del(&client);
	return ret;
}
