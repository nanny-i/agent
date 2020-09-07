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
#include "LogicPoInPtnSPRule.h"

//---------------------------------------------------------------------------

CLogicPoInPtnSPRule*		t_LogicPoInPtnSPRule = NULL;

//---------------------------------------------------------------------------

CLogicPoInPtnSPRule::CLogicPoInPtnSPRule()
{	
	m_strLogicName		= "link po in ptn sp rule";
		
	m_nEvtObjType		= 0;
	m_nEvtObjCode		= 0;
}
//---------------------------------------------------------------------------

CLogicPoInPtnSPRule::~CLogicPoInPtnSPRule()
{

}
//---------------------------------------------------------------------------

INT32	CLogicPoInPtnSPRule::AnalyzePkt_FromLink_Ext()
{
	switch(m_nPktCode)
	{		
		case G_CODE_COMMON_REQUEST:		AnalyzePkt_FromLink_Ext_Req();		break;
		default:						break;		
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32		CLogicPoInPtnSPRule::AnalyzePkt_FromLink_Ext_Req()
{
	DB_PO_IN_PTN_SP_RULE data;

	if(CheckPktResult(RecvToken))
	{
		WriteLogE("[%s] check pkt result is : [%x]:[pt:%x][pc:%x]", m_strLogicName.c_str(), m_nPktRst, m_nPktType, m_nPktCode);
		return AZPKT_CB_RTN_SUCCESS_END;
	}
	
	if(!RecvToken.TokenDel_32(m_nRecvID))					return AZPKT_CB_RTN_PKT_INVALID;
	if( RecvToken.TokenDel_String(data.tDPH.strName) < 0)	return AZPKT_CB_RTN_PKT_INVALID;
	if( RecvToken.TokenDel_String(data.tDPH.strDescr) < 0)	return AZPKT_CB_RTN_PKT_INVALID;
	if(!RecvToken.TokenDel_32(data.nReqLevel))				return AZPKT_CB_RTN_PKT_INVALID;
	if(!RecvToken.TokenDel_32(data.nReqDay))				return AZPKT_CB_RTN_PKT_INVALID;
	
	{
		PDB_LOG_SECU pdata_log = t_ManageLogSecu->FindItem(m_nRecvID);
		if(!pdata_log)		return AZPKT_CB_RTN_SUCCESS_END;

		{
			DWORD dwFileType = WE_INVALID_FILE;
			ASI_WENG_WL_EX tAWWE;
			memset(&tAWWE, 0, sizeof(ASI_WENG_WL_EX));

			String strFileFullPath;
			strFileFullPath = SPrintf("%s/%s", pdata_log->strObjectPath.c_str(), pdata_log->strObjectName.c_str());

//			t_ASIWENGDLLUtil->GetWL(strFileFullPath.c_str(), &tAWWE, sizeof(ASI_WENG_WL_EX), &dwFileType);
			if(dwFileType == WE_INVALID_FILE)
			{
				return AZPKT_CB_RTN_SUCCESS_END;
			}

			data.strFileKey = BinToHexLen((PBYTE)(tAWWE.acWhiteHash), SHA512_BLOCK_SIZE);
			data.tDPH.nUsedMode = STATUS_USED_MODE_ON;
		}	
	}

	{
		if(data.strFileKey.empty())	
		{
			return AZPKT_CB_RTN_SUCCESS_END;
		}

		if(t_ManagePoInPtnSPRule->FindStrKeyID(data.strFileKey))
		{
			return AZPKT_CB_RTN_SUCCESS_END;
		}


	}

	if(ChkAutoConfirm(&data))
	{
		t_LogicMgrPoInPtnSPRule->SendPkt_Req(&data);
	}
	else
	{
		data.tDPH.nID = t_ManagePoInPtnSPRule->GetNextLocalID();

		if(t_ManagePoInPtnSPRule->ApplyPoInPtnSPRule(data))
		{
			SetDLEH_EC(g_nErrRtn);
			WriteLogE("[%s] apply policy unit information : [%d]", m_strLogicName.c_str(), g_nErrRtn);

			return AZPKT_CB_RTN_SUCCESS_END;
		}
		{
			t_ManagePoInPtnSPRule->SetPkt(SendToken);
			SendData_Link(G_TYPE_PO_IN_PTN_SP_RULE, G_CODE_COMMON_EDIT, SendToken);
			SendToken.Clear();
		}

		t_ThreadTimer->t_TimerUtil.EnableTimer(TIMER_ID_POLICY_APPLY_EPS);
	}
	
	return SetHdrAndRtn(AZPKT_CB_RTN_SUCCESS);
}
//---------------------------------------------------------------------------

INT32		CLogicPoInPtnSPRule::AnalyzePkt_FromLink_Del_Ext()
{
// 	INT32 nPolicyType = 0;
// 
// 	TListDBLogDoc tLogDocList;
// 	if(!RecvToken.TokenDel_32(m_nRecvNum))			return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
// 	while(m_nRecvNum--)
// 	{
// 		DB_LOG_DOC dld;
// 
// 		if(t_ManageLogDoc->GetPkt_Link(RecvToken, dld))	return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
// 		
// 		tLogDocList.push_back(dld);
// 
// 		nPolicyType = dld.nPolicyType;
// 	}
// 
// 	{
// 		INT32 nRtn = 0;
// 		TListDBLogDocItor begin, end;
// 		begin = tLogDocList.begin();	end = tLogDocList.end();
// 		for(begin; begin != end; begin++)
// 		{
// 			UINT32 nTempID = begin->nID;
// 			begin->nID = 0;
// 
// 			nRtn = t_LogicMgrLogDoc->DeleteLogDoc(*begin);
// 			if(nRtn && !begin->nBackupTime)
// 			{
// 				continue;
// 			}
// 
// 			m_tIDList.push_back(nTempID);
// 		}
// 	}
// 
// 	{
// 		MEM_FIND_ORDER_INFO tMFOI;
// 		tMFOI.nPoID				= nPolicyType;
// 		tMFOI.nOpType			= SS_LOG_DOC_OP_TYPE_SCAN;
// 
// 		if(GetUnitIDtoPolicyType(nPolicyType) < FF_START_ORDER_ID_PO_FA_CLEAR)
// 			tMFOI.nOpType	= SS_LOG_DOC_OP_TYPE_SCHEDULE_DEMAND;
// 
// 		tMFOI.nNotiTotalFind	= m_tIDList.size();
// 
// 		if(tMFOI.nNotiTotalFind > 0)
// 			t_LogicPoInPtnSPRule->SendPkt_Del_Last(tMFOI);
// 	}
// 
// 	{
// 		SendToken.TokenAdd_IDList(m_tIDList);
// 		SendData_Link(m_nPktType, m_nPktCode, SendToken);
// 		SendToken.Clear();
// 	}
	return SetHdrAndRtn(AZPKT_CB_RTN_SUCCESS);
}
//---------------------------------------------------------------------------

INT32		CLogicPoInPtnSPRule::ChkAutoConfirm(PDB_PO_IN_PTN_SP_RULE pdata)
{
	PDB_PO_IN_PTN_SP pdata_pol = (PDB_PO_IN_PTN_SP)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_IN_PTN_SP);
	if(!pdata_pol)		return -1;

	if(pdata_pol->tDPH.nUsedMode == STATUS_USED_MODE_OFF)	return -1;
	if((pdata_pol->tDPH.nExtOption & SS_PO_IN_PTN_SP_EXT_OPTION_RULE_CHECK_AGENT) == 0)		return -2;
	if(t_EnvInfoOp->m_nMgrSvrAuthStatus == CLIENT_CON_STATUS_CONNECTED)						return -3;

	if(pdata_pol->nConfirmLevel != SS_PO_IN_PTN_SP_REQ_LEVEL_NONE && pdata_pol->nConfirmLevel <= pdata->nReqLevel)
	{
		pdata->nConfirmType = SS_PO_IN_PTN_SP_RULE_CONFIRM_TYPE_AGENT_POLICY;
		pdata->nConfirmID = pdata_pol->tDPH.nID;
		pdata->nConfirmRst = SS_PO_IN_PTN_SP_RULE_CONFIRM_RST_TYPE_ALLOW;
		if(pdata_pol->nConfirmDay == 0)		pdata->nUseDay = pdata->nReqDay;
		else if(pdata->nReqDay == 0)		pdata->nUseDay = pdata_pol->nConfirmDay;
		else
		{
			pdata->nUseDay = (pdata_pol->nConfirmDay > pdata->nReqDay ? pdata->nReqDay : pdata_pol->nConfirmDay);
		}
		pdata->nEvtDate = GetCurrentDateTimeInt();		
		return 0;
	}

	PDB_SITE_FILE pdata_sf = t_ManageSiteFile->FindItem(pdata->nFileID);
	if(!pdata_sf)	return -2;

	{
		CMatchFilterUtil tMatchFilterUtil;
		TMapIDItor begin, end;
		begin = pdata_pol->tDPH.tSubIDMap.begin();	end = pdata_pol->tDPH.tSubIDMap.end();
		for(begin; begin != end; begin++)
		{
			PDB_PO_IN_PTN_SP_UNIT pdata_unit = t_ManagePoInPtnSPUnit->FindItem(begin->second);
			if(!pdata_unit)		continue;

			if(pdata_unit->tDPH.nUsedMode != STATUS_USED_MODE_ON)	continue;

			if(tMatchFilterUtil.IsMatchFilter(pdata_sf, pdata_unit->tDFI, pdata_unit->nFltChkType))	continue;

			{
				pdata->nConfirmType	= SS_PO_IN_PTN_SP_RULE_CONFIRM_TYPE_AGENT_POLICY_UNIT;
				pdata->nConfirmID = pdata_unit->tDPH.nID;				
				pdata->nConfirmRst = pdata_unit->nBlockMode;

				if(pdata_unit->nUseDay == 0)		pdata->nUseDay = pdata->nReqDay;
				else if(pdata->nReqDay == 0)		pdata->nUseDay = pdata_unit->nUseDay;
				else
				{
					pdata->nUseDay = (pdata_unit->nUseDay > pdata->nReqDay ? pdata->nReqDay : pdata_unit->nUseDay);
				}


				pdata->nEvtDate = GetCurrentDateTimeInt();
				return 0;
			}
		}
	}
	return -10;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
