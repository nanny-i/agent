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

//---------------------------------------------------------------------------

#ifndef _ENCODE_UTIL_H__
#define _ENCODE_UTIL_H__
//---------------------------------------------------------------------------

class CEncodeUtil
{

public:
	String		EncBase(PBYTE pValue, INT32 nValLen);
	void		DecBase(String strValue, PBYTE pValue, INT32& nValLen);
	UINT32		EncBase_U32(UINT32	nValue);
	UINT32		DecBase_U32(UINT32	nValue);

public:
	CEncodeUtil();
    ~CEncodeUtil();
};

#endif /*_ENCODE_UTIL_H__*/