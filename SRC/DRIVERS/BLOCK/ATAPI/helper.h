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

#ifndef _HELPER_H_
#define _HELPER_H_


BOOL AtaGetRegistryValue(HKEY hKey, const TCHAR* szValueName, PDWORD pdwValue);
BOOL AtaGetRegistryString( HKEY hKey, const TCHAR* szValueName, PTSTR *pszValue, DWORD dwSize=0);
BOOL AtaGetRegistryString2( HKEY hKey, PTSTR szValueName, PTSTR *pszValue, DWORD dwSize=0);
BOOL AtaSetRegistryValue(HKEY hKey, const TCHAR* szValueName, DWORD dwValue);
BOOL AtaSetRegistryValue2(HKEY hKey, PTSTR szValueName, DWORD dwValue);
BOOL AtaSetRegistryString( HKEY hKey, const TCHAR* szValueName, PTSTR szValue);
BOOL ATAParseIdString(const BYTE *str, int len, DWORD *pdwOffset,BYTE **ppDest, DWORD *pcBytesLeft);

// This function is used to fetch an IDE/ATA channel's I/O window from its instance key;
BOOL AtaGetRegistryResources(HKEY hDevKey, PDDKWINDOWINFO pdwi);
#ifdef I830M4
BOOL AtaGetRegistryPciInfo(HKEY hDevKey, PDDKPCIINFO ppi);
#endif

// This function translates a bus address in an I/O window to a virtual address
DWORD DoIoTranslation(PDDKWINDOWINFO pdwi, DWORD dwWindowIndex, IN OUT PBOOL pisIOMapped);

// This function translates a bus address to a static physical address usable by giisr.dll
DWORD DoStaticTranslation(PDDKWINDOWINFO pdwi, DWORD dwWindowIndex, IN OUT PBOOL pisIOMapped);


#endif // _HELPER_H_