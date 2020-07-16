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
#include "ManageSiteVulnScan.h"

//---------------------------------------------------------------------------

CManageSiteVulnScan*	t_ManageSiteVulnScan = NULL;

//---------------------------------------------------------------------------

CManageSiteVulnScan::CManageSiteVulnScan()
{
	t_DBMgrSiteVulnScan	= new CDBMgrSiteVulnScan();
}
//---------------------------------------------------------------------------

CManageSiteVulnScan::~CManageSiteVulnScan()
{
	if(t_DBMgrSiteVulnScan)	{	delete t_DBMgrSiteVulnScan;	t_DBMgrSiteVulnScan = NULL;	}
}
//---------------------------------------------------------------------------

INT32		CManageSiteVulnScan::LoadDBMS()
{
	TListDBSiteVulnScan tDBSiteVulnScanList;
    TListDBSiteVulnScanItor begin, end;
	if(SetER(t_DBMgrSiteVulnScan->LoadExecute(&tDBSiteVulnScanList)))
    {
    	return g_nErrRtn;
    }

    begin = tDBSiteVulnScanList.begin();	end = tDBSiteVulnScanList.end();
    for(begin; begin != end; begin++)
    {
    	AddItem(begin->nID, *begin);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManageSiteVulnScan::InitHash()
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

INT32					CManageSiteVulnScan::GetHashData(UINT32 nID, String& strOrgValue)
{
	PDB_SITE_VULN_SCAN pdata 			= NULL;
	{
		if( (pdata = FindItem(nID)) == NULL)
		{
			WriteLogE("not find site_vuln_scan by hash : [%d]", ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			return ERR_INFO_NOT_OP_BECAUSE_NOT_FIND;
		}
	}

	{
		strOrgValue = SPrintf("%u,%u,%u,%u,%u,%u,"
							"%s,%s,"
							"%u,%I64u,%u,"
							"%u,%u,%u,"
							"%u,%u,"
							"%s, %u,"
							"%u,%u,%s,", 
							pdata->nID, pdata->nUsedFlag, pdata->nRegDate, pdata->nUsedMode, pdata->nAdminID, pdata->nExtOption,
							pdata->strName.c_str(), pdata->strDescr.c_str(), 
							pdata->nOsType, pdata->nOsID, pdata->nOsPa, 
							pdata->nSVulnID, pdata->nSVulnSubID, pdata->nScanOrder,
							pdata->nScanType, pdata->nCustomID,
							pdata->strScanPath.c_str(), pdata->nValueType,
							pdata->nDecisionType, pdata->nCompType, pdata->strCompValue.c_str());

		//TRACE("%s\n", strOrgValue);
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManageSiteVulnScan::AddSiteVulnScan(DB_SITE_VULN_SCAN&	data)
{
	if(SetER(t_DBMgrSiteVulnScan->InsertExecute(&data)))
    {
    	return g_nErrRtn;
    }

    AddItem(data.nID, data);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManageSiteVulnScan::EditSiteVulnScan(DB_SITE_VULN_SCAN&	data)
{
	PDB_SITE_VULN_SCAN pdata = FindItem(data.nID);
	if(!pdata)	return ERR_DBMS_UPDATE_FAIL;

	if(SetER(t_DBMgrSiteVulnScan->UpdateExecute(&data)))
    {
    	return g_nErrRtn;
    }

    EditItem(data.nID, data);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManageSiteVulnScan::DelSiteVulnScan(UINT32 nID)
{
	PDB_SITE_VULN_SCAN pdata = FindItem(nID);
	if(!pdata)	return ERR_DBMS_DELETE_FAIL;

	if(SetER(t_DBMgrSiteVulnScan->DeleteExecute(pdata->nID)))
    {
    	return g_nErrRtn;
    }

    DeleteItem(nID);
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManageSiteVulnScan::ApplySiteVulnScan(DB_SITE_VULN_SCAN&	data)
{
	if(FindItem(data.nID))
	{
		return EditSiteVulnScan(data);
	}
	return AddSiteVulnScan(data);
}
//---------------------------------------------------------------------------

String					CManageSiteVulnScan::GetName(UINT32 nID)
{
	PDB_SITE_VULN_SCAN pdata = FindItem(nID);
    if(!pdata)	return "";
    return pdata->strName;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManageSiteVulnScan::SetPkt(MemToken& SendToken)
{
    SendToken.TokenAdd_32(m_tMap.size());

	TMapDBSiteVulnScanItor begin, end;
    begin = m_tMap.begin();	end = m_tMap.end();
    for(begin; begin != end; begin++)
    {
    	SetPkt(&(begin->second), SendToken);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManageSiteVulnScan::SetPkt(UINT32 nID, MemToken& SendToken)
{
	PDB_SITE_VULN_SCAN pdata = FindItem(nID);
	if(!pdata)	return -1;

	SetPkt(pdata, SendToken);
	
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManageSiteVulnScan::SetPkt(PDB_SITE_VULN_SCAN pdata, MemToken& SendToken)
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
	SendToken.TokenAdd_32(pdata->nScanOrder);

	SendToken.TokenAdd_32(pdata->nScanType);
	SendToken.TokenAdd_32(pdata->nCustomID);

	SendToken.TokenAdd_String(pdata->strScanPath);
	SendToken.TokenAdd_32(pdata->nValueType);

	SendToken.TokenAdd_32(pdata->nDecisionType);
	SendToken.TokenAdd_32(pdata->nCompType);
	SendToken.TokenAdd_String(pdata->strCompValue);

	SendToken.TokenSet_Block();
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManageSiteVulnScan::GetPkt(MemToken& RecvToken, DB_SITE_VULN_SCAN& data)
{
	if(!RecvToken.TokenDel_32(data.nID))					goto INVALID_PKT;
	if(!RecvToken.TokenDel_32(data.nUsedFlag))				goto INVALID_PKT;
	if(!RecvToken.TokenDel_32(data.nRegDate))				goto INVALID_PKT;
	if(!RecvToken.TokenDel_32(data.nUsedMode))				goto INVALID_PKT;
	if(!RecvToken.TokenDel_32(data.nAdminID))				goto INVALID_PKT;
	if(!RecvToken.TokenDel_32(data.nExtOption))				goto INVALID_PKT;

	if( RecvToken.TokenDel_String(data.strName) < 0)		goto INVALID_PKT;
	if( RecvToken.TokenDel_String(data.strDescr) < 0)		goto INVALID_PKT;

	if(!RecvToken.TokenDel_32(data.nOsType))				goto INVALID_PKT;
	if(!RecvToken.TokenDel_64(data.nOsID))					goto INVALID_PKT;
	if(!RecvToken.TokenDel_32(data.nOsPa))					goto INVALID_PKT;

	if(!RecvToken.TokenDel_32(data.nSVulnID))				goto INVALID_PKT;
	if(!RecvToken.TokenDel_32(data.nSVulnSubID))			goto INVALID_PKT;
	if(!RecvToken.TokenDel_32(data.nScanOrder))				goto INVALID_PKT;

	if(!RecvToken.TokenDel_32(data.nScanType))				goto INVALID_PKT;
	if(!RecvToken.TokenDel_32(data.nCustomID))				goto INVALID_PKT;

	if( RecvToken.TokenDel_String(data.strScanPath) < 0)	goto INVALID_PKT;
	if(!RecvToken.TokenDel_32(data.nValueType))				goto INVALID_PKT;

	if(!RecvToken.TokenDel_32(data.nDecisionType))			goto INVALID_PKT;
	if(!RecvToken.TokenDel_32(data.nCompType))				goto INVALID_PKT;
	if( RecvToken.TokenDel_String(data.strCompValue) < 0)	goto INVALID_PKT;

	RecvToken.TokenSkip_Block();

	return 0;
INVALID_PKT:
	return -1;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------



