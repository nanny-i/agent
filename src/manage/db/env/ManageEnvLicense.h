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

#ifndef ManageEnvLicenseH
#define ManageEnvLicenseH
//---------------------------------------------------------------------------

class CManageEnvLicense : public CManagePoBase<DB_ENV_LICENSE>
{
public:
	INT32					LoadDBMS();

public:
	INT32					InitHash();
	String					GetHash();

public:
	INT32					AddEnvLicense(DB_ENV_LICENSE&	del);
    INT32					EditEnvLicense(DB_ENV_LICENSE&	del);
	INT32					DelEnvLicense(UINT32 nID);
	INT32					ApplyEnvLicense(DB_ENV_LICENSE&	del);

public:
	String					GetName(UINT32 nID);    

public:
	UINT64					IsInvalidRight(UINT64 nPackage, UINT64 nPolicy, UINT64 nControl);
	UINT64					IsValidRight(UINT64 nPackage, UINT64 nPolicy, UINT64 nControl);

	UINT64					IsValidRight(PDB_ENV_LICENSE pdata, UINT64 nPackage, UINT64 nPolicy, UINT64 nControl);
	UINT64					IsInvalidRight(PDB_ENV_LICENSE pdata, UINT64 nPackage, UINT64 nPolicy, UINT64 nControl);
	

public:
	INT32					SetPkt(MemToken& SendToken);
	INT32					SetPkt(UINT32 nID, MemToken& SendToken);
	INT32					SetPkt(PDB_ENV_LICENSE pdel, MemToken& SendToken);
	INT32					GetPkt(MemToken& RecvToken, DB_ENV_LICENSE& del);

public:
	CManageEnvLicense();
    ~CManageEnvLicense();

};

extern CManageEnvLicense*	t_ManageEnvLicense;

#endif
