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
#ifndef __nv_gf108_pwr_pri_hwref_h__
#define __nv_gf108_pwr_pri_hwref_h__

#define NV_PPWR_FALCON_IRQSSET                            0x10a000
#define NV_PPWR_FALCON_IRQSSET_SWGEN0                          6:6
#define NV_PPWR_FALCON_IRQSCLR                            0x10a004
#define NV_PPWR_FALCON_IRQSTAT                            0x10a008
#define NV_PPWR_FALCON_IRQSTAT_HALT                            4:4
#define NV_PPWR_FALCON_IRQSTAT_SWGEN0                          6:6
#define NV_PPWR_FALCON_IRQMODE                            0x10a00c
#define NV_PPWR_FALCON_IRQMSET                            0x10a010
#define NV_PPWR_FALCON_IRQMSET_GPTMR                           0:0
#define NV_PPWR_FALCON_IRQMSET_MTHD                            2:2
#define NV_PPWR_FALCON_IRQMSET_CTXSW                           3:3
#define NV_PPWR_FALCON_IRQMSET_HALT                            4:4
#define NV_PPWR_FALCON_IRQMSET_SWGEN0                          6:6
#define NV_PPWR_FALCON_IRQMSET_SWGEN1                          7:7
#define NV_PPWR_FALCON_IRQMCLR                            0x10a014
#define NV_PPWR_FALCON_IRQMCLR_GPTMR                           0:0
#define NV_PPWR_FALCON_IRQMCLR_MTHD                            2:2
#define NV_PPWR_FALCON_IRQMCLR_CTXSW                           3:3
#define NV_PPWR_FALCON_IRQMCLR_HALT                            4:4
#define NV_PPWR_FALCON_IRQMCLR_SWGEN0                          6:6
#define NV_PPWR_FALCON_IRQMCLR_SWGEN1                          7:7
#define NV_PPWR_FALCON_IRQMCLR_EXT                            15:8
#define NV_PPWR_FALCON_IRQMASK                            0x10a018
#define NV_PPWR_FALCON_IRQDEST                            0x10a01c
#define NV_PPWR_FALCON_CURCTX                             0x10a050
#define NV_PPWR_FALCON_NXTCTX                             0x10a054
#define NV_PPWR_FALCON_MAILBOX0                           0x10a040
#define NV_PPWR_FALCON_MAILBOX1                           0x10a044
#define NV_PPWR_FALCON_ITFEN                              0x10a048
#define NV_PPWR_FALCON_ITFEN_CTXEN                             0:0
#define NV_PPWR_FALCON_IDLESTATE                          0x10a04c
#define NV_PPWR_FALCON_IDLESTATE_FALCON_BUSY                   0:0
#define NV_PPWR_FALCON_IDLESTATE_EXT_BUSY                     15:1
#define NV_PPWR_FALCON_OS                                 0x10a080
#define NV_PPWR_FALCON_ENGCTL                             0x10a0a4
#define NV_PPWR_FALCON_CPUCTL                             0x10a100
#define NV_PPWR_FALCON_CPUCTL_STARTCPU                         1:1
#define NV_PPWR_FALCON_CPUCTL_HALTED                           4:4
#define NV_PPWR_FALCON_BOOTVEC                            0x10a104
#define NV_PPWR_FALCON_BOOTVEC_VEC                            15:0
#define NV_PPWR_FALCON_HWCFG                              0x10a108
#define NV_PPWR_FALCON_HWCFG_IMEM_SIZE                         8:0
#define NV_PPWR_FALCON_HWCFG_DMEM_SIZE                        17:9
#define NV_PPWR_FALCON_DMACTL                             0x10a10c
#define NV_PPWR_FALCON_DMATRFBASE                         0x10a110
#define NV_PPWR_FALCON_DMATRFMOFFS                        0x10a114
#define NV_PPWR_FALCON_DMATRFCMD                          0x10a118
#define NV_PPWR_FALCON_DMATRFCMD_IMEM                          4:4
#define NV_PPWR_FALCON_DMATRFCMD_WRITE                         5:5
#define NV_PPWR_FALCON_DMATRFCMD_SIZE                         10:8
#define NV_PPWR_FALCON_DMATRFCMD_CTXDMA                      14:12
#define NV_PPWR_FALCON_DMATRFFBOFFS                       0x10a11c
#define NV_PPWR_FALCON_IMEMC(i)                  (0x10a180+(i)*16)
#define NV_PPWR_FALCON_IMEMC_OFFS                              7:2
#define NV_PPWR_FALCON_IMEMC_BLK                              15:8
#define NV_PPWR_FALCON_IMEMC_AINCW                           24:24
#define NV_PPWR_FALCON_IMEMD(i)                  (0x10a184+(i)*16)
#define NV_PPWR_FALCON_IMEMT(i)                  (0x10a188+(i)*16)
#define NV_PPWR_FALCON_DMEMC(i)                   (0x10a1c0+(i)*8)
#define NV_PPWR_FALCON_DMEMC_OFFS                              7:2
#define NV_PPWR_FALCON_DMEMC_BLK                              15:8
#define NV_PPWR_FALCON_DMEMC_AINCW                           24:24
#define NV_PPWR_FALCON_DMEMC_AINCR                           25:25
#define NV_PPWR_FALCON_DMEMD(i)                   (0x10a1c4+(i)*8)
#define NV_PPWR_PMU_NEW_INSTBLK                           0x10a47c
#define NV_PPWR_PMU_NEW_INSTBLK_PTR                           27:0
#define NV_PPWR_PMU_NEW_INSTBLK_TARGET                       29:28
#define NV_PPWR_PMU_NEW_INSTBLK_TARGET_FB                        0
#define NV_PPWR_PMU_NEW_INSTBLK_TARGET_SYS_COH                   2
#define NV_PPWR_PMU_NEW_INSTBLK_VALID                        30:30
#define NV_PPWR_PMU_MUTEX_ID                              0x10a488
#define NV_PPWR_PMU_MUTEX_ID_VALUE                             7:0
#define NV_PPWR_PMU_MUTEX_ID_VALUE_INIT                          0
#define NV_PPWR_PMU_MUTEX_ID_VALUE_NOT_AVAIL                  0xff
#define NV_PPWR_PMU_MUTEX_ID_RELEASE                      0x10a48c
#define NV_PPWR_PMU_MUTEX_ID_RELEASE_VALUE                     7:0
#define NV_PPWR_PMU_MUTEX_ID_RELEASE_VALUE_INIT                  0
#define NV_PPWR_PMU_MUTEX(i)                      (0x10a580+(i)*4)
#define NV_PPWR_PMU_MUTEX__SIZE_1                               16
#define NV_PPWR_PMU_MUTEX_VALUE                                7:0
#define NV_PPWR_PMU_MUTEX_VALUE_INITIAL_LOCK                     0
#define NV_PPWR_PMU_QUEUE_HEAD(i)                 (0x10a4a0+(i)*4)
#define NV_PPWR_PMU_QUEUE_HEAD__SIZE_1                           4
#define NV_PPWR_PMU_QUEUE_HEAD_ADDRESS                        31:0
#define NV_PPWR_PMU_QUEUE_TAIL(i)                 (0x10a4b0+(i)*4)
#define NV_PPWR_PMU_QUEUE_TAIL__SIZE_1                           4
#define NV_PPWR_PMU_QUEUE_TAIL_ADDRESS                        31:0
#define NV_PPWR_PMU_MSGQ_HEAD                             0x10a4c8
#define NV_PPWR_PMU_MSGQ_HEAD_VAL                             31:0
#define NV_PPWR_PMU_MSGQ_TAIL                             0x10a4cc
#define NV_PPWR_PMU_MSGQ_TAIL_VAL                             31:0
#define NV_PPWR_PMU_IDLE_MASK(i)                 (0x10a504+(i)*16)
#define NV_PPWR_PMU_IDLE_MASK_GR                               0:0
#define NV_PPWR_PMU_IDLE_COUNT(i)                (0x10a508+(i)*16)
#define NV_PPWR_PMU_IDLE_COUNT_VALUE                          30:0
#define NV_PPWR_PMU_IDLE_COUNT_RESET                         31:31
#define NV_PPWR_PMU_IDLE_CTRL(i)                 (0x10a50c+(i)*16)
#define NV_PPWR_PMU_IDLE_CTRL_VALUE                            1:0
#define NV_PPWR_PMU_IDLE_CTRL_VALUE_BUSY                         2
#define NV_PPWR_PMU_IDLE_CTRL_VALUE_ALWAYS                       3
#define NV_PPWR_PMU_DEBUG(i)                      (0x10a5c0+(i)*4)
#define NV_PPWR_PMU_DEBUG__SIZE_1                                4
#define NV_PPWR_PMU_MAILBOX(i)                    (0x10a5d0+(i)*4)
#define NV_PPWR_PMU_MAILBOX__SIZE_1                              4
#define NV_PPWR_PMU_BAR0_ADDR                             0x10a7a0
#define NV_PPWR_PMU_BAR0_DATA                             0x10a7a4
#define NV_PPWR_PMU_BAR0_TIMEOUT                          0x10a7a8
#define NV_PPWR_PMU_BAR0_CTL                              0x10a7ac
#define NV_PPWR_PMU_BAR0_ERROR_STATUS                     0x10a7b0
#define NV_PPWR_FBIF_TRANSCFG(i)                  (0x10a600+(i)*4)
#define NV_PPWR_FBIF_TRANSCFG_TARGET                           1:0
#define NV_PPWR_FBIF_TRANSCFG_TARGET_LOCAL_FB                    0
#define NV_PPWR_FBIF_TRANSCFG_TARGET_COHERENT_SYSMEM             1
#define NV_PPWR_FBIF_TRANSCFG_TARGET_NONCOHERENT_SYSMEM          2
#define NV_PPWR_FBIF_TRANSCFG_MEM_TYPE                         2:2
#define NV_PPWR_FBIF_TRANSCFG_MEM_TYPE_VIRTUAL                   0
#define NV_PPWR_FBIF_TRANSCFG_MEM_TYPE_PHYSICAL                  1

#endif /* __nv_gf108_pwr_pri_hwref_h__ */
