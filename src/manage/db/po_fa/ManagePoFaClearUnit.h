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

#ifndef ManagePoFaClearUnitH
#define ManagePoFaClearUnitH
//---------------------------------------------------------------------------

class CManagePoFaClearUnit : public CManagePoBase<DB_PO_FA_CLEAR_UNIT>
{
public:
	INT32					LoadDBMS();

public:
	INT32					GetHash(UINT32 nID, String& strOrgValue);

public:
	INT32					AddPoFaClearUnit(DB_PO_FA_CLEAR_UNIT&	dpfcu);
    INT32					EditPoFaClearUnit(DB_PO_FA_CLEAR_UNIT&	dpfcu);
	INT32					DelPoFaClearUnit(UINT32 nID);
	INT32					ApplyPoFaClearUnit(DB_PO_FA_CLEAR_UNIT&	dpfcu);

public:
	String					GetName(UINT32 nID);
	INT32					GetLastChkTime(UINT32 nID);

public:
	INT32					SetPkt(MemToken& SendToken);
	INT32					SetPkt(UINT32 nID, MemToken& SendToken);
	INT32					SetPkt(PDB_PO_FA_CLEAR_UNIT pdpfcu, MemToken& SendToken);
	INT32					GetPkt(MemToken& RecvToken, DB_PO_FA_CLEAR_UNIT& dpfcu);

	INT32					SetPkt_Link(MemToken& SendToken);
	INT32					SetPkt_Link(PDB_PO_FA_CLEAR_UNIT pdpfcu, MemToken& SendToken);

public:
	CManagePoFaClearUnit();
    ~CManagePoFaClearUnit();

};

extern CManagePoFaClearUnit*	t_ManagePoFaClearUnit;

#endif
