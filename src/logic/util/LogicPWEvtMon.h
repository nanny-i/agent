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
#pragma once


class CLogicPWEvtMon : public CLogicBase
{
public:
	INT32		ApplyPolicy();
	INT32		OnTimer_Logic();

public:	
	INT32		CheckFastBoot();
	INT32		RunBootTimeOp(UINT32 nBootType = ASI_BOOT_TYPE_NORMAL);
	INT32		ExecuteEventHandler();
	INT32		RecordTimeStamp();

	INT32		IsNotExcutePwevt();

public:
	INT32		InitEnv();
		
public:
	CLogicPWEvtMon();
    ~CLogicPWEvtMon();
};

extern CLogicPWEvtMon*		t_LogicPWEvtMon;