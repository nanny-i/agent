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

#ifndef LogicMgrLogPatchH
#define LogicMgrLogPatchH
//---------------------------------------------------------------------------

class CLogicMgrLogPatch	: public CLogicBase
{
private:
	INT32		AnalyzePkt_FromMgr_Ext();
	INT32		AnalyzePkt_FromMgr_Add_Ext();
	INT32		AnalyzePkt_FromMgr_Edit_Ext();
	INT32		AnalyzePkt_FromMgr_Del_Ext();

	INT32		AnalyzePkt_FromMgr_Ext_Sync();

public:
	INT32		StartDownLoad(TListDBLogPatch& tLogList, UINT32 nPoUnitID = 0);
	INT32		AddDpDownInfoPatch(PDB_LOG_PATCH pdata, UINT32 nPoUnitID = 0);

public:
	INT32		ApplyExecuteEnd(UINT32 nWorkID);

public:
	INT32		IsWaitBootByPatch(UINT32 nID);

public:
	void		SetLogPatch(DB_LOG_PATCH& data);
	void		SetLogPatch(TListDBLogPatch& tLogList);

public:
	CLogicMgrLogPatch();
    ~CLogicMgrLogPatch();
};

extern CLogicMgrLogPatch*		t_LogicMgrLogPatch;

#endif
