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

// PowerUtil.cpp: implementation of the CPowerUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "com_struct.h"
#include "PowerUtil.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------

CPowerUtil*	t_PowerUtil = NULL;

//--------------------------------------------------------------------
CPowerUtil::CPowerUtil()
{

}
//--------------------------------------------------------------------

CPowerUtil::~CPowerUtil()
{

}
//--------------------------------------------------------------------

BOOL CPowerUtil::GrabPrivilege (LPCTSTR lpctPrivName) 
{ 
	BOOL bRetVal = FALSE; 
	return bRetVal; 
}
//--------------------------------------------------------------------

BOOL CPowerUtil::SystemShutDown()
{
	return FALSE;
}
//--------------------------------------------------------------------

BOOL CPowerUtil::RestartSystem()
{
	return FALSE;	
}
//---------------------------------------------------------------------------

BOOL	CPowerUtil::SetSystemPower(UINT32 nFlag, DWORD dwReason)
{
	return FALSE;
}
//---------------------------------------------------------------------------

void	CPowerUtil::ChangeDisplayInfo(INT32 nX, INT32 nY, INT32 nQuality)
{
}
//---------------------------------------------------------------------------

void	CPowerUtil::MonitorPowerOff(HWND hWnd)
{
	return;
}
//---------------------------------------------------------------------------

void	CPowerUtil::MonitorPowerOn(HWND hWnd)
{
	return;
}
//---------------------------------------------------------------------------


