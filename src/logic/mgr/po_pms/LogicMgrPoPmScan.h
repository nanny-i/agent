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

#ifndef LogicMgrPoPmScanH
#define LogicMgrPoPmScanH
//---------------------------------------------------------------------------

class CLogicMgrPoPmScan	: public CLogicBase
{
private:
	INT32		AnalyzePkt_FromMgr_Ext();
	INT32		AnalyzePkt_FromMgr_Edit_Ext();

public:
	INT32		OnTimer_Logic();
	INT32		ApplyPolicy_Unit(UINT32 nUnitID);
	INT32		ApplyPolicy_Unit(PDB_PO_PM_SCAN_UNIT pdata);
	
public:
	INT32		IsUsedOffLineScan();

public:
	INT32		StartScanDefault();
	INT32		StartScanUnit(PDB_PO_PM_SCAN_UNIT pdata);

public:
	INT32		SendPkt_NewPatch(UINT32 nWorkID);

public:
	CLogicMgrPoPmScan();
    ~CLogicMgrPoPmScan();
};

extern CLogicMgrPoPmScan*		t_LogicMgrPoPmScan;

#endif
