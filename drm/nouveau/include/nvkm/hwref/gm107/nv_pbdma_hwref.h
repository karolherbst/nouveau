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
#ifndef __nv_gm107_pbdma_hwref_h__
#define __nv_gm107_pbdma_hwref_h__

#define NV_PPBDMA_GP_ENTRY1                             0x10000004
#define NV_PPBDMA_GP_ENTRY1_GET_HI                             7:0
#define NV_PPBDMA_GP_ENTRY1_LENGTH                           30:10
#define NV_PPBDMA_GP_BASE(i)                  (0x40048+(i)*0x2000)
#define NV_PPBDMA_GP_BASE__SIZE_1                                2
#define NV_PPBDMA_GP_BASE_OFFSET                              31:3
#define NV_PPBDMA_GP_BASE_RSVD                                 2:0
#define NV_PPBDMA_GP_BASE_HI(i)               (0x4004c+(i)*0x2000)
#define NV_PPBDMA_GP_BASE_HI_OFFSET                            7:0
#define NV_PPBDMA_GP_BASE_HI_LIMIT2                          20:16
#define NV_PPBDMA_GP_FETCH(i)                 (0x40050+(i)*0x2000)
#define NV_PPBDMA_GP_GET(i)                   (0x40014+(i)*0x2000)
#define NV_PPBDMA_GP_PUT(i)                   (0x40000+(i)*0x2000)
#define NV_PPBDMA_PB_FETCH(i)                 (0x40054+(i)*0x2000)
#define NV_PPBDMA_PB_FETCH_HI(i)              (0x40058+(i)*0x2000)
#define NV_PPBDMA_GET(i)                      (0x40018+(i)*0x2000)
#define NV_PPBDMA_GET_HI(i)                   (0x4001c+(i)*0x2000)
#define NV_PPBDMA_PUT(i)                      (0x4005c+(i)*0x2000)
#define NV_PPBDMA_PUT_HI(i)                   (0x40060+(i)*0x2000)
#define NV_PPBDMA_FORMATS(i)                  (0x4009c+(i)*0x2000)
#define NV_PPBDMA_FORMATS_GP                                   1:0
#define NV_PPBDMA_FORMATS_GP_FERMI0                              0
#define NV_PPBDMA_FORMATS_PB                                   9:8
#define NV_PPBDMA_FORMATS_PB_FERMI1                              1
#define NV_PPBDMA_FORMATS_MP                                 25:24
#define NV_PPBDMA_FORMATS_MP_FERMI0                              0
#define NV_PPBDMA_PB_HEADER(i)                (0x40084+(i)*0x2000)
#define NV_PPBDMA_PB_HEADER_PRIV                               1:1
#define NV_PPBDMA_PB_HEADER_PRIV_USER                            0
#define NV_PPBDMA_PB_HEADER_METHOD                            13:2
#define NV_PPBDMA_PB_HEADER_METHOD_ZERO                          0
#define NV_PPBDMA_PB_HEADER_SUBCHANNEL                       18:16
#define NV_PPBDMA_PB_HEADER_SUBCHANNEL_ZERO                      0
#define NV_PPBDMA_PB_HEADER_LEVEL                            20:20
#define NV_PPBDMA_PB_HEADER_LEVEL_MAIN                           0
#define NV_PPBDMA_PB_HEADER_FIRST                            22:22
#define NV_PPBDMA_PB_HEADER_TYPE                             31:29
#define NV_PPBDMA_PB_HEADER_TYPE_INC                             1
#define NV_PPBDMA_SUBDEVICE(i)                (0x40094+(i)*0x2000)
#define NV_PPBDMA_SUBDEVICE_ID                                11:0
#define NV_PPBDMA_SUBDEVICE_STATUS                           28:28
#define NV_PPBDMA_SUBDEVICE_STATUS_ACTIVE                        1
#define NV_PPBDMA_SUBDEVICE_CHANNEL_DMA                      29:29
#define NV_PPBDMA_SUBDEVICE_CHANNEL_DMA_ENABLE                   1
#define NV_PPBDMA_METHOD0(i)                  (0x400c0+(i)*0x2000)
#define NV_PPBDMA_DATA0(i)                    (0x400c4+(i)*0x2000)
#define NV_PPBDMA_TARGET(i)                   (0x400ac+(i)*0x2000)
#define NV_PPBDMA_TARGET_ENGINE                                4:0
#define NV_PPBDMA_TARGET_ENGINE_SW                              31
#define NV_PPBDMA_ACQUIRE(i)                  (0x40030+(i)*0x2000)
#define NV_PPBDMA_ACQUIRE_RETRY_MAN                            6:0
#define NV_PPBDMA_ACQUIRE_RETRY_MAN_2                            2
#define NV_PPBDMA_ACQUIRE_RETRY_EXP                           10:7
#define NV_PPBDMA_ACQUIRE_RETRY_EXP_2                            2
#define NV_PPBDMA_ACQUIRE_TIMEOUT_EXP                        14:11
#define NV_PPBDMA_ACQUIRE_TIMEOUT_EXP_MAX                       15
#define NV_PPBDMA_ACQUIRE_TIMEOUT_MAN                        30:15
#define NV_PPBDMA_ACQUIRE_TIMEOUT_MAN_MAX                   0xffff
#define NV_PPBDMA_ACQUIRE_TIMEOUT_EN                         31:31
#define NV_PPBDMA_ACQUIRE_TIMEOUT_EN_DISABLE                     0
#define NV_PPBDMA_STATUS(i)                   (0x40100+(i)*0x2000)
#define NV_PPBDMA_CHANNEL(i)                  (0x40120+(i)*0x2000)
#define NV_PPBDMA_HDR_SHADOW(i)               (0x40118+(i)*0x2000)
#define NV_PPBDMA_SIGNATURE(i)                (0x40010+(i)*0x2000)
#define NV_PPBDMA_SIGNATURE_HW                                15:0
#define NV_PPBDMA_SIGNATURE_HW_VALID                        0xface
#define NV_PPBDMA_SIGNATURE_SW                               31:16
#define NV_PPBDMA_SIGNATURE_SW_ZERO                              0
#define NV_PPBDMA_USERD(i)                    (0x40008+(i)*0x2000)
#define NV_PPBDMA_USERD_TARGET                                 1:0
#define NV_PPBDMA_USERD_TARGET_VID_MEM                           0
#define NV_PPBDMA_USERD_ADDR                                  31:9
#define NV_PPBDMA_USERD_HI(i)                 (0x4000c+(i)*0x2000)
#define NV_PPBDMA_USERD_HI_ADDR                                7:0
#define NV_PPBDMA_RUNLIST_TIMESLICE(i)        (0x400f8+(i)*0x2000)
#define NV_PPBDMA_RUNLIST_TIMESLICE_TIMEOUT                    7:0
#define NV_PPBDMA_RUNLIST_TIMESLICE_TIMEOUT_128               0x80
#define NV_PPBDMA_RUNLIST_TIMESLICE_TIMESCALE                15:12
#define NV_PPBDMA_RUNLIST_TIMESLICE_TIMESCALE_3                  3
#define NV_PPBDMA_RUNLIST_TIMESLICE_ENABLE                   28:28
#define NV_PPBDMA_HCE_CTRL(i)                 (0x400e4+(i)*0x2000)
#define NV_PPBDMA_HCE_CTRL_HCE_PRIV_MODE                       5:5
#define NV_PPBDMA_TIMEOUT(i)                  (0x4012c+(i)*0x2000)
#define NV_PPBDMA_TIMEOUT__SIZE_1                                2
#define NV_PPBDMA_TIMEOUT_PERIOD                              31:0
#define NV_PPBDMA_TIMEOUT_PERIOD_MAX                    0xffffffff
#define NV_PPBDMA_INTR_0(i)                   (0x40108+(i)*0x2000)
#define NV_PPBDMA_INTR_0_MEMREQ                                0:0
#define NV_PPBDMA_INTR_0_MEMACK_TIMEOUT                        1:1
#define NV_PPBDMA_INTR_0_MEMACK_EXTRA                          2:2
#define NV_PPBDMA_INTR_0_MEMDAT_TIMEOUT                        3:3
#define NV_PPBDMA_INTR_0_MEMDAT_EXTRA                          4:4
#define NV_PPBDMA_INTR_0_MEMFLUSH                              5:5
#define NV_PPBDMA_INTR_0_MEMOP                                 6:6
#define NV_PPBDMA_INTR_0_LBCONNECT                             7:7
#define NV_PPBDMA_INTR_0_LBREQ                                 8:8
#define NV_PPBDMA_INTR_0_LBACK_TIMEOUT                         9:9
#define NV_PPBDMA_INTR_0_LBACK_EXTRA                         10:10
#define NV_PPBDMA_INTR_0_LBDAT_TIMEOUT                       11:11
#define NV_PPBDMA_INTR_0_LBDAT_EXTRA                         12:12
#define NV_PPBDMA_INTR_0_GPFIFO                              13:13
#define NV_PPBDMA_INTR_0_GPPTR                               14:14
#define NV_PPBDMA_INTR_0_GPENTRY                             15:15
#define NV_PPBDMA_INTR_0_GPCRC                               16:16
#define NV_PPBDMA_INTR_0_PBPTR                               17:17
#define NV_PPBDMA_INTR_0_PBENTRY                             18:18
#define NV_PPBDMA_INTR_0_PBCRC                               19:19
#define NV_PPBDMA_INTR_0_XBARCONNECT                         20:20
#define NV_PPBDMA_INTR_0_METHOD                              21:21
#define NV_PPBDMA_INTR_0_METHODCRC                           22:22
#define NV_PPBDMA_INTR_0_DEVICE                              23:23
#define NV_PPBDMA_INTR_0_SEMAPHORE                           25:25
#define NV_PPBDMA_INTR_0_ACQUIRE                             26:26
#define NV_PPBDMA_INTR_0_PRI                                 27:27
#define NV_PPBDMA_INTR_0_NO_CTXSW_SEG                        29:29
#define NV_PPBDMA_INTR_0_PBSEG                               30:30
#define NV_PPBDMA_INTR_0_SIGNATURE                           31:31
#define NV_PPBDMA_INTR_1(i)                   (0x40148+(i)*0x2000)
#define NV_PPBDMA_INTR_EN_0(i)                (0x4010c+(i)*0x2000)
#define NV_PPBDMA_INTR_EN_0_LBREQ                              8:8
#define NV_PPBDMA_INTR_EN_1(i)                (0x4014c+(i)*0x2000)
#define NV_PPBDMA_INTR_STALL(i)               (0x4013c+(i)*0x2000)
#define NV_PPBDMA_INTR_STALL_LBREQ                             8:8
#define NV_UDMA_NOP                                              8

#endif /* __nv_gm107_pbdma_hwref_h__ */
