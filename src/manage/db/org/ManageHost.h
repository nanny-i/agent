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

#ifndef ManageHostH
#define ManageHostH
//---------------------------------------------------------------------------

class CManageHost : public CManageBase<DB_HOST>
{
public:
	INT32					LoadDBMS();

public:
	INT32					AddHost(DB_HOST& dh);
    INT32					EditHost(DB_HOST& dh);
	INT32					EditHost_UsedFlag(UINT32 nID, UINT32 nUsedFlag);
    INT32					DelHost(UINT32 nID);

public:
	INT32					ChgUIDToHID(TListID& tUIDList, TMapID& tHIDMap);
	INT32					ChgUIDToHID(TListID& tUIDList, TListID& tHIDList);

public:
	INT32		GetPktHost(MemToken& RecvToken, DB_HOST& dh);
	INT32		SetPktHost(MemToken& SendToken);
	INT32		SetPktHost(PDB_HOST pdh, MemToken& SendToken);

public:
	CManageHost();
    ~CManageHost();

};

extern CManageHost*	t_ManageHost;

#endif
