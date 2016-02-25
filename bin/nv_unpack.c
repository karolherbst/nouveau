/*
 * Copyright 2016 Red Hat Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Ben Skeggs
 */
#include <sys/mman.h>

#include <nvif/os.h>

struct fw_av {
	u32 addr;
	u32 data;
};

struct fw_aiv {
	u32 addr;
	u32 index;
	u32 data;
};

int
main(int argc, char **argv)
{
	const char *path = NULL;
	int type = 0, fd, i;
	void *data;
	long size;

	while ((i = getopt(argc, argv, "-t:")) != -1) {
		switch (i) {
		case 't':
			if (!strcmp(optarg, "av"))
				type = 0;
			else
			if (!strcmp(optarg, "aiv"))
				type = 1;
			else
				return -1;
			break;
		case 1:
			if (path)
				return -1;
			path = optarg;
			break;
		default:
			return -1;
		}
	}

	if (!path)
		return -1;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return -1;

	size = lseek(fd, 0, SEEK_END);
	data = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (data == MAP_FAILED)
		return -1;

	if (type == 0) {
		struct fw_av *av = data;
		for (i = 0; i < size / sizeof(*av); i++)
			printf("%08x %08x\n", av[i].addr, av[i].data);
	} else
	if (type == 1) {
		struct fw_aiv *av = data;
		for (i = 0; i < size / sizeof(*av); i++) {
			printf("%08x %08x %08x\n", av[i].addr,
			       av[i].index, av[i].data);
		}
	}

	return 0;
}
