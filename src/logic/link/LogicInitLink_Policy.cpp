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
#include "LogicInitLink.h"

//---------------------------------------------------------------------------

void		CLogicInitLink::SendPkt_Init_Policy()
{
	SendPkt_Init_Policy_SA();
	SendPkt_Init_Policy_AC();
	SendPkt_Init_Policy_FA();
	SendPkt_Init_Policy_FE();
	SendPkt_Init_Policy_IN();
	SendPkt_Init_Policy_IN_AC();
	SendPkt_Init_Policy_IN_VULN();

	return;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void		CLogicInitLink::SendPkt_Init_Policy_SA()
{
	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_SVR_INFO_LGN;
		t_ManagePoSvrInfoLgn->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_svr_info_lgn][%d]", t_ManagePoSvrInfoLgn->Count());	
	}

	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_SVR_INFO_UDT;
		t_ManagePoSvrInfoUdt->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_svr_info_udt][%d]", t_ManagePoSvrInfoUdt->Count());	
	}

	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_HOST_RM_INFO;
		t_ManagePoHostRmInfo->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_host_rm_info][%d]", t_ManagePoHostRmInfo->Count());	
	}

	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_HOST_RUN;
		t_ManagePoHostRun->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_host_run][%d]", t_ManagePoHostRun->Count());	
	}

	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_SCH;
		t_ManagePoSch->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_sch][%d]", t_ManagePoSch->Count());

		m_tPktData->hdr.code = G_CODE_INIT_PO_SCH_PKG;
		t_ManagePoSchPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_sch_pkg][%d]", t_ManagePoSchPkg->Count());		

		m_tPktData->hdr.code = G_CODE_INIT_PO_SCH_UNIT;
		t_ManagePoSchUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_sch_unit][%d]", t_ManagePoSchUnit->Count());	
	}

	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_POWER;
		t_ManagePoPower->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_power][%d]", t_ManagePoPower->Count());

		m_tPktData->hdr.code = G_CODE_INIT_PO_POWER_PKG;
		t_ManagePoPowerPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_power_pkg][%d]", t_ManagePoPowerPkg->Count());		

		m_tPktData->hdr.code = G_CODE_INIT_PO_POWER_UNIT;
		t_ManagePoPowerUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_power_unit][%d]", t_ManagePoPowerUnit->Count());	
	}

	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_WIN_RUN;
		t_ManagePoWinRun->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_win_run][%d]", t_ManagePoWinRun->Count());
	}

	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_CTL_PANEL;
		t_ManagePoCtlPanel->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_ctl_panel][%d]", t_ManagePoCtlPanel->Count());

		m_tPktData->hdr.code = G_CODE_INIT_PO_CTL_PANEL_PKG;
		t_ManagePoCtlPanelPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_ctl_panel_pkg][%d]", t_ManagePoCtlPanelPkg->Count());		

		m_tPktData->hdr.code = G_CODE_INIT_PO_CTL_PANEL_UNIT;
		t_ManagePoCtlPanelUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_ctl_panel_unit][%d]", t_ManagePoCtlPanelUnit->Count());		
	}

	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_DEPLOY_FILE;
		t_ManagePoDeployFile->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_deploy_file][%d]", t_ManagePoDeployFile->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_DEPLOY_FILE_PKG;
		t_ManagePoDeployFilePkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_deploy_file_pkg][%d]", t_ManagePoDeployFilePkg->Count());		

		m_tPktData->hdr.code = G_CODE_INIT_PO_DEPLOY_FILE_UNIT;
		t_ManagePoDeployFileUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_deploy_file_unit][%d]", t_ManagePoDeployFileUnit->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_DEPLOY_FILE_UNIT_INFO_PKG;
		t_ManagePoDeployFileUnitInfoPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_deploy_file_unit_info_pkg][%d]", t_ManagePoDeployFileUnitInfoPkg->Count());


		m_tPktData->hdr.code = G_CODE_INIT_PO_DEPLOY_FILE_UNIT_CHK_PKG;
		t_ManagePoDeployFileUnitChkPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_deploy_file_unit_chk_pkg][%d]", t_ManagePoDeployFileUnitChkPkg->Count());

		m_tPktData->hdr.code = G_CODE_INIT_PO_DEPLOY_FILE_UNIT_TAR_PKG;
		t_ManagePoDeployFileUnitTarPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_deploy_file_unit_tar_pkg][%d]", t_ManagePoDeployFileUnitTarPkg->Count());

		m_tPktData->hdr.code = G_CODE_INIT_PO_DEPLOY_FILE_UNIT_SCH_PKG;
		t_ManagePoDeployFileUnitSchPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_deploy_file_unit_sch_pkg][%d]", t_ManagePoDeployFileUnitSchPkg->Count());			

		m_tPktData->hdr.code = G_CODE_INIT_PO_DEPLOY_FILE_INFO_UNIT;
		t_ManagePoDeployFileInfoUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_deploy_file_unit_info_unit][%d]", t_ManagePoDeployFileInfoUnit->Count());		


		m_tPktData->hdr.code = G_CODE_INIT_PO_DEPLOY_FILE_CHK_UNIT;
		t_ManagePoDeployFileChkUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_deploy_file_unit_chk_unit][%d]", t_ManagePoDeployFileChkUnit->Count());		

		m_tPktData->hdr.code = G_CODE_INIT_PO_DEPLOY_FILE_TAR_UNIT;
		t_ManagePoDeployFileTarUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_deploy_file_unit_tar_unit][%d]", t_ManagePoDeployFileTarUnit->Count());		

		m_tPktData->hdr.code = G_CODE_INIT_PO_DEPLOY_FILE_SCH_UNIT;
		t_ManagePoDeployFileSchUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_deploy_file_unit_sch_unit][%d]", t_ManagePoDeployFileSchUnit->Count());	
	}
	return;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void		CLogicInitLink::SendPkt_Init_Policy_AC()
{
	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_CTL_PROC;
		t_ManagePoCtlProc->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_ctl_proc][%d]", t_ManagePoCtlProc->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_CTL_PROC_PKG;
		t_ManagePoCtlProcPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_ctl_proc_pkg][%d]", t_ManagePoCtlProcPkg->Count());		

		m_tPktData->hdr.code = G_CODE_INIT_PO_CTL_PROC_UNIT;
		t_ManagePoCtlProcUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_ctl_proc_unit][%d]", t_ManagePoCtlProcUnit->Count());		
	}

	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_SELF_PROTECT;
		t_ManagePoSelfProtect->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_self_protect][%d]", t_ManagePoSelfProtect->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_SELF_PROTECT_PKG;
		t_ManagePoSelfProtectPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_self_protect_pkg][%d]", t_ManagePoSelfProtectPkg->Count());		

		m_tPktData->hdr.code = G_CODE_INIT_PO_SELF_PROTECT_UNIT;
		t_ManagePoSelfProtectUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_self_protect_unit][%d]", t_ManagePoSelfProtectUnit->Count());	
	}
	return;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void		CLogicInitLink::SendPkt_Init_Policy_FA()
{
	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_FA_OP;
		t_ManagePoFaOp->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fa_op][%d]", t_ManagePoFaOp->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_FA_OP_PKG;
		t_ManagePoFaOpPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fa_op_pkg][%d]", t_ManagePoFaOpPkg->Count());		

		m_tPktData->hdr.code = G_CODE_INIT_PO_FA_OP_UNIT;
		t_ManagePoFaOpUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fa_op_unit][%d]", t_ManagePoFaOpUnit->Count());		

		m_tPktData->hdr.code = G_CODE_INIT_PO_FA_OP_UNIT_OBJ_PKG;
		t_ManagePoFaOpUnitObjPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fa_op_unit_obj_pkg][%d]", t_ManagePoFaOpUnitObjPkg->Count());		

		m_tPktData->hdr.code = G_CODE_INIT_PO_FA_OP_UNIT_SUB_PKG;
		t_ManagePoFaOpUnitSubPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fa_op_unit_sub_pkg][%d]", t_ManagePoFaOpUnitSubPkg->Count());		

		m_tPktData->hdr.code = G_CODE_INIT_PO_FA_OP_UNIT_SCH_PKG;
		t_ManagePoFaOpUnitSchPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fa_op_unit_sch_pkg][%d]", t_ManagePoFaOpUnitSchPkg->Count());		

		m_tPktData->hdr.code = G_CODE_INIT_PO_FA_OP_UNIT_RUL_PKG;
		t_ManagePoFaOpUnitRulPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fa_op_unit_rul_pkg][%d]", t_ManagePoFaOpUnitRulPkg->Count());



		m_tPktData->hdr.code = G_CODE_INIT_PO_FA_OP_OBJ_UNIT;
		t_ManagePoFaOpObjUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fa_op_obj_unit][%d]", t_ManagePoFaOpObjUnit->Count());		

		m_tPktData->hdr.code = G_CODE_INIT_PO_FA_OP_SUB_UNIT;
		t_ManagePoFaOpSubUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fa_op_sub_unit][%d]", t_ManagePoFaOpSubUnit->Count());		

		m_tPktData->hdr.code = G_CODE_INIT_PO_FA_OP_SCH_UNIT;
		t_ManagePoFaOpSchUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fa_op_sch_unit][%d]", t_ManagePoFaOpSchUnit->Count());	
	}

	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_FA_CLEAR;
		t_ManagePoFaClear->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fa_clear][%d]", t_ManagePoFaClear->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_FA_CLEAR_PKG;
		t_ManagePoFaClearPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fa_clear_pkg][%d]", t_ManagePoFaClearPkg->Count());		

		m_tPktData->hdr.code = G_CODE_INIT_PO_FA_CLEAR_UNIT;
		t_ManagePoFaClearUnit->SetPkt_Link(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fa_clear_unit][%d]", t_ManagePoFaClearUnit->Count());		
	}

	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_FA_PROC;
		t_ManagePoFaProc->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fa_proc][%d]", t_ManagePoFaProc->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_FA_PROC_PKG;
		t_ManagePoFaProcPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fa_proc_pkg][%d]", t_ManagePoFaProcPkg->Count());		

		m_tPktData->hdr.code = G_CODE_INIT_PO_FA_PROC_UNIT;
		t_ManagePoFaProcUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fa_proc_unit][%d]", t_ManagePoFaProcUnit->Count());		
	}

	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_FA_ENV;
		t_ManagePoFaEnv->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fa_env][%d]", t_ManagePoFaEnv->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_FA_ENV_PKG;
		t_ManagePoFaEnvPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fa_env_pkg][%d]", t_ManagePoFaEnvPkg->Count());		

		m_tPktData->hdr.code = G_CODE_INIT_PO_FA_ENV_UNIT;
		t_ManagePoFaEnvUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fa_env_unit][%d]", t_ManagePoFaEnvUnit->Count());		
	}

	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_FA_BK;
		t_ManagePoFaBk->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fa_bk][%d]", t_ManagePoFaBk->Count());	
	}

	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_FA_NOTIFY;
		t_ManagePoFaNotify->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fa_notify][%d]", t_ManagePoFaNotify->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_FA_NOTIFY_PKG;
		t_ManagePoFaNotifyPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fa_notify_pkg][%d]", t_ManagePoFaNotifyPkg->Count());	
	}
	return;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void		CLogicInitLink::SendPkt_Init_Policy_FE()
{
	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_FE_PTN_OP;
		t_ManagePoFePtnOp->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fe_ptn_op][%d]", t_ManagePoFePtnOp->Count());	
	}

	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_FE_PTN_LO;
		t_ManagePoFePtnLo->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fe_ptn_lo][%d]", t_ManagePoFePtnLo->Count());	
	}

	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_FE_PTN_BL;
		t_ManagePoFePtnBL->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fe_ptn_bl][%d]", t_ManagePoFePtnBL->Count());	
	}

	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_FE_PTN_WL;
		t_ManagePoFePtnWL->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fe_ptn_wl][%d]", t_ManagePoFePtnWL->Count());	
	}

	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_FE_EXCLUDE;
		t_ManagePoFeExclude->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fe_exclude][%d]", t_ManagePoFeExclude->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_FE_EXCLUDE_PKG;
		t_ManagePoFeExcludePkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fe_exclude_pkg][%d]", t_ManagePoFeExcludePkg->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_FE_EXCLUDE_UNIT;
		t_ManagePoFeExcludeUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fe_exclude_unit][%d]", t_ManagePoFeExcludeUnit->Count());	
	}

	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_FE_NOTIFY;
		t_ManagePoFeNotify->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fe_notify][%d]", t_ManagePoFeNotify->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_FE_NOTIFY_PKG;
		t_ManagePoFeNotifyPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fe_notify_pkg][%d]", t_ManagePoFeNotifyPkg->Count());			
	}

	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_FE_SINGLE_PTN;
		t_ManagePoFeSinglePtn->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fe_single_ptn][%d]", t_ManagePoFeSinglePtn->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_FE_SINGLE_PTN_UNIT;
		t_ManagePoFeSinglePtnUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_fe_notify_unit][%d]", t_ManagePoFeSinglePtnUnit->Count());			
	}
	return;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void		CLogicInitLink::SendPkt_Init_Policy_IN()
{
	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_PTN_OP;
		t_ManagePoInPtnOp->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ptn_op][%d]", t_ManagePoInPtnOp->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_PTN_OP_PKG;
		t_ManagePoInPtnOpPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ptn_op_pkg][%d]", t_ManagePoInPtnOpPkg->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_PTN_OP_UNIT;
		t_ManagePoInPtnOpUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ptn_op_unit][%d]", t_ManagePoInPtnOpUnit->Count());		
		///////////////////////////////////////////////////////////////////////////////////////////////	
		///////////////////////////////////////////////////////////////////////////////////////////////
		
		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_PTN_BL;
		t_ManagePoInPtnBL->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ptn_bl][%d]", t_ManagePoInPtnBL->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_PTN_BL_PKG;
		t_ManagePoInPtnBLPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ptn_bl_pkg][%d]", t_ManagePoInPtnBLPkg->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_PTN_BL_UNIT;
		t_ManagePoInPtnBLUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ptn_bl_unit][%d]", t_ManagePoInPtnBLUnit->Count());	
		///////////////////////////////////////////////////////////////////////////////////////////////	
		///////////////////////////////////////////////////////////////////////////////////////////////

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_PTN_WL;
		t_ManagePoInPtnWL->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ptn_wl][%d]", t_ManagePoInPtnWL->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_PTN_WL_PKG;
		t_ManagePoInPtnWLPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ptn_wl_pkg][%d]", t_ManagePoInPtnWLPkg->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_PTN_WL_UNIT;
		t_ManagePoInPtnWLUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ptn_wl_unit][%d]", t_ManagePoInPtnWLUnit->Count());		
		///////////////////////////////////////////////////////////////////////////////////////////////	
		///////////////////////////////////////////////////////////////////////////////////////////////

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_PTN_EX;
		t_ManagePoInPtnEx->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ptn_ex][%d]", t_ManagePoInPtnEx->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_PTN_EX_PKG;
		t_ManagePoInPtnExPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ptn_ex_pkg][%d]", t_ManagePoInPtnExPkg->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_PTN_EX_UNIT;
		t_ManagePoInPtnExUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ptn_ex_unit][%d]", t_ManagePoInPtnExUnit->Count());	
		///////////////////////////////////////////////////////////////////////////////////////////////	
		///////////////////////////////////////////////////////////////////////////////////////////////

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_PTN_SP;
		t_ManagePoInPtnSP->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ptn_sp][%d]", t_ManagePoInPtnSP->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_PTN_SP_PKG;
		t_ManagePoInPtnSPPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ptn_sp_pkg][%d]", t_ManagePoInPtnSPPkg->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_PTN_SP_UNIT;
		t_ManagePoInPtnSPUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ptn_sp_unit][%d]", t_ManagePoInPtnSPUnit->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_PTN_SP_RULE;
		t_ManagePoInPtnSPRule->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ptn_sp_rule][%d]", t_ManagePoInPtnSPRule->Count());	
		///////////////////////////////////////////////////////////////////////////////////////////////	
		///////////////////////////////////////////////////////////////////////////////////////////////

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_PTN_NO;
		t_ManagePoInPtnNo->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ptn_no][%d]", t_ManagePoInPtnNo->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_PTN_NO_PKG;
		t_ManagePoInPtnNoPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ptn_no_pkg][%d]", t_ManagePoInPtnNoPkg->Count());	
	}	
	
	return;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void		CLogicInitLink::SendPkt_Init_Policy_IN_AC()
{
	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_AC_DOC;
		t_ManagePoInAcDoc->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ac_doc][%d]", t_ManagePoInAcDoc->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_AC_DOC_PKG;
		t_ManagePoInAcDocPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ac_doc_pkg][%d]", t_ManagePoInAcDocPkg->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_AC_DOC_UNIT;
		t_ManagePoInAcDocUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ac_doc_unit][%d]", t_ManagePoInAcDocUnit->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_AC_DOC_UNIT_SUB_PKG;
		t_ManagePoInAcDocUnitSubPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ac_doc_unit_sub_pkg][%d]", t_ManagePoInAcDocUnitSubPkg->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_AC_DOC_UNIT_OBJ_PKG;
		t_ManagePoInAcDocUnitObjPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ac_doc_unit_obj_pkg][%d]", t_ManagePoInAcDocUnitObjPkg->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_AC_DOC_SUB_UNIT;
		t_ManagePoInAcDocSubUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ac_doc_sub_unit][%d]", t_ManagePoInAcDocSubUnit->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_AC_DOC_OBJ_UNIT;
		t_ManagePoInAcDocObjUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ac_doc_obj_unit][%d]", t_ManagePoInAcDocObjUnit->Count());	
		///////////////////////////////////////////////////////////////////////////////////////////////	
		///////////////////////////////////////////////////////////////////////////////////////////////

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_AC_SF;
		t_ManagePoInAcSf->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ac_sf][%d]", t_ManagePoInAcSf->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_AC_SF_PKG;
		t_ManagePoInAcSfPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ac_sf_pkg][%d]", t_ManagePoInAcSfPkg->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_AC_SF_UNIT;
		t_ManagePoInAcSfUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ac_sf_unit][%d]", t_ManagePoInAcSfUnit->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_AC_SF_UNIT_SUB_PKG;
		t_ManagePoInAcSfUnitSubPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ac_sf_unit_sub_pkg][%d]", t_ManagePoInAcSfUnitSubPkg->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_AC_SF_UNIT_OBJ_PKG;
		t_ManagePoInAcSfUnitObjPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ac_sf_unit_obj_pkg][%d]", t_ManagePoInAcSfUnitObjPkg->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_AC_SF_SUB_UNIT;
		t_ManagePoInAcSfSubUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ac_sf_sub_unit][%d]", t_ManagePoInAcSfSubUnit->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_AC_SF_OBJ_UNIT;
		t_ManagePoInAcSfObjUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ac_sf_obj_unit][%d]", t_ManagePoInAcSfObjUnit->Count());	
		///////////////////////////////////////////////////////////////////////////////////////////////	
		///////////////////////////////////////////////////////////////////////////////////////////////

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_AC_FILE;
		t_ManagePoInAcFile->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ac_file][%d]", t_ManagePoInAcFile->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_AC_FILE_PKG;
		t_ManagePoInAcFilePkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ac_file_pkg][%d]", t_ManagePoInAcFilePkg->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_AC_FILE_UNIT;
		t_ManagePoInAcFileUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ac_file_unit][%d]", t_ManagePoInAcFileUnit->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_AC_FILE_UNIT_SUB_PKG;
		t_ManagePoInAcFileUnitSubPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ac_file_unit_sub_pkg][%d]", t_ManagePoInAcFileUnitSubPkg->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_AC_FILE_UNIT_OBJ_PKG;
		t_ManagePoInAcFileUnitObjPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ac_file_unit_obj_pkg][%d]", t_ManagePoInAcFileUnitObjPkg->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_AC_FILE_UNIT_SCH_PKG;
		t_ManagePoInAcFileUnitSchPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ac_file_unit_sch_pkg][%d]", t_ManagePoInAcFileUnitSchPkg->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_AC_FILE_UNIT_RUL_PKG;
		t_ManagePoInAcFileUnitRulPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ac_file_unit_rule_pkg][%d]", t_ManagePoInAcFileUnitRulPkg->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_AC_FILE_SUB_UNIT;
		t_ManagePoInAcFileSubUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ac_file_sub_unit][%d]", t_ManagePoInAcFileSubUnit->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_AC_FILE_OBJ_UNIT;
		t_ManagePoInAcFileObjUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ac_doc_file_unit][%d]", t_ManagePoInAcFileObjUnit->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_AC_FILE_SCH_UNIT;
		t_ManagePoInAcFileSchUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_ac_doc_sch_unit][%d]", t_ManagePoInAcFileSchUnit->Count());	
		///////////////////////////////////////////////////////////////////////////////////////////////	
		///////////////////////////////////////////////////////////////////////////////////////////////
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void		CLogicInitLink::SendPkt_Init_Policy_IN_VULN()
{
	{
		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_VULN_OP;
		t_ManagePoInVulnOp->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_vuln_op][%d]", t_ManagePoInVulnOp->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_VULN_OP_PKG;
		t_ManagePoInVulnOpPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_vuln_op_pkg][%d]", t_ManagePoInVulnOpPkg->Count());	
		///////////////////////////////////////////////////////////////////////////////////////////////	
		///////////////////////////////////////////////////////////////////////////////////////////////

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_VULN_SCAN;
		t_ManagePoInVulnScan->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_vuln_scan][%d]", t_ManagePoInVulnScan->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_VULN_SCAN_PKG;
		t_ManagePoInVulnScanPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_vuln_scan_pkg][%d]", t_ManagePoInVulnScanPkg->Count());	

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_VULN_SCAN_UNIT;
		t_ManagePoInVulnScanUnit->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_vuln_scan_unit][%d]", t_ManagePoInVulnScanUnit->Count());

		m_tPktData->hdr.code = G_CODE_INIT_PO_IN_VULN_SCAN_UNIT_PKG;
		t_ManagePoInVulnScanUnitPkg->SetPkt(SendToken);
		SendData_Link(m_tPktData, SendToken);
		SendToken.Clear();
		WriteLogN("[logic init] send init link data [po_in_vuln_scan_unit_pkg][%d]", t_ManagePoInVulnScanUnitPkg->Count());
		///////////////////////////////////////////////////////////////////////////////////////////////	
		///////////////////////////////////////////////////////////////////////////////////////////////

	}	

	return;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------



