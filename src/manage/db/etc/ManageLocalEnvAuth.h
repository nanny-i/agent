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

#ifndef ManageLocalEnvAuthH
#define ManageLocalEnvAuthH
//---------------------------------------------------------------------------

class CManageLocalEnvAuth : public CManageBase<DB_LOCAL_ENV_AUTH>
{
public:
	INT32					LoadDBMS();

public:
	INT32					InitHash();
	String					GetHash();

public:
	INT32					AddLocalEnvAuth(DB_LOCAL_ENV_AUTH&	dlea);
    INT32					EditLocalEnvAuth(DB_LOCAL_ENV_AUTH&	dlea);
	INT32					DelLocalEnvAuth(UINT32 nID);
	INT32					ApplyLocalEnvAuth(DB_LOCAL_ENV_AUTH&	dlea);

public:
	UINT64					IsInvalidRight(UINT64 nPackage, UINT64 nPolicy, UINT64 nControl);

public:
	INT32					SetPkt(MemToken& SendToken);
	INT32					SetPkt(UINT32 nID, MemToken& SendToken);
	INT32					SetPkt(PDB_LOCAL_ENV_AUTH pdlea, MemToken& SendToken);
	INT32					GetPkt(MemToken& RecvToken, DB_LOCAL_ENV_AUTH& dlea);

public:
	CManageLocalEnvAuth();
    ~CManageLocalEnvAuth();

};

extern CManageLocalEnvAuth*	t_ManageLocalEnvAuth;

#endif
