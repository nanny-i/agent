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


#ifndef COM_HEADER_HOOK_EXIT_WIN_DLL_H_152BCED9_0D66_4F66_8A87_BF47B4A5386C
#define COM_HEADER_HOOK_EXIT_WIN_DLL_H_152BCED9_0D66_4F66_8A87_BF47B4A5386C
//--------------------------------------------------------------------------

#define ASI_HK_NAME_GLOBAL		"Global\\"
#define ASI_HK_NAME_EXITWIN		"ASI_HK_NAME_EXITWIN"

//--------------------------------------------------------------------------

#define ASI_HK_EXIT_WIN_CHK_TYPE_NONE			0x00000000
#define ASI_HK_EXIT_WIN_CHK_TYPE_WAIT			0x00000001
#define ASI_HK_EXIT_WIN_CHK_TYPE_DONE			0x00000002
#define ASI_HK_EXIT_WIN_CHK_TYPE_SKIP			0x00000004

//--------------------------------------------------------------------------

#define ASI_HK_EXIT_WIN_RTN_TYPE_NONE			0
#define ASI_HK_EXIT_WIN_RTN_TYPE_ALLOW			1
#define ASI_HK_EXIT_WIN_RTN_TYPE_DENY			2

//--------------------------------------------------------------------------

typedef struct _asi_hk_exit_win
{
	_asi_hk_exit_win()
	{
		nChkFlag	= 0;

		nFlags		= 0;
		dwReason	= 0;
		nChkRtn		= 0;

		nFileOp		= 0;
		nSearchTotal	= 0;
		nSearchEnd		= 0;
		nFindFileTotal	= 0;
		nFindFileEnd	= 0;
		memset(szFilePath, 0, MAX_PATH);
		memset(szFileName, 0, MAX_PATH);
	}
	UINT32	nChkFlag;

	UINT32 	nFlags;
	DWORD 	dwReason;
	UINT32	nChkRtn;

	UINT32	nFileOp;
	UINT32	nSearchTotal;
	UINT32	nSearchEnd;
	UINT32	nFindFileTotal;
	UINT32	nFindFileEnd;
	CHAR	szFilePath[MAX_PATH];
	CHAR	szFileName[MAX_PATH];
}ASI_HK_EXIT_WIN, *PASI_HK_EXIT_WIN;

//--------------------------------------------------------------------------

#endif      //COM_HEADER_HOOK_EXIT_WIN_DLL_H_152BCED9_0D66_4F66_8A87_BF47B4A5386C
