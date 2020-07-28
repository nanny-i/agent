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
#include "LogicMgrHostSys.h"

//---------------------------------------------------------------------------

CLogicMgrHostSys*		t_LogicMgrHostSys = NULL;

//---------------------------------------------------------------------------

CLogicMgrHostSys::CLogicMgrHostSys()
{
 	t_ManageHostSys		= new CManageHostSys();
	
	t_ManageHostSys->LoadDBMS();

	m_strLogicName = "logic mgr host sys";
	
	m_nControlType	= SS_CONTROL_TYPE_ORG_HOST;	
	m_nEvtObjType	= EVENT_OBJECT_TYPE_HOST;
	m_nEvtObjCode	= 0;
}
//---------------------------------------------------------------------------

CLogicMgrHostSys::~CLogicMgrHostSys()
{
	SAFE_DELETE(t_ManageHostSys);
}
//---------------------------------------------------------------------------

INT32		CLogicMgrHostSys::AnalyzePkt_FromMgr_Ext()
{
	UINT32 nRtn = AZPKT_CB_RTN_SUCCESS;
	switch(m_nPktCode)
	{
		default:
		{
			nRtn = AZPKT_CB_RTN_PKT_NOT_DEFINE_CODE;
			break;
		}
	}

	return SetHdrAndRtn(nRtn);
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

INT32		CLogicMgrHostSys::AnalyzePkt_FromMgr_Edit_Ext()
{
	PDB_HOST_SYS pdhs = NULL;
	DB_HOST_SYS dhs;

	if( t_ManageHostSys->GetPkt(RecvToken, dhs, SS_PKT_TYPE_AGENT))		return AZPKT_CB_RTN_PKT_INVALID;

	if( (pdhs = t_ManageHostSys->FirstItem()) == NULL)
	{
		WriteLogE("[%s] not find host sys info", m_strLogicName.c_str());
		return AZPKT_CB_RTN_DBMS_FAIL;	
	}

	if(pdhs->nOsID == dhs.nOsID && pdhs->nOsSP == dhs.nOsSP && 
		pdhs->nOsPd == dhs.nOsPd && pdhs->nOsPa == dhs.nOsPa &&
		pdhs->strOsPdLux == dhs.strOsPdLux)							return AZPKT_CB_RTN_SUCCESS_END;

	// 20200724 add jhjung
	if(pdhs->nOsID != dhs.nOsID)
		t_ManageHostSys->SetHostSysType(dhs.nOsID);

	pdhs->nOsID			= dhs.nOsID;
	pdhs->nOsSP			= dhs.nOsSP;
	pdhs->nOsPd			= dhs.nOsPd;
	pdhs->nOsPa			= dhs.nOsPa;
	pdhs->strOsPdLux	= dhs.strOsPdLux;	

	if(SetER(t_ManageHostSys->EditHostSys(*pdhs)))
	{
		WriteLogE("[%s] edit host information fail : [%u]", m_strLogicName.c_str(), pdhs->nID);
		return AZPKT_CB_RTN_DBMS_FAIL;	
	}

	{	
		t_ManageHostSys->SetPkt(SendToken);
		SendData_Link(G_TYPE_HOST_SYS, G_CODE_COMMON_EDIT, SendToken);
		SendToken.Clear();
	}

	return AZPKT_CB_RTN_SUCCESS_END;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void		CLogicMgrHostSys::SendPkt_Edit()
{
	INT32 nSendPkt = 1;	
	DB_HOST_SYS dhs;

	{
		CSystemInfo tSystemInfo;
		dhs.nOsID	= tSystemInfo.GetSystemID();
		dhs.nOsSP	= tSystemInfo.GetSPID();
		dhs.nOsPa	= tSystemInfo.GetSystemPaType();
		dhs.nOsPd	= tSystemInfo.GetSystemPdType();

		// 20200724 add jhjung
		//dhs.strOsPdLux	= "???????????????????????";
	}
	
	PDB_HOST_SYS pdhs = t_ManageHostSys->FirstItem();
	if(!pdhs)
	{
		WriteLogE("[%s] not find host sys first item..", m_strLogicName.c_str());
		goto SEND_PKT;
	}	

	do 
	{
		// 20200724 edit jhjung
		if( pdhs->nOsID != dhs.nOsID ||
			pdhs->nOsSP != dhs.nOsSP ||
			pdhs->nOsPa != dhs.nOsPa ||
			pdhs->nOsPd != dhs.nOsPd ||
			pdhs->strOsPdLux != dhs.strOsPdLux)
		{
			break;
		}

		nSendPkt = 0;
	} while (FALSE);

	if(!nSendPkt)	return;

SEND_PKT:
	SendToken.Clear();
	t_ManageHostSys->SetPkt(&dhs, SendToken);
	SendData(G_TYPE_HOST_SYS, G_CODE_COMMON_EDIT, SendToken);
	SendToken.Clear();

	return;
}
//---------------------------------------------------------------------------