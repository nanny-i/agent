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

#ifndef TimerUtilH
#define TimerUtilH
//---------------------------------------------------------------------------
typedef void (*OnTimerType)();

typedef struct _timer_info
{
	_timer_info()
    {
    	nID				= 0;
    	nInterval		= 1;
        nLastChkTime    = 0;
        nEnabled		= 0;
		nMessageType	= 1;
		nChkDTType		= 0;
		nLimited		= -1;
        OnTimer			= 0;
		nExcuteNow		= 0;
    }
    UINT32			nID;
	UINT32			nInterval;
    UINT32			nLastChkTime;
    UINT32			nEnabled;
	UINT32			nMessageType;
	UINT32			nChkDTType;
	INT32			nLimited;
	OnTimerType		OnTimer;
	UINT32			nExcuteNow;
}TIMER_INFO, *PTIMER_INFO;

typedef list<TIMER_INFO>			TListTimerInfo;
typedef TListTimerInfo::iterator    TListTimerInfoItor;

class CTimerUtil
{
private:
	TListTimerInfo		tTimerInfoList;
    UINT32				m_nMaxID;
	CMutexExt			t_Mutex;
	HWND				m_pNotifyWnd;
	UINT32				m_nNotifyID;

private:
	UINT32			GetNextTimerID();
    PTIMER_INFO 	FindTimer(UINT32 nTimerID);


public:
	UINT32	AddTimer(UINT32 nTimerID, UINT32 nInterval, OnTimerType OnTimer, UINT32 nMsgType = 1, UINT32 nEnabled = 1, INT32 nLimited = -1, INT32 nExcuteNow = 0);
    INT32	EditTimer(UINT32 nTimerID, UINT32 nInterval, OnTimerType OnTimer, UINT32 nMsgType, UINT32 nEnabled, INT32 nChkMutex = 1, INT32 nLimited = -1, INT32 nExcuteNow = 0);
	INT32	EnableTimer(UINT32 nTimerID, UINT32 nResetTime = 1);
	INT32	DisableTimer(UINT32 nTimerID, UINT32 nResetTime = 1);
    INT32	DelTimer(UINT32 nTimerID);
	UINT32	IsExistTimerID(UINT32 nTimerID);
	UINT32	IsEnabledTimer(UINT32 nTimerID);

public:
	INT32	SetNotifyWnd(HWND tNotifyWnd, UINT32 nNotifyID);
	
public:
	void	ChkTimer();    

public:
	CTimerUtil();
    ~CTimerUtil();
};

extern CTimerUtil*	t_TimerUtil;


#endif
