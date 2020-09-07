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


#ifndef ManagePoInRsBkH
#define ManagePoInRsBkH
//---------------------------------------------------------------------------

class CManagePoInRsBk : public CManagePoBase<DB_PO_IN_RS_BK>
{
public:
	INT32					LoadDBMS();

public:
	INT32					InitHash();
	INT32					InitHash(UINT32 nID);

public:
	INT32					AddPoInRsBk(DB_PO_IN_RS_BK&	data);
    INT32					EditPoInRsBk(DB_PO_IN_RS_BK&	data);
	INT32					DelPoInRsBk(UINT32 nID);
	INT32					ApplyPoInRsBk(DB_PO_IN_RS_BK&	data);

public:
	String					GetName(UINT32 nID);    

public:
	INT32					SetPkt(MemToken& SendToken);
	INT32					SetPkt(UINT32 nID, MemToken& SendToken);
	INT32					SetPkt(PDB_PO_IN_RS_BK pdata, MemToken& SendToken);
	INT32					GetPkt(MemToken& RecvToken, DB_PO_IN_RS_BK& data);

public:
	CManagePoInRsBk();
    ~CManagePoInRsBk();

};

extern CManagePoInRsBk*	t_ManagePoInRsBk;

#endif
