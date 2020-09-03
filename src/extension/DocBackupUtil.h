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

#pragma once

class CDocBackupUtil : public CUtilBase
{
public:
	CDocBackupUtil(void);
	~CDocBackupUtil(void);

private:
	CFileUtil	m_tFileUtil;
	CMutexExt	m_tBkMutex;
	CProcUtil	m_tProcUtil;

private:
	TMapStr		m_tSkipNameMap;
	TMapStr		m_tSkipProcMap;

private:
	TMapStrID	m_tDirSizeMap;

public:
	INT32		InitEnv();

public:
	INT32		RemoveBackupFile(PDB_LOG_DOC pdld);
	INT32		BackupFile(PDB_LOG_DOC pdld, UINT32 nDelMethod = 0, UINT32 nDelCnt = 7, UINT32 nLimitSize = 0, UINT32 nLimitDelCnt = 0);
	INT32		RecoveryFile(PDB_LOG_DOC pdld);

public:
	INT32		BackupFile(PDB_LOG_RS_BK pdata);
	INT32		RecoveryFile(PDB_LOG_RS_BK pdata);
	INT32		RemoveBackupFile(PDB_LOG_RS_BK pdata);

public:
	INT32		RemoveBackupFilesByNonExistLog(UINT32& nContinue);

private:
	INT32		SetBkSeedKey(PBYTE pSeedKey, UINT32 nMode = 0);
};

extern CDocBackupUtil*		t_DocBackupUtil;
