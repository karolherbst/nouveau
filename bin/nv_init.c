#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

#include <core/os.h>
#include <core/object.h>
#include <core/class.h>

#include <core/device.h>

struct nouveau_object *client;
struct nouveau_object *device;

int
main(int argc, char **argv)
{
	bool suspend = false, wait = false;
	int ret, c;

	while ((c = getopt(argc, argv, "-sw")) != -1) {
		switch (c) {
		case 's':
			suspend = true;
			break;
		case 'w':
			wait = true;
			break;
		case 1:
			return -EINVAL;
		}
	}

	ret = os_client_new(NULL, "trace", argc, argv, &client);
	if (ret)
		return ret;

	ret = nouveau_object_new(client, ~0, 0, 0x0080,
				&(struct nv_device_class) {
					.device = ~0ULL,
					.disable = 0ULL,
					.debug0 = 0ULL,
				}, sizeof(struct nv_device_class), &device);
	if (ret)
		return ret;

	if (suspend) {
		os_suspend();
		os_resume();
	}

	while (wait && (c = getchar()) == EOF) {
		sched_yield();
	}

	os_client_del(&client);
	nouveau_object_debug();
	return ret;
}
