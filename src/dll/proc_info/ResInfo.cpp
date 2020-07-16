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
#include "ResInfo.h"
#include "NetworkInfo.h"
#include "ResInfoUtil.h"


//-----------------------------------------------------------------------------
INT32	InitProcInfo(PVOID* lpObject)
{
	CResInfoUtil* tResInfoUtil = NULL;
	if(lpObject == NULL)
		return -1;
	
	tResInfoUtil = new CResInfoUtil();
	if(tResInfoUtil == NULL)
		return -2;
	*lpObject = (PVOID)tResInfoUtil;
	return 0;
}
//----------------------------------------------------------------------------
INT32	FreeProcInfo(PVOID lpObject)
{
	CResInfoUtil* tResInfoUtil = NULL; 
	if(lpObject == NULL)
		return -1;

	tResInfoUtil = (CResInfoUtil*)lpObject;
	delete tResInfoUtil;
	return 0;
}
//----------------------------------------------------------------------------
INT32 GetProcessResInfo(PVOID lpObject, LPVOID lParam, CallBack_ProcessInfo fnCallback)
{
	CResInfoUtil* tResInfoUtil = NULL; 
	if(lpObject == NULL)
		return -1;
	
	tResInfoUtil = (CResInfoUtil*)lpObject;
	tResInfoUtil->GetProcessResInfo(lParam, fnCallback);
	return 0;
}
//----------------------------------------------------------------------------- 
INT32	GetNetWorkResInfo(PVOID lpObject, LPVOID lParam, CallBack_NetWorkInfo fnCallback)
{	
	CResInfoUtil* tResInfoUtil = NULL; 
	if(lpObject == NULL)
		return -1;
	tResInfoUtil = (CResInfoUtil*)lpObject;
	tResInfoUtil->GetNetWorkResInfo(lParam, fnCallback);
	return 0;
}
