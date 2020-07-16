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
#include "LogicMgrHost.h"

//---------------------------------------------------------------------------

CLogicMgrHost*		t_LogicMgrHost = NULL;

//---------------------------------------------------------------------------

CLogicMgrHost::CLogicMgrHost()
{
	t_ManageHost		= new CManageHost();
	
	t_ManageHost->LoadDBMS();
	
	m_strLogicName = "logic mgr host";
	
	m_nControlType	= SS_CONTROL_TYPE_ORG_HOST;	
	m_nEvtObjType	= EVENT_OBJECT_TYPE_HOST;
	m_nEvtObjCode	= 0;
}
//---------------------------------------------------------------------------

CLogicMgrHost::~CLogicMgrHost()
{
	SAFE_DELETE(t_ManageHost)
}
//---------------------------------------------------------------------------

INT32		CLogicMgrHost::AnalyzePkt_FromMgr_Ext()
{
	UINT32 nRtn = AZPKT_CB_RTN_SUCCESS;
	switch(m_nPktCode)
	{
		case G_CODE_COMMON_SYNC:			nRtn = AnalyzePkt_FromMgr_Ext_Sync();		break;
		case G_CODE_HOST_SET_USED_FLAG:		nRtn = AnalyzePkt_FromMgr_Ext_Used();		break;
		case G_CODE_HOST_SET_NAME:			nRtn = AnalyzePkt_FromMgr_Ext_SetName();	break;
		default:
		{	
			nRtn = AZPKT_CB_RTN_PKT_NOT_DEFINE_CODE;
			break;
		}
	}

	return SetHdrAndRtn(nRtn);
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

INT32		CLogicMgrHost::AnalyzePkt_FromMgr_Edit_Ext()
{
	PDB_HOST pdh = NULL;
	DB_HOST dh;

	if(t_ManageHost->GetPktHost(RecvToken, dh) < 0)
	{
		return AZPKT_CB_RTN_PKT_INVALID;
	}

	if( (pdh = t_ManageHost->FirstItem()) == NULL)
	{
		WriteLogE("[%s] not find host info", m_strLogicName.c_str());
		return AZPKT_CB_RTN_SUCCESS_END;
	}

	if(	pdh->strName.compare(dh.strName) ||
		pdh->strWorkGroup.compare(dh.strWorkGroup) ||
		pdh->strPriIP.compare(dh.strPriIP) ||
		pdh->strMac.compare(dh.strMac) ||
		pdh->strUserUnicode.compare(dh.strUserUnicode) ||
		CompareMapID(pdh->tPoIDMap, dh.tPoIDMap) ||
		CompareMapID(pdh->tPoSeqNoMap, dh.tPoSeqNoMap) ||
		CompareMapID(pdh->tPoTimeMap, dh.tPoTimeMap))
	{
		pdh->strName = dh.strName;
		pdh->strWorkGroup = dh.strWorkGroup;
		pdh->strPriIP = dh.strPriIP;
		pdh->strNatIP = dh.strNatIP;
		pdh->strMac = dh.strMac;
		pdh->strUserUnicode = dh.strUserUnicode;
		pdh->nUserID		= dh.nUserID;
		
		pdh->tPoIDMap = dh.tPoIDMap;
		pdh->tPoSeqNoMap = dh.tPoSeqNoMap;
		pdh->tPoTimeMap = dh.tPoTimeMap;

		if(SetER(t_ManageHost->EditHost(*pdh)))
		{
			WriteLogE("[%s] edit host information fail : [%u]", m_strLogicName.c_str(), pdh->nID);
			return AZPKT_CB_RTN_SUCCESS_END;
		}

		{		
			t_ManageHost->SetPktHost(SendToken);
			SendData_Link(G_TYPE_HOST, G_CODE_COMMON_EDIT, SendToken);
			SendToken.Clear();
		}
	}	
	return AZPKT_CB_RTN_SUCCESS_END;
}
//---------------------------------------------------------------------------

INT32		CLogicMgrHost::AnalyzePkt_FromMgr_Ext_Sync()
{
	WriteLogN("[%s] sync policy host information start", m_strLogicName.c_str());

	t_LogicMgrAuth->SendMgrInitData_Polcy();


	return AZPKT_CB_RTN_SUCCESS_END;
}
//---------------------------------------------------------------------------

INT32		CLogicMgrHost::AnalyzePkt_FromMgr_Ext_Used()
{
	UINT32	nStatus = 1;

	if (!RecvToken.TokenDel_32(nStatus))		return AZPKT_CB_RTN_PKT_INVALID;
	RecvToken.TokenSkip_Block();

	if (nStatus == USED_FLAG_TYPE_DELETE)
	{
		WriteLogN("[%s] change used mode : auto remove module", m_strLogicName.c_str());
		SetUninstallHost();
	}

	return AZPKT_CB_RTN_SUCCESS_END;
}

//---------------------------------------------------------------------------

INT32		CLogicMgrHost::AnalyzePkt_FromMgr_Ext_SetName()
{	
	DB_HOST dh;
	
	if(CheckPktResult(RecvToken))
	{
		WriteLogE("[%s] check pkt result is : [%x]", m_strLogicName.c_str(), m_nPktRst);
		return AZPKT_CB_RTN_RESULT_FAILED;
	}

	if( RecvToken.TokenDel_String(dh.strName) < 0)		return AZPKT_CB_RTN_PKT_INVALID;

	{
		ASI_TS_INFO tATI;

		ASI_TS_MGR_PARAM tATMP;
		{
			String strPath = "", strBatData = "";
			strPath = SPrintf("%s/%s", t_EnvInfo->m_strRootPath.c_str(), "renamecom.bat");
//			strBatData = SPrintf("%s\r\nwmic ComputerSystem Where Name=\"%%COMPUTERNAME%%\" Call Rename Name=\"%s\"\r\ndel \"%s\n", STR_BATCH_GETADMIN_CMD, dh.strName.c_str(), strPath.c_str());

			CFileUtil tFileUtil;
			if(tFileUtil.WriteFileBuffer(strPath, strBatData) != 0)
			{
				WriteLogE("[%s] computer rename batch file create fail", m_strLogicName.c_str());
				return AZPKT_CB_RTN_SUCCESS_END;
			}

			sprintf_ext(CHAR_MAX_SIZE, tATI.szTaskName, STR_TS_NANE_RENAMECOM); 
			tATI.nChkPeriod = ASI_TS_CHECK_PREIOD_TYPE_ONCE;
			tATI.nStartTime	= GetCurrentDateTimeInt() + 5;

			tATMP.strTSChildPath	= strPath;
			tATMP.nTSChildHideMode	= 1;
			tATMP.nTSSingleRun		= 1;
			tATMP.nTSWaitMode		= 0;
			tATMP.nTSAutoDel		= 1;
		}
		t_ExecuteFileUtil->ExecuteFileByUser(tATI, tATMP);
	}
	
	return AZPKT_CB_RTN_SUCCESS_END;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void		CLogicMgrHost::SendPkt_Edit()
{
	INT32 nSendPkt = 1;
	DB_HOST dh;
	{

		dh.strName		= t_EnvInfoOp->GetComputerName();
		dh.strPriIP = t_EnvInfoOp->m_strPriIPAddr;
		dh.strMac = t_EnvInfoOp->m_strPriMacAddr;
		dh.strUserUnicode = t_EnvInfoOp->GetUserUniCode();		
	}

	PDB_HOST pdh = t_ManageHost->FirstItem();
	if(!pdh)
	{
		WriteLogE("[%s] not find host first item..", m_strLogicName.c_str());
		goto SEND_PKT;
	}
	do 
	{
		if( pdh->strName != dh.strName ||
			pdh->strWorkGroup != dh.strWorkGroup ||
			pdh->strPriIP != dh.strPriIP ||
			pdh->strMac != dh.strMac ||
			pdh->strUserUnicode != dh.strUserUnicode)
		{
			break;
		}

		nSendPkt = 0;
	} while (FALSE);

	if(!nSendPkt)	return;

SEND_PKT:
	SendToken.Clear();
	t_ManageHost->SetPktHost(&dh, SendToken);
	SendData(G_TYPE_HOST, G_CODE_COMMON_EDIT, SendToken);
	SendToken.Clear();

	return;
}
//---------------------------------------------------------------------------

void		CLogicMgrHost::SetUninstallHost()
{
	ASI_TS_INFO tATI;
	ASI_TS_MGR_PARAM tATMP;
	{
		String strPath;
		strPath = SPrintf("%s/%s", t_EnvInfo->m_strRootPath.c_str(), STR_PROC_NAME_NANNY_RM);

		sprintf_ext(CHAR_MAX_SIZE, tATI.szTaskName, STR_TS_NAME_RM); 
		tATI.nChkPeriod = ASI_TS_CHECK_PREIOD_TYPE_ONCE;
		tATI.nStartTime	= GetCurrentDateTimeInt() + 5;

		tATMP.strTSChildPath	= strPath;
		tATMP.strTSChildArgument= "/auto_remove";
		tATMP.nTSChildHideMode	= 1;
		tATMP.nTSSingleRun		= 1;
		tATMP.nTSWaitMode		= 0;
	}
	t_ExecuteFileUtil->ExecuteFileByUser(tATI, tATMP);

	return;
}
