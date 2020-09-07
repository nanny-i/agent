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
#include "LogicPtnPatch.h"

//---------------------------------------------------------------------------

CLogicPtnPatch*		t_LogicPtnPatch = NULL;

//---------------------------------------------------------------------------

CLogicPtnPatch::CLogicPtnPatch()
{	
	m_strLogicName = "logic ptn patch";
}
//---------------------------------------------------------------------------

CLogicPtnPatch::~CLogicPtnPatch()
{
}
//---------------------------------------------------------------------------

void		CLogicPtnPatch::AnalyzePkt_PtnPatch(PPKT_DATA pkt_data)
{
	InitBaseMember(pkt_data);
	switch(m_nPktCode)
    {
		default:
        {
        	WriteLogE("[%s] not define pkt code from console : [%d][%d]", m_strLogicName.c_str(), m_nPktType, m_nPktCode);
			break;
        }
    }
	InitBaseMember();
    return;
}
//---------------------------------------------------------------------------

void		CLogicPtnPatch::SendPkt_Sync()
{
	TMapID tIDMap;
	t_ManageLinkEnv->GetKeyIDMap(G_TYPE_PTN_PATCH, tIDMap);

	SendData_Link(G_TYPE_PTN_PATCH, G_CODE_COMMON_SYNC, SendToken);
	SendToken.Clear();
}
//---------------------------------------------------------------------------



