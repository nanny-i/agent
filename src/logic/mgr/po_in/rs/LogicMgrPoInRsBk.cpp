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
#include "LogicMgrPoInRsBk.h"

//---------------------------------------------------------------------------

CLogicMgrPoInRsBk*		t_LogicMgrPoInRsBk = NULL;

//---------------------------------------------------------------------------

CLogicMgrPoInRsBk::CLogicMgrPoInRsBk()
{
	t_ManagePoInRsBk	= new CManagePoInRsBk();
	t_ManagePoInRsBk->LoadDBMS();
	t_ManagePoInRsBk->InitHash();

	m_strLogicName		= "mgr po in rs bk";

	m_nPolicyType		= SS_POLICY_TYPE_IN_RS_BK;	
	m_nEvtObjType		= EVENT_OBJECT_TYPE_POLICY;
	m_nEvtObjCode		= EVENT_OBJECT_CODE_POLICY_IN_RS_BK;
}
//---------------------------------------------------------------------------

CLogicMgrPoInRsBk::~CLogicMgrPoInRsBk()
{
	SAFE_DELETE(t_ManagePoInRsBk);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32		CLogicMgrPoInRsBk::AnalyzePkt_FromMgr_Ext()
{
	return SetHdrAndRtn(AZPKT_CB_RTN_SUCCESS);
}
//---------------------------------------------------------------------------

INT32		CLogicMgrPoInRsBk::AnalyzePkt_FromMgr_Edit_Ext()
{
	PDB_PO_IN_RS_BK pdata = NULL;
	DB_PO_IN_RS_BK data, data_old;
	m_tDPH = &(data.tDPH);

	if( t_ManagePoInRsBk->GetPkt(RecvToken, data))		return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);

	pdata = (PDB_PO_IN_RS_BK)t_DeployPolicyUtil->GetCurPoPtr(m_nPolicyType);
	if(pdata)
	{
		data_old = *pdata;
		t_ManagePoInRsBk->DelPoInRsBk(pdata->tDPH.nID);
	}
	
	{
		if(SetER(t_ManagePoInRsBk->ApplyPoInRsBk(data)))
		{
			SetDLEH_EC(g_nErrRtn);
			WriteLogE("[%s] apply policy information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
			return SetHdrAndRtn(AZPKT_CB_RTN_DBMS_FAIL);
		}
	}

	if(data_old.tDPH.nUsedMode != data.tDPH.nUsedMode)
	{
		t_ThreadTimer->t_TimerUtil.EnableTimer(TIMER_ID_POLICY_APPLY_EPS);
		if(data.tDPH.nUsedMode == STATUS_USED_MODE_ON)
		{
			t_LogicMgrLogRsBk->MakeLogRsBk();
		}
	}

	return SetHdrAndRtn(AZPKT_CB_RTN_SUCCESS);
}
//---------------------------------------------------------------------------

INT32		CLogicMgrPoInRsBk::ApplyPolicy()
{
	return 0;
}
//---------------------------------------------------------------------------

INT32		CLogicMgrPoInRsBk::OnTimer_Logic()
{
	UINT64 ddwFreeSize = 0;
	UINT64 ddwTotal = 0, ddwAvail = 0;
	PDB_PO_IN_RS_BK pdb_po = (PDB_PO_IN_RS_BK)t_DeployPolicyUtil->GetCurPoPtr(m_nPolicyType);
	if(!pdb_po)	
	{
		WriteLogE("[%s] not find in rs bk policy", m_strLogicName.c_str());
		return 0;
	}

	if(pdb_po->tDPH.nUsedMode == STATUS_USED_MODE_OFF)
	{
		return 0;
	}

	{
		CFileUtil tFileUtil;
		String strBkPath;
		strBkPath = SPrintf("%s/%s", t_EnvInfo->m_strRootPath.c_str(), STR_BACKUP_RS_BK);
		UINT32 nMaxKeepNum = pdb_po->nFileKeppNum;
		UINT32 nTryLoof = 10;

		if(pdb_po->nKeepSize)
		{
			UINT64 nKeepSize = t_ManageLogRsBk->GetTBkSize();
			UINT64 nMaxKeepSize = ((UINT64)pdb_po->nKeepSize * (ASI_GIGABYTE));
			while(nKeepSize > nMaxKeepSize && nTryLoof--)
			{
				TListStr tStrKeyList;
				t_ManageLogRsBk->GetStrKeyIDList(tStrKeyList);
				if(DeleteBkLog(tStrKeyList, nMaxKeepNum) == 0)
				{
					break;
				}
				nKeepSize = t_ManageLogRsBk->GetTBkSize();
				if(nMaxKeepNum)		nMaxKeepNum -= 1;
			}
		}

		if(pdb_po->nFreeSize)
		{
			t_ResInfoDLLUtil->GetHddInfo(&ddwTotal, &ddwAvail, strBkPath.c_str());
			ddwFreeSize = (ddwTotal / 100) * pdb_po->nFreeSize;
			if(ddwFreeSize > ddwAvail)
			{
				WriteLogN("[%s] available size small then check free size : [a:%llu]<[f:%llu][%d]", m_strLogicName.c_str(), ddwAvail, ddwFreeSize, pdb_po->nFreeSize);
			}
		}
	}	
	return 0;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32		CLogicMgrPoInRsBk::DeleteBkLog(TListStr& tKeyList, INT32 nRemainNum)
{
	INT32 nRemoveNum = 0;

	TListStrItor begin_key, end_key;
	begin_key = tKeyList.begin();	end_key = tKeyList.end();
	for(begin_key; begin_key != end_key; begin_key++)
	{
		TListID tIDList;
		t_ManageLogRsBk->GetFirstRsBk(*begin_key, tIDList, nRemainNum);

		TListIDItor begin, end;
		begin = tIDList.begin();	end = tIDList.end();
		for(begin; begin != end; begin++)
		{
			PDB_LOG_RS_BK pdata = t_ManageLogRsBk->FindItem(*begin);
			if(!pdata)		continue;

			t_DocBackupUtil->RemoveBackupFile(pdata);

			t_ManageLogRsBk->DelLogRsBk(*begin);
			nRemoveNum += 1;
		}
	}
	return nRemoveNum;
}
//---------------------------------------------------------------------------