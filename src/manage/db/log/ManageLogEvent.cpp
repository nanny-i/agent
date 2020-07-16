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
#include "ManageLogEvent.h"

//---------------------------------------------------------------------------

CManageLogEvent*	t_ManageLogEvent = NULL;

//---------------------------------------------------------------------------

CManageLogEvent::CManageLogEvent()
{
	t_DBMgrLogEvent	= new CDBMgrLogEvent();
}
//---------------------------------------------------------------------------

CManageLogEvent::~CManageLogEvent()
{
	if(t_DBMgrLogEvent)	{	delete t_DBMgrLogEvent;	t_DBMgrLogEvent = NULL;	}
}
//---------------------------------------------------------------------------

INT32		CManageLogEvent::LoadDBMS()
{
	TListDBLogEvent tDBLogEventList;
	TListDBLogEventItor begin, end;
	if(SetER(t_DBMgrLogEvent->LoadExecute(&tDBLogEventList)))
    {
    	return g_nErrRtn;
    }

	UINT32 nShowLogDay = 0;
	{
		PDB_PO_HOST_RUN pdphr = (PDB_PO_HOST_RUN)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_HOST_RUN);
		if(pdphr)	nShowLogDay = ((GetCurrentDateTimeInt() / 86400) - pdphr->nShowLogDay) * 86400;		
	}

	begin = tDBLogEventList.begin();	end = tDBLogEventList.end();
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

INT32					CManageLogEvent::AddLogEvent(DB_LOG_EVENT&	dle)
{
	if(SetER(t_DBMgrLogEvent->InsertExecute(&dle)))
    {
    	return g_nErrRtn;
    }

    AddItem(dle);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManageLogEvent::EditLogEvent(DB_LOG_EVENT&	dle)
{
	PDB_LOG_EVENT pdle = FindLogEvent(dle.nID);
	if(!pdle)	return ERR_INFO_NOT_EDIT_BECAUSE_NOT_FIND;

	if(SetER(t_DBMgrLogEvent->UpdateExecute(&dle)))
    {
    	return g_nErrRtn;
    }

    EditItem(dle);
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManageLogEvent::DelLogEvent(UINT32 nID)
{
	PDB_LOG_EVENT pdle = FindLogEvent(nID);
	if(!pdle)	return ERR_INFO_NOT_DELETE_BECAUSE_NOT_FIND;

	if(SetER(t_DBMgrLogEvent->DeleteExecute(pdle->nID)))
    {
    	return g_nErrRtn;
    }

    DeleteItem(nID);
    return 0;
}
//---------------------------------------------------------------------------

PDB_LOG_EVENT	CManageLogEvent::FindLogEvent(UINT32 nID)
{
	return FindItem(nID);
}
//---------------------------------------------------------------------------

INT32					CManageLogEvent::GetInitPktList(UINT32 nAdminID, TListPVOID& tInitPktList)
{
	return 0;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManageLogEvent::SetPkt(MemToken& SendToken, UINT32 nAdminID)
{
	TListPVOID tInitPktList;
	GetInitPktList(nAdminID, tInitPktList);

	SendToken.TokenAdd_32(tInitPktList.size());

	TListPVOIDItor begin, end;
	begin = tInitPktList.begin();	end = tInitPktList.end();
	for(begin; begin != end; begin++)
	{
		PDB_LOG_EVENT pdle = (PDB_LOG_EVENT)*begin;

		SetPkt(pdle, SendToken);
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManageLogEvent::SetPkt(MemToken& SendToken)
{
    SendToken.TokenAdd_32(m_tMap.size());

	TMapDBLogEventItor begin, end;	
    begin = m_tMap.begin();	end = m_tMap.end();
    for(begin; begin != end; begin++)
    {
    	SetPkt(&(begin->second), SendToken);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManageLogEvent::SetPkt(PDB_LOG_EVENT pdle, MemToken& SendToken)
{
	SendToken.TokenAdd_32(pdle->nID);
	SendToken.TokenAdd_32(pdle->nRegDate);
	SendToken.TokenAdd_32(pdle->nEvtTime);
	SendToken.TokenAdd_32(pdle->nEvtErrCode);

	SendToken.TokenAdd_32(pdle->nNotifyType);
	SendToken.TokenAdd_32(pdle->nNotifyID);

	SendToken.TokenAdd_32(pdle->nSubjectType);
	SendToken.TokenAdd_32(pdle->nSubjectID);
	SendToken.TokenAdd_String(pdle->strSubjectInfo);

	SendToken.TokenAdd_32(pdle->nTargetType);
	SendToken.TokenAdd_32(pdle->nTargetID);
	SendToken.TokenAdd_String(pdle->strTargetInfo);

	SendToken.TokenAdd_32(pdle->nObjectType);
	SendToken.TokenAdd_32(pdle->nObjectCode);
	SendToken.TokenAdd_32(pdle->nObjectID);
	SendToken.TokenAdd_String(pdle->strObjectInfo);

	SendToken.TokenAdd_32(pdle->nOperationType);
	SendToken.TokenAdd_String(pdle->strEventDescr);

	SendToken.TokenSet_Block();

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManageLogEvent::GetPkt(MemToken& RecvToken, DB_LOG_EVENT& dle)
{
	if (!RecvToken.TokenDel_32(dle.nID))						goto	INVALID_PKT;
	if (!RecvToken.TokenDel_32(dle.nRegDate))					goto	INVALID_PKT;
	if (!RecvToken.TokenDel_32(dle.nEvtTime))					goto	INVALID_PKT;
	if (!RecvToken.TokenDel_32(dle.nEvtErrCode))				goto	INVALID_PKT;

	if (!RecvToken.TokenDel_32(dle.nNotifyType))				goto 	INVALID_PKT;
	if (!RecvToken.TokenDel_32(dle.nNotifyID))					goto 	INVALID_PKT;

	if (!RecvToken.TokenDel_32(dle.nSubjectType))				goto 	INVALID_PKT;
	if (!RecvToken.TokenDel_32(dle.nSubjectID))					goto 	INVALID_PKT;
	if ( RecvToken.TokenDel_String(dle.strSubjectInfo) < 0)		goto	INVALID_PKT;

	if (!RecvToken.TokenDel_32(dle.nTargetType))				goto 	INVALID_PKT;
	if (!RecvToken.TokenDel_32(dle.nTargetID))					goto 	INVALID_PKT;
	if ( RecvToken.TokenDel_String(dle.strTargetInfo) < 0)		goto	INVALID_PKT;

	if (!RecvToken.TokenDel_32(dle.nObjectType))				goto 	INVALID_PKT;
	if (!RecvToken.TokenDel_32(dle.nObjectCode))				goto 	INVALID_PKT;
	if (!RecvToken.TokenDel_32(dle.nObjectID))					goto 	INVALID_PKT;
	if ( RecvToken.TokenDel_String(dle.strObjectInfo) < 0)		goto	INVALID_PKT;

	if (!RecvToken.TokenDel_32(dle.nOperationType))				goto 	INVALID_PKT;
	if ( RecvToken.TokenDel_String(dle.strEventDescr) < 0)		goto	INVALID_PKT;

	RecvToken.TokenSkip_Block();
	return 0;
INVALID_PKT:
	return -1;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------



