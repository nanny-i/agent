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

//---------------------------------------------------------------------------

#include "stdafx.h"
#include "com_struct.h"
#include "ManageDeviceMedia.h"

//---------------------------------------------------------------------------

CManageDeviceMedia*	t_ManageDeviceMedia = NULL;

//---------------------------------------------------------------------------

CManageDeviceMedia::CManageDeviceMedia()
{
	m_hNotifyWnd				= NULL;
	m_uNotifyMessage			= 0;
	m_uRegisterNotifyMessage	= 0;
}
//---------------------------------------------------------------------------

CManageDeviceMedia::~CManageDeviceMedia()
{
	Release();
}
//---------------------------------------------------------------------------

BOOL	CManageDeviceMedia::Init(HWND hNotifyWnd, UINT nNotifyMessage)
{
	return TRUE;
}
//---------------------------------------------------------------------------

INT32 CManageDeviceMedia::Release()
{
	return 0;
}
//---------------------------------------------------------------------------

VOID CManageDeviceMedia::OnMediaChange(WPARAM wParam, LPARAM lParam)
{

}
//---------------------------------------------------------------------------

INT32 CManageDeviceMedia::AttachInstance(LPCTSTR lpszDrv)
{
	if (lpszDrv == NULL || lpszDrv[0] == NULL)
		return -1;

	return 0;
}
//---------------------------------------------------------------------------

INT32 CManageDeviceMedia::DetachInstance(LPCTSTR lpszDrv)
{
	if (lpszDrv == NULL || lpszDrv[0] == NULL)
		return -1;

	return 0;
}
//---------------------------------------------------------------------------

INT32 CManageDeviceMedia::SetPkt(MemToken& SendToken)
{
	TMapStrID	tUsbDrvMap;
	t_ManageSysDrive.GetUSBDriveMap(0, tUsbDrvMap);

	TMapStrIDItor begin, end;
	begin = tUsbDrvMap.begin();	end = tUsbDrvMap.end();

	SendToken.TokenAdd_32(tUsbDrvMap.size());
	for(begin; begin != end; begin++)
	{
		String strPath = begin->first;
		replace_char_in_str((char *)strPath.c_str(), '*', 0);
		SendToken.TokenAdd_String(strPath);
	}

	SendToken.TokenSet_Block();
	return 0;
}