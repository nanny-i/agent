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


#ifndef _AS_TIME_H__
#define	_AS_TIME_H__

typedef struct _TIMSTM
{
	char        chYear[4];
	char        ch4;
	char        chMonth[2];
	char        ch7;
	char        chDay[2];
	char        ch10;
	char        chHour[2];
	char        ch13;
	char        chMinute[2];
	char        ch16;
	char        chSecond[2];
	char        ch19;
	char        chMicroSecond[6];
	char        chNull;
}TIMSTM, *PTIMSTM;

#define Int32x32To64(a, b)	(((int64_t)((long)(a))) * ((int64_t)((long)(b))))
#define UInt32x32To64(a, b) (((uint64_t)((unsigned int)(a))) * ((uint64_t)((unsigned int)(b))))

static const LONGLONG SECS_BETWEEN_EPOCHS = 11644473600;
static const LONGLONG SECS_TO_100NS = 10000000; /* 10^7 */

extern void UnixTimeToFileTime(time_t* pt, LPFILETIME pft);
extern void FileTimeToUnixTime(LPFILETIME pft, time_t* pt);
extern void UnixTimeToSystemTime(time_t* pt, LPSYSTEMTIME pst);
extern void SystemTimeToUnixTime(LPSYSTEMTIME pst, time_t* pt);
extern void FileTimeToDBTime( LPFILETIME pft, PTIMSTM pts );
extern void DBTimeToFileTime( PTIMSTM pts, LPFILETIME pft );
extern void DBTimeToSystemTime(PTIMSTM pt, LPSYSTEMTIME pst);
extern void SystemTimeToDBTime(LPSYSTEMTIME pst, PTIMSTM pt);
extern void UnixTimeToDBTime(time_t* pt, PTIMSTM pst);
extern void DBTimeToUnixTime(PTIMSTM pst, time_t* pt);
extern time_t LocalTimeToGlobalTime(time_t& nTime);
extern time_t GlobalTimeToLocalTime(time_t& nTime);

extern void	GetCurrentDateTime(INT32 nDateTime, OUT LPTSTR lpBuf);
extern UINT32	GetCurrentDateTimeInt();
extern INT32 GetFileTimeInfo(LPCSTR pcPath, UINT32 *pdwCreateTime, UINT32 *pdwModifyTime, UINT32 *pdwAccessTime);
extern UINT32	GetCurrentYearMon();
extern UINT32	GetCurrentYearMon(UINT32 nTime);
extern UINT32	GetCurrentYearMonDay(UINT32 nShort = 0);
extern UINT32	GetDayOfWeek(UINT32 nTime);
extern UINT32	GetDayOfDay(UINT32 nTime);
extern UINT32	GetDayOfMonth(UINT32 nTime);
extern UINT32	GetDayDiffCurrent(UINT32 nTime);
extern LPCTSTR	GetFormatTime(UINT32 nTime, LPTSTR lpBuf, LPTSTR lpFormat = 0);
extern LPTSTR	GetDateTimeFmt(UINT32 nTime, OUT LPTSTR lpBuf, INT32 nFormat = 0);

#endif /*_AS_TIME_H__*/


