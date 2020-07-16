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


#ifndef _DEVICE_INFO_H__

#define _DEVICE_INFO_H__

extern "C" {

INT32 InitDevInfo(PVOID* lpObject);
INT32 FreeDevInfo(PVOID lpObject);
INT32 ASIDVI_EnumDeviceInfoList(PVOID lpObject, LPVOID lParam, CallBack_DeviceInfo fnCallback);
INT32 ASIDVI_StateChange(PVOID lpObject, LPCTSTR pszDeviceInstanceID, DWORD nEnableFlag);
INT32 ASIDVI_GetDeviceStatus(PVOID lpObject, LPCTSTR pszDeviceInstanceID);
INT32 ASIDVI_RemoveDevice(PVOID lpObject, LPCTSTR pszDeviceInstanceID);
INT32 ASIDVI_IsExistDevice(PVOID lpObject, LPCTSTR pszDeviceInstanceID);

}

#endif /*_DEVICE_INFO_H__*/

