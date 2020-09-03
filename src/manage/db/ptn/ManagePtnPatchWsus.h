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

#ifndef ManagePtnPatchWsusH
#define ManagePtnPatchWsusH
//---------------------------------------------------------------------------

class CManagePtnPatchWsus : public CManageBase<DB_PTN_PATCH_WSUS>
{

private:
	CDBMgrPtnPatchWsus*	m_tDBMgrPtnPatchWsus;

public:
	INT32			LoadDBMS();

public:
	INT32				AddPtnPatchWsus(DB_PTN_PATCH_WSUS& data);
    INT32				EditPtnPatchWsus(DB_PTN_PATCH_WSUS& data);
    INT32				DelPtnPatchWsus(UINT32 nID);
	PDB_PTN_PATCH_WSUS	GetPtnPatchWsus(UINT64 nSysID, UINT32 nSpID);
	INT32				IsValidPtnFile(PDB_PTN_PATCH_WSUS pdata, UINT32 nDnType);

public:
	INT32			GetPkt(MemToken& RecvToken, DB_PTN_PATCH_WSUS& data);
	INT32			SetPkt(MemToken& SendToken);
    INT32			SetPkt(PDB_PTN_PATCH_WSUS pdata, MemToken& SendToken);

public:
	void 			RemainDBG_ItemCnt(UINT32 nIdx);

public:
	CManagePtnPatchWsus();
    ~CManagePtnPatchWsus();

};

#endif
