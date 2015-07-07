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
#ifndef __nv_gf108_fb_hwref_h__
#define __nv_gf108_fb_hwref_h__

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

#endif /* __nv_gf108_fb_hwref_h__ */
