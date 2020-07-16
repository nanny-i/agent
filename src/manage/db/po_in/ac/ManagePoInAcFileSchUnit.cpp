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
#include "ManagePoInAcFileSchUnit.h"

//---------------------------------------------------------------------------

CManagePoInAcFileSchUnit*	t_ManagePoInAcFileSchUnit = NULL;

//---------------------------------------------------------------------------

CManagePoInAcFileSchUnit::CManagePoInAcFileSchUnit()
{
	t_DBMgrPoInAcFileSchUnit	= new CDBMgrPoInAcFileSchUnit();
}
//---------------------------------------------------------------------------

CManagePoInAcFileSchUnit::~CManagePoInAcFileSchUnit()
{
	if(t_DBMgrPoInAcFileSchUnit)	{	delete t_DBMgrPoInAcFileSchUnit;	t_DBMgrPoInAcFileSchUnit = NULL;	}
}
//---------------------------------------------------------------------------

INT32		CManagePoInAcFileSchUnit::LoadDBMS()
{
	TListDBPoInAcFileSchUnit tDBPoInAcFileSchUnitList;
    TListDBPoInAcFileSchUnitItor begin, end;
	if(SetER(t_DBMgrPoInAcFileSchUnit->LoadExecute(&tDBPoInAcFileSchUnitList)))
    {
    	return g_nErrRtn;
    }

    begin = tDBPoInAcFileSchUnitList.begin();	end = tDBPoInAcFileSchUnitList.end();
    for(begin; begin != end; begin++)
    {
    	AddItem(begin->tDPH.nID, *begin);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFileSchUnit::GetHash(UINT32 nID, String& strOrgValue)
{
	PDB_PO_IN_AC_FILE_SCH_UNIT pdpiafsu 			= NULL;
	{
		if( (pdpiafsu = FindItem(nID)) == NULL)
		{
			WriteLogE("not find po_in_ac_file_sch_unit by hash : [%d]", ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			return ERR_INFO_NOT_OP_BECAUSE_NOT_FIND;
		}
	}

	{
		m_strHashValue = SPrintf("%s,"
							"%u,%u,%u,%u,%u,", 
							GetHdrHashInfo(pdpiafsu).c_str(),
							pdpiafsu->nSchMon, pdpiafsu->nSchDay, pdpiafsu->nSchWeek, 
							pdpiafsu->nSchHour, pdpiafsu->nSchMin);

		strOrgValue += m_strHashValue;
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFileSchUnit::AddPoInAcFileSchUnit(DB_PO_IN_AC_FILE_SCH_UNIT&	dpiafsu)
{
	if(SetER(t_DBMgrPoInAcFileSchUnit->InsertExecute(&dpiafsu)))
    {
    	return g_nErrRtn;
    }

    AddItem(dpiafsu.tDPH.nID, dpiafsu);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFileSchUnit::EditPoInAcFileSchUnit(DB_PO_IN_AC_FILE_SCH_UNIT&	dpiafsu)
{
	PDB_PO_IN_AC_FILE_SCH_UNIT pdpiafsu = FindItem(dpiafsu.tDPH.nID);
	if(!pdpiafsu)	return ERR_DBMS_UPDATE_FAIL;

	if(SetER(t_DBMgrPoInAcFileSchUnit->UpdateExecute(&dpiafsu)))
    {
    	return g_nErrRtn;
    }

    EditItem(dpiafsu.tDPH.nID, dpiafsu);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFileSchUnit::DelPoInAcFileSchUnit(UINT32 nID)
{
	PDB_PO_IN_AC_FILE_SCH_UNIT pdpiafsu = FindItem(nID);
	if(!pdpiafsu)	return ERR_DBMS_DELETE_FAIL;

	if(SetER(t_DBMgrPoInAcFileSchUnit->DeleteExecute(pdpiafsu->tDPH.nID)))
    {
    	return g_nErrRtn;
    }

    DeleteItem(nID);
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFileSchUnit::ApplyPoInAcFileSchUnit(DB_PO_IN_AC_FILE_SCH_UNIT&	dpiafsu)
{
	if(FindItem(dpiafsu.tDPH.nID))
	{
		return EditPoInAcFileSchUnit(dpiafsu);
	}
	return AddPoInAcFileSchUnit(dpiafsu);
}
//---------------------------------------------------------------------------

String					CManagePoInAcFileSchUnit::GetName(UINT32 nID)
{
	PDB_PO_IN_AC_FILE_SCH_UNIT pdpiafsu = FindItem(nID);
    if(!pdpiafsu)	return "";
    return pdpiafsu->tDPH.strName;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManagePoInAcFileSchUnit::SetPkt(MemToken& SendToken)
{
    SendToken.TokenAdd_32(m_tMap.size());

	TMapDBPoInAcFileSchUnitItor begin, end;
    begin = m_tMap.begin();	end = m_tMap.end();
    for(begin; begin != end; begin++)
    {
    	SetPkt(&(begin->second), SendToken);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFileSchUnit::SetPkt(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_AC_FILE_SCH_UNIT pdpiafsu = FindItem(nID);
	if(!pdpiafsu)	return -1;

	return SetPkt(pdpiafsu, SendToken);
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFileSchUnit::SetPkt(PDB_PO_IN_AC_FILE_SCH_UNIT pdpiafsu, MemToken& SendToken)
{
	SendToken.TokenAdd_DPH(pdpiafsu->tDPH);

	SendToken.TokenAdd_32(pdpiafsu->nSchMon);
	SendToken.TokenAdd_32(pdpiafsu->nSchDay);
	SendToken.TokenAdd_32(pdpiafsu->nSchWeek);
	SendToken.TokenAdd_32(pdpiafsu->nSchHour);
	SendToken.TokenAdd_32(pdpiafsu->nSchMin);

	SendToken.TokenSet_Block();
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFileSchUnit::GetPkt(MemToken& RecvToken, DB_PO_IN_AC_FILE_SCH_UNIT& dpiafsu)
{
	if (!RecvToken.TokenDel_DPH(dpiafsu.tDPH))				goto	INVALID_PKT;

	if (!RecvToken.TokenDel_32(dpiafsu.nSchMon))				goto	INVALID_PKT;
	if (!RecvToken.TokenDel_32(dpiafsu.nSchDay))				goto	INVALID_PKT;
	if (!RecvToken.TokenDel_32(dpiafsu.nSchWeek))			goto	INVALID_PKT;
	if (!RecvToken.TokenDel_32(dpiafsu.nSchHour))			goto	INVALID_PKT;
	if (!RecvToken.TokenDel_32(dpiafsu.nSchMin))				goto	INVALID_PKT;

	RecvToken.TokenSkip_Block();
	return 0;
INVALID_PKT:
	return -1;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------



