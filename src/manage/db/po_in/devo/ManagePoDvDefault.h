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


#ifndef ManagePoDvDefaultH
#define ManagePoDvDefaultH
//---------------------------------------------------------------------------

class CManagePoDvDefault : public CManagePoBase<DB_PO_DV_DEFAULT>
{
public:
	INT32					LoadDBMS();

public:
	
public:
	INT32					AddPoDvDefault(DB_PO_DV_DEFAULT&	didi);
    INT32					EditPoDvDefault(DB_PO_DV_DEFAULT&	didi);
    INT32					DelPoDvDefault(UINT32 nID);
	INT32					ApplyPoDvDefault(DB_PO_DV_DEFAULT&	didi);
	INT32					ResetPoDvDefault();
	String					FindDvPdName(TListDeviceInfo& tList, String strDvInstanceID);
	INT32					DeleteAllDvDefault();
	INT32					DeleteDvDefault(UINT32 nID);
	INT32					FindDvPolID(String strDvInstanceID, String strDvPaInstanceID);
	UINT32					GetDvDefaultCnt();


public:
	String					GetName(UINT32 nID);    

public:
	INT32					SetPkt(MemToken& SendToken, BOOL nIsUse = FALSE);
	INT32					SetPkt(UINT32 nID, MemToken& SendToken);
	INT32					SetPkt(PDB_PO_DV_DEFAULT pdidi, MemToken& SendToken);
	INT32					GetPkt(MemToken& RecvToken, DB_PO_DV_DEFAULT& didi);

public:
	CManagePoDvDefault();
    ~CManagePoDvDefault();

};

extern CManagePoDvDefault*	t_ManagePoDvDefault;

#endif
