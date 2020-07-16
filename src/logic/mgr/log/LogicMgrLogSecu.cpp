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
#include "LogicMgrLogSecu.h"

//---------------------------------------------------------------------------

CLogicMgrLogSecu*		t_LogicMgrLogSecu = NULL;

//---------------------------------------------------------------------------

CLogicMgrLogSecu::CLogicMgrLogSecu()
{	
	t_ManageLogSecu	= new CManageLogSecu();
	t_LogicLogSecu	= new CLogicLogSecu();

	t_ManageLogSecu->LoadDBMS();

	m_strLogicName		= "logic mgr log secu";

	m_nControlType		= SS_CONTROL_TYPE_LOG_SECU;
	m_nEvtObjType		= EVENT_OBJECT_TYPE_HOST;
	m_nEvtObjCode		= 0;
}
//---------------------------------------------------------------------------

CLogicMgrLogSecu::~CLogicMgrLogSecu()
{
	SAFE_DELETE(t_LogicLogSecu);
	SAFE_DELETE(t_ManageLogSecu);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32		CLogicMgrLogSecu::AnalyzePkt_FromMgr_Ext()
{
	UINT32 nRtn = AZPKT_CB_RTN_SUCCESS;
	switch(m_nPktCode)
	{
		case G_CODE_COMMON_SYNC:		nRtn = AnalyzePkt_FromMgr_Ext_Sync();			break;
		default:
		{
			nRtn = AZPKT_CB_RTN_PKT_NOT_DEFINE_CODE;
			break;
		}
	}

	return SetHdrAndRtn(nRtn);
}
//---------------------------------------------------------------------------

INT32		CLogicMgrLogSecu::AnalyzePkt_FromMgr_Add_Ext()
{
	DB_LOG_SECU dls;

	if(t_ManageLogSecu->GetPkt(RecvToken, dls))		return AZPKT_CB_RTN_PKT_INVALID;

	dls.nEvtTime	= t_ValidTimeUtil->GetValidTime();
	HISYNCSTEPUP(dls.nSyncSvrStep);

	SetLogSecu(dls);

	return AZPKT_CB_RTN_SUCCESS_END;
}
//---------------------------------------------------------------------------

INT32		CLogicMgrLogSecu::AnalyzePkt_FromMgr_Edit_Ext()
{
	return AZPKT_CB_RTN_SUCCESS_END;
}
//---------------------------------------------------------------------------

INT32		CLogicMgrLogSecu::AnalyzePkt_FromMgr_Del_Ext()
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
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32		CLogicMgrLogSecu::AnalyzePkt_FromMgr_Ext_Sync()
{	
	TListDBLogSecu tDBLogSecuList;

	if(CheckPktResult(RecvToken))					return AZPKT_CB_RTN_RESULT_FAILED;
	if(!RecvToken.TokenDel_32(m_nRecvNum))			return AZPKT_CB_RTN_PKT_INVALID;
	while(m_nRecvNum--)
	{
		DB_LOG_SECU tDLS;
		if(t_ManageLogSecu->GetPkt(RecvToken, tDLS))		return AZPKT_CB_RTN_PKT_INVALID;

		tDBLogSecuList.push_back(tDLS);
	}

	{
		TListDBLogSecuItor begin, end;
		begin = tDBLogSecuList.begin();	end = tDBLogSecuList.end();
		for(begin; begin != end; begin++)
		{
			t_ManageLogSecu->EditLogSecu(*begin);
		}
	}
	return AZPKT_CB_RTN_SUCCESS_END;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void		CLogicMgrLogSecu::SetLogSecu(DB_LOG_SECU& dls)
{
	{
		if(dls.strObjectPath.find("%") == string::npos && dls.strObjectName.find("%") == string::npos &&
			dls.strSubjectPath.find("%") == string::npos && dls.strSubjectName.find("%") == string::npos)
		{
			WriteLogN("[%s] remain evt log to file : pt[%d]:bt[%d]:ot:[%d]:sb[%s/%s]:ob[%s/%s]", 
							m_strLogicName.c_str(),
							dls.nPolicyType, dls.nBlockType, dls.nObjectType, 
							dls.strSubjectPath.c_str(), dls.strSubjectName.c_str(), 
							dls.strObjectPath.c_str(), dls.strObjectName.c_str());

		}
	}

	{
		PDB_ENV_LOG_UNIT pDELEU = t_ManageEnvLogUnit->FindRecordLogSecuUnit(&dls);
		if(pDELEU && pDELEU->tDPH.nUsedMode == STATUS_USED_MODE_ON)
		{
			dls.nSkipTarget = pDELEU->tDPH.nExtOption;
		}
	}
	
	if(!(dls.nSkipTarget & SS_ENV_LOG_OPTION_FLAGE_SKIP_SAVE_AGENT))
	{
		t_ManageLogSecu->AddLogSecu(dls);
	}

	{	
		SendToken.Set(1024);
		SendToken.TokenAdd_32(1);
		t_ManageLogSecu->SetPkt(&dls, SendToken);
		if(!(dls.nSkipTarget & SS_ENV_LOG_OPTION_FLAGE_SKIP_SAVE_SERVER))
		{
			SendData(G_TYPE_LOG_SECU, G_CODE_COMMON_SYNC, SendToken);
		}
		if(!(dls.nSkipTarget & SS_ENV_LOG_OPTION_FLAGE_SKIP_SAVE_AGENT))		
		{
			SendData_Link(G_TYPE_LOG_SECU, G_CODE_COMMON_SYNC, SendToken);
		}
		SendToken.Clear();
	}
	return;
}
//---------------------------------------------------------------------------
