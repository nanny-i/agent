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

// ValidTimeUtil.h: interface for the CValidTimeUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VALIDTIMEUTIL_H__7CA430D1_302A_4318_9017_7F8963AA8BBD__INCLUDED_)
#define AFX_VALIDTIMEUTIL_H__7CA430D1_302A_4318_9017_7F8963AA8BBD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CValidTimeUtil  
{
private:
	DWORD		m_nValidTickCnt;
	UINT32		m_nValidTime;

public:
	void		InitValidTime(UINT32 nCurTime);
	UINT32		GetValidTime();

public:
	CValidTimeUtil();
	virtual ~CValidTimeUtil();

};

extern CValidTimeUtil* t_ValidTimeUtil;

#endif // !defined(AFX_VALIDTIMEUTIL_H__7CA430D1_302A_4318_9017_7F8963AA8BBD__INCLUDED_)
