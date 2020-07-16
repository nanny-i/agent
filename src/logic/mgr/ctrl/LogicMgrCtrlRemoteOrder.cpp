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
#include "LogicMgrCtrlRemoteOrder.h"
//---------------------------------------------------------------------------

CLogicMgrCtrlRemoteOrder*		t_LogicMgrCtrlRemoteOrder = NULL;

//---------------------------------------------------------------------------

CLogicMgrCtrlRemoteOrder::CLogicMgrCtrlRemoteOrder()
{
	m_strLogicName		= "ctrl remote control";

	m_nControlType		= SS_CONTROL_TYPE_CONTROL_REMOTE_ORDER;
	m_nEvtSubType		= EVENT_SUBJECT_TYPE_ADMIN;
	m_nEvtObjType		= EVENT_OBJECT_TYPE_HOST;
	m_nEvtObjCode		= EVENT_OBJECT_CODE_HOST_CTRL_REMOTE_REQUEST;
}
//---------------------------------------------------------------------------

CLogicMgrCtrlRemoteOrder::~CLogicMgrCtrlRemoteOrder()
{
}
//---------------------------------------------------------------------------

INT32		CLogicMgrCtrlRemoteOrder::AnalyzePkt_FromMgr_Ext()
{
	UINT32 nRtn = AZPKT_CB_RTN_SUCCESS;
	switch(m_nPktCode)
	{
		case G_CODE_COMMON_CTRL:		nRtn = AnalyzePkt_FromMgr_Ext_Ctrl();			break;
		default:
		{
			nRtn = AZPKT_CB_RTN_PKT_NOT_DEFINE_CODE;
			break;
		}
	}

	return SetHdrAndRtn(nRtn);
}
//---------------------------------------------------------------------------

INT32		CLogicMgrCtrlRemoteOrder::AnalyzePkt_FromMgr_Ext_Ctrl()
{
	MEM_CTRL_REMOTE_ORDER tMCRO;
	
	if(!RecvToken.TokenDel_32(tMCRO.nType))					return AZPKT_CB_RTN_PKT_INVALID;
	if(!RecvToken.TokenDel_32(tMCRO.nSubGroup))				return AZPKT_CB_RTN_PKT_INVALID;
	if(!RecvToken.TokenDel_32(tMCRO.nOption))				return AZPKT_CB_RTN_PKT_INVALID;
	if( RecvToken.TokenDel_String(tMCRO.strValue) < 0)		return AZPKT_CB_RTN_PKT_INVALID;

	if( RecvToken.TokenDel_IDMap(tMCRO.tValueMap) < 0)		return AZPKT_CB_RTN_PKT_INVALID;
	if( RecvToken.TokenDel_StrMap(tMCRO.tStrValueMap) < 0)	return AZPKT_CB_RTN_PKT_INVALID;

	RecvToken.TokenSkip_Block();

	ApplyRemotePolicy(&tMCRO); 

	return AZPKT_CB_RTN_SUCCESS;
}
//---------------------------------------------------------------------------

INT32		CLogicMgrCtrlRemoteOrder::ApplyRemotePolicy(PMEM_CTRL_REMOTE_ORDER pMCRO)
{
	INT32 nRtn = 0;
	m_nEvtOpType = EVENT_OPERATION_TYPE_CONTROL;

	if (!pMCRO)		return nRtn;

	switch(pMCRO->nType)
	{
		case SS_COMMON_REMOTE_ORDER_TYPE_NC_PTN_GET_FILE_INFO:		nRtn = ApplyRemotePolicy_NCScan(pMCRO);		break;				
		case SS_COMMON_REMOTE_ORDER_TYPE_NO_PTN_GET_FILE_INFO:		nRtn = ApplyRemotePolicy_NOScan(pMCRO);		break;				
		case SS_COMMON_REMOTE_ORDER_TYPE_NO_PTN_RE_SEND_FILE_INFO:	nRtn = ApplyRemotePolicy_NOReSend(pMCRO);		break;				
	}


	{
		InitDLEALL(m_nEvtOpType, m_nEvtSubType, m_nSessionID, m_nEvtTarType, 0, m_nEvtObjType, m_nEvtObjCode, pMCRO->nType, pMCRO->strValue, m_strEvtDesc);
		t_LogicLogEvent->SetLogEvent(m_tDLE);
	}
	
	return nRtn;
}
//---------------------------------------------------------------------------

INT32		CLogicMgrCtrlRemoteOrder::ApplyRemotePolicy_NCScan(PMEM_CTRL_REMOTE_ORDER pMCRO)
{
	t_LogicMgrPoFePtnOp->ScanDefaultOption();
	return AZPKT_CB_RTN_SUCCESS;
}
//---------------------------------------------------------------------------

INT32		CLogicMgrCtrlRemoteOrder::ApplyRemotePolicy_NOScan(PMEM_CTRL_REMOTE_ORDER pMCRO)
{
	{
		DB_PO_IN_PTN_OP_UNIT data;
		WriteLogN("start remote ctrl : po in ptn scan : [%s]", pMCRO->strValue.c_str());		
		{			
			data.strScanPath = pMCRO->strValue;
			data.tDPH.strName = "admin demand control";
			data.nFileGatherType = SS_PO_IN_PTN_OP_NEW_FILE_SEND_TYPE_INFO;

			t_ThreadPoInPtnScan->AddWork(&data);
		}
	}
	return AZPKT_CB_RTN_SUCCESS;
}
//---------------------------------------------------------------------------

INT32		CLogicMgrCtrlRemoteOrder::ApplyRemotePolicy_NOReSend(PMEM_CTRL_REMOTE_ORDER pMCRO)
{
	{
		WriteLogN("start remote ctrl : po in ptn resend : [%d]", pMCRO->nType);		
		{			
			t_LogicMgrSiteFile->SendPkt_ReSend();
		}
	}
	return AZPKT_CB_RTN_SUCCESS;
}
//---------------------------------------------------------------------------