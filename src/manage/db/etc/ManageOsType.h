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

#ifndef ManageOsTypeH
#define ManageOsTypeH
//---------------------------------------------------------------------------

class CManageOsType : public CManageBase<DB_OS_TYPE>
{
public:
	INT32				LoadDBMS();

public:
    INT32				IsServerType(UINT32 nID);
    String				GetOsName(UINT32 nID);
    String				GetOsNameSP(UINT32 nID, UINT32 nSP);

public:
	INT32				SetPkt(MemToken& SendToken);
    INT32				SetPkt(PDB_OS_TYPE pdot, MemToken& SendToken);
    
public:
	CManageOsType();
    ~CManageOsType();

};

extern CManageOsType*	t_ManageOsType;

#endif
