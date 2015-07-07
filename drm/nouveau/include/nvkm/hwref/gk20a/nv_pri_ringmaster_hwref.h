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
#ifndef __nv_gk20a_pri_ringmaster_hwref_h__
#define __nv_gk20a_pri_ringmaster_hwref_h__

#define NV_PPRIV_MASTER_RING_COMMAND                      0x12004c
#define NV_PPRIV_MASTER_RING_COMMAND_CMD                       5:0
#define NV_PPRIV_MASTER_RING_COMMAND_CMD_NO_CMD                  0
#define NV_PPRIV_MASTER_RING_COMMAND_CMD_START_RING              1
#define NV_PPRIV_MASTER_RING_COMMAND_CMD_ACK_INTERRUPT           2
#define NV_PPRIV_MASTER_RING_COMMAND_CMD_ENUMERATE_STATIONS      3
#define NV_PPRIV_MASTER_RING_COMMAND_CMD_ENUMERATE_STATIONS_BC_GRP         8:6
#define NV_PPRIV_MASTER_RING_COMMAND_CMD_ENUMERATE_STATIONS_BC_GRP_ALL       0
#define NV_PPRIV_MASTER_RING_COMMAND_DATA                 0x120048
#define NV_PPRIV_MASTER_RING_START_RESULTS                0x120050
#define NV_PPRIV_MASTER_RING_START_RESULTS_CONNECTIVITY        0:0
#define NV_PPRIV_MASTER_RING_START_RESULTS_CONNECTIVITY_PASS     1
#define NV_PPRIV_MASTER_RING_INTERRUPT_STATUS0            0x120058
#define NV_PPRIV_MASTER_RING_INTERRUPT_STATUS1            0x12005c
#define NV_PPRIV_MASTER_RING_GLOBAL_CTL                   0x120060
#define NV_PPRIV_MASTER_RING_GLOBAL_CTL_RING_RESET             0:0
#define NV_PPRIV_MASTER_RING_GLOBAL_CTL_RING_RESET_ASSERTED      1
#define NV_PPRIV_MASTER_RING_GLOBAL_CTL_RING_RESET_DEASSERTED    0
#define NV_PPRIV_MASTER_RING_ENUMERATE_RESULTS_FBP        0x120074
#define NV_PPRIV_MASTER_RING_ENUMERATE_RESULTS_FBP_COUNT       4:0
#define NV_PPRIV_MASTER_RING_ENUMERATE_RESULTS_GPC        0x120078
#define NV_PPRIV_MASTER_RING_ENUMERATE_RESULTS_GPC_COUNT       4:0

#endif /* __nv_gk20a_pri_ringmaster_hwref_h__ */
