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
#include "ManageLogDocDScan.h"

CManageLogDocDScan*	t_ManageLogDocDScan = NULL;

CManageLogDocDScan::CManageLogDocDScan(void)
{
	t_DBMgrLogDocDScan = new CDBMgrLogDocDScan();
}
//-------------------------------------------------------------------------------------

CManageLogDocDScan::~CManageLogDocDScan(void)
{
	if(t_DBMgrLogDocDScan)	{	delete t_DBMgrLogDocDScan;	t_DBMgrLogDocDScan = NULL;	}
}
//-------------------------------------------------------------------------------------

INT32		CManageLogDocDScan::LoadDBMS()
{
	UINT32 nLogMode = 0, nLogNum = 0;
	{
		PDB_ENV_LOG pdel = t_ManageEnvLog->FindItem(DEFAULT_ID);
		if(pdel)
		{
			nLogMode = t_ManageEnvLog->GetLogValue(pdel->tAgtLoadModeMap, SS_ENV_LOG_INDEX_DOC_DSCAN);
			nLogNum = t_ManageEnvLog->GetLogValue(pdel->tAgtLoadNumMap, SS_ENV_LOG_INDEX_DOC_DSCAN);
			if(nLogMode == SS_ENV_LOG_LOAD_MODE_TYPE_DAY && nLogNum)
			{
				nLogNum = ((GetCurrentDateTimeInt() / 86400) - nLogNum) * 86400;
			}
		}
	}

	TListDBLogDocDScan		tDBLogDocDScanList;
	TListDBLogDocDScanItor begin, end;
	if(SetER(t_DBMgrLogDocDScan->LoadDB(nLogMode, nLogNum, tDBLogDocDScanList)))
	{
		return g_nErrRtn;
	}

	UINT32 nShowLogDay = 0;	
	begin = tDBLogDocDScanList.begin();	end = tDBLogDocDScanList.end();
	for(begin; begin != end; begin++)
	{
		if(begin->nRegDate < nShowLogDay)
			continue;

		AddItem(*begin);
	}
	return 0;
}
//-------------------------------------------------------------------------------------

INT32		CManageLogDocDScan::AddLogDocDScan(DB_LOG_DOC_DSCAN& dldd)
{
	if(SetER(t_DBMgrLogDocDScan->InsertExecute(&dldd)))
	{
		return g_nErrRtn;
	}

	return CManageBase::AddItem(dldd.nID, dldd);
}
//-------------------------------------------------------------------------------------

INT32		CManageLogDocDScan::EditLogDocDScan(DB_LOG_DOC_DSCAN& dldd)
{
	PDB_LOG_DOC_DSCAN pdldd = FindItem(dldd.nID);
	if(!pdldd)	return ERR_INFO_NOT_EDIT_BECAUSE_NOT_FIND;

	if(SetER(t_DBMgrLogDocDScan->UpdateExecute(&dldd)))
	{
		return g_nErrRtn;
	}

	EditItem(dldd);

	return 0;
}
//-------------------------------------------------------------------------------------

INT32		CManageLogDocDScan::ClearItem()
{
	return CManageBase::ClearItem();
}
//-------------------------------------------------------------------------------------

INT32		CManageLogDocDScan::SetPkt(PDB_LOG_DOC_DSCAN pdldd, MemToken& SendToken)
{
	String strEucData;
	SendToken.TokenAdd_32(pdldd->nID);
	SendToken.TokenAdd_32(pdldd->nUsedFlag);
	SendToken.TokenAdd_32(pdldd->nRegDate);
	SendToken.TokenAdd_32(pdldd->nExtOption);

	if(ConvertCharsetString(CHARSET_UTF8, CHARSET_EUCKR, pdldd->strScanPath, strEucData) == 0)
	{
		SendToken.TokenAdd_String(strEucData);
	}
	else
		SendToken.TokenAdd_String(pdldd->strScanPath);

	SendToken.TokenAdd_String(pdldd->strScanPtn);

	SendToken.TokenAdd_32(pdldd->nFindNum);
	SendToken.TokenAdd_32(pdldd->nDelNum);

	SendToken.TokenSet_Block();

	return 0;
}
//-------------------------------------------------------------------------------------

INT32		CManageLogDocDScan::GetPkt(MemToken& RecvToken, DB_LOG_DOC_DSCAN& dldd)
{
	String strUtcData;
	if(!RecvToken.TokenDel_32(dldd.nID))							goto	INVALID_PKT;
	if(!RecvToken.TokenDel_32(dldd.nUsedFlag))						goto	INVALID_PKT;
	if(!RecvToken.TokenDel_32(dldd.nRegDate))						goto	INVALID_PKT;
	if(!RecvToken.TokenDel_32(dldd.nExtOption))						goto	INVALID_PKT;

	if(RecvToken.TokenDel_String(dldd.strScanPath) < 0)				goto	INVALID_PKT;
	if(ConvertCharsetString(CHARSET_EUCKR, CHARSET_UTF8, dldd.strScanPath, strUtcData) == 0)
	{
		dldd.strScanPath = strUtcData;
	}

	if(RecvToken.TokenDel_String(dldd.strScanPtn) < 0)				goto	INVALID_PKT;

	if(!RecvToken.TokenDel_32(dldd.nFindNum))						goto	INVALID_PKT;
	if(!RecvToken.TokenDel_32(dldd.nDelNum))						goto	INVALID_PKT;

	RecvToken.TokenSkip_Block();
	return 0;
INVALID_PKT:
	return -1;
}
//-------------------------------------------------------------------------------------

INT32		CManageLogDocDScan::SetPkt_Link(MemToken& SendToken)
{
	SendToken.TokenAdd_32(m_tMap.size());
	{
		TMapDBLogDocDScanItor begin, end;
		begin = m_tMap.begin();	end = m_tMap.end();
		for(begin; begin != end; begin++)
		{
			SetPkt(&(begin->second), SendToken);
		}
	}
	return 0;
}
//-------------------------------------------------------------------------------------