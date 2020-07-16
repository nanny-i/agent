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

// ThreadEvtMon.cpp : implementation file
//

#include "stdafx.h"
#include "com_struct.h"
#include "ThreadEvtMon.h"

/////////////////////////////////////////////////////////////////////////////
// CThreadEvtMon

CThreadEvtMon*	t_ThreadEvtMon = NULL;

CThreadEvtMon::CThreadEvtMon()
{
}

CThreadEvtMon::~CThreadEvtMon()
{
}

BOOL CThreadEvtMon::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CThreadEvtMon::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CThreadBase::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// CThreadEvtMon message handlers

int CThreadEvtMon::Run() 
{
	// TODO: Add your specialized code here and/or call the base class
	m_nRunFlag = 1;
	WriteLogN("start %s thread : [%d]", m_strThreadName.c_str(), m_nRunFlag);
	while(t_EnvInfoOp && t_EnvInfoOp->GetMainContinue() && GetContinue())
	{
		if(!m_nPause)
		{
			ChkEvtTime();
		}
		
		Sleep(100);
	}

	if(!t_EnvInfoOp)
		WriteLogE("environment operation util is null : [%s]", m_strThreadName.c_str());
	else if(!t_EnvInfoOp->GetMainContinue())
		WriteLogN("stop thread by main continue flag : [%s]", m_strThreadName.c_str());
	else if(!GetContinue())
		WriteLogN("stop thread by sub continue flag : [%s]", m_strThreadName.c_str());

	return 0;
}
//------------------------------------------------------------------------------

INT32	CThreadEvtMon::ChkEvtTime()
{
	TListMemEvtMon tEvtMonList;
	t_ManageEvtMon.GetOverTimeEvtMon(tEvtMonList);
	TListMemEvtMonItor begin, end;
	begin = tEvtMonList.begin();	end = tEvtMonList.end();
	for(begin; begin != end; begin++)
	{
		WriteLogN("[%s] detect over time evt : [%d]:[%d][%s][%d][%d] : %I64u", m_strThreadName.c_str(), begin->nID, begin->nClass, begin->strName.c_str(), begin->nType, begin->nCode, begin->nThreadID);
	}
	return 0;
}
//------------------------------------------------------------------------------