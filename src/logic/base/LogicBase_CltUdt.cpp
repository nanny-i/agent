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
#include "LogicBase.h"

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void	CLogicBase::SendData_Udt(PPKT_DATA pkt_data, MemToken& SendToken)
{
	SendData_Udt(pkt_data->hdr.type, pkt_data->hdr.code, SendToken);
    return;
}
//---------------------------------------------------------------------------

void	CLogicBase::SendData_Udt(UINT16 nType, UINT16 nCode, MemToken& SendToken)
{
	t_UdtCltUtil->Send_CLD(nType, nCode, SendToken.GetLength(), SendToken.GetData());

    return;
}
//---------------------------------------------------------------------------

void	CLogicBase::EditSKey_Udt(UINT32 nSessionKey)
{
	t_UdtCltUtil->EditSessionKey_CLD(nSessionKey);

    return;
}
//---------------------------------------------------------------------------

void	CLogicBase::Disconnected_Udt()
{
	t_UdtCltUtil->CloseSocket_CLD(0);
	return;
}
//---------------------------------------------------------------------------

String	CLogicBase::GetConnectAddr_Udt()
{
	char pszAddr[CHAR_MAX_SIZE] = {0, };
	UINT32 nAddr = GetConnectIP_Udt();

    return ConvertIP(nAddr);
}
//---------------------------------------------------------------------------

UINT32	CLogicBase::GetConnectIP_Udt()
{
	UINT32 nAddr = 0;
	t_UdtCltUtil->GetLocalAddress_CLD(nAddr);

    return nAddr;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------



