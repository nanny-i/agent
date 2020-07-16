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


#include "stdafx.h"
#include "com_struct.h"
#include "LogicMgrPoInAcFile.h"

//---------------------------------------------------------------------------

CLogicMgrPoInAcFile*		t_LogicMgrPoInAcFile = NULL;

//---------------------------------------------------------------------------

CLogicMgrPoInAcFile::CLogicMgrPoInAcFile()
{
	t_ManagePoInAcFile			= new CManagePoInAcFile();
	t_ManagePoInAcFilePkg		= new CManagePoInAcFilePkg();
	t_ManagePoInAcFileUnit		= new CManagePoInAcFileUnit();

	t_ManagePoInAcFileUnitObjPkg	= new CManagePoInAcFileUnitObjPkg();
	t_ManagePoInAcFileUnitSubPkg	= new CManagePoInAcFileUnitSubPkg();
	t_ManagePoInAcFileUnitSchPkg	= new CManagePoInAcFileUnitSchPkg();
	t_ManagePoInAcFileUnitRulPkg	= new CManagePoInAcFileUnitRulPkg();

	t_ManagePoInAcFileObjUnit	= new CManagePoInAcFileObjUnit();
	t_ManagePoInAcFileSubUnit	= new CManagePoInAcFileSubUnit();
	t_ManagePoInAcFileSchUnit	= new CManagePoInAcFileSchUnit();



	t_ManagePoInAcFile->LoadDBMS();
	t_ManagePoInAcFilePkg->LoadDBMS();
	t_ManagePoInAcFileUnit->LoadDBMS();

	t_ManagePoInAcFileUnitObjPkg->LoadDBMS();
	t_ManagePoInAcFileUnitSubPkg->LoadDBMS();
	t_ManagePoInAcFileUnitSchPkg->LoadDBMS();
	t_ManagePoInAcFileUnitRulPkg->LoadDBMS();

	t_ManagePoInAcFileObjUnit->LoadDBMS();
	t_ManagePoInAcFileSubUnit->LoadDBMS();
	t_ManagePoInAcFileSchUnit->LoadDBMS();

	{
		t_ManagePoInAcFileUnitObjPkg->InitPkg();
		t_ManagePoInAcFileUnitSubPkg->InitPkg();
		t_ManagePoInAcFileUnitSchPkg->InitPkg();
		t_ManagePoInAcFileUnitRulPkg->InitPkg();
	}

	t_ManagePoInAcFile->InitHash();

	m_strLogicName		= "mgr agt po in ac file";
	
	m_nPolicyType		= SS_POLICY_TYPE_IN_AC_FILE;
	m_nSSPoSeqIdx		= SS_POLICY_INDEX_IN_AC_FILE;
	m_nAgtPktEditCode	= G_CODE_COMMON_EDIT;	
	
	m_nEvtObjType		= EVENT_OBJECT_TYPE_POLICY;
	m_nEvtObjCode		= EVENT_OBJECT_CODE_POLICY_IN_AC_FILE;
}
//---------------------------------------------------------------------------

CLogicMgrPoInAcFile::~CLogicMgrPoInAcFile()
{
	SAFE_DELETE(t_ManagePoInAcFileObjUnit);
	SAFE_DELETE(t_ManagePoInAcFileSubUnit);
	SAFE_DELETE(t_ManagePoInAcFileSchUnit);

	SAFE_DELETE(t_ManagePoInAcFileUnitObjPkg);
	SAFE_DELETE(t_ManagePoInAcFileUnitSubPkg);
	SAFE_DELETE(t_ManagePoInAcFileUnitSchPkg);
	SAFE_DELETE(t_ManagePoInAcFileUnitRulPkg);

	SAFE_DELETE(t_ManagePoInAcFileUnit);
	SAFE_DELETE(t_ManagePoInAcFilePkg);
	SAFE_DELETE(t_ManagePoInAcFile);

}
//---------------------------------------------------------------------------
INT32		CLogicMgrPoInAcFile::AnalyzePkt_FromMgr_Ext()
{
	return SetHdrAndRtn(AZPKT_CB_RTN_SUCCESS);
}
//---------------------------------------------------------------------------

INT32		CLogicMgrPoInAcFile::AnalyzePkt_FromMgr_Edit_Ext()
{
	PDB_PO_IN_AC_FILE pdpiaf = NULL;
	DB_PO_IN_AC_FILE dpiaf;

	m_tDPH = &(dpiaf.tDPH);

	TListDBPoInAcFilePkg	tPkgList;
	TListDBPoInAcFileUnit	tUnitList;

	TListDBPoInAcFileUnitObjPkg	tObjPkgList;
	TListDBPoInAcFileUnitSubPkg	tSubPkgList;
	TListDBPoInAcFileUnitSchPkg	tSchPkgList;
	TListDBPoInAcFileUnitRulPkg	tRulPkgList;

	TMapDBPoInAcFileObjUnit		tObjMap;
	TMapDBPoInAcFileSubUnit		tSubMap;
	TMapDBPoInAcFileSchUnit		tSchMap;

	if( t_ManagePoInAcFile->GetPkt(RecvToken, dpiaf))				return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
	if(!RecvToken.TokenDel_32(m_nRecvNum))						return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
	while(m_nRecvNum--)
	{
		DB_PO_IN_AC_FILE_PKG	dpiafp;		
		DB_PO_IN_AC_FILE_UNIT dpiafu;

		if( t_ManagePoInAcFilePkg->GetPkt(RecvToken, dpiafp))		return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
		if( t_ManagePoInAcFileUnit->GetPkt(RecvToken, dpiafu))		return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);

		{
			UINT32 nSubRecvNum = 0;
			if(!RecvToken.TokenDel_32(nSubRecvNum))				return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
			while(nSubRecvNum--)
			{
				DB_PO_IN_AC_FILE_UNIT_SUB_PKG sub_pkg;
				DB_PO_IN_AC_FILE_SUB_UNIT sub_unit;

				if( t_ManagePoInAcFileUnitSubPkg->GetPkt(RecvToken, sub_pkg))		return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
				if( t_ManagePoInAcFileSubUnit->GetPkt(RecvToken, sub_unit))			return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);

				tSubPkgList.push_back(sub_pkg);
				tSubMap[sub_unit.tDPH.nID] = sub_unit;

				dpiafu.tDPH._add_key_id_value(SS_PO_IN_AC_UNIT_KEY_TYPE_SUBJECT, sub_pkg.tDPH.nID, sub_unit.tDPH.nID);
			}
			RecvToken.TokenSkip_Block();
		}

		{
			UINT32 nSubRecvNum = 0;
			if(!RecvToken.TokenDel_32(nSubRecvNum))				return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
			while(nSubRecvNum--)
			{
				DB_PO_IN_AC_FILE_UNIT_OBJ_PKG sub_pkg;
				DB_PO_IN_AC_FILE_OBJ_UNIT sub_unit;

				if( t_ManagePoInAcFileUnitObjPkg->GetPkt(RecvToken, sub_pkg))		return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
				if( t_ManagePoInAcFileObjUnit->GetPkt(RecvToken, sub_unit))			return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);

				tObjPkgList.push_back(sub_pkg);
				tObjMap[sub_unit.tDPH.nID] = sub_unit;

				dpiafu.tDPH._add_key_id_value(SS_PO_IN_AC_UNIT_KEY_TYPE_OBJECT, sub_pkg.tDPH.nID, sub_unit.tDPH.nID);
			}
			RecvToken.TokenSkip_Block();
		}

		{
			UINT32 nSchRecvNum = 0;
			if(!RecvToken.TokenDel_32(nSchRecvNum))				return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
			while(nSchRecvNum--)
			{
				DB_PO_IN_AC_FILE_UNIT_SCH_PKG sub_pkg;
				DB_PO_IN_AC_FILE_SCH_UNIT sub_unit;

				if( t_ManagePoInAcFileUnitSchPkg->GetPkt(RecvToken, sub_pkg))		return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
				if( t_ManagePoInAcFileSchUnit->GetPkt(RecvToken, sub_unit))			return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);

				tSchPkgList.push_back(sub_pkg);
				tSchMap[sub_unit.tDPH.nID] = sub_unit;

				dpiafu.tDPH._add_key_id_value(SS_PO_IN_AC_UNIT_KEY_TYPE_SCHEDULE, sub_pkg.tDPH.nID, sub_unit.tDPH.nID);
			}
			RecvToken.TokenSkip_Block();
		}

		{
			UINT32 nSubRecvNum = 0;
			if(!RecvToken.TokenDel_32(nSubRecvNum))				return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
			while(nSubRecvNum--)
			{
				DB_PO_IN_AC_FILE_UNIT_RUL_PKG sub_pkg;
				DB_PO_IN_AC_FILE_SUB_UNIT sub_unit;

				if( t_ManagePoInAcFileUnitRulPkg->GetPkt(RecvToken, sub_pkg))		return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
				if( t_ManagePoInAcFileSubUnit->GetPkt(RecvToken, sub_unit))			return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);

				tRulPkgList.push_back(sub_pkg);
				tSubMap[sub_unit.tDPH.nID] = sub_unit;

				dpiafu.tDPH._add_key_id_value(SS_PO_IN_AC_UNIT_KEY_TYPE_RULE, sub_pkg.tDPH.nID, sub_unit.tDPH.nID);
			}
			RecvToken.TokenSkip_Block();
		}	
		RecvToken.TokenSkip_Block();	
		
		tPkgList.push_back(dpiafp);
		tUnitList.push_back(dpiafu);

		dpiaf.tDPH._add_id(dpiafp.tDPH.nID);
	}

// 	{
// 		dpiaf.nScanTime = GetCurrentDateTimeInt();
// 	}

	pdpiaf = (PDB_PO_IN_AC_FILE)t_DeployPolicyUtil->GetCurPoPtr(m_nPolicyType);
	if(pdpiaf)
	{
// 		if(pdpiaf->tDPH.nID == dpiaf.tDPH.nID && pdpiaf->nSchTime == dpiaf.nSchTime)
// 		{
// 			dpiaf.nScanTime = pdpiaf->nScanTime;
// 		}
		
		t_ManagePoInAcFilePkg->ClearPkgUnitByPolicyID(pdpiaf->tDPH.nID);		
		t_ManagePoInAcFile->DelPoInAcFile(pdpiaf->tDPH.nID);
	}

	{
		{
			{
				TMapDBPoInAcFileSubUnitItor begin, end;
				begin = tSubMap.begin();	end = tSubMap.end();
				for(begin; begin != end; begin++)
				{
					if(t_ManagePoInAcFileSubUnit->ApplyPoInAcFileSubUnit(begin->second))
					{
						SetDLEA_EC(g_nErrRtn);
						WriteLogE("[%s] apply policy sub subject unit information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
						continue;
					}
				}
			}

			{
				TMapDBPoInAcFileObjUnitItor begin, end;
				begin = tObjMap.begin();	end = tObjMap.end();
				for(begin; begin != end; begin++)
				{
					if(t_ManagePoInAcFileObjUnit->ApplyPoInAcFileObjUnit(begin->second))
					{
						SetDLEA_EC(g_nErrRtn);
						WriteLogE("[%s] apply policy sub object unit information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
						continue;
					}
				}
			}

			{
				TMapDBPoInAcFileSchUnitItor begin, end;
				begin = tSchMap.begin();	end = tSchMap.end();
				for(begin; begin != end; begin++)
				{
					if(t_ManagePoInAcFileSchUnit->ApplyPoInAcFileSchUnit(begin->second))
					{
						SetDLEA_EC(g_nErrRtn);
						WriteLogE("[%s] apply policy sub schedule unit information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
						continue;
					}
				}
			}
		}

		{
			{
				TListDBPoInAcFileUnitSubPkgItor begin, end;
				begin = tSubPkgList.begin();	end = tSubPkgList.end();
				for(begin; begin != end; begin++)
				{
					if(t_ManagePoInAcFileUnitSubPkg->FindItem(begin->tDPH.nID))
					{
						SetDLEA_EC(g_nErrRtn);
						WriteLogE("[%s] add policy sub subject pkg information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
						continue;
					}

					t_ManagePoInAcFileUnitSubPkg->AddPoInAcFileUnitSubPkg(*begin);
				}
			}
			{
				TListDBPoInAcFileUnitObjPkgItor begin, end;
				begin = tObjPkgList.begin();	end = tObjPkgList.end();
				for(begin; begin != end; begin++)
				{
					if(t_ManagePoInAcFileUnitObjPkg->FindItem(begin->tDPH.nID))
					{
						SetDLEA_EC(g_nErrRtn);
						WriteLogE("[%s] add policy sub object pkg information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
						continue;
					}

					t_ManagePoInAcFileUnitObjPkg->AddPoInAcFileUnitObjPkg(*begin);
				}
			}
			{
				TListDBPoInAcFileUnitSchPkgItor begin, end;
				begin = tSchPkgList.begin();	end = tSchPkgList.end();
				for(begin; begin != end; begin++)
				{
					if(t_ManagePoInAcFileUnitSchPkg->FindItem(begin->tDPH.nID))
					{
						SetDLEA_EC(g_nErrRtn);
						WriteLogE("[%s] add policy sub schedule pkg information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
						continue;
					}

					t_ManagePoInAcFileUnitSchPkg->AddPoInAcFileUnitSchPkg(*begin);
				}
			}
			{
				TListDBPoInAcFileUnitRulPkgItor begin, end;
				begin = tRulPkgList.begin();	end = tRulPkgList.end();
				for(begin; begin != end; begin++)
				{
					if(t_ManagePoInAcFileUnitRulPkg->FindItem(begin->tDPH.nID))
					{
						SetDLEA_EC(g_nErrRtn);
						WriteLogE("[%s] add policy sub rule pkg information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
						continue;
					}

					t_ManagePoInAcFileUnitRulPkg->AddPoInAcFileUnitRulPkg(*begin);
				}
			}
		}	

		{
			{
				TListDBPoInAcFileUnitItor begin, end;
				begin = tUnitList.begin();	end = tUnitList.end();
				for(begin; begin != end; begin++)
				{
					if(t_ManagePoInAcFileUnit->ApplyPoInAcFileUnit(*begin))
					{
						SetDLEA_EC(g_nErrRtn);
						WriteLogE("[%s] apply policy unit information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
						continue;
					}
				}
			}

			{
				TListDBPoInAcFilePkgItor begin, end;
				begin = tPkgList.begin();	end = tPkgList.end();
				for(begin; begin != end; begin++)
				{
					if(t_ManagePoInAcFilePkg->FindItem(begin->tDPH.nID))
					{
						SetDLEA_EC(g_nErrRtn);
						WriteLogE("[%s] add policy pkg information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
						continue;
					}

					t_ManagePoInAcFilePkg->AddPoInAcFilePkg(*begin);
				}
			}

			if(SetER(t_ManagePoInAcFile->ApplyPoInAcFile(dpiaf)))
			{
				SetDLEA_EC(g_nErrRtn);
				WriteLogE("[%s] apply policy information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
				return SetHdrAndRtn(AZPKT_CB_RTN_DBMS_FAIL);
			}
		}
	}

	{
		t_ThreadTimer->t_TimerUtil.EnableTimer(TIMER_ID_POLICY_APPLY_EPS);
	}

	return SetHdrAndRtn(AZPKT_CB_RTN_SUCCESS);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32		CLogicMgrPoInAcFile::IsExistSysOffSchByPoPwr()
{
	UINT32 nRet = 0;

	PDB_PO_IN_AC_FILE pdb_po = (PDB_PO_IN_AC_FILE)t_DeployPolicyUtil->GetCurPoPtr(m_nPolicyType);
	if(!pdb_po)	
	{
		WriteLogE("[%s] not find current policy", m_strLogicName.c_str());
		return 0;
	}

	if(pdb_po->tDPH.nUsedMode == STATUS_USED_MODE_OFF)
	{
		return 0;
	}

// 	{
// 
// 		if(!pdb_po || pdb_po->tDPH.nUsedMode == STATUS_USED_MODE_OFF)
// 		{ 
// 			return 0;
// 		}
// 
// 		U64_SCHEDULE tIS;
// 		tIS.all = pdb_po->nSchTime;	
// 		if(tIS.all == 0)	tIS.cell.type = SCHEDULE_PERIOD_TYPE_BOOT;
// 
// 		if(tIS.cell.type == SCHEDULE_PERIOD_TYPE_SHUTDOWN_EXT)
// 		{
// 			nRet = 1;
// 		}
// 	}	
	return nRet;
}
//---------------------------------------------------------------------------


INT32		CLogicMgrPoInAcFile::OnTimer_Logic()
{
	PDB_PO_IN_AC_FILE pdb_po = (PDB_PO_IN_AC_FILE)t_DeployPolicyUtil->GetCurPoPtr(m_nPolicyType);
	if(!pdb_po)	
	{
		WriteLogE("[%s] not find current policy", m_strLogicName.c_str());
		return 0;
	}

	if(pdb_po->tDPH.nUsedMode == STATUS_USED_MODE_OFF)
	{
		return 0;
	}

	{
		ApplyPolicy_Sch();
	}	
	return 1;
}
//---------------------------------------------------------------------------

INT32		CLogicMgrPoInAcFile::ApplyPolicy_Sch()
{
	PDB_PO_IN_AC_FILE pdb_po = (PDB_PO_IN_AC_FILE)t_DeployPolicyUtil->GetCurPoPtr(m_nPolicyType);
	if(!pdb_po)	
	{
		WriteLogE("[%s] not find current policy", m_strLogicName.c_str());
		return 0;
	}
	
// 	UINT32 nLastChkTime = pdb_po->nScanTime;
// 	U64_SCHEDULE tIS;
// 	tIS.all = pdb_po->nSchTime;	
// 	if(tIS.all == 0)	tIS.cell.type = SCHEDULE_PERIOD_TYPE_BOOT;
// 
// 	{
// 		MEM_ENV_NOTIFY_INFO_SCH menis;
// 		menis.nNotifyType = SS_POLICY_TYPE_FA_NOTIFY;
// 		menis.nPolType    = SS_POLICY_TYPE_IN_AC_FILE;
// 		menis.nOpType     = EVENT_OPERATION_TYPE_DEL;
// 		menis.nSchType	  = tIS.cell.type;
// 
// 		menis.tDPH.nID    = pdb_po->tDPH.nID;
// 
// 		if(!t_LogicMgrEnvNotifyInfo->IsValidSchduleNotify(nLastChkTime, tIS.all, menis))
// 			t_LogicEnvNotifyInfo->SendPkt_Notify_Sch_info(menis);
// 	}
// 
// 	if(IsValidSchedule(tIS.all, nLastChkTime) == 0)
// 	{
// 		return -1;
// 	}
// 
// 	WriteLogN("start(check) fa op schedule : [id:%d][%d.%d.%d.%d][%u][del_af_day:%d:%d]", pdb_po->tDPH.nID, 
//  				tIS.cell.type, tIS.cell.value, tIS.cell.hour, tIS.cell.min, nLastChkTime, pdb_po->nChkFDTType, pdb_po->nChkFDTValue);
// 
// 	pdb_po->nScanTime = nLastChkTime;
// 	if(pdb_po->tDPH.nID)	t_ManagePoInAcFile->EditPoInAcFile(*pdb_po);
// 
// 	t_LogicMgrLogDoc->ChkBackupOp(pdb_po->nDelCount, pdb_po->nChkFDTType, pdb_po->nChkFDTValue);
// 	t_LogicMgrLogDoc->ChkDelBackupOp();
	
	return 0;
}
//---------------------------------------------------------------------------

