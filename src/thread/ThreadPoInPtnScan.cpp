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

// ThreadPoInPtnScan.cpp : implementation file
//

#include "stdafx.h"
#include "com_struct.h"
#include "ThreadPoInPtnScan.h"

/////////////////////////////////////////////////////////////////////////////
// CThreadPoInPtnScan

CThreadPoInPtnScan*	t_ThreadPoInPtnScan = NULL;

CThreadPoInPtnScan::CThreadPoInPtnScan()
{
	m_nOrderID = 10000;
	m_nWorkID = 0;
}

CThreadPoInPtnScan::~CThreadPoInPtnScan()
{
}

BOOL CThreadPoInPtnScan::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CThreadPoInPtnScan::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CThreadBase::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// CThreadPoInPtnScan message handlers



INT32		CThreadPoInPtnScan::AddWork(PDB_PO_IN_PTN_OP_UNIT punit)
{
	m_tWorkMutex.Lock();		
	m_tWorkInfoMap[GetNextOrderID()] = *punit;
	m_tWorkMutex.UnLock();
	return 0;
}
//---------------------------------------------------------------------------

INT32		CThreadPoInPtnScan::DelWork(UINT32 nID)
{
	m_tWorkMutex.Lock();	
	m_tWorkInfoMap.erase(nID);
	m_tWorkMutex.UnLock();
	return 0;
}
//---------------------------------------------------------------------------

UINT32			CThreadPoInPtnScan::GetNextWork()
{
	UINT32 nRtn = 0;
	m_tWorkMutex.Lock();
	if(m_tWorkInfoMap.size())
	{
		nRtn = m_tWorkInfoMap.begin()->first;
	}
	m_tWorkMutex.UnLock();
	return nRtn;
}
//-------------------------------------------------------------------------------

PDB_PO_IN_PTN_OP_UNIT	CThreadPoInPtnScan::GetCurWork()
{
	PDB_PO_IN_PTN_OP_UNIT pdata = NULL;
	m_tWorkMutex.Lock();	
	TMapDBPoInPtnOpUnitItor find = m_tWorkInfoMap.find(m_nWorkID);
	if(find != m_tWorkInfoMap.end())
		pdata = &(find->second);
	m_tWorkMutex.UnLock();

	return pdata;
}
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------

int CThreadPoInPtnScan::Run() 
{
	// TODO: Add your specialized code here and/or call the base class
	m_nRunFlag = 1;

	WriteLogN("start %s thread : [%d]", m_strThreadName.c_str(), m_nRunFlag);

	while(t_EnvInfoOp && t_EnvInfoOp->GetMainContinue() && GetContinue())
	{
		m_nWorkID = GetNextWork();
		if(m_nWorkID)
		{	
			do 
			{
				if(StartScan())
				{
					WriteLogE("init environment fail : [%s][oid:%u]", m_strThreadName.c_str(), m_nWorkID);
					break;
				}

				if(m_tWEngWLExMap.size())
				{
					ProcessScanResult();

// 					WriteLogN("send message : [%x]", t_EnvInfoOp->GetMainHandle());
// 					DWORD hRst = SendMessage(t_EnvInfoOp->GetMainHandle(), WM_GLOBAL_THREAD_END, (WPARAM)&m_tCurPolicy, (LPARAM)G_TYPE_PO_IN_PTN_LO);			
//					WriteLogN("return send message : [%x][%d]", t_EnvInfoOp->GetMainHandle(), hRst);
				}
			} while (FALSE);						

			StopScan();
			DelWork(m_nWorkID);
			WriteLogE("stop scan : [%s][oid:%u]", m_strThreadName.c_str(), m_nWorkID);
		}
		Sleep(10);
	}

	if(!t_EnvInfoOp)							WriteLogE("environment operation util is null : [%s]", m_strThreadName.c_str());
	else if(!t_EnvInfoOp->GetMainContinue())	WriteLogN("stop thread by main continue flag : [%s]", m_strThreadName.c_str());
	else if(!GetContinue())						WriteLogN("stop thread by sub continue flag : [%s]", m_strThreadName.c_str());

	return 0;
}
//---------------------------------------------------------------------------

INT32		CThreadPoInPtnScan::StartScan()
{
	{
		CHAR szDLLName[CHAR_MAX_SIZE] = {0, };

		if(m_tFFDLLUtil.LoadLibraryExt(FormatString(szDLLName, "%s/asi_ff.dll", t_EnvInfo->m_strDLLPath.c_str())))
		{
			WriteLogE("load library fail : [%s][%d]", szDLLName, errno);
			return -15;
		}
	}

	{
		ASI_FF_INIT_INFO tAFII;
		t_EnvInfoOp->GetFFPtnInitData(tAFII);
		m_tFFDLLUtil.ASIFF_Init(&tAFII);
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32		CThreadPoInPtnScan::StopScan()
{
	m_tFFDLLUtil.FreeLibraryExt();
	return 0;
}
//---------------------------------------------------------------------------

INT32		CThreadPoInPtnScan::ChkScanFile()
{
	return 0;
}
//---------------------------------------------------------------------------

INT32		CThreadPoInPtnScan::ProcessScanResult()
{
	return 0;
}
//---------------------------------------------------------------------------
