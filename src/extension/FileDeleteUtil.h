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

#ifndef _FILE_DELETE_UTIL_H__

#define _FILE_DELETE_UTIL_H__


#include "SecureDeleteUtil.h"

#define SECURE_DEL_BUF_SIZE (1024)

class CFileDeleteUtil : public CUtilBase
{
public:
	CFileDeleteUtil(void);
	~CFileDeleteUtil(void);

public:
	void		SetDeleteMethod(UINT32 nMethod=0);
	INT32 		SecureDeleteFile(LPCSTR szPath, UINT32 nDelMethod, DWORD dwOverwriteCount=3, BOOL bReadOnlyDelete=TRUE, BOOL bWait=TRUE, UINT32 nLimitMByteByte=0, UINT32 nLimitDelCnt=0);

private:
	INT32 		ZeroFile(LPCSTR szPath, DWORD dwOverwriteCount);

	UINT32		m_nDelMethod;
	CSecureDeleteUtil*		t_WipeUtil;
};

extern CFileDeleteUtil*		t_FileDeleteUtil;

#endif /*_FILE_DELETE_UTIL_H__*/