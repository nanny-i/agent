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

//
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "com_struct.h"
#include "DownloadFileDLLUtil.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CASIFDLDLLUtil*	t_ASIFDLDLLUtil		= NULL;

CASIFDLDLLUtil::CASIFDLDLLUtil()
{
	m_hDLL = NULL;
}
//--------------------------------------------------------------------

CASIFDLDLLUtil::~CASIFDLDLLUtil()
{
	FreeLibraryExt();
}
//--------------------------------------------------------------------

INT32 CASIFDLDLLUtil::LoadLibraryExt(LPCTSTR lpDLLName)
{
	if(m_hDLL)
		return 0;

	if( (m_hDLL = LoadLibrary(lpDLLName)) == NULL)
	{	
		return -1;
	}
	return 0;
}
//--------------------------------------------------------------------

INT32		CASIFDLDLLUtil::FreeLibraryExt()
{
	if(m_hDLL)
	{
		FreeLibrary(m_hDLL);
		m_hDLL = NULL;
	}
	return 0;
}
//--------------------------------------------------------------------


INT32		CASIFDLDLLUtil::AddDLInfo(PASI_FDL_INFO pafi)
{
	if(!m_hDLL)		return -1;

	ASIFDL_AddDLInfoType fASIFDL_AddDLInfo = (ASIFDL_AddDLInfoType)GetProcAddress(m_hDLL, "ASIFDL_AddDLInfo");
	if(!fASIFDL_AddDLInfo)		return -2;

	return fASIFDL_AddDLInfo(pafi);
}
//----------------------------------------------------------------------------------


INT32		CASIFDLDLLUtil::FindDLInfo(UINT32 nID, PASI_FDL_INFO pafi)
{
	if(!m_hDLL)		return -1;

	ASIFDL_FindDLInfoType fASIFDL_FindDLInfo = (ASIFDL_FindDLInfoType)GetProcAddress(m_hDLL, "ASIFDL_FindDLInfo");
	if(!fASIFDL_FindDLInfo)		return -2;

	return fASIFDL_FindDLInfo(nID, pafi);
}
//----------------------------------------------------------------------------------

INT32		CASIFDLDLLUtil::DelDLInfo(UINT32 nType, UINT32 nID)
{
	if(!m_hDLL)		return -1;

	ASIFDL_DelDLInfoType fASIFDL_DelDLInfo = (ASIFDL_DelDLInfoType)GetProcAddress(m_hDLL, "ASIFDL_DelDLInfo");
	if(!fASIFDL_DelDLInfo)		return -2;

	return fASIFDL_DelDLInfo(nType, nID);
}
//----------------------------------------------------------------------------------

INT32		CASIFDLDLLUtil::RunDL()
{
	if(!m_hDLL)		return -1;

	ASIFDL_RunDLType fASIFDL_RunDL = (ASIFDL_RunDLType)GetProcAddress(m_hDLL, "ASIFDL_RunDL");
	if(!fASIFDL_RunDL)		return -2;

	return fASIFDL_RunDL();
}
//----------------------------------------------------------------------------------

INT32		CASIFDLDLLUtil::IsRunDL()
{
	if(!m_hDLL)		return -1;

	ASIFDL_IsRunDLType fASIFDL_IsRunDL = (ASIFDL_IsRunDLType)GetProcAddress(m_hDLL, "ASIFDL_IsRunDL");
	if(!fASIFDL_IsRunDL)		return -2;
	
	return fASIFDL_IsRunDL();
}
//----------------------------------------------------------------------------------

INT32		CASIFDLDLLUtil::StopDL()
{
	if(!m_hDLL)		return -1;

	ASIFDL_StopDLType fASIFDL_StopDL = (ASIFDL_StopDLType)GetProcAddress(m_hDLL, "ASIFDL_StopDL");
	if(!fASIFDL_StopDL)		return -2;

	return fASIFDL_StopDL();
}
//----------------------------------------------------------------------------------

INT32		CASIFDLDLLUtil::SetDLInit(PASI_FDL_INIT pafi)
{
	if(!m_hDLL)		return -1;

	ASIFDL_SetDLInitType fASIFDL_SetDLInit = (ASIFDL_SetDLInitType)GetProcAddress(m_hDLL, "ASIFDL_SetDLInit");
	if(!fASIFDL_SetDLInit)		return -2;
	
	return fASIFDL_SetDLInit(pafi);
}
//----------------------------------------------------------------------------------

INT32		CASIFDLDLLUtil::SetDLSvrType(UINT32 nDLSvrType)
{
	if(!m_hDLL)		return -1;

	ASIFDL_SetDLSvrTypeType fASIFDL_SetDLSvrType = (ASIFDL_SetDLSvrTypeType)GetProcAddress(m_hDLL, "ASIFDL_SetDLSvrType");
	if(!fASIFDL_SetDLSvrType)		return -2;
	
	return fASIFDL_SetDLSvrType(nDLSvrType);
}
//----------------------------------------------------------------------------------

INT32		CASIFDLDLLUtil::SetDLSvrInfo(UINT32 nItemType, LPCTSTR szSvrInfo)
{
	if(!m_hDLL)		return -1;

	ASIFDL_SetDLSvrInfoType fASIFDL_SetDLSvrInfo = (ASIFDL_SetDLSvrInfoType)GetProcAddress(m_hDLL, "ASIFDL_SetDLSvrInfo");
	if(!fASIFDL_SetDLSvrInfo)		return -2;
	
	return fASIFDL_SetDLSvrInfo(nItemType, szSvrInfo);
}
//----------------------------------------------------------------------------------

