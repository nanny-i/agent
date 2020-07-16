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

INT32 InitProcInfo(PVOID* lpObject);
INT32 FreeProcInfo(PVOID lpObject);
INT32 GetProcessResInfo(PVOID lpObject, LPVOID lParam, CallBack_ProcessInfo fnCallback);
INT32 GetNetWorkResInfo(PVOID lpObject, LPVOID lParam, CallBack_NetWorkInfo fnCallback);
}
#endif