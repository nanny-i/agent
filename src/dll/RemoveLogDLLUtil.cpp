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

// RemoveLogDLLUtil.cpp: implementation of the CRemoveLogDLLUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "com_struct.h"
#include "RemoveLogDLLUtil.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRemoveLogDLLUtil*	t_RemoveLogDLLUtil = NULL;
//----------------------------------------------------------------------------------

CRemoveLogDLLUtil::CRemoveLogDLLUtil()
{
	m_hDLL = NULL;

	f_RemoveFileByDT 		= NULL;
    f_RemoveFileByLastDay	= NULL;
}
//----------------------------------------------------------------------------------

CRemoveLogDLLUtil::~CRemoveLogDLLUtil()
{

}
//----------------------------------------------------------------------------------

INT32		CRemoveLogDLLUtil::LoadLibraryExt(LPCTSTR lpDLLPath)
{
	if((m_hDLL = LoadLibrary(lpDLLPath)) == NULL)	return -1;
	
	if((f_RemoveFileByDT = (RemoveFileByDTType)GetProcAddress(m_hDLL, "RemoveFileByDT")) == NULL)	return -11;
    if((f_RemoveFileByLastDay = (RemoveFileByLastDayType)GetProcAddress(m_hDLL, "RemoveFileByLastDay")) == NULL)	return -12;
	return 0;
}
//----------------------------------------------------------------------------------

void		CRemoveLogDLLUtil::RemoveFileByDT(LPCTSTR lpFindPath, UINT32 nChkType, UINT32 nDay)
{
	if(f_RemoveFileByDT == NULL)	return;

	f_RemoveFileByDT(lpFindPath, nChkType, nDay);
	return;
}
//----------------------------------------------------------------------------------   

void		CRemoveLogDLLUtil::RemoveFileByLastDay(LPCTSTR lpFindPath, UINT32 nChkType, UINT32 nDay)
{
	if(f_RemoveFileByLastDay == NULL)	return;

	f_RemoveFileByLastDay(lpFindPath, nChkType, nDay);
	return;
}
//----------------------------------------------------------------------------------
