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

#ifndef ManageHostSwH
#define ManageHostSwH
//---------------------------------------------------------------------------

class CManageHostSw : public CManageBase<DB_HOST_SW>
{

public:
	INT32			LoadDBMS();

public:
	INT32			AddHostSw(DB_HOST_SW& dhs);
    INT32			EditHostSw(DB_HOST_SW& dhs);
    INT32			DelHostSw(UINT32 nID);
    PDB_HOST_SW		FindHostKey(UINT32 nHostID);

public:
	UINT32			FindChkVerID(PDB_HOST_SW pdata);
	UINT32			FindChkVerID(String strChkKey, String strVersion);
	PDB_HOST_SW		FindChkKeyVerItem(String strChkKey, String strVersion);

public:
	INT32			IsExistLocalSw(TListSwInfo* tSwInfoList, String strName);
	INT32			IsExistLocalSwKeyVer(TListSwInfo* tSwInfoList, String strChkKey, String strVersion);

public:
	INT32			GetPkt(MemToken& RecvToken, DB_HOST_SW& dhs);
	INT32			SetPkt(MemToken& SendToken);
	INT32			SetPkt(TListDBHostSw& tDBHostSwList, MemToken& SendToken);
	INT32			SetPkt(PDB_HOST_SW pdhs, MemToken& SendToken);	

public:
	void 			RemainDBG_ItemCnt(UINT32 nIdx);

public:
	CManageHostSw();
    ~CManageHostSw();

};

extern CManageHostSw*	t_ManageHostSw;

#endif
