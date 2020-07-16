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
#include "as_parse.h"
#include "as_zip.h"

#define ZIP_FILE 1
#define UNZIP_FILE 2

void print_usage()
{
	printf("Examples : \n");
	printf("\tupdate -z -d zip_dir [-f zip_file_name]\n");
	printf("\t# create a zip file from zip_dir. (default zip file name : ssa_lnx_x64_XXXXXXXX.upt)\n");
	printf("\tupdate -u -f zip_file_name [-d ext_dir]\n");
	printf("\t# extract a zip file to ext_dir. (default ext dir : /tmp/ssa_lnx_udt/XXXXXXXX)\n");
}

INT32 remove_file_all(char *pDirPath)
{
	char acFilePath[MAX_PATH] = {0,};
	DIR *dp = NULL;
	struct dirent *dirp = NULL;
	if(pDirPath == NULL)
		return -1;

	if(DirectoryExists(pDirPath) == FALSE)
	{
		return -2;
	}

	dp = opendir(pDirPath);
	if (dp == NULL)
	{
		return -3;
	}

	while((dirp = readdir(dp)) != NULL)
	{
		if(!_stricmp(dirp->d_name, ".") || !_stricmp(dirp->d_name, ".."))
		{
			continue;
		}

		if(DT_DIR == dirp->d_type)
		{
			continue;
		}
		snprintf(acFilePath, MAX_PATH-1, "%s/%s", pDirPath, (char *)dirp->d_name);
		unlink(acFilePath);
		Sleep(10);
	}

	closedir(dp);
	return 0;
}

int set_opt(int argc, char *argv[], char *pcFileName, int nFileMax, char *pcPath, int nPathMax)
{
	int c;
	extern char *optarg;
	int nRetVal = 0;
	if(pcFileName == NULL || nFileMax < 1 || pcPath == NULL || nPathMax < 1)
		return 0;

	while ((c = getopt(argc, argv, "d:f:uzh")) != EOF)
	{
		switch ((char)c)
		{
		case 'd':
			if(optarg != NULL)
				strncpy(pcPath, optarg, nPathMax-1);
			break;
		case 'f':
			if(optarg != NULL)
				strncpy(pcFileName, optarg, nFileMax-1);
			break;
		case 'u':
			nRetVal = UNZIP_FILE;
			break;
		case 'z':
			nRetVal = ZIP_FILE;
			break;
		case 'h':
		default:
			print_usage();
			nRetVal = 0;
			break;
		}
	}
	return nRetVal;
}

int get_zip_path(char *pZipPath, int nMaxLen, char *pZipFileName)
{
	char acTempPath[CHAR_MAX_SIZE] = {0,};
	char acUpdatePath[CHAR_MAX_SIZE] = {0,};
	char acCurrentTime[CHAR_MAX_SIZE] = {0,};
	int i = 0;
	int nRet = 0;
	if(pZipPath == NULL || nMaxLen < 1)
		return -1;
	if(getcwd(acTempPath, CHAR_MAX_SIZE) == NULL)
		return -2;
	GetCurrentDateTime(0, acCurrentTime);

	snprintf(acUpdatePath, CHAR_MAX_SIZE-1, "%s/ssa_lnx_udt/%s", acTempPath, acCurrentTime);
	if(DirectoryExists(acUpdatePath) == FALSE)
	{
		if(ForceDirectories(acUpdatePath) == FALSE)
		{
			return -3;
		}
	}
	if(pZipFileName == NULL || pZipFileName[0] == 0)
	{
		nRet = -4;
		for(i=1; i<99;)
		{
			snprintf(acTempPath, CHAR_MAX_SIZE-1, "%s/ssa_lnx_x64_%s%02d.udt", acUpdatePath, acCurrentTime, i);
			if(is_file(acTempPath) != 0)
			{
				strncpy(pZipPath, acTempPath, nMaxLen-1);
				nRet = 0;
				break;
			}
			i += 2;
		}
	}
	else
	{
		snprintf(pZipPath, CHAR_MAX_SIZE-1, "%s/%s", acUpdatePath, pZipFileName);
		nRet = 0;
	}
	return nRet;
}


int get_ext_path(char *pExtPath, int nMaxLen, char *pDstDir, char *pZipFileName)
{
	char acExtractPath[CHAR_MAX_SIZE] = {0,};
	char acCurrentTime[CHAR_MAX_SIZE] = {0,};
	char acFileName[MAX_FILE_NAME] = {0,};
	int i = 0;
	int nRet = 0;
	if(pExtPath == NULL || nMaxLen < 1)
		return -1;
	
	if(pDstDir == NULL || pDstDir[0] == 0)
	{
		snprintf(acExtractPath, CHAR_MAX_SIZE-1, "/tmp/ssa_lnx_udt/update");
		if(DirectoryExists(acExtractPath) == FALSE)
		{
			if(ForceDirectories(acExtractPath) == FALSE)
			{
				return -2;
			}
		}
		else
		{
			remove_file_all(acExtractPath);
		}
	}
	else
	{
		GetCurrentDateTime(0, acCurrentTime);
		if(pZipFileName != NULL)
		{
			if(get_basename(pZipFileName, acFileName, MAX_FILE_NAME-1) != NULL)
			{
				if(remove_extname(acFileName, acFileName, MAX_FILE_NAME-1) != NULL)
				{
					strncpy(acCurrentTime, acFileName, CHAR_MAX_SIZE-1);
				}
			}
		}
		snprintf(acExtractPath, CHAR_MAX_SIZE-1, "%s/%s", pDstDir, acCurrentTime);
		if(DirectoryExists(acExtractPath) == FALSE)
		{
			if(ForceDirectories(acExtractPath) == FALSE)
			{
				return -3;
			}
		}
		else
		{
			remove_file_all(acExtractPath);
		}
	}

	strncpy(pExtPath, acExtractPath, nMaxLen-1);
	return 0;
}

int main(int argc, char* argv[])
{
	char acDirPath[MAX_PATH] = {0,};
	char acZipFileName[MAX_PATH] = {0,};
	char acZipPath[CHAR_MAX_SIZE] = {0,};
	int nZipFlag = 0;
	int nRetVal = 0;

	nZipFlag = set_opt(argc, argv, acZipFileName, MAX_PATH, acDirPath, MAX_PATH);
	if(nZipFlag == 0)
	{
		print_usage();
		return 2;
	}

	if(nZipFlag == ZIP_FILE)
	{
		if(acDirPath[0] == 0)
		{
			print_usage();
			return 3;
		}
		nRetVal = get_zip_path(acZipPath, CHAR_MAX_SIZE, acZipFileName);
		if(nRetVal < 0)
		{
			printf("fail to get zip file name (%d)\n", nRetVal);
			return 4;
		}
		nRetVal = as_zip_file(acZipPath, acDirPath, NULL);
		if(nRetVal != 0)
		{
			printf("fail to create a %s (%d)\n", acZipPath, nRetVal);
			return 5;
		}
		printf("success to create a %s from %s\n", acZipPath, acDirPath);
	}
	else if(nZipFlag == UNZIP_FILE)
	{
		if(acZipFileName[0] == 0)
		{
			print_usage();
			return 6;
		}

		nRetVal = get_ext_path(acZipPath, CHAR_MAX_SIZE, acDirPath, acZipFileName);
		if(nRetVal < 0)
		{
			printf("fail to get zip file name (%d)\n", nRetVal);
			return 7;
		}

		nRetVal = as_unzip_file(acZipFileName, acZipPath, NULL);
		if(nRetVal != 0)
		{
			printf("fail to extract a %s to %s (%d)\n", acZipFileName, acZipPath, nRetVal);
			return 5;
		}
		printf("success to extract a %s from %s\n", acZipFileName, acZipPath);
	}
	else
	{
		print_usage();
		return 3;
	}
	
	return 0;
}
