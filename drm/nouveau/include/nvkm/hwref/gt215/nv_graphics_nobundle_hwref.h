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
#ifndef __nv_gt215_graphics_nobundle_hwref_h__
#define __nv_gt215_graphics_nobundle_hwref_h__

#define NV_PGRAPH_INTR                                    0x400100
#define NV_PGRAPH_INTR_NOTIFY                                  0:0
#define NV_PGRAPH_INTR_NOTIFY_RESET                              1
#define NV_PGRAPH_INTR_SEMAPHORE                               1:1
#define NV_PGRAPH_INTR_SEMAPHORE_RESET                           1
#define NV_PGRAPH_INTR_SEMAPHORE_TIMEOUT                       2:2
#define NV_PGRAPH_INTR_SEMAPHORE_TIMEOUT_RESET                   1
#define NV_PGRAPH_INTR_ILLEGAL_METHOD                          4:4
#define NV_PGRAPH_INTR_ILLEGAL_METHOD_RESET                      1
#define NV_PGRAPH_INTR_ILLEGAL_CLASS                           5:5
#define NV_PGRAPH_INTR_ILLEGAL_CLASS_RESET                       1
#define NV_PGRAPH_INTR_ILLEGAL_NOTIFY                          6:6
#define NV_PGRAPH_INTR_ILLEGAL_NOTIFY_RESET                      1
#define NV_PGRAPH_INTR_CLASS_ERROR                           20:20
#define NV_PGRAPH_INTR_CLASS_ERROR_RESET                         1
#define NV_PGRAPH_INTR_EXCEPTION                             21:21
#define NV_PGRAPH_INTR_EXCEPTION_RESET                           1
#define NV_PGRAPH_EXCEPTION                               0x400108
#define NV_PGRAPH_EXCEPTION_FE                                 0:0
#define NV_PGRAPH_EXCEPTION_MEMFMT                             1:1
#define NV_PGRAPH_EXCEPTION_EN                            0x400138
#define NV_PGRAPH_EXCEPTION_EN_FE                              0:0
#define NV_PGRAPH_CLASS_ERROR                             0x400110
#define NV_PGRAPH_CLASS_ERROR_CODE                            15:0
#define NV_PGRAPH_INTR_EN                                 0x40013c
#define NV_PGRAPH_GRFIFO_CONTROL                          0x400500
#define NV_PGRAPH_GRFIFO_CONTROL_ACCESS                        0:0
#define NV_PGRAPH_GRFIFO_CONTROL_SEMAPHORE_ACCESS            16:16
#define NV_PGRAPH_GRFIFO_STATUS                           0x400504
#define NV_PGRAPH_TRAPPED_ADDR                            0x400704
#define NV_PGRAPH_TRAPPED_ADDR_MTHD                           12:2
#define NV_PGRAPH_TRAPPED_ADDR_SUBCH                         18:16
#define NV_PGRAPH_TRAPPED_DATA_LOW                        0x400708
#define NV_PGRAPH_TRAPPED_DATA_HIGH                       0x40070c
#define NV_PGRAPH_STATUS                                  0x400700
#define NV_PGRAPH_ACTIVITY1                               0x400384
#define NV_PGRAPH_ACTIVITY2                               0x400388
#define NV_PGRAPH_ACTIVITY0                               0x400380
#define NV_PGRAPH_PIPE_BUNDLE_ADDRESS                     0x400200
#define NV_PGRAPH_PIPE_BUNDLE_ADDRESS_VALUE                   15:0
#define NV_PGRAPH_PIPE_BUNDLE_DATA                        0x400204
#define NV_PGRAPH_PRI_FE_HWW_ESR                          0x400804
#define NV_PGRAPH_PRI_FE_HWW_ESR_RESET                       30:30
#define NV_PGRAPH_PRI_FE_HWW_ESR_RESET_ACTIVE                    1
#define NV_PGRAPH_PRI_FE_HWW_ESR_EN                          31:31
#define NV_PGRAPH_PRI_FE_HWW_ESR_EN_ENABLE                       1
#define NV_PGRAPH_PRI_MEMFMT_HWW_ESR                      0x406800
#define NV_PGRAPH_PRI_MEMFMT_HWW_ESR_RESET                   30:30
#define NV_PGRAPH_PRI_MEMFMT_HWW_ESR_RESET_ACTIVE                1
#define NV_PGRAPH_PRI_MEMFMT_HWW_ESR_EN                      31:31
#define NV_PGRAPH_PRI_MEMFMT_HWW_ESR_EN_ENABLE                   1
#define NV_PGRAPH_PRI_SCC_HWW_ESR                         0x405018
#define NV_PGRAPH_PRI_SCC_HWW_ESR_RESET                      30:30
#define NV_PGRAPH_PRI_SCC_HWW_ESR_RESET_ACTIVE                   1
#define NV_PGRAPH_PRI_SCC_HWW_ESR_EN                         31:31
#define NV_PGRAPH_PRI_SCC_HWW_ESR_EN_ENABLE                      1
#define NV_PGRAPH_PRI_SCC_INIT                            0x405020
#define NV_PGRAPH_PRI_SCC_INIT_RAM                             0:0

#endif /* __nv_gt215_graphics_nobundle_hwref_h__ */
