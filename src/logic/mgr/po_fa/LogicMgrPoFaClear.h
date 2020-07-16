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

#ifndef LogicMgrPoFaClearH
#define LogicMgrPoFaClearH
//---------------------------------------------------------------------------

class CLogicMgrPoFaClear	: public CLogicBase
{
private:
	INT32		AnalyzePkt_FromMgr_Ext();
	INT32		AnalyzePkt_FromMgr_Edit_Ext();

public:
	INT32		ApplyPolicy();
	INT32		OnTimer_Logic();

public:
	INT32		ApplyPolicy_Unit(UINT32 nUnitID, MEM_FIND_ORDER_INFO& tMFOI);
	INT32		ApplyPolicy_Unit(PDB_PO_FA_CLEAR_UNIT pdpfcu, MEM_FIND_ORDER_INFO& tMFOI);

public:
	INT32		ApplyPolicy_SendLastChkTime(INT32 nUnitID);

public:
	INT32		EndFindOrder(PMEM_FIND_ORDER_INFO pMFOI);
	INT32		PgFindOrder(PMEM_FIND_ORDER_INFO pMFOI);

public:
	INT32		IsExistSysOffSch();
	INT32		IsExistSysOffSchByPoPwr();

public:
	INT32		ConvertEnvPathToLocalPath(String strInPath, String& strOutPath);
	
public:
	VOID		cbDriveInfoList(PASIDM_LOCAL_DRIVE_INFO pamldi, INT32 nSize, PVOID lParam);

public:
	CLogicMgrPoFaClear();
    ~CLogicMgrPoFaClear();
};

extern CLogicMgrPoFaClear*		t_LogicMgrPoFaClear;

#endif
