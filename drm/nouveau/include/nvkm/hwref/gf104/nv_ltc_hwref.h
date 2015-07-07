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
#ifndef __nv_gf104_ltc_hwref_h__
#define __nv_gf104_ltc_hwref_h__

#define NV_PLTCG_LTC0_LTS0_INTR                           0x141020
#define NV_PLTCG_LTC0_LTS0_CBC_CTRL_1                     0x1410c8
#define NV_PLTCG_LTC0_LTS0_TSTG_CFG_1                     0x141104
#define NV_PLTCG_LTC0_LTS0_TSTG_CFG_1_ACTIVE_WAYS             15:0
#define NV_PLTCG_LTC0_LTS0_DSTG_CFG0                      0x141200
#define NV_PLTCG_LTC0_LTSS_INTR                           0x140820
#define NV_PLTCG_LTC0_LTSS_TSTG_CMGMT_0                   0x140910
#define NV_PLTCG_LTC0_LTSS_TSTG_CMGMT_0_INVALIDATE             0:0
#define NV_PLTCG_LTC0_LTSS_TSTG_CMGMT_1                   0x140914
#define NV_PLTCG_LTC0_LTSS_TSTG_CMGMT_1_CLEAN                  0:0
#define NV_PLTCG_LTC1_LTSS_TSTG_CMGMT_0                   0x142910
#define NV_PLTCG_LTC1_LTSS_TSTG_CMGMT_0_INVALIDATE             0:0
#define NV_PLTCG_LTC1_LTSS_TSTG_CMGMT_1                   0x142914
#define NV_PLTCG_LTC1_LTSS_TSTG_CMGMT_1_CLEAN                  0:0
#define NV_PLTCG_LTCS_LTSS_INTR                           0x17e820
#define NV_PLTCG_LTCS_LTSS_INTR_EN_EVICTED_CB                20:20
#define NV_PLTCG_LTCS_LTSS_CBC_CTRL_1                     0x17e8c8
#define NV_PLTCG_LTCS_LTSS_CBC_CTRL_1_CLEAN                    0:0
#define NV_PLTCG_LTCS_LTSS_CBC_CTRL_1_CLEAN_ACTIVE               1
#define NV_PLTCG_LTCS_LTSS_CBC_CTRL_1_INVALIDATE               1:1
#define NV_PLTCG_LTCS_LTSS_CBC_CTRL_1_INVALIDATE_ACTIVE          1
#define NV_PLTCG_LTCS_LTSS_CBC_CTRL_1_CLEAR                    2:2
#define NV_PLTCG_LTCS_LTSS_CBC_CTRL_1_CLEAR_ACTIVE               1
#define NV_PLTCG_LTCS_LTSS_CBC_CTRL_2                     0x17e8cc
#define NV_PLTCG_LTCS_LTSS_CBC_CTRL_2_CLEAR_LOWER_BOUND       16:0
#define NV_PLTCG_LTCS_LTSS_CBC_CTRL_3                     0x17e8d0
#define NV_PLTCG_LTCS_LTSS_CBC_CTRL_3_CLEAR_UPPER_BOUND       16:0
#define NV_PLTCG_LTCS_LTSS_CBC_CTRL_3_CLEAR_UPPER_BOUND_INIT           0x1ffff
#define NV_PLTCG_LTCS_LTSS_CBC_BASE                       0x17e8d4
#define NV_PLTCG_LTCS_LTSS_CBC_BASE_ADDRESS                   25:0
#define NV_PLTCG_LTCS_LTSS_CBC_PARAM                      0x17e8dc
#define NV_PLTCG_LTCS_LTSS_CBC_PARAM_COMPTAGS_PER_CACHE_LINE  15:0
#define NV_PLTCG_LTCS_LTSS_CBC_PARAM_CACHE_LINE_SIZE         27:24
#define NV_PLTCG_LTCS_LTSS_CBC_PARAM_SLICES_PER_FBP          31:28
#define NV_PLTCG_LTCS_LTSS_TSTG_CMGMT_0                   0x17e910
#define NV_PLTCG_LTCS_LTSS_TSTG_CMGMT_0_INVALIDATE             0:0
#define NV_PLTCG_LTCS_LTSS_TSTG_CMGMT_0_MAX_CYCLES_BETWEEN_INVALIDATES    11:8
#define NV_PLTCG_LTCS_LTSS_TSTG_CMGMT_0_MAX_CYCLES_BETWEEN_INVALIDATES_3     3
#define NV_PLTCG_LTCS_LTSS_TSTG_CMGMT_0_INVALIDATE_EVICT_LAST_CLASS      28:28
#define NV_PLTCG_LTCS_LTSS_TSTG_CMGMT_0_INVALIDATE_EVICT_NORMAL_CLASS    29:29
#define NV_PLTCG_LTCS_LTSS_TSTG_CMGMT_0_INVALIDATE_EVICT_FIRST_CLASS     30:30
#define NV_PLTCG_LTCS_LTSS_TSTG_CMGMT_1                   0x17e914
#define NV_PLTCG_LTCS_LTSS_TSTG_CMGMT_1_CLEAN                  0:0
#define NV_PLTCG_LTCS_LTSS_TSTG_CMGMT_1_MAX_CYCLES_BETWEEN_CLEANS         11:8
#define NV_PLTCG_LTCS_LTSS_TSTG_CMGMT_1_MAX_CYCLES_BETWEEN_CLEANS_3          3
#define NV_PLTCG_LTCS_LTSS_TSTG_CMGMT_1_CLEAN_WAIT_FOR_FB_TO_PULL        16:16
#define NV_PLTCG_LTCS_LTSS_TSTG_CMGMT_1_CLEAN_EVICT_LAST_CLASS           28:28
#define NV_PLTCG_LTCS_LTSS_TSTG_CMGMT_1_CLEAN_EVICT_NORMAL_CLASS         29:29
#define NV_PLTCG_LTCS_LTSS_TSTG_CMGMT_1_CLEAN_EVICT_FIRST_CLASS          30:30
#define NV_PLTCG_LTCS_LTSS_TSTG_SET_MGMT_0                0x17e91c
#define NV_PLTCG_LTCS_LTSS_TSTG_SET_MGMT_0_MAX_WAYS_EVICT_LAST           20:16
#define NV_PLTCG_LTCS_LTSS_TSTG_SET_MGMT_2                0x17e924
#define NV_PLTCG_LTCS_LTSS_TSTG_SET_MGMT_2_L2_BYPASS_MODE    28:28
#define NV_PLTCG_LTCS_LTSS_DSTG_CFG0                      0x17ea00
#define NV_PLTCG_LTCS_LTSS_DSTG_ZBC_INDEX                 0x17ea44
#define NV_PLTCG_LTCS_LTSS_DSTG_ZBC_INDEX_ADDRESS              3:0
#define NV_PLTCG_LTCS_LTSS_DSTG_ZBC_COLOR_CLEAR_VALUE(i)    (0x17ea48+((i)*4))
#define NV_PLTCG_LTCS_LTSS_DSTG_ZBC_COLOR_CLEAR_VALUE__SIZE_1    4
#define NV_PLTCG_LTCS_LTSS_DSTG_ZBC_DEPTH_CLEAR_VALUE     0x17ea58
#define NV_PLTCG_LTCS_LTSS_DSTG_ZBC_DEPTH_CLEAR_VALUE_FIELD   31:0
#define NV_PLTCG_LTC0_LTS0_CBC_BASE_ALIGNMENT_SHIFT             11

#endif /* __nv_gf104_ltc_hwref_h__ */
