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
#ifndef __nv_gm206_fuse_hwref_h__
#define __nv_gm206_fuse_hwref_h__

#define NV_FUSE_CTRL_OPT_TPC_GPC(i)                (0x21838+(i)*4)
#define NV_FUSE_CTRL_OPT_RAM_SVOP_PDP                      0x21944
#define NV_FUSE_CTRL_OPT_RAM_SVOP_PDP_DATA                     1:0
#define NV_FUSE_CTRL_OPT_RAM_SVOP_PDP_OVERRIDE             0x21948
#define NV_FUSE_CTRL_OPT_RAM_SVOP_PDP_OVERRIDE_DATA            0:0
#define NV_FUSE_STATUS_OPT_TPC_GPC(i)              (0x21c38+(i)*4)
#define NV_FUSE_STATUS_OPT_ROP_L2_FBP(i)           (0x21d70+(i)*4)
#define NV_FUSE_STATUS_OPT_FBP                             0x21d38
#define NV_FUSE_STATUS_OPT_FBP_IDX(i)                      (i):(i)
#define NV_FUSE_STATUS_OPT_FBIO                            0x21c14
#define NV_FUSE_STATUS_OPT_FBIO_DATA                          15:0

#endif /* __nv_gm206_fuse_hwref_h__ */
