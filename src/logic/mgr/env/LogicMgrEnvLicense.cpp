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
#include "LogicMgrEnvLicense.h"

//---------------------------------------------------------------------------

CLogicMgrEnvLicense*		t_LogicMgrEnvLicense = NULL;

//---------------------------------------------------------------------------

CLogicMgrEnvLicense::CLogicMgrEnvLicense()
{
	t_ManageEnvLicense	= new CManageEnvLicense();
	t_ManageEnvLicense->LoadDBMS();
	t_ManageEnvLicense->InitHash();

	m_strLogicName		= "mgr env license";

	m_nControlType		= SS_CONTROL_TYPE_ENV_LICENSE;	
	m_nEvtObjType		= EVENT_OBJECT_TYPE_ENV;
	m_nEvtObjCode		= EVENT_OBJECT_CODE_ENV_LICENSE;
}
//---------------------------------------------------------------------------

CLogicMgrEnvLicense::~CLogicMgrEnvLicense()
{
	SAFE_DELETE(t_ManageEnvLicense);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32		CLogicMgrEnvLicense::AnalyzePkt_FromMgr_Ext()
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

INT32		CLogicMgrEnvLicense::AnalyzePkt_FromMgr_Edit_Ext()
{
	DB_ENV_LICENSE del;

	if( t_ManageEnvLicense->GetPkt(RecvToken, del))	return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
	
	if(t_ManageEnvLicense->ApplyEnvLicense(del))
	{
		SetDLEA_EC(g_nErrRtn);
		WriteLogE("[%s] apply env information : [%d]", m_strLogicName.c_str(), g_nErrRtn);			
		return SetHdrAndRtn(AZPKT_CB_RTN_DBMS_FAIL);
	}

	t_ManageEnvLicense->InitHash();

	return SetHdrAndRtn(AZPKT_CB_RTN_SUCCESS);
}
//---------------------------------------------------------------------------

INT32		CLogicMgrEnvLicense::ApplyPolicy()
{	
	return 0;
}
//---------------------------------------------------------------------------

INT32		CLogicMgrEnvLicense::OnTimer_Logic()
{
	return 0;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
