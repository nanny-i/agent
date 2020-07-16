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

// SGC.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "com_struct.h"
#include "Compress.h"
#include "CompSecuUtil.h"

CCompUtil tCompUtil;

INT32 ASICOMP_CompDir(PASI_COMP_INFO paci)
{
	return tCompUtil.CompressDir(paci);
}
//-------------------------------------------------------------------------

INT32 ASICOMP_DecompDir(PASI_DECOMP_INFO padi)
{
	return tCompUtil.DecompressDir(padi);
}
//-------------------------------------------------------------------------

INT32 ASICOMP_SetNotifyState(PVOID lParam, PVOID pNotifyState)
{
	return tCompUtil.SetNotifyState(lParam, pNotifyState);
}
//-------------------------------------------------------------------------

INT32 ASICOMP_CompFile(LPCTSTR lpFileName, LPCTSTR lpSaveDir, LPCTSTR lpSaveFile)
{
	return tCompUtil.CompressFileAndSave(lpFileName, lpSaveDir, lpSaveFile);	
}
//-------------------------------------------------------------------------

INT32 ASICOMP_DecompFile(LPCTSTR lpFileName, LPCTSTR lpSaveDir, LPCTSTR lpSavedFile)
{
	return tCompUtil.DecompressFileAndSave(lpFileName, lpSaveDir, lpSavedFile);	
}
//-------------------------------------------------------------------------

INT32 ASICOMP_CompFileW(wchar_t *wcFileName, LPCTSTR lpSaveDir, LPCTSTR lpSaveFile)
{
	return tCompUtil.CompressFileAndSaveW(wcFileName, lpSaveDir, lpSaveFile);	
}
//-------------------------------------------------------------------------

INT32 ASICOMP_DecompFileW(LPCTSTR lpFileName, wchar_t * lpSaveDir, wchar_t * lpSavedFile)
{
	return tCompUtil.DecompressFileAndSaveW(lpFileName, lpSaveDir, lpSavedFile);	
}
//-------------------------------------------------------------------------

INT32 ASICOMP_CompBufferAndSaveFile(LPCTSTR lpFileName, BYTE* lpSrcBuffer, INT32 nBufferLen, LPCTSTR lpSaveDir, LPCTSTR lpSaveFile)
{
	return tCompUtil.CompressBufferAndSave(lpFileName, lpSrcBuffer, nBufferLen, lpSaveDir, lpSaveFile);
}
//-------------------------------------------------------------------------

INT32 ASICOMP_DecompFileAndBuffer(LPCTSTR lpFileName, BYTE** lpOutBuffer, INT32& nOutBuffeLen)
{
	return tCompUtil.DecompressFileAndBuffer(lpFileName, lpOutBuffer, nOutBuffeLen);
}
//-------------------------------------------------------------------------

INT32 ASICOMP_CompBufferAndBuffer(BYTE* lpInBuffer, INT32 nLen, LPCTSTR lpRelativeFilePath, LPCTSTR lpAbsoluteFileName, BYTE** lpOutBuffer, INT32& nOutBufferLen, INT32 nUsedComp)
{
	return tCompUtil.CompressBufferAndBuffer(lpInBuffer, nLen, lpRelativeFilePath, lpAbsoluteFileName, lpOutBuffer, nOutBufferLen, nUsedComp);
}
//-------------------------------------------------------------------------

INT32 ASICOMP_CompFileAndBuffer(LPCTSTR lpFilePath, LPCTSTR lpFileName, BYTE** lpOutBuffer, INT32& nOutBufferLen, INT32 nUsedComp)
{
	return tCompUtil.CompressFileAndBuffer(lpFilePath, lpFileName, lpOutBuffer, nOutBufferLen, nUsedComp);
}
//-------------------------------------------------------------------------


INT32 ASICOMP_DecompBufferAndSave(BYTE* lpSrcBuffer, INT32 nSrcBuffLen, LPCTSTR lpSaveDir, LPTSTR lpSaveFile, INT32 nSaveFileLen, LPCTSTR lpSaveFileAddOn, UINT32 nUsedComp)
{
	return tCompUtil.DecompressBufferAndSave(lpSrcBuffer, nSrcBuffLen, lpSaveDir, lpSaveFile, nSaveFileLen, lpSaveFileAddOn, nUsedComp);
}
//-------------------------------------------------------------------------

INT32 ASICOMP_FreeMemory(BYTE* lpOutBuffer)
{
	safe_free(lpOutBuffer);
	return 0;
}
//-------------------------------------------------------------------------

INT32	ASICOMP_S_CompFile(PASI_COMP_SECU pACS, INT32 nLen)
{
	CCompSecuUtil tCompSUtil;
	return tCompSUtil.CompFile(pACS, nLen);
}
//-------------------------------------------------------------------------

INT32	ASICOMP_S_DecompFile(PASI_COMP_SECU pACS, INT32 nLen)
{
	CCompSecuUtil tCompSUtil;
	return tCompSUtil.DecompFile(pACS, nLen);
}
//-------------------------------------------------------------------------

