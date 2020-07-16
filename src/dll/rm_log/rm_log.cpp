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
	DIR     *pDir = NULL;
	time_t  CurrentTime, ChkTime;
	char    DelFilePath[CHAR_MAX_SIZE] = {0,};
	int     nChkDay, nChkHour, nChkMin, nChkSec;
	double  DiffTime;
	struct stat FindStat, FileStat;
	struct dirent entry, *result = NULL;
	

	if (lstat(lpFindPath, &FindStat) != 0)
	{
		printf("[RemoveFileByDT] fail to stat %s %d\n", lpFindPath, errno);
		return -1;
	}

	if (S_ISDIR(FindStat.st_mode))
	{
		if ( (pDir = opendir(lpFindPath)) == NULL)
		{
			printf("[FindFileByLastDay] fail to open %s %d\n", lpFindPath, errno);
			return -1;
		}
		while (readdir_r(pDir, &entry, &result) == 0 && result != NULL )
		{
			if (entry.d_ino == 0 ) {
				continue;
			}

			if (strcmp(entry.d_name, ".") == 0 || strcmp(entry.d_name,"..") == 0) {
				continue;
			}
			snprintf(DelFilePath, CHAR_MAX_SIZE-1, "%s/%s", lpFindPath, entry.d_name);
			DelFilePath[CHAR_MAX_SIZE-1] = 0;

			if (lstat(DelFilePath, &FileStat) != 0)
			{
				printf("[RemoveFileByDT] fail to stat %s %d\n", DelFilePath, errno);
				return -1;
			}
			switch(nChkType)
			{
				case FILE_DT_CHK_TYPE_WRITE:
					ChkTime = FileStat.st_mtime;
					break;
				case FILE_DT_CHK_TYPE_ACCESS:
					ChkTime = FileStat.st_atime;
					break;
				default :
					return 0;
			}

			time(&CurrentTime);

			DiffTime = difftime(CurrentTime, ChkTime);

			nChkDay = DiffTime / (60 * 60 * 24);
			if (nChkDay < nDay)
			{
				continue;
			}

			unlink(DelFilePath);

		}
		closedir(pDir);
	}
	
	return 0;
}

int FindFileByLastDay(const char* lpFindPath, unsigned int nChkType, unsigned int nDay, 
		DEL_FILE_LIST& DelFileList, time_t& tOldestDay)
{
	DIR     *pDir = NULL;
	struct dirent entry, *result = NULL;
	char    DelFilePath[CHAR_MAX_SIZE] = {0,};
	struct stat FileStat;
	time_t  ChkTime;
	UINT32 nChkDay;

	{
		if ( (pDir = opendir(lpFindPath)) == NULL)
		{
			printf("[FindFileByLastDay] fail to open %s %d\n", lpFindPath, errno);
			return -1;
		}
		while (readdir_r(pDir, &entry, &result) == 0 && result != NULL )
		{
			if (entry.d_ino == 0 )
			{
				continue;
			}

			if (strcmp(entry.d_name, ".") == 0 || strcmp(entry.d_name,"..") == 0)
			{
				continue;
			}
			snprintf(DelFilePath, CHAR_MAX_SIZE-1, "%s/%s", lpFindPath, entry.d_name);
			DelFilePath[CHAR_MAX_SIZE-1] = 0;

			if (lstat(DelFilePath, &FileStat) != 0)
			{
				printf("[FindFileByLastDay] fail to stat %s %d\n", DelFilePath, errno);
				return -1;
			}
			if (S_ISDIR(FileStat.st_mode))
			{
				FindFileByLastDay(DelFilePath, nChkType, nDay, DelFileList, tOldestDay);

			}
			else if (S_ISREG(FileStat.st_mode))
			{
				switch(nChkType) {
					case FILE_DT_CHK_TYPE_WRITE:
						ChkTime = FileStat.st_mtime;
						break;
					case FILE_DT_CHK_TYPE_ACCESS:
						ChkTime = FileStat.st_atime;
						break;
					default :
						return 0;
				}

				nChkDay = ChkTime/(60*60*24);
				if(tOldestDay == 0)
					tOldestDay = nChkDay;
				else if(tOldestDay > nChkDay)
					tOldestDay = nChkDay;

				DeleteFileList_t* FileInfoList = (DeleteFileList_t*)malloc(sizeof(DeleteFileList_t));
				FileInfoList->nChkDay = nChkDay;
				snprintf(FileInfoList->FilePath, sizeof(FileInfoList->FilePath)-1, "%s", lpFindPath);
				snprintf(FileInfoList->FileName, sizeof(FileInfoList->FilePath)-1, "%s", entry.d_name);
				DelFileList.push_back(FileInfoList);

			}
		}
		closedir(pDir);
	}
}

int RemoveFileByLastDay(const char* lpFindPath, unsigned int nChkType, unsigned int nDay)
{
	struct stat FindStat;

	if(lpFindPath == NULL)
	{
		printf("[RemoveFileByLastDay] invalid input data\n");
		return -1;
	}
	if (lstat(lpFindPath, &FindStat) != 0)
	{
		printf("[RemoveFileByLastDay] fail to get stat %s %d\n", lpFindPath, errno);
		return -1;
	}

	time_t tOldestDay = 0;
	DEL_FILE_LIST DelFileList;

	if (S_ISDIR(FindStat.st_mode)) 
	{
		FindFileByLastDay(lpFindPath, nChkType, nDay, DelFileList, tOldestDay);
		find_entry(DelFileList, (UINT32)tOldestDay + nDay);
	}

	delItor begin, end;	
	begin = DelFileList.begin(); end = DelFileList.end();
	for(;begin != end; begin++)	
	{	
		DeleteFileList_t* pInfo = *begin;		
		delete pInfo;	    
	}
	DelFileList.clear();	
	
	return 0;
}

void find_entry(DEL_FILE_LIST& FindList, int maxChkDay)
{
	DeleteFileList_t *list = NULL;
	CHAR szFullPath[PATH_MAX] = {0,};
	
	delItor begin, end;
	begin = FindList.begin(); end = FindList.end();
	for(;begin != end; begin++)
	{
		list = *begin;
		if(list != NULL)
		{
			if (list->nChkDay < maxChkDay)
			{
				snprintf(szFullPath, PATH_MAX-1, "%s/%s", list->FilePath,list->FileName);
				szFullPath[PATH_MAX-1] = 0;
				if(unlink(szFullPath) == -1)
				{
					printf("[find_entry] fail to unlink %s %d\n", szFullPath, errno);
				}
			}
		}
	}
}
