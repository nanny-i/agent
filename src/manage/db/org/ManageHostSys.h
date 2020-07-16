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

#ifndef ManageHostSysH
#define ManageHostSysH
//---------------------------------------------------------------------------

class CManageHostSys : public CManageBase<DB_HOST_SYS>
{
public:
	INT32			LoadDBMS();

public:
	INT32			AddHostSys(DB_HOST_SYS& dhs);
    INT32			EditHostSys(DB_HOST_SYS& dhs);
    INT32			DelHostSys(UINT32 nID);

public:
	INT32			GetPkt(MemToken& RecvToken, DB_HOST_SYS& dhs, UINT32 nPktType);
	INT32			SetPkt(MemToken& SendToken);
    INT32			SetPkt(PDB_HOST_SYS pdhs, MemToken& SendToken);

public:
	CManageHostSys();
    ~CManageHostSys();

};

extern CManageHostSys*	t_ManageHostSys;

#endif
