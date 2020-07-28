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
#include "ManageHostSys.h"

//---------------------------------------------------------------------------

CManageHostSys*	t_ManageHostSys = NULL;

//---------------------------------------------------------------------------

CManageHostSys::CManageHostSys()
{
	t_DBMgrHostSys	= new CDBMgrHostSys();
}
//---------------------------------------------------------------------------

CManageHostSys::~CManageHostSys()
{
	if(t_DBMgrHostSys)		{	delete t_DBMgrHostSys;		t_DBMgrHostSys = NULL;	}
}
//---------------------------------------------------------------------------

INT32		CManageHostSys::LoadDBMS()
{	
	TListDBHostSys tDBHostSysList;
    TListDBHostSysItor begin, end;
	
	if(SetER(t_DBMgrHostSys->LoadExecute(&tDBHostSysList)))
    {		
    	return g_nErrRtn;
    }

    begin = tDBHostSysList.begin();	end = tDBHostSysList.end();
    for(begin; begin != end; begin++)
    {
    	AddItem(begin->nID, *begin);
    }

	// 20200724  edit jhjung
	if(tDBHostSysList.size() == 0)
	{
		DB_HOST_SYS dhs;
		memset(&dhs, 0, sizeof(DB_HOST_SYS));
		AddHostSys(dhs);
	}
	else
	{
		PDB_HOST_SYS pdhs = FirstItem();
		if(pdhs)	SetHostSysType(pdhs->nOsID);
	}
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManageHostSys::AddHostSys(DB_HOST_SYS&	dhs)
{
	if(SetER(t_DBMgrHostSys->InsertExecute(&dhs)))
    {
    	return g_nErrRtn;
    }

    AddItem(dhs.nID, dhs);     
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManageHostSys::EditHostSys(DB_HOST_SYS&	dhs)
{
    if(t_DBMgrHostSys->UpdateExecute(&dhs))		return ERR_DBMS_UPDATE_FAIL;

	EditItem(dhs.nID, dhs);
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManageHostSys::DelHostSys(UINT32 nID)
{
	PDB_HOST_SYS pdhs = FindItem(nID);
	if(!pdhs)	return ERR_INFO_NOT_DELETE_BECAUSE_NOT_FIND;

	if(SetER(t_DBMgrHostSys->DeleteExecute(pdhs->nID)))
    {
    	return g_nErrRtn;
    }
    DeleteItem(nID);
    return 0;
}
//---------------------------------------------------------------------------

INT32	CManageHostSys::GetPkt(MemToken& RecvToken, DB_HOST_SYS& dhs, UINT32 nPktType)
{
	if (!RecvToken.TokenDel_64(dhs.nOsID))						goto INVALID_PKT;
	if (!RecvToken.TokenDel_32(dhs.nOsSP))						goto INVALID_PKT;
	if (!RecvToken.TokenDel_32(dhs.nOsPd))						goto INVALID_PKT;
	if ( RecvToken.TokenDel_String(dhs.strOsPdLux) < 0)			goto INVALID_PKT;
	if (!RecvToken.TokenDel_32(dhs.nOsPa))						goto INVALID_PKT;
	
	RecvToken.TokenSkip_Block();
	return 0;
INVALID_PKT:
	return -1;
}
//-------------------------------------------------------------------------------------

INT32		CManageHostSys::SetPkt(MemToken& SendToken)
{
	SendToken.TokenAdd_32(m_tMap.size());

	TMapDBHostSysItor begin, end;
	begin = m_tMap.begin();	end = m_tMap.end();
	for(begin; begin != end; begin++)
	{
		PDB_HOST_SYS pdhs = &(begin->second);
		if(!pdhs)  	continue;

		SetPkt(pdhs, SendToken);
	}
	return 0;
}
//-------------------------------------------------------------------------------------

INT32		CManageHostSys::SetPkt(PDB_HOST_SYS pdhs, MemToken& SendToken)
{
	SendToken.TokenAdd_64(pdhs->nOsID);
	SendToken.TokenAdd_32(pdhs->nOsSP);
	SendToken.TokenAdd_32(pdhs->nOsPd);
	SendToken.TokenAdd_String(pdhs->strOsPdLux);
	SendToken.TokenAdd_32(pdhs->nOsPa);

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

INT32			CManageHostSys::SetHostSysType(UINT64 nOsID)
{
	if(nOsID < ASI_SYSTEM_ID_LAST)
		t_EnvInfo->m_nHostSysType = ASI_SYSTEM_OS_TYPE_WIN;
	else 
		t_EnvInfo->m_nHostSysType = ASI_SYSTEM_OS_TYPE_LINUX;

	return 0;
}
//--------------------------------------------------------------------------- 

