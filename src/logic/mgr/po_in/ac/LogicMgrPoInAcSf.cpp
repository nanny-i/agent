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
#include "LogicMgrPoInAcSf.h"

//---------------------------------------------------------------------------

CLogicMgrPoInAcSf*		t_LogicMgrPoInAcSf = NULL;

//---------------------------------------------------------------------------

CLogicMgrPoInAcSf::CLogicMgrPoInAcSf()
{
	t_ManagePoInAcSf			= new CManagePoInAcSf();
	t_ManagePoInAcSfPkg		= new CManagePoInAcSfPkg();
	t_ManagePoInAcSfUnit		= new CManagePoInAcSfUnit();

	t_ManagePoInAcSfUnitObjPkg	= new CManagePoInAcSfUnitObjPkg();
	t_ManagePoInAcSfUnitSubPkg	= new CManagePoInAcSfUnitSubPkg();	

	t_ManagePoInAcSfObjUnit	= new CManagePoInAcSfObjUnit();
	t_ManagePoInAcSfSubUnit	= new CManagePoInAcSfSubUnit();

	t_ManagePoInAcSf->LoadDBMS();
	t_ManagePoInAcSfPkg->LoadDBMS();
	t_ManagePoInAcSfUnit->LoadDBMS();

	t_ManagePoInAcSfUnitObjPkg->LoadDBMS();
	t_ManagePoInAcSfUnitSubPkg->LoadDBMS();	

	t_ManagePoInAcSfObjUnit->LoadDBMS();
	t_ManagePoInAcSfSubUnit->LoadDBMS();	

	{
		t_ManagePoInAcSfUnitObjPkg->InitPkg();
		t_ManagePoInAcSfUnitSubPkg->InitPkg();		
	}

	t_ManagePoInAcSf->InitHash();

	m_strLogicName		= "mgr agt po in ac sf";
	
	m_nPolicyType		= SS_POLICY_TYPE_IN_AC_SF;
	m_nSSPoSeqIdx		= SS_POLICY_INDEX_IN_AC_SF;
	m_nAgtPktEditCode	= G_CODE_COMMON_EDIT;	
	
	m_nEvtObjType		= EVENT_OBJECT_TYPE_POLICY;
	m_nEvtObjCode		= EVENT_OBJECT_CODE_POLICY_IN_AC_SF;
}
//---------------------------------------------------------------------------

CLogicMgrPoInAcSf::~CLogicMgrPoInAcSf()
{
	SAFE_DELETE(t_ManagePoInAcSfObjUnit);
	SAFE_DELETE(t_ManagePoInAcSfSubUnit);	

	SAFE_DELETE(t_ManagePoInAcSfUnitObjPkg);
	SAFE_DELETE(t_ManagePoInAcSfUnitSubPkg);	

	SAFE_DELETE(t_ManagePoInAcSfUnit);
	SAFE_DELETE(t_ManagePoInAcSfPkg);
	SAFE_DELETE(t_ManagePoInAcSf);

}
//---------------------------------------------------------------------------
INT32		CLogicMgrPoInAcSf::AnalyzePkt_FromMgr_Ext()
{
	return SetHdrAndRtn(AZPKT_CB_RTN_SUCCESS);
}
//---------------------------------------------------------------------------

INT32		CLogicMgrPoInAcSf::AnalyzePkt_FromMgr_Edit_Ext()
{
	PDB_PO_IN_AC_SF pdpiaf = NULL;
	DB_PO_IN_AC_SF dpiaf;

	m_tDPH = &(dpiaf.tDPH);

	TListDBPoInAcSfPkg	tPkgList;
	TListDBPoInAcSfUnit	tUnitList;

	TListDBPoInAcSfUnitObjPkg	tObjPkgList;
	TListDBPoInAcSfUnitSubPkg	tSubPkgList;

	TMapDBPoInAcSfObjUnit		tObjMap;
	TMapDBPoInAcSfSubUnit		tSubMap;	

	if( t_ManagePoInAcSf->GetPkt(RecvToken, dpiaf))
		return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
	if(!RecvToken.TokenDel_32(m_nRecvNum))
		return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
	while(m_nRecvNum--)
	{
		DB_PO_IN_AC_SF_PKG	dpiafp;		
		DB_PO_IN_AC_SF_UNIT dpiafu;

		if( t_ManagePoInAcSfPkg->GetPkt(RecvToken, dpiafp))
			return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
		if( t_ManagePoInAcSfUnit->GetPkt(RecvToken, dpiafu))
			return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);

		{
			UINT32 nSubRecvNum = 0;
			if(!RecvToken.TokenDel_32(nSubRecvNum))
				return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
			while(nSubRecvNum--)
			{
				DB_PO_IN_AC_SF_UNIT_SUB_PKG sub_pkg;
				DB_PO_IN_AC_SF_SUB_UNIT sub_unit;

				if( t_ManagePoInAcSfUnitSubPkg->GetPkt(RecvToken, sub_pkg))
					return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
				if( t_ManagePoInAcSfSubUnit->GetPkt(RecvToken, sub_unit))
					return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);

				tSubPkgList.push_back(sub_pkg);
				tSubMap[sub_unit.tDPH.nID] = sub_unit;

				dpiafu.tDPH._add_key_id_value(SS_PO_IN_AC_UNIT_KEY_TYPE_SUBJECT, sub_pkg.tDPH.nID, sub_unit.tDPH.nID);
			}
			RecvToken.TokenSkip_Block();
		}

		{
			UINT32 nSubRecvNum = 0;
			if(!RecvToken.TokenDel_32(nSubRecvNum))
				return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
			while(nSubRecvNum--)
			{
				DB_PO_IN_AC_SF_UNIT_OBJ_PKG sub_pkg;
				DB_PO_IN_AC_SF_OBJ_UNIT sub_unit;

				if( t_ManagePoInAcSfUnitObjPkg->GetPkt(RecvToken, sub_pkg))
					return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
				if( t_ManagePoInAcSfObjUnit->GetPkt(RecvToken, sub_unit))
					return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);

				tObjPkgList.push_back(sub_pkg);
				tObjMap[sub_unit.tDPH.nID] = sub_unit;

				dpiafu.tDPH._add_key_id_value(SS_PO_IN_AC_UNIT_KEY_TYPE_OBJECT, sub_pkg.tDPH.nID, sub_unit.tDPH.nID);
			}
			RecvToken.TokenSkip_Block();
		}		
		RecvToken.TokenSkip_Block();	
		
		tPkgList.push_back(dpiafp);
		tUnitList.push_back(dpiafu);

		dpiaf.tDPH._add_id(dpiafp.tDPH.nID);
	}

	pdpiaf = (PDB_PO_IN_AC_SF)t_DeployPolicyUtil->GetCurPoPtr(m_nPolicyType);
	if(pdpiaf)
	{
		t_ManagePoInAcSfPkg->ClearPkgUnitByPolicyID(pdpiaf->tDPH.nID);		
		t_ManagePoInAcSf->DelPoInAcSf(pdpiaf->tDPH.nID);
	}

	{
		{
			{
				TMapDBPoInAcSfSubUnitItor begin, end;
				begin = tSubMap.begin();	end = tSubMap.end();
				for(begin; begin != end; begin++)
				{
					if(t_ManagePoInAcSfSubUnit->ApplyPoInAcSfSubUnit(begin->second))
					{
						SetDLEA_EC(g_nErrRtn);
						WriteLogE("[%s] apply policy sub subject unit information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
						continue;
					}
				}
			}

			{
				TMapDBPoInAcSfObjUnitItor begin, end;
				begin = tObjMap.begin();	end = tObjMap.end();
				for(begin; begin != end; begin++)
				{
					if(t_ManagePoInAcSfObjUnit->ApplyPoInAcSfObjUnit(begin->second))
					{
						SetDLEA_EC(g_nErrRtn);
						WriteLogE("[%s] apply policy sub object unit information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
						continue;
					}
				}
			}			
		}

		{
			{
				TListDBPoInAcSfUnitSubPkgItor begin, end;
				begin = tSubPkgList.begin();	end = tSubPkgList.end();
				for(begin; begin != end; begin++)
				{
					if(t_ManagePoInAcSfUnitSubPkg->FindItem(begin->tDPH.nID))
					{
						SetDLEA_EC(g_nErrRtn);
						WriteLogE("[%s] add policy sub subject pkg information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
						continue;
					}

					t_ManagePoInAcSfUnitSubPkg->AddPoInAcSfUnitSubPkg(*begin);
				}
			}
			{
				TListDBPoInAcSfUnitObjPkgItor begin, end;
				begin = tObjPkgList.begin();	end = tObjPkgList.end();
				for(begin; begin != end; begin++)
				{
					if(t_ManagePoInAcSfUnitObjPkg->FindItem(begin->tDPH.nID))
					{
						SetDLEA_EC(g_nErrRtn);
						WriteLogE("[%s] add policy sub object pkg information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
						continue;
					}

					t_ManagePoInAcSfUnitObjPkg->AddPoInAcSfUnitObjPkg(*begin);
				}
			}			
		}	

		{
			{
				TListDBPoInAcSfUnitItor begin, end;
				begin = tUnitList.begin();	end = tUnitList.end();
				for(begin; begin != end; begin++)
				{
					if(t_ManagePoInAcSfUnit->ApplyPoInAcSfUnit(*begin))
					{
						SetDLEA_EC(g_nErrRtn);
						WriteLogE("[%s] apply policy unit information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
						continue;
					}
				}
			}

			{
				TListDBPoInAcSfPkgItor begin, end;
				begin = tPkgList.begin();	end = tPkgList.end();
				for(begin; begin != end; begin++)
				{
					if(t_ManagePoInAcSfPkg->FindItem(begin->tDPH.nID))
					{
						SetDLEA_EC(g_nErrRtn);
						WriteLogE("[%s] add policy pkg information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
						continue;
					}

					t_ManagePoInAcSfPkg->AddPoInAcSfPkg(*begin);
				}
			}

			if(SetER(t_ManagePoInAcSf->ApplyPoInAcSf(dpiaf)))
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

INT32		CLogicMgrPoInAcSf::IsExistSysOffSchByPoPwr()
{
	UINT32 nRet = 0;

	PDB_PO_IN_AC_SF pdb_po = (PDB_PO_IN_AC_SF)t_DeployPolicyUtil->GetCurPoPtr(m_nPolicyType);
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


INT32		CLogicMgrPoInAcSf::OnTimer_Logic()
{
	PDB_PO_IN_AC_SF pdb_po = (PDB_PO_IN_AC_SF)t_DeployPolicyUtil->GetCurPoPtr(m_nPolicyType);
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

INT32		CLogicMgrPoInAcSf::ApplyPolicy_Sch()
{
	PDB_PO_IN_AC_SF pdb_po = (PDB_PO_IN_AC_SF)t_DeployPolicyUtil->GetCurPoPtr(m_nPolicyType);
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
// 		menis.nPolType    = SS_POLICY_TYPE_IN_AC_SF;
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
// 	if(pdb_po->tDPH.nID)	t_ManagePoInAcSf->EditPoInAcSf(*pdb_po);
// 
// 	t_LogicMgrLogDoc->ChkBackupOp(pdb_po->nDelCount, pdb_po->nChkFDTType, pdb_po->nChkFDTValue);
// 	t_LogicMgrLogDoc->ChkDelBackupOp();
	
	return 0;
}
//---------------------------------------------------------------------------

