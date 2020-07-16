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
#include "LogicAuth.h"

//---------------------------------------------------------------------------

CLogicAuth*		t_LogicAuth = NULL;

//---------------------------------------------------------------------------

CLogicAuth::CLogicAuth()
{
	m_strLogicName = "logic auth";
}
//---------------------------------------------------------------------------

CLogicAuth::~CLogicAuth()
{
}
//---------------------------------------------------------------------------

void		CLogicAuth::AnalyzePkt_Auth(PPKT_DATA pkt_data)
{
	InitBaseMember(pkt_data);
	switch(m_nPktCode)
    {
		case AK_CODE_AUTH_LOGIN:		AnalyzePkt_Auth_Login();		break;
		default:
        {
        	WriteLogE("[%s] not define pkt code : [%d][%d]", m_strLogicName.c_str(), m_nPktType, m_nPktCode);
			break;
        }
    }
	InitBaseMember();
    return;
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

void		CLogicAuth::AnalyzePkt_Auth_Login()
{
	DB_LINK_LICENSE tDLL;
	PDB_LINK_LICENSE pDLL = NULL;
	if( RecvToken.TokenDel_String(tDLL.strLicenseKey) < 0)	goto INVALID_PKT;

	{	
		if((pDLL = t_ManageLinkLicense->FindLicense(tDLL.strLicenseKey)) == NULL)
		{
			SendToken.TokenAdd_32(ERR_AUTH_ACCOUNT_INFO_INVALID);
			goto SEND_PKT;
		}				
	}

	{
		UINT32 nNextSID = t_ManageLinkLicense->GetNextSID();
		EditSID_Link(m_nSessionID, nNextSID);
		m_tPktData->nSessionID = nNextSID;

		SendToken.TokenAdd_32(ERR_SUCCESS);
	}

	goto SEND_PKT;
	
INVALID_PKT:
	SendToken.TokenAdd_32(ERR_SOCKET_SVR_TO_CLT_INVALID_PKT);
	WriteLogE("[%s] recv invalid pkt : [%d][%d]:[%d]", m_strLogicName.c_str(), m_nPktType, m_nPktCode, m_nDbgPos);

SEND_PKT:
	SendData_Link(m_tPktData, SendToken);
	return;	
}
//--------------------------------------------------------------------------- 
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
