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

// ValidTimeUtil.cpp: implementation of the CValidTimeUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "com_struct.h"
#include "ValidTimeUtil.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CValidTimeUtil* t_ValidTimeUtil;

CValidTimeUtil::CValidTimeUtil()
{
	m_nValidTime = 0;
	m_nValidTickCnt = 0;
}
//---------------------------------------------------------------------

CValidTimeUtil::~CValidTimeUtil()
{
	m_nValidTime = 0;
	m_nValidTickCnt = 0;
}
//---------------------------------------------------------------------

void		CValidTimeUtil::InitValidTime(UINT32 nCurTime)
{
	m_nValidTime = nCurTime;
	m_nValidTickCnt = GetTickCount();
	return;
}
//---------------------------------------------------------------------

UINT32		CValidTimeUtil::GetValidTime()
{
	UINT32 nRtnTime = 0;

	if(m_nValidTime)
	{
		nRtnTime = m_nValidTime + ((GetTickCount() - m_nValidTickCnt) / 1000);
	}
	else
	{
		nRtnTime = GetCurrentDateTimeInt();
	}
	return nRtnTime;
}
//---------------------------------------------------------------------
