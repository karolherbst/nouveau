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
#ifndef __nv_gf116_top_hwref_h__
#define __nv_gf116_top_hwref_h__

#define NV_PTOP_SCAL_NUM_GPCS                              0x22430
#define NV_PTOP_SCAL_NUM_GPCS_VALUE                            4:0
#define NV_PTOP_SCAL_NUM_TPC_PER_GPC                       0x22434
#define NV_PTOP_SCAL_NUM_TPC_PER_GPC_VALUE                     4:0
#define NV_PTOP_SCAL_NUM_FBPS                              0x22438
#define NV_PTOP_SCAL_NUM_FBPS_VALUE                            4:0
#define NV_PTOP_FS_STATUS                                  0x22500
#define NV_PTOP_FS_STATUS_FBP                              0x22548
#define NV_PTOP_FS_STATUS_FBP_CLUSTER                         15:0
#define NV_PTOP_FS_STATUS_FBP_CLUSTER_ENABLE                     0
#define NV_PTOP_FS_STATUS_FBP_CLUSTER_DISABLE                    1

#endif /* __nv_gf116_top_hwref_h__ */
