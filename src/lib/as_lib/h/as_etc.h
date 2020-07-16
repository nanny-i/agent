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


#ifndef _AS_ETC_H__
#define	_AS_ETC_H__


INT32	SetER(INT32 nRtn);
String	GetGUID();
String GetOTPKey();
String GetOTPStr(UINT32 nTimeStamp, String strDefaultKey);
DWORD CoCreateGuid(GUID* pguid);
UINT32	htonl_ext(UINT32 nValue);
UINT16	htonl16_ext(UINT16 nValue);
UINT64	htonl64_ext(UINT64 nValue);
DWORD	GetFileSizeExt(LPCTSTR lpFileName);

PVOID	MallocExt(UINT32 nSize);


extern 	INT32	g_nErrRtn;

#endif /*_AS_ETC_H__*/