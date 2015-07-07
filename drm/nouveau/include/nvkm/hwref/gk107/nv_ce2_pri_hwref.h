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
#ifndef __nv_gk107_ce2_pri_hwref_h__
#define __nv_gk107_ce2_pri_hwref_h__

#define NV_PCE2_COP2_INTR_STATUS                          0x106908
#define NV_PCE2_COP2_INTR_STATUS_BLOCKPIPE                     0:0
#define NV_PCE2_COP2_INTR_STATUS_BLOCKPIPE_RESET                 1
#define NV_PCE2_COP2_INTR_STATUS_NONBLOCKPIPE                  1:1
#define NV_PCE2_COP2_INTR_STATUS_NONBLOCKPIPE_RESET              1
#define NV_PCE2_COP2_INTR_STATUS_LAUNCHERR                     2:2
#define NV_PCE2_COP2_INTR_STATUS_LAUNCHERR_RESET                 1

#endif /* __nv_gk107_ce2_pri_hwref_h__ */
