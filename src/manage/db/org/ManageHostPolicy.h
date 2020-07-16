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

#ifndef ManageHostPolicyH
#define ManageHostPolicyH
//---------------------------------------------------------------------------

class CManageHostPolicy : public CManageBase<DB_HOST_POLICY>
{
public:
	INT32					LoadDBMS();

public:
	INT32					AddHostPolicy(DB_HOST_POLICY&	dhp);
    INT32					EditHostPolicy(DB_HOST_POLICY&	dhp);
    INT32					DelHostPolicy(UINT32 nID);
	PDB_HOST_POLICY			FindHostPolicy_HostID(UINT32 nHostID);

public:
	UINT32					GetHostPolicyID(UINT32 nHostID, UINT64 nPolicyType);

public:
	INT32					GetHostIDMap(TMapID& tIDMap, UINT32 nPkgID, UINT64 nPolicyType);
    INT32					GetHostIDList(TListID& tIDList, UINT32 nPkgID, UINT64 nPolicyType);
    INT32					CheckHostPolicyStatus(TListID& tHIDList, UINT32 nPkgID, UINT64 nPolicyType, TListID& tApplyIDList, TListID& tReleaseIDList);  

public:
	INT32				SetPkt(MemToken& SendToken);
    INT32				SetPkt(PDB_HOST_POLICY pdhp, MemToken& SendToken);


public:
	CManageHostPolicy();
    ~CManageHostPolicy();

};

extern CManageHostPolicy*	t_ManageHostPolicy;

#endif
