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
#ifndef __nv_gk107_pri_ringstation_sys_hwref_h__
#define __nv_gk107_pri_ringstation_sys_hwref_h__

#define NV_PPRIV_SYS_MASTER_SM_CONFIG(i)          (0x122300+(i)*4)
#define NV_PPRIV_SYS_PRIV_DECODE_CONFIG                   0x122204
#define NV_PPRIV_SYS_PRIV_DECODE_CONFIG_RING                   2:0
#define NV_PPRIV_SYS_PRIV_DECODE_CONFIG_RING_DROP_ON_RING_NOT_STARTED        1

#endif /* __nv_gk107_pri_ringstation_sys_hwref_h__ */
