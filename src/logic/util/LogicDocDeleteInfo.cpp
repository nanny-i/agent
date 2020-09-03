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
#include "LogicDocDeleteInfo.h"

//---------------------------------------------------------------------------

CLogicDocDeleteInfo*	t_LogicDocDeleteInfo = NULL;

CLogicDocDeleteInfo::CLogicDocDeleteInfo()
{
	t_ManageDocDeleteInfo			= new CManageDocDeleteInfo();
	t_ManageDocDeleteInfo->LoadDBMS();

	m_strLogicName		= "logic doc delete info";
}
//---------------------------------------------------------------------------

CLogicDocDeleteInfo::~CLogicDocDeleteInfo()
{
	SAFE_DELETE(t_ManageDocDeleteInfo);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void	CLogicDocDeleteInfo::SendPkt_DocDeleteInfo_Edit()
{
	DB_DOC_DELETE_INFO data;
	t_ManageDocDeleteInfo->GetData(data);
	t_ManageDocDeleteInfo->SetPkt(&data, SendToken);
	SendData_Mgr(G_TYPE_HOST_STATUS, G_CODE_HOST_SET_DOC_DEL_INFO, SendToken);
	SendToken.Clear();
	return;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------