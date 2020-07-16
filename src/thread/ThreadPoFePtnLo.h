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

#if !defined(AFX_THREAD_PO_FE_PTN_LO_H__83ABD8B0_065D_4303_A05E_165A4583F052__INCLUDED_)
#define AFX_THREAD_PO_FE_PTN_LO_H__83ABD8B0_065D_4303_A05E_165A4583F052__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ThreadPoFePtnLo.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CThreadPoFePtnLo thread

class CThreadPoFePtnLo : public CThreadBase
{
public:
	CThreadPoFePtnLo();           // protected constructor used by dynamic creation
	virtual ~CThreadPoFePtnLo();

private:
	UINT32			m_nOrderID;
	UINT32			m_nWorkOrderID;
	CASIFFDLLUtil	m_tFFDLLUtil;
//	CASIWEngDLLUtil	m_tWEDLLUtil;
//	CASIFIDLLUtil	m_tFIDLLUtil;
//	CASIHASHDLLUtil	m_tHashDLLUtil;

private:
	TMapWEngWLEx	m_tWEngWLExMap;
	TMapID64		m_tOrderIDMap;
	TListID64		m_tOrderIDList;
	CMutexExt		m_tOrderMutex;

public:
	void			AddWork(UINT64 nOrderID);
	UINT32			IsWork();
	UINT32			NextWork();
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThreadPoFePtnLo)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
	//}}AFX_VIRTUAL

private:
	DB_PO_FE_PTN_LO		m_tCurPolicy;

public:
	INT32		InitEnv();
	INT32		FreeEnv();

	INT32		ChkScanFile();
	INT32		SavePtnFile();
	

// Implementation
protected:

};

extern	CThreadPoFePtnLo*	t_ThreadPoFePtnLo;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THREAD_PO_FE_PTN_LO_H__83ABD8B0_065D_4303_A05E_165A4583F052__INCLUDED_)
