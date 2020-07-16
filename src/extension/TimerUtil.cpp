/*
 * Copyright (C) 2020-2025 ASHINi corp. 
 * 
 * This library is free software; you can redistribute it and/or 
 * modify it under the terms of the GNU Lesser General Public 
 * License as published by the Free Software Foundation; either 
 * version 2.1 of the License, or (at your option) any later version. 
 * 
 * This library is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
 * Lesser General Public License for more details. 
 * 
 * You should have received a copy of the GNU Lesser General Public 
 * License along with this library; if not, write to the Free Software 
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA 
 * 
 */

//---------------------------------------------------------------------------
#include "stdafx.h"
#include "com_struct.h"
#include "TimerUtil.h"

//---------------------------------------------------------------------------

CTimerUtil*		t_TimerUtil = NULL;

//---------------------------------------------------------------------------


CTimerUtil::CTimerUtil()
{
	m_nMaxID	= 1;
	m_nNotifyID	= 0;
	m_pNotifyWnd = NULL;
}
//---------------------------------------------------------------------------

CTimerUtil::~CTimerUtil()
{
}
//---------------------------------------------------------------------------

INT32	CTimerUtil::SetNotifyWnd(HWND pNotifyWnd, UINT32 dwNotifyID)
{
	m_pNotifyWnd = pNotifyWnd;
	m_nNotifyID	= dwNotifyID;
	return 0;
}
//---------------------------------------------------------------------------

UINT32	CTimerUtil::GetNextTimerID()
{
	UINT32 nRtn = 0;

	TListTimerInfoItor begin, end;
    begin = tTimerInfoList.begin();	end = tTimerInfoList.end();
    for(begin; begin != end; begin++)
    {
    	if( begin->nID < nRtn)	continue;

        nRtn = begin->nID;
    }

    return ++nRtn;
}
//---------------------------------------------------------------------------

UINT32	CTimerUtil::IsExistTimerID(UINT32 nTimerID)
{
	TListTimerInfoItor begin, end;
    begin = tTimerInfoList.begin();	end = tTimerInfoList.end();
    for(begin; begin != end; begin++)
    {
    	if( begin->nID != nTimerID)	continue;

	    return 1;
    }
	
	return 0;
}
//---------------------------------------------------------------------------

UINT32	CTimerUtil::IsEnabledTimer(UINT32 nTimerID)
{
	PTIMER_INFO pti = FindTimer(nTimerID);
	if(!pti)	return 0;

	return pti->nEnabled;
}
//---------------------------------------------------------------------------

PTIMER_INFO 	CTimerUtil::FindTimer(UINT32 nTimerID)
{
 	TListTimerInfoItor begin, end;
    begin = tTimerInfoList.begin();	end = tTimerInfoList.end();
    for(begin; begin != end; begin++)
    {
    	if( begin->nID != nTimerID)	continue;

		return &(*begin);
    }

	return NULL;
}
//---------------------------------------------------------------------------

UINT32	CTimerUtil::AddTimer(UINT32 nTimerID, UINT32 nInterval, OnTimerType OnTimer, UINT32 nMsgType, UINT32 nEnabled, INT32 nLimited, INT32 nExcuteNow)
{
    TIMER_INFO timer_info;
	memset(&timer_info, 0, sizeof(TIMER_INFO));
	t_Mutex.Lock();
	if(IsExistTimerID(nTimerID))
    	nTimerID = GetNextTimerID();

    timer_info.nID			= nTimerID;
    timer_info.nInterval    = nInterval;
    timer_info.OnTimer		= OnTimer;
    timer_info.nEnabled		= nEnabled;
	timer_info.nMessageType	= nMsgType;
	timer_info.nLimited		= nLimited;
	timer_info.nLastChkTime	= GetCurrentDateTimeInt();
	timer_info.nExcuteNow   = nExcuteNow;

    tTimerInfoList.push_back(timer_info);
	t_Mutex.UnLock();

    return nTimerID;
}
//---------------------------------------------------------------------------

INT32	CTimerUtil::EditTimer(UINT32 nTimerID, UINT32 nInterval, OnTimerType OnTimer, UINT32 nMsgType, UINT32 nEnabled, INT32 nChkMutex, INT32 nLimited, INT32 nExcuteNow)
{
	if(nChkMutex)	t_Mutex.Lock();
	PTIMER_INFO ptimer_info = FindTimer(nTimerID);
    if(ptimer_info == 0)
	{
		//WriteLogN("not find timer id : [%d]", nTimerID);
		if(nChkMutex)	t_Mutex.UnLock();
		return -1;
	}

    if(nInterval)	ptimer_info->nInterval	= nInterval;
    if(OnTimer)		ptimer_info->OnTimer	= OnTimer;
    ptimer_info->nEnabled		= nEnabled;
	ptimer_info->nMessageType	= nMsgType;
	ptimer_info->nLimited		= nLimited;
	if(nEnabled)	ptimer_info->nLastChkTime	= GetCurrentDateTimeInt();

	ptimer_info->nExcuteNow		= nExcuteNow;

	if(nChkMutex)	t_Mutex.UnLock();
    return 0;
}
//---------------------------------------------------------------------------

INT32	CTimerUtil::EnableTimer(UINT32 nTimerID, UINT32 nResetTime)
{
	PTIMER_INFO ptimer_info = FindTimer(nTimerID);
    if(ptimer_info == 0)
	{
		return -1;
	}

	if(nResetTime)
	{
		ptimer_info->nLastChkTime	= GetCurrentDateTimeInt();
	}

	ptimer_info->nEnabled	= 1;	
	return 0;
}
//---------------------------------------------------------------------------

INT32	CTimerUtil::DisableTimer(UINT32 nTimerID, UINT32 nResetTime)
{
	PTIMER_INFO ptimer_info = FindTimer(nTimerID);
    if(ptimer_info == 0)
	{
		return -1;
	}

	if(nResetTime)
	{
		ptimer_info->nLastChkTime	= GetCurrentDateTimeInt();
	}

	ptimer_info->nEnabled	= 0;	
	return 0;
}
//---------------------------------------------------------------------------

INT32	CTimerUtil::DelTimer(UINT32 nTimerID)
{
	t_Mutex.Lock();
	TListTimerInfoItor begin, end;
    begin = tTimerInfoList.begin();	end = tTimerInfoList.end();
    for(begin; begin != end; begin++)
    {
    	if( begin->nID != nTimerID)	continue;

        tTimerInfoList.erase(begin);
        break;
    }
	t_Mutex.UnLock();
    return 1;
}
//---------------------------------------------------------------------------

void	CTimerUtil::ChkTimer()
{
	CMainDlg* pMainDlg = (CMainDlg *)m_pNotifyWnd;
	UINT32 nChkTimerID = 0;
	UINT32 nNowTime = 0;
	TListTimerInfoItor begin, end;

	t_Mutex.Lock();
	begin = tTimerInfoList.begin();	end = tTimerInfoList.end();
	for(begin; begin != end; begin++)
	{
		if( begin->nEnabled == 0)
			continue;

		nNowTime = GetCurrentDateTimeInt();

		if(!begin->nExcuteNow && nNowTime - begin->nLastChkTime <= begin->nInterval)
			continue;
		nChkTimerID = begin->nID;
		
		if(begin->OnTimer)
			begin->OnTimer();
		else
		{
			if(pMainDlg != NULL)
				pMainDlg->PostMessage(m_nNotifyID, nChkTimerID, 0);

			if(begin->nLimited > 0)
			{
				begin->nLimited--;				
			}
			if(begin->nLimited == 0)
				begin->nEnabled = 0;
		}
		begin->nExcuteNow	= 0;
		begin->nLastChkTime = nNowTime;
	}
	t_Mutex.UnLock();
}


