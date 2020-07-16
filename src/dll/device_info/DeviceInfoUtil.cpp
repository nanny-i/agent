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

#include "stdafx.h"
#include "com_struct.h"
#include "DeviceInfoUtil.h"
#include "DevInfo.h"

CDeviceInfoUtil::CDeviceInfoUtil()
{

}
CDeviceInfoUtil::~CDeviceInfoUtil()
{
}

//----------------------------------------------------------------------
INT32	CDeviceInfoUtil::GetDeviceInfoList(LPVOID lParam, CallBack_DeviceInfo fnCallback)
{
	CDevInfo tDevInfo;
	tDevInfo.LoadStorageController();

	TMapDeviceItemClassItor begin, end;
	begin = tDevInfo.m_tDeviceItemClassMap.begin();		end = tDevInfo.m_tDeviceItemClassMap.end();
	for(begin; begin != end; begin++)
	{
		PDEVICE_ITEM_CLASS pDIC = &(*begin).second;
		TListDeviceInfoItor c_begin, c_end;
		c_begin = pDIC->tDeviceItemInfoList.begin();	c_end = pDIC->tDeviceItemInfoList.end();
		for(c_begin; c_begin != c_end; c_begin++)
		{
			if(fnCallback)	
				fnCallback(lParam, *c_begin);
		}
	}
	return 0;
}
//----------------------------------------------------------------------
INT32	CDeviceInfoUtil::StateChange(LPCTSTR pszDeviceInstanceID, DWORD nEnableFlag)
{
	CDevInfo tDevInfo;
	return tDevInfo.StateChange(pszDeviceInstanceID, nEnableFlag);
}
//----------------------------------------------------------------------
INT32	CDeviceInfoUtil::GetDeviceStatus(LPCTSTR pszDeviceInstanceID)
{
	CDevInfo tDevInfo;
	return tDevInfo.GetDeviceStatus(pszDeviceInstanceID);
}
//----------------------------------------------------------------------
INT32	CDeviceInfoUtil::RemoveDevice(LPCTSTR pszDeviceInstanceID)
{
	CDevInfo tDevInfo;
	return tDevInfo.RemoveDevice(pszDeviceInstanceID);
}
//----------------------------------------------------------------------
INT32	CDeviceInfoUtil::IsExistDevice(LPCTSTR pszDeviceInstanceID)
{
	CDevInfo tDevInfo;
	return tDevInfo.IsExistDevice(pszDeviceInstanceID);
}