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



#ifndef     COM_HEADER_WENG_DLL_H_152BCED9_0D66_4F66_8A87_BF47B4A5386C
#define     COM_HEADER_WENG_DLL_H_152BCED9_0D66_4F66_8A87_BF47B4A5386C

//------------------------------------------------------------------------------

#define		ETC_LENGTH			64
#define		HASH_PADDING_LEN	8
#define		SHA512_BLOCK_SIZE	128
//------------------------------------------------------------------------------

#define		WE_WHITE_FILE				0x0000
#define		WE_NORMAL_FILE				0x0001
#define		WE_WINDOW_FILE				0x0002
#define		WE_INVALID_FILE				0x0004
//------------------------------------------------------------------------------

#define		WE_LOCAL_WHITE			1
#define		WE_GLOBAL_WHITE			2
#define		WE_GLOBAL_BLACK			4
//------------------------------------------------------------------------------

typedef struct _asi_weng_version_info
{
	_asi_weng_version_info()
	{
		wVer0		= 0;
		wVer1		= 0;
		wVer2		= 0;
		wVer3		= 0;
	}
	WORD wVer0;
	WORD wVer1;
	WORD wVer2;
	WORD wVer3;
}ASI_WENG_VERSION_INFO, *PASI_WENG_VERSION_INFO;

typedef struct _asi_weng_wl_signiture_ex
{
	_asi_weng_wl_signiture_ex()
	{
		dwFileSize		= 0;
		dwMasic			= 0;
		dwCreateTime	= 0;
		dwAccessTime	= 0;
		dwWriteTime		= 0;

		ZeroMemory(acFileName,	ETC_LENGTH);
		ZeroMemory(acDbName,	ETC_LENGTH);
		ZeroMemory(acFileHash,	SHA512_BLOCK_SIZE+HASH_PADDING_LEN);
		ZeroMemory(acFilePath,	MAX_PATH);
	}
	DWORD					dwFileSize;
	DWORD					dwMasic;
	DWORD					dwCreateTime;
	DWORD					dwAccessTime;
	DWORD					dwWriteTime;
	ASI_WENG_VERSION_INFO	stVersionInfo;
	CHAR acFileName[ETC_LENGTH];
	CHAR acDbName[ETC_LENGTH];
	CHAR acFileHash[SHA512_BLOCK_SIZE+HASH_PADDING_LEN];
	CHAR acFilePath[MAX_PATH];
} ASI_WENG_WL_SIGNITURE_EX, *PASI_WENG_WL_SIGNITURE_EX;

typedef struct _asi_weng_wl_ex
{
	DWORD dwCategory;				//4
	DWORD dwFileSize;				//8
	DWORD dwMasic;					//12
	DWORD dwResponse;				//16
	DWORD dwRole;					//20
	DWORD dwCreateTime;				//24
	DWORD dwAccessTime;				//28
	DWORD dwWriteTime;				//32
	DWORD dwFileVersionLS;
	DWORD dwFileVersionMS;
	char acTagName[ETC_LENGTH];		//104
	char acProductName[ETC_LENGTH];	//168
	char acCompanyName[ETC_LENGTH];	//232
	char acDescName[ETC_LENGTH];	//296
	char acSignCompanyName[ETC_LENGTH];	//360
	char acWhiteHash[SHA512_BLOCK_SIZE+HASH_PADDING_LEN];	//496
	char acFilePath[MAX_PATH];	//756
	char acDbName[ETC_LENGTH];	//820
} ASI_WENG_WL_EX, *PASI_WENG_WL_EX;

typedef list<ASI_WENG_WL_EX>				TListWEngWLEx;
typedef TListWEngWLEx::iterator				TListWEngWLExItor;
typedef TListWEngWLEx::reverse_iterator		TListWEngWLExRItor;

typedef map<String, ASI_WENG_WL_EX>		TMapWEngWLEx;
typedef TMapWEngWLEx::iterator				TMapWEngWLExItor;
typedef TMapWEngWLEx::reverse_iterator		TMapWEngWLExRItor;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

typedef	INT32	(*ASIWENG_InitType)(PVOID* lpObject);
typedef	INT32	(*ASIWENG_FreeType)(PVOID lpObject);

typedef	INT32	(*ASIWENG_ScanFileType)(PVOID lpObject, char *szPath, PASI_WENG_WL_SIGNITURE_EX pOldWhiteList, PDWORD pdwFileType, char *acLogMsg);
typedef	INT32	(*ASIWENG_InitDBType)(PVOID lpObject, char *acLogMsg);
typedef	INT32	(*ASIWENG_LoadDBType)(PVOID lpObject, char *acEnginePath, char *acLogMsg);
typedef	INT32	(*ASIWENG_CreateDBType)(PVOID lpObject, char *acWhitePath, char *acEnginePath, char *acDbName, char *acLogMsg);
typedef	INT32	(*ASIWENG_AddFileType)(PVOID lpObject, char *szPath, char *acLogMsg);
typedef	INT32	(*ASIWENG_DelFileType)(PVOID lpObject, char *szPath, char *acLogMsg);
typedef	INT32	(*ASIWENG_ClearFileType)(PVOID lpObject);
typedef	INT32	(*ASIWENG_MakeDBType)(PVOID lpObject, char *acEnginePath, char *acDbName, char *acLogMsg);
typedef	INT32	(*ASIWENG_UnInitDBType)(PVOID lpObject);
typedef	INT32	(*ASIWENG_AddWLType)(PVOID lpObject, char *szPath, PVOID pWhiteList, DWORD dwListSize, char *acLogMsg);
typedef	INT32	(*ASIWENG_ModWLType)(PVOID lpObject, PVOID pWhiteList, DWORD dwListSize, char *acLogMsg);
typedef	INT32	(*ASIWENG_DelWLType)(PVOID lpObject, char *szPath,  PVOID pWhiteList, DWORD dwListSize, char *acLogMsg);
typedef	INT32	(*ASIWENG_GetWLType)(PVOID lpObject, char *szPath, PVOID pWhiteList, DWORD dwListSize, PDWORD pdwWFileType, char *acLogMsg);
typedef	INT32	(*ASIWENG_GetWLCntType)(PVOID lpObject, PVOID pPasrseData, DWORD dwDataSize, DWORD *pdwCount, char *acLogMsg);
typedef	INT32	(*ASIWENG_GetAllWLType)(PVOID lpObject, PVOID pPasrseData, DWORD dwDataSize, DWORD dwTotalCount, PVOID pWhiteList, DWORD dwListSize, char *acLogMsg);
typedef	INT32	(*ASIWENG_GetWLDBCntType)(PVOID lpObject, char *szEnginePath, DWORD *pdwFileCount, char *acLogMsg);
typedef	INT32	(*ASIWENG_GetAllWLDBHdrType)(PVOID lpObject, char *szEnginePath, DWORD dwFileCount, PVOID pWhiteHdr, DWORD dwHdrSize, char *acLogMsg);
typedef	INT32	(*ASIWENG_GetWLDBHdrType)(PVOID lpObject, char *acEngineFile, PVOID pWhiteHdr, DWORD dwHdrSize, char *acLogMsg);
typedef	INT32	(*ASIWENG_MakeWLDBType)(PVOID lpObject, char *szEngineFile, DWORD dwCategory, PVOID pPasrseData, DWORD dwDataSize, DWORD *pdwCount, char *acLogMsg);
typedef	INT32	(*ASIWENG_LoadWLType)(PVOID lpObject, char *szEngineFile, PVOID pPasrseData, DWORD dwDataSize, DWORD *pdwCount, char *acLogMsg);

//--------------------------------------------------------------------------
//--------------------------------------------------------------------------


#endif      //COM_HEADER_WENG_DLL_H_152BCED9_0D66_4F66_8A87_BF47B4A5386C
