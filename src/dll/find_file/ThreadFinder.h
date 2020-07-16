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

#if !defined(AFX_THREAD_FINDER_H__83ABD8B0_065D_4303_A05E_165A4583F052__INCLUDED_)
#define AFX_THREAD_FINDER_H__83ABD8B0_065D_4303_A05E_165A4583F052__INCLUDED_

/////////////////////////////////////////////////////////////////////////////
// CThreadFinder thread

class CThreadFinder : public CThreadBase
{
public:
	CThreadFinder();           // protected constructor used by dynamic creation
	virtual ~CThreadFinder();

public:

// Operations
public:

	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
protected:
	INT32		ChkWorkFindDir();
	INT32		ChkWorkFindFile();

};

#endif // !defined(AFX_THREAD_FINDER_H__83ABD8B0_065D_4303_A05E_165A4583F052__INCLUDED_)
