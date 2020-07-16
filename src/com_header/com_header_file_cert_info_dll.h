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



#ifndef     COM_HEADER_FILE_CERT_INFO_DLL_H_938EF200_F60B_452A_BD30_A10E8507EDCC
#define     COM_HEADER_FILE_CERT_INFO_DLL_H_938EF200_F60B_452A_BD30_A10E8507EDCC

//------------------------------------------------------------------------------

typedef struct _asi_file_cert_info
{
	CHAR	szCheckFileName[MAX_PATH];
	CHAR	szPubName[CHAR_MAX_SIZE];
	CHAR	szPubSN[MAX_PATH];
	CHAR	szCntPubName[CHAR_MAX_SIZE];
	CHAR	szCntPubSN[MAX_PATH];
	_asi_file_cert_info()
	{
		ZeroMemory(szCheckFileName, MAX_PATH);
		ZeroMemory(szPubName, CHAR_MAX_SIZE);
		ZeroMemory(szPubSN, MAX_PATH);
		ZeroMemory(szCntPubName, CHAR_MAX_SIZE);
		ZeroMemory(szCntPubSN, MAX_PATH);
	}
}ASI_FILE_CERT_INFO, *PASI_FILE_CERT_INFO;
//------------------------------------------------------------------------------


typedef	INT32 (*ASIFCI_GetFileCertInfoType)(PASI_FILE_CERT_INFO pafci, INT32 nSize);
//------------------------------------------------------------------------------


#endif      //COM_HEADER_FILE_CERT_INFO_DLL_H_938EF200_F60B_452A_BD30_A10E8507EDCC
