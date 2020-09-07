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
#include "ManagePatchFile.h"

//---------------------------------------------------------------------------

CManagePatchFile*	t_ManagePatchFile = NULL;

//---------------------------------------------------------------------------

CManagePatchFile::CManagePatchFile()
{
}
//---------------------------------------------------------------------------

CManagePatchFile::~CManagePatchFile()
{
	
}
//---------------------------------------------------------------------------

INT32		CManagePatchFile::SetDnFileList(UINT32 nID, String strFileList, CHAR szTok)
{
	MEM_PATCH_FILE data;
	data.nID = nID;	
	StrToMapIDStr(strFileList, data.tDnFileMap, szTok);

	return AddItem(data);
}
//---------------------------------------------------------------------------

INT32		CManagePatchFile::SetDnFileList(UINT32 nID, TMapIDStr& tDnMap)
{
	MEM_PATCH_FILE data;
	data.nID = nID;
	data.tDnFileMap = tDnMap;

	return AddItem(data);	
}
//---------------------------------------------------------------------------

INT32			CManagePatchFile::ChgValidPatchFile(UINT32 nPatchID)
{
	return 0;
}
//---------------------------------------------------------------------------

INT32			CManagePatchFile::ChgValidPatchFile(TMapIDStr& tFileMap)
{
	return 0;
}
//---------------------------------------------------------------------------

INT32	CManagePatchFile::IsReadyPatchFile(UINT32 nID)
{
	return 0;
}
//---------------------------------------------------------------------------

INT32	CManagePatchFile::IsReadyPatchFile(TMapIDStr& tFileMap)
{
	return 0;
}
//---------------------------------------------------------------------------
