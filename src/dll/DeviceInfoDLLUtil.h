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

// ASIDVIDLLUtil.h: interface for the CDEVINFODLLUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ASIRIDLLUTIL_H__BBCD1EB7_1B5F_497A_87D5_BDEC7EBF1C3F__INCLUDED_)
#define AFX_ASIRIDLLUTIL_H__BBCD1EB7_1B5F_497A_87D5_BDEC7EBF1C3F__INCLUDED_


//------------------------------------------------------
#include "com_header_dvi_dll.h"
//------------------------------------------------------


class CDEVINFODLLUtil
{
private:
	HINSTANCE	m_hDLL;
	PVOID		m_lpObject;

public:
	INT32		LoadLibraryExt(LPCTSTR szDLLPath);
	INT32		FreeLibraryExt();

public:
	INT32		Init();
	INT32		Free();

	INT32		GetDeviceInfo(TListDeviceInfo& tDeviceInfoList);


public:
	TListDeviceInfo				m_tDeviceInfoList;

public:
	CDEVINFODLLUtil();
	virtual ~CDEVINFODLLUtil();

};

extern CDEVINFODLLUtil*	t_DevInfoDLLUtil;

#endif // !defined(AFX_ASIRIDLLUTIL_H__BBCD1EB7_1B5F_497A_87D5_BDEC7EBF1C3F__INCLUDED_)
