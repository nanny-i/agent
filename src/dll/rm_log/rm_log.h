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

#ifndef _SC_SERVER_RM_LOG_DLL_
#define _SC_SERVER_RM_LOG_DLL_

#include <dirent.h>

extern "C" {
typedef struct DeleteFileList_t {

	int nChkDay;
	char FilePath[CHAR_MAX_SIZE];
	char FileName[CHAR_MAX_SIZE];
	DeleteFileList_t *next;

}DeleteFileList;

int RemoveFileByDT(const char* lpFindPath, unsigned int nChkType, unsigned int nDay);
int RemoveFileByLastDay(const char* lpFindPath, unsigned int nChkType, unsigned int nDay);

}

#endif
