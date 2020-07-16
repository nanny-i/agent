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

#include "stdafx.h"
#include "com_struct.h"
#include "ManageSysDrive.h"

//---------------------------------------------------------------------------

CManageSysDrive	t_ManageSysDrive;

//---------------------------------------------------------------------------

CManageSysDrive::CManageSysDrive()
{
	m_nGlobalID = 1;
}
//---------------------------------------------------------------------------

CManageSysDrive::~CManageSysDrive()
{
	
}
//---------------------------------------------------------------------------

INT32		CManageSysDrive::InitSysDrive()
{
	{
		TMapStrID tNewDrvMap;
		GetFixDriveMap(0, tNewDrvMap);

		TMapStrIDItor begin, end;
		begin = tNewDrvMap.begin();	end = tNewDrvMap.end();
		for(begin; begin != end; begin++)
		{
			MEM_SYS_DRIVE tMSD;
			tMSD.strDriveName = begin->first;
			tMSD.nDriveType = DRIVE_FIXED;

			AddSysDrive(tMSD);
		}
	}

	{
		TMapStrID tNewDrvMap;
		GetNetDriveMap(0, tNewDrvMap);

		TMapStrIDItor begin, end;
		begin = tNewDrvMap.begin();	end = tNewDrvMap.end();
		for(begin; begin != end; begin++)
		{
			MEM_SYS_DRIVE tMSD;
			tMSD.strDriveName = begin->first;
			tMSD.nDriveType = DRIVE_REMOTE;

			AddSysDrive(tMSD);
		}
	}

	return 0;
}
//---------------------------------------------------------------------------

INT32		CManageSysDrive::AddSysDrive(MEM_SYS_DRIVE& tMSD)
{
	if(tMSD.nID == 0)	tMSD.nID = m_nGlobalID++;

	AddStrKeyID(tMSD.strDriveName, tMSD.nID);
	return AddItem(tMSD);
}
//---------------------------------------------------------------------------

INT32				CManageSysDrive::DelSysDrive(String strDriveName)
{
	UINT32 nID = FindStrKeyID(strDriveName);
	if(!nID)	return -1;

	DelStrKeyID(strDriveName);
	DeleteItem(nID);
	return 0;
}
//---------------------------------------------------------------------------

PMEM_SYS_DRIVE		CManageSysDrive::FindSysDrive(String strDriveName)
{
	return FindStrKeyItem(strDriveName);
}
//---------------------------------------------------------------------------

INT32				CManageSysDrive::GetNetDriveMap(UINT32 nChkMode, TMapStrID& tDrvMap)
{
	if(nChkMode)
	{
		TMapMemSysDriverItor begin, end;
		begin = m_tMap.begin();	end = m_tMap.end();
		for(begin; begin != end; begin++)
		{
			if(begin->second.nDriveType != DRIVE_REMOTE)	continue;

			tDrvMap[begin->second.strDriveName] = begin->first;
			//WriteLogN("net old [%s]", tDrvMap.rbegin()->first);
		}
	}
	else
	{
		String strDrvList = t_ComFuncUtil->GetNetDrvList();
		CHAR chTok = GetToken(strDrvList, ';', ',');
		CTokenString Token(strDrvList.c_str(), strDrvList.length(), chTok);
		while(Token.IsNextToken())
		{
			tDrvMap[Token.NextToken()] = 0;
			//WriteLogN("net new [%s]", tDrvMap.rbegin()->first);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32				CManageSysDrive::GetFixDriveMap(UINT32 nChkMode, TMapStrID& tDrvMap)
{
	if(nChkMode)
	{
		TMapMemSysDriverItor begin, end;
		begin = m_tMap.begin();	end = m_tMap.end();
		for(begin; begin != end; begin++)
		{
			if(begin->second.nDriveType != DRIVE_FIXED)	continue;

			tDrvMap[begin->second.strDriveName] = begin->first;
		}
	}
	else
	{
		ASIDM_INIT tADI;
		t_EnvInfoOp->GetDMInitData(tADI);

		String strDrvList = "";
		CHAR chTok = GetToken(strDrvList, ';', ',');
		CTokenString Token(strDrvList.c_str(), strDrvList.length(), chTok);
		while(Token.IsNextToken())
		{
			tDrvMap[Token.NextToken()] = 0;
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
INT32				CManageSysDrive::GetUSBDriveMap(UINT32 nChkMode, TMapStrID& tDrvMap)
{
	if(nChkMode)
	{
		TMapMemSysDriverItor begin, end;
		begin = m_tMap.begin();	end = m_tMap.end();
		for(begin; begin != end; begin++)
		{
			if(begin->second.nDriveType != DRIVE_REMOVABLE)	continue;

			tDrvMap[begin->second.strDriveName] = begin->first;
		}
	}
	else
	{
		ASIDM_INIT tADI;
		t_EnvInfoOp->GetDMInitData(tADI);

		String strDrvList = "";
		CHAR chTok = GetToken(strDrvList, ';', ',');
		CTokenString Token(strDrvList.c_str(), strDrvList.length(), chTok);
		while(Token.IsNextToken())
		{
			tDrvMap[Token.NextToken()] = 0;
		}
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32				CManageSysDrive::IsChangeNetDrive()
{
	TMapStrID tNewDrvMap, tOldDrvMap;

	GetNetDriveMap(0, tNewDrvMap);
	GetNetDriveMap(1, tOldDrvMap);

	INT32 nRtn = 0;
	{
		TMapStrIDItor begin, end;
		begin = tOldDrvMap.begin();	end = tOldDrvMap.end();
		for(begin; begin != end; begin++)
		{
			if(tNewDrvMap.find(begin->first) != tNewDrvMap.end())	continue;
			DelSysDrive(begin->first);
			nRtn = 1;
		}
	}
	{
		TMapStrIDItor begin, end;
		begin = tNewDrvMap.begin();	end = tNewDrvMap.end();
		for(begin; begin != end; begin++)
		{
			if(tOldDrvMap.find(begin->first) != tOldDrvMap.end())	continue;

			MEM_SYS_DRIVE tMSD;
			tMSD.strDriveName = begin->first;
			tMSD.nDriveType = DRIVE_REMOTE;
			AddSysDrive(tMSD);
			nRtn = 1;
		}
	}
	return nRtn;
}
//---------------------------------------------------------------------------

INT32				CManageSysDrive::IsChangeFixDrive()
{

	TMapStrID tNewDrvMap, tOldDrvMap;

	GetFixDriveMap(0, tNewDrvMap);
	GetFixDriveMap(1, tOldDrvMap);

	INT32 nRtn = 0;
	{
		TMapStrIDItor begin, end;
		begin = tOldDrvMap.begin();	end = tOldDrvMap.end();
		for(begin; begin != end; begin++)
		{
			if(tNewDrvMap.find(begin->first) != tNewDrvMap.end())	continue;
			DelSysDrive(begin->first);
			nRtn = 1;
		}
	}
	{
		TMapStrIDItor begin, end;
		begin = tNewDrvMap.begin();	end = tNewDrvMap.end();
		for(begin; begin != end; begin++)
		{
			if(tOldDrvMap.find(begin->first) != tOldDrvMap.end())	continue;

			MEM_SYS_DRIVE tMSD;
			tMSD.strDriveName = begin->first;
			tMSD.nDriveType = DRIVE_FIXED;
			AddSysDrive(tMSD);
			nRtn = 1;
		}
	}
	return nRtn;
}
//---------------------------------------------------------------------------



