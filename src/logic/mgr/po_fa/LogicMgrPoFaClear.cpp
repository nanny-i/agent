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
#include "LogicMgrPoFaClear.h"

//---------------------------------------------------------------------------

CLogicMgrPoFaClear*		t_LogicMgrPoFaClear = NULL;

//---------------------------------------------------------------------------

CLogicMgrPoFaClear::CLogicMgrPoFaClear()
{
	t_ManagePoFaClear		= new CManagePoFaClear();
	t_ManagePoFaClearPkg	= new CManagePoFaClearPkg();
	t_ManagePoFaClearUnit	= new CManagePoFaClearUnit();
	t_LogicPoFaClear		= new CLogicPoFaClear();

	t_ManagePoFaClear->LoadDBMS();
	t_ManagePoFaClearPkg->LoadDBMS();
	t_ManagePoFaClearUnit->LoadDBMS();

	t_ManagePoFaClear->InitHash();

	m_strLogicName		= "mgr agt po fa clear";
	
	m_nPolicyType		= SS_POLICY_TYPE_FA_CLEAR;
	m_nSSPoSeqIdx		= SS_POLICY_INDEX_FA_CLEAR;
	m_nAgtPktEditCode	= G_CODE_COMMON_EDIT;	
	
	m_nEvtObjType		= EVENT_OBJECT_TYPE_POLICY;
	m_nEvtObjCode		= EVENT_OBJECT_CODE_POLICY_FA_CLEAR;
}
//---------------------------------------------------------------------------

CLogicMgrPoFaClear::~CLogicMgrPoFaClear()
{
	SAFE_DELETE(t_LogicPoFaClear);

	SAFE_DELETE(t_ManagePoFaClear);
	SAFE_DELETE(t_ManagePoFaClearPkg);
	SAFE_DELETE(t_ManagePoFaClearUnit);
}
//---------------------------------------------------------------------------
INT32		CLogicMgrPoFaClear::AnalyzePkt_FromMgr_Ext()
{
	return SetHdrAndRtn(AZPKT_CB_RTN_SUCCESS);
}
//---------------------------------------------------------------------------

INT32		CLogicMgrPoFaClear::AnalyzePkt_FromMgr_Edit_Ext()
{
	PDB_PO_FA_CLEAR pdpfc = NULL;
	DB_PO_FA_CLEAR dpfc;

	m_tDPH = &(dpfc.tDPH);

	TListDBPoFaClearPkg		tPkgList;
	TListDBPoFaClearUnit	tUnitList;

	if( t_ManagePoFaClear->GetPkt(RecvToken, dpfc))					return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
	if(!RecvToken.TokenDel_32(m_nRecvNum))							return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
	while(m_nRecvNum--)
	{
		DB_PO_FA_CLEAR_PKG	dpfcp;		
		DB_PO_FA_CLEAR_UNIT dpfcu;

		if( t_ManagePoFaClearPkg->GetPkt(RecvToken, dpfcp))			return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
		if( t_ManagePoFaClearUnit->GetPkt(RecvToken, dpfcu))		return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);

		{
			dpfcu.nScanTime = GetCurrentDateTimeInt();
			if(dpfcu.nSchType == SCHEDULE_PERIOD_TYPE_BOOT)
			{
				U64_SCHEDULE tDT;
				tDT.all = dpfcu.nScanTime;
				if(tDT.U8.min && t_EnvInfoOp->IsSysBootTime() == 0)
				{
					dpfcu.nScanTime = t_EnvInfo->m_nBootChkTime;
					WriteLogN("[%s] auto setting last scan time  : [%d][%u]", m_strLogicName.c_str(), dpfcu.tDPH.nID, dpfcu.nScanTime);
				}
			}
		}

		tPkgList.push_back(dpfcp);
		tUnitList.push_back(dpfcu);

		dpfc.tDPH._add_id(dpfcp.tDPH.nID);
	}

	pdpfc = (PDB_PO_FA_CLEAR)t_DeployPolicyUtil->GetCurPoPtr(m_nPolicyType);
	if(pdpfc)
	{
		t_ManagePoFaClearPkg->ClearItemByPolicyID(pdpfc->tDPH.nID);		
		t_ManagePoFaClear->DelPoFaClear(pdpfc->tDPH.nID);
	}

	{
		{
			TListDBPoFaClearUnitItor begin, end;
			begin = tUnitList.begin();	end = tUnitList.end();
			for(begin; begin != end; begin++)
			{
				if(t_ManagePoFaClearUnit->ApplyPoFaClearUnit(*begin))
				{
					SetDLEA_EC(g_nErrRtn);
					WriteLogE("[%s] apply policy unit information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
					continue;
				}
			}
		}

		{
			TListDBPoFaClearPkgItor begin, end;
			begin = tPkgList.begin();	end = tPkgList.end();
			for(begin; begin != end; begin++)
			{
				if(t_ManagePoFaClearPkg->FindItem(begin->tDPH.nID))
				{
					SetDLEA_EC(g_nErrRtn);
					WriteLogE("[%s] add policy pkg information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
					continue;
				}

				t_ManagePoFaClearPkg->AddPoFaClearPkg(*begin);
			}
		}

		if(SetER(t_ManagePoFaClear->ApplyPoFaClear(dpfc)))
		{
			SetDLEA_EC(g_nErrRtn);
			WriteLogE("[%s] apply policy information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
			return SetHdrAndRtn(AZPKT_CB_RTN_DBMS_FAIL);
		}
	}

	return SetHdrAndRtn(AZPKT_CB_RTN_SUCCESS);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32		CLogicMgrPoFaClear::IsExistSysOffSch()
{
	UINT32 nRet = 0;

	PDB_PO_FA_CLEAR pdb_po = (PDB_PO_FA_CLEAR)t_DeployPolicyUtil->GetCurPoPtr(m_nPolicyType);
	if(!pdb_po)	
	{
		WriteLogE("[%s:IsExistSysOffSch] not find current policy", m_strLogicName.c_str());
		return 0;
	}

	if(pdb_po->tDPH.nUsedMode == STATUS_USED_MODE_OFF)
	{
		return 0;
	}

	{
		TListID tIDList;
		t_ManagePoFaClearPkg->GetKeyIDList(pdb_po->tDPH.nID, tIDList);
		TListIDItor begin, end;
		begin = tIDList.begin();	end = tIDList.end();
		for(begin; begin != end; begin++)
		{
			PDB_PO_FA_CLEAR_UNIT pdpfcu = t_ManagePoFaClearUnit->FindItem(*begin);
			if(!pdpfcu || pdpfcu->tDPH.nUsedMode == STATUS_USED_MODE_OFF)
			{ 
				continue;
			}

			if(pdpfcu->nSchType != SCHEDULE_PERIOD_TYPE_SHUTDOWN && pdpfcu->nSchType != SCHEDULE_PERIOD_TYPE_SHUTDOWN_EXT)		continue;

			nRet = 1;
			break;
		}
	}	
	return nRet;
}
//---------------------------------------------------------------------------

INT32		CLogicMgrPoFaClear::IsExistSysOffSchByPoPwr()
{
	UINT32 nRet = 0;

	PDB_PO_FA_CLEAR pdb_po = (PDB_PO_FA_CLEAR)t_DeployPolicyUtil->GetCurPoPtr(m_nPolicyType);
	if(!pdb_po)	
	{
		WriteLogE("[%s:IsExistSysOffSchByPoPwr] not find current policy", m_strLogicName.c_str());
		return 0;
	}

	if(pdb_po->tDPH.nUsedMode == STATUS_USED_MODE_OFF)
	{
		return 0;
	}

	{
		TListID tIDList;
		t_ManagePoFaClearPkg->GetKeyIDList(pdb_po->tDPH.nID, tIDList);
		TListIDItor begin, end;
		begin = tIDList.begin();	end = tIDList.end();
		for(begin; begin != end; begin++)
		{
			PDB_PO_FA_CLEAR_UNIT pdpfcu = t_ManagePoFaClearUnit->FindItem(*begin);
			if(!pdpfcu || pdpfcu->tDPH.nUsedMode == STATUS_USED_MODE_OFF)
			{ 
				continue;
			}

			if(pdpfcu->nSchType != SCHEDULE_PERIOD_TYPE_SHUTDOWN_EXT)		continue;

			nRet = 1;
			break;
		}
	}	
	return nRet;
}
//---------------------------------------------------------------------------

INT32		CLogicMgrPoFaClear::OnTimer_Logic()
{
	INT32 nRet = -1;
	TListID tIDList;
	MEM_FIND_ORDER_INFO tMFOI;
	TListIDItor begin, end;
	UINT32 dwID = 0;
	PDB_PO_FA_CLEAR pDbPo = (PDB_PO_FA_CLEAR)t_DeployPolicyUtil->GetCurPoPtr(m_nPolicyType);
	if(!pDbPo)	
	{
		WriteLogE("[%s:OnTimer_Logic] not find current policy", m_strLogicName.c_str());
		return 0;
	}

	if(pDbPo->tDPH.nUsedMode == STATUS_USED_MODE_OFF)
	{
		return 0;
	}

	dwID = pDbPo->tDPH.nID;
	t_ManagePoFaClearPkg->GetKeyIDList(dwID, tIDList);
	begin = tIDList.begin();	end = tIDList.end();
	for(begin; begin != end; begin++)
	{
		tMFOI.nPoID = *begin;
		tMFOI.nOpType = SS_LOG_DOC_OP_TYPE_SCHEDULE;
		tMFOI.nNextOp = G_CODE_COMMON_DEL;
		nRet = ApplyPolicy_Unit(*begin, tMFOI);
		if(!nRet)
			ApplyPolicy_SendLastChkTime(*begin);
	}
	return 1;
}
//---------------------------------------------------------------------------

INT32		CLogicMgrPoFaClear::ApplyPolicy()
{
	if(t_EnvInfoOp->IsSysOffMode() == 0)
	{
		t_LogicApplyPolicy->SetEPSHookPolicy();	
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32		CLogicMgrPoFaClear::ApplyPolicy_Unit(UINT32 nUnitID, MEM_FIND_ORDER_INFO& tMFOI)
{
	PDB_PO_FA_CLEAR_UNIT pdpfcu = t_ManagePoFaClearUnit->FindItem(nUnitID);
	if(!pdpfcu || pdpfcu->tDPH.nUsedMode == STATUS_USED_MODE_OFF)
	{ 
		return -1;
	}

	return ApplyPolicy_Unit(pdpfcu, tMFOI);
}
//---------------------------------------------------------------------------

INT32		CLogicMgrPoFaClear::ApplyPolicy_Unit(PDB_PO_FA_CLEAR_UNIT pdpfcu, MEM_FIND_ORDER_INFO& tMFOI)
{
	CFileUtil tFileUtil;
	U64_SCHEDULE tIS;
	UINT32 nLastChkTime = 0;
	INT32 nRetVal = 0;

	if(pdpfcu == NULL)
	{
		return -1;
	}

	nLastChkTime = pdpfcu->nScanTime;

	tIS.all = pdpfcu->nSchTime;
	tIS.U8.type = pdpfcu->nSchType;

	tFileUtil.SetEnvPathRegKey(STR_REG_DEFAULT_SVC_PATH_ENV_PATH);

	if(tMFOI.nOpType == SS_LOG_DOC_OP_TYPE_SCHEDULE_DEMAND || tMFOI.nOpType == SS_LOG_DOC_OP_TYPE_SCAN)
	{
		if(pdpfcu->tDPH.nID)	
		{
			nLastChkTime = GetCurrentDateTimeInt();
		}
	}
	else
	{
		{
			MEM_ENV_NOTIFY_INFO_SCH menis;
			menis.nNotifyType = SS_POLICY_TYPE_FA_NOTIFY;
			menis.nPolType    = SS_POLICY_TYPE_FA_CLEAR;
			menis.nOpType     = EVENT_OPERATION_TYPE_DEL;
			menis.nSchType	  = tIS.U8.type;

			menis.tDPH.nID       = pdpfcu->tDPH.nID;

			if(!t_LogicMgrEnvNotifyInfo->IsValidSchduleNotify(nLastChkTime, tIS.all, menis))
				t_LogicEnvNotifyInfo->SendPkt_Notify_Sch_info(menis);
		}
		if(IsValidSchedule(tIS.all, nLastChkTime) == 0)
		{
			return -1;
		}
		if(pdpfcu->nScanType == SS_PO_FA_CLEAR_SCAN_TYPE_DEMAND)
		{
			INT32 nReadOnly = 0;
			PDB_PO_HOST_RUN pdphr = (PDB_PO_HOST_RUN)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_HOST_RUN);
			if(!pdphr || pdphr->nMgrShowType == SS_PO_HOST_RUN_MGR_SHOW_TYPE_NOT_USED)
				nReadOnly = 1;

			if(pdpfcu->tDPH.nExtOption & SS_PO_FA_CLEAR_UNIT_OPTION_FLAG_SCAN_TYPE_DEMAND_NON_FIND_AUTO)
			{
				pdpfcu->nScanTime = nLastChkTime;
				if(pdpfcu->tDPH.nID)
					t_ManagePoFaClearUnit->EditPoFaClearUnit(*pdpfcu);
				WriteLogN("init fa clear request excute view .. from schedule : [uid:%d]", pdpfcu->tDPH.nID);
			}

			t_LogicPoFaClear->SendPkt_Init(pdpfcu->tDPH.nID, nLastChkTime);
			WriteLogN("init fa clear request scan .. from schedule : [uid:%d]", pdpfcu->tDPH.nID);
			return -1;
		}
	}

	WriteLogN("start(check) fa clear schedule : [uid:%d][mfoi_optype:%d]", pdpfcu->tDPH.nID, tMFOI.nOpType);
	pdpfcu->nScanTime = nLastChkTime;
	if(pdpfcu->tDPH.nID)
		t_ManagePoFaClearUnit->EditPoFaClearUnit(*pdpfcu);

	String strReqScanPath, strReqScanPtn, strReqScanExPath;
	String strScanPath, strScanPtn, strScanExPath;
	String strUserChildProc;

	{
		strReqScanExPath	= pdpfcu->strExPath;
		strReqScanPtn		= pdpfcu->strFilePtnLocal;
	}

	if(tMFOI.nOpType == SS_LOG_DOC_OP_TYPE_SCAN)
	{
		strReqScanExPath = "";
		strReqScanPath = pdpfcu->strExPath;
	}

	if(pdpfcu->strExePath.empty() == FALSE)
	{
		TListStr tCPList;
		TListStrItor cp_begin, cp_end;
		tFileUtil.GetEnvPathToLocalPath(pdpfcu->strExePath, &tCPList);
		cp_begin = tCPList.begin();	cp_end = tCPList.end();
		if(cp_begin != cp_end)		strUserChildProc = *cp_begin;
	}

	{
		strScanExPath = strReqScanExPath;
	}

	{
		switch(pdpfcu->nFilePtnType)
		{
			case SS_PO_FA_CLEAR_PTN_TYPE_LOCAL:
			{
				strScanPtn = strReqScanPtn;
				break;
			}
			case SS_PO_FA_CLEAR_PTN_TYPE_GLOBAL:
			{
				PDB_PO_FA_ENV pdb_po = (PDB_PO_FA_ENV)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_FA_ENV);
				if(!pdb_po)	
				{
					WriteLogE("[%s] not find [fa env] current policy", m_strLogicName.c_str());					
				}
				else if(pdb_po->tDPH.nUsedMode == STATUS_USED_MODE_OFF)
				{
					break;
				}
				else
				{
					TListID tEnvIDList;
					t_ManagePoFaEnvPkg->GetKeyIDList(pdb_po->tDPH.nID, tEnvIDList);
					TListIDItor begin_e, end_e;
					begin_e = tEnvIDList.begin();	end_e = tEnvIDList.end();
					for(begin_e; begin_e != end_e; begin_e++)
					{
						PDB_PO_FA_ENV_UNIT pdb_unit_env = t_ManagePoFaEnvUnit->FindItem(*begin_e);
						if(!pdb_unit_env || pdb_unit_env->tDPH.nUsedMode == STATUS_USED_MODE_OFF)
							continue;

						if(strScanPtn.empty() == FALSE)
						{
							tFileUtil.AddLasCHAR(strScanPtn, ';');
						}
						strScanPtn += pdb_unit_env->strFilePtnGlobal;
					}
					if(!strScanPtn.empty())
						replace_char_in_str((char *)strScanPtn.c_str(), ';', ',');

				}
				break;
			}
		}		
	}

	if(strReqScanPath.empty())
	{
		if(!pdpfcu->strInPath.empty())
		{
			if(strScanPath.empty())
				strScanPath = pdpfcu->strInPath;
			else
				strScanPath += ";" + pdpfcu->strInPath;
		}
	}
	else
	{
		if(strScanPath.empty())
			strScanPath = strReqScanPath;
		else
			strScanPath += ";" + strReqScanPath;
	}
		
	WriteLogN("[%s] fa clear scan info : path : [%s]", m_strLogicName.c_str(), strScanPath.c_str());
	WriteLogN("[%s] fa clear scan info : ptn : [%s]", m_strLogicName.c_str(), strScanPtn.c_str());
	WriteLogN("[%s] fa clear scan info : ex_path : [%s]", m_strLogicName.c_str(), strScanExPath.c_str());
	WriteLogN("[%s] fa clear scan info : in_path : [%s]", m_strLogicName.c_str(), strScanPath.c_str());
	WriteLogN("[%s] fa clear scan info : reg_path : [%s]", m_strLogicName.c_str(), strReqScanPath.c_str());

	if(strScanPtn.length() < 3)
	{
		WriteLogE("[%s] fa clear operation stop ... empty ptn info : [uid:%u][%s]", m_strLogicName.c_str(), pdpfcu->tDPH.nID, strScanPtn.c_str());
		return -1;
	}


	{
		tMFOI.nID = t_ThreadPoFaClear->GetNextOrderID();
		{	
			CHAR chTok = GetToken(strScanExPath, ';', ',');
			CTokenString Token(strScanExPath.c_str(), strScanExPath.length(), chTok);
			while(Token.IsNextToken())
			{
				String strExPath = Token.NextToken();
				if(t_ASIFFDLLUtil)
				{
					nRetVal = t_ASIFFDLLUtil->ASIFF_AddExceptPath(tMFOI.nID, strExPath.c_str());
					if(nRetVal == 0)
						WriteLogN("[%s] success to add exception path : [%d][%s]", m_strLogicName.c_str(), tMFOI.nID, strExPath.c_str());
					else
						WriteLogE("[%s] fail to add exception path : [%d][%s] (%d)", m_strLogicName.c_str(), tMFOI.nID, strExPath.c_str(), nRetVal);
				}		
				
			}
		}

		{
			CHAR chTok = GetToken(strScanPtn, ';', ',');
			CTokenString Token(strScanPtn.c_str(), strScanPtn.length(), chTok);
			while(Token.IsNextToken())
			{
				String strFileExt = Token.NextToken();
				if(t_ASIFFDLLUtil)
				{
					nRetVal = t_ASIFFDLLUtil->ASIFF_AddFileMask(tMFOI.nID, strFileExt.c_str());
					if(nRetVal == 0)
						WriteLogN("[%s] success to add file extension : [%d][%s]", m_strLogicName.c_str(), tMFOI.nID, strFileExt.c_str());
					else
						WriteLogE("[%s] fail to add file extension : [%d][%s] (%d)", m_strLogicName.c_str(), tMFOI.nID, strFileExt.c_str(), nRetVal);
				}
			}
		}

		{
			CHAR chTok = GetToken(strScanPath, ';', ',');
			CTokenString Token(strScanPath.c_str(), strScanPath.length(), chTok);
			while(Token.IsNextToken())
			{
				String strPath = Token.NextToken();
				if(t_ASIFFDLLUtil)
				{
					nRetVal = t_ASIFFDLLUtil->ASIFF_AddSearchDirPath(tMFOI.nID, strPath.c_str());
					if(nRetVal == 0)
						WriteLogN("[%s] success to add file path : [%d][%s]", m_strLogicName.c_str(), tMFOI.nID, strPath.c_str());
					else
						WriteLogE("[%s] fail to add file path : [%d][%s] (%d)", m_strLogicName.c_str(), tMFOI.nID, strPath.c_str(), nRetVal);
				}
			}
		}

		UINT32 nASIFFOption = 0;
		if(pdpfcu->tDPH.nExtOption & SS_PO_FA_CLEAR_UNIT_OPTION_FLAG_SCAN_DOC_FILE_FMT)
			nASIFFOption += ASI_FF_FIND_OPTION_USED_DOC_FILE_FORMAT;
		if(tMFOI.nNetDrv)
			nASIFFOption += ASI_FF_FIND_OPTION_SEARCH_NET_DRIVE;


		if(t_ASIFFDLLUtil)
		{
	 		nRetVal = t_ASIFFDLLUtil->ASIFF_AddFileDateTime(tMFOI.nID, pdpfcu->nChkFDTType, pdpfcu->nChkFDTValue * 86400);
			if(nRetVal == 0)
				WriteLogN("[%s] success to add file date time : [%d][%d][%d]", m_strLogicName.c_str(), tMFOI.nID, pdpfcu->nChkFDTType, pdpfcu->nChkFDTValue);
			else
				WriteLogE("[%s] fail to add file date time : [%d][%d][%d] (%d)", m_strLogicName.c_str(), tMFOI.nID, pdpfcu->nChkFDTType, pdpfcu->nChkFDTValue, nRetVal);

	 		nRetVal = t_ASIFFDLLUtil->ASIFF_AddFileFindOption(tMFOI.nID, nASIFFOption);
			if(nRetVal == 0)
				WriteLogN("[%s] success to add file find option : [%d][%d]", m_strLogicName.c_str(), tMFOI.nID, nASIFFOption);
			else
				WriteLogE("[%s] fail to add file find option : [%d][%d] (%d)", m_strLogicName.c_str(), tMFOI.nID, nASIFFOption, nRetVal);

	 		nRetVal = t_ASIFFDLLUtil->ASIFF_SearchDirFileThread(tMFOI.nID);
			if(nRetVal == 0)
				WriteLogN("[%s] success to start search dir thread : [%d]", m_strLogicName.c_str(), tMFOI.nID);
			else
				WriteLogE("[%s] fail to start search dir thread : [%d] (%d)", m_strLogicName.c_str(), tMFOI.nID, nRetVal);
		}
		t_ThreadPoFaClear->AddOrderID(&tMFOI);  
		t_ThreadPoFaClear->SetResume();
	}

	{
		if(pdpfcu->tDPH.nID && SetER(t_ManagePoFaClearUnit->EditPoFaClearUnit(*pdpfcu)))
		{
			WriteLogE("[%s] edit po fa clear unit fail : [%d]", m_strLogicName.c_str(), pdpfcu->tDPH.nID);
			return -1;
		}
	}	
	return 0;
}
//---------------------------------------------------------------------------

INT32		CLogicMgrPoFaClear::EndFindOrder(PMEM_FIND_ORDER_INFO pMFOI)
{
	INT32 nPolicyType = (pMFOI->nPoID ? pMFOI->nPoID : pMFOI->nID) + ASI_EPS_APP_POLICY_GROUP_ID_FA_CLEAR;

	switch(pMFOI->nOpType)
	{
		case SS_LOG_DOC_OP_TYPE_SCHEDULE:
			t_LogicPoFaClear->SendPkt_Del_Last(nPolicyType, pMFOI->nOpType, pMFOI->nNotiTotalFind);
			break;
		case SS_LOG_DOC_OP_TYPE_SCHEDULE_DEMAND:
			t_LogicPoFaClear->SendPkt_End(*pMFOI);
			break;
		case SS_LOG_DOC_OP_TYPE_SCAN:
			t_LogicLogDocDScan->SendPkt_End(*pMFOI);
			break;
	}

	if(pMFOI->nOpType == SS_LOG_DOC_OP_TYPE_SCHEDULE)
	{
		InitDLST_PoOp(pMFOI->nPoID, t_ManagePoFaClearUnit->GetName(pMFOI->nPoID), EVENT_OPERATION_TYPE_START);
		AppendDLStDesc(SS_LOG_STATUS_DESC_KEY_PO_START_TIME, t_ManagePoFaClearUnit->GetLastChkTime(pMFOI->nPoID));
		AppendDLStDesc(SS_LOG_STATUS_DESC_KEY_DOC_DEL_CNT, pMFOI->nNotiTotalFind);
		HISYNCSTEPUP(m_tDLST.nSyncSvrStep);
		t_LogicMgrLogStatus->SetLogStatus(m_tDLST);
	}

	return 0;
}
//---------------------------------------------------------------------------

INT32		CLogicMgrPoFaClear::PgFindOrder(PMEM_FIND_ORDER_INFO pMFOI)
{
	switch(pMFOI->nOpType)
	{
		case SS_LOG_DOC_OP_TYPE_SCHEDULE_DEMAND:	t_LogicPoFaClear->SendPkt_Progress(pMFOI);			break;
		case SS_LOG_DOC_OP_TYPE_SCAN:				t_LogicLogDocDScan->SendPkt_Progress(pMFOI);		break;
	}
	return 0;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

VOID		CLogicMgrPoFaClear::cbDriveInfoList(PASIDM_LOCAL_DRIVE_INFO pamldi, INT32 nSize, PVOID lParam)
{
	TMapMediaLocalDriveInfo* pDrvInfoMap = (TMapMediaLocalDriveInfo*)lParam;
	if(pDrvInfoMap == NULL)		return;

	ASIDM_LOCAL_DRIVE_INFO tALDI;
	memcpy(&tALDI, pamldi, min(nSize, (INT32)sizeof(ASIDM_LOCAL_DRIVE_INFO)));
	(*pDrvInfoMap)[tALDI.nDriveName] = tALDI;
	return;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
INT32		CLogicMgrPoFaClear::ApplyPolicy_SendLastChkTime(INT32 nUnitID)
{	
	SendToken.Clear();

	SendToken.TokenAdd_32(nUnitID);
	SendToken.TokenAdd_32(t_ManagePoFaClearUnit->GetLastChkTime(nUnitID));

	SendData_Link(G_TYPE_PO_FA_CLEAR, G_CODE_COMMON_APPLY, SendToken);
	SendToken.Clear();
	return 0;
}
//---------------------------------------------------------------------------

INT32		CLogicMgrPoFaClear::ConvertEnvPathToLocalPath(String strInPath, String& strOutPath)
{
	return t_ComFuncUtil->ConvertEnvPathToLocalPath(strInPath, strOutPath);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
