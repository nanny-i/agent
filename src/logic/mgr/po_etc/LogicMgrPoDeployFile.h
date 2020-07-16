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

#ifndef LogicMgrPoDeployFileH
#define LogicMgrPoDeployFileH
//---------------------------------------------------------------------------

class CLogicMgrPoDeployFile	: public CLogicBase
{
private:
	INT32		AnalyzePkt_FromMgr_Ext();
	INT32		AnalyzePkt_FromMgr_Edit_Ext();

public:
	INT32		ApplyPolicy();
	INT32		OnTimer_Logic();

	INT32		ChkEndDpFile();

private:
	INT32		IsValidSchedule(UINT32 nUnitID, TListID& tValidSchIDList);
	INT32		IsValidCheck(UINT32 nUnitID);
	INT32		IsValidTarget(UINT32 nUnitID);
	INT32		AddDpDownInfo(UINT32 nPoID, UINT32 nUnitID, TListID& tSchPkgIDList);

private:
	INT32		ComppareInfo_AppWiz(UINT32 nChkUnitID);
	INT32		ComppareInfo_Registry(UINT32 nChkUnitID);
	INT32		ComppareInfo_FilePath(UINT32 nChkUnitID);
	INT32		ComppareInfo_FileVersion(UINT32 nChkUnitID);
	INT32		ComppareInfo_Process(UINT32 nChkUnitID);

public:
	VOID	ASISI_GetSwInfo(PASISI_SW_INFO pasi, INT32 nSize, PVOID lParam);

public:
	CLogicMgrPoDeployFile();
    ~CLogicMgrPoDeployFile();
};

extern CLogicMgrPoDeployFile*		t_LogicMgrPoDeployFile;

#endif
