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
#include "LogicMgrPoInRegVuln.h"

//---------------------------------------------------------------------------

CLogicMgrPoInRegVuln*		t_LogicMgrPoInRegVuln = NULL;

//---------------------------------------------------------------------------

CLogicMgrPoInRegVuln::CLogicMgrPoInRegVuln()
{
	t_ManagePoInRegVuln		= new CManagePoInRegVuln();
	t_ManagePoInRegVulnPkg	= new CManagePoInRegVulnPkg();
	t_ManagePoInRegVulnUnit	= new CManagePoInRegVulnUnit();

	t_ManagePoInRegVuln->LoadDBMS();
	t_ManagePoInRegVulnPkg->LoadDBMS();
	t_ManagePoInRegVulnUnit->LoadDBMS();

	t_ManagePoInRegVuln->InitHash();

	m_strLogicName		= "mgr agt po in reg vuln";
	
	m_nPolicyType		= SS_POLICY_TYPE_IN_REG_VULN;
	m_nSSPoSeqIdx		= SS_POLICY_INDEX_IN_REG_VULN;
	m_nAgtPktEditCode	= G_CODE_COMMON_EDIT;
}
//---------------------------------------------------------------------------

CLogicMgrPoInRegVuln::~CLogicMgrPoInRegVuln()
{
	SAFE_DELETE(t_ManagePoInRegVuln);
	SAFE_DELETE(t_ManagePoInRegVulnPkg);
	SAFE_DELETE(t_ManagePoInRegVulnUnit);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------


INT32		CLogicMgrPoInRegVuln::AnalyzePkt_FromMgr_Ext()
{
	return SetHdrAndRtn(AZPKT_CB_RTN_SUCCESS);
}
//---------------------------------------------------------------------------

INT32		CLogicMgrPoInRegVuln::AnalyzePkt_FromMgr_Edit_Ext()
{
	PDB_PO_IN_REG_VULN pdpirv = NULL;
	DB_PO_IN_REG_VULN dpirv;

	m_tDPH = &(dpirv.tDPH);

	TListDBPoInRegVulnPkg		tPkgList;
	TListDBPoInRegVulnUnit		tUnitList;

	if( t_ManagePoInRegVuln->GetPkt(RecvToken, dpirv))				return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
	if(!RecvToken.TokenDel_32(m_nRecvNum))							return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
	while(m_nRecvNum--)
	{
		DB_PO_IN_REG_VULN_PKG	dpirvp;		
		DB_PO_IN_REG_VULN_UNIT dpirvu;

		if( t_ManagePoInRegVulnPkg->GetPkt(RecvToken, dpirvp))		return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
		if( t_ManagePoInRegVulnUnit->GetPkt(RecvToken, dpirvu))		return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);

		tPkgList.push_back(dpirvp);
		tUnitList.push_back(dpirvu);

		dpirv.tDPH._add_id(dpirvp.tDPH.nID);
	}

	pdpirv = (PDB_PO_IN_REG_VULN)t_DeployPolicyUtil->GetCurPoPtr(m_nPolicyType);
	if(pdpirv)
	{
		t_ManagePoInRegVulnPkg->ClearItemByPolicyID(pdpirv->tDPH.nID);		
		t_ManagePoInRegVuln->DelPoInRegVuln(pdpirv->tDPH.nID);
	}

	{
		{
			TListDBPoInRegVulnUnitItor begin, end;
			begin = tUnitList.begin();	end = tUnitList.end();
			for(begin; begin != end; begin++)
			{
				if(t_ManagePoInRegVulnUnit->ApplyPoInRegVulnUnit(*begin))
				{
					SetDLEA_EC(g_nErrRtn);
					WriteLogE("[%s] apply policy unit information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
					continue;
				}				
			}
		}

		{
			TListDBPoInRegVulnPkgItor begin, end;
			begin = tPkgList.begin();	end = tPkgList.end();
			for(begin; begin != end; begin++)
			{
				if(t_ManagePoInRegVulnPkg->FindItem(begin->tDPH.nID))
				{
					SetDLEA_EC(g_nErrRtn);
					WriteLogE("[%s] add policy pkg information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
					continue;
				}

				t_ManagePoInRegVulnPkg->AddPoInRegVulnPkg(*begin);
			}
		}

		if(SetER(t_ManagePoInRegVuln->ApplyPoInRegVuln(dpirv)))
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
