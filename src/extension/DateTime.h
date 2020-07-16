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

#ifndef _DATETIME_H_
#define _DATETIME_H_

#include <time.h>

class CTime
{
private:
	enum TimeStatus
	{
		error = -1,
		valid = 0,
		invalid = 1,    // Invalid date (out of range, etc.)
		null = 2,       // Literally has no value
	};

	time_t m_dt;
	TimeStatus m_status;

public:
	CTime(void);
	CTime(time_t tTime);
	~CTime(void);

	int GetYear(void);
	int GetMonth(void);
	int GetDay(void);
	int GetHour(void);
	int GetMinute(void);
	int GetSecond(void);
	int GetDayOfWeek(void);
	int GetDayOfYear(void);
};


#endif


