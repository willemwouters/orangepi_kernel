/*************************************************************************/ /*!
@Title          Test Chip Framework PDP register definitions	
@Copyright      Copyright (c) Imagination Technologies Ltd. All Rights Reserved
@Description    Autogenerated C -- do not edit
                Generated from: tcf_rgbpdp_regs.def 
@License        Dual MIT/GPLv2

The contents of this file are subject to the MIT license as set out below.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

Alternatively, the contents of this file may be used under the terms of
the GNU General Public License Version 2 ("GPL") in which case the provisions
of GPL are applicable instead of those above.

If you wish to allow use of your version of this file only under the terms of
GPL, and not to allow others to use your version of this file under the terms
of the MIT license, indicate your decision by deleting the provisions above
and replace them with the notice and other provisions required by GPL as set
out in the file called "GPL-COPYING" included in this distribution. If you do
not delete the provisions above, a recipient may use your version of this file
under the terms of either the MIT license or GPL.

This License is also included in this distribution in the file called
"MIT-COPYING".

EXCEPT AS OTHERWISE STATED IN A NEGOTIATED AGREEMENT: (A) THE SOFTWARE IS
PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
PURPOSE AND NONINFRINGEMENT; AND (B) IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/ /**************************************************************************/

#if !defined(_TCF_RGBPDP_REGS_H_)
#define _TCF_RGBPDP_REGS_H_

/*
	Register PVR_TCF_RGBPDP_STR1SURF
*/
#define TCF_RGBPDP_PVR_TCF_RGBPDP_STR1SURF  0x0000
#define STR1HEIGHT_MASK                     0x000007FFU
#define STR1HEIGHT_SHIFT                    0
#define STR1HEIGHT_SIGNED                   0

#define STR1WIDTH_MASK                      0x003FF800U
#define STR1WIDTH_SHIFT                     11
#define STR1WIDTH_SIGNED                    0

#define STR1PIXFMT_MASK                     0x0F000000U
#define STR1PIXFMT_SHIFT                    24
#define STR1PIXFMT_SIGNED                   0

/*
	Register PVR_TCF_RGBPDP_STR1ADDRCTRL
*/
#define TCF_RGBPDP_PVR_TCF_RGBPDP_STR1ADDRCTRL 0x0004
#define STR1BASE_MASK                       0x03FFFFFFU
#define STR1BASE_SHIFT                      0
#define STR1BASE_SIGNED                     0

#define STR1INTFIELD_MASK                   0x40000000U
#define STR1INTFIELD_SHIFT                  30
#define STR1INTFIELD_SIGNED                 0

#define STR1STREN_MASK                      0x80000000U
#define STR1STREN_SHIFT                     31
#define STR1STREN_SIGNED                    0

/*
	Register PVR_PDP_STR1POSN
*/
#define TCF_RGBPDP_PVR_PDP_STR1POSN         0x0008
#define STR1STRIDE_MASK                     0x000003FFU
#define STR1STRIDE_SHIFT                    0
#define STR1STRIDE_SIGNED                   0

/*
	Register PVR_TCF_RGBPDP_MEMCTRL
*/
#define TCF_RGBPDP_PVR_TCF_RGBPDP_MEMCTRL   0x000C
#define MEMREFRESH_MASK                     0xC0000000U
#define MEMREFRESH_SHIFT                    30
#define MEMREFRESH_SIGNED                   0

/*
	Register PVR_TCF_RGBPDP_STRCTRL
*/
#define TCF_RGBPDP_PVR_TCF_RGBPDP_STRCTRL   0x0010
#define BURSTLEN_GFX_MASK                   0x000000FFU
#define BURSTLEN_GFX_SHIFT                  0
#define BURSTLEN_GFX_SIGNED                 0

#define THRESHOLD_GFX_MASK                  0x0000FF00U
#define THRESHOLD_GFX_SHIFT                 8
#define THRESHOLD_GFX_SIGNED                0

/*
	Register PVR_TCF_RGBPDP_SYNCCTRL
*/
#define TCF_RGBPDP_PVR_TCF_RGBPDP_SYNCCTRL  0x0014
#define HSDIS_MASK                          0x00000001U
#define HSDIS_SHIFT                         0
#define HSDIS_SIGNED                        0

#define HSPOL_MASK                          0x00000002U
#define HSPOL_SHIFT                         1
#define HSPOL_SIGNED                        0

#define VSDIS_MASK                          0x00000004U
#define VSDIS_SHIFT                         2
#define VSDIS_SIGNED                        0

#define VSPOL_MASK                          0x00000008U
#define VSPOL_SHIFT                         3
#define VSPOL_SIGNED                        0

#define BLNKDIS_MASK                        0x00000010U
#define BLNKDIS_SHIFT                       4
#define BLNKDIS_SIGNED                      0

#define BLNKPOL_MASK                        0x00000020U
#define BLNKPOL_SHIFT                       5
#define BLNKPOL_SIGNED                      0

#define HS_SLAVE_MASK                       0x00000040U
#define HS_SLAVE_SHIFT                      6
#define HS_SLAVE_SIGNED                     0

#define VS_SLAVE_MASK                       0x00000080U
#define VS_SLAVE_SHIFT                      7
#define VS_SLAVE_SIGNED                     0

#define INTERLACE_MASK                      0x00000100U
#define INTERLACE_SHIFT                     8
#define INTERLACE_SIGNED                    0

#define FIELDPOL_MASK                       0x00000200U
#define FIELDPOL_SHIFT                      9
#define FIELDPOL_SIGNED                     0

#define CLKPOL_MASK                         0x00000800U
#define CLKPOL_SHIFT                        11
#define CLKPOL_SIGNED                       0

#define CSYNC_EN_MASK                       0x00001000U
#define CSYNC_EN_SHIFT                      12
#define CSYNC_EN_SIGNED                     0

#define FIELD_EN_MASK                       0x00002000U
#define FIELD_EN_SHIFT                      13
#define FIELD_EN_SIGNED                     0

#define UPDWAIT_MASK                        0x000F0000U
#define UPDWAIT_SHIFT                       16
#define UPDWAIT_SIGNED                      0

#define UPDCTRL_MASK                        0x01000000U
#define UPDCTRL_SHIFT                       24
#define UPDCTRL_SIGNED                      0

#define UPDINTCTRL_MASK                     0x02000000U
#define UPDINTCTRL_SHIFT                    25
#define UPDINTCTRL_SIGNED                   0

#define UPDSYNCTRL_MASK                     0x04000000U
#define UPDSYNCTRL_SHIFT                    26
#define UPDSYNCTRL_SIGNED                   0

#define POWERDN_MASK                        0x10000000U
#define POWERDN_SHIFT                       28
#define POWERDN_SIGNED                      0

#define DISP_RST_MASK                       0x20000000U
#define DISP_RST_SHIFT                      29
#define DISP_RST_SIGNED                     0

#define SYNCACTIVE_MASK                     0x80000000U
#define SYNCACTIVE_SHIFT                    31
#define SYNCACTIVE_SIGNED                   0

/*
	Register PVR_TCF_RGBPDP_BORDCOL
*/
#define TCF_RGBPDP_PVR_TCF_RGBPDP_BORDCOL   0x0018
#define BORDCOL_MASK                        0x00FFFFFFU
#define BORDCOL_SHIFT                       0
#define BORDCOL_SIGNED                      0

/*
	Register PVR_TCF_RGBPDP_UPDCTRL
*/
#define TCF_RGBPDP_PVR_TCF_RGBPDP_UPDCTRL   0x001C
#define UPDFIELD_MASK                       0x00000001U
#define UPDFIELD_SHIFT                      0
#define UPDFIELD_SIGNED                     0

/*
	Register PVR_TCF_RGBPDP_HSYNC1
*/
#define TCF_RGBPDP_PVR_TCF_RGBPDP_HSYNC1    0x0020
#define HT_MASK                             0x00000FFFU
#define HT_SHIFT                            0
#define HT_SIGNED                           0

#define HBPS_MASK                           0x0FFF0000U
#define HBPS_SHIFT                          16
#define HBPS_SIGNED                         0

/*
	Register PVR_TCF_RGBPDP_HSYNC2
*/
#define TCF_RGBPDP_PVR_TCF_RGBPDP_HSYNC2    0x0024
#define HLBS_MASK                           0x00000FFFU
#define HLBS_SHIFT                          0
#define HLBS_SIGNED                         0

#define HAS_MASK                            0x0FFF0000U
#define HAS_SHIFT                           16
#define HAS_SIGNED                          0

/*
	Register PVR_TCF_RGBPDP_HSYNC3
*/
#define TCF_RGBPDP_PVR_TCF_RGBPDP_HSYNC3    0x0028
#define HRBS_MASK                           0x00000FFFU
#define HRBS_SHIFT                          0
#define HRBS_SIGNED                         0

#define HFPS_MASK                           0x0FFF0000U
#define HFPS_SHIFT                          16
#define HFPS_SIGNED                         0

/*
	Register PVR_TCF_RGBPDP_VSYNC1
*/
#define TCF_RGBPDP_PVR_TCF_RGBPDP_VSYNC1    0x002C
#define VT_MASK                             0x00000FFFU
#define VT_SHIFT                            0
#define VT_SIGNED                           0

#define VBPS_MASK                           0x0FFF0000U
#define VBPS_SHIFT                          16
#define VBPS_SIGNED                         0

/*
	Register PVR_TCF_RGBPDP_VSYNC2
*/
#define TCF_RGBPDP_PVR_TCF_RGBPDP_VSYNC2    0x0030
#define VTBS_MASK                           0x00000FFFU
#define VTBS_SHIFT                          0
#define VTBS_SIGNED                         0

#define VAS_MASK                            0x0FFF0000U
#define VAS_SHIFT                           16
#define VAS_SIGNED                          0

/*
	Register PVR_TCF_RGBPDP_VSYNC3
*/
#define TCF_RGBPDP_PVR_TCF_RGBPDP_VSYNC3    0x0034
#define VBBS_MASK                           0x00000FFFU
#define VBBS_SHIFT                          0
#define VBBS_SIGNED                         0

#define VFPS_MASK                           0x0FFF0000U
#define VFPS_SHIFT                          16
#define VFPS_SIGNED                         0

/*
	Register PVR_TCF_RGBPDP_HDECTRL
*/
#define TCF_RGBPDP_PVR_TCF_RGBPDP_HDECTRL   0x0038
#define HDEF_MASK                           0x00000FFFU
#define HDEF_SHIFT                          0
#define HDEF_SIGNED                         0

#define HDES_MASK                           0x0FFF0000U
#define HDES_SHIFT                          16
#define HDES_SIGNED                         0

/*
	Register PVR_TCF_RGBPDP_VDECTRL
*/
#define TCF_RGBPDP_PVR_TCF_RGBPDP_VDECTRL   0x003C
#define VDEF_MASK                           0x00000FFFU
#define VDEF_SHIFT                          0
#define VDEF_SIGNED                         0

#define VDES_MASK                           0x0FFF0000U
#define VDES_SHIFT                          16
#define VDES_SIGNED                         0

/*
	Register PVR_TCF_RGBPDP_VEVENT
*/
#define TCF_RGBPDP_PVR_TCF_RGBPDP_VEVENT    0x0040
#define VFETCH_MASK                         0x00000FFFU
#define VFETCH_SHIFT                        0
#define VFETCH_SIGNED                       0

#define VEVENT_MASK                         0x0FFF0000U
#define VEVENT_SHIFT                        16
#define VEVENT_SIGNED                       0

/*
	Register PVR_TCF_RGBPDP_OPMASK
*/
#define TCF_RGBPDP_PVR_TCF_RGBPDP_OPMASK    0x0044
#define MASKR_MASK                          0x000000FFU
#define MASKR_SHIFT                         0
#define MASKR_SIGNED                        0

#define MASKG_MASK                          0x0000FF00U
#define MASKG_SHIFT                         8
#define MASKG_SIGNED                        0

#define MASKB_MASK                          0x00FF0000U
#define MASKB_SHIFT                         16
#define MASKB_SIGNED                        0

#define BLANKLEVEL_MASK                     0x40000000U
#define BLANKLEVEL_SHIFT                    30
#define BLANKLEVEL_SIGNED                   0

#define MASKLEVEL_MASK                      0x80000000U
#define MASKLEVEL_SHIFT                     31
#define MASKLEVEL_SIGNED                    0

/*
	Register PVR_TCF_RGBPDP_INTSTAT
*/
#define TCF_RGBPDP_PVR_TCF_RGBPDP_INTSTAT   0x0048
#define INTS_HBLNK0_MASK                    0x00000001U
#define INTS_HBLNK0_SHIFT                   0
#define INTS_HBLNK0_SIGNED                  0

#define INTS_HBLNK1_MASK                    0x00000002U
#define INTS_HBLNK1_SHIFT                   1
#define INTS_HBLNK1_SIGNED                  0

#define INTS_VBLNK0_MASK                    0x00000004U
#define INTS_VBLNK0_SHIFT                   2
#define INTS_VBLNK0_SIGNED                  0

#define INTS_VBLNK1_MASK                    0x00000008U
#define INTS_VBLNK1_SHIFT                   3
#define INTS_VBLNK1_SIGNED                  0

#define INTS_STR1URUN_MASK                  0x00000010U
#define INTS_STR1URUN_SHIFT                 4
#define INTS_STR1URUN_SIGNED                0

#define INTS_STR1ORUN_MASK                  0x00000020U
#define INTS_STR1ORUN_SHIFT                 5
#define INTS_STR1ORUN_SIGNED                0

#define INTS_DISPURUN_MASK                  0x00000040U
#define INTS_DISPURUN_SHIFT                 6
#define INTS_DISPURUN_SIGNED                0

/*
	Register PVR_TCF_RGBPDP_INTENAB
*/
#define TCF_RGBPDP_PVR_TCF_RGBPDP_INTENAB   0x004C
#define INTEN_HBLNK0_MASK                   0x00000001U
#define INTEN_HBLNK0_SHIFT                  0
#define INTEN_HBLNK0_SIGNED                 0

#define INTEN_HBLNK1_MASK                   0x00000002U
#define INTEN_HBLNK1_SHIFT                  1
#define INTEN_HBLNK1_SIGNED                 0

#define INTEN_VBLNK0_MASK                   0x00000004U
#define INTEN_VBLNK0_SHIFT                  2
#define INTEN_VBLNK0_SIGNED                 0

#define INTEN_VBLNK1_MASK                   0x00000008U
#define INTEN_VBLNK1_SHIFT                  3
#define INTEN_VBLNK1_SIGNED                 0

#define INTEN_STR1URUN_MASK                 0x00000010U
#define INTEN_STR1URUN_SHIFT                4
#define INTEN_STR1URUN_SIGNED               0

#define INTEN_STR1ORUN_MASK                 0x00000020U
#define INTEN_STR1ORUN_SHIFT                5
#define INTEN_STR1ORUN_SIGNED               0

#define INTEN_DISPURUN_MASK                 0x00000040U
#define INTEN_DISPURUN_SHIFT                6
#define INTEN_DISPURUN_SIGNED               0

/*
	Register PVR_TCF_RGBPDP_INTCLEAR
*/
#define TCF_RGBPDP_PVR_TCF_RGBPDP_INTCLEAR  0x0050
#define INTCLR_HBLNK0_MASK                  0x00000001U
#define INTCLR_HBLNK0_SHIFT                 0
#define INTCLR_HBLNK0_SIGNED                0

#define INTCLR_HBLNK1_MASK                  0x00000002U
#define INTCLR_HBLNK1_SHIFT                 1
#define INTCLR_HBLNK1_SIGNED                0

#define INTCLR_VBLNK0_MASK                  0x00000004U
#define INTCLR_VBLNK0_SHIFT                 2
#define INTCLR_VBLNK0_SIGNED                0

#define INTCLR_VBLNK1_MASK                  0x00000008U
#define INTCLR_VBLNK1_SHIFT                 3
#define INTCLR_VBLNK1_SIGNED                0

#define INTCLR_STR1URUN_MASK                0x00000010U
#define INTCLR_STR1URUN_SHIFT               4
#define INTCLR_STR1URUN_SIGNED              0

#define INTCLR_STR1ORUN_MASK                0x00000020U
#define INTCLR_STR1ORUN_SHIFT               5
#define INTCLR_STR1ORUN_SIGNED              0

#define INTCLR_DISPURUN_MASK                0x00000040U
#define INTCLR_DISPURUN_SHIFT               6
#define INTCLR_DISPURUN_SIGNED              0

/*
	Register PVR_TCF_RGBPDP_INTCTRL
*/
#define TCF_RGBPDP_PVR_TCF_RGBPDP_INTCTRL   0x0054
#define HBLNK_LINENO_MASK                   0x00000FFFU
#define HBLNK_LINENO_SHIFT                  0
#define HBLNK_LINENO_SIGNED                 0

#define HBLNK_LINE_MASK                     0x00010000U
#define HBLNK_LINE_SHIFT                    16
#define HBLNK_LINE_SIGNED                   0

/*
	Register PVR_TCF_RGBPDP_SIGNAT
*/
#define TCF_RGBPDP_PVR_TCF_RGBPDP_SIGNAT    0x0058
#define SIGNATURE_MASK                      0xFFFFFFFFU
#define SIGNATURE_SHIFT                     0
#define SIGNATURE_SIGNED                    0

/*
	Register PVR_TCF_RGBPDP_LINESTAT
*/
#define TCF_RGBPDP_PVR_TCF_RGBPDP_LINESTAT  0x005C
#define LINENO_MASK                         0x00000FFFU
#define LINENO_SHIFT                        0
#define LINENO_SIGNED                       0

/*
	Register PVR_TCF_RGBPDP_DBGCTRL
*/
#define TCF_RGBPDP_PVR_TCF_RGBPDP_DBGCTRL   0x0060
#define DBG_ENAB_MASK                       0x00000001U
#define DBG_ENAB_SHIFT                      0
#define DBG_ENAB_SIGNED                     0

#define DBG_READ_MASK                       0x00000002U
#define DBG_READ_SHIFT                      1
#define DBG_READ_SIGNED                     0

/*
	Register PVR_TCF_RGBPDP_DBGDATA
*/
#define TCF_RGBPDP_PVR_TCF_RGBPDP_DBGDATA   0x0064
#define DBG_DATA_MASK                       0x00FFFFFFU
#define DBG_DATA_SHIFT                      0
#define DBG_DATA_SIGNED                     0

/*
	Register PVR_TCF_RGBPDP_DBGSIDE
*/
#define TCF_RGBPDP_PVR_TCF_RGBPDP_DBGSIDE   0x0068
#define DBG_SIDE_MASK                       0x00000007U
#define DBG_SIDE_SHIFT                      0
#define DBG_SIDE_SIGNED                     0

#define DBG_VAL_MASK                        0x00000008U
#define DBG_VAL_SHIFT                       3
#define DBG_VAL_SIGNED                      0

/*
	Register PVR_TCF_RGBPDP_REGLD_STAT
*/
#define TCF_RGBPDP_PVR_TCF_RGBPDP_REGLD_STAT 0x0070
#define REGLD_ADDROUT_MASK                  0x00FFFFFFU
#define REGLD_ADDROUT_SHIFT                 0
#define REGLD_ADDROUT_SIGNED                0

#define REGLD_ADDREN_MASK                   0x80000000U
#define REGLD_ADDREN_SHIFT                  31
#define REGLD_ADDREN_SIGNED                 0

/*
	Register PVR_TCF_RGBPDP_REGLD_CTRL
*/
#define TCF_RGBPDP_PVR_TCF_RGBPDP_REGLD_CTRL 0x0074
#define REGLD_ADDRIN_MASK                   0x00FFFFFFU
#define REGLD_ADDRIN_SHIFT                  0
#define REGLD_ADDRIN_SIGNED                 0

#define REGLD_VAL_MASK                      0x01000000U
#define REGLD_VAL_SHIFT                     24
#define REGLD_VAL_SIGNED                    0

#define REGLD_ADDRLEN_MASK                  0xFE000000U
#define REGLD_ADDRLEN_SHIFT                 25
#define REGLD_ADDRLEN_SIGNED                0

/*
	Register PVR_TCF_RGBPDP_CORE_ID
*/
#define TCF_RGBPDP_PVR_TCF_RGBPDP_CORE_ID   0x0078
#define CONFIG_ID_MASK                      0x0000FFFFU
#define CONFIG_ID_SHIFT                     0
#define CONFIG_ID_SIGNED                    0

#define CORE_ID_MASK                        0x00FF0000U
#define CORE_ID_SHIFT                       16
#define CORE_ID_SIGNED                      0

#define GROUP_ID_MASK                       0xFF000000U
#define GROUP_ID_SHIFT                      24
#define GROUP_ID_SIGNED                     0

/*
	Register PVR_TCF_RGBPDP_CORE_REV
*/
#define TCF_RGBPDP_PVR_TCF_RGBPDP_CORE_REV  0x007C
#define MAINT_REV_MASK                      0x000000FFU
#define MAINT_REV_SHIFT                     0
#define MAINT_REV_SIGNED                    0

#define MINOR_REV_MASK                      0x0000FF00U
#define MINOR_REV_SHIFT                     8
#define MINOR_REV_SIGNED                    0

#define MAJOR_REV_MASK                      0x00FF0000U
#define MAJOR_REV_SHIFT                     16
#define MAJOR_REV_SIGNED                    0

#endif /* !defined(_TCF_RGBPDP_REGS_H_) */

/*****************************************************************************
 End of file (tcf_rgbpdp_regs.h)
*****************************************************************************/
