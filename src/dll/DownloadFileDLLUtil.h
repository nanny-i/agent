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

// ASIFDLDLLUtil.h: interface for the CASIFDLDLLUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ASIFDLDLLUTIL_H__BBCD1EB7_1B5F_497A_87D5_BDEC7EBF1C3F__INCLUDED_)
#define AFX_ASIFDLDLLUTIL_H__BBCD1EB7_1B5F_497A_87D5_BDEC7EBF1C3F__INCLUDED_


//------------------------------------------------------
#include "com_header_file_download_dll.h"
//------------------------------------------------------


class CASIFDLDLLUtil  
{
private:
	HINSTANCE m_hDLL;
	
public:
	INT32		LoadLibraryExt(LPCTSTR lpDLLPath);
	INT32		FreeLibraryExt();

public:
	INT32		AddDLInfo(PASI_FDL_INFO pafi);
	INT32		FindDLInfo(UINT32 nID, PASI_FDL_INFO pafi);
	INT32		DelDLInfo(UINT32 nType, UINT32 nID);

	INT32		RunDL();
	INT32		IsRunDL();
	INT32		StopDL();

	INT32		SetDLInit(PASI_FDL_INIT pafi);
	INT32		SetDLSvrType(UINT32 nDLSvrType);
	INT32		SetDLSvrInfo(UINT32 nItemType, LPCTSTR szSvrInfo);

public:
	CASIFDLDLLUtil();
	virtual ~CASIFDLDLLUtil();

};

extern CASIFDLDLLUtil*	t_ASIFDLDLLUtil;

#endif // !defined(AFX_ASIFDLDLLUTIL_H__BBCD1EB7_1B5F_497A_87D5_BDEC7EBF1C3F__INCLUDED_)
