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
#include "LogicMgrSiteVulnLock.h"

//---------------------------------------------------------------------------

CLogicMgrSiteVulnLock*		t_LogicMgrSiteVulnLock = NULL;

//---------------------------------------------------------------------------

CLogicMgrSiteVulnLock::CLogicMgrSiteVulnLock()
{
	t_LogicSiteVulnLock		= new CLogicSiteVulnLock();
	t_ManageSiteVulnLock		= new CManageSiteVulnLock();
	
	t_ManageSiteVulnLock->LoadDBMS();
	
	t_ManageSiteVulnLock->InitHash();

	m_strLogicName		= "mgr agt site vuln lock";
	
	m_nAgtPktEditCode	= G_CODE_COMMON_EDIT;	
	
	m_nControlType		= SS_CONTROL_TYPE_COMMON_SITE_VULN_LOCK;
	m_nEvtObjType		= EVENT_OBJECT_TYPE_COMMON;
	m_nEvtObjCode		= EVENT_OBJECT_CODE_COMMON_SITE_VULN_LOCK;
}
//---------------------------------------------------------------------------

CLogicMgrSiteVulnLock::~CLogicMgrSiteVulnLock()
{
	SAFE_DELETE(t_ManageSiteVulnLock);

	SAFE_DELETE(t_LogicSiteVulnLock);
}
//---------------------------------------------------------------------------
INT32		CLogicMgrSiteVulnLock::AnalyzePkt_FromMgr_Ext()
{
	return SetHdrAndRtn(AZPKT_CB_RTN_SUCCESS);
}
//---------------------------------------------------------------------------

INT32		CLogicMgrSiteVulnLock::AnalyzePkt_FromMgr_Edit_Ext()
{	
	TListDBSiteVulnLock	tDBSiteVulnLockList;

	if(!RecvToken.TokenDel_32(m_nRecvNum))						return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
	while(m_nRecvNum--)
	{
		DB_SITE_VULN_LOCK		data;	

		if( t_ManageSiteVulnLock->GetPkt(RecvToken, data))		return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);

		tDBSiteVulnLockList.push_back(data);
	}

	{
		TListID tIDList;
		t_ManageSiteVulnLock->GetItemIDList(tIDList);
		TListIDItor begin, end;
		begin = tIDList.begin();	end = tIDList.end();
		for(begin; begin != end; begin++)
		{
			if(t_ManageSiteVulnLock->IsExistID(*begin, tDBSiteVulnLockList))		continue;

			t_ManageSiteVulnLock->DelSiteVulnLock(*begin);
		}
	}

	{
		TListDBSiteVulnLockItor begin, end;
		begin = tDBSiteVulnLockList.begin();	end = tDBSiteVulnLockList.end();
		for(begin; begin != end; begin++)
		{
			if(t_ManageSiteVulnLock->ApplySiteVulnLock(*begin))
			{
				SetDLEA_EC(g_nErrRtn);
				WriteLogE("[%s] apply policy unit information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
				continue;
			}
		}

		t_ManageSiteVulnLock->InitHash();
	}

	return SetHdrAndRtn(AZPKT_CB_RTN_SUCCESS);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
