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
#include "LogicMgrPoInRegSys.h"

//---------------------------------------------------------------------------

CLogicMgrPoInRegSys*		t_LogicMgrPoInRegSys = NULL;

//---------------------------------------------------------------------------

CLogicMgrPoInRegSys::CLogicMgrPoInRegSys()
{
	t_ManagePoInRegSys		= new CManagePoInRegSys();
	t_ManagePoInRegSysPkg	= new CManagePoInRegSysPkg();
	t_ManagePoInRegSysUnit	= new CManagePoInRegSysUnit();

	t_ManagePoInRegSys->LoadDBMS();
	t_ManagePoInRegSysPkg->LoadDBMS();
	t_ManagePoInRegSysUnit->LoadDBMS();

	t_ManagePoInRegSys->InitHash();

	m_strLogicName		= "mgr agt po in reg sys";
	
	m_nPolicyType		= SS_POLICY_TYPE_IN_REG_SYS;
	m_nSSPoSeqIdx		= SS_POLICY_INDEX_IN_REG_SYS;
	m_nAgtPktEditCode	= G_CODE_COMMON_EDIT;
}
//---------------------------------------------------------------------------

CLogicMgrPoInRegSys::~CLogicMgrPoInRegSys()
{
	SAFE_DELETE(t_ManagePoInRegSys);
	SAFE_DELETE(t_ManagePoInRegSysPkg);
	SAFE_DELETE(t_ManagePoInRegSysUnit);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------


INT32		CLogicMgrPoInRegSys::AnalyzePkt_FromMgr_Ext()
{
	return SetHdrAndRtn(AZPKT_CB_RTN_SUCCESS);
}
//---------------------------------------------------------------------------

INT32		CLogicMgrPoInRegSys::AnalyzePkt_FromMgr_Edit_Ext()
{
	PDB_PO_IN_REG_SYS pdpirs = NULL;
	DB_PO_IN_REG_SYS dpirs;

	m_tDPH = &(dpirs.tDPH);

	TListDBPoInRegSysPkg		tPkgList;
	TListDBPoInRegSysUnit		tUnitList;

	if( t_ManagePoInRegSys->GetPkt(RecvToken, dpirs))				return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
	if(!RecvToken.TokenDel_32(m_nRecvNum))							return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
	while(m_nRecvNum--)
	{
		DB_PO_IN_REG_SYS_PKG	dpirsp;		
		DB_PO_IN_REG_SYS_UNIT dpirsu;

		if( t_ManagePoInRegSysPkg->GetPkt(RecvToken, dpirsp))		return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
		if( t_ManagePoInRegSysUnit->GetPkt(RecvToken, dpirsu))		return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);

		tPkgList.push_back(dpirsp);
		tUnitList.push_back(dpirsu);

		dpirs.tDPH._add_id(dpirsp.tDPH.nID);
	}

	pdpirs = (PDB_PO_IN_REG_SYS)t_DeployPolicyUtil->GetCurPoPtr(m_nPolicyType);
	if(pdpirs)
	{
		t_ManagePoInRegSysPkg->ClearItemByPolicyID(pdpirs->tDPH.nID);		
		t_ManagePoInRegSys->DelPoInRegSys(pdpirs->tDPH.nID);
	}

	{
		{
			TListDBPoInRegSysUnitItor begin, end;
			begin = tUnitList.begin();	end = tUnitList.end();
			for(begin; begin != end; begin++)
			{
				if(t_ManagePoInRegSysUnit->ApplyPoInRegSysUnit(*begin))
				{
					SetDLEA_EC(g_nErrRtn);
					WriteLogE("[%s] apply policy unit information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
					continue;
				}				
			}
		}

		{
			TListDBPoInRegSysPkgItor begin, end;
			begin = tPkgList.begin();	end = tPkgList.end();
			for(begin; begin != end; begin++)
			{
				if(t_ManagePoInRegSysPkg->FindItem(begin->tDPH.nID))
				{
					SetDLEA_EC(g_nErrRtn);
					WriteLogE("[%s] add policy pkg information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
					continue;
				}

				t_ManagePoInRegSysPkg->AddPoInRegSysPkg(*begin);
			}
		}

		if(SetER(t_ManagePoInRegSys->ApplyPoInRegSys(dpirs)))
		{
			SetDLEA_EC(g_nErrRtn);
			WriteLogE("[%s] apply policy information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
			return SetHdrAndRtn(AZPKT_CB_RTN_DBMS_FAIL);
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
