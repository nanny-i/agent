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
#include "LogicMgrPoFaInotifyFile.h"
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

CLogicMgrPoFaInotifyFile*		t_LogicMgrPoFaInotifyFile = NULL;

CLogicMgrPoFaInotifyFile::CLogicMgrPoFaInotifyFile()
{
	t_ManagePoFaInotifyFile	= new CManagePoFaInotifyFile();
	if(t_ManagePoFaInotifyFile)
		t_ManagePoFaInotifyFile->LoadDBMS();
	m_strLogicName		= "mgr po fa inotify file";
}
//---------------------------------------------------------------------------

CLogicMgrPoFaInotifyFile::~CLogicMgrPoFaInotifyFile()
{
	SAFE_DELETE(t_ManagePoFaInotifyFile);
}

INT32		CLogicMgrPoFaInotifyFile::GetAllInotifyPath(PNOTIFY_PATH pNotifyPath, INT32 nCount)
{
	INT32 nRetVal = 0;
	if(t_ManagePoFaInotifyFile == NULL || pNotifyPath == NULL || nCount < 1)
	{
		WriteLogE("[%s] invalid input data", m_strLogicName.c_str());
		return -1;
	}
	nRetVal = t_ManagePoFaInotifyFile->GetAllInotifyPath(pNotifyPath, nCount);
	if(nRetVal != 0)
	{
		WriteLogE("[%s] fail to get all inotify file path (%d)", m_strLogicName.c_str(), nRetVal);
		nRetVal -= 100;
	}
	return nRetVal;
}

INT32		CLogicMgrPoFaInotifyFile::InsertInotifyPath(PNOTIFY_PATH pNotifyPath)
{
	INT32 nRetVal = 0;
	if(t_ManagePoFaInotifyFile == NULL || pNotifyPath == NULL)
	{
		WriteLogE("[%s] invalid input data", m_strLogicName.c_str());
		return -1;
	}

	nRetVal = t_ManagePoFaInotifyFile->InsertInotifyPath(pNotifyPath);
	if(nRetVal != 0)
	{
		WriteLogE("[%s] fail to insert inotify file path (%d)", m_strLogicName.c_str(), nRetVal);
		nRetVal -= 100;
	}
	return nRetVal;
}

INT32		CLogicMgrPoFaInotifyFile::DeleteInotifyPath(PNOTIFY_PATH pNotifyPath)
{
	INT32 nRetVal = 0;
	if(t_ManagePoFaInotifyFile == NULL || pNotifyPath == NULL)
	{
		WriteLogE("[%s] invalid input data", m_strLogicName.c_str());
		return -1;
	}

	nRetVal = t_ManagePoFaInotifyFile->DeleteInotifyPath(pNotifyPath);
	if(nRetVal != 0)
	{
		nRetVal -= 100;
	}
	return nRetVal;
}

INT32		CLogicMgrPoFaInotifyFile::GetInotifyPathCount()
{
	if(t_ManagePoFaInotifyFile == NULL)
	{
		return 0;
	}

	return t_ManagePoFaInotifyFile->GetInotifyPathCount();
}


VOID		CLogicMgrPoFaInotifyFile::DelAllInotifyPath(PNOTIFY_PATH pNotifyPath, INT32 nCount)
{
	if(t_ManagePoFaInotifyFile != NULL)
	{
		t_ManagePoFaInotifyFile->DelAllInotifyPath(pNotifyPath, nCount);
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
