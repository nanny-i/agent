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

#ifndef ManagePtnPatchH
#define ManagePtnPatchH
//---------------------------------------------------------------------------

class CManagePtnPatch : public CManageBase<DB_PTN_PATCH>
{

private:
	CDBMgrPtnPatch*		m_tDBMgrPtnPatch;

public:
	INT32			LoadDBMS();

private:
	String			m_strOsName;
	UINT32			m_nProcArch;

public:
	INT32			AddPtnPatch(DB_PTN_PATCH& data);
    INT32			EditPtnPatch(DB_PTN_PATCH& data);
    INT32			DelPtnPatch(UINT32 nID);
	PDB_PTN_PATCH	FindPtnPatchKey(String strKey);
	PDB_PTN_PATCH	FindPtnPatchByKBID(UINT32 nKBID);

public:
	INT32			SetSystemInfo();

public:
	String			GetOsShortName(UINT64 nOsID);

	PDB_PTN_PATCH_LAN	GetLan(UINT32 nID);
	String				GetName(UINT32 nID);

public:
	INT32			GetPkt(MemToken& RecvToken, DB_PTN_PATCH& data);
	INT32			SetPkt(MemToken& SendToken);
	INT32			SetPkt(TMapID& tIDMap, MemToken& SendToken);
    INT32			SetPkt(PDB_PTN_PATCH pdata, MemToken& SendToken);

public:
	void 			RemainDBG_ItemCnt(UINT32 nIdx);

public:
	CManagePtnPatch();
    ~CManagePtnPatch();

};

#endif
