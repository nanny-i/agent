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
#include "ManagePoInAcDocSubUnit.h"

//---------------------------------------------------------------------------

CManagePoInAcDocSubUnit*	t_ManagePoInAcDocSubUnit = NULL;

//---------------------------------------------------------------------------

CManagePoInAcDocSubUnit::CManagePoInAcDocSubUnit()
{
	t_DBMgrPoInAcDocSubUnit	= new CDBMgrPoInAcDocSubUnit();
}
//---------------------------------------------------------------------------

CManagePoInAcDocSubUnit::~CManagePoInAcDocSubUnit()
{
	if(t_DBMgrPoInAcDocSubUnit)	{	delete t_DBMgrPoInAcDocSubUnit;	t_DBMgrPoInAcDocSubUnit = NULL;	}
}
//---------------------------------------------------------------------------

INT32		CManagePoInAcDocSubUnit::LoadDBMS()
{
	TListDBPoInAcDocSubUnit tDBPoInAcDocSubUnitList;
    TListDBPoInAcDocSubUnitItor begin, end;
	if(SetER(t_DBMgrPoInAcDocSubUnit->LoadExecute(&tDBPoInAcDocSubUnitList)))
    {
    	return g_nErrRtn;
    }

    begin = tDBPoInAcDocSubUnitList.begin();	end = tDBPoInAcDocSubUnitList.end();
    for(begin; begin != end; begin++)
    {
    	AddItem(begin->tDPH.nID, *begin);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocSubUnit::GetHash(UINT32 nID, String& strOrgValue)
{
	PDB_PO_IN_AC_DOC_SUB_UNIT pdpiadsu 			= NULL;
	{
		if( (pdpiadsu = FindItem(nID)) == NULL)
		{
			WriteLogE("not find po_in_ac_doc_sub_unit by hash : [%d]", ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			return ERR_INFO_NOT_OP_BECAUSE_NOT_FIND;
		}
	}

	{		
		m_strHashValue = SPrintf("%s,"														
							"%u,"
							"%s,%s,",							
							GetHdrHashInfo(pdpiadsu).c_str(),														
							pdpiadsu->nSbType, 
							pdpiadsu->strSbName.c_str(), pdpiadsu->strSbProc.c_str());					

		strOrgValue += m_strHashValue;
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocSubUnit::AddPoInAcDocSubUnit(DB_PO_IN_AC_DOC_SUB_UNIT&	dpiadsu)
{
	if(SetER(t_DBMgrPoInAcDocSubUnit->InsertExecute(&dpiadsu)))
    {
    	return g_nErrRtn;
    }

    AddItem(dpiadsu.tDPH.nID, dpiadsu);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocSubUnit::EditPoInAcDocSubUnit(DB_PO_IN_AC_DOC_SUB_UNIT&	dpiadsu)
{
	PDB_PO_IN_AC_DOC_SUB_UNIT pdpiadsu = FindItem(dpiadsu.tDPH.nID);
	if(!pdpiadsu)	return ERR_DBMS_UPDATE_FAIL;

	if(SetER(t_DBMgrPoInAcDocSubUnit->UpdateExecute(&dpiadsu)))
    {
    	return g_nErrRtn;
    }

    EditItem(dpiadsu.tDPH.nID, dpiadsu);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocSubUnit::DelPoInAcDocSubUnit(UINT32 nID)
{
	PDB_PO_IN_AC_DOC_SUB_UNIT pdpiadsu = FindItem(nID);
	if(!pdpiadsu)	return ERR_DBMS_DELETE_FAIL;

	if(SetER(t_DBMgrPoInAcDocSubUnit->DeleteExecute(pdpiadsu->tDPH.nID)))
    {
    	return g_nErrRtn;
    }

    DeleteItem(nID);
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocSubUnit::ApplyPoInAcDocSubUnit(DB_PO_IN_AC_DOC_SUB_UNIT&	dpiadsu)
{
	if(FindItem(dpiadsu.tDPH.nID))
	{
		return EditPoInAcDocSubUnit(dpiadsu);
	}
	return AddPoInAcDocSubUnit(dpiadsu);
}
//---------------------------------------------------------------------------

String					CManagePoInAcDocSubUnit::GetName(UINT32 nID)
{
	PDB_PO_IN_AC_DOC_SUB_UNIT pdpiadsu = FindItem(nID);
    if(!pdpiadsu)	return "";
    return pdpiadsu->tDPH.strName;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocSubUnit::SetPkt(MemToken& SendToken)
{
    SendToken.TokenAdd_32(m_tMap.size());

	TMapDBPoInAcDocSubUnitItor begin, end;
    begin = m_tMap.begin();	end = m_tMap.end();
    for(begin; begin != end; begin++)
    {
    	SetPkt(&(begin->second), SendToken);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocSubUnit::SetPkt(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_AC_DOC_SUB_UNIT pdpiadsu = FindItem(nID);
	if(!pdpiadsu)	return -1;

	return SetPkt(pdpiadsu, SendToken);
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocSubUnit::SetPkt(PDB_PO_IN_AC_DOC_SUB_UNIT pdpiadsu, MemToken& SendToken)
{
	SendToken.TokenAdd_DPH(pdpiadsu->tDPH);
	
	SendToken.TokenAdd_32(pdpiadsu->nSbType);	
	SendToken.TokenAdd_String(pdpiadsu->strSbName);
	SendToken.TokenAdd_String(pdpiadsu->strSbProc);	

	SendToken.TokenSet_Block();
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocSubUnit::GetPkt(MemToken& RecvToken, DB_PO_IN_AC_DOC_SUB_UNIT& dpiadsu)
{
	if (!RecvToken.TokenDel_DPH(dpiadsu.tDPH))					goto	INVALID_PKT;
	
	if (!RecvToken.TokenDel_32(dpiadsu.nSbType))					goto	INVALID_PKT;	
	if ( RecvToken.TokenDel_String(dpiadsu.strSbName) < 0)			goto	INVALID_PKT;
	if ( RecvToken.TokenDel_String(dpiadsu.strSbProc) < 0)			goto	INVALID_PKT;	

	RecvToken.TokenSkip_Block();
	return 0;
INVALID_PKT:
	return -1;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------



