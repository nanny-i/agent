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
#include "LogicMgrLogDeployFile.h"

//---------------------------------------------------------------------------

CLogicMgrLogDeployFile*		t_LogicMgrLogDeployFile = NULL;

//---------------------------------------------------------------------------

CLogicMgrLogDeployFile::CLogicMgrLogDeployFile()
{	
	
	t_ManageLogDeployFile	= new CManageLogDeployFile();
	t_LogicLogDeployFile	= new CLogicLogDeployFile();

	t_ManageLogDeployFile->LoadDBMS();

	m_strLogicName		= "mgr log deploy file";
	
	m_nControlType		= SS_CONTROL_TYPE_LOG_DEPLOY_FILE;	
	m_nEvtObjType		= EVENT_OBJECT_TYPE_HOST;
	m_nEvtObjCode		= 0;
}
//---------------------------------------------------------------------------

CLogicMgrLogDeployFile::~CLogicMgrLogDeployFile()
{
	SAFE_DELETE(t_LogicLogDeployFile);
	SAFE_DELETE(t_ManageLogDeployFile);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32		CLogicMgrLogDeployFile::AnalyzePkt_FromMgr_Ext()
{
	UINT32 nRtn = AZPKT_CB_RTN_SUCCESS;
	switch(m_nPktCode)
	{
		case G_CODE_COMMON_SYNC:					AnalyzePkt_FromMgr_Ext_Sync();			break;
		default:
		{
			nRtn = AZPKT_CB_RTN_PKT_NOT_DEFINE_CODE;
			break;
		}
	}

	return SetHdrAndRtn(nRtn);
}
//---------------------------------------------------------------------------

INT32		CLogicMgrLogDeployFile::AnalyzePkt_FromMgr_Ext_Sync()
{		
	TListDBLogDeployFile tDBLogDeployFileList;

	if(CheckPktResult(RecvToken))								return AZPKT_CB_RTN_RESULT_FAILED;
	if(!RecvToken.TokenDel_32(m_nRecvNum))						return AZPKT_CB_RTN_PKT_INVALID;
	while(m_nRecvNum--)
	{
		DB_LOG_DEPLOY_FILE tDLD;
		if(t_ManageLogDeployFile->GetPkt(RecvToken, tDLD))		return AZPKT_CB_RTN_PKT_INVALID;

		tDBLogDeployFileList.push_back(tDLD);

		WriteLogN("[%s] ack remain evt log to file : pi[%d]:ui[%d]:et[%d]:er[%d][%d:%d]", m_strLogicName.c_str(),
			tDLD.nPolicyID, tDLD.nUnitID, tDLD.nEndTime, tDLD.nEndReason,
			HISYNCSTEP(tDLD.nSyncSvrStep), LOSYNCSTEP(tDLD.nSyncSvrStep));
	}

	{
		TListDBLogDeployFileItor begin, end;
		begin = tDBLogDeployFileList.begin();	end = tDBLogDeployFileList.end();
		for(begin; begin != end; begin++)
		{
			SetLogDeployFile(*begin);
		}
	}

	return AZPKT_CB_RTN_SUCCESS_END;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void		CLogicMgrLogDeployFile::SetLogDeployFile(DB_LOG_DEPLOY_FILE& dldf)
{
	if(!ISSYNCSTEP(dldf.nSyncSvrStep))
	{
		WriteLogN("[%s] remain evt log to file : pi[%d]:ui[%d]:et[%d]:er[%d][%d:%d]", 
												m_strLogicName.c_str(),
												dldf.nPolicyID, dldf.nUnitID, dldf.nEndTime, dldf.nEndReason,
												HISYNCSTEP(dldf.nSyncSvrStep), LOSYNCSTEP(dldf.nSyncSvrStep));
	}	

	{
		PDB_ENV_LOG_UNIT pDELEU = t_ManageEnvLogUnit->FindRecordLogDeployFileUnit(&dldf);
		if(pDELEU && pDELEU->tDPH.nUsedMode == STATUS_USED_MODE_ON)
		{
			dldf.nSkipTarget = pDELEU->tDPH.nExtOption;
		}
	}
		
	if(t_ManageLogDeployFile->IsExistLogDeployFile(dldf))
	{
		t_ManageLogDeployFile->EditLogDeployFile(dldf);
	}
	else
	{
		t_ManageLogDeployFile->AddLogDeployFile(dldf);
	}

	{	
		SendToken.Set(1024);
		SendToken.TokenAdd_32(1);
		t_ManageLogDeployFile->SetPkt(&dldf, SendToken);
		if(!ISSYNCSTEP(dldf.nSyncSvrStep) && !(dldf.nSkipTarget & SS_ENV_LOG_OPTION_FLAGE_SKIP_SAVE_SERVER))	
		{
			SendData(G_TYPE_LOG_DEPLOY_FILE, G_CODE_COMMON_SYNC, SendToken);
		}
		SendData_Link(G_TYPE_LOG_DEPLOY_FILE, G_CODE_COMMON_SYNC, SendToken);
		SendToken.Clear();
	}
	return;
}
//---------------------------------------------------------------------------
