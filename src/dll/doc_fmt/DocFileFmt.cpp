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
#include "DocFileFmt.h"
#include "DocFileFmtUtil.h"


//---------------------------------------------------------------------------------

INT32 ASIDF_SetDFFmtInit(PASI_DFILE_FMT_INIT pADFFI)
{
	ASI_DFILE_FMT_INIT tADFI;
	if(pADFFI == NULL)
		return -1;
	memcpy(&tADFI, pADFFI, sizeof(tADFI));
	
	SetLogFileInfo(tADFI.szLogPath, tADFI.szLogFile, tADFI.nRemainLog);
	return 0;
}
//---------------------------------------------------------------------------------

INT32 ASIDF_GetDFFmtInfo(PASI_DFILE_FMT_INFO pADFFI, char *acLogMsg)
{	
	ASI_DFILE_FMT_INFO tADFFI;
	CDocFileFmtUtil tDFFUtil;
	if(pADFFI == NULL)
		return -1;

	memcpy(&tADFFI, pADFFI, sizeof(tADFFI));

	tDFFUtil.ProcAnalysis(&tADFFI, acLogMsg);

	memcpy(pADFFI, &tADFFI, sizeof(tADFFI));
	return 0;
}
//---------------------------------------------------------------------------------
