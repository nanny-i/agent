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

//---------------------------------------------------------------------------


#include "stdafx.h"
#include "com_struct.h"
#include "ManageDocDeleteInfo.h"

//---------------------------------------------------------------------------

CManageDocDeleteInfo*	t_ManageDocDeleteInfo = NULL;

//---------------------------------------------------------------------------

CManageDocDeleteInfo::CManageDocDeleteInfo()
{
	t_DBMgrDocDeleteInfo	= new CDBMgrDocDeleteInfo();
	m_nDocCnt = 0;
	m_nSchCnt = 0;
	m_nMenualCnt = 0;
}
//---------------------------------------------------------------------------

CManageDocDeleteInfo::~CManageDocDeleteInfo()
{
	if(t_DBMgrDocDeleteInfo)		{	delete t_DBMgrDocDeleteInfo;		t_DBMgrDocDeleteInfo = NULL;	}
}
//---------------------------------------------------------------------------

INT32		CManageDocDeleteInfo::LoadDBMS()
{
	TListDBDocDeleteInfo tDBDocDeleteInfoList;
    TListDBDocDeleteInfoItor begin, end;
	if(SetER(t_DBMgrDocDeleteInfo->LoadExecute(&tDBDocDeleteInfoList)))
    {
    	return g_nErrRtn;
    }

    begin = tDBDocDeleteInfoList.begin();	end = tDBDocDeleteInfoList.end();
    for(begin; begin != end; begin++)
    {
    	AddItem(begin->nID, *begin);
    }
    return 0;
}
//---------------------------------------------------------------------------
INT32		CManageDocDeleteInfo::AddDocDeleteInfo(DB_DOC_DELETE_INFO&	dddi)
{
	if(SetER(t_DBMgrDocDeleteInfo->InsertExecute(&dddi)))
	{
		return g_nErrRtn;
	}

	AddItem(dddi.nID, dddi);

	return 0;
}
//---------------------------------------------------------------------------

INT32		CManageDocDeleteInfo::EditDocDeleteInfo(DB_DOC_DELETE_INFO&	dddi)
{
	PDB_DOC_DELETE_INFO pdpfe = FindItem(dddi.nID);
	if(!pdpfe)	return ERR_DBMS_UPDATE_FAIL;

	if(SetER(t_DBMgrDocDeleteInfo->UpdateExecute(&dddi)))
	{
		return g_nErrRtn;
	}

	EditItem(dddi.nID, dddi);
	
	return 0;
}
//---------------------------------------------------------------------------   
void CManageDocDeleteInfo::UpdateDocScanTime()
{
	UINT32 nScanDay = GetCurrentYearMonDay();
	PDB_DOC_DELETE_INFO pData = LastItem();
	
	if(pData && pData->nRegDate == nScanDay)
	{
		DB_DOC_DELETE_INFO data = *pData;
		data.nLastScanTime = GetCurrentDateTimeInt();
		EditDocDeleteInfo(data);
		return;
	}
		
	DB_DOC_DELETE_INFO data;
	data.nRegDate = nScanDay;
	data.nLastScanTime = GetCurrentDateTimeInt();
	AddDocDeleteInfo(data);
}
//---------------------------------------------------------------------------
void CManageDocDeleteInfo::UpdateDocDeleteInfo()
{
	DB_DOC_DELETE_INFO data;
	UINT32 nScanDay = GetCurrentYearMonDay();
	PDB_DOC_DELETE_INFO pData = LastItem();
	
	if(pData && pData->nRegDate == nScanDay)
	{
		data = *pData;
		data.nLastDelTime = GetCurrentDateTimeInt();
		data.nDocCnt += m_nDocCnt;
		data.nSchCnt += m_nSchCnt;
		data.nMenualCnt += m_nMenualCnt;
		EditDocDeleteInfo(data);
	}
	else
	{
		if(pData)	data.nLastScanTime = pData->nLastScanTime;
		data.nRegDate = nScanDay;
		data.nLastDelTime = GetCurrentDateTimeInt();
		data.nDocCnt += m_nDocCnt;
		data.nSchCnt += m_nSchCnt;
		data.nMenualCnt += m_nMenualCnt;
		AddDocDeleteInfo(data);
	}
	m_nDocCnt = 0;
	m_nSchCnt = 0;
	m_nMenualCnt = 0;	
	m_tData = data;
}
//---------------------------------------------------------------------------
void	CManageDocDeleteInfo::DocDeleteCount(UINT32 nOpType)
{
	switch(nOpType)
	{
		case SS_LOG_DOC_OP_TYPE_DOCTRACE:			m_nDocCnt++;			break;
		case SS_LOG_DOC_OP_TYPE_SCHEDULE:			m_nSchCnt++;			break;
		case SS_LOG_DOC_OP_TYPE_SCHEDULE_DEMAND:	m_nMenualCnt++;			break;
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32				CManageDocDeleteInfo::SetPkt(MemToken& SendToken)
{
    return 0;
}
//---------------------------------------------------------------------------

INT32				CManageDocDeleteInfo::SetPkt(PDB_DOC_DELETE_INFO pddi, MemToken& SendToken)
{
	SendToken.TokenAdd_32(pddi->nLastScanTime);
	SendToken.TokenAdd_32(pddi->nLastDelTime);
	SendToken.TokenAdd_32(pddi->nDocCnt);
	SendToken.TokenAdd_32(pddi->nSchCnt);
	SendToken.TokenAdd_32(pddi->nMenualCnt);

	SendToken.TokenSet_Block();
    return 0;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
