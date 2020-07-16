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
#include "LogicMgrPoInRegSW.h"

//---------------------------------------------------------------------------

CLogicMgrPoInRegSW*		t_LogicMgrPoInRegSW = NULL;

//---------------------------------------------------------------------------

CLogicMgrPoInRegSW::CLogicMgrPoInRegSW()
{
	t_ManagePoInRegSW			= new CManagePoInRegSW();
	t_ManagePoInRegSWPkg		= new CManagePoInRegSWPkg();
	t_ManagePoInRegSWUnit		= new CManagePoInRegSWUnit();

	t_ManagePoInRegSWUnitObjPkg	= new CManagePoInRegSWUnitObjPkg();
	t_ManagePoInRegSWUnitSubPkg	= new CManagePoInRegSWUnitSubPkg();		

	t_ManagePoInRegSWObjUnit	= new CManagePoInRegSWObjUnit();
	t_ManagePoInRegSWSubUnit	= new CManagePoInRegSWSubUnit();	



	t_ManagePoInRegSW->LoadDBMS();
	t_ManagePoInRegSWPkg->LoadDBMS();
	t_ManagePoInRegSWUnit->LoadDBMS();

	t_ManagePoInRegSWUnitObjPkg->LoadDBMS();
	t_ManagePoInRegSWUnitSubPkg->LoadDBMS();		

	t_ManagePoInRegSWObjUnit->LoadDBMS();
	t_ManagePoInRegSWSubUnit->LoadDBMS();	

	{
		t_ManagePoInRegSWUnitObjPkg->InitPkg();
		t_ManagePoInRegSWUnitSubPkg->InitPkg();				
	}

	t_ManagePoInRegSW->InitHash();

	m_strLogicName		= "mgr agt po in reg sw";
	
	m_nPolicyType		= SS_POLICY_TYPE_IN_REG_SW;
	m_nSSPoSeqIdx		= SS_POLICY_INDEX_IN_REG_SW;

	m_nAgtPktEditCode	= G_CODE_COMMON_EDIT;	
	
	m_nEvtObjType		= EVENT_OBJECT_TYPE_POLICY;
	m_nEvtObjCode		= EVENT_OBJECT_CODE_POLICY_IN_REG_SW;
}
//---------------------------------------------------------------------------

CLogicMgrPoInRegSW::~CLogicMgrPoInRegSW()
{
	SAFE_DELETE(t_ManagePoInRegSWObjUnit);
	SAFE_DELETE(t_ManagePoInRegSWSubUnit);	

	SAFE_DELETE(t_ManagePoInRegSWUnitObjPkg);
	SAFE_DELETE(t_ManagePoInRegSWUnitSubPkg);		

	SAFE_DELETE(t_ManagePoInRegSWUnit);
	SAFE_DELETE(t_ManagePoInRegSWPkg);
	SAFE_DELETE(t_ManagePoInRegSW);

}
//---------------------------------------------------------------------------
INT32		CLogicMgrPoInRegSW::AnalyzePkt_FromMgr_Ext()
{
	return SetHdrAndRtn(AZPKT_CB_RTN_SUCCESS);
}
//---------------------------------------------------------------------------

INT32		CLogicMgrPoInRegSW::AnalyzePkt_FromMgr_Edit_Ext()
{
	PDB_PO_IN_REG_SW pdpirs = NULL;
	DB_PO_IN_REG_SW dpirs;

	m_tDPH = &(dpirs.tDPH);

	TListDBPoInRegSWPkg	tPkgList;
	TListDBPoInRegSWUnit	tUnitList;

	TListDBPoInRegSWUnitObjPkg	tObjPkgList;
	TListDBPoInRegSWUnitSubPkg	tSubPkgList;		

	TMapDBPoInRegSWObjUnit		tObjMap;
	TMapDBPoInRegSWSubUnit		tSubMap;	

	if( t_ManagePoInRegSW->GetPkt(RecvToken, dpirs))				return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
	if(!RecvToken.TokenDel_32(m_nRecvNum))						return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
	while(m_nRecvNum--)
	{
		DB_PO_IN_REG_SW_PKG	dpirsp;		
		DB_PO_IN_REG_SW_UNIT dpirsu;

		if( t_ManagePoInRegSWPkg->GetPkt(RecvToken, dpirsp))		return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
		if( t_ManagePoInRegSWUnit->GetPkt(RecvToken, dpirsu))		return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);

		{
			UINT32 nSubRecvNum = 0;
			if(!RecvToken.TokenDel_32(nSubRecvNum))				return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
			while(nSubRecvNum--)
			{
				DB_PO_IN_REG_SW_UNIT_SUB_PKG sub_pkg;
				DB_PO_IN_REG_SW_SUB_UNIT sub_unit;

				if( t_ManagePoInRegSWUnitSubPkg->GetPkt(RecvToken, sub_pkg))		return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
				if( t_ManagePoInRegSWSubUnit->GetPkt(RecvToken, sub_unit))			return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);

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
				DB_PO_IN_REG_SW_UNIT_OBJ_PKG sub_pkg;
				DB_PO_IN_REG_SW_OBJ_UNIT sub_unit;

				if( t_ManagePoInRegSWUnitObjPkg->GetPkt(RecvToken, sub_pkg))		return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
				if( t_ManagePoInRegSWObjUnit->GetPkt(RecvToken, sub_unit))			return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);

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

	pdpirs = (PDB_PO_IN_REG_SW)t_DeployPolicyUtil->GetCurPoPtr(m_nPolicyType);
	if(pdpirs)
	{
		t_ManagePoInRegSWPkg->ClearPkgUnitByPolicyID(pdpirs->tDPH.nID);		
		t_ManagePoInRegSW->DelPoInRegSW(pdpirs->tDPH.nID);
	}

	{
		{
			{
				TMapDBPoInRegSWSubUnitItor begin, end;
				begin = tSubMap.begin();	end = tSubMap.end();
				for(begin; begin != end; begin++)
				{
					if(t_ManagePoInRegSWSubUnit->ApplyPoInRegSWSubUnit(begin->second))
					{
						SetDLEA_EC(g_nErrRtn);
						WriteLogE("[%s] apply policy sub subject unit information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
						continue;
					}
				}
			}

			{
				TMapDBPoInRegSWObjUnitItor begin, end;
				begin = tObjMap.begin();	end = tObjMap.end();
				for(begin; begin != end; begin++)
				{
					if(t_ManagePoInRegSWObjUnit->ApplyPoInRegSWObjUnit(begin->second))
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
				TListDBPoInRegSWUnitSubPkgItor begin, end;
				begin = tSubPkgList.begin();	end = tSubPkgList.end();
				for(begin; begin != end; begin++)
				{
					if(t_ManagePoInRegSWUnitSubPkg->FindItem(begin->tDPH.nID))
					{
						SetDLEA_EC(g_nErrRtn);
						WriteLogE("[%s] add policy sub subject pkg information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
						continue;
					}

					t_ManagePoInRegSWUnitSubPkg->AddPoInRegSWUnitSubPkg(*begin);
				}
			}
			{
				TListDBPoInRegSWUnitObjPkgItor begin, end;
				begin = tObjPkgList.begin();	end = tObjPkgList.end();
				for(begin; begin != end; begin++)
				{
					if(t_ManagePoInRegSWUnitObjPkg->FindItem(begin->tDPH.nID))
					{
						SetDLEA_EC(g_nErrRtn);
						WriteLogE("[%s] add policy sub object pkg information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
						continue;
					}

					t_ManagePoInRegSWUnitObjPkg->AddPoInRegSWUnitObjPkg(*begin);
				}
			}						
		}	

		{
			{
				TListDBPoInRegSWUnitItor begin, end;
				begin = tUnitList.begin();	end = tUnitList.end();
				for(begin; begin != end; begin++)
				{
					if(t_ManagePoInRegSWUnit->ApplyPoInRegSWUnit(*begin))
					{
						SetDLEA_EC(g_nErrRtn);
						WriteLogE("[%s] apply policy unit information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
						continue;
					}
				}
			}

			{
				TListDBPoInRegSWPkgItor begin, end;
				begin = tPkgList.begin();	end = tPkgList.end();
				for(begin; begin != end; begin++)
				{
					if(t_ManagePoInRegSWPkg->FindItem(begin->tDPH.nID))
					{
						SetDLEA_EC(g_nErrRtn);
						WriteLogE("[%s] add policy pkg information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
						continue;
					}

					t_ManagePoInRegSWPkg->AddPoInRegSWPkg(*begin);
				}
			}

			if(SetER(t_ManagePoInRegSW->ApplyPoInRegSW(dpirs)))
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

