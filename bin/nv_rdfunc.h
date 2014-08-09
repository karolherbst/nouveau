#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

#include <nvif/client.h>
#include <nvif/device.h>
#include <nvif/class.h>

#ifndef ENABLE
#define ENABLE NV_DEVICE_V0_DISABLE_MMIO
#endif
#ifndef DEBUG0
#define DEBUG0 0ULL
#endif

int
main(int argc, char **argv)
{
	const char *drv = NULL;
	const char *cfg = NULL;
	const char *dbg = "fatal";
	u64 dev = ~0ULL;
	struct nvif_client *client;
	struct nvif_device *device;
	struct nv_device_v0 args = {};
	char *rstr = NULL;
	enum {
		NORMAL,
		QUIET,
		RATES,
		WATCH,
	} mode = NORMAL;
	struct {
		u64 addr;
		u32 data;
	} *data = NULL;
	int mdata = 1;
	int ndata = 0;
	int ret, c;

	while ((c = getopt(argc, argv, "-a:b:c:d:qrw")) != -1) {
		switch (c) {
		case 'a': dev = strtoull(optarg, NULL, 0); break;
		case 'b': drv = optarg; break;
		case 'c': cfg = optarg; break;
		case 'd': dbg = optarg; break;
		case 'q': mode = QUIET; break;
		case 'r': mode = RATES; break;
		case 'w': mode = WATCH; break;
		case 1:
			if (rstr)
				return 1;
			rstr = optarg;
			break;
		}
	}

	ret = nvif_client_new(drv, argv[0], dev, cfg, dbg, &client);
	if (ret)
		return ret;

	args.device  = ~0ULL;
	args.disable = ~ENABLE;
	args.debug0  = ~DEBUG0;

	ret = nvif_device_new(nvif_object(client), 0x00000000, NV_DEVICE,
			      &args, sizeof(args), &device);
	nvif_client_ref(NULL, &client);
	if (ret)
		return ret;

	while (rstr && *rstr != '\0') {
		unsigned long cnt = 1;
		unsigned long reg;

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

		switch (*rstr) {
		case ',':
			rstr++;
		case '\0':
			if (ndata + cnt >= mdata) {
				while (ndata + cnt > mdata)
					mdata <<= 1;
				assert(data = realloc(data, sizeof(*data) * mdata));
			}

			for (; cnt; cnt--, reg += sizeof(CAST)) {
				data[ndata].addr = reg;
				data[ndata].data = READ(reg);
				ndata++;
			}
			break;
		default:
			return 1;
		}
	}

	switch (mode) {
	case NORMAL:
		for (c = 0; c < ndata; c++) {
			printf(NAME" "FMTADDR" "FMTDATA"\n",
			       data[c].addr, data[c].data);
		}
		break;
	case QUIET:
		for (c = 0; c < ndata; c++) {
			printf(FMTDATA"\n", data[c].data);
		}
		break;
	case RATES:
		while (1) {
			for (c = 0; c < ndata; c++) {
				CAST next = READ(data[c].addr);
				printf(NAME" "FMTADDR" "FMTDATA" "FMTDATA" %d/s\n",
				       data[c].addr, data[c].data, next,
				       next - data[c].data);
				data[c].data = next;
			}
			sleep(1);
		}
		break;
	case WATCH:
		while (1) {
			for (c = 0; c < ndata; c++) {
				CAST next = READ(data[c].addr);
				if (next != data[c].data) {
					printf(NAME" "FMTADDR" "FMTDATA"\n",
					       data[c].addr, next);
					data[c].data = next;
				}
			}
		}
		break;
	default:
		assert(0);
		return 1;
	}

	free(data);
	nvif_device_ref(NULL, &device);
	return 0;
}
