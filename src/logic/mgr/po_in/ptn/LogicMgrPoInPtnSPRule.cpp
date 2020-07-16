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
#include "LogicMgrPoInPtnSPRule.h"

//---------------------------------------------------------------------------

CLogicMgrPoInPtnSPRule*		t_LogicMgrPoInPtnSPRule = NULL;

//---------------------------------------------------------------------------

CLogicMgrPoInPtnSPRule::CLogicMgrPoInPtnSPRule()
{
	t_LogicPoInPtnSPRule		= new CLogicPoInPtnSPRule();
	t_ManagePoInPtnSPRule		= new CManagePoInPtnSPRule();
	
	t_ManagePoInPtnSPRule->LoadDBMS();
	
	t_ManagePoInPtnSPRule->InitHash();

	m_strLogicName		= "mgr agt po in ptn sp rule";
	
	m_nPolicyUnitType	= SS_POLICY_UNIT_TYPE_IN_PTN_SP_RULE;
	m_nSSPoSeqIdx		= SS_POLICY_INDEX_IN_PTN_SP;
	m_nAgtPktEditCode	= G_CODE_COMMON_EDIT;	
	
	m_nEvtObjType		= EVENT_OBJECT_TYPE_POLICY_UNIT;
	m_nEvtObjCode		= EVENT_OBJECT_CODE_POLICY_UNIT_IN_PTN_SP_RULE;
}
//---------------------------------------------------------------------------

CLogicMgrPoInPtnSPRule::~CLogicMgrPoInPtnSPRule()
{
	SAFE_DELETE(t_ManagePoInPtnSPRule);

	SAFE_DELETE(t_LogicPoInPtnSPRule);
}
//---------------------------------------------------------------------------
INT32		CLogicMgrPoInPtnSPRule::AnalyzePkt_FromMgr_Ext()
{
	return SetHdrAndRtn(AZPKT_CB_RTN_SUCCESS);
}
//---------------------------------------------------------------------------

INT32		CLogicMgrPoInPtnSPRule::AnalyzePkt_FromMgr_Edit_Ext()
{	
	TListDBPoInPtnSPRule	tRuleList;

	if(!RecvToken.TokenDel_32(m_nRecvNum))						return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
	while(m_nRecvNum--)
	{
		DB_PO_IN_PTN_SP_RULE		data;	

		if( t_ManagePoInPtnSPRule->GetPkt(RecvToken, data))		return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);

		tRuleList.push_back(data);
	}

	{
		TListID tIDList;
		t_ManagePoInPtnSPRule->GetItemIDList(tIDList);
		TListIDItor begin, end;
		begin = tIDList.begin();	end = tIDList.end();
		for(begin; begin != end; begin++)
		{
			if(t_ManagePoInPtnSPRule->IsExistID(*begin, tRuleList))		continue;

			t_ManagePoInPtnSPRule->DelPoInPtnSPRule(*begin);
		}
	}

	{
		TListDBPoInPtnSPRuleItor begin, end;
		begin = tRuleList.begin();	end = tRuleList.end();
		for(begin; begin != end; begin++)
		{
			if(t_ManagePoInPtnSPRule->ApplyPoInPtnSPRule(*begin))
			{
				SetDLEA_EC(g_nErrRtn);
				WriteLogE("[%s] apply policy unit information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
				continue;
			}
		}

		t_ManagePoInPtnSPRule->InitHash();
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

void		CLogicMgrPoInPtnSPRule::SendPkt_Req(PDB_PO_IN_PTN_SP_RULE pdata)
{	
	SendToken.Clear();
	t_ManagePoInPtnSPRule->SetPkt(pdata, SendToken);
	SendData(G_TYPE_PO_IN_PTN_SP_RULE, G_CODE_COMMON_REQUEST, SendToken);
	SendToken.Clear();
	return;
}
//---------------------------------------------------------------------------
