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

#ifndef ManageLocalEnvLogH
#define ManageLocalEnvLogH
//---------------------------------------------------------------------------

class CManageLocalEnvLog : public CManageBase<DB_LOCAL_ENV_LOG>
{
public:
	INT32					LoadDBMS();

public:
	INT32					InitHash();
	String					GetHash();

public:
	INT32					AddLocalEnvLog(DB_LOCAL_ENV_LOG&	dlel);
    INT32					EditLocalEnvLog(DB_LOCAL_ENV_LOG&	dlel);
	INT32					DelLocalEnvLog(UINT32 nID);
	INT32					ApplyLocalEnvLog(DB_LOCAL_ENV_LOG&	dlel);

public:
	UINT64					IsInvalidRight(UINT64 nPackage, UINT64 nPolicy, UINT64 nControl);

public:
	INT32					SetPkt(MemToken& SendToken);
	INT32					SetPkt(UINT32 nID, MemToken& SendToken);
	INT32					SetPkt(PDB_LOCAL_ENV_LOG pdlel, MemToken& SendToken);
	INT32					GetPkt(MemToken& RecvToken, DB_LOCAL_ENV_LOG& dlel);

public:
	CManageLocalEnvLog();
    ~CManageLocalEnvLog();

};

extern CManageLocalEnvLog*	t_ManageLocalEnvLog;

#endif
