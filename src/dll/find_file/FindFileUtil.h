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

#ifndef _FIND_FILE_UTIL_H__

#define _FIND_FILE_UTIL_H__


#include "FileInfoDLLUtil.h"
#include "DocFileFmtDLLUtil.h"

class CFindFileUtil
{
private:
	TListID64			m_tFinderThreadList;
	TMapIDMapStr		m_tFileMaskMap;
	TMapIDMapStrID		m_tExceptDirMap;
	TMapIDMapStr		m_tExceptDirFileMaskMap;
	TMapIDListStr		m_tSearchListMap;
	TMapIDMap			m_tFileDTMap;
	TMapID				m_tFindOptionMap;
	

private:
	TListFindDirItem		m_tFindSubDirItemList;
	CMutexExt				m_tFindSubDirItemMutex;

	TListFindDirItem		m_tFindFileDirItemList;
	CMutexExt				m_tFindFileDirItemMutex;

	TMapFindFileWork		m_tFindFileWorkMap;
	CMutexExt				m_tFindFileWorkMutex;
	CSemExt 				m_SemExt;
	
private:
	CASIDFFDLLUtil*			m_tASIDFFDLLUtil;
	CASIFIDLLUtil*			m_tASIFIDLLUtil;

private:
	UINT32		m_nPreSearchLevel;
	UINT32		GetPreSearchLevel(String strSearchPath);

private:
	ASI_FF_INIT_INFO		m_tAFII;

public:
	INT32		Init(PASI_FF_INIT_INFO pafii);
	INT32		Release();

private:
	INT32		StopThread_Common(CThreadBase* tThreadObject, UINT32 nWaitTime = 5/*sec*/);

private:
	INT32		PreSearchDirThread(UINT32 nOrderID, String strRootPath);
	INT32		PreSearchDir(UINT32 nOrderID, String strRootPath);

public:
	INT32		Recursive_SearchDir(UINT32 nOrderID, String strRootPath, String strSubDir, INT32 nSubDirSearch, TListStr& tNameList, TListStr* tLastNameList = NULL, TListFindFileItem* tFindFileItemList = NULL, PUINT32 pnContinue = NULL);	
	INT32		Recursive_SearchFile(UINT32 nOrderID, String strSearchPath, TListFindFileItem& tFindFileItemList, PUINT32 pnContinue);
	INT32		Recursive_SearchDirFile(UINT32 nOrderID, String strSearchPath, String strSubDir, INT32 nSubDirSearch, UINT32& nDirNum, TListFindFileItem& tFindFileItemList);

public:
	INT32		AddFindSubDirItem(UINT32 nOrderID, UINT32 nSubSearch, TListStr& tNameList);
	INT32		GetFindSubDirItem(FIND_DIR_ITEM& tFDI);
	INT32		ClearFindSubDirItem();

public:
	INT32		AddFindFileDirItem(UINT32 nOrderID, TListStr& tNameList, PUINT32 nWorkNum);
	INT32		GetFindFileDirItem(FIND_DIR_ITEM& tFDI);
	INT32		GetFindFileDirItem(TListFindDirItem& tSFDWList, UINT32& nOrderID, UINT32 nLimited = 1000);
	INT32		ClearFindFileDirItem();

public:
	INT32		InitFindFileWork(UINT32 nOrderID);
	INT32		DeleteFindFileWork(UINT32 nOrderID);
	INT32		ClearFindFileWork();

	PFIND_FILE_WORK	GetFindFileWork(UINT32 nOrderID);

	INT32		SetFindFileWork_SearchPath(UINT32 nOrderID, UINT32 nType, UINT32 nValue);
	INT32		SetFindFileWork_TotalDir(UINT32 nOrderID, UINT32 nDirNum, UINT32 nDirSubSearchedNum = 0);	

	INT32		AddFindFileItemList(UINT32 nOrderID, UINT32 nSearchDirNum, TListFindFileItem& tFindFileItemList);
	INT32		AddFindFileItemList(UINT32 nOrderID, UINT32 nSearchDirNum, PFIND_FILE_ITEM pAFFI = NULL);

public:
	INT32		AddFileMask(UINT32 nOrderID, LPCTSTR lpFileMask);
	INT32		DelFileMask(UINT32 nOrderID, LPCTSTR lpFileMask);
	INT32		ClearFileMask(UINT32 nOrderID);
	INT32		IsExistFileMask(UINT32 nOrderID, String strFilePath, String strFileName, UINT32& nMatchType);

public:
	INT32		IsExistFileMaskByDFF(UINT32 nOrderID, String strFileFullName);

public:
	INT32		AddExceptDir(UINT32 nOrderID, LPCTSTR lpDirPath);
	INT32		DelExceptDir(UINT32 nOrderID, LPCTSTR lpDirPath);
	INT32		ClearExceptDir(UINT32 nOrderID);
	INT32		IsExistExceptDir(UINT32 nOrderID, LPCTSTR lpDirPath);

public:
	INT32		AddExceptDirFileMask(UINT32 nOrderID, LPCTSTR lpDirPathFileMask);
	INT32		DelExceptDirFileMask(UINT32 nOrderID, LPCTSTR lpDirPathFileMask);
	INT32		ClearExceptDirFileMask(UINT32 nOrderID);
	INT32		IsExistExceptDirFileMask(UINT32 nOrderID, String strFilePath, String strFileName);

public:
	INT32		AddFileDateTime(UINT32 nOrderID, UINT32 nType, UINT32 nChkDT);
	INT32		DelFileDateTime(UINT32 nOrderID, UINT32 nType);
	INT32		ClearFileDateTime(UINT32 nOrderID);
	INT32		IsExistFileDateTime(UINT32 nOrderID, String strFilePath, String strFileName);

public:
	INT32		StringMatchSpec(LPCTSTR pszTarget, LPCTSTR pszSpec);

public:
	INT32		AddSearchDirPath(UINT32 nOrderID, LPCTSTR lpSearchRoot);
	INT32		ClearSearchDirPath(UINT32 nOrderID);

public:
	INT32		AddFileFindOption(UINT32 nOrderID, UINT32 nFindOption);
	INT32		ClearFileFindOption(UINT32 nOrderID);
	UINT32		GetFileFindOption(UINT32 nOrderID);

public:
	INT32		SearchDirFileThread(UINT32 nOrderID);
	INT32		SearchDirFile(UINT32 nOrderID);
	INT32		GetFindFileItem(UINT32 nOrderID, PASI_FF_FILE_ITEM pAFFI, PUINT32 nBufNum, PASI_FF_FILE_RESULT pAFFR);

public:
	INT32		SetPreSearchLevel(UINT32 nLevel);




public:
	CFindFileUtil(void);
	~CFindFileUtil(void);
};

#endif /*_FIND_FILE_UTIL_H__*/