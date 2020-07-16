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

// SeedUtil.h: interface for the CSeedUtil class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _SEED_UTILS_H__
#define _SEED_UTILS_H__

class CSeedUtil  
{
private:
	INT32	m_nIsInit;
	DWORD	m_pdwRoundKey[32];	

public: 
	INT32	Set_Key(BYTE* lpKey, INT32 nKeyLen = 16);
	INT32	Make_Key(BYTE* lpKey);
	INT32	Encrypt_Data(BYTE* lpData, INT32 nLen, BYTE** lpOutData, UINT32& nOutLen);
	INT32	Encrypt_Len(INT32 nLen);
	INT32	Decrypt_Data(BYTE* lpData, BYTE** lpOutData, UINT32& nOutLen);
	INT32	FreeBuffer(BYTE* lpBuffer);

public:
	CSeedUtil();
	virtual ~CSeedUtil();

};

#endif // _SEED_UTILS_H__