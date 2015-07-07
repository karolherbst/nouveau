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
#ifndef __nv_gk110b_ctxsw_prog_hwref_h__
#define __nv_gk110b_ctxsw_prog_hwref_h__

#define NV_CTXSW_FECS_HEADER                                 0x100
#define NV_CTXSW_MAIN_IMAGE_NUM_GPCS                             8
#define NV_CTXSW_MAIN_IMAGE_PRI_PATCH_COUNT                     16
#define NV_CTXSW_MAIN_IMAGE_PRI_PATCH_ADR_LO                    20
#define NV_CTXSW_MAIN_IMAGE_PRI_PATCH_ADR_HI                    24
#define NV_CTXSW_MAIN_IMAGE_ZCULL                               28
#define NV_CTXSW_MAIN_IMAGE_ZCULL_MODE                         2:0
#define NV_CTXSW_MAIN_IMAGE_ZCULL_MODE_NO_CTXSW                  1
#define NV_CTXSW_MAIN_IMAGE_ZCULL_MODE_SEPARATE_BUFFER           2
#define NV_CTXSW_MAIN_IMAGE_ZCULL_PTR                           32
#define NV_CTXSW_MAIN_IMAGE_PM                                0x28
#define NV_CTXSW_MAIN_IMAGE_PM_MODE                            2:0
#define NV_CTXSW_MAIN_IMAGE_PM_MODE_NO_CTXSW                     0
#define NV_CTXSW_MAIN_IMAGE_SMPC_MODE                          5:3
#define NV_CTXSW_MAIN_IMAGE_SMPC_MODE_NO_CTXSW                   0
#define NV_CTXSW_MAIN_IMAGE_SMPC_MODE_CTXSW                      1
#define NV_CTXSW_MAIN_IMAGE_PM_PTR                            0x2c
#define NV_CTXSW_MAIN_IMAGE_MISC_OPTIONS                      0x3c
#define NV_CTXSW_MAIN_IMAGE_MISC_OPTIONS_VERIF_FEATURES        3:3
#define NV_CTXSW_MAIN_IMAGE_PREEMPTION_OPTIONS                0x60
#define NV_CTXSW_MAIN_IMAGE_PREEMPTION_OPTIONS_CONTROL         0:0
#define NV_CTXSW_MAIN_IMAGE_PRIV_ACCESS_MAP_CONFIG            0xa0
#define NV_CTXSW_MAIN_IMAGE_PRIV_ACCESS_MAP_CONFIG_MODE        1:0
#define NV_CTXSW_MAIN_IMAGE_PRIV_ACCESS_MAP_CONFIG_MODE_ALLOW_ALL            0
#define NV_CTXSW_MAIN_IMAGE_PRIV_ACCESS_MAP_CONFIG_MODE_USE_MAP  2
#define NV_CTXSW_MAIN_IMAGE_PRIV_ACCESS_MAP_ADDR_LO           0xa4
#define NV_CTXSW_MAIN_IMAGE_PRIV_ACCESS_MAP_ADDR_HI           0xa8
#define NV_CTXSW_MAIN_EXTENDED_BUFFER_CTL                     0xec
#define NV_CTXSW_MAIN_EXTENDED_BUFFER_CTL_OFFSET              15:0
#define NV_CTXSW_MAIN_EXTENDED_BUFFER_CTL_SIZE               23:16
#define NV_CTXSW_MAIN_IMAGE_NUM_SAVE_OPERATIONS               0xf4
#define NV_CTXSW_MAIN_IMAGE_NUM_RESTORE_OPERATIONS            0xf8
#define NV_CTXSW_MAIN_IMAGE_MAGIC_VALUE                       0xfc
#define NV_CTXSW_MAIN_IMAGE_MAGIC_VALUE_V                     31:0
#define NV_CTXSW_MAIN_IMAGE_MAGIC_VALUE_V_VALUE         0x600dc0de
#define NV_CTXSW_LOCAL_PRIV_REGISTER_CTL                        12
#define NV_CTXSW_LOCAL_PRIV_REGISTER_CTL_OFFSET               15:0
#define NV_CTXSW_LOCAL_IMAGE_PPC_INFO                         0xf4
#define NV_CTXSW_LOCAL_IMAGE_PPC_INFO_NUM_PPCS                15:0
#define NV_CTXSW_LOCAL_IMAGE_PPC_INFO_PPC_MASK               31:16
#define NV_CTXSW_LOCAL_IMAGE_NUM_TPCS                         0xf8
#define NV_CTXSW_LOCAL_MAGIC_VALUE                            0xfc
#define NV_CTXSW_LOCAL_MAGIC_VALUE_V                          31:0
#define NV_CTXSW_LOCAL_MAGIC_VALUE_V_VALUE              0xad0becab
#define NV_CTXSW_EXTENDED_BUFFER_SEGMENTS_SIZE_IN_BYTES      0x100
#define NV_CTXSW_EXTENDED_MARKER_SIZE_IN_BYTES                   4
#define NV_CTXSW_EXTENDED_NUM_SMPC_QUADRANTS                     4
#define NV_CTXSW_EXTENDED_SM_DSM_PERF_COUNTER_CONTROL_REGISTER_STRIDE        4
#define NV_CTXSW_EXTENDED_SM_DSM_PERF_COUNTER_REGISTER_STRIDE    5

#endif /* __nv_gk110b_ctxsw_prog_hwref_h__ */
