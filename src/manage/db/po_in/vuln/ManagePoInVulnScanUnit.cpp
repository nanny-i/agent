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
#include "ManagePoInVulnScanUnit.h"

//---------------------------------------------------------------------------

CManagePoInVulnScanUnit*	t_ManagePoInVulnScanUnit = NULL;

//---------------------------------------------------------------------------

CManagePoInVulnScanUnit::CManagePoInVulnScanUnit()
{
	t_DBMgrPoInVulnScanUnit	= new CDBMgrPoInVulnScanUnit();
}
//---------------------------------------------------------------------------

CManagePoInVulnScanUnit::~CManagePoInVulnScanUnit()
{
	if(t_DBMgrPoInVulnScanUnit)	{	delete t_DBMgrPoInVulnScanUnit;	t_DBMgrPoInVulnScanUnit = NULL;	}
}
//---------------------------------------------------------------------------

INT32		CManagePoInVulnScanUnit::LoadDBMS()
{
	TListDBPoInVulnScanUnit tDBPoInVulnScanUnitList;
    TListDBPoInVulnScanUnitItor begin, end;
	if(SetER(t_DBMgrPoInVulnScanUnit->LoadExecute(&tDBPoInVulnScanUnitList)))
    {
    	return g_nErrRtn;
    }

    begin = tDBPoInVulnScanUnitList.begin();	end = tDBPoInVulnScanUnitList.end();
    for(begin; begin != end; begin++)
    {
    	AddItem(begin->tDPH.nID, *begin);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInVulnScanUnit::GetHash(UINT32 nID, String& strOrgValue)
{
	PDB_PO_IN_VULN_SCAN_UNIT pdata 			= NULL;
	{
		if( (pdata = FindItem(nID)) == NULL)
		{
			WriteLogE("not find po_in_vuln_scan_unit by hash : [%d]", ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			return ERR_INFO_NOT_OP_BECAUSE_NOT_FIND;
		}
	}

	{
		strOrgValue = SPrintf("%s,"
							"%llu,%u,", 
							GetHdrHashInfo(pdata).c_str(),
							pdata->nSchTime, pdata->nScanType);
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInVulnScanUnit::AddPoInVulnScanUnit(DB_PO_IN_VULN_SCAN_UNIT&	data)
{
	if(SetER(t_DBMgrPoInVulnScanUnit->InsertExecute(&data)))
    {
    	return g_nErrRtn;
    }

    AddItem(data.tDPH.nID, data);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInVulnScanUnit::EditPoInVulnScanUnit(DB_PO_IN_VULN_SCAN_UNIT&	data)
{
	PDB_PO_IN_VULN_SCAN_UNIT pdata = FindItem(data.tDPH.nID);
	if(!pdata)	return ERR_DBMS_UPDATE_FAIL;

	if(SetER(t_DBMgrPoInVulnScanUnit->UpdateExecute(&data)))
    {
    	return g_nErrRtn;
    }

    EditItem(data.tDPH.nID, data);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInVulnScanUnit::DelPoInVulnScanUnit(UINT32 nID)
{
	PDB_PO_IN_VULN_SCAN_UNIT pdata = FindItem(nID);
	if(!pdata)	return ERR_DBMS_DELETE_FAIL;

	if(SetER(t_DBMgrPoInVulnScanUnit->DeleteExecute(pdata->tDPH.nID)))
    {
    	return g_nErrRtn;
    }

    DeleteItem(nID);
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInVulnScanUnit::ApplyPoInVulnScanUnit(DB_PO_IN_VULN_SCAN_UNIT&	data)
{
	if(FindItem(data.tDPH.nID))
	{
		return EditPoInVulnScanUnit(data);
	}
	return AddPoInVulnScanUnit(data);
}
//---------------------------------------------------------------------------

String					CManagePoInVulnScanUnit::GetName(UINT32 nID)
{
	PDB_PO_IN_VULN_SCAN_UNIT pdata = FindItem(nID);
    if(!pdata)	return "";
    return pdata->tDPH.strName;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManagePoInVulnScanUnit::SetPkt(MemToken& SendToken)
{
    SendToken.TokenAdd_32(m_tMap.size());

	TMapDBPoInVulnScanUnitItor begin, end;
    begin = m_tMap.begin();	end = m_tMap.end();
    for(begin; begin != end; begin++)
    {
    	SetPkt(&(begin->second), SendToken);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInVulnScanUnit::SetPkt(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_VULN_SCAN_UNIT pdata = FindItem(nID);
	if(!pdata)	return -1;

	return SetPkt(pdata, SendToken);
}
//---------------------------------------------------------------------------

INT32					CManagePoInVulnScanUnit::SetPkt(PDB_PO_IN_VULN_SCAN_UNIT pdata, MemToken& SendToken)
{
	SendToken.TokenAdd_DPH(pdata->tDPH);

	SendToken.TokenAdd_64(pdata->nSchTime);
	SendToken.TokenAdd_32(pdata->nScanType);

	SendToken.TokenSet_Block();
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInVulnScanUnit::GetPkt(MemToken& RecvToken, DB_PO_IN_VULN_SCAN_UNIT& data)
{
	if (!RecvToken.TokenDel_DPH(data.tDPH))							goto	INVALID_PKT;

	if (!RecvToken.TokenDel_64(data.nSchTime))						goto	INVALID_PKT;
	if (!RecvToken.TokenDel_32(data.nScanType))						goto	INVALID_PKT;

	RecvToken.TokenSkip_Block();
	return 0;
INVALID_PKT:
	return -1;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------



