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
#include "ManageErrorCode.h"

//---------------------------------------------------------------------------

CManageErrorCode*	t_ManageErrorCode = NULL;

//---------------------------------------------------------------------------

CManageErrorCode::CManageErrorCode()
{
	t_DBMgrErrorCode	= new CDBMgrErrorCode();    
}
//---------------------------------------------------------------------------

CManageErrorCode::~CManageErrorCode()
{
	if(t_DBMgrErrorCode)
	{
		delete t_DBMgrErrorCode;
		t_DBMgrErrorCode = NULL;
	}
}
//---------------------------------------------------------------------------

INT32		CManageErrorCode::LoadDBMS()
{
	TListDBErrorCode tDBErrorCodeList;
    TListDBErrorCodeItor begin, end;
	if(SetER(t_DBMgrErrorCode->LoadExecute(&tDBErrorCodeList)))
    {
    	return g_nErrRtn;
    }

    begin = tDBErrorCodeList.begin();	end = tDBErrorCodeList.end();
    for(begin; begin != end; begin++)
    {
    	AddItem(begin->nID, *begin);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManageErrorCode::SetPkt(MemToken& SendToken)
{
	SendToken.TokenAdd_32(m_tMap.size());

	TMapDBErrorCodeItor begin, end;
    begin = m_tMap.begin();	end = m_tMap.end();
    for(begin; begin != end; begin++)
    {
    	SetPkt(&(begin->second), SendToken);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManageErrorCode::SetPkt(PDB_ERROR_CODE pdee, MemToken& SendToken)
{
	SendToken.TokenAdd_32(pdee->nID);
    SendToken.TokenAdd_String(pdee->lan_kor.strType);
    SendToken.TokenAdd_String(pdee->lan_kor.strDescr);
    SendToken.TokenAdd_String(pdee->lan_eng.strType);
	SendToken.TokenAdd_String(pdee->lan_eng.strDescr);

	SendToken.TokenSet_Block();

    return 0;
}
//---------------------------------------------------------------------------


