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

class CExecuteFileUtil : public CUtilBase
{
public:
	CExecuteFileUtil(void);
	~CExecuteFileUtil(void);

private:
	CProcUtil	m_tProcUtil;

private:
	INT32		ChkFileHash(String strFileName, String strFileHash);
	INT32		ChkFileCertInfo(String strFileName);

public:
	INT32		ExecuteFileByUser(ASI_TS_INFO& tATIO, ASI_TS_MGR_PARAM& tATMP, UINT32 nWaitTime = -1);

private:
	INT32		ExecuteFile_Udt();
	INT32		ExecuteFile_DpFile();
	INT32		ExecuteFile_WPtnGBL(INT32& nChgWPtn);
	INT32		ExecuteFile_WPtnGWL(INT32& nChgWPtn);
	INT32		ExecuteFile_WPtnGBO(INT32& nChgWPtn);
	INT32		ExecuteFile_WPtnGWO(INT32& nChgWPtn);

public:
	INT32		ExecuteFile();
};

extern CExecuteFileUtil*		t_ExecuteFileUtil;
