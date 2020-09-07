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
#include "LogicMgrPoFaDelFileAfterBoot.h"
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

CLogicMgrPoFaDelFileAfterBoot*	t_LogicMgrPoFaDelFileAfterBoot = NULL;

CLogicMgrPoFaDelFileAfterBoot::CLogicMgrPoFaDelFileAfterBoot()
{
	t_ManagePoFaDelFileAfterBoot	= new CManagePoFaDelFileAfterBoot();
	if(t_ManagePoFaDelFileAfterBoot)
		t_ManagePoFaDelFileAfterBoot->LoadDBMS();
	m_strLogicName		= "mgr po fa del file";
}
//---------------------------------------------------------------------------

CLogicMgrPoFaDelFileAfterBoot::~CLogicMgrPoFaDelFileAfterBoot()
{
	SAFE_DELETE(t_ManagePoFaDelFileAfterBoot);
}


INT32		CLogicMgrPoFaDelFileAfterBoot::DelFileAfterBoot()
{
	INT32 nBootTime = 0;
	INT32 nFileCount = 0;
	if(t_ManagePoFaDelFileAfterBoot == NULL)
	{
		WriteLogE("[%s] invalid input data", m_strLogicName.c_str());
		return -1;
	}

	nBootTime = uptime();
	nFileCount = t_ManagePoFaDelFileAfterBoot->GetDelFileListCount();

	if(nBootTime > TIMER_INTERVAL_TIME_SYS_BOOT || nFileCount < 1)
	{
		return 0;
	}

	WriteLogN("[%s] delete files (%d) on boot time (%d)", m_strLogicName.c_str(), nFileCount, nBootTime);

	t_ManagePoFaDelFileAfterBoot->DelFileListAfterBoot();
}

INT32		CLogicMgrPoFaDelFileAfterBoot::InsertDelFileInfo(LPCSTR pcFilePath)
{
	INT32 nRetVal = 0;
	if(t_ManagePoFaDelFileAfterBoot == NULL || pcFilePath == NULL || pcFilePath[0] == 0)
	{
		WriteLogE("[%s] invalid input data", m_strLogicName.c_str());
		return -1;
	}

	nRetVal = t_ManagePoFaDelFileAfterBoot->InsertFilePathAfterBoot(pcFilePath);
	if(nRetVal != 0)
	{
		WriteLogE("[%s] fail to insert file path info (%d)", m_strLogicName.c_str(), nRetVal);
		nRetVal -= 100;
		return nRetVal;
	}
	return 0;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
