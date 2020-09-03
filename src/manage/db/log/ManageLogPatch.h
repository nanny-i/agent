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

#ifndef ManageLogPatchH
#define ManageLogPatchH
//---------------------------------------------------------------------------

class CManageLogPatch : public CManageBase<DB_LOG_PATCH>
{
public:
	INT32					LoadDBMS();

public:
	INT32					AddLogPatch(DB_LOG_PATCH&	data);
    INT32					EditLogPatch(DB_LOG_PATCH&	data);
    INT32					DelLogPatch(UINT32 nID);

public:
	INT32					IsExistLocalPatch(TListDBLogPatch* tPatchInfoList, PDB_LOG_PATCH pdata);
	INT32					IsRestartSystem();
	INT32					GetApplyNum(UINT32 nID);


public:
	INT32					SetPkt(MemToken& SendToken);
	INT32					SetPkt(TListDBLogPatch& tLogList, MemToken& SendToken);
	INT32					SetPkt(PDB_LOG_PATCH pdata, MemToken& SendToken);
	INT32					GetPkt(MemToken& RecvToken, DB_LOG_PATCH& data);

	INT32					SetPkt_Link(MemToken& SendToken);
	INT32					SetPkt_Link(TListDBLogPatch& tLogList, MemToken& SendToken);
	INT32					SetPkt_Link(PDB_LOG_PATCH pdata, MemToken& SendToken);
	INT32					GetPkt_Link(MemToken& RecvToken, DB_LOG_PATCH& data);

public:
	CManageLogPatch();
    ~CManageLogPatch();

};

extern CManageLogPatch*	t_ManageLogPatch;

#endif
