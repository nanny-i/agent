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
#include "ManageSiteVulnRepair.h"

//---------------------------------------------------------------------------

CManageSiteVulnRepair*	t_ManageSiteVulnRepair = NULL;

//---------------------------------------------------------------------------

CManageSiteVulnRepair::CManageSiteVulnRepair()
{
	t_DBMgrSiteVulnRepair	= new CDBMgrSiteVulnRepair();
}
//---------------------------------------------------------------------------

CManageSiteVulnRepair::~CManageSiteVulnRepair()
{
	if(t_DBMgrSiteVulnRepair)	{	delete t_DBMgrSiteVulnRepair;	t_DBMgrSiteVulnRepair = NULL;	}
}
//---------------------------------------------------------------------------

INT32		CManageSiteVulnRepair::LoadDBMS()
{
	TListDBSiteVulnRepair tDBSiteVulnRepairList;
    TListDBSiteVulnRepairItor begin, end;
	if(SetER(t_DBMgrSiteVulnRepair->LoadExecute(&tDBSiteVulnRepairList)))
    {
    	return g_nErrRtn;
    }

    begin = tDBSiteVulnRepairList.begin();	end = tDBSiteVulnRepairList.end();
    for(begin; begin != end; begin++)
    {
    	AddItem(begin->nID, *begin);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManageSiteVulnRepair::InitHash()
{
	TListID tIDList;
	TListIDItor begin, end;

	String strOrgValue;
	
	GetItemIDList(tIDList);
	begin = tIDList.begin();		end = tIDList.end();
	for(begin; begin != end; begin++)
	{
		String strValue;
		GetHashData(*begin, strValue);

		strOrgValue += strValue;
	}	

	{
		char pszHashValue[CHAR_MAX_SIZE] = {0, };
		SHAString(ASIHASH_SHA_LEN_TYPE_128, strOrgValue.c_str(), strOrgValue.length(), pszHashValue, CHAR_MAX_SIZE);
		m_strFullHash = pszHashValue;
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManageSiteVulnRepair::GetHashData(UINT32 nID, String& strOrgValue)
{
	PDB_SITE_VULN_REPAIR pdata 			= NULL;
	{
		if( (pdata = FindItem(nID)) == NULL)
		{
			WriteLogE("not find site_vuln_repair by hash : [%d]", ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			return ERR_INFO_NOT_OP_BECAUSE_NOT_FIND;
		}
	}

	{
		strOrgValue = SPrintf("%u,%u,%u,%u,%u,%u,"
							"%s,%s,"
							"%u,%I64u,%u,"
							"%u,%u,%u,"
							"%u,%u,"
							"%s,%u,%u,%s,", 
							pdata->nID, pdata->nUsedFlag, pdata->nRegDate, pdata->nUsedMode, pdata->nAdminID, pdata->nExtOption,
							pdata->strName.c_str(), pdata->strDescr.c_str(), 
							pdata->nOsType, pdata->nOsID, pdata->nOsPa, 
							pdata->nSVulnID, pdata->nSVulnSubID, pdata->nRepairOrder,
							pdata->nRepairType, pdata->nCustomID,
							pdata->strRepairPath.c_str(), pdata->nValueType, pdata->nRepairOpType, pdata->strRepairValue.c_str());
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManageSiteVulnRepair::AddSiteVulnRepair(DB_SITE_VULN_REPAIR&	data)
{
	if(SetER(t_DBMgrSiteVulnRepair->InsertExecute(&data)))
    {
    	return g_nErrRtn;
    }

    AddItem(data.nID, data);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManageSiteVulnRepair::EditSiteVulnRepair(DB_SITE_VULN_REPAIR&	data)
{
	PDB_SITE_VULN_REPAIR pdata = FindItem(data.nID);
	if(!pdata)	return ERR_DBMS_UPDATE_FAIL;

	if(SetER(t_DBMgrSiteVulnRepair->UpdateExecute(&data)))
    {
    	return g_nErrRtn;
    }

    EditItem(data.nID, data);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManageSiteVulnRepair::DelSiteVulnRepair(UINT32 nID)
{
	PDB_SITE_VULN_REPAIR pdata = FindItem(nID);
	if(!pdata)	return ERR_DBMS_DELETE_FAIL;

	if(SetER(t_DBMgrSiteVulnRepair->DeleteExecute(pdata->nID)))
    {
    	return g_nErrRtn;
    }

    DeleteItem(nID);
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManageSiteVulnRepair::ApplySiteVulnRepair(DB_SITE_VULN_REPAIR&	data)
{
	if(FindItem(data.nID))
	{
		return EditSiteVulnRepair(data);
	}
	return AddSiteVulnRepair(data);
}
//---------------------------------------------------------------------------

String					CManageSiteVulnRepair::GetName(UINT32 nID)
{
	PDB_SITE_VULN_REPAIR pdata = FindItem(nID);
    if(!pdata)	return "";
    return pdata->strName;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManageSiteVulnRepair::SetPkt(MemToken& SendToken)
{
    SendToken.TokenAdd_32(m_tMap.size());

	TMapDBSiteVulnRepairItor begin, end;
    begin = m_tMap.begin();	end = m_tMap.end();
    for(begin; begin != end; begin++)
    {
    	SetPkt(&(begin->second), SendToken);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManageSiteVulnRepair::SetPkt(UINT32 nID, MemToken& SendToken)
{
	PDB_SITE_VULN_REPAIR pdata = FindItem(nID);
	if(!pdata)	return -1;

	SetPkt(pdata, SendToken);
	
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManageSiteVulnRepair::SetPkt(PDB_SITE_VULN_REPAIR pdata, MemToken& SendToken)
{
	SendToken.TokenAdd_32(pdata->nID);
	SendToken.TokenAdd_32(pdata->nUsedFlag);
	SendToken.TokenAdd_32(pdata->nRegDate);
	SendToken.TokenAdd_32(pdata->nUsedMode);
	SendToken.TokenAdd_32(pdata->nAdminID);
	SendToken.TokenAdd_32(pdata->nExtOption);

	SendToken.TokenAdd_String(pdata->strName);
	SendToken.TokenAdd_String(pdata->strDescr);

	SendToken.TokenAdd_32(pdata->nOsType);
	SendToken.TokenAdd_64(pdata->nOsID);
	SendToken.TokenAdd_32(pdata->nOsPa);

	SendToken.TokenAdd_32(pdata->nSVulnID);
	SendToken.TokenAdd_32(pdata->nSVulnSubID);
	SendToken.TokenAdd_32(pdata->nRepairOrder);

	SendToken.TokenAdd_32(pdata->nRepairType);
	SendToken.TokenAdd_32(pdata->nCustomID);

	SendToken.TokenAdd_String(pdata->strRepairPath);
	SendToken.TokenAdd_32(pdata->nValueType);
	SendToken.TokenAdd_32(pdata->nRepairOpType);
	SendToken.TokenAdd_String(pdata->strRepairValue);

	SendToken.TokenSet_Block();
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManageSiteVulnRepair::GetPkt(MemToken& RecvToken, DB_SITE_VULN_REPAIR& data)
{
	if(!RecvToken.TokenDel_32(data.nID))						goto INVALID_PKT;
	if(!RecvToken.TokenDel_32(data.nUsedFlag))					goto INVALID_PKT;
	if(!RecvToken.TokenDel_32(data.nRegDate))					goto INVALID_PKT;
	if(!RecvToken.TokenDel_32(data.nUsedMode))					goto INVALID_PKT;
	if(!RecvToken.TokenDel_32(data.nAdminID))					goto INVALID_PKT;
	if(!RecvToken.TokenDel_32(data.nExtOption))					goto INVALID_PKT;

	if( RecvToken.TokenDel_String(data.strName) < 0)			goto INVALID_PKT;
	if( RecvToken.TokenDel_String(data.strDescr) < 0)			goto INVALID_PKT;

	if(!RecvToken.TokenDel_32(data.nOsType))					goto INVALID_PKT;
	if(!RecvToken.TokenDel_64(data.nOsID))						goto INVALID_PKT;
	if(!RecvToken.TokenDel_32(data.nOsPa))						goto INVALID_PKT;

	if(!RecvToken.TokenDel_32(data.nSVulnID))					goto INVALID_PKT;
	if(!RecvToken.TokenDel_32(data.nSVulnSubID))				goto INVALID_PKT;
	if(!RecvToken.TokenDel_32(data.nRepairOrder))				goto INVALID_PKT;

	if(!RecvToken.TokenDel_32(data.nRepairType))				goto INVALID_PKT;
	if(!RecvToken.TokenDel_32(data.nCustomID))					goto INVALID_PKT;

	if( RecvToken.TokenDel_String(data.strRepairPath) < 0)		goto INVALID_PKT;
	if(!RecvToken.TokenDel_32(data.nValueType))					goto INVALID_PKT;
	if(!RecvToken.TokenDel_32(data.nRepairOpType))				goto INVALID_PKT;
	if( RecvToken.TokenDel_String(data.strRepairValue) < 0)		goto INVALID_PKT;

	RecvToken.TokenSkip_Block();

	return 0;
INVALID_PKT:
	return -1;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------



