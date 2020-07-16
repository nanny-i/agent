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

#ifndef ManageEnvSelfProtectAgtH
#define ManageEnvSelfProtectAgtH
//---------------------------------------------------------------------------

class CManageEnvSelfProtectAgt : public CManagePoBase<DB_ENV_SELF_PROTECT_AGT>
{
public:
	INT32					LoadDBMS();

public:
	INT32					InitHash();
	String					GetHash();

public:
	INT32					AddEnvSelfProtectAgt(DB_ENV_SELF_PROTECT_AGT&	despa);
    INT32					EditEnvSelfProtectAgt(DB_ENV_SELF_PROTECT_AGT&	despa);
	INT32					DelEnvSelfProtectAgt(UINT32 nID);
	INT32					ApplyEnvSelfProtectAgt(DB_ENV_SELF_PROTECT_AGT&	despa);

public:
	String					GetName(UINT32 nID);    

public:
	INT32					SetPkt(MemToken& SendToken);
	INT32					SetPkt(UINT32 nID, MemToken& SendToken);
	INT32					SetPkt(PDB_ENV_SELF_PROTECT_AGT pdespa, MemToken& SendToken);
	INT32					GetPkt(MemToken& RecvToken, DB_ENV_SELF_PROTECT_AGT& despa);

public:
	CManageEnvSelfProtectAgt();
    ~CManageEnvSelfProtectAgt();

};

extern CManageEnvSelfProtectAgt*	t_ManageEnvSelfProtectAgt;

#endif
