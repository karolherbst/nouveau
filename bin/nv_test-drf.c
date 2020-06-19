/*
 * Copyright 2020 Red Hat Inc.
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
 */
#include <nvif/os.h>

#include <nvhw/drf.h>

#define RD32_(p,o,a) ({ u32 _d = data[((o)+(a))/4]; printf("rd32 %04x %08x\n", (o)+(a), _d); _d; })
#define WR32_(p,o,a,d) do { printf("wr32 %04x %08x\n", (o)+(a), (u32)(d)); data[((o)+(a))/4] = (d); } while(0)
#define RD32(A...) DRF_RD(RD32_,             NULL, 0, ##A)
#define RV32(A...) DRF_RV(RD32_,             NULL, 0, ##A)
#define TV32(A...) DRF_TV(RD32_,             NULL, 0, ##A)
#define TD32(A...) DRF_TD(RD32_,             NULL, 0, ##A)
#define WR32(A...) DRF_WR(       WR32_,      NULL, 0, ##A)
#define WV32(A...) DRF_WV(       WR32_,      NULL, 0, ##A)
#define WD32(A...) DRF_WD(       WR32_,      NULL, 0, ##A)
#define MR32(A...) DRF_MR(RD32_, WR32_, u32, NULL, 0, ##A)
#define MV32(A...) DRF_MV(RD32_, WR32_, u32, NULL, 0, ##A)
#define MD32(A...) DRF_MD(RD32_, WR32_, u32, NULL, 0, ##A)

#define D                 0
#define D_R0         0x0000
#define D_R0_F0       15:12
#define D_R0_F0_V0     0x05
#define D_R0_F1       31:24
#define D_R0_F1_V0     0x77
#define D_R1         0x0004
#define D_R2(i) (i*4+0x0008)
#define D_R2_F0       15:12
#define D_R2_F0_V0     0x05
#define D_R2_F1       31:24
#define D_R2_F1_V0     0x77

int
main(int argc, char **argv)
{
	u32 data[0x100] = {};

	// read
	assert(RD32(D, R0) == 0x00000000);

	// read at offset
	assert(RD32(D, R1) == 0x00000000);

	// write
	WR32(D, R0, 0xffffffff);
	assert(RD32(D, R0) == 0xffffffff);
	assert(data[D_R0/4] == 0xffffffff);

	// write at offset
	WR32(D, R1, 0xeeeeeeee);
	assert(RD32(D, R1) == 0xeeeeeeee);
	assert(data[D_R1/4] == 0xeeeeeeee);

	// modify, and return previous value
	assert(RD32(D, R0) == 0xffffffff);
	assert(MR32(D, R0, 0x55555555, 0x00000000) == 0xffffffff);
	assert(RD32(D, R0) == 0xaaaaaaaa);

	// read field value
	assert(RV32(D, R0, F0) == 0x0a);

	// write field value
	WV32(D, R0, F0, 0x0b);
	assert(RV32(D, R0, F0) == 0x0b);
	assert(data[D_R0/4] == 0x0b << DRF_LO(D_R0_F0));

	// write field definition
	WD32(D, R0, F0, V0);
	assert(RV32(D, R0, F0) == D_R0_F0_V0);
	assert(data[D_R0/4] == D_R0_F0_V0 << DRF_LO(D_R0_F0));

	// modify field value, and return previous value
	assert(MV32(D, R0, F1, 0x55) == 0x00);
	assert(RV32(D, R0, F1) == 0x55);
	assert(data[D_R0/4] == (      0x55 << DRF_LO(D_R0_F1) |
				D_R0_F0_V0 << DRF_LO(D_R0_F0)));

	// modify field definition, and return previous value
	assert(MD32(D, R0, F1, V0) == 0x55);
	assert(RV32(D, R0, F1) == D_R0_F1_V0);
	assert(data[D_R0/4] == (D_R0_F1_V0 << DRF_LO(D_R0_F1) |
				D_R0_F0_V0 << DRF_LO(D_R0_F0)));

	// test field against value
	for (int v = 0; v <= DRF_MASK(D_R0_F1); v++) {
		assert(TV32(D, R0, F1, !=, v) == (RV32(D, R0, F1) != v));
		assert(TV32(D, R0, F1, < , v) == (RV32(D, R0, F1) <  v));
		assert(TV32(D, R0, F1, <=, v) == (RV32(D, R0, F1) <= v));
		assert(TV32(D, R0, F1, ==, v) == (RV32(D, R0, F1) == v));
		assert(TV32(D, R0, F1, >=, v) == (RV32(D, R0, F1) >= v));
		assert(TV32(D, R0, F1, > , v) == (RV32(D, R0, F1) >  v));
		assert(TV32(D, R0, F1, & , v) == (RV32(D, R0, F1) &  v));
	}

	// test field agsinst definition
	assert(!TD32(D, R0, F1, !=, V0));
	assert(!TD32(D, R0, F1, < , V0));
	assert( TD32(D, R0, F1, <=, V0));
	assert( TD32(D, R0, F1, ==, V0));
	assert( TD32(D, R0, F1, >=, V0));
	assert(!TD32(D, R0, F1, > , V0));
	assert( TD32(D, R0, F1, & , V0) == D_R0_F1_V0);

	for (int i = 0; i < 2; i++) {
		// indexed read
		assert(RD32(D, R2, i) == 0x00000000);

		// indexed write
		WR32(D, R2, i, 0xffffffff);
		assert(RD32(D, R2, i) == 0xffffffff);
		assert(data[D_R2(i)/4] == 0xffffffff);

		// indexed modify, and return previous value
		assert(MR32(D, R2, i, 0x55555555, 0x00000000) == 0xffffffff);
		assert(RD32(D, R2, i) == 0xaaaaaaaa);

		// indexed read field value
		assert(RV32(D, R2, i, F0) == 0x0a);

		// indexed, write field value
		WV32(D, R2, i, F0, 0x0b);
		assert(RV32(D, R2, i, F0) == 0x0b);
		assert(data[D_R2(i)/4] == 0x0b << DRF_LO(D_R2_F0));

		// indexed write field definition
		WD32(D, R2, i, F0, V0);
		assert(RV32(D, R2, i, F0) == D_R2_F0_V0);
		assert(data[D_R2(i)/4] == D_R2_F0_V0 << DRF_LO(D_R2_F0));

		// indexed modify field value, and return previous value
		assert(MV32(D, R2, i, F1, 0x55) == 0x00);
		assert(RV32(D, R2, i, F1) == 0x55);
		assert(data[D_R2(i)/4] == (      0x55 << DRF_LO(D_R2_F1) |
					   D_R2_F0_V0 << DRF_LO(D_R2_F0)));

		// indexed modify field definition, and return previous value
		assert(MD32(D, R2, i, F1, V0) == 0x55);
		assert(RV32(D, R2, i, F1) == D_R2_F1_V0);
		assert(data[D_R2(i)/4] == (D_R2_F1_V0 << DRF_LO(D_R2_F1) |
					   D_R2_F0_V0 << DRF_LO(D_R2_F0)));

		// indexed test field against value
		for (int v = 0; v <= DRF_MASK(D_R2_F1); v++) {
			assert(TV32(D, R2, i, F1, !=, v) == (RV32(D, R2, i, F1) != v));
			assert(TV32(D, R2, i, F1, < , v) == (RV32(D, R2, i, F1) <  v));
			assert(TV32(D, R2, i, F1, <=, v) == (RV32(D, R2, i, F1) <= v));
			assert(TV32(D, R2, i, F1, ==, v) == (RV32(D, R2, i, F1) == v));
			assert(TV32(D, R2, i, F1, >=, v) == (RV32(D, R2, i, F1) >= v));
			assert(TV32(D, R2, i, F1, > , v) == (RV32(D, R2, i, F1) >  v));
			assert(TV32(D, R2, i, F1, & , v) == (RV32(D, R2, i, F1) &  v));
		}

		// indexed test field agsinst definition
		assert(!TD32(D, R2, i, F1, !=, V0));
		assert(!TD32(D, R2, i, F1, < , V0));
		assert( TD32(D, R2, i, F1, <=, V0));
		assert( TD32(D, R2, i, F1, ==, V0));
		assert( TD32(D, R2, i, F1, >=, V0));
		assert(!TD32(D, R2, i, F1, > , V0));
		assert( TD32(D, R2, i, F1, & , V0) == D_R2_F1_V0);
	}


	return 0;
}
