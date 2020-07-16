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
#include "ManagePoInRegSvcPkg.h"
#include "ManagePoInRegSvc.h"

//---------------------------------------------------------------------------

CManagePoInRegSvc*	t_ManagePoInRegSvc = NULL;

//---------------------------------------------------------------------------

CManagePoInRegSvc::CManagePoInRegSvc()
{
	t_DBMgrPoInRegSvc	= new CDBMgrPoInRegSvc();
}
//---------------------------------------------------------------------------

CManagePoInRegSvc::~CManagePoInRegSvc()
{
	if(t_DBMgrPoInRegSvc)	{	delete t_DBMgrPoInRegSvc;	t_DBMgrPoInRegSvc = NULL;	}
}
//---------------------------------------------------------------------------

INT32		CManagePoInRegSvc::LoadDBMS()
{
	TListDBPoInRegSvc tDBPoInRegSvcList;
    TListDBPoInRegSvcItor begin, end;
	if(SetER(t_DBMgrPoInRegSvc->LoadExecute(&tDBPoInRegSvcList)))
    {
    	return g_nErrRtn;
    }

    begin = tDBPoInRegSvcList.begin();	end = tDBPoInRegSvcList.end();
    for(begin; begin != end; begin++)
    {
    	AddItem(begin->tDPH.nID, *begin);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvc::InitHash()
{
	t_ManagePoInRegSvcPkg->InitPkg();
	
	TListID tIDList;
	TListIDItor begin, end;

	GetItemIDList(tIDList);
	begin = tIDList.begin();		end = tIDList.end();
	for(begin; begin != end; begin++)
	{
		InitHash(*begin);
	}	
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvc::InitHash(UINT32 nID)
{
	String strOrgValue;

	PDB_PO_IN_REG_SVC pdpirs 			= NULL;
	{
		if( (pdpirs = FindItem(nID)) == NULL)
		{
			WriteLogE("not find po_in_reg_svc by hash : [%d]", ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			return ERR_INFO_NOT_OP_BECAUSE_NOT_FIND;
		}
	}

	{
		strOrgValue = SPrintf("%s,", 
							GetHdrHashInfo(pdpirs).c_str());

		{
			TMapIDItor begin, end;
			begin = pdpirs->tDPH.tSubIDMap.begin();	end = pdpirs->tDPH.tSubIDMap.end();
			for(begin; begin != end; begin++)
			{
				t_ManagePoInRegSvcPkg->GetHash(begin->first, EmptyStr(m_strHashValue));
				strOrgValue += m_strHashValue;
			}
		}
	}

	{
		char pszHashValue[CHAR_MAX_SIZE] = {0, };
		SHAString(ASIHASH_SHA_LEN_TYPE_128, strOrgValue.c_str(), strOrgValue.length(), pszHashValue, CHAR_MAX_SIZE);
		pdpirs->tDPH.strHash = pszHashValue;
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvc::AddPoInRegSvc(DB_PO_IN_REG_SVC&	dpirs)
{
	if(SetER(t_DBMgrPoInRegSvc->InsertExecute(&dpirs)))
    {
    	return g_nErrRtn;
    }

    AddItem(dpirs.tDPH.nID, dpirs);
	InitHash(dpirs.tDPH.nID);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvc::EditPoInRegSvc(DB_PO_IN_REG_SVC&	dpirs)
{
	PDB_PO_IN_REG_SVC pdpirs = FindItem(dpirs.tDPH.nID);
	if(!pdpirs)	return ERR_DBMS_UPDATE_FAIL;

	if(SetER(t_DBMgrPoInRegSvc->UpdateExecute(&dpirs)))
    {
    	return g_nErrRtn;
    }

    EditItem(dpirs.tDPH.nID, dpirs);
	InitHash(dpirs.tDPH.nID);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvc::DelPoInRegSvc(UINT32 nID)
{
	PDB_PO_IN_REG_SVC pdpirs = FindItem(nID);
	if(!pdpirs)	return ERR_DBMS_DELETE_FAIL;

	if(SetER(t_DBMgrPoInRegSvc->DeleteExecute(pdpirs->tDPH.nID)))
    {
    	return g_nErrRtn;
    }

    DeleteItem(nID);
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvc::ApplyPoInRegSvc(DB_PO_IN_REG_SVC&	dpirs)
{
	if(FindItem(dpirs.tDPH.nID))
	{
		return EditPoInRegSvc(dpirs);
	}
	return AddPoInRegSvc(dpirs);
}
//---------------------------------------------------------------------------

String					CManagePoInRegSvc::GetName(UINT32 nID)
{
	PDB_PO_IN_REG_SVC pdpirs = FindItem(nID);
    if(!pdpirs)	return "";
    return pdpirs->tDPH.strName;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvc::IsValidPtnFile(UINT32 nID)
{	
	PDB_PO_IN_REG_SVC pdpirs = FindItem(nID);
	if(!pdpirs)	return 0;

	if(pdpirs->tDPH.nUsedMode == STATUS_USED_MODE_OFF)		return 0;

	return 1;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvc::SetPkt(MemToken& SendToken)
{
    SendToken.TokenAdd_32(m_tMap.size());

	TMapDBPoInRegSvcItor begin, end;
    begin = m_tMap.begin();	end = m_tMap.end();
    for(begin; begin != end; begin++)
    {
    	SetPkt(&(begin->second), SendToken);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvc::SetPkt(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_REG_SVC pdpirs = FindItem(nID);
	if(!pdpirs)	return -1;

	SetPkt(pdpirs, SendToken);
	
	{
		SendToken.TokenAdd_32(pdpirs->tDPH.tSubIDMap.size());

		TMapIDItor begin, end;
		begin = pdpirs->tDPH.tSubIDMap.begin();	end = pdpirs->tDPH.tSubIDMap.end();
		for(begin; begin != end; begin++)
		{
			t_ManagePoInRegSvcPkg->SetPkt(begin->first, SendToken);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvc::SetPktHost(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_REG_SVC pdpirs = FindItem(nID);
	if(!pdpirs)	return -1;
	
	SetPkt(pdpirs, SendToken);

	{		
		SendToken.TokenAdd_32(pdpirs->tDPH.tSubIDMap.size());

		TMapIDItor begin, end;
		begin = pdpirs->tDPH.tSubIDMap.begin();	end = pdpirs->tDPH.tSubIDMap.end();
		for(begin; begin != end; begin++)
		{
			t_ManagePoInRegSvcPkg->SetPktHost(begin->first, SendToken);
		}
	}

	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvc::SetPkt(PDB_PO_IN_REG_SVC pdpirs, MemToken& SendToken)
{
	SendToken.TokenAdd_DPH(pdpirs->tDPH);

	SendToken.TokenSet_Block();
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvc::GetPkt(MemToken& RecvToken, DB_PO_IN_REG_SVC& dpirs)
{
	if (!RecvToken.TokenDel_DPH(dpirs.tDPH))				goto	INVALID_PKT;	

	RecvToken.TokenSkip_Block();
	return 0;
INVALID_PKT:
	return -1;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------



