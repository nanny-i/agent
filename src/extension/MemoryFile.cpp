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

//-----------------------------------------------------------

#include "stdafx.h"
#include "com_struct.h"
#include "MemoryFile.h"

CMemoryFile::CMemoryFile()
{
	m_hMemFile	= NULL;
	m_pMapFile	= NULL;
	ZeroMemory(&m_ST, sizeof(m_ST));

	m_nUsedMutex	= 0;
}
//-----------------------------------------------------------------------

CMemoryFile::~CMemoryFile()
{
}
//-----------------------------------------------------------------------

PVOID CMemoryFile::GetSecurityAttributes()
{	
	return NULL;
}
//-----------------------------------------------------------------------

INT32	CMemoryFile::CreateMemFile(String strFileName, UINT32 nFileSize)
{
	return 0;
}
//-----------------------------------------------------------------------

INT32	CMemoryFile::OpenMemFile(String strFileName)
{
	return 0;
}
//-----------------------------------------------------------------------

INT32	CMemoryFile::CloseMemFile()
{
	return 0;
}
//-----------------------------------------------------------------------

PVOID	CMemoryFile::MapViewFile(UINT32 nAccess)	
{
	return m_pMapFile;
}
//-----------------------------------------------------------------------

INT32	CMemoryFile::UnmapViewFile()
{
	return 0;
}
//-----------------------------------------------------------------------

INT32	CMemoryFile::SetUsedMutex(UINT32 nMode /* = 1 */)
{
	m_nUsedMutex = nMode;
	return m_nUsedMutex;
}
//-----------------------------------------------------------------------