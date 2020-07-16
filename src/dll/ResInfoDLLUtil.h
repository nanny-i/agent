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

#ifndef _RES_INFO_DLL_UTIL_H__
#define _RES_INFO_DLL_UTIL_H__

//--------------------------------------------------------------------------------------------------
typedef INT32	(*GetCpuUsageTotalType)(UINT32* nUsage);
typedef INT32	(*GetMemoryInfoType)(UINT64* nTotalPhySize, UINT64* nTotalPageSize, UINT64* nAvailPhySize, UINT64* nAvailPageSize);
typedef INT32	(*GetHddInfoType)(UINT64* nTotalHddSize, UINT64* nUsageHddSize, LPCTSTR lpDriveName);
typedef INT32	(*GetTrafficBandWidhtType)(INT32 nItemID, DOUBLE* dBandWidth);
typedef INT32	(*GetTrafficValueType)(INT32 nItemID, DOUBLE* dTrafficValue);
//--------------------------------------------------------------------------------------------------

class CResInfoDLLUtil  
{
private:
	HINSTANCE		m_hDLL;

private:
	GetCpuUsageTotalType		f_GetCpuUsageTotal;
	GetMemoryInfoType			f_GetMemoryInfo;
	GetHddInfoType				f_GetHddInfo;
	GetTrafficBandWidhtType		f_GetTrafficBandWidht;
	GetTrafficValueType			f_GetTrafficValue;

public:
	INT32			LoadLibraryExt(LPCTSTR lpDLLName);

public:
	INT32			GetCpuUsageTotal(UINT32* nUsage);
	INT32			GetMemoryInfo(UINT64* nTotalPhySize, UINT64* nTotalPageSize, UINT64* nAvailPhySize, UINT64* nAvailPageSize);
	INT32			GetHddInfo(UINT64* nTotalHddSize, UINT64* nUsageHddSize, LPCTSTR lpDriveName);
	INT32			GetTrafficBandWidht(INT32 nItemID, DOUBLE* dBandWidth);
	INT32			GetTrafficValue(INT32 nItemID, DOUBLE* dTrafficValue);

public:
	CResInfoDLLUtil();
	virtual ~CResInfoDLLUtil();

};

extern CResInfoDLLUtil*		t_ResInfoDLLUtil;

#endif  /*_RES_INFO_DLL_UTIL_H__*/