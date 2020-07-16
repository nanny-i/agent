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
#include "ManagePoInAcSfSubUnit.h"

//---------------------------------------------------------------------------

CManagePoInAcSfSubUnit*	t_ManagePoInAcSfSubUnit = NULL;

//---------------------------------------------------------------------------

CManagePoInAcSfSubUnit::CManagePoInAcSfSubUnit()
{
	t_DBMgrPoInAcSfSubUnit	= new CDBMgrPoInAcSfSubUnit();
}
//---------------------------------------------------------------------------

CManagePoInAcSfSubUnit::~CManagePoInAcSfSubUnit()
{
	if(t_DBMgrPoInAcSfSubUnit)	{	delete t_DBMgrPoInAcSfSubUnit;	t_DBMgrPoInAcSfSubUnit = NULL;	}
}
//---------------------------------------------------------------------------

INT32		CManagePoInAcSfSubUnit::LoadDBMS()
{
	TListDBPoInAcSfSubUnit tDBPoInAcSfSubUnitList;
    TListDBPoInAcSfSubUnitItor begin, end;
	if(SetER(t_DBMgrPoInAcSfSubUnit->LoadExecute(&tDBPoInAcSfSubUnitList)))
    {
    	return g_nErrRtn;
    }

    begin = tDBPoInAcSfSubUnitList.begin();	end = tDBPoInAcSfSubUnitList.end();
    for(begin; begin != end; begin++)
    {
    	AddItem(begin->tDPH.nID, *begin);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfSubUnit::GetHash(UINT32 nID, String& strOrgValue)
{
	PDB_PO_IN_AC_SF_SUB_UNIT pdpiafsu 			= NULL;
	{
		if( (pdpiafsu = FindItem(nID)) == NULL)
		{
			WriteLogE("not find po_in_ac_sf_sub_unit by hash : [%d]", ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			return ERR_INFO_NOT_OP_BECAUSE_NOT_FIND;
		}
	}

	{		
		m_strHashValue = SPrintf("%s,"
							"%u,"
							"%s,%s,",							
							GetHdrHashInfo(pdpiafsu).c_str(),
							pdpiafsu->nSbType, 
							pdpiafsu->strSbName.c_str(), pdpiafsu->strSbProc.c_str());										

		strOrgValue += m_strHashValue;
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfSubUnit::AddPoInAcSfSubUnit(DB_PO_IN_AC_SF_SUB_UNIT&	dpiafsu)
{
	if(SetER(t_DBMgrPoInAcSfSubUnit->InsertExecute(&dpiafsu)))
    {
    	return g_nErrRtn;
    }

    AddItem(dpiafsu.tDPH.nID, dpiafsu);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfSubUnit::EditPoInAcSfSubUnit(DB_PO_IN_AC_SF_SUB_UNIT&	dpiafsu)
{
	PDB_PO_IN_AC_SF_SUB_UNIT pdpiafsu = FindItem(dpiafsu.tDPH.nID);
	if(!pdpiafsu)	return ERR_DBMS_UPDATE_FAIL;

	if(SetER(t_DBMgrPoInAcSfSubUnit->UpdateExecute(&dpiafsu)))
    {
    	return g_nErrRtn;
    }

    EditItem(dpiafsu.tDPH.nID, dpiafsu);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfSubUnit::DelPoInAcSfSubUnit(UINT32 nID)
{
	PDB_PO_IN_AC_SF_SUB_UNIT pdpiafsu = FindItem(nID);
	if(!pdpiafsu)	return ERR_DBMS_DELETE_FAIL;

	if(SetER(t_DBMgrPoInAcSfSubUnit->DeleteExecute(pdpiafsu->tDPH.nID)))
    {
    	return g_nErrRtn;
    }

    DeleteItem(nID);
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfSubUnit::ApplyPoInAcSfSubUnit(DB_PO_IN_AC_SF_SUB_UNIT&	dpiafsu)
{
	if(FindItem(dpiafsu.tDPH.nID))
	{
		return EditPoInAcSfSubUnit(dpiafsu);
	}
	return AddPoInAcSfSubUnit(dpiafsu);
}
//---------------------------------------------------------------------------

String					CManagePoInAcSfSubUnit::GetName(UINT32 nID)
{
	PDB_PO_IN_AC_SF_SUB_UNIT pdpiafsu = FindItem(nID);
    if(!pdpiafsu)	return "";
    return pdpiafsu->tDPH.strName;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfSubUnit::SetPkt(MemToken& SendToken)
{
    SendToken.TokenAdd_32(m_tMap.size());

	TMapDBPoInAcSfSubUnitItor begin, end;
    begin = m_tMap.begin();	end = m_tMap.end();
    for(begin; begin != end; begin++)
    {
    	SetPkt(&(begin->second), SendToken);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfSubUnit::SetPkt(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_AC_SF_SUB_UNIT pdpiafsu = FindItem(nID);
	if(!pdpiafsu)	return -1;

	return SetPkt(pdpiafsu, SendToken);
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfSubUnit::SetPkt(PDB_PO_IN_AC_SF_SUB_UNIT pdpiafsu, MemToken& SendToken)
{
	SendToken.TokenAdd_DPH(pdpiafsu->tDPH);
	
	SendToken.TokenAdd_32(pdpiafsu->nSbType);	
	SendToken.TokenAdd_String(pdpiafsu->strSbName);
	SendToken.TokenAdd_String(pdpiafsu->strSbProc);	

	SendToken.TokenSet_Block();
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfSubUnit::GetPkt(MemToken& RecvToken, DB_PO_IN_AC_SF_SUB_UNIT& dpiafsu)
{
	if (!RecvToken.TokenDel_DPH(dpiafsu.tDPH))					goto	INVALID_PKT;
	
	if (!RecvToken.TokenDel_32(dpiafsu.nSbType))					goto	INVALID_PKT;	
	if ( RecvToken.TokenDel_String(dpiafsu.strSbName) < 0)			goto	INVALID_PKT;
	if ( RecvToken.TokenDel_String(dpiafsu.strSbProc) < 0)			goto	INVALID_PKT;	

	RecvToken.TokenSkip_Block();
	return 0;
INVALID_PKT:
	return -1;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------



