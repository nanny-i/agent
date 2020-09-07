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
#include "ManageLogDevice.h"

//---------------------------------------------------------------------------

CManageLogDevice*	t_ManageLogDevice = NULL;

//---------------------------------------------------------------------------

CManageLogDevice::CManageLogDevice()
{
	t_DBMgrLogDevice	= new CDBMgrLogDevice();
}
//---------------------------------------------------------------------------

CManageLogDevice::~CManageLogDevice()
{
	if(t_DBMgrLogDevice)	{	delete t_DBMgrLogDevice;	t_DBMgrLogDevice = NULL;	}
}
//---------------------------------------------------------------------------

INT32		CManageLogDevice::LoadDBMS()
{
	UINT32 nLogMode = 0, nLogNum = 0;
	{
		PDB_ENV_LOG pdel = t_ManageEnvLog->FindItem(DEFAULT_ID);
		if(pdel)
		{
			nLogMode = t_ManageEnvLog->GetLogValue(pdel->tAgtLoadModeMap, SS_ENV_LOG_INDEX_SECU);
			nLogNum = t_ManageEnvLog->GetLogValue(pdel->tAgtLoadNumMap, SS_ENV_LOG_INDEX_SECU);
			if(nLogMode == SS_ENV_LOG_LOAD_MODE_TYPE_DAY && nLogNum)
			{
				nLogNum = ((GetCurrentDateTimeInt() / 86400) - nLogNum) * 86400;
			}
		}
	}

	TListDBLogDevice tDBLogDeviceList;	
	TListDBLogDeviceItor begin, end;
	if(SetER(t_DBMgrLogDevice->LoadDB(nLogMode, nLogNum, tDBLogDeviceList)))
    {
    	return g_nErrRtn;
    }

	UINT32 nShowLogDay = 0;
	{
		PDB_PO_HOST_RUN pdphr = (PDB_PO_HOST_RUN)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_HOST_RUN);
		if(pdphr)	nShowLogDay = ((GetCurrentDateTimeInt() / 86400) - pdphr->nShowLogDay) * 86400;		
	}

	begin = tDBLogDeviceList.begin();	end = tDBLogDeviceList.end();
	for(begin; begin != end; begin++)
	{
		if(ISSYNCSTEP(begin->nSyncSvrStep) && (begin->nRegDate < nShowLogDay))
		{
			continue;
		}

		AddItem(*begin);
	}    
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManageLogDevice::AddLogDevice(DB_LOG_DEVICE&	dld)
{
	if(SetER(t_DBMgrLogDevice->InsertExecute(&dld)))
    {
    	return g_nErrRtn;
    }

    AddItem(dld);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManageLogDevice::EditLogDevice(DB_LOG_DEVICE&	dld)
{
	PDB_LOG_DEVICE pdls = FindItem(dld.nID);
	if(!pdls)	return ERR_INFO_NOT_EDIT_BECAUSE_NOT_FIND;

	if(SetER(t_DBMgrLogDevice->UpdateExecute(&dld)))
    {
    	return g_nErrRtn;
    }

    *pdls = dld;

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManageLogDevice::DelLogDevice(UINT32 nID)
{
	PDB_LOG_DEVICE pdld = FindItem(nID);
	if(!pdld)	return ERR_INFO_NOT_DELETE_BECAUSE_NOT_FIND;

	if(SetER(t_DBMgrLogDevice->DeleteExecute(pdld->nID)))
    {
    	return g_nErrRtn;
    }

    DeleteItem(nID);
    return 0;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32			CManageLogDevice::SetPktSync(TListPVOID& tIDList)
{
	{
		TMapDBLogDeviceItor begin, end;
		begin = m_tMap.begin();	end = m_tMap.end();
		for(begin; begin != end; begin++)
		{
			if(ISSYNCSTEP(begin->second.nSyncSvrStep) || 
				(begin->second.nSkipTarget & SS_ENV_LOG_OPTION_FLAGE_SKIP_SAVE_SERVER))	continue;

			tIDList.push_back(&(begin->second));
		}

		if(tIDList.empty())	return -1;
	}
	return 0;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManageLogDevice::SetPkt(MemToken& SendToken)
{
    TListPVOID tSendList;

	{
		TMapDBLogDeviceItor begin, end;
		begin = m_tMap.begin();	end = m_tMap.end();
		for(begin; begin != end; begin++)
		{
			if(ISSYNCSTEP(begin->second.nSyncSvrStep) || 
				(begin->second.nSkipTarget & SS_ENV_LOG_OPTION_FLAGE_SKIP_SAVE_SERVER))	continue;

			tSendList.push_back(&(begin->second));
		}

		if(tSendList.empty())	return -1;
	}
			
	SendToken.TokenAdd_32(tSendList.size());
	{
		TListPVOIDItor begin, end;
		begin = tSendList.begin();	end = tSendList.end();
		for(begin; begin != end; begin++)
		{
			SetPkt((PDB_LOG_DEVICE)(*begin), SendToken);
		}
	}	
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManageLogDevice::SetPkt_Link(MemToken& SendToken)
{
	SendToken.TokenAdd_32(m_tMap.size());
	{
		TMapDBLogDeviceItor begin, end;
		begin = m_tMap.begin();	end = m_tMap.end();
		for(begin; begin != end; begin++)
		{
			SetPkt(&(begin->second), SendToken);
		}
	}	
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManageLogDevice::SetPkt(PDB_LOG_DEVICE pdld, MemToken& SendToken)
{
	SendToken.TokenAdd_32(pdld->nID);
	SendToken.TokenAdd_32(pdld->nRegDate);
	SendToken.TokenAdd_32(pdld->nEvtTime);
	SendToken.TokenAdd_32(pdld->nEvtErrCode);

	SendToken.TokenAdd_32(pdld->nNotifyType);
	SendToken.TokenAdd_32(pdld->nNotifyID);

	SendToken.TokenAdd_32(pdld->nHostID);
	SendToken.TokenAdd_32(pdld->nPolicyType);
	SendToken.TokenAdd_32(pdld->nOpType);

	SendToken.TokenAdd_32(pdld->nRegSvrID);
	SendToken.TokenAdd_32(pdld->nSyncSvrStep);

	SendToken.TokenAdd_32(pdld->nBlockType);
	SendToken.TokenAdd_String(pdld->strDvInstanceID);

	SendToken.TokenAdd_32(pdld->nUserID);

	SendToken.TokenSet_Block();

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManageLogDevice::GetPkt(MemToken& RecvToken, DB_LOG_DEVICE& dld)
{
	if (!RecvToken.TokenDel_32(dld.nID))						goto	INVALID_PKT;
	if (!RecvToken.TokenDel_32(dld.nRegDate))					goto	INVALID_PKT;
	if (!RecvToken.TokenDel_32(dld.nEvtTime))					goto	INVALID_PKT;
	if (!RecvToken.TokenDel_32(dld.nEvtErrCode))				goto	INVALID_PKT;

	if (!RecvToken.TokenDel_32(dld.nNotifyType))				goto 	INVALID_PKT;
	if (!RecvToken.TokenDel_32(dld.nNotifyID))					goto 	INVALID_PKT;

	if (!RecvToken.TokenDel_32(dld.nHostID))					goto 	INVALID_PKT;
	if (!RecvToken.TokenDel_32(dld.nPolicyType))				goto 	INVALID_PKT;
	if (!RecvToken.TokenDel_32(dld.nOpType))					goto 	INVALID_PKT;

	if (!RecvToken.TokenDel_32(dld.nRegSvrID))					goto 	INVALID_PKT;
	if (!RecvToken.TokenDel_32(dld.nSyncSvrStep))				goto 	INVALID_PKT;

	if (!RecvToken.TokenDel_32(dld.nBlockType))					goto 	INVALID_PKT;
	if ( RecvToken.TokenDel_String(dld.strDvInstanceID) < 0)	goto	INVALID_PKT;

	if (!RecvToken.TokenDel_32(dld.nUserID))					goto	INVALID_PKT;

	RecvToken.TokenSkip_Block();
	return 0;
INVALID_PKT:
	return -1;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------



