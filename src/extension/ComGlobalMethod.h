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

#ifndef COM_GLOBAL_METHOD_H_15BE18C4_D543_413E_96F8_61C24AD45984
#define COM_GLOBAL_METHOD_H_15BE18C4_D543_413E_96F8_61C24AD45984

INT32	GetUnitIDtoPolicyType(INT32 nPolicyType);
INT32	GetPoGroupIDtoPolicyType(INT32 nPolicyType);

INT32	GetDayDiffWeek(INT32 nStWeek, INT32 nEdWeek);
INT32	GetHourDiffHour(INT32 nStTime, INT32 nEdTime);
INT32	GetMinDiffMin(INT32 nStTime, INT32 nEdTime);
INT32   GetTimeIntAddMonth(INT32 nTime, INT32 nAddMonth);

#endif //COM_GLOBAL_METHOD_H_15BE18C4_D543_413E_96F8_61C24AD45984