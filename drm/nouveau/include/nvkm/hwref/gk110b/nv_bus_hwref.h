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
#ifndef __nv_gk110b_bus_hwref_h__
#define __nv_gk110b_bus_hwref_h__

#define NV_PBUS_INTR_0                                      0x1100
#define NV_PBUS_INTR_0_PRI_SQUASH                              1:1
#define NV_PBUS_INTR_0_PRI_FECSERR                             2:2
#define NV_PBUS_INTR_0_PRI_TIMEOUT                             3:3
#define NV_PBUS_INTR_EN_0                                   0x1140
#define NV_PBUS_INTR_EN_0_PRI_SQUASH                           1:1
#define NV_PBUS_INTR_EN_0_PRI_FECSERR                          2:2
#define NV_PBUS_INTR_EN_0_PRI_TIMEOUT                          3:3
#define NV_PBUS_BAR1_BLOCK                                  0x1704
#define NV_PBUS_BAR1_BLOCK_PTR                                27:0
#define NV_PBUS_BAR1_BLOCK_TARGET                            29:28
#define NV_PBUS_BAR1_BLOCK_TARGET_VID_MEM                        0
#define NV_PBUS_BAR1_BLOCK_MODE                              31:31
#define NV_PBUS_BAR1_BLOCK_MODE_VIRTUAL                          1
#define NV_PBUS_BAR1_BLOCK_PTR_SHIFT                            12
#define NV_PBUS_BAR2_BLOCK                                  0x1714
#define NV_PBUS_BAR2_BLOCK_PTR                                27:0
#define NV_PBUS_BAR2_BLOCK_TARGET                            29:28
#define NV_PBUS_BAR2_BLOCK_TARGET_VID_MEM                        0
#define NV_PBUS_BAR2_BLOCK_MODE                              31:31
#define NV_PBUS_BAR2_BLOCK_MODE_VIRTUAL                          1
#define NV_PBUS_BAR2_BLOCK_PTR_SHIFT                            12

#endif /* __nv_gk110b_bus_hwref_h__ */
