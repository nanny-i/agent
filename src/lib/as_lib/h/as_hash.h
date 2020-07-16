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

#ifndef _AS_HASH_H_
#define _AS_HASH_H_

#define ASIHASH_SHA_LEN_TYPE_128		0
#define ASIHASH_SHA_LEN_TYPE_256		1

#define ASIHASH_SHA_TYPE_128_LEN		40
#define ASIHASH_SHA_TYPE_256_LEN		64

extern INT32 SHAString(INT32 nLenType, LPCSTR lpString, INT32 nInLen, LPTSTR lpBuffer, INT32 nOutLen);
extern INT32 SHAByte(INT32 nLenType, LPCSTR lpString, INT32 nInLen, BYTE* lpBuffer, INT32 nOutLen);
extern INT32 SHAFileLen(INT32 nLenType, LPCSTR lpFileName);
extern INT32 SHAFile(INT32 nLenType, LPCSTR lpFileName, LPTSTR lpBuffer, INT32 nOutLen);

#endif /* _AS_HASH_H_ */


