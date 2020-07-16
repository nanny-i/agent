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
#include "ManagePoFaOpObjUnit.h"

//---------------------------------------------------------------------------

CManagePoFaOpObjUnit*	t_ManagePoFaOpObjUnit = NULL;

//---------------------------------------------------------------------------

CManagePoFaOpObjUnit::CManagePoFaOpObjUnit()
{
	t_DBMgrPoFaOpObjUnit	= new CDBMgrPoFaOpObjUnit();
}
//---------------------------------------------------------------------------

CManagePoFaOpObjUnit::~CManagePoFaOpObjUnit()
{
	if(t_DBMgrPoFaOpObjUnit)	{	delete t_DBMgrPoFaOpObjUnit;	t_DBMgrPoFaOpObjUnit = NULL;	}
}
//---------------------------------------------------------------------------

INT32		CManagePoFaOpObjUnit::LoadDBMS()
{
	TListDBPoFaOpObjUnit tDBPoFaOpObjUnitList;
    TListDBPoFaOpObjUnitItor begin, end;
	if(SetER(t_DBMgrPoFaOpObjUnit->LoadExecute(&tDBPoFaOpObjUnitList)))
    {
    	return g_nErrRtn;
    }

    begin = tDBPoFaOpObjUnitList.begin();	end = tDBPoFaOpObjUnitList.end();
    for(begin; begin != end; begin++)
    {
    	AddItem(begin->tDPH.nID, *begin);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoFaOpObjUnit::GetHash(UINT32 nID, String& strOrgValue)
{
	PDB_PO_FA_OP_OBJ_UNIT pdpfoou 			= NULL;
	{
		if( (pdpfoou = FindItem(nID)) == NULL)
		{
			WriteLogE("not find po_fa_op_obj_unit by hash : [%d]", ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			return ERR_INFO_NOT_OP_BECAUSE_NOT_FIND;
		}
	}

	{
		m_strHashValue = SPrintf("%s,"
							"%s,%u,%u,", 
							GetHdrHashInfo(pdpfoou).c_str(),
							pdpfoou->strFilePath.c_str(), pdpfoou->nChkAcPath, pdpfoou->nChkSelfPath);

		strOrgValue += m_strHashValue;
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoFaOpObjUnit::AddPoFaOpObjUnit(DB_PO_FA_OP_OBJ_UNIT&	dpfoou)
{
	if(SetER(t_DBMgrPoFaOpObjUnit->InsertExecute(&dpfoou)))
    {
    	return g_nErrRtn;
    }

    AddItem(dpfoou.tDPH.nID, dpfoou);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoFaOpObjUnit::EditPoFaOpObjUnit(DB_PO_FA_OP_OBJ_UNIT&	dpfoou)
{
	PDB_PO_FA_OP_OBJ_UNIT pdpfoou = FindItem(dpfoou.tDPH.nID);
	if(!pdpfoou)	return ERR_DBMS_UPDATE_FAIL;

	if(SetER(t_DBMgrPoFaOpObjUnit->UpdateExecute(&dpfoou)))
    {
    	return g_nErrRtn;
    }

    EditItem(dpfoou.tDPH.nID, dpfoou);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoFaOpObjUnit::DelPoFaOpObjUnit(UINT32 nID)
{
	PDB_PO_FA_OP_OBJ_UNIT pdpfoou = FindItem(nID);
	if(!pdpfoou)	return ERR_DBMS_DELETE_FAIL;

	if(SetER(t_DBMgrPoFaOpObjUnit->DeleteExecute(pdpfoou->tDPH.nID)))
    {
    	return g_nErrRtn;
    }

    DeleteItem(nID);
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoFaOpObjUnit::ApplyPoFaOpObjUnit(DB_PO_FA_OP_OBJ_UNIT&	dpfoou)
{
	if(FindItem(dpfoou.tDPH.nID))
	{
		return EditPoFaOpObjUnit(dpfoou);
	}
	return AddPoFaOpObjUnit(dpfoou);
}
//---------------------------------------------------------------------------

String					CManagePoFaOpObjUnit::GetName(UINT32 nID)
{
	PDB_PO_FA_OP_OBJ_UNIT pdpfoou = FindItem(nID);
    if(!pdpfoou)	return "";
    return pdpfoou->tDPH.strName;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManagePoFaOpObjUnit::SetPkt(MemToken& SendToken)
{
    SendToken.TokenAdd_32(m_tMap.size());

	TMapDBPoFaOpObjUnitItor begin, end;
    begin = m_tMap.begin();	end = m_tMap.end();
    for(begin; begin != end; begin++)
    {
    	SetPkt(&(begin->second), SendToken);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoFaOpObjUnit::SetPkt(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_FA_OP_OBJ_UNIT pdpfoou = FindItem(nID);
	if(!pdpfoou)	return -1;

	return SetPkt(pdpfoou, SendToken);
}
//---------------------------------------------------------------------------

INT32					CManagePoFaOpObjUnit::SetPkt(PDB_PO_FA_OP_OBJ_UNIT pdpfoou, MemToken& SendToken)
{
	SendToken.TokenAdd_DPH(pdpfoou->tDPH);

	SendToken.TokenAdd_String(pdpfoou->strFilePath);
	SendToken.TokenAdd_32(pdpfoou->nChkAcPath);
	SendToken.TokenAdd_32(pdpfoou->nChkSelfPath);

	SendToken.TokenSet_Block();
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoFaOpObjUnit::GetPkt(MemToken& RecvToken, DB_PO_FA_OP_OBJ_UNIT& dpfoou)
{
	if (!RecvToken.TokenDel_DPH(dpfoou.tDPH))					goto	INVALID_PKT;

	if ( RecvToken.TokenDel_String(dpfoou.strFilePath) < 0)		goto	INVALID_PKT;
	if (!RecvToken.TokenDel_32(dpfoou.nChkAcPath))				goto	INVALID_PKT;
	if (!RecvToken.TokenDel_32(dpfoou.nChkSelfPath))			goto	INVALID_PKT;

	RecvToken.TokenSkip_Block();
	return 0;
INVALID_PKT:
	return -1;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------



