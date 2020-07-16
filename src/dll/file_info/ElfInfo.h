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

#ifndef _ELF_INFO_H__
#define _ELF_INFO_H__


#include <elf.h>

//=============================================================================
class CELFInfo
//=============================================================================
{
// Construction
public:
	CELFInfo(char *pcFile = NULL);
	virtual ~CELFInfo();

// Attributes
public:
	INT32	GetFileElfType();
	INT32 	GetMachineType();
	VOID	GetFileElfTypeString(char *pcElfType, INT32 nLength);
	VOID	GetFileElfAbiString(char *pcElfAbi, INT32 nLength);
	VOID	GetFileElfEntryPointString(char *pcEntryPoint, INT32 nLength);
	BOOL	Is64Bit();
	void	Close();
	BOOL	Open(char *pcFile);
protected:
	BOOL	IsOpen()	{ return m_nFd != -1; }
	BOOL	IsELF();
	BOOL	IsELF64();
	INT32	ReadElfHdr();
	INT32	ReadElfHdr64();
	

protected:
	INT32		m_nFd;
	INT32		m_nElfClass;
	Elf32_Ehdr 	m_stElfHeader;
	Elf64_Ehdr	m_stElfHeader64;
};

#endif //_ELF_INFO_H__
