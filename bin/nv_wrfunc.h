#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

#include <nvif/client.h>
#include <nvif/device.h>
#include <nvif/class.h>
#include <core/class.h>

#ifndef ENABLE
#define ENABLE NV_DEVICE_V0_DISABLE_MMIO
#endif
#ifndef DEBUG0
#define DEBUG0 0ULL
#endif

int
MAIN(int argc, char **argv)
{
	const char *drv = NULL;
	const char *cfg = NULL;
	const char *dbg = "fatal";
	u64 dev = ~0ULL;
	struct nvif_client *client;
	struct nvif_device *device;
	struct nv_device_v0 args = {};
	char *rstr = NULL;
	char *vstr = NULL;
	int quiet = 0;
	int ret, c;

	while ((c = getopt(argc, argv, "-a:b:c:d:q")) != -1) {
		switch (c) {
		case 'a': dev = strtoull(optarg, NULL, 0); break;
		case 'b': drv = optarg; break;
		case 'c': cfg = optarg; break;
		case 'd': dbg = optarg; break;
		case 'q':
			quiet = 1;
			break;
		case 1:
			if (rstr) {
				if (vstr)
					return 1;
				vstr = optarg;
			} else {
				rstr = optarg;
			}
			break;
		}
	}

	ret = nvif_client_new(drv, argv[0], dev, cfg, dbg, &client);
	if (ret)
		return ret;

	args.device  = ~0ULL;
	args.disable = ~ENABLE;
	args.debug0  = ~DEBUG0;

	ret = nvif_device_new(nvif_object(client), 0, NV_DEVICE,
			     &args, sizeof(args), &device);
	nvif_client_ref(NULL, &client);
	if (ret)
		return ret;

	while (rstr && *rstr != '\0') {
		unsigned long cnt = 1;
		unsigned long reg;
		unsigned long val;

		if ((reg = strtoul(rstr, &rstr, 0)) == ULONG_MAX)
			return 1;

		if (*rstr == '/') {
			if ((cnt = strtoul(rstr + 1, &rstr, 0)) == ULONG_MAX)
				return 1;
		} else
		if (*rstr == '+') {
			if ((cnt = strtoul(rstr + 1, &rstr, 0)) == ULONG_MAX)
				return 1;
			cnt /= sizeof(CAST);
		}

		if (*rstr == '=') {
			if ((val = strtoul(rstr + 1, &rstr, 0)) == ULONG_MAX)
				return 1;
		} else {
			if (!vstr ||
			    (val = strtoul(vstr, NULL, 0)) == ULONG_MAX)
				return 1;
		}

		switch (*rstr) {
		case ',':
			rstr++;
		case '\0':
			while (cnt--) {
				if (!quiet)
					printk(NAME" "FMTADDR" "FMTDATA"\n", reg, (CAST)val);
				WRITE(reg, val);
				reg += sizeof(CAST);
			}
			break;
		default:
			return 1;
		}
	}

	nvif_device_ref(NULL, &device);
	return 0;
}
