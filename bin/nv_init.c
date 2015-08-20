#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

#include <nvif/client.h>
#include <nvif/driver.h>
#include <nvif/device.h>
#include <nvif/class.h>

#include "util.h"

int
main(int argc, char **argv)
{
	struct nvif_client client;
	struct nvif_device device;
	bool suspend = false, wait = false;
	int ret, c;

	while ((c = getopt(argc, argv, "sw"U_GETOPT)) != -1) {
		switch (c) {
		case 's':
			suspend = true;
			break;
		case 'w':
			wait = true;
			break;
		default:
			if (!u_option(c))
				return 1;
			break;
		}
	}

	ret = u_device(NULL, argv[0], "info", true, true, ~0ULL,
		       0x00000000, &client, &device);
	if (ret)
		return ret;

	if (suspend) {
		nvif_client_suspend(&client);
		nvif_client_resume(&client);
	}

	while (wait && (c = getchar()) == EOF) {
		sched_yield();
	}

	printf("shutting down...\n");
	nvif_device_fini(&device);
	nvif_client_fini(&client);
	printf("done!\n");
	return ret;
}
