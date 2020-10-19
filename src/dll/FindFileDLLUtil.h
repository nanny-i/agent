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

// ASICOMPDLLUtil.h: interface for the CASICOMPDLLUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ASIFFDLLUTIL_H__BBCD1EB7_1B5F_497A_87D5_BDEC7EBF1C3F__INCLUDED_)
#define AFX_ASIFFDLLUTIL_H__BBCD1EB7_1B5F_497A_87D5_BDEC7EBF1C3F__INCLUDED_


//------------------------------------------------------
#include "com_header_find_file_dll.h"
//------------------------------------------------------

class CASIFFDLLUtil  
{

private:
	HINSTANCE		m_hDLL;
	PVOID			m_lpObject;
	
public:
	INT32			LoadLibraryExt(LPCTSTR lpDLLPath);
	INT32			FreeLibraryExt();

public:
	INT32	ASIFF_Init(PASI_FF_INIT_INFO pafii);
	INT32	ASIFF_Free();

	INT32	ASIFF_DeleteFindFileWork(UINT32 nOrderID);
	INT32	ASIFF_AddSearchDirPath(UINT32 nOrderID, LPCTSTR lpSearchPath);
	INT32	ASIFF_ClearSearchDirPath(UINT32 nOrderID);

	INT32	ASIFF_AddFileMask(UINT32 nOrderID, LPCTSTR lpFileMask);
	INT32	ASIFF_DelFileMask(UINT32 nOrderID, LPCTSTR lpFileMask);
	INT32	ASIFF_ClearFileMask(UINT32 nOrderID);

	INT32	ASIFF_AddExceptPath(UINT32 nOrderID, LPCTSTR lpExceptPath);
	INT32	ASIFF_DelExceptPath(UINT32 nOrderID, LPCTSTR lpExceptPath);
	INT32	ASIFF_ClearExceptPath(UINT32 nOrderID);

	INT32	ASIFF_AddFileDateTime(UINT32 nOrderID, UINT32 nType, UINT32 nChkTime);
	INT32	ASIFF_DelFileDateTime(UINT32 nOrderID, UINT32 nType);
	INT32	ASIFF_ClearFileDateTime(UINT32 nOrderID);

	INT32	ASIFF_AddFileFindOption(UINT32 nOrderID, UINT32 nFindOption);
	INT32	ASIFF_ClearFileFindOption(UINT32 nOrderID);

	INT32	ASIFF_SearchDirFile(UINT32 nOrderID);
	INT32	ASIFF_SearchDirFileThread(UINT32 nOrderID);
	INT32	ASIFF_GetFindFileItem(UINT32 nOrderID, PASI_FF_FILE_ITEM pAFFIList, PUINT32 nListSize, PASI_FF_FILE_RESULT pAFFR);

	INT32	ASIFF_IsDocFileFormat(LPCTSTR pFilePath, INT32 *pnFileType);

public:
	CASIFFDLLUtil();
	virtual ~CASIFFDLLUtil();

};

extern CASIFFDLLUtil*	t_ASIFFDLLUtil;

#endif // !defined(AFX_ASIFFDLLUTIL_H__BBCD1EB7_1B5F_497A_87D5_BDEC7EBF1C3F__INCLUDED_)
