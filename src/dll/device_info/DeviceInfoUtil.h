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

#if !defined(AFX_DEVICEINFOUTIL_H__A00D015F_9061_11D2_8D3B_FC17F33B2809__INCLUDED_)
#define AFX_DEVICEINFOUTIL_H__A00D015F_9061_11D2_8D3B_FC17F33B2809__INCLUDED_

class CDeviceInfoUtil  
{
	// Construction
public:
	CDeviceInfoUtil();
public:
	INT32	GetDeviceInfoList(LPVOID lParam, CallBack_DeviceInfo fnCallback);
	INT32	StateChange(LPCTSTR pszDeviceInstanceID, DWORD nEnableFlag);
	INT32	GetDeviceStatus(LPCTSTR pszDeviceInstanceID);
	INT32	RemoveDevice(LPCTSTR pszDeviceInstanceID);
	INT32	IsExistDevice(LPCTSTR pszDeviceInstanceID);

public:
	virtual ~CDeviceInfoUtil();
};

#endif // !defined(AFX_DEVICEINFOUTIL_H__A00D015F_9061_11D2_8D3B_FC17F33B2809__INCLUDED_)