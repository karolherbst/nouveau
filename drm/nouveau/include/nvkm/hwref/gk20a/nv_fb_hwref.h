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
#ifndef __nv_gk20a_fb_hwref_h__
#define __nv_gk20a_fb_hwref_h__

#define NV_PFB_PRI_MMU_CTRL                               0x100c80
#define NV_PFB_PRI_MMU_CTRL_VM_PG_SIZE                         0:0
#define NV_PFB_PRI_MMU_CTRL_VM_PG_SIZE_128KB                     0
#define NV_PFB_PRI_MMU_CTRL_VM_PG_SIZE_64KB                      1
#define NV_PFB_PRI_MMU_CTRL_PRI_FIFO_EMPTY                   15:15
#define NV_PFB_PRI_MMU_CTRL_PRI_FIFO_SPACE                   23:16
#define NV_PFB_PRI_MMU_INVALIDATE_PDB                     0x100cb8
#define NV_PFB_PRI_MMU_INVALIDATE_PDB_APERTURE                 1:1
#define NV_PFB_PRI_MMU_INVALIDATE_PDB_APERTURE_VID_MEM           0
#define NV_PFB_PRI_MMU_INVALIDATE_PDB_ADDR                    31:4
#define NV_PFB_PRI_MMU_INVALIDATE                         0x100cbc
#define NV_PFB_PRI_MMU_INVALIDATE_ALL_VA                       0:0
#define NV_PFB_PRI_MMU_INVALIDATE_ALL_PDB                      1:1
#define NV_PFB_PRI_MMU_INVALIDATE_TRIGGER                    31:31
#define NV_PFB_PRI_MMU_DEBUG_CTRL                         0x100cc4
#define NV_PFB_PRI_MMU_DEBUG_CTRL_DEBUG                      16:16
#define NV_PFB_PRI_MMU_DEBUG_WR                           0x100cc8
#define NV_PFB_PRI_MMU_DEBUG_WR_APERTURE                       1:0
#define NV_PFB_PRI_MMU_DEBUG_WR_APERTURE_VID_MEM                 0
#define NV_PFB_PRI_MMU_DEBUG_WR_VOL                            2:2
#define NV_PFB_PRI_MMU_DEBUG_WR_ADDR                          31:4
#define NV_PFB_PRI_MMU_DEBUG_WR_ADDR_ALIGNMENT                  12
#define NV_PFB_PRI_MMU_DEBUG_RD                           0x100ccc
#define NV_PFB_PRI_MMU_DEBUG_RD_APERTURE                       1:0
#define NV_PFB_PRI_MMU_DEBUG_RD_APERTURE_VID_MEM                 0
#define NV_PFB_PRI_MMU_DEBUG_RD_VOL                            2:2
#define NV_PFB_PRI_MMU_DEBUG_RD_ADDR                          31:4
#define NV_PFB_PRI_MMU_DEBUG_RD_ADDR_ALIGNMENT                  12
#define NV_PFB_PRI_MMU_VPR_INFO                           0x100cd0
#define NV_PFB_PRI_MMU_VPR_INFO_INDEX                          1:0
#define NV_PFB_PRI_MMU_VPR_INFO_INDEX_ADDR_LO                    0
#define NV_PFB_PRI_MMU_VPR_INFO_INDEX_ADDR_HI                    1
#define NV_PFB_PRI_MMU_VPR_INFO_INDEX_CYA_LO                     2
#define NV_PFB_PRI_MMU_VPR_INFO_INDEX_CYA_HI                     3
#define NV_PFB_PRI_MMU_VPR_INFO_FETCH                          2:2

#endif /* __nv_gk20a_fb_hwref_h__ */
