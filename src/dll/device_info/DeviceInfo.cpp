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

// ResInfo.cpp : Defines the entry point for the DLL application.

#include "stdafx.h"
#include "com_struct.h"
#include "DeviceInfo.h"
#include "DeviceInfoUtil.h"

//-----------------------------------------------------------------------------
INT32	InitDevInfo(PVOID* lpObject)
{
	INT32 nRtn = 0;
	try
	{
		CDeviceInfoUtil* tDVIUtil = new CDeviceInfoUtil();
		if(!tDVIUtil)
			return -1;
		*lpObject = (PVOID)tDVIUtil;
	}
	catch(...)
	{
		nRtn = -1001;
	}
	return nRtn;
}
//----------------------------------------------------------------------------
INT32	FreeDevInfo(PVOID lpObject)
{
	INT32 nRtn = 0;
	try
	{
		if(!lpObject)
			return -100;

		CDeviceInfoUtil* tDVIUtil = (CDeviceInfoUtil*)lpObject;
		delete tDVIUtil;
	}
	catch (...)
	{
		nRtn = -1001;
	}
	return nRtn;
}
//----------------------------------------------------------------------------
INT32 ASIDVI_EnumDeviceInfoList(PVOID lpObject, PVOID lParam, CallBack_DeviceInfo fnCallback)
{
	INT32 nRtn = 0;
	try
	{
		if(!lpObject)	return -100;
		CDeviceInfoUtil* tDVIUtil = (CDeviceInfoUtil*)lpObject;
		tDVIUtil->GetDeviceInfoList(lParam, fnCallback);
	}
	catch (...)
	{
		nRtn = -1001;
	}
	return nRtn;
}
//----------------------------------------------------------------------------- 
INT32	ASIDVI_StateChange(PVOID lpObject, LPCTSTR pszDeviceInstanceID, DWORD nEnableFlag)
{	
	INT32 nRtn = 0;
	try
	{
		if(!lpObject)	return -100;
		CDeviceInfoUtil* tDVIUtil = (CDeviceInfoUtil*)lpObject;
		tDVIUtil->StateChange(pszDeviceInstanceID, nEnableFlag);
	}
	catch (...)
	{
		nRtn = -1001;
	}
	return nRtn;
}
//-----------------------------------------------------------------------------
INT32	ASIDVI_GetDeviceStatus(PVOID lpObject, LPCTSTR pszDeviceInstanceID)
{
	INT32 nRtn = 0;
	try
	{
		if(!lpObject)	return -100;
		CDeviceInfoUtil* tDVIUtil = (CDeviceInfoUtil*)lpObject;
		tDVIUtil->GetDeviceStatus(pszDeviceInstanceID);
	}
	catch (...)
	{
		nRtn = -1001;
	}
	return nRtn;
}
//-----------------------------------------------------------------------------
INT32	ASIDVI_RemoveDevice(PVOID lpObject, LPCTSTR pszDeviceInstanceID)
{
	INT32 nRtn = 0;
	try
	{
		if(!lpObject)	return -100;
		CDeviceInfoUtil* tDVIUtil = (CDeviceInfoUtil*)lpObject;
		tDVIUtil->RemoveDevice(pszDeviceInstanceID);
	}
	catch (...)
	{
		nRtn = -1001;
	}
	return nRtn;
}
//----------------------------------------------------------------------
INT32	ASIDVI_IsExistDevice(PVOID lpObject, LPCTSTR pszDeviceInstanceID)
{
	INT32 nRtn = 0;
	try
	{
		if(!lpObject)	return -100;
		CDeviceInfoUtil* tDVIUtil = (CDeviceInfoUtil*)lpObject;
		tDVIUtil->IsExistDevice(pszDeviceInstanceID);
	}
	catch (...)
	{
		nRtn = -1001;
	}
	return nRtn;
}
//----------------------------------------------------------------------
