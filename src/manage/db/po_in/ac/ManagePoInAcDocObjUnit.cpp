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
#include "ManagePoInAcDocObjUnit.h"

//---------------------------------------------------------------------------

CManagePoInAcDocObjUnit*	t_ManagePoInAcDocObjUnit = NULL;

//---------------------------------------------------------------------------

CManagePoInAcDocObjUnit::CManagePoInAcDocObjUnit()
{
	t_DBMgrPoInAcDocObjUnit	= new CDBMgrPoInAcDocObjUnit();
}
//---------------------------------------------------------------------------

CManagePoInAcDocObjUnit::~CManagePoInAcDocObjUnit()
{
	if(t_DBMgrPoInAcDocObjUnit)	{	delete t_DBMgrPoInAcDocObjUnit;	t_DBMgrPoInAcDocObjUnit = NULL;	}
}
//---------------------------------------------------------------------------

INT32		CManagePoInAcDocObjUnit::LoadDBMS()
{
	TListDBPoInAcDocObjUnit tDBPoInAcDocObjUnitList;
    TListDBPoInAcDocObjUnitItor begin, end;
	if(SetER(t_DBMgrPoInAcDocObjUnit->LoadExecute(&tDBPoInAcDocObjUnitList)))
    {
    	return g_nErrRtn;
    }

    begin = tDBPoInAcDocObjUnitList.begin();	end = tDBPoInAcDocObjUnitList.end();
    for(begin; begin != end; begin++)
    {
    	AddItem(begin->tDPH.nID, *begin);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocObjUnit::GetHash(UINT32 nID, String& strOrgValue)
{
	PDB_PO_IN_AC_DOC_OBJ_UNIT pdpiadou 			= NULL;
	{
		if( (pdpiadou = FindItem(nID)) == NULL)
		{
			WriteLogE("not find po_in_ac_doc_obj_unit by hash : [%d]", ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			return ERR_INFO_NOT_OP_BECAUSE_NOT_FIND;
		}
	}

	{
		m_strHashValue = SPrintf("%s,"
							"%s,", 
							GetHdrHashInfo(pdpiadou).c_str(),
							pdpiadou->strFilePath.c_str());

		strOrgValue += m_strHashValue;
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocObjUnit::AddPoInAcDocObjUnit(DB_PO_IN_AC_DOC_OBJ_UNIT&	dpiadou)
{
	if(SetER(t_DBMgrPoInAcDocObjUnit->InsertExecute(&dpiadou)))
    {
    	return g_nErrRtn;
    }

    AddItem(dpiadou.tDPH.nID, dpiadou);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocObjUnit::EditPoInAcDocObjUnit(DB_PO_IN_AC_DOC_OBJ_UNIT&	dpiadou)
{
	PDB_PO_IN_AC_DOC_OBJ_UNIT pdpiadou = FindItem(dpiadou.tDPH.nID);
	if(!pdpiadou)	return ERR_DBMS_UPDATE_FAIL;

	if(SetER(t_DBMgrPoInAcDocObjUnit->UpdateExecute(&dpiadou)))
    {
    	return g_nErrRtn;
    }

    EditItem(dpiadou.tDPH.nID, dpiadou);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocObjUnit::DelPoInAcDocObjUnit(UINT32 nID)
{
	PDB_PO_IN_AC_DOC_OBJ_UNIT pdpiadou = FindItem(nID);
	if(!pdpiadou)	return ERR_DBMS_DELETE_FAIL;

	if(SetER(t_DBMgrPoInAcDocObjUnit->DeleteExecute(pdpiadou->tDPH.nID)))
    {
    	return g_nErrRtn;
    }

    DeleteItem(nID);
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocObjUnit::ApplyPoInAcDocObjUnit(DB_PO_IN_AC_DOC_OBJ_UNIT&	dpiadou)
{
	if(FindItem(dpiadou.tDPH.nID))
	{
		return EditPoInAcDocObjUnit(dpiadou);
	}
	return AddPoInAcDocObjUnit(dpiadou);
}
//---------------------------------------------------------------------------

String					CManagePoInAcDocObjUnit::GetName(UINT32 nID)
{
	PDB_PO_IN_AC_DOC_OBJ_UNIT pdpiadou = FindItem(nID);
    if(!pdpiadou)	return "";
    return pdpiadou->tDPH.strName;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocObjUnit::SetPkt(MemToken& SendToken)
{
    SendToken.TokenAdd_32(m_tMap.size());

	TMapDBPoInAcDocObjUnitItor begin, end;
    begin = m_tMap.begin();	end = m_tMap.end();
    for(begin; begin != end; begin++)
    {
    	SetPkt(&(begin->second), SendToken);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocObjUnit::SetPkt(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_AC_DOC_OBJ_UNIT pdpiadou = FindItem(nID);
	if(!pdpiadou)	return -1;

	return SetPkt(pdpiadou, SendToken);
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocObjUnit::SetPkt(PDB_PO_IN_AC_DOC_OBJ_UNIT pdpiadou, MemToken& SendToken)
{
	SendToken.TokenAdd_DPH(pdpiadou->tDPH);

	SendToken.TokenAdd_String(pdpiadou->strFilePath);	

	SendToken.TokenSet_Block();
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocObjUnit::GetPkt(MemToken& RecvToken, DB_PO_IN_AC_DOC_OBJ_UNIT& dpiadou)
{
	if (!RecvToken.TokenDel_DPH(dpiadou.tDPH))					goto	INVALID_PKT;

	if ( RecvToken.TokenDel_String(dpiadou.strFilePath) < 0)		goto	INVALID_PKT;	

	RecvToken.TokenSkip_Block();
	return 0;
INVALID_PKT:
	return -1;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------



