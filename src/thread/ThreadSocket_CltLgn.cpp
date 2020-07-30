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

INT32		CThreadSocket::Logic_CltLgn(INT32& nTotalPktCnt, INT32 nOncePktNum)
{
	PKT_DATA pkt_data;
	CMainDlg* pMainDlg = (CMainDlg*)t_EnvInfoOp->GetMainHandle();
	CCltSocketUtil*	tCltSocketUtil = t_LgnCltUtil;

	if(pMainDlg == NULL || tCltSocketUtil == NULL)
	{
		WriteLogE("[Logic_CltLgn] invalid logic clt lgn class");
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
					WriteLogN("agt_lgn connected [%d][%s]", pkt_data.nSessionID, ConvertIP(pkt_data.sock_evt.nAddress).c_str());
				}
				else if(pkt_data.sock_evt.nEventID == ASI_SOCKET_EVENT_DISCONNECT)
				{
					WriteLogN("agt_lgn disconnected [%d][%s][%d]", pkt_data.nSessionID,  ConvertIP(pkt_data.sock_evt.nAddress).c_str(), pkt_data.sock_evt.nErrorCode);
				}
			}
			else
			{
				InitPktDbgTime("agt_lgn", &pkt_data);

				pMainDlg->OnSockEvtCltLgn(&pkt_data);

				tCltSocketUtil->FreeMemory_CLD(pkt_data.body.data);
				nTotalPktCnt++;
				FreePktDbgTime("agt_lgn", &pkt_data);
			}
		}
	}
	catch(...)
	{
		WriteLogE("pkt operation (agt_lgn) exception %d,%d", pkt_data.hdr.type, pkt_data.hdr.code);
	}
	return 1;
}
//---------------------------------------------------------------------------
