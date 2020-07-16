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
#include "ManagePoInRegSWSubUnit.h"

//---------------------------------------------------------------------------

CManagePoInRegSWSubUnit*	t_ManagePoInRegSWSubUnit = NULL;

//---------------------------------------------------------------------------

CManagePoInRegSWSubUnit::CManagePoInRegSWSubUnit()
{
	t_DBMgrPoInRegSWSubUnit	= new CDBMgrPoInRegSWSubUnit();
}
//---------------------------------------------------------------------------

CManagePoInRegSWSubUnit::~CManagePoInRegSWSubUnit()
{
	if(t_DBMgrPoInRegSWSubUnit)	{	delete t_DBMgrPoInRegSWSubUnit;	t_DBMgrPoInRegSWSubUnit = NULL;	}
}
//---------------------------------------------------------------------------

INT32		CManagePoInRegSWSubUnit::LoadDBMS()
{
	TListDBPoInRegSWSubUnit tDBPoInRegSWSubUnitList;
    TListDBPoInRegSWSubUnitItor begin, end;
	if(SetER(t_DBMgrPoInRegSWSubUnit->LoadExecute(&tDBPoInRegSWSubUnitList)))
    {
    	return g_nErrRtn;
    }

    begin = tDBPoInRegSWSubUnitList.begin();	end = tDBPoInRegSWSubUnitList.end();
    for(begin; begin != end; begin++)
    {
    	AddItem(begin->tDPH.nID, *begin);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSWSubUnit::GetHash(UINT32 nID, String& strOrgValue)
{
	PDB_PO_IN_REG_SW_SUB_UNIT pdpirssu 			= NULL;
	{
		if( (pdpirssu = FindItem(nID)) == NULL)
		{
			WriteLogE("not find po_in_reg_sw_sub_unit by hash : [%d]", ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			return ERR_INFO_NOT_OP_BECAUSE_NOT_FIND;
		}
	}

	{		
		m_strHashValue = SPrintf("%s,%u,"
							"%s,%s,",							
							GetHdrHashInfo(pdpirssu).c_str(),pdpirssu->nSbType,
							pdpirssu->strSbName.c_str(), pdpirssu->strSbProc.c_str());							

		strOrgValue += m_strHashValue;
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSWSubUnit::AddPoInRegSWSubUnit(DB_PO_IN_REG_SW_SUB_UNIT&	dpirssu)
{
	if(SetER(t_DBMgrPoInRegSWSubUnit->InsertExecute(&dpirssu)))
    {
    	return g_nErrRtn;
    }

    AddItem(dpirssu.tDPH.nID, dpirssu);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSWSubUnit::EditPoInRegSWSubUnit(DB_PO_IN_REG_SW_SUB_UNIT&	dpirssu)
{
	PDB_PO_IN_REG_SW_SUB_UNIT pdpirssu = FindItem(dpirssu.tDPH.nID);
	if(!pdpirssu)	return ERR_DBMS_UPDATE_FAIL;

	if(SetER(t_DBMgrPoInRegSWSubUnit->UpdateExecute(&dpirssu)))
    {
    	return g_nErrRtn;
    }

    EditItem(dpirssu.tDPH.nID, dpirssu);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSWSubUnit::DelPoInRegSWSubUnit(UINT32 nID)
{
	PDB_PO_IN_REG_SW_SUB_UNIT pdpirssu = FindItem(nID);
	if(!pdpirssu)	return ERR_DBMS_DELETE_FAIL;

	if(SetER(t_DBMgrPoInRegSWSubUnit->DeleteExecute(pdpirssu->tDPH.nID)))
    {
    	return g_nErrRtn;
    }

    DeleteItem(nID);
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSWSubUnit::ApplyPoInRegSWSubUnit(DB_PO_IN_REG_SW_SUB_UNIT&	dpirssu)
{
	if(FindItem(dpirssu.tDPH.nID))
	{
		return EditPoInRegSWSubUnit(dpirssu);
	}
	return AddPoInRegSWSubUnit(dpirssu);
}
//---------------------------------------------------------------------------

String					CManagePoInRegSWSubUnit::GetName(UINT32 nID)
{
	PDB_PO_IN_REG_SW_SUB_UNIT pdpirssu = FindItem(nID);
    if(!pdpirssu)	return "";
    return pdpirssu->tDPH.strName;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManagePoInRegSWSubUnit::SetPkt(MemToken& SendToken)
{
    SendToken.TokenAdd_32(m_tMap.size());

	TMapDBPoInRegSWSubUnitItor begin, end;
    begin = m_tMap.begin();	end = m_tMap.end();
    for(begin; begin != end; begin++)
    {
    	SetPkt(&(begin->second), SendToken);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSWSubUnit::SetPkt(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_REG_SW_SUB_UNIT pdpirssu = FindItem(nID);
	if(!pdpirssu)	return -1;

	return SetPkt(pdpirssu, SendToken);
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSWSubUnit::SetPkt(PDB_PO_IN_REG_SW_SUB_UNIT pdpirssu, MemToken& SendToken)
{
	SendToken.TokenAdd_DPH(pdpirssu->tDPH);

	SendToken.TokenAdd_32(pdpirssu->nSbType);	
	SendToken.TokenAdd_String(pdpirssu->strSbName);
	SendToken.TokenAdd_String(pdpirssu->strSbProc);
	
	SendToken.TokenSet_Block();
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSWSubUnit::GetPkt(MemToken& RecvToken, DB_PO_IN_REG_SW_SUB_UNIT& dpirssu)
{
	if (!RecvToken.TokenDel_DPH(dpirssu.tDPH))						goto	INVALID_PKT;

	if (!RecvToken.TokenDel_32(dpirssu.nSbType))					goto	INVALID_PKT;	
	if ( RecvToken.TokenDel_String(dpirssu.strSbName) < 0)			goto	INVALID_PKT;
	if ( RecvToken.TokenDel_String(dpirssu.strSbProc) < 0)			goto	INVALID_PKT;	

	RecvToken.TokenSkip_Block();
	return 0;
INVALID_PKT:
	return -1;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------



