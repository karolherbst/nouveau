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
#ifndef __nv_g92_fifo_hwref_h__
#define __nv_g92_fifo_hwref_h__

#define NV_PFIFO_INTR_0                                     0x2100
#define NV_PFIFO_INTR_0_PIO_ERROR                              8:8
#define NV_PFIFO_INTR_0_PIO_ERROR_RESET                          1
#define NV_PFIFO_INTR_0_CHSW_ERROR                           19:19
#define NV_PFIFO_INTR_0_CHSW_ERROR_RESET                         1
#define NV_PFIFO_INTR_0_FB_FLUSH_TIMEOUT                     26:26
#define NV_PFIFO_INTR_0_FB_FLUSH_TIMEOUT_RESET                   1
#define NV_PFIFO_INTR_EN_0                                  0x2140
#define NV_PFIFO_RUNLIST                                    0x32ec
#define NV_PFIFO_PREEMPT                                    0x32fc

#endif /* __nv_g92_fifo_hwref_h__ */
