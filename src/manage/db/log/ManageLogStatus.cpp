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
#include "ManageLogStatus.h"

//---------------------------------------------------------------------------

CManageLogStatus*	t_ManageLogStatus = NULL;

//---------------------------------------------------------------------------

CManageLogStatus::CManageLogStatus()
{
	t_DBMgrLogStatus	= new CDBMgrLogStatus();
}
//---------------------------------------------------------------------------

CManageLogStatus::~CManageLogStatus()
{
	if(t_DBMgrLogStatus)	{	delete t_DBMgrLogStatus;	t_DBMgrLogStatus = NULL;	}
}
//---------------------------------------------------------------------------

INT32		CManageLogStatus::LoadDBMS()
{
	TListDBLogStatus tDBLogStatusList;
	TListDBLogStatusItor begin, end;
	if(SetER(t_DBMgrLogStatus->LoadExecute(&tDBLogStatusList)))
    {
    	return g_nErrRtn;
    }

	UINT32 nShowLogDay = 0;
	{
		PDB_PO_HOST_RUN pdphr = (PDB_PO_HOST_RUN)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_HOST_RUN);
		if(pdphr)	nShowLogDay = ((GetCurrentDateTimeInt() / 86400) - pdphr->nShowLogDay) * 86400;		
	}

	begin = tDBLogStatusList.begin();	end = tDBLogStatusList.end();
	for(begin; begin != end; begin++)
	{
		if(begin->nRegDate < nShowLogDay)
		{
			continue;
		}

		AddItem(*begin);
	}
    
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManageLogStatus::AddLogStatus(DB_LOG_STATUS&	dls)
{
	if(SetER(t_DBMgrLogStatus->InsertExecute(&dls)))
    {
    	return g_nErrRtn;
    }

    AddItem(dls);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManageLogStatus::EditLogStatus(DB_LOG_STATUS&	dls)
{
	PDB_LOG_STATUS pdls = FindLogStatus(dls.nID);
	if(!pdls)	return ERR_INFO_NOT_EDIT_BECAUSE_NOT_FIND;

	if(SetER(t_DBMgrLogStatus->UpdateExecute(&dls)))
    {
    	return g_nErrRtn;
    }

    EditItem(dls);
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManageLogStatus::DelLogStatus(UINT32 nID)
{
	PDB_LOG_STATUS pdls = FindLogStatus(nID);
	if(!pdls)	return ERR_INFO_NOT_DELETE_BECAUSE_NOT_FIND;

	if(SetER(t_DBMgrLogStatus->DeleteExecute(pdls->nID)))
    {
    	return g_nErrRtn;
    }

    DeleteItem(nID);
    return 0;
}
//---------------------------------------------------------------------------

PDB_LOG_STATUS		CManageLogStatus::FindLogStatus(UINT32 nID)
{
	return FindItem(nID);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
INT32					CManageLogStatus::IsExistLogStatus(DB_LOG_STATUS&	dls)
{
	TMapDBLogStatusRItor begin, end;
	begin = m_tMap.rbegin();	end = m_tMap.rend();
	for(begin; begin != end; begin++)
	{
		if(begin->second.nObjectType == dls.nObjectType &&
			begin->second.nObjectCode == dls.nObjectCode &&
			begin->second.nObjectID == dls.nObjectID &&
			begin->second.nOperationType == dls.nOperationType)		
		{
			return begin->second.nID;
		}
	}
	return 0;
}

//---------------------------------------------------------------------------

String					CManageLogStatus::GetFullDesc(DB_LOG_STATUS dlst)
{
	return	MapID_StrToStr(dlst.tDescIDStrMap);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManageLogStatus::SetPkt(MemToken& SendToken)
{
	TListPVOID tSendList;

	{
		TMapDBLogStatusItor begin, end;
		begin = m_tMap.begin();	end = m_tMap.end();
		for(begin; begin != end; begin++)
		{
			if(	ISSYNCSTEP(begin->second.nSyncSvrStep) || 
				(begin->second.nSkipTarget & SS_ENV_LOG_OPTION_FLAGE_SKIP_SAVE_SERVER))	continue;

			tSendList.push_back(&(begin->second));
		}
		if(tSendList.empty())	return -1;
	}

	SendToken.TokenAdd_32(tSendList.size());
	{
		TListPVOIDItor begin, end;
		begin = tSendList.begin();	end = tSendList.end();
		for(begin; begin != end; begin++)
		{
			PDB_LOG_STATUS pdls = (PDB_LOG_STATUS)*begin;
			if(!pdls)
				continue;

			SetPkt(pdls, SendToken);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManageLogStatus::SetPkt_Link(MemToken& SendToken)
{
    SendToken.TokenAdd_32(m_tMap.size());

	TMapDBLogStatusItor begin, end;	
    begin = m_tMap.begin();	end = m_tMap.end();
    for(begin; begin != end; begin++)
    {
    	SetPkt(&(begin->second), SendToken);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManageLogStatus::SetPkt(PDB_LOG_STATUS pdls, MemToken& SendToken)
{
	SendToken.TokenAdd_32(pdls->nID);
	SendToken.TokenAdd_32(pdls->nRegDate);
	SendToken.TokenAdd_32(pdls->nEvtTime);
	SendToken.TokenAdd_32(pdls->nEvtErrCode);

	SendToken.TokenAdd_32(pdls->nNotifyType);
	SendToken.TokenAdd_32(pdls->nNotifyID);

	SendToken.TokenAdd_32(pdls->nHostID);
	SendToken.TokenAdd_32(pdls->nRegSvrID);
	SendToken.TokenAdd_32(pdls->nSyncSvrStep);

	SendToken.TokenAdd_32(pdls->nSubjectType);
	SendToken.TokenAdd_32(pdls->nSubjectID);
	SendToken.TokenAdd_String(pdls->strSubjectInfo);

	SendToken.TokenAdd_32(pdls->nTargetType);
	SendToken.TokenAdd_32(pdls->nTargetID);
	SendToken.TokenAdd_String(pdls->strTargetInfo);

	SendToken.TokenAdd_32(pdls->nObjectType);
	SendToken.TokenAdd_32(pdls->nObjectCode);
	SendToken.TokenAdd_32(pdls->nObjectID);
	SendToken.TokenAdd_String(pdls->strObjectInfo);

	SendToken.TokenAdd_32(pdls->nOperationType);
	SendToken.TokenAdd_IDMapStr(pdls->tDescIDStrMap);

	SendToken.TokenAdd_32(pdls->nExtOption);

	SendToken.TokenSet_Block();

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManageLogStatus::GetPkt(MemToken& RecvToken, DB_LOG_STATUS& dls)
{
	if (!RecvToken.TokenDel_32(dls.nID))						goto	INVALID_PKT;
	if (!RecvToken.TokenDel_32(dls.nRegDate))					goto	INVALID_PKT;
	if (!RecvToken.TokenDel_32(dls.nEvtTime))					goto	INVALID_PKT;
	if (!RecvToken.TokenDel_32(dls.nEvtErrCode))				goto	INVALID_PKT;

	if (!RecvToken.TokenDel_32(dls.nNotifyType))				goto 	INVALID_PKT;
	if (!RecvToken.TokenDel_32(dls.nNotifyID))					goto 	INVALID_PKT;

	if (!RecvToken.TokenDel_32(dls.nHostID))					goto	INVALID_PKT;
	if (!RecvToken.TokenDel_32(dls.nRegSvrID))					goto 	INVALID_PKT;
	if (!RecvToken.TokenDel_32(dls.nSyncSvrStep))				goto 	INVALID_PKT;

	if (!RecvToken.TokenDel_32(dls.nSubjectType))				goto 	INVALID_PKT;
	if (!RecvToken.TokenDel_32(dls.nSubjectID))					goto 	INVALID_PKT;
	if ( RecvToken.TokenDel_String(dls.strSubjectInfo) < 0)		goto	INVALID_PKT;

	if (!RecvToken.TokenDel_32(dls.nTargetType))				goto 	INVALID_PKT;
	if (!RecvToken.TokenDel_32(dls.nTargetID))					goto 	INVALID_PKT;
	if ( RecvToken.TokenDel_String(dls.strTargetInfo) < 0)		goto	INVALID_PKT;

	if (!RecvToken.TokenDel_32(dls.nObjectType))				goto 	INVALID_PKT;
	if (!RecvToken.TokenDel_32(dls.nObjectCode))				goto 	INVALID_PKT;
	if (!RecvToken.TokenDel_32(dls.nObjectID))					goto 	INVALID_PKT;
	if ( RecvToken.TokenDel_String(dls.strObjectInfo) < 0)		goto	INVALID_PKT;

	if (!RecvToken.TokenDel_32(dls.nOperationType))				goto 	INVALID_PKT;
	if ( RecvToken.TokenDel_IDMapStr(dls.tDescIDStrMap) < 0)	goto	INVALID_PKT;

	if (!RecvToken.TokenDel_32(dls.nExtOption))					goto	INVALID_PKT;

	RecvToken.TokenSkip_Block();
	return 0;
INVALID_PKT:
	return -1;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------



