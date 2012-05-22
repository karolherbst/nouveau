#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

#include <core/os.h>
#include <core/object.h>
#include <core/class.h>

#ifndef ENABLE
#define ENABLE NV_DEVICE_DISABLE_MMIO
#endif
#ifndef DEBUG0
#define DEBUG0 0ULL
#endif

int
MAIN(int argc, char **argv)
{
	struct nouveau_object *client;
	struct nouveau_object *device;
	struct nv_device_class args;
	char *rstr = NULL;
	char *vstr = NULL;
	int quiet = 0;
	int ret, c;

	while ((c = getopt(argc, argv, "-q")) != -1) {
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
		}
	}

	ret = os_client_new(NULL, "fatal", argc, argv, &client);
	if (ret)
		return ret;

	args.device  = ~0ULL;
	args.disable = ~ENABLE;
	args.debug0  = ~DEBUG0;

	ret = nouveau_object_new(client, ~0, 0, 0x0080, &args, sizeof(args),
				 &device);
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

	return 0;
}
