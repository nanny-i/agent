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
#include "LogicMgrLogDoc.h"

//---------------------------------------------------------------------------

CLogicMgrLogDoc*		t_LogicMgrLogDoc = NULL;

//---------------------------------------------------------------------------

CLogicMgrLogDoc::CLogicMgrLogDoc()
{		
	t_ManageLogDoc	= new CManageLogDoc();
//	t_LogicLogDoc	= new CLogicLogDoc();

	t_ManageLogDocHost	= new CManageLogDocHost();

	t_ManageLogDoc->LoadDBMS();
	t_ManageLogDocHost->LoadDBMS();

	m_strLogicName		= "mgr log doc";

	m_nControlType		= SS_CONTROL_TYPE_LOG_DOC_ROLLBACK;
	m_nEvtObjType		= EVENT_OBJECT_TYPE_HOST;
	m_nEvtObjCode		= 0;
}
//---------------------------------------------------------------------------

CLogicMgrLogDoc::~CLogicMgrLogDoc()
{
	SAFE_DELETE(t_ManageLogDocHost);

//	SAFE_DELETE(t_LogicLogDoc);
	SAFE_DELETE(t_ManageLogDoc);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32		CLogicMgrLogDoc::AnalyzePkt_FromMgr_Ext()
{
	UINT32 nRtn = AZPKT_CB_RTN_SUCCESS;
	switch(m_nPktCode)
	{
		case G_CODE_COMMON_FIND:				nRtn = AnalyzePkt_FromMgr_Ext_Find();				break;
		case G_CODE_COMMON_SCAN:				nRtn = AnalyzePkt_FromMgr_Ext_Scan();				break;
		case G_CODE_COMMON_SYNC:				nRtn = AnalyzePkt_FromMgr_Ext_Sync();				break;
		case G_CODE_COMMON_ROLLBACK:			nRtn = AnalyzePkt_FromMgr_Ext_RollBack();			break;
		case G_CODE_LOG_DOC_ROLLBACK_EACH_HOST:	nRtn = AnalyzePkt_FromMgr_Ext_RollBack_Each_Host();	break;
		default:
		{
			nRtn = AZPKT_CB_RTN_PKT_NOT_DEFINE_CODE;
			break;
		}
	}

	return SetHdrAndRtn(nRtn);
}
//---------------------------------------------------------------------------

INT32		CLogicMgrLogDoc::AnalyzePkt_FromMgr_Add_Ext()
{
	DB_LOG_DOC dld;
	if(t_ManageLogDoc->GetPkt_Link(RecvToken, dld))		return AZPKT_CB_RTN_PKT_INVALID;

	dld.nEvtTime	= t_ValidTimeUtil->GetValidTime();
	HISYNCSTEPUP(dld.nSyncSvrStep);

	if(t_ManageLogDoc->IsExistLogDoc(dld))
	{
		return AZPKT_CB_RTN_SUCCESS_END;
	}

	SetLogDoc(dld);

	return AZPKT_CB_RTN_SUCCESS_END;
}
//---------------------------------------------------------------------------

INT32		CLogicMgrLogDoc::AnalyzePkt_FromMgr_Edit_Ext()
{
	return AZPKT_CB_RTN_SUCCESS_END;
}
//---------------------------------------------------------------------------

INT32		CLogicMgrLogDoc::AnalyzePkt_FromMgr_Del_Ext()
{
	DB_LOG_DOC dld;	

	if(t_ManageLogDoc->GetPkt_Link(RecvToken, dld))		return AZPKT_CB_RTN_PKT_INVALID;

	DeleteLogDoc(dld);

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

INT32		CLogicMgrLogDoc::AnalyzePkt_FromMgr_Ext_Find()
{
	DB_LOG_DOC dld;	

	if(CheckPktResult(RecvToken))					return AZPKT_CB_RTN_RESULT_FAILED;
	if(t_ManageLogDoc->GetPkt_Link(RecvToken, dld))		return AZPKT_CB_RTN_PKT_INVALID;

	dld.nEvtTime	= t_ValidTimeUtil->GetValidTime();

	{	
		t_LogicPoFaClear->SendPkt_Find(&dld);
	}

	return AZPKT_CB_RTN_SUCCESS_END;
}
//---------------------------------------------------------------------------

INT32		CLogicMgrLogDoc::AnalyzePkt_FromMgr_Ext_Scan()
{
	DB_LOG_DOC dld;	

	if(CheckPktResult(RecvToken))					return AZPKT_CB_RTN_RESULT_FAILED;
	if(t_ManageLogDoc->GetPkt_Link(RecvToken, dld))		return AZPKT_CB_RTN_PKT_INVALID;

	dld.nEvtTime	= t_ValidTimeUtil->GetValidTime();

	{	
		t_LogicLogDocDScan->SendPkt_Find(&dld);
	}

	return AZPKT_CB_RTN_SUCCESS_END;
}
//---------------------------------------------------------------------------

INT32		CLogicMgrLogDoc::AnalyzePkt_FromMgr_Ext_Sync()
{
	TListDBLogDoc tDBLogDocList;

	if(CheckPktResult(RecvToken))					return AZPKT_CB_RTN_RESULT_FAILED;
	if(!RecvToken.TokenDel_32(m_nRecvNum))			return AZPKT_CB_RTN_PKT_INVALID;
	while(m_nRecvNum--)
	{
		DB_LOG_DOC tDLD;
		if(t_ManageLogDoc->GetPkt(RecvToken, tDLD))		return AZPKT_CB_RTN_PKT_INVALID;

		tDBLogDocList.push_back(tDLD);
	}

	{
		TListDBLogDocItor begin, end;
		begin = tDBLogDocList.begin();	end = tDBLogDocList.end();
		for(begin; begin != end; begin++)
		{
			t_LogicMgrLogDoc->SetLogDoc_Mgr(*begin);
		}
	}

	return AZPKT_CB_RTN_SUCCESS_END;
}
//---------------------------------------------------------------------------

INT32		CLogicMgrLogDoc::AnalyzePkt_FromMgr_Ext_RollBack()
{
	m_nEvtOpType = EVENT_OPERATION_TYPE_ROLLBACK;
	
	if(CheckPktResult(RecvToken))						return AZPKT_CB_RTN_RESULT_FAILED;
	if( RecvToken.TokenDel_IDList(m_tRecvIDList) < 0)	return AZPKT_CB_RTN_PKT_INVALID;

	{
		TListIDItor begin, end;
		begin = m_tRecvIDList.begin();	end = m_tRecvIDList.end();
		for(begin; begin != end; begin++)
		{
			PDB_LOG_DOC pdld = t_ManageLogDoc->FindKeyItem(*begin);
			if(!pdld)
			{
				SetDLEA_EC(ERR_INFO_NOT_DELETE_BECAUSE_NOT_FIND, 0);
				WriteLogE("[%s] not find host information for delete [id:%d]", m_strLogicName.c_str(), *begin);
				continue;
			}

			if(pdld->nRemoveTime)			continue;
			if(pdld->nBackupTime == 0)		continue;

			{
				InitDLEALL(m_nEvtOpType, m_nEvtSubType, m_nSessionID, m_nEvtTarType, 0, m_nEvtObjType, m_nEvtObjCode, pdld->nID, pdld->strObjectName, m_strName);
				t_LogicLogEvent->SetLogEvent(m_tDLE);
			}

			if(SetER(t_DocBackupUtil->RecoveryFile(pdld)))
			{
				WriteLogE("[%s] doc recovery operation fail : [er:%d][id:0]", m_strLogicName.c_str(), g_nErrRtn);
				return AZPKT_CB_RTN_SUCCESS_END;
			}

			HISYNCSTEPUP(pdld->nSyncSvrStep);
			SetLogDoc(*pdld);
		}
	}
	return AZPKT_CB_RTN_SUCCESS_END;
}
//---------------------------------------------------------------------------

INT32		CLogicMgrLogDoc::AnalyzePkt_FromMgr_Ext_RollBack_Each_Host()
{
	m_nEvtOpType = EVENT_OPERATION_TYPE_ROLLBACK;

	UINT32 nStDate = 0, nEdDate = 0;

	if(CheckPktResult(RecvToken))						return AZPKT_CB_RTN_RESULT_FAILED;
	
	if(!RecvToken.TokenDel_32(nStDate))					return AZPKT_CB_RTN_PKT_INVALID;
	if(!RecvToken.TokenDel_32(nEdDate))					return AZPKT_CB_RTN_PKT_INVALID;

	t_ManageLogDoc->GetKeyIDList(m_tRecvIDList);

	{
		TListIDItor begin, end;
		begin = m_tRecvIDList.begin();	end = m_tRecvIDList.end();
		for(begin; begin != end; begin++)
		{
			PDB_LOG_DOC pdld = t_ManageLogDoc->FindKeyItem(*begin);
			if(!pdld)
			{
				SetDLEA_EC(ERR_INFO_NOT_DELETE_BECAUSE_NOT_FIND, 0);
				WriteLogE("[%s] not find host information for delete [id:%d]", m_strLogicName.c_str(), *begin);
				continue;
			}

			if(pdld->nRemoveTime)			continue;
			if(pdld->nBackupTime == 0)		continue;
			if(nStDate != 0 && pdld->nBackupTime < nStDate)		continue;
			if(nEdDate != 0 && pdld->nBackupTime > nEdDate)		continue;

			if(SetER(t_DocBackupUtil->RecoveryFile(pdld)))
				WriteLogE("[%s] doc recovery operation fail : [er:%d][id:0]", m_strLogicName.c_str(), g_nErrRtn);

			HISYNCSTEPUP(pdld->nSyncSvrStep);
			SetLogDoc(*pdld);
		}

		WriteLogN("[%s] doc recovery each host operation success : [cnt:%u][st:%u][ed:%u]", m_strLogicName.c_str(), m_tRecvIDList.size(), nStDate, nEdDate);

		{
			String strObjectInfo = "[doc recovery each host]";
			InitDLEALL(m_nEvtOpType, m_nEvtSubType, m_nSessionID, m_nEvtTarType, 0, m_nEvtObjType, m_nEvtObjCode, 0, strObjectInfo, m_strName);
			t_LogicLogEvent->SetLogEvent(m_tDLE);
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

INT32		CLogicMgrLogDoc::DeleteLogDoc(DB_LOG_DOC& dld)
{	
	PDB_LOG_DOC pdld = NULL;
	{
		pdld = t_ManageLogDoc->GetExistLogDoc(dld);
		if(pdld)
		{
			DB_LOG_DOC dld_temp = *pdld;
			dld_temp.nOpType = dld.nOpType;
			dld_temp.nPolicyType = dld.nPolicyType;

			dld = dld_temp;
		}
		else
		{
			dld.nEvtTime	= t_ValidTimeUtil->GetValidTime();
		}
	}

	UINT32 nDelCnt = 7, nLimitSize = 0, nLimitDelCnt = 0, nDelMethod = 0;
	if(dld.nOpType == SS_LOG_DOC_OP_TYPE_SCHEDULE || dld.nOpType == SS_LOG_DOC_OP_TYPE_SCHEDULE_DEMAND)
	{
		PDB_PO_FA_CLEAR_UNIT pdb_unit = t_ManagePoFaClearUnit->FindItem(dld.nPolicyType - ASI_EPS_APP_POLICY_GROUP_ID_FA_CLEAR);
		if(pdb_unit)
		{
			nDelCnt			= pdb_unit->nDelCount;
			nLimitSize		= pdb_unit->nLimitSize;
			nLimitDelCnt	= pdb_unit->nLimitCnt;
			nDelMethod		= pdb_unit->nDelMethod;
		}
	}

	if(SetER(t_DocBackupUtil->BackupFile(&dld, nDelMethod, nDelCnt, nLimitSize, nLimitDelCnt)))
	{
		WriteLogE("[%s] doc backup operation fail : [er:%d][id:0]", m_strLogicName.c_str(), g_nErrRtn);
		return -1;
	}

	HISYNCSTEPUP(dld.nSyncSvrStep);
	SetLogDoc(dld);
	return 0;
}
//---------------------------------------------------------------------------

void		CLogicMgrLogDoc::SetLogDoc(DB_LOG_DOC& dld)
{
	if(!ISSYNCSTEP(dld.nSyncSvrStep)) 
	{
		if(dld.strObjectPath.find("%") == string::npos && dld.strObjectName.find("%") == string::npos &&
			dld.strSubjectPath.find("%") == string::npos && dld.strSubjectName.find("%") == string::npos)
		{

			WriteLogN("[%s] remain evt log to file : op[%d]:rm[%d]:bk[%d]:fi[%s/%s:%s/%s][%s]", 
				m_strLogicName.c_str(),
				dld.nOpType, dld.nRemoveTime, dld.nBackupTime,
				dld.strSubjectPath.c_str(), dld.strSubjectName.c_str(), 
				dld.strObjectPath.c_str(), dld.strObjectName.c_str(), dld.strBkFileName.c_str());

		}
	}

	{
		PDB_ENV_LOG_UNIT pDELEU = t_ManageEnvLogUnit->FindRecordLogDocUnit(&dld);
		if(pDELEU && pDELEU->tDPH.nUsedMode == STATUS_USED_MODE_ON)
		{
			dld.nSkipTarget = pDELEU->tDPH.nExtOption;
		}
	}

	if(t_ManageLogDoc->FindItem(dld.nID))
	{
		t_ManageLogDoc->EditLogDoc(dld);
	}
	else
	{
		t_ManageLogDoc->AddLogDocWithHost(dld);
	}
	
	{	
		SendToken.Set(1024);
		SendToken.TokenAdd_32(1);
		t_ManageLogDoc->SetPkt(&dld, SendToken);
		if(!ISSYNCSTEP(dld.nSyncSvrStep) && !(dld.nSkipTarget & SS_ENV_LOG_OPTION_FLAGE_SKIP_SAVE_SERVER))
		{
			SendData(G_TYPE_LOG_DOC, G_CODE_COMMON_SYNC, SendToken);
		}
		SendToken.Clear();
		
		{
			SendToken.TokenAdd_32(1);
			t_ManageLogDoc->SetPkt_Link(&dld, SendToken);
			SendData_Link(G_TYPE_LOG_DOC, G_CODE_COMMON_SYNC, SendToken);
			SendToken.Clear();
		}
	}
	return;
}
//---------------------------------------------------------------------------

void		CLogicMgrLogDoc::SetLogDoc_Mgr(DB_LOG_DOC& dld)
{
	PDB_LOG_DOC pdld = t_ManageLogDoc->FindItem(dld.nID);
	if(pdld)
	{
		dld.nFileCrTime = pdld->nFileCrTime;
		dld.nFileMdTime = pdld->nFileMdTime;
		dld.nFileAcTime = pdld->nFileAcTime;
	}

	SetLogDoc(dld);
}
//---------------------------------------------------------------------------

INT32		CLogicMgrLogDoc::ChkBackupOp(UINT32 nDelMethod, UINT32 nDelCnt, UINT32 nLimitSize, UINT32 nLimitDelCnt, UINT32 nChkFDTType, UINT32 nDelAfterDay)
{
	PDB_PO_FA_BK pdpfb = (PDB_PO_FA_BK)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_FA_BK);
	if(!pdpfb)	
	{
		WriteLogN("[%s] not find backup policy", m_strLogicName.c_str());
		return 0;
	}
	
	WriteLogN("[%s] backup policy info : [%d][%d][%d][%d][%d]", m_strLogicName.c_str(), pdpfb->tDPH.nUsedMode, pdpfb->nKeepDay, pdpfb->nKeepSize, pdpfb->nFreeSize, pdpfb->nFileMaxSize);

	CFileUtil tFileUtil;
	INT32 nDelDocCount = 0;
	
	TListID tIDList;
	t_ManageLogDoc->GetItemIDList(tIDList);
	TListIDItor begin, end;
	begin = tIDList.begin();	end = tIDList.end();
	for(begin; begin != end; begin++)
	{
		PDB_LOG_DOC pdld = t_ManageLogDoc->FindItem(*begin);
		if(!pdld)	continue;

		String strFilePath, strFileName;

 		strFilePath = pdld->strObjectPath;
 		strFileName = pdld->strObjectName;
		
		UINT32 nEvtTimeHost = t_ManageLogDocHost->GetLogDocHostEvtTime(*begin);

		{
			if(pdld->nBackupTime || pdld->nRemoveTime || pdld->nOpType != SS_LOG_DOC_OP_TYPE_DOCTRACE )		continue;
			if(nEvtTimeHost && nEvtTimeHost > t_EnvInfo->m_nBootChkTime)	continue;
		}

/*
		{
			if(tFileUtil.FileExists(pdld->strObjectPath.c_str()))
			{
				if(nDelAfterDay && !tFileUtil.IsExistFileDateTime(nChkFDTType, nDelAfterDay * TIMER_INTERVAL_TIME_DAY, strFilePath, strFileName))	continue;
			}
		}
*/
		if(SetER(t_DocBackupUtil->BackupFile(pdld, nDelCnt, nLimitSize, nLimitDelCnt)))
		{
			WriteLogE("[%s] doc backup operation fail : [er:%d][id:%d]", m_strLogicName.c_str(), g_nErrRtn, pdld->nID);
			continue;
		}		
		HISYNCSTEPUP(pdld->nSyncSvrStep);
		SetLogDoc(*pdld);

		nDelDocCount++;
	}

	{
		MEM_FIND_ORDER_INFO tMFOI;
		tMFOI.nPoID				= 0;
		tMFOI.nOpType			= SS_LOG_DOC_OP_TYPE_DOCTRACE;
		tMFOI.nNotiTotalFind	= nDelDocCount;

		if(tMFOI.nNotiTotalFind > 0)
			t_LogicPoFaClear->SendPkt_Del_Last(tMFOI);
	}

	return nDelDocCount;
}
//---------------------------------------------------------------------------

INT32		CLogicMgrLogDoc::ChkDelBackupOp()
{
	INT32 nRmCount = 0;
	TListID tIDList;
	WriteLogN("[%s] doc remove backup operation start", m_strLogicName.c_str());
	t_ManageLogDoc->GetItemIDList(tIDList);
	TListIDRItor begin, end;
	begin = tIDList.rbegin();	end = tIDList.rend();
	for(begin; begin != end; begin++)
	{
		PDB_LOG_DOC pdld = t_ManageLogDoc->FindItem(*begin);
		if(!pdld)	continue;

		if(pdld->nBackupTime == 0 || pdld->nRemoveTime || !(pdld->nOpType == SS_LOG_DOC_OP_TYPE_DOCTRACE || pdld->nOpType == SS_LOG_DOC_OP_TYPE_SCHEDULE))		continue;

		if(SetER(t_DocBackupUtil->RemoveBackupFile(pdld)))
		{
			if(g_nErrRtn > 10)	continue;

			WriteLogE("[%s] doc remove backup operation fail : [er:%d][id:%d]", m_strLogicName.c_str(), g_nErrRtn, pdld->nID);
			continue;
		}

		nRmCount++;

		HISYNCSTEPUP(pdld->nSyncSvrStep);
		SetLogDoc(*pdld);
	}

	WriteLogN("[%s] doc remove backup operation end [rm_count:%d]", m_strLogicName.c_str(), nRmCount);

	return nRmCount;
}
//---------------------------------------------------------------------------

