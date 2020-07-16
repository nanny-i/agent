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

#ifndef COM_HEADER_OTP_DLL_H_4D39CDDB_E289_4d56_9F98_FE42776F4467
#define COM_HEADER_OTP_DLL_H_4D39CDDB_E289_4d56_9F98_FE42776F4467

#pragma pack(1)
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////

typedef	INT32 (*ASIOTP_GenOtpRandomKeyType)(LPTSTR lpKey, INT32 nKeyLen);
typedef	INT32 (*ASIOTP_GenOtpValueType)(LPCTSTR lpKey, UINT32 nTimeKey, UINT32& nCode);
typedef	INT32 (*ASIOTP_ChkOtpValueType)(LPCTSTR lpKey, UINT32 nTimeKey, UINT32 nCode, INT32 nTimeArea);
typedef	INT32 (*ASIOTP_GenOtpQRCodeType)(LPCTSTR lpKey, LPCTSTR lpName, LPCTSTR lpEmail, PBYTE* pQRCode, INT32& nQRSize);
typedef	INT32 (*ASIOTP_FreeBufferType)(PBYTE* pQRCode);
//--------------------------------------------------------------------------

#pragma pack()

#endif //COM_HEADER_NET_DLL_H_4D39CDDB_E289_4d56_9F98_FE42776F4467



