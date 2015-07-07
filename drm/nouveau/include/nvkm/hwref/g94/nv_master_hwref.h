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
#ifndef __nv_g94_master_hwref_h__
#define __nv_g94_master_hwref_h__

#define NV_PMC_BOOT_0                                            0
#define NV_PMC_BOOT_0_MINOR_REVISION                           3:0
#define NV_PMC_BOOT_0_MAJOR_REVISION                           7:4
#define NV_PMC_BOOT_0_IMPLEMENTATION                         23:20
#define NV_PMC_BOOT_0_ARCHITECTURE                           28:24
#define NV_PMC_INTR_0                                        0x100
#define NV_PMC_INTR_0_PFIFO                                    8:8
#define NV_PMC_INTR_0_PGRAPH                                 12:12
#define NV_PMC_INTR_0_PBUS                                   28:28
#define NV_PMC_INTR_EN_0                                     0x140
#define NV_PMC_INTR_EN_0_INTA                                  1:0
#define NV_PMC_INTR_EN_0_INTA_HARDWARE                           1
#define NV_PMC_ENABLE                                        0x200
#define NV_PMC_ENABLE_PMEDIA                                   4:4
#define NV_PMC_ENABLE_PFIFO                                    8:8
#define NV_PMC_ENABLE_PGRAPH                                 12:12
#define NV_PMC_ENABLE_PFB                                    20:20

#endif /* __nv_g94_master_hwref_h__ */
