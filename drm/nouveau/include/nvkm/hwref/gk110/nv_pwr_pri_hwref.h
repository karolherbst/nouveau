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
#ifndef __nv_gk110_pwr_pri_hwref_h__
#define __nv_gk110_pwr_pri_hwref_h__

#define NV_PPWR_FALCON_IRQSSET                            0x10a000
#define NV_PPWR_FALCON_IRQSSET_SWGEN0                          6:6
#define NV_PPWR_FALCON_IRQSSET_SWGEN0_SET                        1
#define NV_PPWR_FALCON_IRQSCLR                            0x10a004
#define NV_PPWR_FALCON_IRQSTAT                            0x10a008
#define NV_PPWR_FALCON_IRQSTAT_HALT                            4:4
#define NV_PPWR_FALCON_IRQSTAT_EXTERR                          5:5
#define NV_PPWR_FALCON_IRQSTAT_SWGEN0                          6:6
#define NV_PPWR_FALCON_IRQMODE                            0x10a00c
#define NV_PPWR_FALCON_IRQMSET                            0x10a010
#define NV_PPWR_FALCON_IRQMSET_GPTMR                           0:0
#define NV_PPWR_FALCON_IRQMSET_WDTMR                           1:1
#define NV_PPWR_FALCON_IRQMSET_MTHD                            2:2
#define NV_PPWR_FALCON_IRQMSET_CTXSW                           3:3
#define NV_PPWR_FALCON_IRQMSET_HALT                            4:4
#define NV_PPWR_FALCON_IRQMSET_EXTERR                          5:5
#define NV_PPWR_FALCON_IRQMSET_SWGEN0                          6:6
#define NV_PPWR_FALCON_IRQMSET_SWGEN1                          7:7
#define NV_PPWR_FALCON_IRQMCLR                            0x10a014
#define NV_PPWR_FALCON_IRQMCLR_GPTMR                           0:0
#define NV_PPWR_FALCON_IRQMCLR_WDTMR                           1:1
#define NV_PPWR_FALCON_IRQMCLR_MTHD                            2:2
#define NV_PPWR_FALCON_IRQMCLR_CTXSW                           3:3
#define NV_PPWR_FALCON_IRQMCLR_HALT                            4:4
#define NV_PPWR_FALCON_IRQMCLR_EXTERR                          5:5
#define NV_PPWR_FALCON_IRQMCLR_SWGEN0                          6:6
#define NV_PPWR_FALCON_IRQMCLR_SWGEN1                          7:7
#define NV_PPWR_FALCON_IRQMCLR_EXT                            15:8
#define NV_PPWR_FALCON_IRQMASK                            0x10a018
#define NV_PPWR_FALCON_IRQDEST                            0x10a01c
#define NV_PPWR_FALCON_IRQDEST_HOST_GPTMR                      0:0
#define NV_PPWR_FALCON_IRQDEST_HOST_WDTMR                      1:1
#define NV_PPWR_FALCON_IRQDEST_HOST_MTHD                       2:2
#define NV_PPWR_FALCON_IRQDEST_HOST_CTXSW                      3:3
#define NV_PPWR_FALCON_IRQDEST_HOST_HALT                       4:4
#define NV_PPWR_FALCON_IRQDEST_HOST_EXTERR                     5:5
#define NV_PPWR_FALCON_IRQDEST_HOST_SWGEN0                     6:6
#define NV_PPWR_FALCON_IRQDEST_HOST_SWGEN1                     7:7
#define NV_PPWR_FALCON_IRQDEST_HOST_EXT                       15:8
#define NV_PPWR_FALCON_IRQDEST_TARGET_GPTMR                  16:16
#define NV_PPWR_FALCON_IRQDEST_TARGET_WDTMR                  17:17
#define NV_PPWR_FALCON_IRQDEST_TARGET_MTHD                   18:18
#define NV_PPWR_FALCON_IRQDEST_TARGET_CTXSW                  19:19
#define NV_PPWR_FALCON_IRQDEST_TARGET_HALT                   20:20
#define NV_PPWR_FALCON_IRQDEST_TARGET_EXTERR                 21:21
#define NV_PPWR_FALCON_IRQDEST_TARGET_SWGEN0                 22:22
#define NV_PPWR_FALCON_IRQDEST_TARGET_SWGEN1                 23:23
#define NV_PPWR_FALCON_IRQDEST_TARGET_EXT                    31:24
#define NV_PPWR_FALCON_CURCTX                             0x10a050
#define NV_PPWR_FALCON_NXTCTX                             0x10a054
#define NV_PPWR_FALCON_MAILBOX0                           0x10a040
#define NV_PPWR_FALCON_MAILBOX1                           0x10a044
#define NV_PPWR_FALCON_ITFEN                              0x10a048
#define NV_PPWR_FALCON_ITFEN_CTXEN                             0:0
#define NV_PPWR_FALCON_ITFEN_CTXEN_ENABLE                        1
#define NV_PPWR_FALCON_IDLESTATE                          0x10a04c
#define NV_PPWR_FALCON_IDLESTATE_FALCON_BUSY                   0:0
#define NV_PPWR_FALCON_IDLESTATE_EXT_BUSY                     15:1
#define NV_PPWR_FALCON_OS                                 0x10a080
#define NV_PPWR_FALCON_ENGCTL                             0x10a0a4
#define NV_PPWR_FALCON_CPUCTL                             0x10a100
#define NV_PPWR_FALCON_CPUCTL_STARTCPU                         1:1
#define NV_PPWR_FALCON_CPUCTL_HALTED                           4:4
#define NV_PPWR_FALCON_BOOTVEC                            0x10a104
#define NV_PPWR_FALCON_BOOTVEC_VEC                            31:0
#define NV_PPWR_FALCON_HWCFG                              0x10a108
#define NV_PPWR_FALCON_HWCFG_IMEM_SIZE                         8:0
#define NV_PPWR_FALCON_HWCFG_DMEM_SIZE                        17:9
#define NV_PPWR_FALCON_DMACTL                             0x10a10c
#define NV_PPWR_FALCON_DMACTL_DMEM_SCRUBBING                   1:1
#define NV_PPWR_FALCON_DMACTL_IMEM_SCRUBBING                   2:2
#define NV_PPWR_FALCON_DMATRFBASE                         0x10a110
#define NV_PPWR_FALCON_DMATRFMOFFS                        0x10a114
#define NV_PPWR_FALCON_DMATRFCMD                          0x10a118
#define NV_PPWR_FALCON_DMATRFCMD_IMEM                          4:4
#define NV_PPWR_FALCON_DMATRFCMD_WRITE                         5:5
#define NV_PPWR_FALCON_DMATRFCMD_SIZE                         10:8
#define NV_PPWR_FALCON_DMATRFCMD_CTXDMA                      14:12
#define NV_PPWR_FALCON_DMATRFFBOFFS                       0x10a11c
#define NV_PPWR_FALCON_EXTERRADDR                         0x10a168
#define NV_PPWR_FALCON_EXTERRSTAT                         0x10a16c
#define NV_PPWR_FALCON_EXTERRSTAT_VALID                      31:31
#define NV_PPWR_FALCON_ICD_CMD                            0x10a200
#define NV_PPWR_FALCON_ICD_CMD_OPC                             3:0
#define NV_PPWR_FALCON_ICD_CMD_OPC_RREG                          8
#define NV_PPWR_FALCON_ICD_CMD_OPC_RSTAT                        14
#define NV_PPWR_FALCON_ICD_CMD_IDX                            12:8
#define NV_PPWR_FALCON_ICD_RDATA                          0x10a20c
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
#define NV_PPWR_PMU_IDLE_MASK_CE_2                           21:21
#define NV_PPWR_PMU_IDLE_COUNT(i)                (0x10a508+(i)*16)
#define NV_PPWR_PMU_IDLE_COUNT_VALUE                          30:0
#define NV_PPWR_PMU_IDLE_COUNT_RESET                         31:31
#define NV_PPWR_PMU_IDLE_CTRL(i)                 (0x10a50c+(i)*16)
#define NV_PPWR_PMU_IDLE_CTRL_VALUE                            1:0
#define NV_PPWR_PMU_IDLE_CTRL_VALUE_BUSY                         2
#define NV_PPWR_PMU_IDLE_CTRL_VALUE_ALWAYS                       3
#define NV_PPWR_PMU_IDLE_CTRL_FILTER                           2:2
#define NV_PPWR_PMU_IDLE_MASK_SUPP(i)             (0x10a9f0+(i)*8)
#define NV_PPWR_PMU_IDLE_MASK_1_SUPP(i)           (0x10a9f4+(i)*8)
#define NV_PPWR_PMU_IDLE_CTRL_SUPP(i)             (0x10aa30+(i)*8)
#define NV_PPWR_PMU_DEBUG(i)                      (0x10a5c0+(i)*4)
#define NV_PPWR_PMU_DEBUG__SIZE_1                                4
#define NV_PPWR_PMU_MAILBOX(i)                    (0x10a5d0+(i)*4)
#define NV_PPWR_PMU_MAILBOX__SIZE_1                              4
#define NV_PPWR_PMU_BAR0_ADDR                             0x10a7a0
#define NV_PPWR_PMU_BAR0_DATA                             0x10a7a4
#define NV_PPWR_PMU_BAR0_CTL                              0x10a7ac
#define NV_PPWR_PMU_BAR0_TIMEOUT                          0x10a7a8
#define NV_PPWR_PMU_BAR0_ERROR_STATUS                     0x10a7b0
#define NV_PPWR_PMU_BAR0_FECS_ERROR                       0x10a988
#define NV_PPWR_PMU_PG_IDLEFILTH(i)               (0x10a6c0+(i)*4)
#define NV_PPWR_PMU_PG_PPUIDLEFILTH(i)            (0x10a6e8+(i)*4)
#define NV_PPWR_PMU_PG_IDLE_CNT(i)                (0x10a710+(i)*4)
#define NV_PPWR_PMU_PG_INTREN(i)                  (0x10a760+(i)*4)
#define NV_PPWR_FBIF_TRANSCFG(i)                  (0x10a600+(i)*4)
#define NV_PPWR_FBIF_TRANSCFG_TARGET                           1:0
#define NV_PPWR_FBIF_TRANSCFG_TARGET_LOCAL_FB                    0
#define NV_PPWR_FBIF_TRANSCFG_TARGET_COHERENT_SYSMEM             1
#define NV_PPWR_FBIF_TRANSCFG_TARGET_NONCOHERENT_SYSMEM          2
#define NV_PPWR_FBIF_TRANSCFG_MEM_TYPE                         2:2
#define NV_PPWR_FBIF_TRANSCFG_MEM_TYPE_VIRTUAL                   0
#define NV_PPWR_FBIF_TRANSCFG_MEM_TYPE_PHYSICAL                  1

#endif /* __nv_gk110_pwr_pri_hwref_h__ */
