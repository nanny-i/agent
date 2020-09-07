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
#include "ManagePoInVulnSwUnit.h"

//---------------------------------------------------------------------------

CManagePoInVulnSwUnit*	t_ManagePoInVulnSwUnit = NULL;

//---------------------------------------------------------------------------

CManagePoInVulnSwUnit::CManagePoInVulnSwUnit()
{
	t_DBMgrPoInVulnSwUnit	= new CDBMgrPoInVulnSwUnit();
}
//---------------------------------------------------------------------------

CManagePoInVulnSwUnit::~CManagePoInVulnSwUnit()
{
	if(t_DBMgrPoInVulnSwUnit)	{	delete t_DBMgrPoInVulnSwUnit;	t_DBMgrPoInVulnSwUnit = NULL;	}
}
//---------------------------------------------------------------------------

INT32		CManagePoInVulnSwUnit::LoadDBMS()
{
	TListDBPoInVulnSwUnit tDBPoInVulnSwUnitList;
	TListDBPoInVulnSwUnitItor begin, end;
	if(SetER(t_DBMgrPoInVulnSwUnit->LoadExecute(&tDBPoInVulnSwUnitList)))
	{
		return g_nErrRtn;
	}

	begin = tDBPoInVulnSwUnitList.begin();	end = tDBPoInVulnSwUnitList.end();
	for(begin; begin != end; begin++)
	{
		AddItem(begin->tDPH.nID, *begin);
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInVulnSwUnit::GetHash(UINT32 nID, String& strOrgValue)
{
	PDB_PO_IN_VULN_SW_UNIT pdata 			= NULL;
	{
		if( (pdata = FindItem(nID)) == NULL)
		{
			WriteLogE("not find po_in_vuln_sw_unit by hash : [%d]", ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			return ERR_INFO_NOT_OP_BECAUSE_NOT_FIND;
		}
	}

	{
		strOrgValue = SPrintf("%s,"
							"%u,%s,%s,", 
							GetHdrHashInfo(pdata).c_str(),
							pdata->nSwID, pdata->strClassName.c_str(), pdata->strSwRegKey.c_str());
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInVulnSwUnit::AddPoInVulnSwUnit(DB_PO_IN_VULN_SW_UNIT&	data)
{
	if(SetER(t_DBMgrPoInVulnSwUnit->InsertExecute(&data)))
	{
		return g_nErrRtn;
	}

	AddItem(data.tDPH.nID, data);

	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInVulnSwUnit::EditPoInVulnSwUnit(DB_PO_IN_VULN_SW_UNIT&	data)
{
	PDB_PO_IN_VULN_SW_UNIT pdata = FindItem(data.tDPH.nID);
	if(!pdata)	return ERR_DBMS_UPDATE_FAIL;

	if(SetER(t_DBMgrPoInVulnSwUnit->UpdateExecute(&data)))
	{
		return g_nErrRtn;
	}

	EditItem(data.tDPH.nID, data);

	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInVulnSwUnit::DelPoInVulnSwUnit(UINT32 nID)
{
	PDB_PO_IN_VULN_SW_UNIT pdata = FindItem(nID);
	if(!pdata)	return ERR_DBMS_DELETE_FAIL;

	if(SetER(t_DBMgrPoInVulnSwUnit->DeleteExecute(pdata->tDPH.nID)))
	{
		return g_nErrRtn;
	}

	DeleteItem(nID);
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInVulnSwUnit::ApplyPoInVulnSwUnit(DB_PO_IN_VULN_SW_UNIT&	data)
{
	if(FindItem(data.tDPH.nID))
	{
		return EditPoInVulnSwUnit(data);
	}
	return AddPoInVulnSwUnit(data);
}
//---------------------------------------------------------------------------

String					CManagePoInVulnSwUnit::GetName(UINT32 nID)
{
	PDB_PO_IN_VULN_SW_UNIT pdata = FindItem(nID);
	if(!pdata)	return "";
	return pdata->tDPH.strName;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManagePoInVulnSwUnit::SetPkt(MemToken& SendToken)
{
	SendToken.TokenAdd_32(m_tMap.size());

	TMapDBPoInVulnSwUnitItor begin, end;
	begin = m_tMap.begin();	end = m_tMap.end();
	for(begin; begin != end; begin++)
	{
		SetPkt(&(begin->second), SendToken);
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInVulnSwUnit::SetPkt(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_VULN_SW_UNIT pdata = FindItem(nID);
	if(!pdata)	return -1;

	return SetPkt(pdata, SendToken);
}
//---------------------------------------------------------------------------

INT32					CManagePoInVulnSwUnit::SetPkt(PDB_PO_IN_VULN_SW_UNIT pdata, MemToken& SendToken)
{
	SendToken.TokenAdd_DPH(pdata->tDPH);

	SendToken.TokenAdd_32(pdata->nSwID);
	SendToken.TokenAdd_String(pdata->strClassName);
	SendToken.TokenAdd_String(pdata->strSwRegKey);

	SendToken.TokenSet_Block();
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInVulnSwUnit::GetPkt(MemToken& RecvToken, DB_PO_IN_VULN_SW_UNIT& data)
{
	if (!RecvToken.TokenDel_DPH(data.tDPH))						goto	INVALID_PKT;

	if (!RecvToken.TokenDel_32(data.nSwID))						goto	INVALID_PKT;
	if (RecvToken.TokenDel_String(data.strClassName)<0)			goto	INVALID_PKT;
	if (RecvToken.TokenDel_String(data.strSwRegKey)<0)			goto	INVALID_PKT;

	RecvToken.TokenSkip_Block();
	return 0;
INVALID_PKT:
	return -1;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------



