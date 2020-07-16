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

// ThreadLog.cpp : implementation file
//

#include "stdafx.h"
#include "com_struct.h"
#include "ThreadLog.h"

/////////////////////////////////////////////////////////////////////////////
// CThreadLog

CThreadLog*	t_ThreadLog = NULL;

CThreadLog::CThreadLog()
{
}

CThreadLog::~CThreadLog()
{
}

BOOL CThreadLog::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CThreadLog::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CThreadBase::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// CThreadLog message handlers

int CThreadLog::Run() 
{
	// TODO: Add your specialized code here and/or call the base class
	//DWORD_PTR dwError = -1;
	PKT_DATA pkt_data;
	m_nRunFlag = 1;
	WriteLogN("start %s thread : [%d]", m_strThreadName.c_str(), m_nRunFlag);
	INT32 nMaxChk = 0;

	while(t_EnvInfoOp && t_EnvInfoOp->GetMainContinue() && GetContinue())
	{
		if(!m_nPause)
		{	
			memset(&pkt_data, 0, sizeof(PKT_DATA));
			pkt_data.hdr.code = G_CODE_COMMON_ADD;

		}
		Sleep(10);
	}

	if(!t_EnvInfoOp)
		WriteLogE("environment operation util is null : [%s]", m_strThreadName.c_str());
	else if(!t_EnvInfoOp->GetMainContinue())
		WriteLogN("stop thread by main continue flag : [%s]", m_strThreadName.c_str());
	else if(!GetContinue())
		WriteLogN("stop thread by sub continue flag : [%s]", m_strThreadName.c_str());

	return 0;
}
