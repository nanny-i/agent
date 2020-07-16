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

#ifndef MEM_SYS_DRIVE_H_4D39CDDB_CTL_E289_4d56_9F98_FE42776F4467
#define MEM_SYS_DRIVE_H_4D39CDDB_CTL_E289_4d56_9F98_FE42776F4467

typedef struct _mem_sys_drive
{
	_mem_sys_drive()
	{
		nID					= 0;
		strDriveName		= "";
	}

	UINT32			nID;	
	UINT32			nDriveType;
	String			strDriveName;
}MEM_SYS_DRIVE, *PMEM_SYS_DRIVE;

typedef list<MEM_SYS_DRIVE>				TListMemSysDriver;
typedef TListMemSysDriver::iterator		TListMemSysDriverItor;

typedef map<UINT32, MEM_SYS_DRIVE>		TMapMemSysDriver;
typedef TMapMemSysDriver::iterator		TMapMemSysDriverItor;

#endif //MEM_SYS_DRIVE_H_4D39CDDB_CTL_E289_4d56_9F98_FE42776F4467



