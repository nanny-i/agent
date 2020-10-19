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


#ifndef _FIND_FILE_H__

#define _FIND_FILE_H__

#include "com_header_find_file_dll.h"

extern "C"{

INT32 ASIFF_Init(PVOID* lpObject, PASI_FF_INIT_INFO pafii, UINT32 nSize);
INT32 ASIFF_Free(PVOID lpObject);

INT32 ASIFF_DeleteFindFileWork(PVOID lpObject, UINT32 nOrderID);
INT32 ASIFF_AddSearchDirPath(PVOID lpObject, UINT32 nOrderID, LPCTSTR lpSearchPath);
INT32 ASIFF_ClearSearchDirPath(PVOID lpObject, UINT32 nOrderID);

INT32 ASIFF_AddFileMask(PVOID lpObject, UINT32 nOrderID, LPCTSTR lpFileMask);
INT32 ASIFF_DelFileMask(PVOID lpObject, UINT32 nOrderID, LPCTSTR lpFileMask);
INT32 ASIFF_ClearFileMask(PVOID lpObject, UINT32 nOrderID);

INT32 ASIFF_AddExceptPath(PVOID lpObject, UINT32 nOrderID, LPCTSTR lpExceptPath);
INT32 ASIFF_DelExceptPath(PVOID lpObject, UINT32 nOrderID, LPCTSTR lpExceptPath);
INT32 ASIFF_ClearExceptPath(PVOID lpObject, UINT32 nOrderID);

INT32 ASIFF_AddExceptPathPtn(PVOID lpObject, UINT32 nOrderID, LPCTSTR lpExceptPathPtn);
INT32 ASIFF_DelExceptPathPtn(PVOID lpObject, UINT32 nOrderID, LPCTSTR lpExceptPathPtn);
INT32 ASIFF_ClearExceptPathPtn(PVOID lpObject, UINT32 nOrderID);

INT32 ASIFF_AddFileDateTime(PVOID lpObject, UINT32 nOrderID, UINT32 nType, UINT32 nChkTime);
INT32 ASIFF_DelFileDateTime(PVOID lpObject, UINT32 nOrderID, UINT32 nType);
INT32 ASIFF_ClearFileDateTime(PVOID lpObject, UINT32 nOrderID);

INT32 ASIFF_AddFileFindOption(PVOID lpObject, UINT32 nOrderID, UINT32 nFindOption);
INT32 ASIFF_ClearFileFindOption(PVOID lpObject, UINT32 nOrderID);

INT32 ASIFF_SearchDirFile(PVOID lpObject, UINT32 nOrderID);
INT32 ASIFF_SearchDirFileThread(PVOID lpObject, UINT32 nOrderID);
INT32 ASIFF_GetFindFileItem(PVOID lpObject, UINT32 nOrderID, PASI_FF_FILE_ITEM pAFFIList, PUINT32 nListSize, PASI_FF_FILE_RESULT pAFFR);
INT32 ASIFF_IsDocFileFormat(PVOID lpObject, LPCTSTR pFilePath, INT32 *pnFileType);

}

#endif /*_FIND_FILE_H__*/