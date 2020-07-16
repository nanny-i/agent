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

#ifndef _AS_WHITE_LIST_DEF__

#define _AS_WHITE_LIST_DEF__

#include <windows.h>

#define AS_NAME_MAX			32
#define AS_ETC_NAME_MAX		64
#define AS_HASH_PADDING		8
#define AS_SEC_NAME_MAX		16
#define AS_SEC_DATA_MAX		1024
#define AS_PATH_NAME_MAX	511
#define AS_DESC_NAME_MAX	255

#define AS_WHITE_FILE		0x0000
#define AS_NORMAL_FILE		0x0001
#define	AS_BLACK_FILE		0x0002
#define AS_INVALID_FILE		0x0004

#define AS_TEMP_WHITE	0
#define AS_LOCAL_WHITE	1
#define AS_GLOBAL_WHITE	2
#define AS_GLOBAL_BLACK	3

#define AS_GATEGORY_MAX 4

#define SHA256_BLOCK_SIZE   64

typedef unsigned __int64 DDWORD;

typedef struct _asi_min_white_list
{
	char acWhiteHash[SHA256_BLOCK_SIZE+AS_HASH_PADDING];
	char acFileHash[SHA256_BLOCK_SIZE+AS_HASH_PADDING];
} asi_min_white_list;

typedef struct _asi_mid_white_list
{
	asi_min_white_list stMinWhite;
	DDWORD ddwRole;
	DWORD dwMagic;
	DWORD dwFileSize;
	char acFileName[AS_NAME_MAX];
} asi_mid_white_list;

typedef struct _asi_max_white_list
{
	asi_mid_white_list stMidWhite;
	DDWORD ddwCreateTime;
	DDWORD ddwAccessTime;
	DDWORD ddwWriteTime;
	DDWORD ddwFileVersion;
	char acTagName[AS_NAME_MAX];
	char acProductName[AS_ETC_NAME_MAX];
	char acCompanyName[AS_ETC_NAME_MAX];
	char acDescName[AS_ETC_NAME_MAX];
	char acSignCompanyName[AS_ETC_NAME_MAX];
	char acFilePath[AS_PATH_NAME_MAX+1];
} asi_max_white_list;



typedef struct _WHITE_LIST_EX
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
	char acTagName[AS_ETC_NAME_MAX];		//104
	char acProductName[AS_ETC_NAME_MAX];	//168
	char acCompanyName[AS_ETC_NAME_MAX];	//232
	char acDescName[AS_ETC_NAME_MAX];	//296
	char acSignCompanyName[AS_ETC_NAME_MAX];	//360
	char acWhiteHash[SHA256_BLOCK_SIZE+AS_HASH_PADDING];	//496
	char acFilePath[MAX_PATH];	//756
	char acDbName[AS_ETC_NAME_MAX];	//820
} WHITE_LIST_EX, *PWHITE_LIST_EX;

typedef struct _WHITE_FILE_HDR
{
	DWORD dwCategory;				//4
	DWORD dwCreateTime;				//8
	DWORD dwWriteTime;				//12
	DWORD dwFileVersionLS;			//16
	DWORD dwFileVersionMS;			//20
	DWORD dwSdkVersionLS;			//24
	DWORD dwSdkVersionMS;			//28
	DWORD dwListSize;				//32
	char acDbName[AS_ETC_NAME_MAX];		//96
} WHITE_FILE_HDR, *PWHITE_FILE_HDR;

typedef struct _WHITE_PARSE_DATA
{
	DWORD dwParseFlag;
	DWORD dwCategory;
	DWORD dwMasic;
	char acTagRule[AS_DESC_NAME_MAX+1];
	char acProductRule[AS_DESC_NAME_MAX+1];
	char acCompanyRule[AS_DESC_NAME_MAX+1];
	char acSignCompanyRule[AS_DESC_NAME_MAX+1];
	char acWdbRule[AS_DESC_NAME_MAX+1];
	char acPathRule[AS_PATH_NAME_MAX+1];
} WHITE_PARSE_DATA, *PWHITE_PARSE_DATA;

typedef struct _PARSE_RULE_NAME
{
	char acName[AS_ETC_NAME_MAX];
} PARSE_RULE_NAME, *PPARSE_RULE_NAME;

typedef struct _PARSE_RULE_PATH {
	DWORD dwWildType;				/* WILDTYPE_xxx */
	DWORD dwWildLen;				/* WILDCARD 사용 문자열 길이 */
	char acWildStr[AS_NAME_MAX];/* wildcard 사용 문자열 (wildcard 제외) */
	char acDirPath[AS_PATH_NAME_MAX+1];	
} PARSE_RULE_PATH, *PPARSE_RULE_PATH;

typedef struct _WHITE_PARSE_RULE
{
	DWORD dwParseFlag;
	DWORD dwCategory;
	DWORD dwMasic;
	DWORD dwTagCount;
	DWORD dwProductCount;
	DWORD dwComapanyCount;
	DWORD dwSignCount;
	DWORD dwWdbCount;
	DWORD dwPathCount;
	PPARSE_RULE_NAME pTagRule;
	PPARSE_RULE_NAME pProductRule;
	PPARSE_RULE_NAME pCompanyRule;
	PPARSE_RULE_NAME pSignRule;
	PPARSE_RULE_NAME pWdbRule;
	PPARSE_RULE_PATH pPathRule;
} WHITE_PARSE_RULE, *PWHITE_PARSE_RULE;

#endif /* _AS_WHITE_LIST_DEF__ */