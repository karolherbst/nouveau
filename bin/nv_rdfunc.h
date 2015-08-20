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
main(int argc, char **argv)
{
	struct nvif_device *device;
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

	while ((c = getopt(argc, argv, "-qrw"U_GETOPT)) != -1) {
		switch (c) {
		case 'q': mode = QUIET; break;
		case 'r': mode = RATES; break;
		case 'w': mode = WATCH; break;
		case 1:
			if (rstr)
				return 1;
			rstr = optarg;
			break;
		default:
			if (!u_option(c))
				return 1;
			break;
		}
	}

	ret = u_device("lib", argv[0], "fatal", DETECT, true, 0,
		       0x00000000, &device);
	if (ret)
		return ret;

	while (rstr && *rstr != '\0') {
		u32 cnt = 1;
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
