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



#include "stdafx.h"
#include "com_struct.h"
#include "rm_log.h"

typedef list<DeleteFileList_t*> DEL_FILE_LIST;
typedef DEL_FILE_LIST::iterator delItor;

void find_entry(DEL_FILE_LIST& FindList, int maxChkDay);

int RemoveFileByDT(const char* lpFindPath, unsigned int nChkType, unsigned int nDay)
{
	time_t  tCurrentTime, tChkTime;
	char    acDelFilePath[CHAR_MAX_SIZE] = {0,};
	int     nChkDay, nChkHour, nChkMin, nChkSec;
	double  dDiffTime;
	struct stat stFileStat;
	DIR     *pDir = NULL;
	struct dirent *pDirEnt = NULL;

	if(nChkType != FILE_DT_CHK_TYPE_WRITE && nChkType != FILE_DT_CHK_TYPE_ACCESS)
	{
		return 0;
	}

	if(lpFindPath == NULL)
		return -1;
	
	if (lstat(lpFindPath, &stFileStat) != 0)
	{
		return -2;
	}

	if (!S_ISDIR(stFileStat.st_mode))
	{
		return 0;
	}

	if ( (pDir = opendir(lpFindPath)) == NULL)
	{
		return -3;
	}

	while((pDirEnt = readdir(pDir)) != NULL)
	{
		if (!_stricmp(pDirEnt->d_name, ".") || !_stricmp(pDirEnt->d_name,".."))
		{
			continue;
		}

		if(DT_REG != pDirEnt->d_type)
		{
			continue;
		}

		snprintf(acDelFilePath, CHAR_MAX_SIZE-1, "%s/%s", lpFindPath, pDirEnt->d_name);
		acDelFilePath[CHAR_MAX_SIZE-1] = 0;

		if (lstat(acDelFilePath, &stFileStat) != 0)
		{
			closedir(pDir);
			return -4;
		}

		if(nChkType == FILE_DT_CHK_TYPE_WRITE)
		{
			tChkTime = stFileStat.st_mtime;
		}
		else if(nChkType == FILE_DT_CHK_TYPE_ACCESS)
		{
			tChkTime = stFileStat.st_atime;
		}
		time(&tCurrentTime);
		dDiffTime = difftime(tCurrentTime, tChkTime);
		nChkDay = dDiffTime / (60 * 60 * 24);
		if (nChkDay < nDay)
		{
			continue;
		}
		unlink(acDelFilePath);
	}
	closedir(pDir);
	
	return 0;
}

int FindFileByLastDay(const char* lpFindPath, unsigned int nChkType, unsigned int nDay, DEL_FILE_LIST& DelFileList, time_t& tOldestDay)
{
	DIR  *pDir = NULL;
	struct dirent *pDirEnt = NULL;
	char acDelFilePath[CHAR_MAX_SIZE] = {0,};
	struct stat stFileStat;
	time_t  tChkTime = 0;
	UINT32 nChkDay = 0;

	if(nChkType != FILE_DT_CHK_TYPE_WRITE && nChkType != FILE_DT_CHK_TYPE_ACCESS)
	{
		return 0;
	}

	if(lpFindPath == NULL)
		return -1;

	if ( (pDir = opendir(lpFindPath)) == NULL)
	{
		return -2;
	}

	while((pDirEnt = readdir(pDir)) != NULL)
	{
		if (strcmp(pDirEnt->d_name, ".") == 0 || strcmp(pDirEnt->d_name,"..") == 0)
		{
			continue;
		}
		snprintf(acDelFilePath, CHAR_MAX_SIZE-1, "%s/%s", lpFindPath, pDirEnt->d_name);
		acDelFilePath[CHAR_MAX_SIZE-1] = 0;

		if(DT_DIR == pDirEnt->d_type)
		{
			FindFileByLastDay(acDelFilePath, nChkType, nDay, DelFileList, tOldestDay);
		}
		else if(DT_REG == pDirEnt->d_type)
		{
			if (lstat(acDelFilePath, &stFileStat) != 0)
			{
				closedir(pDir);
				return -3;
			}
			if(nChkType == FILE_DT_CHK_TYPE_WRITE)
			{
				tChkTime = stFileStat.st_mtime;
			}
			else if(nChkType == FILE_DT_CHK_TYPE_ACCESS)
			{
				tChkTime = stFileStat.st_atime;
			}

			nChkDay = tChkTime/(60*60*24);
			if(tOldestDay == 0)
				tOldestDay = nChkDay;
			else if(tOldestDay > nChkDay)
				tOldestDay = nChkDay;

			DeleteFileList_t* pFileInfoList = (DeleteFileList_t*)malloc(sizeof(DeleteFileList_t));
			if(pFileInfoList != NULL)
			{
				pFileInfoList->nChkDay = nChkDay;
				snprintf(pFileInfoList->acFilePath, CHAR_MAX_SIZE-1, "%s", lpFindPath);
				snprintf(pFileInfoList->acFileName, CHAR_MAX_SIZE-1, "%s", pDirEnt->d_name);
				DelFileList.push_back(pFileInfoList);
			}
		}
	}
	closedir(pDir);
	return 0;
}

int RemoveFileByLastDay(const char* lpFindPath, unsigned int nChkType, unsigned int nDay)
{
	struct stat stFindStat;
	DeleteFileList_t* pInfo = NULL;

	if(lpFindPath == NULL)
	{
		return -1;
	}
	if (lstat(lpFindPath, &stFindStat) != 0)
	{
		return -2;
	}

	time_t tOldestDay = 0;
	DEL_FILE_LIST stDelFileList;

	if (S_ISDIR(stFindStat.st_mode)) 
	{
		FindFileByLastDay(lpFindPath, nChkType, nDay, stDelFileList, tOldestDay);
		find_entry(stDelFileList, (UINT32)tOldestDay + nDay);
	}

	delItor begin, end;	
	begin = stDelFileList.begin(); end = stDelFileList.end();
	for(;begin != end; begin++)	
	{	
		pInfo = *begin;
		safe_free(pInfo);
	}
	stDelFileList.clear();	
	
	return 0;
}

void find_entry(DEL_FILE_LIST& FindList, int maxChkDay)
{
	DeleteFileList_t *pList = NULL;
	char szFullPath[CHAR_MAX_SIZE] = {0,};
	
	delItor begin, end;
	begin = FindList.begin(); end = FindList.end();
	for(;begin != end; begin++)
	{
		pList = *begin;
		if(pList == NULL)
		{
			continue;
		}
		if (pList->nChkDay < maxChkDay)
		{
			snprintf(szFullPath, CHAR_MAX_SIZE-1, "%s/%s", pList->acFilePath,pList->acFileName);
			szFullPath[CHAR_MAX_SIZE-1] = 0;
			unlink(szFullPath);
		}
	}
}
