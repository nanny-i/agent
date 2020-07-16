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
#include "ManagePoInRegVulnUnit.h"

//---------------------------------------------------------------------------

CManagePoInRegVulnUnit*	t_ManagePoInRegVulnUnit = NULL;

//---------------------------------------------------------------------------

CManagePoInRegVulnUnit::CManagePoInRegVulnUnit()
{
	t_DBMgrPoInRegVulnUnit	= new CDBMgrPoInRegVulnUnit();
}
//---------------------------------------------------------------------------

CManagePoInRegVulnUnit::~CManagePoInRegVulnUnit()
{
	if(t_DBMgrPoInRegVulnUnit)	{	delete t_DBMgrPoInRegVulnUnit;	t_DBMgrPoInRegVulnUnit = NULL;	}
}
//---------------------------------------------------------------------------

INT32		CManagePoInRegVulnUnit::LoadDBMS()
{
	TListDBPoInRegVulnUnit tDBPoInRegVulnUnitList;
    TListDBPoInRegVulnUnitItor begin, end;
	if(SetER(t_DBMgrPoInRegVulnUnit->LoadExecute(&tDBPoInRegVulnUnitList)))
    {
    	return g_nErrRtn;
    }

    begin = tDBPoInRegVulnUnitList.begin();	end = tDBPoInRegVulnUnitList.end();
    for(begin; begin != end; begin++)
    {
    	AddItem(begin->tDPH.nID, *begin);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegVulnUnit::GetHash(UINT32 nID, String& strOrgValue)
{
	PDB_PO_IN_REG_VULN_UNIT pdpirvu 			= NULL;
	{
		if( (pdpirvu = FindItem(nID)) == NULL)
		{
			WriteLogE("not find po_in_reg_vuln_unit by hash : [%d]", ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			return ERR_INFO_NOT_OP_BECAUSE_NOT_FIND;
		}
	}

	{
		strOrgValue = SPrintf("%s,%u,%s,", 
							GetHdrHashInfo(pdpirvu).c_str(),
							pdpirvu->strVulnName.c_str(), pdpirvu->nVulnValue);
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegVulnUnit::AddPoInRegVulnUnit(DB_PO_IN_REG_VULN_UNIT&	dpirvu)
{
	if(SetER(t_DBMgrPoInRegVulnUnit->InsertExecute(&dpirvu)))
    {
    	return g_nErrRtn;
    }

    AddItem(dpirvu.tDPH.nID, dpirvu);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegVulnUnit::EditPoInRegVulnUnit(DB_PO_IN_REG_VULN_UNIT&	dpirvu)
{
	PDB_PO_IN_REG_VULN_UNIT pdpirvu = FindItem(dpirvu.tDPH.nID);
	if(!pdpirvu)	return ERR_DBMS_UPDATE_FAIL;

	if(SetER(t_DBMgrPoInRegVulnUnit->UpdateExecute(&dpirvu)))
    {
    	return g_nErrRtn;
    }

    EditItem(dpirvu.tDPH.nID, dpirvu);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegVulnUnit::DelPoInRegVulnUnit(UINT32 nID)
{
	PDB_PO_IN_REG_VULN_UNIT pdpirvu = FindItem(nID);
	if(!pdpirvu)	return ERR_DBMS_DELETE_FAIL;

	if(SetER(t_DBMgrPoInRegVulnUnit->DeleteExecute(pdpirvu->tDPH.nID)))
    {
    	return g_nErrRtn;
    }

    DeleteItem(nID);
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegVulnUnit::ApplyPoInRegVulnUnit(DB_PO_IN_REG_VULN_UNIT&	dpirvu)
{
	if(FindItem(dpirvu.tDPH.nID))
	{
		return EditPoInRegVulnUnit(dpirvu);
	}
	return AddPoInRegVulnUnit(dpirvu);
}
//---------------------------------------------------------------------------

String					CManagePoInRegVulnUnit::GetName(UINT32 nID)
{
	PDB_PO_IN_REG_VULN_UNIT pdpirvu = FindItem(nID);
    if(!pdpirvu)	return "";
    return pdpirvu->tDPH.strName;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManagePoInRegVulnUnit::SetPkt(MemToken& SendToken)
{
    SendToken.TokenAdd_32(m_tMap.size());

	TMapDBPoInRegVulnUnitItor begin, end;
    begin = m_tMap.begin();	end = m_tMap.end();
    for(begin; begin != end; begin++)
    {
    	SetPkt(&(begin->second), SendToken);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegVulnUnit::SetPkt(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_REG_VULN_UNIT pdpirvu = FindItem(nID);
	if(!pdpirvu)	return -1;

	return SetPkt(pdpirvu, SendToken);
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegVulnUnit::SetPkt(PDB_PO_IN_REG_VULN_UNIT pdpirvu, MemToken& SendToken)
{
	SendToken.TokenAdd_DPH(pdpirvu->tDPH);

	SendToken.TokenAdd_String(pdpirvu->strVulnName);
	SendToken.TokenAdd_32(pdpirvu->nVulnValue);	
	
	SendToken.TokenSet_Block();
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegVulnUnit::GetPkt(MemToken& RecvToken, DB_PO_IN_REG_VULN_UNIT& dpirvu)
{
	if (!RecvToken.TokenDel_DPH(dpirvu.tDPH))						goto	INVALID_PKT;
	
	if ( RecvToken.TokenDel_String(dpirvu.strVulnName) < 0)			goto	INVALID_PKT;	
	if (!RecvToken.TokenDel_32(dpirvu.nVulnValue))					goto	INVALID_PKT;		

	RecvToken.TokenSkip_Block();
	return 0;
INVALID_PKT:
	return -1;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------



