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
#include "LogicMgrPoDvLo.h"

//---------------------------------------------------------------------------

CLogicMgrPoDvLo*		t_LogicMgrPoDvLo = NULL;

//---------------------------------------------------------------------------

CLogicMgrPoDvLo::CLogicMgrPoDvLo()
{
	m_strLogicName = "mgr agt po dv lo";
	
	m_nEvtObjType	= EVENT_OBJECT_TYPE_HOST;
	m_nEvtObjCode	= 0;

	t_ManagePoDvDefault			= new CManagePoDvDefault();
	t_ManagePoDvDefault->LoadDBMS();
}
//---------------------------------------------------------------------------

CLogicMgrPoDvLo::~CLogicMgrPoDvLo()
{
	SAFE_DELETE(t_ManagePoDvDefault);
}
//---------------------------------------------------------------------------

INT32		CLogicMgrPoDvLo::AnalyzePkt_FromMgr_Ext()
{
	UINT32 nRtn = AZPKT_CB_RTN_SUCCESS;
	switch(m_nPktCode)
	{
		case G_CODE_COMMON_DRTADD:			nRtn = AnalyzePkt_FromMgr_Ext_DirectAdd();	break;
		case G_CODE_COMMON_DRTDEL:			nRtn = AnalyzePkt_FromMgr_Ext_DirectDel();	break;
		case G_CODE_COMMON_LOAD:			nRtn = AnalyzePkt_FromMgr_Ext_GetDvLo();	break;
		default:
		{	
			nRtn = AZPKT_CB_RTN_PKT_NOT_DEFINE_CODE;
			break;
		}
	}

	return SetHdrAndRtn(nRtn);
}
//---------------------------------------------------------------------------
INT32		CLogicMgrPoDvLo::AnalyzePkt_FromMgr_Ext_DirectAdd()
{
	SendToken.Clear();
	INT32 nConSessionID = 0, nCnt = 0, nRet = AZPKT_CB_RTN_SEND_ACK, nID = 0;
	String strDevName = "", strDvInstanceID = "", strDvPaInstanceID = "";

	if(!RecvToken.TokenDel_32(nConSessionID))					return AZPKT_CB_RTN_PKT_INVALID;
	if(!RecvToken.TokenDel_32(m_nHostID))						return AZPKT_CB_RTN_PKT_INVALID;
	if( RecvToken.TokenDel_String(strDevName) < 0)				return AZPKT_CB_RTN_PKT_INVALID;
	if( RecvToken.TokenDel_String(strDvInstanceID) < 0)			return AZPKT_CB_RTN_PKT_INVALID;
	if( RecvToken.TokenDel_String(strDvPaInstanceID) < 0)		return AZPKT_CB_RTN_PKT_INVALID;

	SendToken.TokenAdd_32(nConSessionID);
	SendToken.TokenAdd_32(m_nHostID);

	nID = t_ManagePoDvDefault->FindDvPolID(strDvInstanceID, strDvPaInstanceID);
	if(nID)
	{
		SendToken.TokenAdd_32(AZPKT_CB_RTN_SUCCESS);
		PDB_PO_DV_DEFAULT pData = t_ManagePoDvDefault->FindItem(nID);
		if(pData && pData->tDPH.nUsedMode == 0)
		{
			pData->tDPH.nUsedMode = 1;
			t_ManagePoDvDefault->EditPoDvDefault(*pData);
		}
		t_ManagePoDvDefault->SetPkt(nID, SendToken);
	}
	else
	{
		DB_PO_DV_DEFAULT ddd;
		ddd.tDPH.nUsedMode = 1;
		ddd.nPoPerm = RET_ALLOW;
		ddd.strDvName = strDevName;
		ddd.strDvInstanceID = strDvInstanceID;
		ddd.strDvPaInstanceID = strDvPaInstanceID;
		if(!t_ManagePoDvDefault->AddPoDvDefault(ddd))
		{
			SendToken.TokenAdd_32(AZPKT_CB_RTN_SUCCESS);
			t_ManagePoDvDefault->SetPkt(nID, SendToken);
			t_ManageDevOInfo->CheckDvPolicy(TRUE);
			t_ThreadTimer->t_TimerUtil.EnableTimer(TIMER_ID_POLICY_APPLY_EPS);
		}
		else
		{
			SendToken.TokenAdd_32(AZPKT_CB_RTN_RESULT_FAILED);
		}
	}
	return nRet;
}
//---------------------------------------------------------------------------
INT32		CLogicMgrPoDvLo::AnalyzePkt_FromMgr_Ext_DirectDel()
{
	SendToken.Clear();
	INT32 nConSessionID = 0, nCnt = 0, nID = 0, nRet = AZPKT_CB_RTN_SEND_ACK;

	if(!RecvToken.TokenDel_32(nConSessionID))	return AZPKT_CB_RTN_PKT_INVALID;
	if(!RecvToken.TokenDel_32(m_nHostID))		return AZPKT_CB_RTN_PKT_INVALID;
	if(!RecvToken.TokenDel_32(nID))				return AZPKT_CB_RTN_PKT_INVALID;

	if(nID)
	{
		SendToken.TokenAdd_32(nConSessionID);
		SendToken.TokenAdd_32(m_nHostID);
		SendToken.TokenAdd_32(nID);
		if(!t_ManagePoDvDefault->DeleteDvDefault(nID))
			SendToken.TokenAdd_32(AZPKT_CB_RTN_SUCCESS);
		else
			SendToken.TokenAdd_32(AZPKT_CB_RTN_RESULT_FAILED);
		SendData_Mgr(G_TYPE_PO_DV_LO, m_nPktCode, SendToken);
		SendToken.Clear();
		m_nHostID = 0;

		t_ManageDevOInfo->CheckDvPolicy();
		t_ThreadTimer->t_TimerUtil.EnableTimer(TIMER_ID_POLICY_APPLY_EPS);
	}
	else
	{
		SendToken.TokenAdd_32(nConSessionID);
		SendToken.TokenAdd_32(m_nHostID);
		SendToken.TokenAdd_32(nID);
		SendToken.TokenAdd_32(AZPKT_CB_RTN_RESULT_FAILED);
		SendData_Mgr(G_TYPE_PO_DV_LO, m_nPktCode, SendToken);
		SendToken.Clear();
		m_nHostID = 0;
	}

	return nRet;
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
INT32		CLogicMgrPoDvLo::AnalyzePkt_FromMgr_Ext_GetDvLo()
{
	SendToken.Clear();

	INT32 nConSessionID = 0, nCnt = 0;

	if(!RecvToken.TokenDel_32(nConSessionID))		return AZPKT_CB_RTN_PKT_INVALID;
	if(!RecvToken.TokenDel_32(m_nHostID))			return AZPKT_CB_RTN_PKT_INVALID;
	
	SendToken.TokenAdd_32(nConSessionID);
	SendToken.TokenAdd_32(m_nHostID);

	t_ManagePoDvDefault->SetPkt(SendToken, TRUE);

	SendData_Mgr(G_TYPE_PO_DV_LO, m_nPktCode, SendToken);
	SendToken.Clear();
	m_nHostID = 0;

	return AZPKT_CB_RTN_SUCCESS_END;
}
//---------------------------------------------------------------------------