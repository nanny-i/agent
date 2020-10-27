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
#include "LogicMgrPoInVulnOp.h"

//---------------------------------------------------------------------------

CLogicMgrPoInVulnOp*		t_LogicMgrPoInVulnOp = NULL;

//---------------------------------------------------------------------------

CLogicMgrPoInVulnOp::CLogicMgrPoInVulnOp()
{
	t_ManagePoInVulnOp			= new CManagePoInVulnOp();
	t_ManagePoInVulnOpPkg		= new CManagePoInVulnOpPkg();

	t_ManagePoInVulnOp->LoadDBMS();
	t_ManagePoInVulnOpPkg->LoadDBMS();

	t_ManagePoInVulnOp->InitHash();

	m_strLogicName		= "mgr agt po in vuln op";
	
	m_nPolicyType		= SS_POLICY_TYPE_IN_VULN_OP;
	m_nSSPoSeqIdx		= SS_POLICY_INDEX_IN_VULN_OP;
	m_nAgtPktEditCode	= G_CODE_COMMON_EDIT;	
	
	m_nEvtObjType		= EVENT_OBJECT_TYPE_POLICY;
	m_nEvtObjCode		= EVENT_OBJECT_CODE_POLICY_IN_VULN_OP;
}
//---------------------------------------------------------------------------

CLogicMgrPoInVulnOp::~CLogicMgrPoInVulnOp()
{
	SAFE_DELETE(t_ManagePoInVulnOp);
	SAFE_DELETE(t_ManagePoInVulnOpPkg);
}
//---------------------------------------------------------------------------
INT32		CLogicMgrPoInVulnOp::AnalyzePkt_FromMgr_Ext()
{
	return SetHdrAndRtn(AZPKT_CB_RTN_SUCCESS);
}
//---------------------------------------------------------------------------

INT32		CLogicMgrPoInVulnOp::AnalyzePkt_FromMgr_Edit_Ext()
{
	PDB_PO_IN_VULN_OP pdata = NULL;
	DB_PO_IN_VULN_OP data, data_old;

	m_tDPH = &(data.tDPH);

	TListDBPoInVulnOpPkg	tPkgList;
	
	if( t_ManagePoInVulnOp->GetPkt(RecvToken, data))			return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
	if(!RecvToken.TokenDel_32(m_nRecvNum))						return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
	while(m_nRecvNum--)
	{
		DB_PO_IN_VULN_OP_PKG	dppp;			
		if( t_ManagePoInVulnOpPkg->GetPkt(RecvToken, dppp))		return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);	

		tPkgList.push_back(dppp);	
		data.tDPH._add_id(dppp.tDPH.nID);
	}

	pdata = (PDB_PO_IN_VULN_OP)t_DeployPolicyUtil->GetCurPoPtr(m_nPolicyType);
	if(pdata)
	{
		data_old = *pdata;
		t_ManagePoInVulnOpPkg->ClearItemByPolicyID(pdata->tDPH.nID);		
		t_ManagePoInVulnOp->DelPoInVulnOp(pdata->tDPH.nID);
	}

	{
		{
			TListDBPoInVulnOpPkgItor begin, end;
			begin = tPkgList.begin();	end = tPkgList.end();
			for(begin; begin != end; begin++)
			{
				if(t_ManagePoInVulnOpPkg->FindItem(begin->tDPH.nID))
				{
					SetDLEH_EC(g_nErrRtn);
					WriteLogE("[%s] add policy pkg information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
					continue;
				}

				t_ManagePoInVulnOpPkg->AddPoInVulnOpPkg(*begin);
			}
		}

		if(SetER(t_ManagePoInVulnOp->ApplyPoInVulnOp(data)))
		{
			SetDLEH_EC(g_nErrRtn);
			WriteLogE("[%s] apply policy information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
			return SetHdrAndRtn(AZPKT_CB_RTN_DBMS_FAIL);
		}
	}

	if(data_old.tDPIVOPF.strPtnFileName != data.tDPIVOPF.strPtnFileName)
	{
		m_nForceApplyPolicy = STATUS_MODE_ON;
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
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32		CLogicMgrPoInVulnOp::ApplyPolicy()
{
	PDB_PO_IN_VULN_OP pdata = (PDB_PO_IN_VULN_OP)t_DeployPolicyUtil->GetCurPoPtr(m_nPolicyType);
	if(!pdata)	
	{
		UINT32 nPolID = t_DeployPolicyUtil->GetCurPoID(m_nPolicyType);
		if(nPolID != 0)
			WriteLogE("[%s] not find current policy (%d)", m_strLogicName.c_str(), nPolID);
		return 0;
	}

	{
		if(pdata->tDPH.nUsedMode != STATUS_USED_MODE_OFF)
		{
			if(t_ManagePoInVulnOp->IsValidPtnFile(pdata) == 0 && t_EnvInfoOp->m_nApplyPolicyStatus)
			{
				AddDpDownInfo();
			}
			else if(m_nForceApplyPolicy)
			{
				if(t_LogicMgrPtnVuln->ReloadPtnVuln() == 0)
				{
					t_LogicMgrPtnVuln->InitPtnDeploy();
				}
			}
		}
	}

	return 0;
}
//---------------------------------------------------------------------------

INT32		CLogicMgrPoInVulnOp::CheckRunEnv()
{
	PDB_PO_IN_VULN_OP pdata = (PDB_PO_IN_VULN_OP)t_DeployPolicyUtil->GetCurPoPtr(m_nPolicyType);
	if(!pdata)	
	{
		UINT32 nPolID = t_DeployPolicyUtil->GetCurPoID(m_nPolicyType);
		if(nPolID != 0)
			WriteLogE("[%s] not find current policy (%d)", m_strLogicName.c_str(), nPolID);
		return -1;
	}

	{
		if(pdata->tDPH.nUsedMode != STATUS_USED_MODE_OFF && t_ManagePoInVulnOp->IsValidPtnFile(pdata) == 0)
		{
			AddDpDownInfo();
			return -10;
		}
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32		CLogicMgrPoInVulnOp::AddDpDownInfo()
{
	PDB_PO_SVR_INFO_UDT pdpsiu = (PDB_PO_SVR_INFO_UDT)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_SVR_INFO_UDT);
	if(!pdpsiu)
	{
		WriteLogE("[%s] not find policy svr info udt", m_strLogicName.c_str());
		return -1;
	}
	else if(pdpsiu->strDataSvrInfoList.empty())
	{
		WriteLogE("[%s] not exists udt chk svr info list", m_strLogicName.c_str());
		return -2;
	}

	PDB_PO_IN_VULN_OP pdata = (PDB_PO_IN_VULN_OP)t_DeployPolicyUtil->GetCurPoPtr(m_nPolicyType);
	if(!pdata)
	{
		UINT32 nPolID = t_DeployPolicyUtil->GetCurPoID(m_nPolicyType);
		if(nPolID != 0)
			WriteLogE("[%s] not find current policy (%d)", m_strLogicName.c_str(), nPolID);
		return -3;
	}

	String strDnFileName, strDnFileHash;
	strDnFileName = (pdata->tDPIVOPF.nPtnDnFileType ? pdata->tDPIVOPF.strPtnDnFileName : pdata->tDPIVOPF.strPtnFileSvName);
	strDnFileHash = (pdata->tDPIVOPF.nPtnDnFileType ? pdata->tDPIVOPF.strPtnDnFileHash : pdata->tDPIVOPF.strPtnFileHash);

	if(strDnFileName.empty() || strDnFileHash.empty())
	{
		WriteLogE("[%s] invalid ptn file info [%s][%s]", m_strLogicName.c_str(), strDnFileName.c_str(), strDnFileHash.c_str());
		return -4;
	}

	{
		ASI_FDL_INFO tAFI;

		tAFI.nID = t_EnvInfoOp->GetGlobalID();
		tAFI.nItemType = SS_DN_FILE_TYPE_VPTN_ASV;
		tAFI.nItemID = 0;	
		tAFI.nPolicyID = pdata->tDPH.nID;
		tAFI.nDLSvrUsedFlag	= (ASIFDL_DL_SVR_TYPE_LOCAL | ASIFDL_DL_SVR_TYPE_PTOP | ASIFDL_DL_SVR_TYPE_SITE);

		strncpy(tAFI.szDLPath, STR_DEPLOY_FILE_HOME_PPTN, MAX_PATH-1);

		{	
			strncpy(tAFI.szFileName, strDnFileName.c_str(), MAX_PATH-1);
			strncpy(tAFI.szFileHash, strDnFileHash.c_str(), MAX_PATH-1);
		}	

		if(t_ManageFileDown->IsExistDnInfo(tAFI.nItemType, tAFI.nPolicyID, tAFI.nItemID))
		{
			WriteLogN("already exists po in vuln download : [%d][%d][%s]:[%s]", tAFI.nID, tAFI.nItemID, tAFI.szFileName, pdpsiu->strDataSvrInfoList.c_str());
			return 0;
		}

		WriteLogN("start po in vuln download : [%d][%d][%s]:[%s]", tAFI.nID, tAFI.nItemID, tAFI.szFileName, pdpsiu->strDataSvrInfoList.c_str());
/*
		t_ASIFDLDLLUtil->SetDLSvrInfo(ASIFDL_DL_SVR_TYPE_SITE, pdpsiu->strDataSvrInfoList);
		t_ASIFDLDLLUtil->AddDLInfo(&tAFI);
*/
		SetDLSvrInfo(ASIFDL_DL_SVR_TYPE_SITE, pdpsiu->strDataSvrInfoList.c_str());
		AddDLInfo(&tAFI);
		t_ManageFileDown->AddItem(tAFI);
	}
	return 0;
}
//---------------------------------------------------------------------------
