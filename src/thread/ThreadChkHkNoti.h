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

#if !defined(AFX_THREAD_CHK_HOOK_NOTI_H__83ABD8B0_065D_4303_A05E_165A4583F052__INCLUDED_)
#define AFX_THREAD_CHK_HOOK_NOTI_H__83ABD8B0_065D_4303_A05E_165A4583F052__INCLUDED_

// ThreadChkHkNoti.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CThreadChkHkNoti thread

#define EWX_LOGOFF          0
#define EWX_SHUTDOWN        0x00000001
#define EWX_REBOOT          0x00000002
#define EWX_FORCE           0x00000004
#define EWX_POWEROFF        0x00000008


class CThreadChkHkNoti : public CThreadBase
{
public:
	CThreadChkHkNoti();           // protected constructor used by dynamic creation
	virtual ~CThreadChkHkNoti();

private:
	CMemoryFile		m_tMemFileExitWin;
	CMutexExt		m_tMemMutex;

public:

	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();

public:
	INT32		InitMemFile_ExitWin(INT32 nMode = 1);
	INT32		SetMemFile_ExitWin(String strFilePath, String strFileName, INT32 nFileOp = 0);
	INT32		SetMemFile_ExitWinProgress(UINT32 nSchTotal, UINT32 nSchEnd, UINT32 nFindTotal, UINT32 nFindEnd);

public:
	INT32		ChkMemFileList();
// Implementation
protected:
	INT32		RunLockProcess();

};

extern	CThreadChkHkNoti*	t_ThreadChkHkNoti;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THREAD_CHK_HOOK_NOTI_H__83ABD8B0_065D_4303_A05E_165A4583F052__INCLUDED_)
