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
#include "ManagePoInAcFileSubUnit.h"

//---------------------------------------------------------------------------

CManagePoInAcFileSubUnit*	t_ManagePoInAcFileSubUnit = NULL;

//---------------------------------------------------------------------------

CManagePoInAcFileSubUnit::CManagePoInAcFileSubUnit()
{
	t_DBMgrPoInAcFileSubUnit	= new CDBMgrPoInAcFileSubUnit();
}
//---------------------------------------------------------------------------

CManagePoInAcFileSubUnit::~CManagePoInAcFileSubUnit()
{
	if(t_DBMgrPoInAcFileSubUnit)	{	delete t_DBMgrPoInAcFileSubUnit;	t_DBMgrPoInAcFileSubUnit = NULL;	}
}
//---------------------------------------------------------------------------

INT32		CManagePoInAcFileSubUnit::LoadDBMS()
{
	TListDBPoInAcFileSubUnit tDBPoInAcFileSubUnitList;
    TListDBPoInAcFileSubUnitItor begin, end;
	if(SetER(t_DBMgrPoInAcFileSubUnit->LoadExecute(&tDBPoInAcFileSubUnitList)))
    {
    	return g_nErrRtn;
    }

    begin = tDBPoInAcFileSubUnitList.begin();	end = tDBPoInAcFileSubUnitList.end();
    for(begin; begin != end; begin++)
    {
    	AddItem(begin->tDPH.nID, *begin);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFileSubUnit::GetHash(UINT32 nID, String& strOrgValue)
{
	PDB_PO_IN_AC_FILE_SUB_UNIT pdpiafsu 			= NULL;
	{
		if( (pdpiafsu = FindItem(nID)) == NULL)
		{
			WriteLogE("not find po_in_ac_file_sub_unit by hash : [%d]", ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
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

INT32					CManagePoInAcFileSubUnit::AddPoInAcFileSubUnit(DB_PO_IN_AC_FILE_SUB_UNIT&	dpiafsu)
{
	if(SetER(t_DBMgrPoInAcFileSubUnit->InsertExecute(&dpiafsu)))
    {
    	return g_nErrRtn;
    }

    AddItem(dpiafsu.tDPH.nID, dpiafsu);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFileSubUnit::EditPoInAcFileSubUnit(DB_PO_IN_AC_FILE_SUB_UNIT&	dpiafsu)
{
	PDB_PO_IN_AC_FILE_SUB_UNIT pdpiafsu = FindItem(dpiafsu.tDPH.nID);
	if(!pdpiafsu)	return ERR_DBMS_UPDATE_FAIL;

	if(SetER(t_DBMgrPoInAcFileSubUnit->UpdateExecute(&dpiafsu)))
    {
    	return g_nErrRtn;
    }

    EditItem(dpiafsu.tDPH.nID, dpiafsu);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFileSubUnit::DelPoInAcFileSubUnit(UINT32 nID)
{
	PDB_PO_IN_AC_FILE_SUB_UNIT pdpiafsu = FindItem(nID);
	if(!pdpiafsu)	return ERR_DBMS_DELETE_FAIL;

	if(SetER(t_DBMgrPoInAcFileSubUnit->DeleteExecute(pdpiafsu->tDPH.nID)))
    {
    	return g_nErrRtn;
    }

    DeleteItem(nID);
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFileSubUnit::ApplyPoInAcFileSubUnit(DB_PO_IN_AC_FILE_SUB_UNIT&	dpiafsu)
{
	if(FindItem(dpiafsu.tDPH.nID))
	{
		return EditPoInAcFileSubUnit(dpiafsu);
	}
	return AddPoInAcFileSubUnit(dpiafsu);
}
//---------------------------------------------------------------------------

String					CManagePoInAcFileSubUnit::GetName(UINT32 nID)
{
	PDB_PO_IN_AC_FILE_SUB_UNIT pdpiafsu = FindItem(nID);
    if(!pdpiafsu)	return "";
    return pdpiafsu->tDPH.strName;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManagePoInAcFileSubUnit::SetPkt(MemToken& SendToken)
{
    SendToken.TokenAdd_32(m_tMap.size());

	TMapDBPoInAcFileSubUnitItor begin, end;
    begin = m_tMap.begin();	end = m_tMap.end();
    for(begin; begin != end; begin++)
    {
    	SetPkt(&(begin->second), SendToken);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFileSubUnit::SetPkt(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_AC_FILE_SUB_UNIT pdpiafsu = FindItem(nID);
	if(!pdpiafsu)	return -1;

	return SetPkt(pdpiafsu, SendToken);
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFileSubUnit::SetPkt(PDB_PO_IN_AC_FILE_SUB_UNIT pdpiafsu, MemToken& SendToken)
{
	SendToken.TokenAdd_DPH(pdpiafsu->tDPH);

	SendToken.TokenAdd_32(pdpiafsu->nSbType);	
	SendToken.TokenAdd_String(pdpiafsu->strSbName);
	SendToken.TokenAdd_String(pdpiafsu->strSbProc);	

	SendToken.TokenSet_Block();
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFileSubUnit::GetPkt(MemToken& RecvToken, DB_PO_IN_AC_FILE_SUB_UNIT& dpiafsu)
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



