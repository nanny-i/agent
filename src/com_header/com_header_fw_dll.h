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



#ifndef     COM_HEADER_FW_DLL_H_152BCED9_0D66_4F66_8A87_BF47B4A5386C
#define     COM_HEADER_FW_DLL_H_152BCED9_0D66_4F66_8A87_BF47B4A5386C

//------------------------------------------------------------------------------

typedef	INT32 (*ASIFW_InitFWType)();
typedef	INT32 (*ASIFW_ClearFWType)();
typedef	INT32 (*ASIFW_AddAppType)(LPCTSTR pszTitle, LPCTSTR pszAppFullPath);
typedef	INT32 (*ASIFW_IsExistAppType)(LPCTSTR pszAppFullPath);
typedef	INT32 (*ASIFW_DelAppType)(LPCTSTR pszAppFullPath);
typedef	INT32 (*ASIFW_AddPortType)(LPCTSTR pszTitle, UINT16 nPort, UINT32 nProtocol);
typedef	INT32 (*ASIFW_IsRunFWType)();
typedef	INT32 (*ASIFW_RunFWType)();
typedef	INT32 (*ASIFW_StopFWType)();
//------------------------------------------------------------------------------


#endif      //COM_HEADER_TS_DLL_H_152BCED9_0D66_4F66_8A87_BF47B4A5386C
