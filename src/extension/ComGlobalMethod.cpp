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
#include "ComGlobalMethod.h"

//-------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------

INT32	GetUnitIDtoPolicyType(INT32 nPolicyType)
{
	INT32 nUnitID = 0;
	nUnitID = nPolicyType%1000;

	return nUnitID;
}
//---------------------------------------------------------------------------------------------------------------------

INT32	GetPoGroupIDtoPolicyType(INT32 nPolicyType)
{
	INT32 nType = nPolicyType/1000;
	nType *= 1000;
	return nType;
}
//---------------------------------------------------------------------------------------------------------------------

INT32	GetDayDiffWeek(INT32 nStWeek, INT32 nEdWeek)
{
	INT32 nCount = 0;
	INT32 nWeek = nStWeek;
	for(; nWeek != nEdWeek; nWeek++)
	{
		nWeek = nWeek % 7;
		nCount++;
	}

	return nCount;
}
//---------------------------------------------------------------------------------------------------------------------

INT32	GetHourDiffHour(INT32 nStTime, INT32 nEdTime)
{
	INT32 nCount = 0;
	INT32 nTime = nStTime;
	for(; nTime != nEdTime; nTime++)
	{
		nTime = nTime % 24;
		nCount++;
	}

	return nCount;
}
//---------------------------------------------------------------------------------------------------------------------

INT32	GetMinDiffMin(INT32 nStTime, INT32 nEdTime)
{
	INT32 nCount = 0;
	INT32 nTime = nStTime;
	for(; nTime != nEdTime; nTime++)
	{
		nTime = nTime % 60;
		nCount++;
	}

	return nCount;
}
//---------------------------------------------------------------------------------------------------------------------

INT32   GetTimeIntAddMonth(INT32 nTime, INT32 nAddMonth)
{
	struct tm *dt;
	time_t tInput = (time_t)nTime;
	dt = localtime(&tInput);

	if(nAddMonth >= 12)
		return 0;

	dt->tm_mon += nAddMonth;
	if(dt->tm_mon > 12)
	{
		dt->tm_mon = dt->tm_mon % 12;
		dt->tm_year += 1;
	}

	time_t t;
	t = mktime(dt);

	struct timeb tstruct;
	ftime(&tstruct);

	return UINT32(t + (tstruct.timezone * 60 * -1));
}
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------

String ConvertStrToInt(UINT32 nValue)
{
	String strValue;
	strValue = SPrintf("%d", nValue);

	return strValue;
}

