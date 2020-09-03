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
#include "ManageChkExistInterval.h"

//---------------------------------------------------------------------------

CManageChkExistInterval	t_ManageChkExistInterval;

//---------------------------------------------------------------------------

CManageChkExistInterval::CManageChkExistInterval()
{
	m_nGlobalID	= 0;

	InitChkExistInterval();
}
//---------------------------------------------------------------------------

CManageChkExistInterval::~CManageChkExistInterval()
{
	
}
//---------------------------------------------------------------------------

INT32		CManageChkExistInterval::InitChkExistInterval()
{
	return 0;
}

//---------------------------------------------------------------------------

INT32		CManageChkExistInterval::SetChkExistStatus(String strChkName, UINT32 nStatus)
{
	m_tMutex.Lock();

	MEM_CHK_EXIST_INTERVAL tdata;
	PMEM_CHK_EXIST_INTERVAL pdata = FindStrKeyItem(strChkName);
	if(!pdata)
	{
		{
			tdata.nID = ++m_nGlobalID;
			tdata.strChkName = strChkName;
		}
		AddStrKeyID(tdata.strChkName, tdata.nID);
		AddItem(tdata);
	}
	else
		tdata = *pdata;

	tdata.nStatus = nStatus;
	EditItem(tdata);

	m_tMutex.UnLock();

	return 0;
}
//---------------------------------------------------------------------------

INT32		CManageChkExistInterval::IsChkExistStatus(String strChkName)
{
	UINT32 nRtn = 0;

	m_tMutex.Lock();

	PMEM_CHK_EXIST_INTERVAL pdata = FindStrKeyItem(strChkName);
	if(!pdata)
	{
		m_tMutex.UnLock();
		return -1;
	}

	nRtn = pdata->nStatus;
	
	m_tMutex.UnLock();

	return nRtn;
}
//---------------------------------------------------------------------------

