/*
 * Copyright (c) 2015, NVIDIA CORPORATION. All rights reserved.
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
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
#ifndef __nv_chipids_hwref_h__
#define __nv_chipids_hwref_h__

#define __nv_g80__                 0x80
#define __nv_g84__                 0x84
#define __nv_g86__                 0x86
#define __nv_g92__                 0x92
#define __nv_g94__                 0x94
#define __nv_g96__                 0x96
#define __nv_g98__                 0x98
#define __nv_mcp77__               0xaa
#define __nv_mcp79__               0xac
#define __nv_mcp89__               0xaf
#define __nv_g200__                0xa0
#define __nv_gt215__               0xa3
#define __nv_gt216__               0xa5
#define __nv_gt218__               0xa8
#define __nv_gf100__               0xc0
#define __nv_gf104__               0xc4
#define __nv_gf106__               0xc3
#define __nv_gf108__               0xc1
#define __nv_gf110__               0xc8
#define __nv_gf116__               0xcf
#define __nv_gf114__               0xce
#define __nv_gf117__               0xd7
#define __nv_gf119__               0xd9
#define __nv_gk104__               0xe4
#define __nv_gk106__               0xe6
#define __nv_gk107__               0xe7
#define __nv_gk110__               0xf0
#define __nv_gk110b__              0xf1
#define __nv_gk208b__             0x106
#define __nv_gk208__              0x108
#define __nv_gk20a__               0xea
#define __nv_gm107__              0x117
#define __nv_gm108__              0x118
#define __nv_gm204__              0x124
#define __nv_gm206__              0x126
#define __nv_gm20b__              0x12b
#define __nv_gpu_is_g8x(x) ((x)!=(x)\
		|| ((x)==__nv_g98__)\
		|| ((x)==__nv_g80__)\
		|| ((x)==__nv_g84__)\
		|| ((x)==__nv_g86__)\
		|| ((x)==__nv_g96__)\
		|| ((x)==__nv_g94__)\
		|| ((x)==__nv_g92__)\
	)

#define __nv_gpu_is_tesla(x) ((x)!=(x)\
		|| ((x)==__nv_mcp79__)\
		|| ((x)==__nv_mcp77__)\
		|| ((x)==__nv_mcp89__)\
		|| ((x)==__nv_g200__)\
		|| ((x)==__nv_gt215__)\
		|| ((x)==__nv_gt216__)\
		|| ((x)==__nv_gt218__)\
	)

#define __nv_gpu_is_fermi(x) ((x)!=(x)\
		|| ((x)==__nv_gf100__)\
		|| ((x)==__nv_gf110__)\
		|| ((x)==__nv_gf106__)\
		|| ((x)==__nv_gf104__)\
		|| ((x)==__nv_gf117__)\
		|| ((x)==__nv_gf108__)\
		|| ((x)==__nv_gf114__)\
		|| ((x)==__nv_gf119__)\
		|| ((x)==__nv_gf116__)\
	)

#define __nv_gpu_is_kepler(x) ((x)!=(x)\
		|| ((x)==__nv_gk104__)\
		|| ((x)==__nv_gk106__)\
		|| ((x)==__nv_gk107__)\
		|| ((x)==__nv_gk110b__)\
		|| ((x)==__nv_gk110__)\
		|| ((x)==__nv_gk208__)\
		|| ((x)==__nv_gk208b__)\
		|| ((x)==__nv_gk20a__)\
	)

#define __nv_gpu_is_maxwell(x) ((x)!=(x)\
		|| ((x)==__nv_gm20b__)\
		|| ((x)==__nv_gm204__)\
		|| ((x)==__nv_gm107__)\
		|| ((x)==__nv_gm206__)\
		|| ((x)==__nv_gm108__)\
	)

#endif /* __nv_chipids_hwref_h__ */
