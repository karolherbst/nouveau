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
#ifndef __nv_gm204_ram_hwref_h__
#define __nv_gm204_ram_hwref_h__

#define NV_RAMIN_BASE_SHIFT                                     12
#define NV_RAMIN_ALLOC_SIZE                                 0x1000
#define NV_RAMIN_RAMFC                       (0x7f*32+31):(0*32+0)
#define NV_RAMIN_PAGE_DIR_BASE_TARGET      (0x80*32+1):(0x80*32+0)
#define NV_RAMIN_PAGE_DIR_BASE_TARGET_VID_MEM                    0
#define NV_RAMIN_PAGE_DIR_BASE_VOL         (0x80*32+2):(0x80*32+2)
#define NV_RAMIN_BIG_PAGE_SIZE           (0x80*32+11):(0x80*32+11)
#define NV_RAMIN_BIG_PAGE_SIZE_128KB                             0
#define NV_RAMIN_BIG_PAGE_SIZE_64KB                              1
#define NV_RAMIN_PAGE_DIR_BASE_LO        (0x80*32+31):(0x80*32+12)
#define NV_RAMIN_PAGE_DIR_BASE_HI          (0x81*32+7):(0x81*32+0)
#define NV_RAMIN_ADR_LIMIT_LO            (0x82*32+31):(0x82*32+12)
#define NV_RAMIN_ADR_LIMIT_HI              (0x83*32+7):(0x83*32+0)
#define NV_RAMIN_ENGINE_CS                 (0x84*32+3):(0x84*32+3)
#define NV_RAMIN_ENGINE_CS_WFI                                   0
#define NV_RAMIN_ENGINE_CS_FG                                    1
#define NV_RAMIN_GR_CS                     (0x84*32+3):(0x84*32+3)
#define NV_RAMIN_GR_CS_WFI                                       0
#define NV_RAMIN_GR_WFI_TARGET             (0x84*32+1):(0x84*32+0)
#define NV_RAMIN_GR_WFI_MODE               (0x84*32+2):(0x84*32+2)
#define NV_RAMIN_GR_WFI_MODE_PHYSICAL                            0
#define NV_RAMIN_GR_WFI_MODE_VIRTUAL                             1
#define NV_RAMIN_GR_WFI_PTR_LO           (0x84*32+31):(0x84*32+12)
#define NV_RAMIN_GR_WFI_PTR_HI             (0x85*32+7):(0x85*32+0)
#define NV_RAMFC_GP_PUT                         (0*32+31):(0*32+0)
#define NV_RAMFC_USERD                          (2*32+31):(2*32+0)
#define NV_RAMFC_USERD_HI                       (3*32+31):(3*32+0)
#define NV_RAMFC_SIGNATURE                      (4*32+31):(4*32+0)
#define NV_RAMFC_GP_GET                         (5*32+31):(5*32+0)
#define NV_RAMFC_PB_GET                         (6*32+31):(6*32+0)
#define NV_RAMFC_PB_GET_HI                      (7*32+31):(7*32+0)
#define NV_RAMFC_PB_TOP_LEVEL_GET               (8*32+31):(8*32+0)
#define NV_RAMFC_PB_TOP_LEVEL_GET_HI            (9*32+31):(9*32+0)
#define NV_RAMFC_ACQUIRE                      (12*32+31):(12*32+0)
#define NV_RAMFC_SEMAPHOREA                   (14*32+31):(14*32+0)
#define NV_RAMFC_SEMAPHOREB                   (15*32+31):(15*32+0)
#define NV_RAMFC_SEMAPHOREC                   (16*32+31):(16*32+0)
#define NV_RAMFC_SEMAPHORED                   (17*32+31):(17*32+0)
#define NV_RAMFC_GP_BASE                      (18*32+31):(18*32+0)
#define NV_RAMFC_GP_BASE_HI                   (19*32+31):(19*32+0)
#define NV_RAMFC_GP_FETCH                     (20*32+31):(20*32+0)
#define NV_RAMFC_PB_FETCH                     (21*32+31):(21*32+0)
#define NV_RAMFC_PB_FETCH_HI                  (22*32+31):(22*32+0)
#define NV_RAMFC_PB_PUT                       (23*32+31):(23*32+0)
#define NV_RAMFC_PB_PUT_HI                    (24*32+31):(24*32+0)
#define NV_RAMFC_PB_HEADER                (0x21*32+31):(0x21*32+0)
#define NV_RAMFC_PB_COUNT                 (0x22*32+31):(0x22*32+0)
#define NV_RAMFC_SUBDEVICE                (0x25*32+31):(0x25*32+0)
#define NV_RAMFC_FORMATS                  (0x27*32+31):(0x27*32+0)
#define NV_RAMFC_TARGET                   (0x2b*32+31):(0x2b*32+0)
#define NV_RAMFC_HCE_CTRL                 (0x39*32+31):(0x39*32+0)
#define NV_RAMFC_CHID                     (0x3a*32+31):(0x3a*32+0)
#define NV_RAMFC_CHID_ID                                      11:0
#define NV_RAMFC_RUNLIST_TIMESLICE        (0x3e*32+31):(0x3e*32+0)
#define NV_RAMFC_SIZE_VAL                                    0x200
#define NV_RAMUSERD_PUT                       (16*32+31):(16*32+0)
#define NV_RAMUSERD_GET                       (17*32+31):(17*32+0)
#define NV_RAMUSERD_REF                       (18*32+31):(18*32+0)
#define NV_RAMUSERD_PUT_HI                    (19*32+31):(19*32+0)
#define NV_RAMUSERD_REF_THRESHOLD             (20*32+31):(20*32+0)
#define NV_RAMUSERD_TOP_LEVEL_GET             (22*32+31):(22*32+0)
#define NV_RAMUSERD_TOP_LEVEL_GET_HI          (23*32+31):(23*32+0)
#define NV_RAMUSERD_GET_HI                    (24*32+31):(24*32+0)
#define NV_RAMUSERD_GP_GET                (0x22*32+31):(0x22*32+0)
#define NV_RAMUSERD_GP_PUT                (0x23*32+31):(0x23*32+0)
#define NV_RAMUSERD_BASE_SHIFT                                   9
#define NV_RAMUSERD_CHAN_SIZE                                0x200
#define NV_RAMUSERD_GP_TOP_LEVEL_GET          (22*32+31):(22*32+0)
#define NV_RAMUSERD_GP_TOP_LEVEL_GET_HI       (23*32+31):(23*32+0)
#define NV_RAMRL_ENTRY_CHID                                   11:0
#define NV_RAMRL_ENTRY_ID                                     11:0
#define NV_RAMRL_ENTRY_TYPE                                  13:13
#define NV_RAMRL_ENTRY_TYPE_CHID                                 0
#define NV_RAMRL_ENTRY_TYPE_TSG                                  1
#define NV_RAMRL_ENTRY_TIMESLICE_SCALE                       17:14
#define NV_RAMRL_ENTRY_TIMESLICE_SCALE_3                         3
#define NV_RAMRL_ENTRY_TIMESLICE_TIMEOUT                     25:18
#define NV_RAMRL_ENTRY_TIMESLICE_TIMEOUT_128                  0x80
#define NV_RAMRL_ENTRY_TSG_LENGTH                            31:26
#define NV_RAMRL_ENTRY_SIZE                                      8

#endif /* __nv_gm204_ram_hwref_h__ */
