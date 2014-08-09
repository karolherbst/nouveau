#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

#include <nvif/client.h>
#include <nvif/driver.h>
#include <nvif/device.h>
#include <nvif/class.h>

int
main(int argc, char **argv)
{
	const char *drv = NULL;
	const char *cfg = NULL;
	const char *dbg = "info";
	u64 dev = ~0ULL;
	struct nvif_client *client;
	struct nvif_device *device;
	bool suspend = false, wait = false;
	int ret, c;

	while ((c = getopt(argc, argv, "-a:b:c:d:sw")) != -1) {
		switch (c) {
		case 'a': dev = strtoull(optarg, NULL, 0); break;
		case 'b': drv = optarg; break;
		case 'c': cfg = optarg; break;
		case 'd': dbg = optarg; break;
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

	ret = nvif_client_new(drv, argv[0], dev, cfg, dbg, &client);
	if (ret)
		return ret;

	ret = nvif_device_new(nvif_object(client), 0, NV_DEVICE,
			      &(struct nv_device_v0) {
					.device = ~0ULL,
					.disable = 0ULL,
					.debug0 = 0ULL,
			      }, sizeof(struct nv_device_v0), &device);
	nvif_client_ref(NULL, &client);
	if (ret)
		return ret;

	if (suspend) {
		client->driver->suspend(client);
		client->driver->resume(client);
	}

	while (wait && (c = getchar()) == EOF) {
		sched_yield();
	}

	printf("shutting down...\n");
	nvif_device_ref(NULL, &device);
	printf("done!\n");
	return ret;
}
