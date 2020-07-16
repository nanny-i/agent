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

#ifndef ManageUserPolicyH
#define ManageUserPolicyH
//---------------------------------------------------------------------------

class CManageUserPolicy : public CManageBase<DB_USER_POLICY>
{
public:
	INT32					LoadDBMS();
    INT32					InitUserPolicy();

public:
	INT32					AddUserPolicy(DB_USER_POLICY&	dup);
    INT32					EditUserPolicy(DB_USER_POLICY&	dup);
    INT32					DelUserPolicy(UINT32 nID);
	PDB_USER_POLICY			FindUserPolicy_UserID(UINT32 nUserID);

public:
	UINT32					GetUserPolicyID(UINT32 nUserID, UINT64 nPolicyType);

public:
	INT32					GetUserIDMap(TMapID& tIDMap, UINT32 nPkgID, UINT64 nPolicyType);
    INT32					GetUserIDList(TListID& tIDList, UINT32 nPkgID, UINT64 nPolicyType);
    INT32					CheckUserPolicyStatus(TListID& tHIDList, UINT32 nPkgID, UINT64 nPolicyType, TListID& tApplyIDList, TListID& tReleaseIDList);  

public:
	INT32				SetPkt(MemToken& SendToken);
    INT32				SetPkt(PDB_USER_POLICY pdup, MemToken& SendToken);


public:
	CManageUserPolicy();
    ~CManageUserPolicy();

};

extern CManageUserPolicy*	t_ManageUserPolicy;

#endif
