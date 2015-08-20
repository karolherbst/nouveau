#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

#include <nvif/client.h>
#include <nvif/device.h>
#include <nvif/class.h>

#ifndef DETECT
#define DETECT false
#endif

#include "util.h"

int
MAIN(int argc, char **argv)
{
	struct nvif_client client;
	struct nvif_device _device, *device = &_device;
	char *rstr = NULL;
	char *vstr = NULL;
	int quiet = 0;
	int ret, c;

	while ((c = getopt(argc, argv, "-q"U_GETOPT)) != -1) {
		switch (c) {
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
		default:
			if (!u_option(c))
				return 1;
			break;
		}
	}

	ret = u_device("lib", argv[0], "fatal", DETECT, true, 0ULL,
		       0x00000000, &client, device);
	if (ret)
		return ret;

	while (rstr && *rstr != '\0') {
		u32 cnt = 1, val;
		u64 reg;

		if ((reg = strtoull(rstr, &rstr, 0)) == ULONG_MAX)
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

	nvif_device_fini(device);
	nvif_client_fini(&client);
	return 0;
}
