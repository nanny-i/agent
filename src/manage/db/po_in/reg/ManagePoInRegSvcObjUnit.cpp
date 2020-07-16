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
#include "ManagePoInRegSvcObjUnit.h"

//---------------------------------------------------------------------------

CManagePoInRegSvcObjUnit*	t_ManagePoInRegSvcObjUnit = NULL;

//---------------------------------------------------------------------------

CManagePoInRegSvcObjUnit::CManagePoInRegSvcObjUnit()
{
	t_DBMgrPoInRegSvcObjUnit	= new CDBMgrPoInRegSvcObjUnit();
}
//---------------------------------------------------------------------------

CManagePoInRegSvcObjUnit::~CManagePoInRegSvcObjUnit()
{
	if(t_DBMgrPoInRegSvcObjUnit)	{	delete t_DBMgrPoInRegSvcObjUnit;	t_DBMgrPoInRegSvcObjUnit = NULL;	}
}
//---------------------------------------------------------------------------

INT32		CManagePoInRegSvcObjUnit::LoadDBMS()
{
	TListDBPoInRegSvcObjUnit tDBPoInRegSvcObjUnitList;
    TListDBPoInRegSvcObjUnitItor begin, end;
	if(SetER(t_DBMgrPoInRegSvcObjUnit->LoadExecute(&tDBPoInRegSvcObjUnitList)))
    {
    	return g_nErrRtn;
    }

    begin = tDBPoInRegSvcObjUnitList.begin();	end = tDBPoInRegSvcObjUnitList.end();
    for(begin; begin != end; begin++)
    {
    	AddItem(begin->tDPH.nID, *begin);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvcObjUnit::GetHash(UINT32 nID, String& strOrgValue)
{
	PDB_PO_IN_REG_SVC_OBJ_UNIT pdpirsou 			= NULL;
	{
		if( (pdpirsou = FindItem(nID)) == NULL)
		{
			WriteLogE("not find po_in_reg_svc_obj_unit by hash : [%d]", ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			return ERR_INFO_NOT_OP_BECAUSE_NOT_FIND;
		}
	}

	{
		m_strHashValue = SPrintf("%s,%s,", 
							GetHdrHashInfo(pdpirsou).c_str(),
							pdpirsou->strSvcName.c_str());

		strOrgValue += m_strHashValue;
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvcObjUnit::AddPoInRegSvcObjUnit(DB_PO_IN_REG_SVC_OBJ_UNIT&	dpirsou)
{
	if(SetER(t_DBMgrPoInRegSvcObjUnit->InsertExecute(&dpirsou)))
    {
    	return g_nErrRtn;
    }

    AddItem(dpirsou.tDPH.nID, dpirsou);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvcObjUnit::EditPoInRegSvcObjUnit(DB_PO_IN_REG_SVC_OBJ_UNIT&	dpirsou)
{
	PDB_PO_IN_REG_SVC_OBJ_UNIT pdpirsou = FindItem(dpirsou.tDPH.nID);
	if(!pdpirsou)	return ERR_DBMS_UPDATE_FAIL;

	if(SetER(t_DBMgrPoInRegSvcObjUnit->UpdateExecute(&dpirsou)))
    {
    	return g_nErrRtn;
    }

    EditItem(dpirsou.tDPH.nID, dpirsou);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvcObjUnit::DelPoInRegSvcObjUnit(UINT32 nID)
{
	PDB_PO_IN_REG_SVC_OBJ_UNIT pdpirsou = FindItem(nID);
	if(!pdpirsou)	return ERR_DBMS_DELETE_FAIL;

	if(SetER(t_DBMgrPoInRegSvcObjUnit->DeleteExecute(pdpirsou->tDPH.nID)))
    {
    	return g_nErrRtn;
    }

    DeleteItem(nID);
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvcObjUnit::ApplyPoInRegSvcObjUnit(DB_PO_IN_REG_SVC_OBJ_UNIT&	dpirsou)
{
	if(FindItem(dpirsou.tDPH.nID))
	{
		return EditPoInRegSvcObjUnit(dpirsou);
	}
	return AddPoInRegSvcObjUnit(dpirsou);
}
//---------------------------------------------------------------------------

String					CManagePoInRegSvcObjUnit::GetName(UINT32 nID)
{
	PDB_PO_IN_REG_SVC_OBJ_UNIT pdpirsou = FindItem(nID);
    if(!pdpirsou)	return "";
    return pdpirsou->tDPH.strName;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvcObjUnit::SetPkt(MemToken& SendToken)
{
    SendToken.TokenAdd_32(m_tMap.size());

	TMapDBPoInRegSvcObjUnitItor begin, end;
    begin = m_tMap.begin();	end = m_tMap.end();
    for(begin; begin != end; begin++)
    {
    	SetPkt(&(begin->second), SendToken);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvcObjUnit::SetPkt(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_REG_SVC_OBJ_UNIT pdpirsou = FindItem(nID);
	if(!pdpirsou)	return -1;

	return SetPkt(pdpirsou, SendToken);
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvcObjUnit::SetPkt(PDB_PO_IN_REG_SVC_OBJ_UNIT pdpirsou, MemToken& SendToken)
{
	SendToken.TokenAdd_DPH(pdpirsou->tDPH);

	SendToken.TokenAdd_String(pdpirsou->strSvcName);	

	SendToken.TokenSet_Block();
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvcObjUnit::GetPkt(MemToken& RecvToken, DB_PO_IN_REG_SVC_OBJ_UNIT& dpirsou)
{
	if (!RecvToken.TokenDel_DPH(dpirsou.tDPH))					goto	INVALID_PKT;

	if ( RecvToken.TokenDel_String(dpirsou.strSvcName) < 0)	goto	INVALID_PKT;	

	RecvToken.TokenSkip_Block();
	return 0;
INVALID_PKT:
	return -1;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------



