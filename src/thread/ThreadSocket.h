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

#if !defined(AFX_THREAD_SOCKET_H__83ABD8B0_065D_4303_A05E_165A4583F052__INCLUDED_)
#define AFX_THREAD_SOCKET_H__83ABD8B0_065D_4303_A05E_165A4583F052__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ThreadSocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CThreadSocket thread

class CThreadSocket : public CThreadBase
{
public:
	CThreadSocket();           // protected constructor used by dynamic creation
	virtual ~CThreadSocket();

public:
	CTimerUtil		t_TimerUtil;
	CMutexExt		m_StatusMutex; 
	CSemExt 		m_SemExt;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThreadSocket)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
	//}}AFX_VIRTUAL

// Implementation
protected:
	volatile LONG	m_nCtlLgnStatus;
	volatile LONG	m_nCtlMgrStatus;
	volatile LONG	m_nCtlUdtStatus;
	volatile LONG	m_nSvrLinkStatus;

protected:
	LONG		CheckLogicStatus(UINT32 nType);

public:
	INT32		SetLogicStatus(UINT32 nType, UINT32 nStatus, UINT32 nWaitTime = 10);

private:
	UINT32		m_nChkPktDbgTime;
	String		m_strPktDbgName;
	void		InitPktDbgTime(String strName, PPKT_DATA pkt_data);
	void		FreePktDbgTime(String strName, PPKT_DATA pkt_data);
	UINT32		GetPktDbgTime() {	return m_nChkPktDbgTime;	}


private:
	INT32		Logic_CltLgn(INT32& nTotalPktCnt, INT32 nOncePktNum);
	INT32		Logic_CltMgr(INT32& nTotalPktCnt, INT32 nOncePktNum);
	INT32		Logic_CltUdt(INT32& nTotalPktCnt, INT32 nOncePktNum);
	INT32		Logic_SvrLink(INT32& nTotalPktCnt, INT32 nOncePktNum);
};

extern	CThreadSocket*	t_ThreadSocket;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THREAD_SOCKET_H__83ABD8B0_065D_4303_A05E_165A4583F052__INCLUDED_)
