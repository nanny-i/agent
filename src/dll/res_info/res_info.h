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

#ifndef _RES_INFO_H__
#define _RES_INFO_H__

extern "C" {

INT32 GetCpuUsageTotal(UINT32* nUsage);
INT32 GetMemoryInfo(UINT64* nTotalPhySize, UINT64* nTotalPageSize, UINT64* nAvailPhySize, UINT64* nAvailPageSize);
INT32 GetHddInfo(UINT64* nTotalHddSize, UINT64* nUsageHddSize, LPCTSTR lpDriveName);
INT32 GetTrafficBandWidht(INT32 nItemID, DOUBLE* dBandWidth);
INT32 GetTrafficValue(INT32 nItemID, DOUBLE* dTrafficValue);

}

#endif /*_RES_INFO_H__*/