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
#ifndef __nv_g92_mmu_hwref_h__
#define __nv_g92_mmu_hwref_h__

#define NV_MMU_PDE_ADDRESS_SHIFT                                12
#define NV_MMU_PDE__SIZE                                         8
#define NV_MMU_PTE_VALID                         (0*32+0):(0*32+0)
#define NV_MMU_PTE_READ_ONLY                     (0*32+3):(0*32+3)
#define NV_MMU_PTE_APERTURE                      (0*32+5):(0*32+4)
#define NV_MMU_PTE_APERTURE_VIDEO_MEMORY                         0
#define NV_MMU_PTE_COMPTAGLINE                 (1*32+28):(1*32+17)
#define NV_MMU_PTE__SIZE                                         8
#define NV_MMU_PTE_KIND                         (1*32+14):(1*32+8)
#define NV_MMU_PTE_KIND_INVALID                               0x7f
#define NV_MMU_PTE_KIND_PITCH                                    0
#define NV_MMU_PTE_KIND_Z24S8                                   16
#define NV_MMU_PTE_KIND_Z24V8_MS4_VC4                           20
#define NV_MMU_PTE_KIND_Z24V8_MS4_VC12                          21
#define NV_MMU_PTE_KIND_Z24V8_MS8_VC8                           22
#define NV_MMU_PTE_KIND_S8Z24                                   32
#define NV_MMU_PTE_KIND_V8Z24_MS4_VC4                         0x24
#define NV_MMU_PTE_KIND_V8Z24_MS4_VC12                        0x25
#define NV_MMU_PTE_KIND_V8Z24_MS8_VC8                         0x26
#define NV_MMU_PTE_KIND_ZF32                                  0x40
#define NV_MMU_PTE_KIND_X8Z24_X16V8S8_MS4_VC4                 0x54
#define NV_MMU_PTE_KIND_X8Z24_X16V8S8_MS4_VC12                0x55
#define NV_MMU_PTE_KIND_X8Z24_X16V8S8_MS8_VC8                 0x56
#define NV_MMU_PTE_KIND_ZF32_X24S8                            0x60
#define NV_MMU_PTE_KIND_ZF32_X16V8S8_MS4_VC4                  0x64
#define NV_MMU_PTE_KIND_ZF32_X16V8S8_MS4_VC12                 0x65
#define NV_MMU_PTE_KIND_ZF32_X16V8S8_MS8_VC8                  0x66

#endif /* __nv_g92_mmu_hwref_h__ */
