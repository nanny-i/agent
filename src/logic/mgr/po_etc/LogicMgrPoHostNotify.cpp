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
#include "LogicMgrPoHostNotify.h"

//---------------------------------------------------------------------------

CLogicMgrPoHostNotify*		t_LogicMgrPoHostNotify = NULL;

//---------------------------------------------------------------------------

CLogicMgrPoHostNotify::CLogicMgrPoHostNotify()
{
	t_ManagePoHostNotify			= new CManagePoHostNotify();
	t_ManagePoHostNotifyPkg			= new CManagePoHostNotifyPkg();
	t_ManagePoHostNotifyUnit		= new CManagePoHostNotifyUnit();

	t_ManagePoHostNotify->LoadDBMS();
	t_ManagePoHostNotifyPkg->LoadDBMS();
	t_ManagePoHostNotifyUnit->LoadDBMS();

	t_ManagePoHostNotify->InitHash();

	m_strLogicName		= "mgr po host notify";
	
	m_nPolicyType		= SS_POLICY_TYPE_HOST_NOTIFY;
	m_nEvtObjType		= EVENT_OBJECT_TYPE_POLICY;
	m_nEvtObjCode		= EVENT_OBJECT_CODE_POLICY_HOST_NOTIFY;
}
//---------------------------------------------------------------------------
CLogicMgrPoHostNotify::~CLogicMgrPoHostNotify()
{
	SAFE_DELETE(t_ManagePoHostNotifyUnit);
	SAFE_DELETE(t_ManagePoHostNotifyPkg);
	SAFE_DELETE(t_ManagePoHostNotify);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
INT32		CLogicMgrPoHostNotify::AnalyzePkt_FromMgr_Ext()
{
	return SetHdrAndRtn(AZPKT_CB_RTN_SUCCESS);
}
//---------------------------------------------------------------------------
INT32		CLogicMgrPoHostNotify::AnalyzePkt_FromMgr_Edit_Ext()
{
	PDB_PO_HOST_NOTIFY pdphn = NULL;
	DB_PO_HOST_NOTIFY dphn;
	m_tDPH = &(dphn.tDPH);
	TListDBPoHostNotifyPkg	tPkgList;
	TListDBPoHostNotifyUnit	tUnitList;

	if( t_ManagePoHostNotify->GetPkt(RecvToken, dphn))		return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
	if(!RecvToken.TokenDel_32(m_nRecvNum))				return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
	while(m_nRecvNum--)
	{
		DB_PO_HOST_NOTIFY_PKG dppp;		
		DB_PO_HOST_NOTIFY_UNIT dppu;

		if( t_ManagePoHostNotifyPkg->GetPkt(RecvToken, dppp))	return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
		if( t_ManagePoHostNotifyUnit->GetPkt(RecvToken, dppu))	return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);

		tPkgList.push_back(dppp);
		tUnitList.push_back(dppu);

		dphn.tDPH._add_id(dppp.tDPH.nID);
	}

	pdphn = (PDB_PO_HOST_NOTIFY)t_DeployPolicyUtil->GetCurPoPtr(m_nPolicyType);
	if(pdphn)
	{
		t_ManagePoHostNotifyPkg->ClearPkgUnitByPolicyID(pdphn->tDPH.nID);		
		t_ManagePoHostNotify->DelPoHostNotify(pdphn->tDPH.nID);
	}

	{
		{
			TListDBPoHostNotifyUnitItor begin, end;
			begin = tUnitList.begin();	end = tUnitList.end();
			for(begin; begin != end; begin++)
			{
				if(t_ManagePoHostNotifyUnit->ApplyPoHostNotifyUnit(*begin))
				{
					SetDLEH_EC(g_nErrRtn);
					WriteLogE("[%s] apply policy unit information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
					continue;
				}
			}
		}

		{
			TListDBPoHostNotifyPkgItor begin, end;
			begin = tPkgList.begin();	end = tPkgList.end();
			for(begin; begin != end; begin++)
			{
				if(t_ManagePoHostNotifyPkg->FindItem(begin->tDPH.nID))
				{
					SetDLEH_EC(g_nErrRtn);
					WriteLogE("[%s] add policy pkg information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
					continue;
				}

				
				t_ManagePoHostNotifyPkg->AddPoHostNotifyPkg(*begin);
			}
		}

		if(SetER(t_ManagePoHostNotify->ApplyPoHostNotify(dphn)))
		{
			SetDLEH_EC(g_nErrRtn);
			WriteLogE("[%s] apply policy information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
			return SetHdrAndRtn(AZPKT_CB_RTN_DBMS_FAIL);
		}
	}

	return SetHdrAndRtn(AZPKT_CB_RTN_SUCCESS);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32		CLogicMgrPoHostNotify::OnTimer_Logic()
{
	PDB_PO_HOST_NOTIFY pdb_pol = (PDB_PO_HOST_NOTIFY)t_DeployPolicyUtil->GetCurPoPtr(m_nPolicyType);
	if(!pdb_pol)
	{
		UINT32 nPolID = t_DeployPolicyUtil->GetCurPoID(m_nPolicyType);
		if(nPolID != 0)
			WriteLogE("[%s] not find current policy (%d)", m_strLogicName.c_str(), nPolID);
		return 0;
	}
	if(pdb_pol->tDPH.nUsedMode != STATUS_USED_MODE_ON)	return 0;

	TListID tIDList;
	t_ManagePoHostNotifyUnit->GetItemIDList(tIDList);
	TListIDItor begin, end;

	begin = tIDList.begin();	end = tIDList.end();
	for(begin; begin != end; begin++)
	{
		PDB_PO_HOST_NOTIFY_UNIT pdphnu = t_ManagePoHostNotifyUnit->FindItem(*begin);
		if(pdphnu->tDPH.nUsedMode != STATUS_USED_MODE_ON)	continue;
		if(pdphnu)
		{
			U64_SCHEDULE tSchDT;
			tSchDT.all =  pdphnu->nSchTime;
			UINT32 nLastChkTime = pdphnu->nNotifyTime;
			if(!tSchDT.U8.type || IsValidSchedule(tSchDT.all, nLastChkTime) == 0)
				continue;
			pdphnu->nNotifyTime = nLastChkTime;
			ExecHostNotify(pdphnu);
		}
	}

	return 1;
}
//---------------------------------------------------------------------------
void	CLogicMgrPoHostNotify::ExecHostNotify(PDB_PO_HOST_NOTIFY_UNIT pdphnu)
{
	CFileUtil tFileUtil;
	String strNotifyInfoFile;
	{
		strNotifyInfoFile = SPrintf("%s/inven/info", t_EnvInfo->m_strRootPath.c_str());
		tFileUtil.ForceDirectory(strNotifyInfoFile.c_str());
		strNotifyInfoFile = SPrintf("%s/inven/info/po_host_notify.info", t_EnvInfo->m_strRootPath.c_str());

		unlink(strNotifyInfoFile.c_str());
	}

	{
		String strChildPath, strChildArg;

		{
			CHAR szShortPath[CHAR_MAX_SIZE] = {0, };
			strChildPath = SPrintf("%s/util/%s", t_EnvInfo->m_strRootPath.c_str(), STR_PROC_NAME_NANNY_INTRO);
//			GetShortPathName(strChildPath, szShortPath, MAX_PATH);
			strChildPath = szShortPath;
		}

		{
			strChildArg = SPrintf("used_mode=%u\f"
				"pos_type=%u\f"
				"show_size=%u\f"
				"show_pos=%u\f"
				"show_time=%u\f"
				"msg_fmt_type=%u\f"
				"msg_info=%s\f",
				pdphnu->tDPH.nUsedMode, pdphnu->nPosType, pdphnu->nShowSize, pdphnu->nShowPos, pdphnu->nShowTime,
				pdphnu->nMsgFmtType, pdphnu->strMsgInfo.c_str());
		}

		{
			tFileUtil.WriteFileBuffer(strNotifyInfoFile, strChildArg);
			strChildArg = SPrintf("/%s/", strNotifyInfoFile.c_str());
		}

		ASI_TS_INFO tATI;
		ASI_TS_MGR_PARAM tATMP;
		{
			sprintf_ext(CHAR_MAX_SIZE, tATI.szTaskName, "%s", STR_TS_NAME_HOST_NOTIFY); 
			tATI.nChkPeriod = ASI_TS_CHECK_PREIOD_TYPE_ONCE;
			tATI.nStartTime	= GetCurrentDateTimeInt() + 5;

			tATMP.strTSChildPath = strChildPath;
			tATMP.strTSChildArgument = strChildArg;
			tATMP.nTSSingleRun		= 1;
			tATMP.nTSWaitMode		= 0;
			tATMP.nTSAutoDel		= 1;
		}
		t_ExecuteFileUtil->ExecuteFileByUser(tATI, tATMP);
	}
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
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
