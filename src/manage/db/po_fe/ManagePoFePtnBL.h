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

#ifndef ManagePoFePtnBLH
#define ManagePoFePtnBLH
//---------------------------------------------------------------------------

class CManagePoFePtnBL : public CManagePoBase<DB_PO_FE_PTN_BL>
{
public:
	INT32					LoadDBMS();

public:
	INT32					InitHash();
	INT32					InitHash(UINT32 nID);

public:
	INT32					AddPoFePtnBL(DB_PO_FE_PTN_BL&	dpfpb);
    INT32					EditPoFePtnBL(DB_PO_FE_PTN_BL&	dpfpb);
	INT32					DelPoFePtnBL(UINT32 nID);
	INT32					ApplyPoFePtnBL(DB_PO_FE_PTN_BL&	dpfpb);

public:
	String					GetName(UINT32 nID);   

public:
	INT32					IsValidPtnFile(UINT32 nID); 
	INT32					IsValidPtnFile(PDB_PO_FE_PTN_BL pdpfpb);

public:
	INT32					SetPkt(MemToken& SendToken);
	INT32					SetPkt(UINT32 nID, MemToken& SendToken);
	INT32					SetPktHost(UINT32 nID, MemToken& SendToken);
	INT32					SetPkt(PDB_PO_FE_PTN_BL pdpfpb, MemToken& SendToken);
	INT32					GetPkt(MemToken& RecvToken, DB_PO_FE_PTN_BL& dpfpb);

public:
	CManagePoFePtnBL();
    ~CManagePoFePtnBL();

};

extern CManagePoFePtnBL*	t_ManagePoFePtnBL;

#endif
