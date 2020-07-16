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

#ifndef ManageFileDownH
#define ManageFileDownH
//---------------------------------------------------------------------------

class CManageFileDown : public CManageBase<ASI_FDL_INFO>
{
public:

public:
	INT32		GetIDListByType(UINT32 nType, TListID& tIDList);
	INT32		ClearItemByType(UINT32 nType);
	INT32		IsExistDnInfo(UINT32 nType, UINT32 nPoID, UINT32 nItemID);

	INT32		ClearItemByEndDp(UINT32 nType, TListID& tNonDelIDList);

public:
	INT32		GetDFIDList(TListID64& tIDList);
	INT32		AddDFInfo(ASI_FDL_INFO& data, TListID& tSchPkgIDList);
	INT32		ChkDFInfo(ASI_FDL_INFO& data, TListID& tSchPkgIDList);

public:
	INT32		AddEndDpFile(UINT32 nProID, UINT32 nDpLogID);
	INT32		GetEndDpFile(UINT32 nProID);

public:
	CManageFileDown();
    ~CManageFileDown();

};

extern CManageFileDown*	t_ManageFileDown;

#endif
