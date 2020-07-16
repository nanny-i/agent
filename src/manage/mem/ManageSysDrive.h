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

#ifndef ManageSysDriveH
#define ManageSysDriveH
//---------------------------------------------------------------------------

class CManageSysDrive : public CManageBase<MEM_SYS_DRIVE>
{
private:
	UINT32				m_nGlobalID;

public:
	INT32				InitSysDrive();
	INT32				AddSysDrive(MEM_SYS_DRIVE& tMSD);
	INT32				DelSysDrive(String strDriveName);
	PMEM_SYS_DRIVE		FindSysDrive(String strDriveName);

public:
	INT32				GetNetDriveMap(UINT32 nChkMode, TMapStrID& tDrvMap);
	INT32				GetFixDriveMap(UINT32 nChkMode, TMapStrID& tDrvMap);
	INT32				GetUSBDriveMap(UINT32 nChkMode, TMapStrID& tDrvMap);

public:
	INT32				IsChangeNetDrive();
	INT32				IsChangeFixDrive();

public:
	CManageSysDrive();
    ~CManageSysDrive();

};

extern CManageSysDrive	t_ManageSysDrive;

#endif
