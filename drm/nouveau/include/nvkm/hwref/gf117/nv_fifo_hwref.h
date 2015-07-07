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
#ifndef __nv_gf117_fifo_hwref_h__
#define __nv_gf117_fifo_hwref_h__

#define NV_PFIFO_BAR1_BASE                                  0x2254
#define NV_PFIFO_BAR1_BASE_PTR                                27:0
#define NV_PFIFO_BAR1_BASE_VALID                             28:28
#define NV_PFIFO_BAR1_BASE_PTR_ALIGN_SHIFT                      12
#define NV_PFIFO_RUNLIST_BASE                               0x2270
#define NV_PFIFO_RUNLIST_BASE_PTR                             27:0
#define NV_PFIFO_RUNLIST_BASE_TARGET                         29:28
#define NV_PFIFO_RUNLIST_BASE_TARGET_VID_MEM                     0
#define NV_PFIFO_RUNLIST                                    0x2274
#define NV_PFIFO_ENG_RUNLIST_BASE(i)                (0x2280+(i)*8)
#define NV_PFIFO_ENG_RUNLIST_BASE__SIZE_1                        6
#define NV_PFIFO_ENG_RUNLIST(i)                     (0x2284+(i)*8)
#define NV_PFIFO_ENG_RUNLIST__SIZE_1                             6
#define NV_PFIFO_ENG_RUNLIST_LENGTH                           11:0
#define NV_PFIFO_ENG_RUNLIST_PENDING                         20:20
#define NV_PFIFO_PB_TIMESLICE(i)                    (0x2350+(i)*4)
#define NV_PFIFO_PB_TIMESLICE_TIMEOUT                          7:0
#define NV_PFIFO_PB_TIMESLICE_TIMEOUT_16                        16
#define NV_PFIFO_PB_TIMESLICE_TIMESCALE                      15:12
#define NV_PFIFO_PB_TIMESLICE_TIMESCALE_0                        0
#define NV_PFIFO_PB_TIMESLICE_ENABLE                         28:28
#define NV_PFIFO_PBDMA_MAP(i)                       (0x2390+(i)*4)
#define NV_PFIFO_INTR_0                                     0x2100
#define NV_PFIFO_INTR_0_BIND_ERROR                             0:0
#define NV_PFIFO_INTR_0_BIND_ERROR_RESET                         1
#define NV_PFIFO_INTR_0_PIO_ERROR                              4:4
#define NV_PFIFO_INTR_0_PIO_ERROR_RESET                          1
#define NV_PFIFO_INTR_0_SCHED_ERROR                            8:8
#define NV_PFIFO_INTR_0_SCHED_ERROR_RESET                        1
#define NV_PFIFO_INTR_0_CHSW_ERROR                           16:16
#define NV_PFIFO_INTR_0_CHSW_ERROR_RESET                         1
#define NV_PFIFO_INTR_0_FB_FLUSH_TIMEOUT                     23:23
#define NV_PFIFO_INTR_0_FB_FLUSH_TIMEOUT_RESET                   1
#define NV_PFIFO_INTR_0_LB_ERROR                             24:24
#define NV_PFIFO_INTR_0_LB_ERROR_RESET                           1
#define NV_PFIFO_INTR_0_DROPPED_MMU_FAULT                    27:27
#define NV_PFIFO_INTR_0_DROPPED_MMU_FAULT_RESET                  1
#define NV_PFIFO_INTR_0_MMU_FAULT                            28:28
#define NV_PFIFO_INTR_0_PBDMA_INTR                           29:29
#define NV_PFIFO_INTR_0_RUNLIST_EVENT                        30:30
#define NV_PFIFO_INTR_0_CHANNEL_INTR                         31:31
#define NV_PFIFO_INTR_EN_0                                  0x2140
#define NV_PFIFO_INTR_EN_0_SCHED_ERROR                         8:8
#define NV_PFIFO_INTR_EN_0_MMU_FAULT                         28:28
#define NV_PFIFO_INTR_EN_1                                  0x2528
#define NV_PFIFO_INTR_BIND_ERROR                            0x252c
#define NV_PFIFO_INTR_SCHED_ERROR                           0x254c
#define NV_PFIFO_INTR_SCHED_ERROR_CODE                         7:0
#define NV_PFIFO_INTR_SCHED_ERROR_CODE_CTXSW_TIMEOUT            10
#define NV_PFIFO_INTR_CHSW_ERROR                            0x256c
#define NV_PFIFO_INTR_MMU_FAULT_ID                          0x259c
#define NV_PFIFO_INTR_MMU_FAULT_ENG_ID_GRAPHICS                  0
#define NV_PFIFO_INTR_MMU_FAULT_INST(i)            (0x2800+(i)*16)
#define NV_PFIFO_INTR_MMU_FAULT_INST_PTR                      27:0
#define NV_PFIFO_INTR_MMU_FAULT_INST_PTR_ALIGN_SHIFT            12
#define NV_PFIFO_INTR_MMU_FAULT_LO(i)              (0x2804+(i)*16)
#define NV_PFIFO_INTR_MMU_FAULT_HI(i)              (0x2808+(i)*16)
#define NV_PFIFO_INTR_MMU_FAULT_INFO(i)            (0x280c+(i)*16)
#define NV_PFIFO_INTR_MMU_FAULT_INFO_TYPE                      3:0
#define NV_PFIFO_INTR_MMU_FAULT_INFO_ENGINE_SUBID              6:6
#define NV_PFIFO_INTR_MMU_FAULT_INFO_ENGINE_SUBID_GPC            0
#define NV_PFIFO_INTR_MMU_FAULT_INFO_ENGINE_SUBID_HUB            1
#define NV_PFIFO_INTR_MMU_FAULT_INFO_CLIENT                   12:8
#define NV_PFIFO_INTR_PBDMA_ID                              0x25a0
#define NV_PFIFO_INTR_RUNLIST                               0x2a00
#define NV_PFIFO_FB_TIMEOUT                                 0x2a04
#define NV_PFIFO_FB_TIMEOUT_PERIOD                            29:0
#define NV_PFIFO_FB_TIMEOUT_PERIOD_MAX                  0x3fffffff
#define NV_PFIFO_PB_TIMEOUT                                 0x2a08
#define NV_PFIFO_PB_TIMEOUT_DETECTION                        31:31
#define NV_PFIFO_ENG_TIMEOUT                                0x2a0c
#define NV_PFIFO_ENG_TIMEOUT_PERIOD                           30:0
#define NV_PFIFO_ENG_TIMEOUT_PERIOD_MAX                 0x7fffffff
#define NV_PFIFO_ENG_TIMEOUT_DETECTION                       31:31
#define NV_PFIFO_ERROR_SCHED_DISABLE                        0x262c
#define NV_PFIFO_SCHED_DISABLE                              0x2630
#define NV_PFIFO_PREEMPT                                    0x2634
#define NV_PFIFO_PREEMPT_PENDING                             20:20
#define NV_PFIFO_TRIGGER_MMU_FAULT(i)               (0x2a30+(i)*4)
#define NV_PFIFO_TRIGGER_MMU_FAULT_ID                          4:0
#define NV_PFIFO_TRIGGER_MMU_FAULT_ENABLE                      8:8
#define NV_PFIFO_ENGINE_STATUS(i)                   (0x2640+(i)*4)
#define NV_PFIFO_ENGINE_STATUS__SIZE_1                           6
#define NV_PFIFO_ENGINE_STATUS_CTXSW                         18:17
#define NV_PFIFO_ENGINE_STATUS_FAULTED                       24:24
#define NV_PFIFO_ENGINE_STATUS_ENGINE                        28:28
#define NV_PFIFO_ENGINE_STATUS_ENGINE_IDLE                       0
#define NV_PFIFO_ENGINE_STATUS_ENGINE_BUSY                       1

#endif /* __nv_gf117_fifo_hwref_h__ */
