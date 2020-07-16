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
#include "ManagePoInAcSfObjUnit.h"

//---------------------------------------------------------------------------

CManagePoInAcSfObjUnit*	t_ManagePoInAcSfObjUnit = NULL;

//---------------------------------------------------------------------------

CManagePoInAcSfObjUnit::CManagePoInAcSfObjUnit()
{
	t_DBMgrPoInAcSfObjUnit	= new CDBMgrPoInAcSfObjUnit();
}
//---------------------------------------------------------------------------

CManagePoInAcSfObjUnit::~CManagePoInAcSfObjUnit()
{
	if(t_DBMgrPoInAcSfObjUnit)	{	delete t_DBMgrPoInAcSfObjUnit;	t_DBMgrPoInAcSfObjUnit = NULL;	}
}
//---------------------------------------------------------------------------

INT32		CManagePoInAcSfObjUnit::LoadDBMS()
{
	TListDBPoInAcSfObjUnit tDBPoInAcSfObjUnitList;
    TListDBPoInAcSfObjUnitItor begin, end;
	if(SetER(t_DBMgrPoInAcSfObjUnit->LoadExecute(&tDBPoInAcSfObjUnitList)))
    {
    	return g_nErrRtn;
    }

    begin = tDBPoInAcSfObjUnitList.begin();	end = tDBPoInAcSfObjUnitList.end();
    for(begin; begin != end; begin++)
    {
    	AddItem(begin->tDPH.nID, *begin);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfObjUnit::GetHash(UINT32 nID, String& strOrgValue)
{
	PDB_PO_IN_AC_SF_OBJ_UNIT pdpiafou 			= NULL;
	{
		if( (pdpiafou = FindItem(nID)) == NULL)
		{
			WriteLogE("not find po_in_ac_sf_obj_unit by hash : [%d]", ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			return ERR_INFO_NOT_OP_BECAUSE_NOT_FIND;
		}
	}

	{
		m_strHashValue = SPrintf("%s,"
							"%s,%u,", 
							GetHdrHashInfo(pdpiafou).c_str(),
							pdpiafou->strFilePath.c_str(), pdpiafou->nSFMode);

		strOrgValue += m_strHashValue;
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfObjUnit::AddPoInAcSfObjUnit(DB_PO_IN_AC_SF_OBJ_UNIT&	dpiafou)
{
	if(SetER(t_DBMgrPoInAcSfObjUnit->InsertExecute(&dpiafou)))
    {
    	return g_nErrRtn;
    }

    AddItem(dpiafou.tDPH.nID, dpiafou);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfObjUnit::EditPoInAcSfObjUnit(DB_PO_IN_AC_SF_OBJ_UNIT&	dpiafou)
{
	PDB_PO_IN_AC_SF_OBJ_UNIT pdpiafou = FindItem(dpiafou.tDPH.nID);
	if(!pdpiafou)	return ERR_DBMS_UPDATE_FAIL;

	if(SetER(t_DBMgrPoInAcSfObjUnit->UpdateExecute(&dpiafou)))
    {
    	return g_nErrRtn;
    }

    EditItem(dpiafou.tDPH.nID, dpiafou);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfObjUnit::DelPoInAcSfObjUnit(UINT32 nID)
{
	PDB_PO_IN_AC_SF_OBJ_UNIT pdpiafou = FindItem(nID);
	if(!pdpiafou)	return ERR_DBMS_DELETE_FAIL;

	if(SetER(t_DBMgrPoInAcSfObjUnit->DeleteExecute(pdpiafou->tDPH.nID)))
    {
    	return g_nErrRtn;
    }

    DeleteItem(nID);
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfObjUnit::ApplyPoInAcSfObjUnit(DB_PO_IN_AC_SF_OBJ_UNIT&	dpiafou)
{
	if(FindItem(dpiafou.tDPH.nID))
	{
		return EditPoInAcSfObjUnit(dpiafou);
	}
	return AddPoInAcSfObjUnit(dpiafou);
}
//---------------------------------------------------------------------------

String					CManagePoInAcSfObjUnit::GetName(UINT32 nID)
{
	PDB_PO_IN_AC_SF_OBJ_UNIT pdpiafou = FindItem(nID);
    if(!pdpiafou)	return "";
    return pdpiafou->tDPH.strName;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfObjUnit::SetPkt(MemToken& SendToken)
{
    SendToken.TokenAdd_32(m_tMap.size());

	TMapDBPoInAcSfObjUnitItor begin, end;
    begin = m_tMap.begin();	end = m_tMap.end();
    for(begin; begin != end; begin++)
    {
    	SetPkt(&(begin->second), SendToken);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfObjUnit::SetPkt(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_AC_SF_OBJ_UNIT pdpiafou = FindItem(nID);
	if(!pdpiafou)	return -1;

	return SetPkt(pdpiafou, SendToken);
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfObjUnit::SetPkt(PDB_PO_IN_AC_SF_OBJ_UNIT pdpiafou, MemToken& SendToken)
{
	SendToken.TokenAdd_DPH(pdpiafou->tDPH);

	SendToken.TokenAdd_String(pdpiafou->strFilePath);
	SendToken.TokenAdd_32(pdpiafou->nSFMode);	

	SendToken.TokenSet_Block();
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfObjUnit::GetPkt(MemToken& RecvToken, DB_PO_IN_AC_SF_OBJ_UNIT& dpiafou)
{
	if (!RecvToken.TokenDel_DPH(dpiafou.tDPH))					goto	INVALID_PKT;

	if ( RecvToken.TokenDel_String(dpiafou.strFilePath) < 0)		goto	INVALID_PKT;
	if (!RecvToken.TokenDel_32(dpiafou.nSFMode))				goto	INVALID_PKT;	

	RecvToken.TokenSkip_Block();
	return 0;
INVALID_PKT:
	return -1;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------



