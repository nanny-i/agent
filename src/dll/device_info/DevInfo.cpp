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

// DevInfo.cpp: implementation of the CDevInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "com_struct.h"
#include "DevInfo.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDevInfo::CDevInfo()
{

}

CDevInfo::~CDevInfo()
{

}

//-----------------------------------------------------------------------------------

INT32 CDevInfo::LoadStorageController()
{
	EnumAddDevices();
	return 0;
}
//-----------------------------------------------------------------------------------

INT32 CDevInfo::EnumAddDevices()
{
	return 0;
}
//-----------------------------------------------------------------------------------

INT32 CDevInfo::StateChange(LPCTSTR pszDeviceInstanceID, DWORD nEnableFlag)
{
	return 0;
}
//-----------------------------------------------------------------------------------

INT32 CDevInfo::GetDeviceStatus(LPCTSTR pszDeviceInstanceID)
{
	return 0;
}
//-----------------------------------------------------------------------------------

INT32	CDevInfo::RemoveDevice(LPCTSTR pszDeviceInstanceID)
{
	return 0;
}
//-----------------------------------------------------------------------------------

INT32	CDevInfo::IsExistDevice(LPCTSTR pszDeviceInstanceID)
{
	return 0;
}
//-----------------------------------------------------------------------------------
