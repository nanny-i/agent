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
#include "LogicMgrPoInVulnOp.h"

//---------------------------------------------------------------------------

CLogicMgrPoInVulnOp*		t_LogicMgrPoInVulnOp = NULL;

//---------------------------------------------------------------------------

CLogicMgrPoInVulnOp::CLogicMgrPoInVulnOp()
{
	t_ManagePoInVulnOp			= new CManagePoInVulnOp();
	t_ManagePoInVulnOpPkg		= new CManagePoInVulnOpPkg();

	t_ManagePoInVulnOp->LoadDBMS();
	t_ManagePoInVulnOpPkg->LoadDBMS();

	t_ManagePoInVulnOp->InitHash();

	m_strLogicName		= "mgr agt po in vuln op";
	
	m_nPolicyType		= SS_POLICY_TYPE_IN_VULN_OP;
	m_nSSPoSeqIdx		= SS_POLICY_INDEX_IN_VULN_OP;
	m_nAgtPktEditCode	= G_CODE_COMMON_EDIT;	
	
	m_nEvtObjType		= EVENT_OBJECT_TYPE_POLICY;
	m_nEvtObjCode		= EVENT_OBJECT_CODE_POLICY_IN_VULN_OP;
}
//---------------------------------------------------------------------------

CLogicMgrPoInVulnOp::~CLogicMgrPoInVulnOp()
{
	SAFE_DELETE(t_ManagePoInVulnOp);
	SAFE_DELETE(t_ManagePoInVulnOpPkg);
}
//---------------------------------------------------------------------------
INT32		CLogicMgrPoInVulnOp::AnalyzePkt_FromMgr_Ext()
{
	return SetHdrAndRtn(AZPKT_CB_RTN_SUCCESS);
}
//---------------------------------------------------------------------------

INT32		CLogicMgrPoInVulnOp::AnalyzePkt_FromMgr_Edit_Ext()
{
	PDB_PO_IN_VULN_OP ppcp = NULL;
	DB_PO_IN_VULN_OP data;

	m_tDPH = &(data.tDPH);

	TListDBPoInVulnOpPkg	tPkgList;
	
	if( t_ManagePoInVulnOp->GetPkt(RecvToken, data))			return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
	if(!RecvToken.TokenDel_32(m_nRecvNum))						return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
	while(m_nRecvNum--)
	{
		DB_PO_IN_VULN_OP_PKG	dppp;			
		if( t_ManagePoInVulnOpPkg->GetPkt(RecvToken, dppp))		return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);	

		tPkgList.push_back(dppp);	
		data.tDPH._add_id(dppp.tDPH.nID);
	}

	ppcp = (PDB_PO_IN_VULN_OP)t_DeployPolicyUtil->GetCurPoPtr(m_nPolicyType);
	if(ppcp)
	{
		t_ManagePoInVulnOpPkg->ClearItemByPolicyID(ppcp->tDPH.nID);		
		t_ManagePoInVulnOp->DelPoInVulnOp(ppcp->tDPH.nID);
	}

	{
		{
			TListDBPoInVulnOpPkgItor begin, end;
			begin = tPkgList.begin();	end = tPkgList.end();
			for(begin; begin != end; begin++)
			{
				if(t_ManagePoInVulnOpPkg->FindItem(begin->tDPH.nID))
				{
					SetDLEA_EC(g_nErrRtn);
					WriteLogE("[%s] add policy pkg information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
					continue;
				}

				t_ManagePoInVulnOpPkg->AddPoInVulnOpPkg(*begin);
			}
		}

		if(SetER(t_ManagePoInVulnOp->ApplyPoInVulnOp(data)))
		{
			SetDLEA_EC(g_nErrRtn);
			WriteLogE("[%s] apply policy information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
			return SetHdrAndRtn(AZPKT_CB_RTN_DBMS_FAIL);
		}
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
