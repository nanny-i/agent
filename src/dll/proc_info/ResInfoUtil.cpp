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

#include "stdafx.h"
#include "com_struct.h"
#include "RegUtil.h"
#include "TokenString.h"
#include "ResInfoUtil.h"
#include "ProcessInfo.h"
#include "ResInfo.h"
#include "NetworkInfo.h"

CResInfoUtil::CResInfoUtil()
{

}
CResInfoUtil::~CResInfoUtil()
{
}

INT32 CResInfoUtil::GetProcessResInfo(PVOID lParam, CallBack_ProcessInfo fnCallback)
{
	TListResInfoProcInfo tListProcessInfo;
	TListResInfoProcInfoItor begin, end;
	CFindProcess tFindProcess;
	INT32 nSize = 0;
	
	if(fnCallback == NULL)
		return -1;
	
	tFindProcess.GetResourceData(tListProcessInfo);

	nSize = tListProcessInfo.size();
	if (nSize == 0)
		return 0;


	begin = tListProcessInfo.begin();
	end = tListProcessInfo.end();

	for (begin; begin != end; begin++)
	{		
		fnCallback(lParam, *begin);		
	}	
	return 0;
}
//-----------------------------------------------------------------------------
INT32	CResInfoUtil::GetNetWorkResInfo(LPVOID lParam, CallBack_NetWorkInfo fnCallback)
{	
	TListResInfoNetStat	tListNetWorkInfo;
	TListResInfoNetStatItor begin, end;
	CNetWorkInfo tNetWorkInfo;
	INT32 nSize = 0;

	if(fnCallback == NULL)
		return -1;
	
	tNetWorkInfo.Get_TCPUDP_Info(tListNetWorkInfo);

	nSize = tListNetWorkInfo.size();

	if (nSize == 0)
		return 0;

	begin = tListNetWorkInfo.begin();
	end = tListNetWorkInfo.end(); 
	for(begin; begin != end; ++begin)
	{
		fnCallback(lParam, *begin);
	}

	return 0;
}
//----------------------------------------------------------------------
