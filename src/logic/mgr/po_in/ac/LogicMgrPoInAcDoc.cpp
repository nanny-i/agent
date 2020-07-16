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
#include "LogicMgrPoInAcDoc.h"

//---------------------------------------------------------------------------

CLogicMgrPoInAcDoc*		t_LogicMgrPoInAcDoc = NULL;

//---------------------------------------------------------------------------

CLogicMgrPoInAcDoc::CLogicMgrPoInAcDoc()
{
	t_ManagePoInAcDoc			= new CManagePoInAcDoc();
	t_ManagePoInAcDocPkg		= new CManagePoInAcDocPkg();
	t_ManagePoInAcDocUnit		= new CManagePoInAcDocUnit();

	t_ManagePoInAcDocUnitObjPkg	= new CManagePoInAcDocUnitObjPkg();
	t_ManagePoInAcDocUnitSubPkg	= new CManagePoInAcDocUnitSubPkg();	

	t_ManagePoInAcDocObjUnit	= new CManagePoInAcDocObjUnit();
	t_ManagePoInAcDocSubUnit	= new CManagePoInAcDocSubUnit();

	t_ManagePoInAcDoc->LoadDBMS();
	t_ManagePoInAcDocPkg->LoadDBMS();
	t_ManagePoInAcDocUnit->LoadDBMS();

	t_ManagePoInAcDocUnitObjPkg->LoadDBMS();
	t_ManagePoInAcDocUnitSubPkg->LoadDBMS();	

	t_ManagePoInAcDocObjUnit->LoadDBMS();
	t_ManagePoInAcDocSubUnit->LoadDBMS();	

	{
		t_ManagePoInAcDocUnitObjPkg->InitPkg();
		t_ManagePoInAcDocUnitSubPkg->InitPkg();	
	}

	t_ManagePoInAcDoc->InitHash();

	m_strLogicName		= "mgr agt po in ac doc";
	
	m_nPolicyType		= SS_POLICY_TYPE_IN_AC_DOC;
	m_nSSPoSeqIdx		= SS_POLICY_INDEX_IN_AC_DOC;
	m_nAgtPktEditCode	= G_CODE_COMMON_EDIT;	
	
	m_nEvtObjType		= EVENT_OBJECT_TYPE_POLICY;
	m_nEvtObjCode		= EVENT_OBJECT_CODE_POLICY_IN_AC_DOC;
}
//---------------------------------------------------------------------------

CLogicMgrPoInAcDoc::~CLogicMgrPoInAcDoc()
{
	SAFE_DELETE(t_ManagePoInAcDocObjUnit);
	SAFE_DELETE(t_ManagePoInAcDocSubUnit);	

	SAFE_DELETE(t_ManagePoInAcDocUnitObjPkg);
	SAFE_DELETE(t_ManagePoInAcDocUnitSubPkg);	

	SAFE_DELETE(t_ManagePoInAcDocUnit);
	SAFE_DELETE(t_ManagePoInAcDocPkg);
	SAFE_DELETE(t_ManagePoInAcDoc);

}
//---------------------------------------------------------------------------
INT32		CLogicMgrPoInAcDoc::AnalyzePkt_FromMgr_Ext()
{
	return SetHdrAndRtn(AZPKT_CB_RTN_SUCCESS);
}
//---------------------------------------------------------------------------

INT32		CLogicMgrPoInAcDoc::AnalyzePkt_FromMgr_Edit_Ext()
{
	PDB_PO_IN_AC_DOC pdpiad = NULL;
	DB_PO_IN_AC_DOC dpiad;

	m_tDPH = &(dpiad.tDPH);

	TListDBPoInAcDocPkg	tPkgList;
	TListDBPoInAcDocUnit	tUnitList;

	TListDBPoInAcDocUnitObjPkg	tObjPkgList;
	TListDBPoInAcDocUnitSubPkg	tSubPkgList;	

	TMapDBPoInAcDocObjUnit		tObjMap;
	TMapDBPoInAcDocSubUnit		tSubMap;	

	if( t_ManagePoInAcDoc->GetPkt(RecvToken, dpiad))				return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
	if(!RecvToken.TokenDel_32(m_nRecvNum))						return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
	while(m_nRecvNum--)
	{
		DB_PO_IN_AC_DOC_PKG	dpiadp;		
		DB_PO_IN_AC_DOC_UNIT dpiadu;

		if( t_ManagePoInAcDocPkg->GetPkt(RecvToken, dpiadp))		return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
		if( t_ManagePoInAcDocUnit->GetPkt(RecvToken, dpiadu))		return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);

		{
			UINT32 nSubRecvNum = 0;
			if(!RecvToken.TokenDel_32(nSubRecvNum))				return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
			while(nSubRecvNum--)
			{
				DB_PO_IN_AC_DOC_UNIT_SUB_PKG sub_pkg;
				DB_PO_IN_AC_DOC_SUB_UNIT sub_unit;

				if( t_ManagePoInAcDocUnitSubPkg->GetPkt(RecvToken, sub_pkg))		return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
				if( t_ManagePoInAcDocSubUnit->GetPkt(RecvToken, sub_unit))			return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);

				tSubPkgList.push_back(sub_pkg);
				tSubMap[sub_unit.tDPH.nID] = sub_unit;

				dpiadu.tDPH._add_key_id_value(SS_PO_IN_AC_UNIT_KEY_TYPE_SUBJECT, sub_pkg.tDPH.nID, sub_unit.tDPH.nID);
			}
			RecvToken.TokenSkip_Block();
		}

		{
			UINT32 nSubRecvNum = 0;
			if(!RecvToken.TokenDel_32(nSubRecvNum))				return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
			while(nSubRecvNum--)
			{
				DB_PO_IN_AC_DOC_UNIT_OBJ_PKG sub_pkg;
				DB_PO_IN_AC_DOC_OBJ_UNIT sub_unit;

				if( t_ManagePoInAcDocUnitObjPkg->GetPkt(RecvToken, sub_pkg))		return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
				if( t_ManagePoInAcDocObjUnit->GetPkt(RecvToken, sub_unit))			return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);

				tObjPkgList.push_back(sub_pkg);
				tObjMap[sub_unit.tDPH.nID] = sub_unit;

				dpiadu.tDPH._add_key_id_value(SS_PO_IN_AC_UNIT_KEY_TYPE_OBJECT, sub_pkg.tDPH.nID, sub_unit.tDPH.nID);
			}
			RecvToken.TokenSkip_Block();
		}		
		RecvToken.TokenSkip_Block();	
		
		tPkgList.push_back(dpiadp);
		tUnitList.push_back(dpiadu);

		dpiad.tDPH._add_id(dpiadp.tDPH.nID);
	}

	pdpiad = (PDB_PO_IN_AC_DOC)t_DeployPolicyUtil->GetCurPoPtr(m_nPolicyType);
	if(pdpiad)
	{
		t_ManagePoInAcDocPkg->ClearPkgUnitByPolicyID(pdpiad->tDPH.nID);		
		t_ManagePoInAcDoc->DelPoInAcDoc(pdpiad->tDPH.nID);
	}

	{
		{
			{
				TMapDBPoInAcDocSubUnitItor begin, end;
				begin = tSubMap.begin();	end = tSubMap.end();
				for(begin; begin != end; begin++)
				{
					if(t_ManagePoInAcDocSubUnit->ApplyPoInAcDocSubUnit(begin->second))
					{
						SetDLEA_EC(g_nErrRtn);
						WriteLogE("[%s] apply policy sub subject unit information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
						continue;
					}
				}
			}

			{
				TMapDBPoInAcDocObjUnitItor begin, end;
				begin = tObjMap.begin();	end = tObjMap.end();
				for(begin; begin != end; begin++)
				{
					if(t_ManagePoInAcDocObjUnit->ApplyPoInAcDocObjUnit(begin->second))
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
				TListDBPoInAcDocUnitSubPkgItor begin, end;
				begin = tSubPkgList.begin();	end = tSubPkgList.end();
				for(begin; begin != end; begin++)
				{
					if(t_ManagePoInAcDocUnitSubPkg->FindItem(begin->tDPH.nID))
					{
						SetDLEA_EC(g_nErrRtn);
						WriteLogE("[%s] add policy sub subject pkg information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
						continue;
					}

					t_ManagePoInAcDocUnitSubPkg->AddPoInAcDocUnitSubPkg(*begin);
				}
			}
			{
				TListDBPoInAcDocUnitObjPkgItor begin, end;
				begin = tObjPkgList.begin();	end = tObjPkgList.end();
				for(begin; begin != end; begin++)
				{
					if(t_ManagePoInAcDocUnitObjPkg->FindItem(begin->tDPH.nID))
					{
						SetDLEA_EC(g_nErrRtn);
						WriteLogE("[%s] add policy sub object pkg information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
						continue;
					}

					t_ManagePoInAcDocUnitObjPkg->AddPoInAcDocUnitObjPkg(*begin);
				}
			}			
		}	

		{
			{
				TListDBPoInAcDocUnitItor begin, end;
				begin = tUnitList.begin();	end = tUnitList.end();
				for(begin; begin != end; begin++)
				{
					if(t_ManagePoInAcDocUnit->ApplyPoInAcDocUnit(*begin))
					{
						SetDLEA_EC(g_nErrRtn);
						WriteLogE("[%s] apply policy unit information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
						continue;
					}
				}
			}

			{
				TListDBPoInAcDocPkgItor begin, end;
				begin = tPkgList.begin();	end = tPkgList.end();
				for(begin; begin != end; begin++)
				{
					if(t_ManagePoInAcDocPkg->FindItem(begin->tDPH.nID))
					{
						SetDLEA_EC(g_nErrRtn);
						WriteLogE("[%s] add policy pkg information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
						continue;
					}

					t_ManagePoInAcDocPkg->AddPoInAcDocPkg(*begin);
				}
			}

			if(SetER(t_ManagePoInAcDoc->ApplyPoInAcDoc(dpiad)))
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

INT32		CLogicMgrPoInAcDoc::IsExistSysOffSchByPoPwr()
{
	UINT32 nRet = 0;

	PDB_PO_IN_AC_DOC pdb_po = (PDB_PO_IN_AC_DOC)t_DeployPolicyUtil->GetCurPoPtr(m_nPolicyType);
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


INT32		CLogicMgrPoInAcDoc::OnTimer_Logic()
{
	PDB_PO_IN_AC_DOC pdb_po = (PDB_PO_IN_AC_DOC)t_DeployPolicyUtil->GetCurPoPtr(m_nPolicyType);
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

INT32		CLogicMgrPoInAcDoc::ApplyPolicy_Sch()
{
	PDB_PO_IN_AC_DOC pdb_po = (PDB_PO_IN_AC_DOC)t_DeployPolicyUtil->GetCurPoPtr(m_nPolicyType);
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
// 		menis.nPolType    = SS_POLICY_TYPE_IN_AC_DOC;
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
// 	if(pdb_po->tDPH.nID)	t_ManagePoInAcDoc->EditPoInAcDoc(*pdb_po);
// 
// 	t_LogicMgrLogDoc->ChkBackupOp(pdb_po->nDelCount, pdb_po->nChkFDTType, pdb_po->nChkFDTValue);
// 	t_LogicMgrLogDoc->ChkDelBackupOp();
	
	return 0;
}
//---------------------------------------------------------------------------

