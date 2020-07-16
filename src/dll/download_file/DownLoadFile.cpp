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
#include "DownLoadFile.h"

CDownLoadUtil	tDownloadUtil;

INT32 ASIFDL_AddDLInfo(PASI_FDL_INFO pafi)
{
	return tDownloadUtil.AddDownLoadInfo(pafi);
}
//--------------------------------------------------------------

INT32 ASIFDL_FindDLInfo(UINT32 nID, PASI_FDL_INFO pafi)
{
	return tDownloadUtil.FindDownLoadInfo(nID, pafi);
}
//--------------------------------------------------------------

INT32	ASIFDL_DelDLInfo(UINT32 nItemType, UINT32 nItemID)
{
	return tDownloadUtil.DelDownLoadInfo(nItemType, nItemID);
}
//--------------------------------------------------------------

INT32 ASIFDL_RunDL()
{
	return tDownloadUtil.RunDownload();
}
//--------------------------------------------------------------

INT32 ASIFDL_IsRunDL()
{
	return tDownloadUtil.IsRunDownload();
}
//--------------------------------------------------------------

INT32 ASIFDL_StopDL()
{
	return tDownloadUtil.StopDownload();
}
//--------------------------------------------------------------

INT32 ASIFDL_SetDLInit(PASI_FDL_INIT pafdli)
{
	return tDownloadUtil.SetDownloadInit(pafdli);
}
//--------------------------------------------------------------

INT32 ASIFDL_SetDLSvrType(UINT32 nDLSvrType)
{
	return tDownloadUtil.SetDLSvrType(nDLSvrType);	
}
//--------------------------------------------------------------

INT32 ASIFDL_SetDLSvrInfo(UINT32 nItemType, LPCTSTR szSvrInfo)
{
	return tDownloadUtil.SetDLSvrInfo(nItemType, szSvrInfo);
}
//--------------------------------------------------------------


INT32 ASIFDL_SetHomePath(LPCTSTR lpHomePathList, UINT32 nLen)
{
	return tDownloadUtil.SetHomePath(lpHomePathList, nLen);
}
//--------------------------------------------------------------