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

#include "stdafx.h"
#include "as_sha1.h"
#include "as_sha256.h"
#include "as_file.h"
#include "as_hash.h"

//-----------------------------------------------------------------
INT32 SHAString(INT32 nLenType, LPCSTR lpString, INT32 nInLen, LPTSTR lpBuffer, INT32 nOutLen)
{
	INT32 nRetVal = 0;
	if(lpString == NULL || nInLen < 1 || lpBuffer == NULL || nOutLen < 1)
	{
		return -1;
	}

	if(nLenType == ASIHASH_SHA_LEN_TYPE_128)
	{
		get_sha1_hash((char *)lpString, nInLen, lpBuffer, nOutLen);
	}
	else if(nLenType == ASIHASH_SHA_LEN_TYPE_256)
	{
		nRetVal = get_sha256_hash((char *)lpString, nInLen, lpBuffer, nOutLen);
	}
	return nRetVal;
}
//-----------------------------------------------------------------

INT32 SHAByte(INT32 nLenType, LPCSTR lpString, INT32 nInLen, BYTE* lpBuffer, INT32 nOutLen)
{
	INT32 nRetVal = 0;
	if(lpString == NULL || nInLen < 1 || lpBuffer == NULL || nOutLen < 1)
	{
		return -1;
	}

	if(nLenType == ASIHASH_SHA_LEN_TYPE_128)
	{
		nRetVal = get_sha1_digest((char *)lpString, nInLen, lpBuffer, nOutLen);
	}
	else if(nLenType == ASIHASH_SHA_LEN_TYPE_256)
	{
		nRetVal = get_sha256_digest((char *)lpString, nInLen, lpBuffer, nOutLen);
	}

	return nRetVal;
}
//-----------------------------------------------------------------

INT32 	SHAFileLen(INT32 nLenType, LPCSTR lpFileName)
{
	INT32 nFileSize = 0;
	if(lpFileName == NULL)
		return 0;
	if(get_file_size(lpFileName, (UINT32 *)&nFileSize) != 0)
		return 0;

	return nFileSize;
}
//-----------------------------------------------------------------

INT32 	SHAFile(INT32 nLenType, LPCSTR lpFileName, LPTSTR lpBuffer, INT32 nOutLen)
{
	INT32 nRetVal = 0;

	if(lpFileName == NULL || lpBuffer == NULL || nOutLen < 1)
	{
		return -1;
	}

	if(nLenType == ASIHASH_SHA_LEN_TYPE_128)
	{
		nRetVal = get_sha1_hash_from_file((char *)lpFileName, lpBuffer, nOutLen);
	}
	else if(nLenType == ASIHASH_SHA_LEN_TYPE_256)
	{
		nRetVal = get_sha256_hash_from_file((char *)lpFileName, lpBuffer, nOutLen);
	}
	return nRetVal;
}

