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
#ifndef __nv_gf104_trim_hwref_h__
#define __nv_gf104_trim_hwref_h__

#define NV_PTRIM_SYS_GPCPLL_CFG                           0x137000
#define NV_PTRIM_SYS_GPCPLL_CFG_ENABLE                         0:0
#define NV_PTRIM_SYS_GPCPLL_CFG_IDDQ                           1:1
#define NV_PTRIM_SYS_GPCPLL_CFG_IDDQ_POWER_ON                    0
#define NV_PTRIM_SYS_GPCPLL_CFG_SYNC_MODE                      2:2
#define NV_PTRIM_SYS_GPCPLL_CFG_SYNC_MODE_DISABLE                0
#define NV_PTRIM_SYS_GPCPLL_CFG_SYNC_MODE_ENABLE                 1
#define NV_PTRIM_SYS_GPCPLL_CFG_ENB_LCKDET                     4:4
#define NV_PTRIM_SYS_GPCPLL_CFG_ENB_LCKDET_POWER_ON              0
#define NV_PTRIM_SYS_GPCPLL_CFG_ENB_LCKDET_POWER_OFF             1
#define NV_PTRIM_SYS_GPCPLL_CFG_PLL_LOCK                     17:17
#define NV_PTRIM_SYS_GPCPLL_COEFF                         0x137004
#define NV_PTRIM_SYS_GPCPLL_COEFF_MDIV                         7:0
#define NV_PTRIM_SYS_GPCPLL_COEFF_NDIV                        15:8
#define NV_PTRIM_SYS_GPCPLL_COEFF_PLDIV                      21:16
#define NV_PTRIM_SYS_SEL_VCO                              0x137100
#define NV_PTRIM_SYS_SEL_VCO_GPC2CLK_OUT                       0:0
#define NV_PTRIM_SYS_SEL_VCO_GPC2CLK_OUT_INIT                    0
#define NV_PTRIM_SYS_SEL_VCO_GPC2CLK_OUT_BYPASS                  0
#define NV_PTRIM_SYS_SEL_VCO_GPC2CLK_OUT_VCO                     1
#define NV_PTRIM_SYS_GPC2CLK_OUT                          0x137250
#define NV_PTRIM_SYS_GPC2CLK_OUT_BYPDIV                        5:0
#define NV_PTRIM_SYS_GPC2CLK_OUT_BYPDIV_BY31                  0x3c
#define NV_PTRIM_SYS_GPC2CLK_OUT_VCODIV                       13:8
#define NV_PTRIM_SYS_GPC2CLK_OUT_VCODIV_BY1                      0
#define NV_PTRIM_SYS_GPC2CLK_OUT_SDIV14                      31:31
#define NV_PTRIM_SYS_GPC2CLK_OUT_SDIV14_INDIV4_MODE              1
#define NV_PTRIM_SYS_BYPASSCTRL_SYS                       0x137340
#define NV_PTRIM_SYS_BYPASSCTRL_SYS_GPCPLL                     0:0
#define NV_PTRIM_SYS_BYPASSCTRL_SYS_GPCPLL_BYPASSCLK             1
#define NV_PTRIM_SYS_BYPASSCTRL_SYS_GPCPLL_VCO                   0
#define NV_PTRIM_GPC_CLK_CNTR_NCGPCCLK_CFG(i) (0x134124+(i)*0x200)
#define NV_PTRIM_GPC_CLK_CNTR_NCGPCCLK_CFG_NOOFIPCLKS         13:0
#define NV_PTRIM_GPC_CLK_CNTR_NCGPCCLK_CFG_WRITE_EN          16:16
#define NV_PTRIM_GPC_CLK_CNTR_NCGPCCLK_CFG_WRITE_EN_ASSERTED     1
#define NV_PTRIM_GPC_CLK_CNTR_NCGPCCLK_CFG_ENABLE            20:20
#define NV_PTRIM_GPC_CLK_CNTR_NCGPCCLK_CFG_ENABLE_ASSERTED       1
#define NV_PTRIM_GPC_CLK_CNTR_NCGPCCLK_CFG_RESET             24:24
#define NV_PTRIM_GPC_CLK_CNTR_NCGPCCLK_CFG_RESET_ASSERTED        1
#define NV_PTRIM_GPC_CLK_CNTR_NCGPCCLK_CNT(i) (0x134128+(i)*0x200)
#define NV_PTRIM_GPC_CLK_CNTR_NCGPCCLK_CNT_VALUE              19:0

#endif /* __nv_gf104_trim_hwref_h__ */
