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
#include "LogicMgrCtrlInstantMsg.h"
//---------------------------------------------------------------------------

CLogicMgrCtrlInstantMsg*		t_LogicMgrCtrlInstantMsg = NULL;

//---------------------------------------------------------------------------

CLogicMgrCtrlInstantMsg::CLogicMgrCtrlInstantMsg()
{
	m_strLogicName		= "ctrl instant msg";

	m_nControlType		= SS_CONTROL_TYPE_CONTROL_INSTANT_MSG;
	m_nEvtSubType		= EVENT_SUBJECT_TYPE_ADMIN;
	m_nEvtObjType		= EVENT_OBJECT_TYPE_HOST;
	m_nEvtObjCode		= EVENT_OBJECT_CODE_HOST_CTRL_INSTANT_MSG;	
}
//---------------------------------------------------------------------------

CLogicMgrCtrlInstantMsg::~CLogicMgrCtrlInstantMsg()
{
}
//---------------------------------------------------------------------------

INT32		CLogicMgrCtrlInstantMsg::AnalyzePkt_FromMgr_Ext()
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

INT32		CLogicMgrCtrlInstantMsg::AnalyzePkt_FromMgr_Ext_Ctrl()
{
	MEM_CTRL_INSTANT_MSG		tMCIM;
	
	if( RecvToken.TokenDel_String(tMCIM.strTitle) < 0)			return AZPKT_CB_RTN_PKT_INVALID;
	if( RecvToken.TokenDel_String(tMCIM.strMsg) < 0)			return AZPKT_CB_RTN_PKT_INVALID;
	RecvToken.TokenSkip_Block();
	
	SetER(ApplyPolicy(&tMCIM));

	{
		SendToken.TokenAdd_32(g_nErrRtn);
	}

	return AZPKT_CB_RTN_SUCCESS;
}
//---------------------------------------------------------------------------

INT32		CLogicMgrCtrlInstantMsg::ApplyPolicy(PMEM_CTRL_INSTANT_MSG pInfo)
{
	INT32 nRet = ERR_SUCCESS;
	if (!pInfo)		return ERR_UNKNOWN;

	m_nEvtOpType = EVENT_OPERATION_TYPE_CONTROL;
	
	CSystemInfo tSysInfo;
	ASI_TS_INFO tATI;
	ASI_TS_MGR_PARAM tATMP;
	{
		sprintf_ext(CHAR_MAX_SIZE, tATI.szTaskName, STR_TS_NAME_INSTANT_MSG, GetTickCount()); 
		if(tSysInfo.IsExistLoginSession())
		{
			tATI.nChkPeriod = ASI_TS_CHECK_PREIOD_TYPE_ONCE;
			tATI.nStartTime	= GetCurrentDateTimeInt() + 5;
		}
		else
		{
			tATI.nChkPeriod = ASI_TS_CHECK_PREIOD_TYPE_USER_LOGIN;
			tATI.nStartTime	= GetCurrentDateTimeInt();
		}

		tATMP.nTSAutoDel		= 1;
		tATMP.nTSSingleRun		= 1;
		tATMP.nTSShow			= 1;
		tATMP.nTSShowMode		= SHOW_MODE_TYPE_INSTANT_MSG;
		tATMP.nTSWaitMode		= 0;

		{
			CFileUtil tFileUtil;
			String strCMFName;
			{
				strCMFName = SPrintf("%s/inven/cmd", t_EnvInfo->m_strRootPath.c_str());
				tFileUtil.ForceDirectory(strCMFName.c_str());
				strCMFName = SPrintf("%s/inven/cmd/%s", t_EnvInfo->m_strRootPath.c_str(), GetGUID().c_str());
			}
			{
				String strArgFileBuf;
				strArgFileBuf = SPrintf("%s\f%s\f", pInfo->strMsg.c_str(), pInfo->strTitle.c_str());
				tFileUtil.WriteFileBuffer(strCMFName, strArgFileBuf);				
			}	

			tATMP.strTSConfirmMsg = strCMFName;
		}

		tATMP.nTSChildWaitMode = 1;
		tATMP.nTSChildHideMode = 0;
	}		
	t_ExecuteFileUtil->ExecuteFileByUser(tATI, tATMP);

	{
		InitDLEALL(m_nEvtOpType, m_nEvtSubType, m_nSessionID, m_nEvtTarType, 0, m_nEvtObjType, m_nEvtObjCode, 0, pInfo->strTitle, m_strEvtDesc);
		t_LogicLogEvent->SetLogEvent(m_tDLE);
	}
	
	return nRet; 
}
//---------------------------------------------------------------------------