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

INT32		CThreadSocket::Logic_CltUdt(INT32& nTotalPktCnt, INT32 nOncePktNum)
{
	PKT_DATA pkt_data;
	CMainDlg* pMainDlg = (CMainDlg*)t_EnvInfoOp->GetMainHandle();
	CCltSocketUtil*	tCltSocketUtil		= t_UdtCltUtil;

	if(pMainDlg == NULL || tCltSocketUtil == NULL)
	{
		WriteLogE("invalid logic clt udt class");
		return 1;
	}

	memset(&pkt_data, 0, sizeof(PKT_DATA));
	
	try
	{
		while(t_EnvInfo->m_nContinueOP && nOncePktNum && tCltSocketUtil->GetPkt_CLD(pkt_data) > 0)
		{
			nOncePktNum--;
			if(pkt_data.nIsSockEvent)
			{
				if(pkt_data.sock_evt.nEventID == ASI_SOCKET_EVENT_CONNECT)
				{
					WriteLogN("agt_udt connected [%d][%s]", pkt_data.nSessionID, ConvertIP(pkt_data.sock_evt.nAddress).c_str());
				}
				else if(pkt_data.sock_evt.nEventID == ASI_SOCKET_EVENT_DISCONNECT)
				{
					WriteLogN("agt_udt disconnected [%d][%s]", pkt_data.nSessionID,  ConvertIP(pkt_data.sock_evt.nAddress).c_str());
				}
			}
			else
			{
				InitPktDbgTime("agt_udt", &pkt_data);

				pMainDlg->OnSockEvtCltUdt(&pkt_data);
				
				tCltSocketUtil->FreeMemory_CLD(pkt_data.body.data);
				nTotalPktCnt++;
				FreePktDbgTime("agt_udt", &pkt_data);
			}
		}
	}
	catch(...)
	{
		WriteLogE("pkt operation (agt_udt) exception %d,%d", pkt_data.hdr.type, pkt_data.hdr.code);
	}
	return 1;
}
//---------------------------------------------------------------------------
