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
#include "ManageLogicTimer.h"

//---------------------------------------------------------------------------

CManageLogicTimer*	t_ManageLogicTimer = NULL;

//---------------------------------------------------------------------------

CManageLogicTimer::CManageLogicTimer()
{
	m_nGlobalID	= 0;
}
//---------------------------------------------------------------------------

CManageLogicTimer::~CManageLogicTimer()
{
	
}
//---------------------------------------------------------------------------

INT32		CManageLogicTimer::AddLogicBase(PVOID tLogicBase, INT32 nPeriodSec)
{
	MEM_LOGIC_TIMER tMLT;
	tMLT.nID		= m_nGlobalID++;
	tMLT.tLogicBase	= tLogicBase;
	tMLT.nPeriodSec	= nPeriodSec;
	
	return AddItem(tMLT);
}
//---------------------------------------------------------------------------

INT32		CManageLogicTimer::EditLogicBase(PVOID tLogicBase, INT32 nPeriodSec)
{
	PMEM_LOGIC_TIMER pMLT = FindItemByLogic(tLogicBase);
	
	if(pMLT)
	{
		pMLT->nPeriodSec	= nPeriodSec;
	}
	
	return 0;
}
//---------------------------------------------------------------------------

INT32		CManageLogicTimer::DelLogicBase(PVOID tLogicBase)
{
	PMEM_LOGIC_TIMER pMLT = FindItemByLogic(tLogicBase);

	if(pMLT)
	{
		DeleteItem(pMLT->nID);
	}
	return 0;
}
//---------------------------------------------------------------------------

PMEM_LOGIC_TIMER	CManageLogicTimer::FindItemByLogic(PVOID tLogicBase)
{
	TMapMemLogicTimerItor begin, end;
	begin = m_tMap.begin();	end = m_tMap.end();
	for(begin; begin != end; begin++)
	{
		if(begin->second.tLogicBase != tLogicBase)		continue;

		return &(begin->second);
	}
	return NULL;
}
//---------------------------------------------------------------------------

