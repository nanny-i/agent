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

#include "stdafx.h"
#include "com_struct.h"
#include "LogicLocalEnvAuth.h"

//---------------------------------------------------------------------------

CLogicLocalEnvAuth*	t_LogicLocalEnvAuth = NULL;

CLogicLocalEnvAuth::CLogicLocalEnvAuth()
{
	t_ManageLocalEnvAuth			= new CManageLocalEnvAuth();
	t_ManageLocalEnvAuth->LoadDBMS();

	m_strLogicName		= "logic local env auth";
}
//---------------------------------------------------------------------------

CLogicLocalEnvAuth::~CLogicLocalEnvAuth()
{
	SAFE_DELETE(t_ManageLocalEnvAuth);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void	CLogicLocalEnvAuth::SendPkt_LocalEnvAuth_Edit()
{
	t_ManageLocalEnvAuth->SetPkt(SendToken);
	SendData_Link(G_TYPE_LOCAL_ENV_AUTH, G_CODE_COMMON_EDIT, SendToken);
	SendToken.Clear();
	return;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------