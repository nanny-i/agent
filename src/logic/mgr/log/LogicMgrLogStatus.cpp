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
#include "LogicMgrLogStatus.h"

//---------------------------------------------------------------------------

CLogicMgrLogStatus*		t_LogicMgrLogStatus = NULL;

//---------------------------------------------------------------------------

CLogicMgrLogStatus::CLogicMgrLogStatus()
{		
	t_ManageLogStatus	= new CManageLogStatus();
	t_LogicLogStatus	= new CLogicLogStatus();

	t_ManageLogStatus->LoadDBMS();

	m_strLogicName		= "mgr log status";

	m_nControlType		= SS_CONTROL_TYPE_LOG_STATUS;
	m_nEvtObjType		= EVENT_OBJECT_TYPE_HOST;
	m_nEvtObjCode		= 0;
}
//---------------------------------------------------------------------------

CLogicMgrLogStatus::~CLogicMgrLogStatus()
{
	SAFE_DELETE(t_LogicLogStatus);
	SAFE_DELETE(t_ManageLogStatus);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32		CLogicMgrLogStatus::AnalyzePkt_FromMgr_Ext()
{
	UINT32 nRtn = AZPKT_CB_RTN_SUCCESS;
	switch(m_nPktCode)
	{
		case G_CODE_COMMON_SYNC:		nRtn = AnalyzePkt_FromMgr_Ext_Sync();				break;
		default:
		{
			nRtn = AZPKT_CB_RTN_PKT_NOT_DEFINE_CODE;
			break;
		}
	}

	return SetHdrAndRtn(nRtn);
}
//---------------------------------------------------------------------------

INT32		CLogicMgrLogStatus::AnalyzePkt_FromMgr_Add_Ext()
{
	return AZPKT_CB_RTN_SUCCESS_END;
}
//---------------------------------------------------------------------------

INT32		CLogicMgrLogStatus::AnalyzePkt_FromMgr_Edit_Ext()
{
	return AZPKT_CB_RTN_SUCCESS_END;
}
//---------------------------------------------------------------------------

INT32		CLogicMgrLogStatus::AnalyzePkt_FromMgr_Del_Ext()
{
	return AZPKT_CB_RTN_SUCCESS_END;
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

INT32		CLogicMgrLogStatus::AnalyzePkt_FromMgr_Ext_Sync()
{
	TListDBLogStatus tDBLogStatusList;

	if(CheckPktResult(RecvToken))					return AZPKT_CB_RTN_RESULT_FAILED;
	if(!RecvToken.TokenDel_32(m_nRecvNum))			return AZPKT_CB_RTN_PKT_INVALID;
	while(m_nRecvNum--)
	{
		DB_LOG_STATUS tDLS;
		if(t_ManageLogStatus->GetPkt(RecvToken, tDLS))		return AZPKT_CB_RTN_PKT_INVALID;

		tDBLogStatusList.push_back(tDLS);
	}

	{
		TListDBLogStatusItor begin, end;
		begin = tDBLogStatusList.begin();	end = tDBLogStatusList.end();
		for(begin; begin != end; begin++)
		{
			t_LogicMgrLogStatus->SetLogStatus(*begin);
		}
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
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void		CLogicMgrLogStatus::SetLogStatus(DB_LOG_STATUS& dls)
{
	if(!ISSYNCSTEP(dls.nSyncSvrStep))
	{
		String strDesc = MapID_StrToStr(dls.tDescIDStrMap);

		if(dls.strSubjectInfo.find("%") == string::npos && dls.strTargetInfo.find("%") == string::npos &&
			dls.strObjectInfo.find("%") == string::npos && strDesc.find("%") == string::npos )
		{

			WriteLogN("[logic log status] remain status log to file : op[%d]:s[%d:%d][%s]:t[%d:%d][%s]:o[%d:%d][%d:%s]:[%s]", 
				dls.nOperationType, 
				dls.nSubjectType, dls.nSubjectID,  dls.strSubjectInfo.c_str(), 
				dls.nTargetType,  dls.nTargetID,   dls.strTargetInfo.c_str(), 
				dls.nObjectType,  dls.nObjectCode, dls.nObjectID, dls.strObjectInfo.c_str(),
				strDesc.c_str());

		}
	}

	{
		PDB_ENV_LOG_UNIT pDELEU = t_ManageEnvLogUnit->FindRecordLogStatusUnit(&dls);
		if(pDELEU && pDELEU->tDPH.nUsedMode == STATUS_USED_MODE_ON)
		{
			dls.nSkipTarget = pDELEU->tDPH.nExtOption;
		}
	}

	if(!(dls.nSkipTarget & SS_ENV_LOG_OPTION_FLAGE_SKIP_SAVE_AGENT))
	{
		t_ManageLogStatus->AddLogStatus(dls);
	}
	
	{	
		SendToken.Set(1024);
		SendToken.TokenAdd_32(1);
		t_ManageLogStatus->SetPkt(&dls, SendToken);
		if(!ISSYNCSTEP(dls.nSyncSvrStep) && !(dls.nSkipTarget & SS_ENV_LOG_OPTION_FLAGE_SKIP_SAVE_SERVER))
		{
			SendData(G_TYPE_LOG_STATUS, G_CODE_COMMON_SYNC, SendToken);
		}
		SendToken.Clear();
	
		if(!(dls.nSkipTarget & SS_ENV_LOG_OPTION_FLAGE_SKIP_SAVE_AGENT))
		{
			SendToken.TokenAdd_32(1);
			t_ManageLogStatus->SetPkt(&dls, SendToken);
			SendData_Link(G_TYPE_LOG_STATUS, G_CODE_COMMON_SYNC, SendToken);
			SendToken.Clear();
		}
	}
	return;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

