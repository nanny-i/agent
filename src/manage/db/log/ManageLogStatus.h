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

#ifndef ManageLogStatusH
#define ManageLogStatusH
//---------------------------------------------------------------------------

class CManageLogStatus : public CManageBase<DB_LOG_STATUS>
{
public:
	INT32		LoadDBMS();

public:
	INT32					AddLogStatus(DB_LOG_STATUS&	dls);
    INT32					EditLogStatus(DB_LOG_STATUS&	dls);
    INT32					DelLogStatus(UINT32 nID);
	PDB_LOG_STATUS			FindLogStatus(UINT32 nID);

public:
	INT32					IsExistLogStatus(DB_LOG_STATUS&	dls);
	String					GetFullDesc(DB_LOG_STATUS dlst);

public:
	INT32					SetPkt(MemToken& SendToken);
	INT32					SetPkt(PDB_LOG_STATUS pdls, MemToken& SendToken);
	INT32					GetPkt(MemToken& RecvToken, DB_LOG_STATUS& dls);

	INT32					SetPkt_Link(MemToken& SendToken);
public:
	CManageLogStatus();
    ~CManageLogStatus();

};

extern CManageLogStatus*	t_ManageLogStatus;

#endif
