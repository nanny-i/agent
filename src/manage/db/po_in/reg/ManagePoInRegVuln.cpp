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
#include "ManagePoInRegVulnPkg.h"
#include "ManagePoInRegVuln.h"

//---------------------------------------------------------------------------

CManagePoInRegVuln*	t_ManagePoInRegVuln = NULL;

//---------------------------------------------------------------------------

CManagePoInRegVuln::CManagePoInRegVuln()
{
	t_DBMgrPoInRegVuln	= new CDBMgrPoInRegVuln();
}
//---------------------------------------------------------------------------

CManagePoInRegVuln::~CManagePoInRegVuln()
{
	if(t_DBMgrPoInRegVuln)	{	delete t_DBMgrPoInRegVuln;	t_DBMgrPoInRegVuln = NULL;	}
}
//---------------------------------------------------------------------------

INT32		CManagePoInRegVuln::LoadDBMS()
{
	TListDBPoInRegVuln tDBPoInRegVulnList;
    TListDBPoInRegVulnItor begin, end;
	if(SetER(t_DBMgrPoInRegVuln->LoadExecute(&tDBPoInRegVulnList)))
    {
    	return g_nErrRtn;
    }

    begin = tDBPoInRegVulnList.begin();	end = tDBPoInRegVulnList.end();
    for(begin; begin != end; begin++)
    {
    	AddItem(begin->tDPH.nID, *begin);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegVuln::InitHash()
{
	t_ManagePoInRegVulnPkg->InitPkg();
	
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

INT32					CManagePoInRegVuln::InitHash(UINT32 nID)
{
	String strOrgValue;

	PDB_PO_IN_REG_VULN pdpirv 			= NULL;
	{
		if( (pdpirv = FindItem(nID)) == NULL)
		{
			WriteLogE("not find po_in_reg_vuln by hash : [%d]", ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			return ERR_INFO_NOT_OP_BECAUSE_NOT_FIND;
		}
	}

	{
		strOrgValue = SPrintf("%s,", 
							GetHdrHashInfo(pdpirv).c_str());

		{
			TMapIDItor begin, end;
			begin = pdpirv->tDPH.tSubIDMap.begin();	end = pdpirv->tDPH.tSubIDMap.end();
			for(begin; begin != end; begin++)
			{
				String strPkgValue;
				t_ManagePoInRegVulnPkg->GetHash(begin->first, strPkgValue);
				strOrgValue += strPkgValue;
			}
		}
	}

	{
		char pszHashValue[CHAR_MAX_SIZE] = {0, };
		SHAString(ASIHASH_SHA_LEN_TYPE_128, strOrgValue.c_str(), strOrgValue.length(), pszHashValue, CHAR_MAX_SIZE);
		pdpirv->tDPH.strHash = pszHashValue;
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegVuln::AddPoInRegVuln(DB_PO_IN_REG_VULN&	dpirv)
{
	if(SetER(t_DBMgrPoInRegVuln->InsertExecute(&dpirv)))
    {
    	return g_nErrRtn;
    }

    AddItem(dpirv.tDPH.nID, dpirv);
	InitHash(dpirv.tDPH.nID);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegVuln::EditPoInRegVuln(DB_PO_IN_REG_VULN&	dpirv)
{
	PDB_PO_IN_REG_VULN pdpirv = FindItem(dpirv.tDPH.nID);
	if(!pdpirv)	return ERR_DBMS_UPDATE_FAIL;

	if(SetER(t_DBMgrPoInRegVuln->UpdateExecute(&dpirv)))
    {
    	return g_nErrRtn;
    }

    EditItem(dpirv.tDPH.nID, dpirv);
	InitHash(dpirv.tDPH.nID);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegVuln::DelPoInRegVuln(UINT32 nID)
{
	PDB_PO_IN_REG_VULN pdpirv = FindItem(nID);
	if(!pdpirv)	return ERR_DBMS_DELETE_FAIL;

	if(SetER(t_DBMgrPoInRegVuln->DeleteExecute(pdpirv->tDPH.nID)))
    {
    	return g_nErrRtn;
    }

    DeleteItem(nID);
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegVuln::ApplyPoInRegVuln(DB_PO_IN_REG_VULN&	dpirv)
{
	if(FindItem(dpirv.tDPH.nID))
	{
		return EditPoInRegVuln(dpirv);
	}
	return AddPoInRegVuln(dpirv);
}
//---------------------------------------------------------------------------

String					CManagePoInRegVuln::GetName(UINT32 nID)
{
	PDB_PO_IN_REG_VULN pdpirv = FindItem(nID);
    if(!pdpirv)	return "";
    return pdpirv->tDPH.strName;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManagePoInRegVuln::SetPkt(MemToken& SendToken)
{
    SendToken.TokenAdd_32(m_tMap.size());

	TMapDBPoInRegVulnItor begin, end;
    begin = m_tMap.begin();	end = m_tMap.end();
    for(begin; begin != end; begin++)
    {
    	SetPkt(&(begin->second), SendToken);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegVuln::SetPkt(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_REG_VULN pdpirv = FindItem(nID);
	if(!pdpirv)	return -1;

	SetPkt(pdpirv, SendToken);
	
	{
		SendToken.TokenAdd_32(pdpirv->tDPH.tSubIDMap.size());

		TMapIDItor begin, end;
		begin = pdpirv->tDPH.tSubIDMap.begin();	end = pdpirv->tDPH.tSubIDMap.end();
		for(begin; begin != end; begin++)
		{
			t_ManagePoInRegVulnPkg->SetPkt(begin->first, SendToken);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegVuln::SetPktHost(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_REG_VULN pdpirv = FindItem(nID);
	if(!pdpirv)	return -1;

	SetPkt(pdpirv, SendToken);

	{
		SendToken.TokenAdd_32(pdpirv->tDPH.tSubIDMap.size());

		TMapIDItor begin, end;
		begin = pdpirv->tDPH.tSubIDMap.begin();	end = pdpirv->tDPH.tSubIDMap.end();
		for(begin; begin != end; begin++)
		{
			t_ManagePoInRegVulnPkg->SetPktHost(begin->first, SendToken);
		}
	}

	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegVuln::SetPkt(PDB_PO_IN_REG_VULN pdpirv, MemToken& SendToken)
{
	SendToken.TokenAdd_DPH(pdpirv->tDPH);

	SendToken.TokenSet_Block();
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegVuln::GetPkt(MemToken& RecvToken, DB_PO_IN_REG_VULN& dpirv)
{
	if (!RecvToken.TokenDel_DPH(dpirv.tDPH))				goto	INVALID_PKT;

	RecvToken.TokenSkip_Block();
	return 0;
INVALID_PKT:
	return -1;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------



