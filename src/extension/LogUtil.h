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


#ifndef ASI_SDK_LV01_GLB_FN_LOG_H_15BE18C4_D543_413E_96F8_61C24AD45985
#define	ASI_SDK_LV01_GLB_FN_LOG_H_15BE18C4_D543_413E_96F8_61C24AD45985

#define ASI_SDK_LOG_KEY_TYPE_SSA20_PKG			1541428297

void	WriteLogN(char* fmt,...);
void	WriteLogE(char* fmt,...);
//void	WriteLogN(UINT32 nID,...);
//void	WriteLogE(UINT32 nID,...);
void    WriteLogN_Size(UINT32 nSize, LPCTSTR lpFileName, char* fmt,...);
void	SetLogFileInfo(LPSTR lpLogPath, LPSTR lpLogName, INT32 nRmLog = 1);

void	Encrypt_Log(UINT32	key, PBYTE SrcData,	INT32 SrcLen);
void	Decript_Log(UINT32	key, PBYTE SrcData,	INT32 SrcLen);
void	WriteLog_Enc(LPTSTR lpLog, FILE* fp);
void	SetLogSKey(UINT32 nSKey);

#endif