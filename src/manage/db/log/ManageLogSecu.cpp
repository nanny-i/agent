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
#include "ManageLogSecu.h"

//---------------------------------------------------------------------------

CManageLogSecu*	t_ManageLogSecu = NULL;

//---------------------------------------------------------------------------

CManageLogSecu::CManageLogSecu()
{
	t_DBMgrLogSecu	= new CDBMgrLogSecu();
}
//---------------------------------------------------------------------------

CManageLogSecu::~CManageLogSecu()
{
	if(t_DBMgrLogSecu)	{	delete t_DBMgrLogSecu;	t_DBMgrLogSecu = NULL;	}
}
//---------------------------------------------------------------------------

INT32		CManageLogSecu::LoadDBMS()
{
	TListDBLogSecu tDBLogSecuList;	
	TListDBLogSecuItor begin, end;
	if(SetER(t_DBMgrLogSecu->LoadExecute(&tDBLogSecuList)))
    {
    	return g_nErrRtn;
    }

	UINT32 nShowLogDay = 0;
	{
		PDB_PO_HOST_RUN pdphr = (PDB_PO_HOST_RUN)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_HOST_RUN);
		if(pdphr)	nShowLogDay = ((GetCurrentDateTimeInt() / 86400) - pdphr->nShowLogDay) * 86400;		
	}

	begin = tDBLogSecuList.begin();	end = tDBLogSecuList.end();
	for(begin; begin != end; begin++)
	{
		if(ISSYNCSTEP(begin->nSyncSvrStep) && (begin->nRegDate < nShowLogDay))
		{
			continue;
		}

		AddItem(*begin);
	}    
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManageLogSecu::AddLogSecu(DB_LOG_SECU&	dls)
{
	if(SetER(t_DBMgrLogSecu->InsertExecute(&dls)))
    {
    	return g_nErrRtn;
    }

    AddItem(dls);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManageLogSecu::EditLogSecu(DB_LOG_SECU&	dls)
{
	PDB_LOG_SECU pdls = FindItem(dls.nID);
	if(!pdls)	return ERR_INFO_NOT_EDIT_BECAUSE_NOT_FIND;

	if(SetER(t_DBMgrLogSecu->UpdateExecute(&dls)))
    {
    	return g_nErrRtn;
    }

    *pdls = dls;

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManageLogSecu::DelLogSecu(UINT32 nID)
{
	PDB_LOG_SECU pdls = FindItem(nID);
	if(!pdls)	return ERR_INFO_NOT_DELETE_BECAUSE_NOT_FIND;

	if(SetER(t_DBMgrLogSecu->DeleteExecute(pdls->nID)))
    {
    	return g_nErrRtn;
    }

    DeleteItem(nID);
    return 0;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManageLogSecu::SetPkt(MemToken& SendToken)
{
    TListPVOID tSendList;

	{
		TMapDBLogSecuItor begin, end;
		begin = m_tMap.begin();	end = m_tMap.end();
		for(begin; begin != end; begin++)
		{
			if(ISSYNCSTEP(begin->second.nSyncSvrStep) || 
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
			SetPkt((PDB_LOG_SECU)(*begin), SendToken);
		}
	}	
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManageLogSecu::SetPkt_Link(MemToken& SendToken)
{
	SendToken.TokenAdd_32(m_tMap.size());
	{
		TMapDBLogSecuItor begin, end;
		begin = m_tMap.begin();	end = m_tMap.end();
		for(begin; begin != end; begin++)
		{
			SetPkt(&(begin->second), SendToken);
		}
	}	
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManageLogSecu::SetPkt(PDB_LOG_SECU pdls, MemToken& SendToken)
{
	SendToken.TokenAdd_32(pdls->nID);
	SendToken.TokenAdd_32(pdls->nRegDate);
	SendToken.TokenAdd_32(pdls->nEvtTime);
	SendToken.TokenAdd_32(pdls->nEvtErrCode);

	SendToken.TokenAdd_32(pdls->nNotifyType);
	SendToken.TokenAdd_32(pdls->nNotifyID);

	SendToken.TokenAdd_32(pdls->nHostID);
	SendToken.TokenAdd_32(pdls->nPolicyType);
	SendToken.TokenAdd_32(pdls->nOpType);

	SendToken.TokenAdd_32(pdls->nRegSvrID);
	SendToken.TokenAdd_32(pdls->nSyncSvrStep);

	SendToken.TokenAdd_32(pdls->nBlockType);
	SendToken.TokenAdd_32(pdls->nObjectType);

	SendToken.TokenAdd_String(pdls->strSubjectPath);
	SendToken.TokenAdd_String(pdls->strSubjectName);
	SendToken.TokenAdd_String(pdls->strObjectPath);
	SendToken.TokenAdd_String(pdls->strObjectName);
	SendToken.TokenAdd_StringW(pdls->strObjectPathW);

	SendToken.TokenSet_Block();

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManageLogSecu::GetPkt(MemToken& RecvToken, DB_LOG_SECU& dls)
{
	if (!RecvToken.TokenDel_32(dls.nID))						goto	INVALID_PKT;
	if (!RecvToken.TokenDel_32(dls.nRegDate))					goto	INVALID_PKT;
	if (!RecvToken.TokenDel_32(dls.nEvtTime))					goto	INVALID_PKT;
	if (!RecvToken.TokenDel_32(dls.nEvtErrCode))				goto	INVALID_PKT;

	if (!RecvToken.TokenDel_32(dls.nNotifyType))				goto 	INVALID_PKT;
	if (!RecvToken.TokenDel_32(dls.nNotifyID))					goto 	INVALID_PKT;

	if (!RecvToken.TokenDel_32(dls.nHostID))					goto 	INVALID_PKT;
	if (!RecvToken.TokenDel_32(dls.nPolicyType))				goto 	INVALID_PKT;
	if (!RecvToken.TokenDel_32(dls.nOpType))					goto 	INVALID_PKT;

	if (!RecvToken.TokenDel_32(dls.nRegSvrID))					goto 	INVALID_PKT;
	if (!RecvToken.TokenDel_32(dls.nSyncSvrStep))				goto 	INVALID_PKT;

	if (!RecvToken.TokenDel_32(dls.nBlockType))					goto 	INVALID_PKT;
	if (!RecvToken.TokenDel_32(dls.nObjectType))				goto 	INVALID_PKT;

	if ( RecvToken.TokenDel_String(dls.strSubjectPath) < 0)		goto	INVALID_PKT;
	if ( RecvToken.TokenDel_String(dls.strSubjectName) < 0)		goto	INVALID_PKT;
	if ( RecvToken.TokenDel_String(dls.strObjectPath) < 0)		goto	INVALID_PKT;
	if ( RecvToken.TokenDel_String(dls.strObjectName) < 0)		goto	INVALID_PKT;
	if ( RecvToken.TokenDel_StringW(dls.strObjectPathW) < 0)	goto	INVALID_PKT;

	RecvToken.TokenSkip_Block();
	return 0;
INVALID_PKT:
	return -1;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------



