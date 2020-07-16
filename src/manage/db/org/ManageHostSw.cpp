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
#include "ManageHostSw.h"

//---------------------------------------------------------------------------

CManageHostSw*	t_ManageHostSw = NULL;

//---------------------------------------------------------------------------

CManageHostSw::CManageHostSw()
{
	t_DBMgrHostSw	= new CDBMgrHostSw();
}
//---------------------------------------------------------------------------

CManageHostSw::~CManageHostSw()
{
	if(t_DBMgrHostSw)		{	delete t_DBMgrHostSw;		t_DBMgrHostSw = NULL;	}
}
//---------------------------------------------------------------------------

INT32		CManageHostSw::LoadDBMS()
{
	TListDBHostSw tDBHostSwList;
    TListDBHostSwItor begin, end;
	if(SetER(t_DBMgrHostSw->LoadExecute(&tDBHostSwList)))
    {
    	return g_nErrRtn;
    }

    begin = tDBHostSwList.begin();	end = tDBHostSwList.end();
    for(begin; begin != end; begin++)
    {
    	AddItem(begin->nID, *begin);

		AddKeyID(begin->nHostID, begin->nID);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManageHostSw::AddHostSw(DB_HOST_SW&	dhs)
{
	if(SetER(t_DBMgrHostSw->InsertExecute(&dhs)))
    {
    	return g_nErrRtn;
    }

    AddItem(dhs.nID, dhs);    
	
	AddKeyID(dhs.nHostID, dhs.nID);
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManageHostSw::EditHostSw(DB_HOST_SW&	dhs)
{
    if(t_DBMgrHostSw->UpdateExecute(&dhs))		return ERR_DBMS_UPDATE_FAIL;

	EditItem(dhs.nID, dhs);
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManageHostSw::DelHostSw(UINT32 nID)
{
	PDB_HOST_SW pdhs = FindItem(nID);
	if(!pdhs)	return ERR_INFO_NOT_DELETE_BECAUSE_NOT_FIND;

	if(SetER(t_DBMgrHostSw->DeleteExecute(pdhs->nID)))
    {
    	return g_nErrRtn;
    }
    
	DelKeyID(pdhs->nHostID);
    DeleteItem(nID);
    return 0;
}
//---------------------------------------------------------------------------

PDB_HOST_SW			CManageHostSw::FindHostKey(UINT32 nHostID)
{
	return FindItem(FindKeyID(nHostID));
}
//---------------------------------------------------------------------------

PDB_HOST_SW		CManageHostSw::FindChkKey(String strChkKey)
{
	TMapDBHostSwItor begin, end;
	begin = m_tMap.begin();	end = m_tMap.end();
	for(begin; begin != end; begin++)
	{
		if(begin->second.strChkKey.compare(strChkKey))
			continue;

		return &(begin->second);
	}
	return NULL;
}
//---------------------------------------------------------------------------

INT32			CManageHostSw::IsExistLocalSw(TListSwInfo* tSwInfoList, String strName)
{
	TListSwInfoItor begin, end;
	begin = tSwInfoList->begin();	end = tSwInfoList->end();
	for(begin; begin != end; begin++)
	{
		if(strName.compare(begin->szName) == 0)		return 1;
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32	CManageHostSw::GetPkt(MemToken& RecvToken, DB_HOST_SW& dhs)
{
	if (!RecvToken.TokenDel_32(dhs.nHostID))				goto INVALID_PKT;
	if (!RecvToken.TokenDel_32(dhs.nUsedFlag))				goto INVALID_PKT;
	if (!RecvToken.TokenDel_32(dhs.nRegDate))				goto INVALID_PKT;
	
	if (!RecvToken.TokenDel_32(dhs.nID))					goto INVALID_PKT;
	if (!RecvToken.TokenDel_32(dhs.nProcArch))				goto INVALID_PKT;

	if ( RecvToken.TokenDel_String(dhs.strChkKey) < 0)		goto INVALID_PKT;
	if ( RecvToken.TokenDel_String(dhs.strName) < 0)		goto INVALID_PKT;
	if ( RecvToken.TokenDel_String(dhs.strPublisher) < 0)	goto INVALID_PKT;
	if ( RecvToken.TokenDel_String(dhs.strInsDate) < 0)		goto INVALID_PKT;
	if ( RecvToken.TokenDel_String(dhs.strVersion) < 0)		goto INVALID_PKT;
	
	RecvToken.TokenSkip_Block();
	return 0;
INVALID_PKT:
	return -1;
}
//---------------------------------------------------------------------------

INT32		CManageHostSw::SetPkt(MemToken& SendToken)
{
	TListID tIDList;
	GetItemIDList(tIDList);
	
	SendToken.TokenAdd_32(tIDList.size());
	TListIDItor begin, end;
	begin = tIDList.begin();	end = tIDList.end();
	for(begin; begin != end; begin++)
	{
		PDB_HOST_SW pdhs = FindItem(*begin);
		if(!pdhs)  	continue;

		SetPkt(pdhs, SendToken);
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32		CManageHostSw::SetPkt(TListDBHostSw& tDBHostSwList, MemToken& SendToken)
{
	SendToken.TokenAdd_32(tDBHostSwList.size());
	TListDBHostSwItor begin, end;
	begin = tDBHostSwList.begin();	end = tDBHostSwList.end();
	for(begin; begin != end; begin++)
	{
		PDB_HOST_SW pdhs = &(*begin);
		if(!pdhs)  	continue;

		SetPkt(pdhs, SendToken);
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32		CManageHostSw::SetPkt(PDB_HOST_SW pdhs, MemToken& SendToken)
{
	SendToken.TokenAdd_32(pdhs->nHostID);
	SendToken.TokenAdd_32(pdhs->nUsedFlag);
	SendToken.TokenAdd_32(pdhs->nRegDate);

	SendToken.TokenAdd_32(pdhs->nID);
	SendToken.TokenAdd_32(pdhs->nProcArch);
	SendToken.TokenAdd_String(pdhs->strChkKey);
	SendToken.TokenAdd_String(pdhs->strName);
	SendToken.TokenAdd_String(pdhs->strPublisher);
	SendToken.TokenAdd_String(pdhs->strInsDate);
	SendToken.TokenAdd_String(pdhs->strVersion);

	SendToken.TokenSet_Block();    
 	return 0;
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

void 		CManageHostSw::RemainDBG_ItemCnt(UINT32 nIdx)
{
	WriteLogN("remain manage item cnt [%d][host_sw] : %u, %u", nIdx, m_tMap.size(), m_tKeyMap.size());
    return;
}
//---------------------------------------------------------------------------





