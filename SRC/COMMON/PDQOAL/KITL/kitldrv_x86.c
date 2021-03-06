//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this sample source code is subject to the terms of the Microsoft
// license agreement under which you licensed this sample source code. If
// you did not accept the terms of the license agreement, you are not
// authorized to use this sample source code. For the terms of the license,
// please see the license agreement between you and Microsoft or, if applicable,
// see the LICENSE.RTF on your install media or the root of your tools installation.
// THE SAMPLE SOURCE CODE IS PROVIDED "AS IS", WITH NO WARRANTIES OR INDEMNITIES.
//
// -- Intel Copyright Notice -- 
//  
// @par 
// Copyright (c) 2002-2011 Intel Corporation All Rights Reserved. 
//  
// @par 
// The source code contained or described herein and all documents 
// related to the source code ("Material") are owned by Intel Corporation 
// or its suppliers or licensors.  Title to the Material remains with 
// Intel Corporation or its suppliers and licensors. 
//  
// @par 
// The Material is protected by worldwide copyright and trade secret laws 
// and treaty provisions. No part of the Material may be used, copied, 
// reproduced, modified, published, uploaded, posted, transmitted, 
// distributed, or disclosed in any way except in accordance with the 
// applicable license agreement . 
//  
// @par 
// No license under any patent, copyright, trade secret or other 
// intellectual property right is granted to or conferred upon you by 
// disclosure or delivery of the Materials, either expressly, by 
// implication, inducement, estoppel, except in accordance with the 
// applicable license agreement. 
//  
// @par 
// Unless otherwise agreed by Intel in writing, you may not remove or 
// alter this notice or any other notice embedded in Materials by Intel 
// or Intel's suppliers or licensors in any way. 
//  
// @par 
// For further details, please see the file README.TXT distributed with 
// this software. 
//  
// @par 
// -- End Intel Copyright Notice -- 
//  

#include <windows.h>
#include <x86kitl.h>
#include <oal_ethdrv.h>
#include <halether.h>

#ifdef  ENABLE_KITL_GBE_E1000
#include "e1000kitl.h"
#endif 

#ifdef  ENABLE_KITL_GBE_PCHEG20T
#include "pchgbe.h"
#endif 

static OAL_KITL_ETH_DRIVER DrvNE2k  = OAL_ETHDRV_NE2000;     // NE2000 
static OAL_KITL_ETH_DRIVER DrvRTL   = OAL_ETHDRV_RTL8139;    // RTL8139
static OAL_KITL_ETH_DRIVER DrvDEC21140=OAL_ETHDRV_DEC21140;  // DEC21140

#ifdef  ENABLE_KITL_GBE_E1000
static OAL_KITL_ETH_DRIVER DrvE1000 = OAL_ETHDRV_E1000;      // EEPRO/1000
#endif
#ifdef  ENABLE_KITL_GBE_PCHEG20T
static OAL_KITL_ETH_DRIVER DrvPCH   = OAL_ETHDRV_PCH;        // PCH GbE Driver
#endif

const SUPPORTED_NIC g_NicSupported []=
{
//   VenId   DevId   UpperMAC      Type              Name   Drivers
//  ---------------------------------------------------------------------------------
    {0x0000, 0x0000, 0x004033, EDBG_ADAPTER_NE2000,  "AD", &DrvNE2k  }, /* Addtron */\
    {0x1050, 0x0940, 0x004005, EDBG_ADAPTER_NE2000,  "LS", &DrvNE2k  }, /* LinkSys */\
    {0x1050, 0x0940, 0x002078, EDBG_ADAPTER_NE2000,  "LS", &DrvNE2k  }, /* LinkSys */\
    {0x10EC, 0x8029, 0x00C0F0, EDBG_ADAPTER_NE2000,  "KS", &DrvNE2k  }, /* Kingston */\
    {0x10EC, 0x8129, 0x000000, EDBG_ADAPTER_RTL8139, "RT", &DrvRTL   }, /* RealTek */\
    {0x10EC, 0x8139, 0x00900B, EDBG_ADAPTER_RTL8139, "RT", &DrvRTL   }, /* RealTek  */\
    {0x10EC, 0x8139, 0x00D0C9, EDBG_ADAPTER_RTL8139, "RT", &DrvRTL   }, /* RealTek */\
    {0x10EC, 0x8139, 0x00E04C, EDBG_ADAPTER_RTL8139, "RT", &DrvRTL   }, /* RealTek */\
    {0x1186, 0x1300, 0x0050BA, EDBG_ADAPTER_RTL8139, "DL", &DrvRTL   }, /* D-Link */\
    {0x1011, 0x0009, 0x0003FF, EDBG_ADAPTER_DEC21140,"DC", &DrvDEC21140}, /* DEC */
#ifdef  ENABLE_KITL_GBE_E1000
    {0x8086, 0x1000, 0x001B21, EDBG_ADAPTER_OEM, "IN", &DrvE1000 },     /* EEPRO/1000 */
#endif
#ifdef  ENABLE_KITL_GBE_PCHEG20T
    {0x8086, 0x8802, 0x000000, EDBG_ADAPTER_OEM, "IN", &DrvPCH },       /* PCH GBE*/
#endif

};

const int g_nNumNicSupported = _countof (g_NicSupported);

