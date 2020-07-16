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
#include "ManagePoInRegSysPkg.h"
#include "ManagePoInRegSWUnitObjPkg.h"
#include "ManagePoInRegSWUnitSubPkg.h"
#include "ManagePoInRegSys.h"

//---------------------------------------------------------------------------

CManagePoInRegSys*	t_ManagePoInRegSys = NULL;

//---------------------------------------------------------------------------

CManagePoInRegSys::CManagePoInRegSys()
{
	t_DBMgrPoInRegSys	= new CDBMgrPoInRegSys();
}
//---------------------------------------------------------------------------

CManagePoInRegSys::~CManagePoInRegSys()
{
	if(t_DBMgrPoInRegSys)	{	delete t_DBMgrPoInRegSys;	t_DBMgrPoInRegSys = NULL;	}
}
//---------------------------------------------------------------------------

INT32		CManagePoInRegSys::LoadDBMS()
{
	TListDBPoInRegSys tDBPoInRegSysList;
    TListDBPoInRegSysItor begin, end;
	if(SetER(t_DBMgrPoInRegSys->LoadExecute(&tDBPoInRegSysList)))
    {
    	return g_nErrRtn;
    }

    begin = tDBPoInRegSysList.begin();	end = tDBPoInRegSysList.end();
    for(begin; begin != end; begin++)
    {
    	AddItem(begin->tDPH.nID, *begin);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSys::InitHash()
{
	t_ManagePoInRegSysPkg->InitPkg();
	
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

INT32					CManagePoInRegSys::InitHash(UINT32 nID)
{
	String strOrgValue;

	PDB_PO_IN_REG_SYS pdpirs 			= NULL;
	{
		if( (pdpirs = FindItem(nID)) == NULL)
		{
			WriteLogE("not find po_in_reg_sys by hash : [%d]", ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			return ERR_INFO_NOT_OP_BECAUSE_NOT_FIND;
		}
	}

	{
		strOrgValue = SPrintf("%s,", GetHdrHashInfo(pdpirs).c_str());

		{
			TMapIDItor begin, end;
			begin = pdpirs->tDPH.tSubIDMap.begin();	end = pdpirs->tDPH.tSubIDMap.end();
			for(begin; begin != end; begin++)
			{
				String strPkgValue;
				t_ManagePoInRegSysPkg->GetHash(begin->first, strPkgValue);
				strOrgValue += strPkgValue;
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

INT32					CManagePoInRegSys::AddPoInRegSys(DB_PO_IN_REG_SYS&	dpirs)
{
	if(SetER(t_DBMgrPoInRegSys->InsertExecute(&dpirs)))
    {
    	return g_nErrRtn;
    }

    AddItem(dpirs.tDPH.nID, dpirs);
	InitHash(dpirs.tDPH.nID);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSys::EditPoInRegSys(DB_PO_IN_REG_SYS&	dpirs)
{
	PDB_PO_IN_REG_SYS pdpirs = FindItem(dpirs.tDPH.nID);
	if(!pdpirs)	return ERR_DBMS_UPDATE_FAIL;

	if(SetER(t_DBMgrPoInRegSys->UpdateExecute(&dpirs)))
    {
    	return g_nErrRtn;
    }

    EditItem(dpirs.tDPH.nID, dpirs);
	InitHash(dpirs.tDPH.nID);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSys::DelPoInRegSys(UINT32 nID)
{
	PDB_PO_IN_REG_SYS pdpirs = FindItem(nID);
	if(!pdpirs)	return ERR_DBMS_DELETE_FAIL;

	if(SetER(t_DBMgrPoInRegSys->DeleteExecute(pdpirs->tDPH.nID)))
    {
    	return g_nErrRtn;
    }

    DeleteItem(nID);
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSys::ApplyPoInRegSys(DB_PO_IN_REG_SYS&	dpirs)
{
	if(FindItem(dpirs.tDPH.nID))
	{
		return EditPoInRegSys(dpirs);
	}
	return AddPoInRegSys(dpirs);
}
//---------------------------------------------------------------------------

String					CManagePoInRegSys::GetName(UINT32 nID)
{
	PDB_PO_IN_REG_SYS pdpirs = FindItem(nID);
    if(!pdpirs)	return "";
    return pdpirs->tDPH.strName;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSys::IsValidPtnFile(UINT32 nID)
{	
	PDB_PO_IN_REG_SYS pdpirs = FindItem(nID);
	if(!pdpirs)	return 0;

	if(pdpirs->tDPH.nUsedMode == STATUS_USED_MODE_OFF)		return 0;

	return 1;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManagePoInRegSys::SetPkt(MemToken& SendToken)
{
    SendToken.TokenAdd_32(m_tMap.size());

	TMapDBPoInRegSysItor begin, end;
    begin = m_tMap.begin();	end = m_tMap.end();
    for(begin; begin != end; begin++)
    {
    	SetPkt(&(begin->second), SendToken);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSys::SetPkt(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_REG_SYS pdpirs = FindItem(nID);
	if(!pdpirs)	return -1;

	SetPkt(pdpirs, SendToken);
	
	{
		SendToken.TokenAdd_32(pdpirs->tDPH.tSubIDMap.size());

		TMapIDItor begin, end;
		begin = pdpirs->tDPH.tSubIDMap.begin();	end = pdpirs->tDPH.tSubIDMap.end();
		for(begin; begin != end; begin++)
		{
			t_ManagePoInRegSysPkg->SetPkt(begin->first, SendToken);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSys::SetPktHost(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_REG_SYS pdpirs = FindItem(nID);
	if(!pdpirs)	return -1;

	SetPkt(pdpirs, SendToken);

	{
		SendToken.TokenAdd_32(pdpirs->tDPH.tSubIDMap.size());

		TMapIDItor begin, end;
		begin = pdpirs->tDPH.tSubIDMap.begin();	end = pdpirs->tDPH.tSubIDMap.end();
		for(begin; begin != end; begin++)
		{
			t_ManagePoInRegSysPkg->SetPktHost(begin->first, SendToken);
		}
	}

	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSys::SetPkt(PDB_PO_IN_REG_SYS pdpirs, MemToken& SendToken)
{
	SendToken.TokenAdd_DPH(pdpirs->tDPH);

	SendToken.TokenSet_Block();
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSys::GetPkt(MemToken& RecvToken, DB_PO_IN_REG_SYS& dpirs)
{
	if (!RecvToken.TokenDel_DPH(dpirs.tDPH))				goto	INVALID_PKT;

	RecvToken.TokenSkip_Block();
	return 0;
INVALID_PKT:
	return -1;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------



