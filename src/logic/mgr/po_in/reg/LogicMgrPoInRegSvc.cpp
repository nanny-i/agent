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
#include "LogicMgrPoInRegSvc.h"

//---------------------------------------------------------------------------

CLogicMgrPoInRegSvc*		t_LogicMgrPoInRegSvc = NULL;

//---------------------------------------------------------------------------

CLogicMgrPoInRegSvc::CLogicMgrPoInRegSvc()
{
	t_ManagePoInRegSvc			= new CManagePoInRegSvc();
	t_ManagePoInRegSvcPkg		= new CManagePoInRegSvcPkg();
	t_ManagePoInRegSvcUnit		= new CManagePoInRegSvcUnit();

	t_ManagePoInRegSvcUnitObjPkg	= new CManagePoInRegSvcUnitObjPkg();
	t_ManagePoInRegSvcUnitSubPkg	= new CManagePoInRegSvcUnitSubPkg();		

	t_ManagePoInRegSvcObjUnit	= new CManagePoInRegSvcObjUnit();
	t_ManagePoInRegSvcSubUnit	= new CManagePoInRegSvcSubUnit();	



	t_ManagePoInRegSvc->LoadDBMS();
	t_ManagePoInRegSvcPkg->LoadDBMS();
	t_ManagePoInRegSvcUnit->LoadDBMS();

	t_ManagePoInRegSvcUnitObjPkg->LoadDBMS();
	t_ManagePoInRegSvcUnitSubPkg->LoadDBMS();		

	t_ManagePoInRegSvcObjUnit->LoadDBMS();
	t_ManagePoInRegSvcSubUnit->LoadDBMS();	

	{
		t_ManagePoInRegSvcUnitObjPkg->InitPkg();
		t_ManagePoInRegSvcUnitSubPkg->InitPkg();				
	}

	t_ManagePoInRegSvc->InitHash();

	m_strLogicName		= "mgr agt po in reg svc";
	
	m_nPolicyType		= SS_POLICY_TYPE_IN_REG_SVC;
	m_nSSPoSeqIdx		= SS_POLICY_INDEX_IN_REG_SVC;
	m_nAgtPktEditCode	= G_CODE_COMMON_EDIT;	
	
	m_nEvtObjType		= EVENT_OBJECT_TYPE_POLICY;
	m_nEvtObjCode		= EVENT_OBJECT_CODE_POLICY_IN_REG_SVC;
}
//---------------------------------------------------------------------------

CLogicMgrPoInRegSvc::~CLogicMgrPoInRegSvc()
{
	SAFE_DELETE(t_ManagePoInRegSvcObjUnit);
	SAFE_DELETE(t_ManagePoInRegSvcSubUnit);	

	SAFE_DELETE(t_ManagePoInRegSvcUnitObjPkg);
	SAFE_DELETE(t_ManagePoInRegSvcUnitSubPkg);		

	SAFE_DELETE(t_ManagePoInRegSvcUnit);
	SAFE_DELETE(t_ManagePoInRegSvcPkg);
	SAFE_DELETE(t_ManagePoInRegSvc);

}
//---------------------------------------------------------------------------
INT32		CLogicMgrPoInRegSvc::AnalyzePkt_FromMgr_Ext()
{
	return SetHdrAndRtn(AZPKT_CB_RTN_SUCCESS);
}
//---------------------------------------------------------------------------

INT32		CLogicMgrPoInRegSvc::AnalyzePkt_FromMgr_Edit_Ext()
{
	PDB_PO_IN_REG_SVC pdpirs = NULL;
	DB_PO_IN_REG_SVC dpirs;

	m_tDPH = &(dpirs.tDPH);

	TListDBPoInRegSvcPkg	tPkgList;
	TListDBPoInRegSvcUnit	tUnitList;

	TListDBPoInRegSvcUnitObjPkg	tObjPkgList;
	TListDBPoInRegSvcUnitSubPkg	tSubPkgList;		

	TMapDBPoInRegSvcObjUnit		tObjMap;
	TMapDBPoInRegSvcSubUnit		tSubMap;	

	if( t_ManagePoInRegSvc->GetPkt(RecvToken, dpirs))				return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
	if(!RecvToken.TokenDel_32(m_nRecvNum))						return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
	while(m_nRecvNum--)
	{
		DB_PO_IN_REG_SVC_PKG	dpirsp;		
		DB_PO_IN_REG_SVC_UNIT dpirsu;

		if( t_ManagePoInRegSvcPkg->GetPkt(RecvToken, dpirsp))		return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
		if( t_ManagePoInRegSvcUnit->GetPkt(RecvToken, dpirsu))		return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);

		{
			UINT32 nSubRecvNum = 0;
			if(!RecvToken.TokenDel_32(nSubRecvNum))				return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
			while(nSubRecvNum--)
			{
				DB_PO_IN_REG_SVC_UNIT_SUB_PKG sub_pkg;
				DB_PO_IN_REG_SVC_SUB_UNIT sub_unit;

				if( t_ManagePoInRegSvcUnitSubPkg->GetPkt(RecvToken, sub_pkg))		return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
				if( t_ManagePoInRegSvcSubUnit->GetPkt(RecvToken, sub_unit))			return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);

				tSubPkgList.push_back(sub_pkg);
				tSubMap[sub_unit.tDPH.nID] = sub_unit;

				dpirsu.tDPH._add_key_id_value(SS_PO_IN_REG_UNIT_KEY_TYPE_SUBJECT, sub_pkg.tDPH.nID, sub_unit.tDPH.nID);
			}
			RecvToken.TokenSkip_Block();
		}

		{
			UINT32 nSubRecvNum = 0;
			if(!RecvToken.TokenDel_32(nSubRecvNum))				return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
			while(nSubRecvNum--)
			{
				DB_PO_IN_REG_SVC_UNIT_OBJ_PKG sub_pkg;
				DB_PO_IN_REG_SVC_OBJ_UNIT sub_unit;

				if( t_ManagePoInRegSvcUnitObjPkg->GetPkt(RecvToken, sub_pkg))		return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
				if( t_ManagePoInRegSvcObjUnit->GetPkt(RecvToken, sub_unit))			return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);

				tObjPkgList.push_back(sub_pkg);
				tObjMap[sub_unit.tDPH.nID] = sub_unit;

				dpirsu.tDPH._add_key_id_value(SS_PO_IN_REG_UNIT_KEY_TYPE_OBJECT, sub_pkg.tDPH.nID, sub_unit.tDPH.nID);
			}
			RecvToken.TokenSkip_Block();
		}		
			
		RecvToken.TokenSkip_Block();	
		
		tPkgList.push_back(dpirsp);
		tUnitList.push_back(dpirsu);

		dpirs.tDPH._add_id(dpirsp.tDPH.nID);
	}

	pdpirs = (PDB_PO_IN_REG_SVC)t_DeployPolicyUtil->GetCurPoPtr(m_nPolicyType);
	if(pdpirs)
	{
		t_ManagePoInRegSvcPkg->ClearPkgUnitByPolicyID(pdpirs->tDPH.nID);		
		t_ManagePoInRegSvc->DelPoInRegSvc(pdpirs->tDPH.nID);
	}

	{
		{
			{
				TMapDBPoInRegSvcSubUnitItor begin, end;
				begin = tSubMap.begin();	end = tSubMap.end();
				for(begin; begin != end; begin++)
				{
					if(t_ManagePoInRegSvcSubUnit->ApplyPoInRegSvcSubUnit(begin->second))
					{
						SetDLEA_EC(g_nErrRtn);
						WriteLogE("[%s] apply policy sub subject unit information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
						continue;
					}
				}
			}

			{
				TMapDBPoInRegSvcObjUnitItor begin, end;
				begin = tObjMap.begin();	end = tObjMap.end();
				for(begin; begin != end; begin++)
				{
					if(t_ManagePoInRegSvcObjUnit->ApplyPoInRegSvcObjUnit(begin->second))
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
				TListDBPoInRegSvcUnitSubPkgItor begin, end;
				begin = tSubPkgList.begin();	end = tSubPkgList.end();
				for(begin; begin != end; begin++)
				{
					if(t_ManagePoInRegSvcUnitSubPkg->FindItem(begin->tDPH.nID))
					{
						SetDLEA_EC(g_nErrRtn);
						WriteLogE("[%s] add policy sub subject pkg information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
						continue;
					}

					t_ManagePoInRegSvcUnitSubPkg->AddPoInRegSvcUnitSubPkg(*begin);
				}
			}
			{
				TListDBPoInRegSvcUnitObjPkgItor begin, end;
				begin = tObjPkgList.begin();	end = tObjPkgList.end();
				for(begin; begin != end; begin++)
				{
					if(t_ManagePoInRegSvcUnitObjPkg->FindItem(begin->tDPH.nID))
					{
						SetDLEA_EC(g_nErrRtn);
						WriteLogE("[%s] add policy sub object pkg information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
						continue;
					}

					t_ManagePoInRegSvcUnitObjPkg->AddPoInRegSvcUnitObjPkg(*begin);
				}
			}						
		}	

		{
			{
				TListDBPoInRegSvcUnitItor begin, end;
				begin = tUnitList.begin();	end = tUnitList.end();
				for(begin; begin != end; begin++)
				{
					if(t_ManagePoInRegSvcUnit->ApplyPoInRegSvcUnit(*begin))
					{
						SetDLEA_EC(g_nErrRtn);
						WriteLogE("[%s] apply policy unit information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
						continue;
					}
				}
			}

			{
				TListDBPoInRegSvcPkgItor begin, end;
				begin = tPkgList.begin();	end = tPkgList.end();
				for(begin; begin != end; begin++)
				{
					if(t_ManagePoInRegSvcPkg->FindItem(begin->tDPH.nID))
					{
						SetDLEA_EC(g_nErrRtn);
						WriteLogE("[%s] add policy pkg information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
						continue;
					}

					t_ManagePoInRegSvcPkg->AddPoInRegSvcPkg(*begin);
				}
			}

			if(SetER(t_ManagePoInRegSvc->ApplyPoInRegSvc(dpirs)))
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
//---------------------------------------------------------------------------

