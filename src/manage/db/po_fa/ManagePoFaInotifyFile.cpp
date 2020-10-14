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
#include "ManagePoFaInotifyFile.h"

//---------------------------------------------------------------------------

CManagePoFaInotifyFile*	t_ManagePoFaInotifyFile = NULL;


//---------------------------------------------------------------------------

CManagePoFaInotifyFile::CManagePoFaInotifyFile()
{
	t_DBMgrPoFaInotifyFile	= new CDBMgrPoFaInotifyFile();
}
//---------------------------------------------------------------------------

CManagePoFaInotifyFile::~CManagePoFaInotifyFile()
{
	if(t_DBMgrPoFaInotifyFile)
	{
		delete t_DBMgrPoFaInotifyFile;
		t_DBMgrPoFaInotifyFile = NULL;
	}
}
//---------------------------------------------------------------------------

INT32		CManagePoFaInotifyFile::LoadDBMS()
{
	TListLogNotifyFile tDBLogNotifyFileList;
    TListLogNotifyFileItor begin, end;

	if(t_DBMgrPoFaInotifyFile == NULL)
	{
		return -1;
	}
	if(SetER(t_DBMgrPoFaInotifyFile->LoadExecute(&tDBLogNotifyFileList)))
    {
    	return g_nErrRtn;
    }

    begin = tDBLogNotifyFileList.begin();	end = tDBLogNotifyFileList.end();
    for(begin; begin != end; begin++)
    {
    	AddItem(begin->nID, *begin);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32	CManagePoFaInotifyFile::GetInotifyPathCount()
{
	return (INT32)m_tMap.size();
}

INT32		CManagePoFaInotifyFile::FindID(char *pPath)
{
	TListLogNotifyFile tDBLogNotifyFileList;
	TListLogNotifyFileItor begin, end;

	if(pPath == NULL)
		return -1;

	begin = tDBLogNotifyFileList.begin();	end = tDBLogNotifyFileList.end();
	for(begin; begin != end; begin++)
	{
		if(!_stricmp(begin->strNotifyFilePath.c_str(), pPath))
			return begin->nID;
	}
	return -2;
}

INT32	CManagePoFaInotifyFile::DeleteInotifyPath(PNOTIFY_PATH pNotifyPath)
{
	INT32 nRetVal = 0;
	INT32 nID = 0;
	if(t_DBMgrPoFaInotifyFile == NULL || pNotifyPath == NULL)
		return -1;

	nID = FindID(pNotifyPath->acNotifyPath);
	if(nID < 0)
		return -2;

	nRetVal = t_DBMgrPoFaClear->DeleteExecute(nID);
	if(nRetVal != 0)
	{
		nRetVal -= 10;
		return nRetVal;
	}

	nRetVal = DeleteItem(nID);
	if(nRetVal != 0)
	{
		nRetVal -= 20;
		return nRetVal;
	}
	return 0;
}

INT32	CManagePoFaInotifyFile::InsertInotifyPath(PNOTIFY_PATH pNotifyPath)
{
	INT32 nRetVal = 0;
	INT32 nID = 0;
	DB_LOG_NOTIFY_FILE stLogNotify;
	if(t_DBMgrPoFaInotifyFile == NULL || pNotifyPath == NULL)
		return -1;

	memset(&stLogNotify, 0, sizeof(stLogNotify));

	stLogNotify.nUsedFlag = 1;
	stLogNotify.nRegDate = GetCurrentDateTimeInt();
	stLogNotify.nOrderID = pNotifyPath->nOrderID;
	stLogNotify.strNotifyFilePath = SPrintf(pNotifyPath->acNotifyPath);

	nRetVal = t_DBMgrPoFaInotifyFile->InsertExecute((PVOID)&stLogNotify);
	if(nRetVal != 0)
	{
		WriteLogE("fail to insert inotify path %s (%d)", stLogNotify.strNotifyFilePath.c_str(), nRetVal);
		nRetVal -= 10;
	}
	nRetVal = AddItem(stLogNotify.nID, stLogNotify);
	if(nRetVal != 0)
	{
		WriteLogE("fail to add item inotify path %s (%d)", stLogNotify.strNotifyFilePath.c_str(), nRetVal);
		nRetVal -= 20;
	}
	nID = FindID((char *)stLogNotify.strNotifyFilePath.c_str());
	if(nID < 0)
	{
		WriteLogE("fail to find item inotify path %s (%d)", stLogNotify.strNotifyFilePath.c_str(), nRetVal);
		nRetVal -= 30;
	}
	nRetVal = DeleteItem(nID);
	if(nRetVal != 0)
	{
		nRetVal -= 40;
		return nRetVal;
	}
	nRetVal = AddItem(stLogNotify.nID, stLogNotify);
	if(nRetVal != 0)
	{
		WriteLogE("fail to add item inotify path %s (%d)", stLogNotify.strNotifyFilePath.c_str(), nRetVal);
		nRetVal -= 50;
	}
	return nRetVal;
}


//---------------------------------------------------------------------------


