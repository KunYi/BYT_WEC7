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
//
/*++
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Module Name:  
    SDWorki.cpp
Abstract:
    SD Async Work Item  Implementation.

Notes: 
--*/
#include <windows.h>
#include <types.h>

#include <sdhcd.h>

#include "sdbus.hpp"
#include "sdslot.hpp"
#include "sdworki.hpp"

///////////////////////////////////////////////////////////////////////////////
//  CSDWorkItem - constructor 
//  Input: 
//  Output: 
//  Notes:  
//      
///////////////////////////////////////////////////////////////////////////////
CSDWorkItem::CSDWorkItem(DWORD dwMaxItem)
:   CMiniThread( 0, TRUE),
    m_dwMaxOfSlotEvent(max(dwMaxItem,MIN_WORK_ITEM))
{
    CeSetThreadAffinity(GetThreadHandle(), 1);
    m_psdSlotEvent = new SD_SLOT_EVENT [m_dwMaxOfSlotEvent];
    m_hWakeupEvent = CreateEvent(NULL,FALSE,TRUE,NULL);
    m_hEmptySlotSem = CreateSemaphore(NULL, m_dwMaxOfSlotEvent-1, m_dwMaxOfSlotEvent-1,NULL);
    m_dwReadIndex = m_dwWriteIndex = 0;
    m_bInitialized = FALSE;
    m_bSuspended = FALSE;
}

///////////////////////////////////////////////////////////////////////////////
//  ~CSDWorkItem - destructor
//  Input:  
//  Output: 
//  Notes:  
//      
///////////////////////////////////////////////////////////////////////////////
CSDWorkItem::~CSDWorkItem() 
{

    Lock();
    m_bTerminated = TRUE;
    ThreadStart();
    Stop();
    if (m_hEmptySlotSem!=NULL)
        CloseHandle(m_hEmptySlotSem);
    if (m_hWakeupEvent!=NULL)
        CloseHandle(m_hWakeupEvent);
    delete m_psdSlotEvent;
    Unlock();
}

BOOL CSDWorkItem::Init(DWORD  dwCeThreadPriority)
{
    BOOL bRet = FALSE;
    Lock();
    if  (
        m_psdSlotEvent  != NULL && 
        m_hWakeupEvent  != NULL && 
        m_hEmptySlotSem != NULL
        )
    {
        //If not initialized already initialize it
        if( m_bInitialized == FALSE)
        {
            m_dwCeThreadPriority = dwCeThreadPriority;
            CeSetPriority( (int)m_dwCeThreadPriority );
            ThreadStart();
            m_bInitialized = TRUE;
        }
        bRet = TRUE;
    }
    Unlock();
    return bRet;
    
}

BOOL CSDWorkItem::Stop()
{
    BOOL bRet = FALSE;
    Lock();
    if  (
        m_bInitialized  == TRUE &&
        m_psdSlotEvent  != NULL && 
        m_hWakeupEvent  != NULL && 
        m_hEmptySlotSem != NULL
        ) 
    {
        VERIFY(ReleaseSemaphore(m_hEmptySlotSem,1,NULL));
        m_dwReadIndex = m_dwWriteIndex = 0;
        SetEvent(m_hWakeupEvent);
        ThreadStop();
        bRet = TRUE;
    };
    m_bSuspended = bRet;
    ASSERT(FALSE);
    Unlock();
    return bRet;
    
}

BOOL CSDWorkItem::ReStart()
{
    BOOL bRet = FALSE;
    Lock();
    if  (
        m_bInitialized  == TRUE &&
        m_bSuspended    == TRUE &&
        m_psdSlotEvent  != NULL && 
        m_hWakeupEvent  != NULL && 
        m_hEmptySlotSem != NULL
        )
    {
        VERIFY(ReleaseSemaphore(m_hEmptySlotSem,1,NULL));
        m_dwReadIndex = m_dwWriteIndex = 0;
        SetEvent(m_hWakeupEvent);
        bRet = Init(m_dwCeThreadPriority);
        m_bSuspended = (bRet == TRUE) ? FALSE : TRUE;
    };
    ASSERT(FALSE);
    Unlock();
    return bRet;
    
}

///////////////////////////////////////////////////////////////////////////////
//  PostMessage - post a message
//  Input:  pMessage - message to post
//  Output: 
//  Return:
//  Notes:  
//      
///////////////////////////////////////////////////////////////////////////////
BOOL CSDWorkItem::PostEvent(SD_SLOT_EVENT sdEvent, DWORD dwWaitTick)
{
    PREFAST_ASSERT(m_psdSlotEvent!=NULL);
    BOOL fRet = FALSE;
    if (::WaitForSingleObject( m_hEmptySlotSem, dwWaitTick ) == WAIT_OBJECT_0 ) {
        Lock();
        if (!IsFull()) {
            m_psdSlotEvent[m_dwWriteIndex] = sdEvent;
            m_dwWriteIndex = IncIndex(m_dwWriteIndex);
            SetEvent(m_hWakeupEvent);
            fRet = TRUE;
        }
        else
            ASSERT(FALSE);
        Unlock();
    }
    return fRet;
}

DWORD  CSDWorkItem::ThreadRun()
{
    while (!m_bTerminated) {
        PREFAST_ASSERT(m_psdSlotEvent!=NULL);
        if (!IsEmpty()) {
            // We don't need take lock since only this thread modify the Read Index.
            SD_SLOT_EVENT sdEvent = m_psdSlotEvent [m_dwReadIndex];
            m_dwReadIndex = IncIndex(m_dwReadIndex);
            VERIFY(ReleaseSemaphore(m_hEmptySlotSem,1,NULL));
            SlotStatusChangeProcessing(sdEvent);
        }
        else
            ::WaitForSingleObject( m_hWakeupEvent, INFINITE );
    }
    return FALSE;
}


