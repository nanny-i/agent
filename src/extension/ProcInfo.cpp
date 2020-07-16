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

// ProcInfo.cpp: implementation of the CProcInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "com_struct.h"
#include "ProcInfo.h"

#define ACCOUNT_GROUP "BUILTIN"
#define ACCOUNT_LOCAL "NT AUTHORITY"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CProcInfo::CProcInfo()
{
	memset(m_szHostName, 0, CHAR_MAX_SIZE);
}
//---------------------------------------------------------------------

CProcInfo::~CProcInfo()
{

}
//---------------------------------------------------------------------

BOOL	CProcInfo::GetProcessUserName(HANDLE hProcess, CHAR *acUserName, CHAR *acDomainName)
{
	BOOL bRet = TRUE;
	return bRet;
}
//---------------------------------------------------------------------

INT32		CProcInfo::GetProcessFullPath(DWORD dwProcessId, CHAR *acProcFullPath, INT32 nLen)
{
	return FALSE;	
}
//---------------------------------------------------------------------

void	CProcInfo::SetProcessPath(CHAR *szFileName, INT32 nLen)
{
}

//---------------------------------------------------------------------
BOOL	  CProcInfo::IsDir(CHAR *path)
{
	INT32 ret;
	struct stat stStat;
	
	ret = stat(path, &stStat);
	if (ret < 0)
		return FALSE;
	
	return S_ISDIR(stStat.st_mode);
}
//---------------------------------------------------------------------
