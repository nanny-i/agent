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
#include "LogicMgrPoFaOp.h"

//---------------------------------------------------------------------------

CLogicMgrPoFaOp*		t_LogicMgrPoFaOp = NULL;

//---------------------------------------------------------------------------

CLogicMgrPoFaOp::CLogicMgrPoFaOp()
{
	t_ManagePoFaOp			= new CManagePoFaOp();
	t_ManagePoFaOpPkg		= new CManagePoFaOpPkg();
	t_ManagePoFaOpUnit		= new CManagePoFaOpUnit();

	t_ManagePoFaOpUnitObjPkg	= new CManagePoFaOpUnitObjPkg();
	t_ManagePoFaOpUnitSubPkg	= new CManagePoFaOpUnitSubPkg();
	t_ManagePoFaOpUnitSchPkg	= new CManagePoFaOpUnitSchPkg();
	t_ManagePoFaOpUnitRulPkg	= new CManagePoFaOpUnitRulPkg();

	t_ManagePoFaOpObjUnit	= new CManagePoFaOpObjUnit();
	t_ManagePoFaOpSubUnit	= new CManagePoFaOpSubUnit();
	t_ManagePoFaOpSchUnit	= new CManagePoFaOpSchUnit();



	t_ManagePoFaOp->LoadDBMS();
	t_ManagePoFaOpPkg->LoadDBMS();
	t_ManagePoFaOpUnit->LoadDBMS();

	t_ManagePoFaOpUnitObjPkg->LoadDBMS();
	t_ManagePoFaOpUnitSubPkg->LoadDBMS();
	t_ManagePoFaOpUnitSchPkg->LoadDBMS();
	t_ManagePoFaOpUnitRulPkg->LoadDBMS();

	t_ManagePoFaOpObjUnit->LoadDBMS();
	t_ManagePoFaOpSubUnit->LoadDBMS();
	t_ManagePoFaOpSchUnit->LoadDBMS();

	{
		t_ManagePoFaOpUnitObjPkg->InitPkg();
		t_ManagePoFaOpUnitSubPkg->InitPkg();
		t_ManagePoFaOpUnitSchPkg->InitPkg();
		t_ManagePoFaOpUnitRulPkg->InitPkg();
	}

	t_ManagePoFaOp->InitHash();

	m_strLogicName		= "mgr agt po fa op";
	
	m_nPolicyType		= SS_POLICY_TYPE_FA_OP;
	m_nSSPoSeqIdx		= SS_POLICY_INDEX_FA_OP;
	m_nAgtPktEditCode	= G_CODE_COMMON_EDIT;	
	
	m_nEvtObjType		= EVENT_OBJECT_TYPE_POLICY;
	m_nEvtObjCode		= EVENT_OBJECT_CODE_POLICY_FA_OP;
}
//---------------------------------------------------------------------------

CLogicMgrPoFaOp::~CLogicMgrPoFaOp()
{
	SAFE_DELETE(t_ManagePoFaOpObjUnit);
	SAFE_DELETE(t_ManagePoFaOpSubUnit);
	SAFE_DELETE(t_ManagePoFaOpSchUnit);

	SAFE_DELETE(t_ManagePoFaOpUnitObjPkg);
	SAFE_DELETE(t_ManagePoFaOpUnitSubPkg);
	SAFE_DELETE(t_ManagePoFaOpUnitSchPkg);
	SAFE_DELETE(t_ManagePoFaOpUnitRulPkg);

	SAFE_DELETE(t_ManagePoFaOpUnit);
	SAFE_DELETE(t_ManagePoFaOpPkg);
	SAFE_DELETE(t_ManagePoFaOp);

}
//---------------------------------------------------------------------------
INT32		CLogicMgrPoFaOp::AnalyzePkt_FromMgr_Ext()
{
	return SetHdrAndRtn(AZPKT_CB_RTN_SUCCESS);
}
//---------------------------------------------------------------------------

INT32		CLogicMgrPoFaOp::AnalyzePkt_FromMgr_Edit_Ext()
{
	PDB_PO_FA_OP pdpfo = NULL;
	DB_PO_FA_OP dpfo;

	m_tDPH = &(dpfo.tDPH);

	TListDBPoFaOpPkg	tPkgList;
	TListDBPoFaOpUnit	tUnitList;

	TListDBPoFaOpUnitObjPkg	tObjPkgList;
	TListDBPoFaOpUnitSubPkg	tSubPkgList;
	TListDBPoFaOpUnitSchPkg	tSchPkgList;
	TListDBPoFaOpUnitRulPkg	tRulPkgList;

	TMapDBPoFaOpObjUnit		tObjMap;
	TMapDBPoFaOpSubUnit		tSubMap;
	TMapDBPoFaOpSchUnit		tSchMap;

	if( t_ManagePoFaOp->GetPkt(RecvToken, dpfo))				return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
	if(!RecvToken.TokenDel_32(m_nRecvNum))						return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
	while(m_nRecvNum--)
	{
		DB_PO_FA_OP_PKG	dpfop;		
		DB_PO_FA_OP_UNIT dpfou;

		if( t_ManagePoFaOpPkg->GetPkt(RecvToken, dpfop))		return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
		if( t_ManagePoFaOpUnit->GetPkt(RecvToken, dpfou))		return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);

		{
			UINT32 nSubRecvNum = 0;
			if(!RecvToken.TokenDel_32(nSubRecvNum))				return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
			while(nSubRecvNum--)
			{
				DB_PO_FA_OP_UNIT_SUB_PKG sub_pkg;
				DB_PO_FA_OP_SUB_UNIT sub_unit;

				if( t_ManagePoFaOpUnitSubPkg->GetPkt(RecvToken, sub_pkg))		return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
				if( t_ManagePoFaOpSubUnit->GetPkt(RecvToken, sub_unit))			return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);

				tSubPkgList.push_back(sub_pkg);
				tSubMap[sub_unit.tDPH.nID] = sub_unit;

				dpfou.tDPH._add_key_id_value(SS_PO_FA_OP_UNIT_KEY_TYPE_SUBJECT, sub_pkg.tDPH.nID, sub_unit.tDPH.nID);
			}
			RecvToken.TokenSkip_Block();
		}

		{
			UINT32 nSubRecvNum = 0;
			if(!RecvToken.TokenDel_32(nSubRecvNum))				return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
			while(nSubRecvNum--)
			{
				DB_PO_FA_OP_UNIT_OBJ_PKG sub_pkg;
				DB_PO_FA_OP_OBJ_UNIT sub_unit;

				if( t_ManagePoFaOpUnitObjPkg->GetPkt(RecvToken, sub_pkg))		return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
				if( t_ManagePoFaOpObjUnit->GetPkt(RecvToken, sub_unit))			return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);

				tObjPkgList.push_back(sub_pkg);
				tObjMap[sub_unit.tDPH.nID] = sub_unit;

				dpfou.tDPH._add_key_id_value(SS_PO_FA_OP_UNIT_KEY_TYPE_OBJECT, sub_pkg.tDPH.nID, sub_unit.tDPH.nID);
			}
			RecvToken.TokenSkip_Block();
		}

		{
			UINT32 nSchRecvNum = 0;
			if(!RecvToken.TokenDel_32(nSchRecvNum))				return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
			while(nSchRecvNum--)
			{
				DB_PO_FA_OP_UNIT_SCH_PKG sub_pkg;
				DB_PO_FA_OP_SCH_UNIT sub_unit;

				if( t_ManagePoFaOpUnitSchPkg->GetPkt(RecvToken, sub_pkg))		return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
				if( t_ManagePoFaOpSchUnit->GetPkt(RecvToken, sub_unit))			return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);

				tSchPkgList.push_back(sub_pkg);
				tSchMap[sub_unit.tDPH.nID] = sub_unit;

				dpfou.tDPH._add_key_id_value(SS_PO_FA_OP_UNIT_KEY_TYPE_SCHEDULE, sub_pkg.tDPH.nID, sub_unit.tDPH.nID);
			}
			RecvToken.TokenSkip_Block();
		}

		{
			UINT32 nSubRecvNum = 0;
			if(!RecvToken.TokenDel_32(nSubRecvNum))				return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
			while(nSubRecvNum--)
			{
				DB_PO_FA_OP_UNIT_RUL_PKG sub_pkg;
				DB_PO_FA_OP_SUB_UNIT sub_unit;

				if( t_ManagePoFaOpUnitRulPkg->GetPkt(RecvToken, sub_pkg))		return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
				if( t_ManagePoFaOpSubUnit->GetPkt(RecvToken, sub_unit))			return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);

				tRulPkgList.push_back(sub_pkg);
				tSubMap[sub_unit.tDPH.nID] = sub_unit;

				dpfou.tDPH._add_key_id_value(SS_PO_FA_OP_UNIT_KEY_TYPE_RULE, sub_pkg.tDPH.nID, sub_unit.tDPH.nID);
			}
			RecvToken.TokenSkip_Block();
		}	
		RecvToken.TokenSkip_Block();	
		
		tPkgList.push_back(dpfop);
		tUnitList.push_back(dpfou);

		dpfo.tDPH._add_id(dpfop.tDPH.nID);
	}

	{
		dpfo.nScanTime = GetCurrentDateTimeInt();
	}

	pdpfo = (PDB_PO_FA_OP)t_DeployPolicyUtil->GetCurPoPtr(m_nPolicyType);
	if(pdpfo)
	{
		if(pdpfo->tDPH.nID == dpfo.tDPH.nID && pdpfo->nSchTime == dpfo.nSchTime)
		{
			dpfo.nScanTime = pdpfo->nScanTime;
		}
		
		t_ManagePoFaOpPkg->ClearPkgUnitByPolicyID(pdpfo->tDPH.nID);		
		t_ManagePoFaOp->DelPoFaOp(pdpfo->tDPH.nID);
	}

	{
		{
			{
				TMapDBPoFaOpSubUnitItor begin, end;
				begin = tSubMap.begin();	end = tSubMap.end();
				for(begin; begin != end; begin++)
				{
					if(t_ManagePoFaOpSubUnit->ApplyPoFaOpSubUnit(begin->second))
					{
						SetDLEH_EC(g_nErrRtn);
						WriteLogE("[%s] apply policy sub subject unit information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
						continue;
					}
				}
			}

			{
				TMapDBPoFaOpObjUnitItor begin, end;
				begin = tObjMap.begin();	end = tObjMap.end();
				for(begin; begin != end; begin++)
				{
					if(t_ManagePoFaOpObjUnit->ApplyPoFaOpObjUnit(begin->second))
					{
						SetDLEH_EC(g_nErrRtn);
						WriteLogE("[%s] apply policy sub object unit information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
						continue;
					}
				}
			}

			{
				TMapDBPoFaOpSchUnitItor begin, end;
				begin = tSchMap.begin();	end = tSchMap.end();
				for(begin; begin != end; begin++)
				{
					if(t_ManagePoFaOpSchUnit->ApplyPoFaOpSchUnit(begin->second))
					{
						SetDLEH_EC(g_nErrRtn);
						WriteLogE("[%s] apply policy sub schedule unit information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
						continue;
					}
				}
			}
		}

		{
			{
				TListDBPoFaOpUnitSubPkgItor begin, end;
				begin = tSubPkgList.begin();	end = tSubPkgList.end();
				for(begin; begin != end; begin++)
				{
					if(t_ManagePoFaOpUnitSubPkg->FindItem(begin->tDPH.nID))
					{
						SetDLEH_EC(g_nErrRtn);
						WriteLogE("[%s] add policy sub subject pkg information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
						continue;
					}

					t_ManagePoFaOpUnitSubPkg->AddPoFaOpUnitSubPkg(*begin);
				}
			}
			{
				TListDBPoFaOpUnitObjPkgItor begin, end;
				begin = tObjPkgList.begin();	end = tObjPkgList.end();
				for(begin; begin != end; begin++)
				{
					if(t_ManagePoFaOpUnitObjPkg->FindItem(begin->tDPH.nID))
					{
						SetDLEH_EC(g_nErrRtn);
						WriteLogE("[%s] add policy sub object pkg information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
						continue;
					}

					t_ManagePoFaOpUnitObjPkg->AddPoFaOpUnitObjPkg(*begin);
				}
			}
			{
				TListDBPoFaOpUnitSchPkgItor begin, end;
				begin = tSchPkgList.begin();	end = tSchPkgList.end();
				for(begin; begin != end; begin++)
				{
					if(t_ManagePoFaOpUnitSchPkg->FindItem(begin->tDPH.nID))
					{
						SetDLEH_EC(g_nErrRtn);
						WriteLogE("[%s] add policy sub schedule pkg information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
						continue;
					}

					t_ManagePoFaOpUnitSchPkg->AddPoFaOpUnitSchPkg(*begin);
				}
			}
			{
				TListDBPoFaOpUnitRulPkgItor begin, end;
				begin = tRulPkgList.begin();	end = tRulPkgList.end();
				for(begin; begin != end; begin++)
				{
					if(t_ManagePoFaOpUnitRulPkg->FindItem(begin->tDPH.nID))
					{
						SetDLEH_EC(g_nErrRtn);
						WriteLogE("[%s] add policy sub rule pkg information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
						continue;
					}

					t_ManagePoFaOpUnitRulPkg->AddPoFaOpUnitRulPkg(*begin);
				}
			}
		}	

		{
			{
				TListDBPoFaOpUnitItor begin, end;
				begin = tUnitList.begin();	end = tUnitList.end();
				for(begin; begin != end; begin++)
				{
					if(t_ManagePoFaOpUnit->ApplyPoFaOpUnit(*begin))
					{
						SetDLEH_EC(g_nErrRtn);
						WriteLogE("[%s] apply policy unit information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
						continue;
					}
				}
			}

			{
				TListDBPoFaOpPkgItor begin, end;
				begin = tPkgList.begin();	end = tPkgList.end();
				for(begin; begin != end; begin++)
				{
					if(t_ManagePoFaOpPkg->FindItem(begin->tDPH.nID))
					{
						SetDLEH_EC(g_nErrRtn);
						WriteLogE("[%s] add policy pkg information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
						continue;
					}

					t_ManagePoFaOpPkg->AddPoFaOpPkg(*begin);
				}
			}

			if(SetER(t_ManagePoFaOp->ApplyPoFaOp(dpfo)))
			{
				SetDLEH_EC(g_nErrRtn);
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

INT32		CLogicMgrPoFaOp::IsExistSysOffSchByPoPwr()
{
	UINT32 nRet = 0;

	PDB_PO_FA_OP pdb_po = (PDB_PO_FA_OP)t_DeployPolicyUtil->GetCurPoPtr(m_nPolicyType);
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

		if(!pdb_po || pdb_po->tDPH.nUsedMode == STATUS_USED_MODE_OFF)
		{ 
			return 0;
		}

		U64_SCHEDULE tIS;
		tIS.all = pdb_po->nSchTime;	
		if(tIS.all == 0)	tIS.U8.type = SCHEDULE_PERIOD_TYPE_BOOT;

		if(tIS.U8.type == SCHEDULE_PERIOD_TYPE_SHUTDOWN_EXT)
		{
			nRet = 1;
		}
	}	
	return nRet;
}
//---------------------------------------------------------------------------


INT32		CLogicMgrPoFaOp::OnTimer_Logic()
{
	PDB_PO_FA_OP pdb_po = (PDB_PO_FA_OP)t_DeployPolicyUtil->GetCurPoPtr(m_nPolicyType);
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

INT32		CLogicMgrPoFaOp::ApplyPolicy_Sch()
{
	PDB_PO_FA_OP pdb_po = (PDB_PO_FA_OP)t_DeployPolicyUtil->GetCurPoPtr(m_nPolicyType);
	if(!pdb_po)	
	{
		WriteLogE("[%s] not find current policy", m_strLogicName.c_str());
		return 0;
	}
	
	UINT32 nLastChkTime = pdb_po->nScanTime;
	U64_SCHEDULE tIS;
	tIS.all = pdb_po->nSchTime;	
	if(tIS.all == 0)	tIS.U8.type = SCHEDULE_PERIOD_TYPE_BOOT;

	{
		MEM_ENV_NOTIFY_INFO_SCH menis;
		menis.nNotifyType = SS_POLICY_TYPE_FA_NOTIFY;
		menis.nPolType    = SS_POLICY_TYPE_FA_OP;
		menis.nOpType     = EVENT_OPERATION_TYPE_DEL;
		menis.nSchType	  = tIS.U8.type;

		menis.tDPH.nID    = pdb_po->tDPH.nID;

		if(!t_LogicMgrEnvNotifyInfo->IsValidSchduleNotify(nLastChkTime, tIS.all, menis))
			t_LogicEnvNotifyInfo->SendPkt_Notify_Sch_info(menis);
	}

	if(IsValidSchedule(tIS.all, nLastChkTime) == 0)
	{
		return -1;
	}

	WriteLogN("start(check) fa op schedule : [id:%d][%d.%d.%d.%d][%u][del_af_day:%d:%d]", pdb_po->tDPH.nID, 
 				tIS.U8.type, tIS.U8.value, tIS.U8.hour, tIS.U8.min, nLastChkTime, pdb_po->nChkFDTType, pdb_po->nChkFDTValue);
	t_ManageDocDeleteInfo->UpdateDocScanTime();

	pdb_po->nScanTime = nLastChkTime;
	if(pdb_po->tDPH.nID)	t_ManagePoFaOp->EditPoFaOp(*pdb_po);

	UINT32 nDelDocCnt = 0, nDelBkCnt = 0;
	nDelDocCnt = t_LogicMgrLogDoc->ChkBackupOp(pdb_po->nDelMethod, pdb_po->nDelCount, pdb_po->nLimitSize, pdb_po->nLimitCnt, pdb_po->nChkFDTType, pdb_po->nChkFDTValue, t_EnvInfoOp->GetStopOpBySysOff());
	nDelBkCnt  = t_LogicMgrLogDoc->ChkDelBackupOp(t_EnvInfoOp->GetStopOpBySysOff());
	t_DocBackupUtil->RemoveBackupFilesByNonExistLog(t_EnvInfoOp->GetStopOpBySysOff());

	{
		InitDLEH_Sync(pdb_po->tDPH.nID, pdb_po->tDPH.strName, EVENT_OPERATION_TYPE_SCHEDULE);
		AppendDLEDesc(SS_LOG_EVENT_HOST_DESC_KEY_START_TIME, nLastChkTime);
		AppendDLEDesc(SS_LOG_EVENT_HOST_DESC_KEY_DOC_DEL_CNT, nDelDocCnt);
		AppendDLEDesc(SS_LOG_EVENT_HOST_DESC_KEY_BK_DEL_CNT, nDelBkCnt);
		t_LogicMgrLogEvent->SetLogEvent(m_tDLE);
	}

	return 0;
}
//---------------------------------------------------------------------------

