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
#include "LogicMgrSiteVulnRepair.h"

//---------------------------------------------------------------------------

CLogicMgrSiteVulnRepair*		t_LogicMgrSiteVulnRepair = NULL;

//---------------------------------------------------------------------------

CLogicMgrSiteVulnRepair::CLogicMgrSiteVulnRepair()
{
	t_LogicSiteVulnRepair		= new CLogicSiteVulnRepair();
	t_ManageSiteVulnRepair		= new CManageSiteVulnRepair();
	
	t_ManageSiteVulnRepair->LoadDBMS();
	
	t_ManageSiteVulnRepair->InitHash();

	m_strLogicName		= "mgr agt site vuln repair";
	
	m_nAgtPktEditCode	= G_CODE_COMMON_EDIT;	
	
	m_nControlType		= SS_CONTROL_TYPE_COMMON_SITE_VULN_REPAIR;
	m_nEvtObjType		= EVENT_OBJECT_TYPE_COMMON;
	m_nEvtObjCode		= EVENT_OBJECT_CODE_COMMON_SITE_VULN_REPAIR;
}
//---------------------------------------------------------------------------

CLogicMgrSiteVulnRepair::~CLogicMgrSiteVulnRepair()
{
	SAFE_DELETE(t_ManageSiteVulnRepair);

	SAFE_DELETE(t_LogicSiteVulnRepair);
}
//---------------------------------------------------------------------------
INT32		CLogicMgrSiteVulnRepair::AnalyzePkt_FromMgr_Ext()
{
	return SetHdrAndRtn(AZPKT_CB_RTN_SUCCESS);
}
//---------------------------------------------------------------------------

INT32		CLogicMgrSiteVulnRepair::AnalyzePkt_FromMgr_Edit_Ext()
{	
	TListDBSiteVulnRepair	tDBSiteVulnRepairList;

	if(!RecvToken.TokenDel_32(m_nRecvNum))						return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
	while(m_nRecvNum--)
	{
		DB_SITE_VULN_REPAIR		data;	

		if( t_ManageSiteVulnRepair->GetPkt(RecvToken, data))		return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);

		tDBSiteVulnRepairList.push_back(data);
	}

	{
		TListID tIDList;
		t_ManageSiteVulnRepair->GetItemIDList(tIDList);
		TListIDItor begin, end;
		begin = tIDList.begin();	end = tIDList.end();
		for(begin; begin != end; begin++)
		{
			if(t_ManageSiteVulnRepair->IsExistID(*begin, tDBSiteVulnRepairList))		continue;

			t_ManageSiteVulnRepair->DelSiteVulnRepair(*begin);
		}
	}

	{
		TListDBSiteVulnRepairItor begin, end;
		begin = tDBSiteVulnRepairList.begin();	end = tDBSiteVulnRepairList.end();
		for(begin; begin != end; begin++)
		{
			if(t_ManageSiteVulnRepair->ApplySiteVulnRepair(*begin))
			{
				SetDLEA_EC(g_nErrRtn);
				WriteLogE("[%s] apply policy unit information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
				continue;
			}
		}

		t_ManageSiteVulnRepair->InitHash();
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
