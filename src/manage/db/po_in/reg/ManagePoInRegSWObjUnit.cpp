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
#include "ManagePoInRegSWObjUnit.h"

//---------------------------------------------------------------------------

CManagePoInRegSWObjUnit*	t_ManagePoInRegSWObjUnit = NULL;

//---------------------------------------------------------------------------

CManagePoInRegSWObjUnit::CManagePoInRegSWObjUnit()
{
	t_DBMgrPoInRegSWObjUnit	= new CDBMgrPoInRegSWObjUnit();
}
//---------------------------------------------------------------------------

CManagePoInRegSWObjUnit::~CManagePoInRegSWObjUnit()
{
	if(t_DBMgrPoInRegSWObjUnit)	{	delete t_DBMgrPoInRegSWObjUnit;	t_DBMgrPoInRegSWObjUnit = NULL;	}
}
//---------------------------------------------------------------------------

INT32		CManagePoInRegSWObjUnit::LoadDBMS()
{
	TListDBPoInRegSWObjUnit tDBPoInRegSWObjUnitList;
    TListDBPoInRegSWObjUnitItor begin, end;
	if(SetER(t_DBMgrPoInRegSWObjUnit->LoadExecute(&tDBPoInRegSWObjUnitList)))
    {
    	return g_nErrRtn;
    }

    begin = tDBPoInRegSWObjUnitList.begin();	end = tDBPoInRegSWObjUnitList.end();
    for(begin; begin != end; begin++)
    {
    	AddItem(begin->tDPH.nID, *begin);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSWObjUnit::GetHash(UINT32 nID, String& strOrgValue)
{
	PDB_PO_IN_REG_SW_OBJ_UNIT pdpirsou 			= NULL;
	{
		if( (pdpirsou = FindItem(nID)) == NULL)
		{
			WriteLogE("not find po_in_reg_sw_obj_unit by hash : [%d]", ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			return ERR_INFO_NOT_OP_BECAUSE_NOT_FIND;
		}
	}

	{
		m_strHashValue = SPrintf("%s,%s,", 
							GetHdrHashInfo(pdpirsou).c_str(),
							pdpirsou->strSWName.c_str());

		strOrgValue += m_strHashValue;
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSWObjUnit::AddPoInRegSWObjUnit(DB_PO_IN_REG_SW_OBJ_UNIT&	dpirsou)
{
	if(SetER(t_DBMgrPoInRegSWObjUnit->InsertExecute(&dpirsou)))
    {
    	return g_nErrRtn;
    }

    AddItem(dpirsou.tDPH.nID, dpirsou);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSWObjUnit::EditPoInRegSWObjUnit(DB_PO_IN_REG_SW_OBJ_UNIT&	dpirsou)
{
	PDB_PO_IN_REG_SW_OBJ_UNIT pdpirsou = FindItem(dpirsou.tDPH.nID);
	if(!pdpirsou)	return ERR_DBMS_UPDATE_FAIL;

	if(SetER(t_DBMgrPoInRegSWObjUnit->UpdateExecute(&dpirsou)))
    {
    	return g_nErrRtn;
    }

    EditItem(dpirsou.tDPH.nID, dpirsou);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSWObjUnit::DelPoInRegSWObjUnit(UINT32 nID)
{
	PDB_PO_IN_REG_SW_OBJ_UNIT pdpirsou = FindItem(nID);
	if(!pdpirsou)	return ERR_DBMS_DELETE_FAIL;

	if(SetER(t_DBMgrPoInRegSWObjUnit->DeleteExecute(pdpirsou->tDPH.nID)))
    {
    	return g_nErrRtn;
    }

    DeleteItem(nID);
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSWObjUnit::ApplyPoInRegSWObjUnit(DB_PO_IN_REG_SW_OBJ_UNIT&	dpirsou)
{
	if(FindItem(dpirsou.tDPH.nID))
	{
		return EditPoInRegSWObjUnit(dpirsou);
	}
	return AddPoInRegSWObjUnit(dpirsou);
}
//---------------------------------------------------------------------------

String					CManagePoInRegSWObjUnit::GetName(UINT32 nID)
{
	PDB_PO_IN_REG_SW_OBJ_UNIT pdpirsou = FindItem(nID);
    if(!pdpirsou)	return "";
    return pdpirsou->tDPH.strName;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManagePoInRegSWObjUnit::SetPkt(MemToken& SendToken)
{
    SendToken.TokenAdd_32(m_tMap.size());

	TMapDBPoInRegSWObjUnitItor begin, end;
    begin = m_tMap.begin();	end = m_tMap.end();
    for(begin; begin != end; begin++)
    {
    	SetPkt(&(begin->second), SendToken);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSWObjUnit::SetPkt(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_REG_SW_OBJ_UNIT pdpirsou = FindItem(nID);
	if(!pdpirsou)	return -1;

	return SetPkt(pdpirsou, SendToken);
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSWObjUnit::SetPkt(PDB_PO_IN_REG_SW_OBJ_UNIT pdpirsou, MemToken& SendToken)
{
	SendToken.TokenAdd_DPH(pdpirsou->tDPH);

	SendToken.TokenAdd_String(pdpirsou->strSWName);	

	SendToken.TokenSet_Block();
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSWObjUnit::GetPkt(MemToken& RecvToken, DB_PO_IN_REG_SW_OBJ_UNIT& dpirsou)
{
	if (!RecvToken.TokenDel_DPH(dpirsou.tDPH))					goto	INVALID_PKT;

	if ( RecvToken.TokenDel_String(dpirsou.strSWName) < 0)	goto	INVALID_PKT;	

	RecvToken.TokenSkip_Block();
	return 0;
INVALID_PKT:
	return -1;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------



