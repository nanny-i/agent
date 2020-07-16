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
#include "ManagePoInRegSysUnit.h"

//---------------------------------------------------------------------------

CManagePoInRegSysUnit*	t_ManagePoInRegSysUnit = NULL;

//---------------------------------------------------------------------------

CManagePoInRegSysUnit::CManagePoInRegSysUnit()
{
	t_DBMgrPoInRegSysUnit	= new CDBMgrPoInRegSysUnit();
}
//---------------------------------------------------------------------------

CManagePoInRegSysUnit::~CManagePoInRegSysUnit()
{
	if(t_DBMgrPoInRegSysUnit)	{	delete t_DBMgrPoInRegSysUnit;	t_DBMgrPoInRegSysUnit = NULL;	}
}
//---------------------------------------------------------------------------

INT32		CManagePoInRegSysUnit::LoadDBMS()
{
	TListDBPoInRegSysUnit tDBPoInRegSysUnitList;
    TListDBPoInRegSysUnitItor begin, end;
	if(SetER(t_DBMgrPoInRegSysUnit->LoadExecute(&tDBPoInRegSysUnitList)))
    {
    	return g_nErrRtn;
    }

    begin = tDBPoInRegSysUnitList.begin();	end = tDBPoInRegSysUnitList.end();
    for(begin; begin != end; begin++)
    {
    	AddItem(begin->tDPH.nID, *begin);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSysUnit::GetHash(UINT32 nID, String& strOrgValue)
{
	PDB_PO_IN_REG_SYS_UNIT pdpirsu 			= NULL;
	{
		if( (pdpirsu = FindItem(nID)) == NULL)
		{
			WriteLogE("not find po_in_reg_sys_unit by hash : [%d]", ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			return ERR_INFO_NOT_OP_BECAUSE_NOT_FIND;
		}
	}

	{
		strOrgValue = SPrintf("%s,%u,%u,%s,", 
							GetHdrHashInfo(pdpirsu).c_str(),
							pdpirsu->nSysType, pdpirsu->nSysPerm, pdpirsu->strSysName.c_str());
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSysUnit::AddPoInRegSysUnit(DB_PO_IN_REG_SYS_UNIT&	dpirsu)
{
	if(SetER(t_DBMgrPoInRegSysUnit->InsertExecute(&dpirsu)))
    {
    	return g_nErrRtn;
    }

    AddItem(dpirsu.tDPH.nID, dpirsu);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSysUnit::EditPoInRegSysUnit(DB_PO_IN_REG_SYS_UNIT&	dpirsu)
{
	PDB_PO_IN_REG_SYS_UNIT pdpirsu = FindItem(dpirsu.tDPH.nID);
	if(!pdpirsu)	return ERR_DBMS_UPDATE_FAIL;

	if(SetER(t_DBMgrPoInRegSysUnit->UpdateExecute(&dpirsu)))
    {
    	return g_nErrRtn;
    }

    EditItem(dpirsu.tDPH.nID, dpirsu);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSysUnit::DelPoInRegSysUnit(UINT32 nID)
{
	PDB_PO_IN_REG_SYS_UNIT pdpirsu = FindItem(nID);
	if(!pdpirsu)	return ERR_DBMS_DELETE_FAIL;

	if(SetER(t_DBMgrPoInRegSysUnit->DeleteExecute(pdpirsu->tDPH.nID)))
    {
    	return g_nErrRtn;
    }

    DeleteItem(nID);
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSysUnit::ApplyPoInRegSysUnit(DB_PO_IN_REG_SYS_UNIT&	dpirsu)
{
	if(FindItem(dpirsu.tDPH.nID))
	{
		return EditPoInRegSysUnit(dpirsu);
	}
	return AddPoInRegSysUnit(dpirsu);
}
//---------------------------------------------------------------------------

String					CManagePoInRegSysUnit::GetName(UINT32 nID)
{
	PDB_PO_IN_REG_SYS_UNIT pdpirsu = FindItem(nID);
    if(!pdpirsu)	return "";
    return pdpirsu->tDPH.strName;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManagePoInRegSysUnit::SetPkt(MemToken& SendToken)
{
    SendToken.TokenAdd_32(m_tMap.size());

	TMapDBPoInRegSysUnitItor begin, end;
    begin = m_tMap.begin();	end = m_tMap.end();
    for(begin; begin != end; begin++)
    {
    	SetPkt(&(begin->second), SendToken);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSysUnit::SetPkt(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_REG_SYS_UNIT pdpirsu = FindItem(nID);
	if(!pdpirsu)	return -1;

	return SetPkt(pdpirsu, SendToken);
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSysUnit::SetPkt(PDB_PO_IN_REG_SYS_UNIT pdpirsu, MemToken& SendToken)
{
	SendToken.TokenAdd_DPH(pdpirsu->tDPH);

	SendToken.TokenAdd_32(pdpirsu->nSysType);
	SendToken.TokenAdd_32(pdpirsu->nSysPerm);
	SendToken.TokenAdd_String(pdpirsu->strSysName);
	
	SendToken.TokenSet_Block();
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSysUnit::GetPkt(MemToken& RecvToken, DB_PO_IN_REG_SYS_UNIT& dpirsu)
{
	if (!RecvToken.TokenDel_DPH(dpirsu.tDPH))						goto	INVALID_PKT;
	
	if (!RecvToken.TokenDel_32(dpirsu.nSysType))					goto	INVALID_PKT;	
	if (!RecvToken.TokenDel_32(dpirsu.nSysPerm))					goto	INVALID_PKT;	
	if ( RecvToken.TokenDel_String(dpirsu.strSysName) < 0)			goto	INVALID_PKT;	

	RecvToken.TokenSkip_Block();
	return 0;
INVALID_PKT:
	return -1;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------



