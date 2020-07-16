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

// ThreadSocket.cpp : implementation file
//

#include "stdafx.h"
#include "com_struct.h"
#include "ThreadSocket.h"

//---------------------------------------------------------------------------

void		CThreadSocket::InitPktDbgTime(String strName, PPKT_DATA pkt_data)
{
	m_nChkPktDbgTime = GetTickCount();
	m_strPktDbgName = strName;

	if(!(t_EnvInfo->m_nRemainSockLog))	return;
	
	String strLogFileName;
	strLogFileName = SPrintf("/nanny_%s_pkt_log_", strName.c_str());
	WriteLogN_Size(3, strLogFileName.c_str(), "init pkt op time {%d}[%d][%d]:[%d]", (pkt_data ? pkt_data->nSessionID : 0), (pkt_data ? pkt_data->hdr.type : 0), (pkt_data ? pkt_data->hdr.code : 0), (pkt_data ? pkt_data->hdr.length : 0));
}
//---------------------------------------------------------------------------

void		CThreadSocket::FreePktDbgTime(String strName, PPKT_DATA pkt_data)
{
	m_nChkPktDbgTime = (GetTickCount() - m_nChkPktDbgTime);
		
	if(t_EnvInfo->m_nRemainSockLog)
	{
		String strLogFileName;
		strLogFileName = SPrintf("/nanny_%s_pkt_log_", strName.c_str());
		WriteLogN_Size(3, strLogFileName.c_str(), "free pkt op time {%d}[%d][%d]:[%d]", (pkt_data ? pkt_data->nSessionID : 0), (pkt_data ? pkt_data->hdr.type : 0), (pkt_data ? pkt_data->hdr.code : 0), m_nChkPktDbgTime);
	}

	if(m_nChkPktDbgTime > 1000)
	{
		WriteLogN_Size(100, "/nanny_common_pkt_log_", "pkt op time over [%s]{%d}[%d][%d]:[%d]", strName.c_str(), (pkt_data ? pkt_data->nSessionID : 0), (pkt_data ? pkt_data->hdr.type : 0), (pkt_data ? pkt_data->hdr.code : 0), m_nChkPktDbgTime);
	}
	return;
}
//---------------------------------------------------------------------------