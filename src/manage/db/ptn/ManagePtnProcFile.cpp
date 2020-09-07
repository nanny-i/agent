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
#include "ManagePtnProcFile.h"

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

CManagePtnProcFile::CManagePtnProcFile()
{
	m_tDBMgrPtnProcFile	= new CDBMgrPtnProcFile();
}
//---------------------------------------------------------------------------

CManagePtnProcFile::~CManagePtnProcFile()
{
	if(m_tDBMgrPtnProcFile)		{	delete m_tDBMgrPtnProcFile;		m_tDBMgrPtnProcFile = NULL;	}
}
//---------------------------------------------------------------------------


INT32		CManagePtnProcFile::LoadDBMS()
{
	TListDBPtnProcFile tDBPtnProcFileList;
    TListDBPtnProcFileItor begin, end;
	if(SetER(m_tDBMgrPtnProcFile->LoadExecute(&tDBPtnProcFileList)))
    {
    	return g_nErrRtn;
    }

    begin = tDBPtnProcFileList.begin();	end = tDBPtnProcFileList.end();
    for(begin; begin != end; begin++)
    {
		AddItem(begin->nID, *begin);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePtnProcFile::AddPtnProcFile(DB_PTN_PROC_FILE&	data)
{
	if(SetER(m_tDBMgrPtnProcFile->InsertExecute(&data)))
    {
    	return g_nErrRtn;
    }

	AddItem(data.nID, data);    
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePtnProcFile::EditPtnProcFile(DB_PTN_PROC_FILE&	data)
{
    if(m_tDBMgrPtnProcFile->UpdateExecute(&data))		return ERR_DBMS_UPDATE_FAIL;

	EditItem(data.nID, data);
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePtnProcFile::DelPtnProcFile(UINT32 nID)
{
	PDB_PTN_PROC_FILE pdata = FindItem(nID);
	if(!pdata)	return ERR_INFO_NOT_DELETE_BECAUSE_NOT_FIND;

	if(SetER(m_tDBMgrPtnProcFile->DeleteExecute(pdata->nID)))
    {
    	return g_nErrRtn;
    }
    DeleteItem(nID);
    return 0;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32	CManagePtnProcFile::GetPkt(MemToken& RecvToken, DB_PTN_PROC_FILE& data)
{	
	if (!RecvToken.TokenDel_32(data.nID))						goto INVALID_PKT;
	if (!RecvToken.TokenDel_32(data.nRegDate))					goto INVALID_PKT;
	if (!RecvToken.TokenDel_32(data.nUsedMode))					goto INVALID_PKT;

	if ( RecvToken.TokenDel_String(data.strFeKey) < 0)			goto INVALID_PKT;
	if ( RecvToken.TokenDel_String(data.strFileHash) < 0)		goto INVALID_PKT;

	if ( RecvToken.TokenDel_String(data.strFilePath) < 0)		goto INVALID_PKT;
	if ( RecvToken.TokenDel_String(data.strFileName) < 0)		goto INVALID_PKT;
	if ( RecvToken.TokenDel_String(data.strFileDescr) < 0)		goto INVALID_PKT;

	if ( RecvToken.TokenDel_String(data.strFileVersion) < 0)	goto INVALID_PKT;
	if (!RecvToken.TokenDel_32(data.nFileSize))					goto INVALID_PKT;

	if ( RecvToken.TokenDel_String(data.strPubName) < 0)		goto INVALID_PKT;
	if ( RecvToken.TokenDel_String(data.strPubSN) < 0)			goto INVALID_PKT;
	if ( RecvToken.TokenDel_String(data.strCntName) < 0)		goto INVALID_PKT;
	if ( RecvToken.TokenDel_String(data.strCntSN) < 0)			goto INVALID_PKT;

	if ( RecvToken.TokenDel_String(data.strPublisherName) < 0)	goto INVALID_PKT;
	if ( RecvToken.TokenDel_String(data.strPublisherName) < 0)	goto INVALID_PKT;

	if (!RecvToken.TokenDel_64(data.nOsID))						goto INVALID_PKT;
	if (!RecvToken.TokenDel_32(data.nBuildSN))					goto INVALID_PKT;
	if (!RecvToken.TokenDel_32(data.nPeType))					goto INVALID_PKT;
	if (!RecvToken.TokenDel_32(data.nPeBit))					goto INVALID_PKT;

	if (!RecvToken.TokenDel_32(data.nPtnSrcType))				goto INVALID_PKT;
	if (!RecvToken.TokenDel_32(data.nPtnType))					goto INVALID_PKT;
	if (!RecvToken.TokenDel_32(data.nPtnRisk))					goto INVALID_PKT;

	RecvToken.TokenSkip_Block();
	return 0;
INVALID_PKT:
	return -1;
}
//-------------------------------------------------------------------------------------

INT32		CManagePtnProcFile::SetPkt(MemToken& SendToken)
{	
	SendToken.TokenAdd_32(m_tMap.size());
	TMapDBPtnProcFileItor begin, end;
	begin = m_tMap.begin();	end = m_tMap.end();
	for(begin; begin != end; begin++)
	{
		PDB_PTN_PROC_FILE pdata = &(begin->second);
		if(!pdata)	continue;

		SetPkt(pdata, SendToken);
	}	
	return m_tMap.size();
}
//---------------------------------------------------------------------------

INT32		CManagePtnProcFile::SetPkt(PDB_PTN_PROC_FILE pdata, MemToken& SendToken)
{
	SendToken.TokenAdd_32(pdata->nID);
	SendToken.TokenAdd_32(pdata->nRegDate);
	SendToken.TokenAdd_32(pdata->nUsedMode);

	SendToken.TokenAdd_String(pdata->strFeKey);
	SendToken.TokenAdd_String(pdata->strFileHash);

	SendToken.TokenAdd_String(pdata->strFilePath);
	SendToken.TokenAdd_String(pdata->strFileName);
	SendToken.TokenAdd_String(pdata->strFileDescr);

	SendToken.TokenAdd_String(pdata->strFileVersion);
	SendToken.TokenAdd_32(pdata->nFileSize);

	SendToken.TokenAdd_String(pdata->strPubName);
	SendToken.TokenAdd_String(pdata->strPubSN);
	SendToken.TokenAdd_String(pdata->strCntName);
	SendToken.TokenAdd_String(pdata->strCntSN);

	SendToken.TokenAdd_String(pdata->strPublisherName);
	SendToken.TokenAdd_String(pdata->strProductName);

	SendToken.TokenAdd_64(pdata->nOsID);
	SendToken.TokenAdd_32(pdata->nBuildSN);
	SendToken.TokenAdd_32(pdata->nPeType);
	SendToken.TokenAdd_32(pdata->nPeBit);

	SendToken.TokenAdd_32(pdata->nPtnSrcType);
	SendToken.TokenAdd_32(pdata->nPtnType);
	SendToken.TokenAdd_32(pdata->nPtnRisk);

	SendToken.TokenSet_Block();
 	return 0;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//--------------------------------------------------------------------------- 

void 		CManagePtnProcFile::RemainDBG_ItemCnt(UINT32 nIdx)
{
	WriteLogN("remain manage item cnt [%d][ptn_proc_file] : %u, %u", nIdx, m_tMap.size(), m_tKeyMap.size());
    return;
}
//---------------------------------------------------------------------------





