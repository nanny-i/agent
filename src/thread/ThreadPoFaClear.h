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

#if !defined(AFX_THREAD_PO_FA_CLEAR_H__83ABD8B0_065D_4303_A05E_165A4583F052__INCLUDED_)
#define AFX_THREAD_PO_FA_CLEAR_H__83ABD8B0_065D_4303_A05E_165A4583F052__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ThreadPoFaClear.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CThreadPoFaClear thread

class CThreadPoFaClear : public CThreadBase
{
public:
	CThreadPoFaClear();           // protected constructor used by dynamic creation
	virtual ~CThreadPoFaClear();

private:
	UINT32						m_nOrderID;
	TMapMemFindOrderInfo		m_tOrderIDMap;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThreadPoFaClear)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
	//}}AFX_VIRTUAL

public:
	UINT32		GetNextOrderID()					{	return ++m_nOrderID;			};
	INT32		AddOrderID(PMEM_FIND_ORDER_INFO pMFOI);
	INT32		IsEndWork()							{	return m_nPause;	};
	INT32		ChkScanFileList();
	INT32		ChkScanFile(PMEM_FIND_ORDER_INFO pMFOI);

// Implementation
protected:

};

extern	CThreadPoFaClear*	t_ThreadPoFaClear;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THREAD_PO_FA_CLEAR_H__83ABD8B0_065D_4303_A05E_165A4583F052__INCLUDED_)
