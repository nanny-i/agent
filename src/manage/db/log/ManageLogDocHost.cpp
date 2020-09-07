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
#include "ManageLogDocHost.h"

//---------------------------------------------------------------------------

CManageLogDocHost*	t_ManageLogDocHost = NULL;

//---------------------------------------------------------------------------

CManageLogDocHost::CManageLogDocHost()
{
	t_DBMgrLogDocHost	= new CDBMgrLogDocHost();
}
//---------------------------------------------------------------------------

CManageLogDocHost::~CManageLogDocHost()
{
	if(t_DBMgrLogDocHost)	{	delete t_DBMgrLogDocHost;	t_DBMgrLogDocHost = NULL;	}
}
//---------------------------------------------------------------------------

INT32		CManageLogDocHost::LoadDBMS()
{
	TListDBLogDocHost tDBLogDocHostList;
	TListDBLogDocHostItor begin, end;
	if(SetER(t_DBMgrLogDocHost->LoadExecute(&tDBLogDocHostList)))
    {
    	return g_nErrRtn;
    }
	
	begin = tDBLogDocHostList.begin();	end = tDBLogDocHostList.end();
	for(begin; begin != end; begin++)
	{		
		if(t_ManageLogDoc && t_ManageLogDoc->FindItem(begin->nLogID) == NULL)		continue;
		
		AddItem(*begin);
		AddKeyID(begin->nLogID, begin->nID);
	}

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManageLogDocHost::AddLogDocHost(DB_LOG_DOC_HOST&	data)
{
	if(SetER(t_DBMgrLogDocHost->InsertExecute(&data)))
    {
    	return g_nErrRtn;
    }

    AddItem(data);
	AddKeyID(data.nLogID, data.nID);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManageLogDocHost::EditLogDocHost(DB_LOG_DOC_HOST&	data)
{
	PDB_LOG_DOC_HOST pdata = FindItem(data.nID);
	if(!pdata)	return ERR_INFO_NOT_EDIT_BECAUSE_NOT_FIND;

	if(SetER(t_DBMgrLogDocHost->UpdateExecute(&data)))
    {
    	return g_nErrRtn;
    }

    *pdata = data;
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManageLogDocHost::DelLogDocHost(UINT32 nID)
{
	PDB_LOG_DOC_HOST pdata = FindItem(nID);
	if(!pdata)	return ERR_INFO_NOT_DELETE_BECAUSE_NOT_FIND;

	if(SetER(t_DBMgrLogDocHost->DeleteExecute(pdata->nID)))
    {
    	return g_nErrRtn;
    }

	DelKeyID(pdata->nLogID);
    DeleteItem(nID);
    return 0;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

UINT32					CManageLogDocHost::GetLogDocHostEvtTime(UINT32 nLogID)
{
	PDB_LOG_DOC_HOST pdata = FindKeyItem(nLogID);
	if(!pdata)	return 0;

	return pdata->nEvtTime;
}
//---------------------------------------------------------------------------




