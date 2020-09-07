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


#ifndef ManagePatchFileH
#define ManagePatchFileH
//---------------------------------------------------------------------------

class CManagePatchFile : public CManageBase<MEM_PATCH_FILE>
{


public:
	INT32		SetDnFileList(UINT32 nID, String strFileList, CHAR szTok);
	INT32		SetDnFileList(UINT32 nID, TMapIDStr& tDnMap);

public:
	INT32		ChgValidPatchFile(UINT32 nPatchID);
	INT32		ChgValidPatchFile(TMapIDStr& tFileMap);
	INT32		IsReadyPatchFile(UINT32 nID);
	INT32		IsReadyPatchFile(TMapIDStr& tFileMap);

public:
	CManagePatchFile();
    ~CManagePatchFile();

};

extern CManagePatchFile*	t_ManagePatchFile;

#endif
