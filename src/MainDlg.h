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

#ifndef _MAIN_DLG_H__

#define _MAIN_DLG_H__


class CMainDlg
{
public:
	CMainDlg();
	virtual ~CMainDlg();
	int			Run();
	BOOL		GetMessage(MSG* pMsg);
	BOOL		PostMessage(UINT dwMsgID, WPARAM wParam, LPARAM lParam);
	void		CloseMain();

public:
    void		WM_AgentInitialize(WPARAM wParam, LPARAM lParam);
    void		WM_MainThreadTerminated(WPARAM wParam, LPARAM lParam);
    void		WM_AgentAutoDestory(WPARAM wParam, LPARAM lParam);
	DWORD		OnThreadTimer(WPARAM wParam, LPARAM lParam);
	INT32 		OnKernelFileLog(UINT32 nLogType, PPKT_DATA pPktData);
	DWORD		OnThreadLog(UINT32 nLogType, PDB_SITE_FILE pDsfSrc);
	DWORD 		OnThreadEnd(UINT32 nEndType, PDB_PO_FE_PTN_LO pDPFPO);
	DWORD		OnThreadWorkEnd(UINT32 nEndWorkType, PMEM_FIND_ORDER_INFO pMFOI);
	DWORD		OnThreadPoFaClearEnd(UINT32 nEndWorkType, PMEM_FIND_ORDER_INFO pMFOI);
	DWORD		OnThreadPoFaClearProgress(UINT32 nEndWorkType, PMEM_FIND_ORDER_INFO pMFOI);
	DWORD		OnSockEvtCltLgn(PPKT_DATA pPktData);
	DWORD		OnSockEvtCltMgr(PPKT_DATA pPktData);
	DWORD		OnSockEvtCltUdt(PPKT_DATA pPktData);
	DWORD		OnSockEvtSvrLink(PPKT_DATA pPktData);
	DWORD		OnFileDown(WPARAM wParam, LPARAM lParam);

private:
    INT32 			m_nCloseMode;
	DWORD			m_dwThreadID;
	TMapIDListStr	m_tDBSyncMap;
	CSemExt 		m_SemExt;

private:
	INT32			StartModule();
	void			StopModule();

private:
	INT32			StopThread_Common(CThreadBase* tThreadObject, UINT32 nWaitTime = 5/*sec*/);
	INT32			SyncDatabase();
	VOID			DelFileAfterBoot();

private:
	INT32			PreCreateSubClass();
	INT32			CreateLoadLibrary();
	INT32			CreateSubClass();
	INT32			DeleteSubClass();

private:
	INT32			InitLoadLibrary();
	INT32			InitSubClass();
	INT32			InitTimerID();
	INT32			InitRunEnv();

private:
	INT32			CheckIntegrity();

private:
	INT32			StartSubClass();
	INT32			StopSubClass();

private:
	INT32			PreStartOperation();
	INT32			PreStartTimer();
	INT32			StartOperation();
};

extern CMainDlg* t_MainDlg;

#endif /*_MAIN_DLG_H__*/


