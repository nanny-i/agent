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

#ifndef DeployPolicyUtilH
#define DeployPolicyUtilH
//---------------------------------------------------------------------------

class CDeployPolicyUtil
{

public:
	INT32		SetPolicy(DB_POLICY& dp, UINT32 nPkgID, UINT64 nPolicyType);
	UINT32		GetPolicy(DB_POLICY& dp, UINT64 nPolicyType);

public:
	UINT32		GetCurPoID(UINT64 nPolicyType);
	PVOID		GetCurPoPtr(UINT64 nPolicyType);
	PVOID		GetPoPtr(UINT32 nID, UINT64 nPolicyType);

public:
	INT32		ApplyPolicy(UINT64 nPolicyType, UINT32 nPoID);

public:
	CDeployPolicyUtil();
    ~CDeployPolicyUtil();
};

extern CDeployPolicyUtil*		t_DeployPolicyUtil;


#endif
