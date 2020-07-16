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
#include "LogicBase.h"

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void	CLogicBase::SendData_Link(UINT16 nType, UINT16 nCode, MemToken& SendToken)
{
	TListID tIDList;
	t_ManageLinkLicense->GetSIDList(tIDList);
	
	TListIDItor begin, end;
	begin = tIDList.begin();	end = tIDList.end();
	for(begin; begin != end; begin++)
	{		
		SendData_Link(*begin, nType, nCode, SendToken);
	}
	return;
}
//---------------------------------------------------------------------------

void	CLogicBase::SendData_Link(UINT32 nID, UINT16 nType, UINT16 nCode, MemToken& SendToken)
{
	t_LinkSvrUtil->SendData(nID, nType, nCode, SendToken.GetLength(), SendToken.GetData());
}
//---------------------------------------------------------------------------

void	CLogicBase::SendData_Link(TListID& tIDList, UINT16 nType, UINT16 nCode, MemToken& SendToken)
{
	TListIDItor begin, end;
	begin = tIDList.begin();	end = tIDList.end();
	for(begin; begin != end; begin++)
	{
		SendData_Link(*begin, nType, nCode, SendToken);
	}
	return;
}
//---------------------------------------------------------------------------

void	CLogicBase::SendData_Link(PPKT_DATA pkt_data, MemToken& SendToken)
{
	if(pkt_data->nSessionID)
	{
		SendData_Link(pkt_data->nSessionID, pkt_data->hdr.type, pkt_data->hdr.code, SendToken);
	}
	else
	{
		SendData_Link(pkt_data->hdr.type, pkt_data->hdr.code, SendToken);
	}
	return;
}
//---------------------------------------------------------------------------

void	CLogicBase::SendData_Link(PPKT_DATA pkt_data, MemToken& SendToken, TListID& tIDList)
{
	TListIDItor begin, end;
	begin = tIDList.begin();	end = tIDList.end();
	for(begin; begin != end; begin++)
	{
		SendData_Link(*begin, pkt_data->hdr.type, pkt_data->hdr.code, SendToken);
	}
	return;
}
//---------------------------------------------------------------------------

void	CLogicBase::EditSID_Link(INT32 nOldID, INT32 nNewID)
{
	t_LinkSvrUtil->EditSessionID(nOldID, nNewID);

    return;
}
//---------------------------------------------------------------------------

INT32	CLogicBase::ExistsID_Link(UINT32 nID)
{
    INT32 nRtnN = t_LinkSvrUtil->IsExistsSessionID(nID);
    if(nRtnN)
    {
    	if(nRtnN == 1)	return 1;
    }
	return 0;
}
//---------------------------------------------------------------------------

void	CLogicBase::EditSKey_Link(INT32 nID, UINT32 nSessionKey)
{
	t_LinkSvrUtil->EditSessionKey(nID, nSessionKey);
    return;
}
//---------------------------------------------------------------------------

void	CLogicBase::Disconnected_Link(INT32 nID, INT32 nRemainPkt)
{
	t_LinkSvrUtil->CloseSocket(nID, nRemainPkt);
	return;
}
//---------------------------------------------------------------------------

void	CLogicBase::Disconnected_Link(TListID& tHIDList)
{
	TListIDItor begin, end;
    begin = tHIDList.begin();	end = tHIDList.end();
    for(begin; begin != end; begin++)
    {
		Disconnected_Link(*begin);
    }
    return;
}
//---------------------------------------------------------------------------

String	CLogicBase::GetHostAddr_Link(INT32 nID)
{
	char pszAddr[CHAR_MAX_SIZE] = {0, };
	t_LinkSvrUtil->GetSocketAddress(nID, pszAddr);

	return String(pszAddr);
}
//---------------------------------------------------------------------------

UINT32	CLogicBase::GetHostIP_Link(INT32 nID)
{
	UINT32 nAddr = 0;
	t_LinkSvrUtil->GetSocketAddressUINT(nID, nAddr);

    return nAddr;
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

void	CLogicBase::AnalyzePkt_FromLink(PPKT_DATA pkt_data)
{
	InitBaseMember(pkt_data);
	switch(m_nPktCode)
	{
		case G_CODE_COMMON_ADD:					AnalyzePkt_FromLink_Add();		break;
		case G_CODE_COMMON_EDIT:				AnalyzePkt_FromLink_Edit();		break;
		case G_CODE_COMMON_DEL:					AnalyzePkt_FromLink_Del();		break;
		default:								AnalyzePkt_FromLink_Ext();		break;		
	}
	InitBaseMember();
	return;
}
//---------------------------------------------------------------------------

void	CLogicBase::AnalyzePkt_FromLink_Add()
{
	m_nEvtOpType = EVENT_OPERATION_TYPE_ADD;	

	INT32 nPktRst = AnalyzePkt_FromLink_Add_Ext();
	switch(nPktRst)
	{
		case AZPKT_CB_RTN_SUCCESS:				break;
		case AZPKT_CB_RTN_SUCCESS_END:			return;
		case AZPKT_CB_RTN_SUCCESS_MADE_PKT:
		{
			SendData_Link(m_nSessionID, m_nPktType, m_nPktCode, SendToken);		
			goto SEND_PKT;
		}
		case AZPKT_CB_RTN_PKT_INVALID:
		{
			WriteLogE("[%s] recv invalid pkt from link : [%x][%x]:[%d]", m_strLogicName.c_str(), m_nPktType, m_nPktCode, m_nDbgPos);
			SendToken.TokenAdd_32(ERR_SOCKET_CLT_TO_SVR_INVALID_PKT);	
			goto SEND_PKT;
		}
		case AZPKT_CB_RTN_PKT_NOT_DEFINE_CODE:
		{
			WriteLogE("[%s] recv not define pkt code from link : [%x][%x]:[%d]", m_strLogicName.c_str(), m_nPktType, m_nPktCode, m_nDbgPos);
			SendToken.TokenAdd_32(ERR_SOCKET_CLT_TO_SVR_INVALID_PKT);	
			goto SEND_PKT;
		}
		case AZPKT_CB_RTN_SEND_ACK:
		{
			goto SEND_PKT;
		}
	}

	SendToken.TokenAdd_32(ERR_SUCCESS);
	return;

SEND_PKT:
	SendData_Link(m_tPktData, SendToken);
	return;
}
//---------------------------------------------------------------------------

void	CLogicBase::AnalyzePkt_FromLink_Edit()
{	
	m_nEvtOpType = EVENT_OPERATION_TYPE_EDIT;	

	INT32 nPktRst = AnalyzePkt_FromLink_Edit_Ext();
	switch(nPktRst)
	{
		case AZPKT_CB_RTN_SUCCESS:				break;
		case AZPKT_CB_RTN_SUCCESS_END:			return;
		case AZPKT_CB_RTN_SUCCESS_MADE_PKT:
		{
			SendData_Link(m_nSessionID, m_nPktType, m_nPktCode, SendToken);		
			goto SEND_PKT;
		}
		case AZPKT_CB_RTN_PKT_INVALID:
		{
			WriteLogE("[%s] recv invalid pkt from link : [%x][%x]:[%d]", m_strLogicName.c_str(), m_nPktType, m_nPktCode, m_nDbgPos);
			SendToken.TokenAdd_32(ERR_SOCKET_CLT_TO_SVR_INVALID_PKT);	
			goto SEND_PKT;
		}
		case AZPKT_CB_RTN_PKT_NOT_DEFINE_CODE:
		{
			WriteLogE("[%s] recv not define pkt code from link : [%x][%x]:[%d]", m_strLogicName.c_str(), m_nPktType, m_nPktCode, m_nDbgPos);
			SendToken.TokenAdd_32(ERR_SOCKET_CLT_TO_SVR_INVALID_PKT);	
			goto SEND_PKT;
		}
		case AZPKT_CB_RTN_SEND_ACK:
		{
			goto SEND_PKT;
		}
	}

	SendToken.TokenAdd_32(ERR_SUCCESS);
	return;

SEND_PKT:
	SendData_Link(m_tPktData, SendToken);
	return;
}
//---------------------------------------------------------------------------

void	CLogicBase::AnalyzePkt_FromLink_Del()
{
	m_nEvtOpType = EVENT_OPERATION_TYPE_DEL;	

	INT32 nPktRst = AnalyzePkt_FromLink_Del_Ext();
	switch(nPktRst)
	{
		case AZPKT_CB_RTN_SUCCESS:				break;
		case AZPKT_CB_RTN_SUCCESS_END:			return;
		case AZPKT_CB_RTN_SUCCESS_MADE_PKT:
		{
			SendData_Link(m_nSessionID, m_nPktType, m_nPktCode, SendToken);		
			goto SEND_PKT;
		}
		case AZPKT_CB_RTN_PKT_INVALID:
		{
			WriteLogE("[%s] recv invalid pkt from link : [%x][%x]:[%d]", m_strLogicName.c_str(), m_nPktType, m_nPktCode, m_nDbgPos);
			SendToken.TokenAdd_32(ERR_SOCKET_CLT_TO_SVR_INVALID_PKT);	
			goto SEND_PKT;
		}
		case AZPKT_CB_RTN_PKT_NOT_DEFINE_CODE:
		{
			WriteLogE("[%s] recv not define pkt code from link : [%x][%x]:[%d]", m_strLogicName.c_str(), m_nPktType, m_nPktCode, m_nDbgPos);
			SendToken.TokenAdd_32(ERR_SOCKET_CLT_TO_SVR_INVALID_PKT);	
			goto SEND_PKT;
		}
		case AZPKT_CB_RTN_SEND_ACK:
		{
			goto SEND_PKT;
		}
	}

	SendToken.TokenAdd_32(ERR_SUCCESS);
	return;

SEND_PKT:
	SendData_Link(m_tPktData, SendToken);
	return;
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

INT32	CLogicBase::SendPktToLink()
{
	PKT_DATA tPktData = *m_tPktData;
	tPktData.nSessionID = 0;	

	switch(m_nControlType)
	{
		case SS_CONTROL_TYPE_ENV_NOTIFY_INFO:
		{
			tPktData.hdr.type = G_TYPE_INIT;
			tPktData.hdr.code = G_CODE_INIT_ENV_NOTIFY_INFO;
			t_ManageEnvNotifyInfo->SetPkt(SendToken);
			SendData_Link(&tPktData, SendToken);
			SendToken.Clear();
			WriteLogN("[logic link] send sync link data [env_notify_info][%d]", t_ManageEnvNotifyInfo->Count());	
			break;
		}
	}
	
	switch(m_nPolicyType)
	{
		case SS_POLICY_TYPE_HOST_RM_INFO:
		{			
			PDB_PO_HOST_RM_INFO pCurPolicy = (PDB_PO_HOST_RM_INFO)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_HOST_RM_INFO);
			if(!pCurPolicy)
			{
				WriteLogE("[%s] set po host rm info fail : not find cur policy", m_strLogicName.c_str());
				break;
			}

			t_ManagePoHostRmInfo->SetPkt(pCurPolicy->tDPH.nID, SendToken);
			SendData_Link(&tPktData, SendToken);
			SendToken.Clear();
			WriteLogN("[logic link] send sync link data [po_host_rm_info][%d]", t_ManagePoHostRmInfo->Count());	
			break;
		}
		case SS_POLICY_TYPE_HOST_RUN:
		{			
			PDB_PO_HOST_RUN pCurPolicy = (PDB_PO_HOST_RUN)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_HOST_RUN);
			if(!pCurPolicy)
			{
				WriteLogE("[%s] set po host run fail : not find cur policy", m_strLogicName.c_str());
				break;
			}

			t_ManagePoHostRun->SetPkt(pCurPolicy->tDPH.nID, SendToken);
			SendData_Link(&tPktData, SendToken);
			SendToken.Clear();
			WriteLogN("[logic link] send sync link data [po_host_run][%d]", t_ManagePoHostRun->Count());	
			break;
		}
		case SS_POLICY_TYPE_SVR_INFO_LGN:
		{			
			PDB_PO_SVR_INFO_LGN pCurPolicy = (PDB_PO_SVR_INFO_LGN)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_SVR_INFO_LGN);
			if(!pCurPolicy)
			{
				WriteLogE("[%s] set po svr info lgn fail : not find cur policy", m_strLogicName.c_str());
				break;
			}

			t_ManagePoSvrInfoLgn->SetPkt(pCurPolicy->tDPH.nID, SendToken);
			SendData_Link(&tPktData, SendToken);
			SendToken.Clear();
			WriteLogN("[logic link] send sync link data [po_svr_info_lgn][%d]", t_ManagePoSvrInfoLgn->Count());	
			break;
		}
		case SS_POLICY_TYPE_SVR_INFO_UDT:
		{			
			PDB_PO_SVR_INFO_UDT pCurPolicy = (PDB_PO_SVR_INFO_UDT)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_SVR_INFO_UDT);
			if(!pCurPolicy)
			{
				WriteLogE("[%s] set po svr info udt fail : not find cur policy", m_strLogicName.c_str());
				break;
			}

			t_ManagePoSvrInfoUdt->SetPkt(pCurPolicy->tDPH.nID, SendToken);
			SendData_Link(&tPktData, SendToken);
			SendToken.Clear();
			WriteLogN("[logic link] send sync link data [po_svr_info_udt][%d]", t_ManagePoSvrInfoUdt->Count());	
			break;
		}
		case SS_POLICY_TYPE_SCH:
		{			
			PDB_PO_SCH pCurPolicy = (PDB_PO_SCH)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_SCH);
			if(!pCurPolicy)
			{
				WriteLogE("[%s] set po sch fail : not find cur policy", m_strLogicName.c_str());
				break;
			}

			t_ManagePoSch->SetPktHost(pCurPolicy->tDPH.nID, SendToken);
			SendData_Link(&tPktData, SendToken);
			SendToken.Clear();
			WriteLogN("[logic link] send sync link data [po_sch][%d]", t_ManagePoSch->Count());			
			break;
		}

		case SS_POLICY_TYPE_POWER:
		{	
			PDB_PO_POWER pCurPolicy = (PDB_PO_POWER)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_POWER);
			if(!pCurPolicy)
			{
				WriteLogE("[%s] set po power fail : not find cur policy", m_strLogicName.c_str());
				break;
			}

			t_ManagePoPower->SetPktHost(pCurPolicy->tDPH.nID, SendToken);
			SendData_Link(&tPktData, SendToken);
			SendToken.Clear();
			WriteLogN("[logic link] send sync link data [po_power][%d]", t_ManagePoPower->Count());
			break;
		}
		case SS_POLICY_TYPE_WIN_RUN:
		{			
			PDB_PO_WIN_RUN pCurPolicy = (PDB_PO_WIN_RUN)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_WIN_RUN);
			if(!pCurPolicy)
			{
				WriteLogE("[%s] set po win run fail : not find cur policy", m_strLogicName.c_str());
				break;
			}

			t_ManagePoWinRun->SetPkt(pCurPolicy->tDPH.nID, SendToken);
			SendData_Link(&tPktData, SendToken);
			SendToken.Clear();
			WriteLogN("[logic link] send sync link data [po_win_run][%d]", t_ManagePoWinRun->Count());
			break;
		}
		case SS_POLICY_TYPE_CTL_PANEL:
		{			
			PDB_PO_CTL_PANEL pCurPolicy = (PDB_PO_CTL_PANEL)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_CTL_PANEL);
			if(!pCurPolicy)
			{
				WriteLogE("[%s] set po ctl panel fail : not find cur policy", m_strLogicName.c_str());
				break;
			}

			t_ManagePoCtlPanel->SetPktHost(pCurPolicy->tDPH.nID, SendToken);
			SendData_Link(&tPktData, SendToken);
			SendToken.Clear();
			WriteLogN("[logic link] send sync link data [po_ctl_panel][%d]", t_ManagePoCtlPanel->Count());
			break;
		}
		case SS_POLICY_TYPE_DEPLOY_FILE:
		{			
			PDB_PO_DEPLOY_FILE pCurPolicy = (PDB_PO_DEPLOY_FILE)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_DEPLOY_FILE);
			if(!pCurPolicy)
			{
				WriteLogE("[%s] set po depoly file fail : not find cur policy", m_strLogicName.c_str());
				break;
			}

			t_ManagePoDeployFile->SetPktHost(pCurPolicy->tDPH.nID, SendToken);
			SendData_Link(&tPktData, SendToken);
			SendToken.Clear();
			WriteLogN("[logic link] send sync link data [po_deploy_file][%d]", t_ManagePoDeployFile->Count());				
			break;
		}
		case SS_POLICY_TYPE_CTL_PROC:
		{			
			PDB_PO_CTL_PROC pCurPolicy = (PDB_PO_CTL_PROC)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_CTL_PROC);
			if(!pCurPolicy)
			{
				WriteLogE("[%s] set po ctl proc fail : not find cur policy", m_strLogicName.c_str());
				break;
			}

			t_ManagePoCtlProc->SetPktHost(pCurPolicy->tDPH.nID, SendToken);
			SendData_Link(&tPktData, SendToken);
			SendToken.Clear();
			WriteLogN("[logic link] send sync link data [po_ctl_proc][%d]", t_ManagePoCtlProc->Count());		
			break;
		}
		case SS_POLICY_TYPE_SELF_PROTECT:
		{		
			PDB_PO_SELF_PROTECT pCurPolicy = (PDB_PO_SELF_PROTECT)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_SELF_PROTECT);
			if(!pCurPolicy)
			{
				WriteLogE("[%s] set po self protect fail : not find cur policy", m_strLogicName.c_str());
				break;
			}

			t_ManagePoSelfProtect->SetPktHost(pCurPolicy->tDPH.nID, SendToken);
			SendData_Link(&tPktData, SendToken);
			SendToken.Clear();
			WriteLogN("[logic link] send sync link data [po_self_protect][%d]", t_ManagePoSelfProtect->Count());		
			break;
		}
		case SS_POLICY_TYPE_FA_OP:
		{			
			PDB_PO_FA_OP pCurPolicy = (PDB_PO_FA_OP)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_FA_OP);
			if(!pCurPolicy)
			{
				WriteLogE("[%s] set po fa op fail : not find cur policy", m_strLogicName.c_str());
				break;
			}

			t_ManagePoFaOp->SetPktHost(pCurPolicy->tDPH.nID, SendToken);
			SendData_Link(&tPktData, SendToken);
			SendToken.Clear();
			WriteLogN("[logic link] send sync link data [po_fa_op][%d]", t_ManagePoFaOp->Count());	
			break;
		}
		case SS_POLICY_TYPE_FA_CLEAR:
		{		
			PDB_PO_FA_CLEAR pCurPolicy = (PDB_PO_FA_CLEAR)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_FA_CLEAR);
			if(!pCurPolicy)
			{
				WriteLogE("[%s] set po fa clear fail : not find cur policy", m_strLogicName.c_str());
				break;
			}

			t_ManagePoFaClear->SetPktHost(pCurPolicy->tDPH.nID, SendToken);
			SendData_Link(&tPktData, SendToken);
			SendToken.Clear();
			WriteLogN("[logic link] send sync link data [po_fa_clear][%d]", t_ManagePoFaClear->Count());	
			break;
		}
		case SS_POLICY_TYPE_FA_ENV:
		{		
			PDB_PO_FA_ENV pCurPolicy = (PDB_PO_FA_ENV)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_FA_ENV);
			if(!pCurPolicy)
			{
				WriteLogE("[%s] set po fa env fail : not find cur policy", m_strLogicName.c_str());
				break;
			}

			t_ManagePoFaEnv->SetPktHost(pCurPolicy->tDPH.nID, SendToken);
			SendData_Link(&tPktData, SendToken);
			SendToken.Clear();
			WriteLogN("[logic link] send sync link data [po_fa_env][%d]", t_ManagePoFaEnv->Count());	
			break;
		}
		case SS_POLICY_TYPE_FA_PROC:
		{		
			PDB_PO_FA_PROC pCurPolicy = (PDB_PO_FA_PROC)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_FA_PROC);
			if(!pCurPolicy)
			{
				WriteLogE("[%s] set po fa proc fail : not find cur policy", m_strLogicName.c_str());
				break;
			}

			t_ManagePoFaProc->SetPktHost(pCurPolicy->tDPH.nID, SendToken);
			SendData_Link(&tPktData, SendToken);
			SendToken.Clear();
			WriteLogN("[logic link] send sync link data [po_fa_proc][%d]", t_ManagePoFaProc->Count());		
			break;
		}
		case SS_POLICY_TYPE_FA_BK:
		{		
			PDB_PO_FA_BK pCurPolicy = (PDB_PO_FA_BK)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_FA_BK);
			if(!pCurPolicy)
			{
				WriteLogE("[%s] set po fa bk fail : not find cur policy", m_strLogicName.c_str());
				break;
			}

			t_ManagePoFaBk->SetPkt(pCurPolicy->tDPH.nID, SendToken);
			SendData_Link(&tPktData, SendToken);
			SendToken.Clear();
			WriteLogN("[logic link] send sync link data [po_fa_bk][%d]", t_ManagePoFaBk->Count());	
			break;
		}
		case SS_POLICY_TYPE_FA_NOTIFY:
		{		
			PDB_PO_FA_NOTIFY pCurPolicy = (PDB_PO_FA_NOTIFY)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_FA_NOTIFY);
			if(!pCurPolicy)
			{
				WriteLogE("[%s] set po fa notify fail : not find cur policy", m_strLogicName.c_str());
				break;
			}

			t_ManagePoFaNotify->SetPktHost(pCurPolicy->tDPH.nID, SendToken);
			SendData_Link(&tPktData, SendToken);
			SendToken.Clear();
			WriteLogN("[logic link] send sync link data [po_fa_Notify][%d]", t_ManagePoFaNotify->Count());		
			break;
		}
		case SS_POLICY_TYPE_FE_PTN_OP:
		{		
			PDB_PO_FE_PTN_OP pCurPolicy = (PDB_PO_FE_PTN_OP)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_FE_PTN_OP);
			if(!pCurPolicy)
			{
				WriteLogE("[%s] set po fe ptn op fail : not find cur policy", m_strLogicName.c_str());
				break;
			}

			t_ManagePoFePtnOp->SetPkt(pCurPolicy->tDPH.nID, SendToken);
			SendData_Link(&tPktData, SendToken);
			SendToken.Clear();
			WriteLogN("[logic link] send sync link data [po_fe_ptn_op][%d]", t_ManagePoFePtnOp->Count());	
			break;
		}
		case SS_POLICY_TYPE_FE_PTN_LO:
		{			
			PDB_PO_FE_PTN_LO pCurPolicy = (PDB_PO_FE_PTN_LO)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_FE_PTN_LO);
			if(!pCurPolicy)
			{
				WriteLogE("[%s] set po fe ptn lo fail : not find cur policy", m_strLogicName.c_str());
				break;
			}

			t_ManagePoFePtnLo->SetPkt(pCurPolicy->tDPH.nID, SendToken);
			SendData_Link(&tPktData, SendToken);
			SendToken.Clear();
			WriteLogN("[logic link] send sync link data [po_fe_ptn_lo][%d]", t_ManagePoFePtnLo->Count());	
			break;
		}
		case SS_POLICY_TYPE_FE_PTN_BL:
		{			
			PDB_PO_FE_PTN_BL pCurPolicy = (PDB_PO_FE_PTN_BL)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_FE_PTN_BL);
			if(!pCurPolicy)
			{
				WriteLogE("[%s] set po fe ptn bl fail : not find cur policy", m_strLogicName.c_str());
				break;
			}

			t_ManagePoFePtnBL->SetPkt(pCurPolicy->tDPH.nID, SendToken);
			SendData_Link(&tPktData, SendToken);
			SendToken.Clear();
			WriteLogN("[logic link] send sync link data [po_fe_ptn_bl][%d]", t_ManagePoFePtnBL->Count());	
			break;
		}
		case SS_POLICY_TYPE_FE_PTN_WL:
		{			
			PDB_PO_FE_PTN_WL pCurPolicy = (PDB_PO_FE_PTN_WL)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_FE_PTN_WL);
			if(!pCurPolicy)
			{
				WriteLogE("[%s] set po fe ptn wl fail : not find cur policy", m_strLogicName.c_str());
				break;
			}

			t_ManagePoFePtnWL->SetPkt(pCurPolicy->tDPH.nID, SendToken);
			SendData_Link(&tPktData, SendToken);
			SendToken.Clear();
			WriteLogN("[logic link] send sync link data [po_fe_ptn_wl][%d]", t_ManagePoFePtnWL->Count());	
			break;
		}
		case SS_POLICY_TYPE_FE_EXCLUDE:
		{		
			PDB_PO_FE_EXCLUDE pCurPolicy = (PDB_PO_FE_EXCLUDE)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_FE_EXCLUDE);
			if(!pCurPolicy)
			{
				WriteLogE("[%s] set po fe exclude fail : not find cur policy", m_strLogicName.c_str());
				break;
			}

			t_ManagePoFeExclude->SetPktHost(pCurPolicy->tDPH.nID, SendToken);
			SendData_Link(&tPktData, SendToken);
			SendToken.Clear();
			WriteLogN("[logic link] send sync link data [po_fe_exclude][%d]", t_ManagePoFeExclude->Count());	
			break;
		}
		case SS_POLICY_TYPE_FE_NOTIFY:
		{			
			PDB_PO_FE_NOTIFY pCurPolicy = (PDB_PO_FE_NOTIFY)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_FE_NOTIFY);
			if(!pCurPolicy)
			{
				WriteLogE("[%s] set po fe notify fail : not find cur policy", m_strLogicName.c_str());
				break;
			}

			t_ManagePoFeNotify->SetPktHost(pCurPolicy->tDPH.nID, SendToken);
			SendData_Link(&tPktData, SendToken);
			SendToken.Clear();
			WriteLogN("[logic link] send sync link data [po_fe_notify][%d]", t_ManagePoFeNotify->Count());	
			break;
		}
		case SS_POLICY_TYPE_FE_SINGLE_PTN:
		{			
			PDB_PO_FE_SINGLE_PTN pCurPolicy = (PDB_PO_FE_SINGLE_PTN)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_FE_SINGLE_PTN);
			if(!pCurPolicy)
			{
				WriteLogE("[%s] set po fe single ptn fail : not find cur policy", m_strLogicName.c_str());
				break;
			}

			t_ManagePoFeSinglePtn->SetPktHost(pCurPolicy->tDPH.nID, SendToken);
			SendData_Link(&tPktData, SendToken);
			SendToken.Clear();
			WriteLogN("[logic link] send sync link data [po_fe_single_ptn][%d]", t_ManagePoFeSinglePtn->Count());		
			break;
		}
		case SS_POLICY_TYPE_IN_PTN_OP:
		{		
			PDB_PO_IN_PTN_OP pCurPolicy = (PDB_PO_IN_PTN_OP)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_IN_PTN_OP);
			if(!pCurPolicy)
			{
				WriteLogE("[%s] set po in ptn op fail : not find cur policy", m_strLogicName.c_str());
				break;
			}

			t_ManagePoInPtnOp->SetPktHost(pCurPolicy->tDPH.nID, SendToken);
			SendData_Link(&tPktData, SendToken);
			SendToken.Clear();
			WriteLogN("[logic link] send sync link data [po_in_ptn_op][%d]", t_ManagePoInPtnOp->Count());				
			break;
		}
		case SS_POLICY_TYPE_IN_PTN_BL:
		{			
			PDB_PO_IN_PTN_BL pCurPolicy = (PDB_PO_IN_PTN_BL)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_IN_PTN_BL);
			if(!pCurPolicy)
			{
				WriteLogE("[%s] set po in ptn bl fail : not find cur policy", m_strLogicName.c_str());
				break;
			}

			t_ManagePoInPtnBL->SetPktHost(pCurPolicy->tDPH.nID, SendToken);
			SendData_Link(&tPktData, SendToken);
			SendToken.Clear();
			WriteLogN("[logic init] send sync link data [po_in_ptn_bl][%d]", t_ManagePoInPtnBL->Count());	
			break;
		}
		case SS_POLICY_TYPE_IN_PTN_WL:
		{			
			PDB_PO_IN_PTN_WL pCurPolicy = (PDB_PO_IN_PTN_WL)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_IN_PTN_WL);
			if(!pCurPolicy)
			{
				WriteLogE("[%s] set po in ptn wl fail : not find cur policy", m_strLogicName.c_str());
				break;
			}

			t_ManagePoInPtnWL->SetPktHost(pCurPolicy->tDPH.nID, SendToken);
			SendData_Link(&tPktData, SendToken);
			SendToken.Clear();
			WriteLogN("[logic init] send sync link data [po_in_ptn_wl][%d]", t_ManagePoInPtnWL->Count());	
			break;
		}
		case SS_POLICY_TYPE_IN_PTN_EX:
		{			
			PDB_PO_IN_PTN_EX pCurPolicy = (PDB_PO_IN_PTN_EX)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_IN_PTN_EX);
			if(!pCurPolicy)
			{
				WriteLogE("[%s] set po in ptn ex fail : not find cur policy", m_strLogicName.c_str());
				break;
			}

			t_ManagePoInPtnEx->SetPktHost(pCurPolicy->tDPH.nID, SendToken);
			SendData_Link(&tPktData, SendToken);
			SendToken.Clear();
			WriteLogN("[logic init] send sync link data [po_in_ptn_ex][%d]", t_ManagePoInPtnEx->Count());	
			break;
		}
		case SS_POLICY_TYPE_IN_PTN_SP:
		{			
			PDB_PO_IN_PTN_SP pCurPolicy = (PDB_PO_IN_PTN_SP)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_IN_PTN_SP);
			if(!pCurPolicy)
			{
				WriteLogE("[%s] set po in ptn sp fail : not find cur policy", m_strLogicName.c_str());
				break;
			}

			t_ManagePoInPtnSP->SetPktHost(pCurPolicy->tDPH.nID, SendToken);
			SendData_Link(&tPktData, SendToken);
			SendToken.Clear();
			WriteLogN("[logic init] send sync link data [po_in_ptn_sp][%d]", t_ManagePoInPtnSP->Count());	
			break;
		}
		case SS_POLICY_TYPE_IN_PTN_NO:
		{			
			PDB_PO_IN_PTN_NO pCurPolicy = (PDB_PO_IN_PTN_NO)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_IN_PTN_NO);
			if(!pCurPolicy)
			{
				WriteLogE("[%s] set po in ptn no fail : not find cur policy", m_strLogicName.c_str());
				break;
			}

			t_ManagePoInPtnNo->SetPktHost(pCurPolicy->tDPH.nID, SendToken);
			SendData_Link(&tPktData, SendToken);
			SendToken.Clear();
			WriteLogN("[logic init] send sync link data [po_in_ptn_no][%d]", t_ManagePoInPtnNo->Count());	
			break;
		}
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		case SS_POLICY_TYPE_IN_AC_DOC:
		{			
			PDB_PO_IN_AC_DOC pCurPolicy = (PDB_PO_IN_AC_DOC)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_IN_AC_DOC);
			if(!pCurPolicy)
			{
				WriteLogE("[%s] set po in ac doc fail : not find cur policy", m_strLogicName.c_str());
				break;
			}

			t_ManagePoInAcDoc->SetPktHost(pCurPolicy->tDPH.nID, SendToken);
			SendData_Link(&tPktData, SendToken);
			SendToken.Clear();
			WriteLogN("[logic link] send sync link data [po_in_ac_doc][%d]", t_ManagePoInAcDoc->Count());						
			break;
		}
		case SS_POLICY_TYPE_IN_AC_SF:
		{		
			PDB_PO_IN_AC_SF pCurPolicy = (PDB_PO_IN_AC_SF)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_IN_AC_SF);
			if(!pCurPolicy)
			{
				WriteLogE("[%s] set po in ac sf fail : not find cur policy", m_strLogicName.c_str());
				break;
			}

			t_ManagePoInAcSf->SetPktHost(pCurPolicy->tDPH.nID, SendToken);
			SendData_Link(&tPktData, SendToken);
			SendToken.Clear();
			WriteLogN("[logic link] send sync link data [po_in_ac_sf][%d]", t_ManagePoInAcSf->Count());					
			break;
		}
		case SS_POLICY_TYPE_IN_AC_FILE:
		{			
			PDB_PO_IN_AC_FILE pCurPolicy = (PDB_PO_IN_AC_FILE)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_IN_AC_FILE);
			if(!pCurPolicy)
			{
				WriteLogE("[%s] set po in ac file fail : not find cur policy", m_strLogicName.c_str());
				break;
			}

			t_ManagePoInAcFile->SetPktHost(pCurPolicy->tDPH.nID, SendToken);
			SendData_Link(&tPktData, SendToken);
			SendToken.Clear();
			WriteLogN("[logic link] send sync link data [po_in_ac_file][%d]", t_ManagePoInAcFile->Count());	
			break;
		}
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		case SS_POLICY_TYPE_IN_VULN_OP:
		{		
			PDB_PO_IN_VULN_OP pCurPolicy = (PDB_PO_IN_VULN_OP)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_IN_VULN_OP);
			if(!pCurPolicy)
			{
				WriteLogE("[%s] set po in vuln op fail : not find cur policy", m_strLogicName.c_str());
				break;
			}

			t_ManagePoInVulnOp->SetPktHost(pCurPolicy->tDPH.nID, SendToken);
			SendData_Link(&tPktData, SendToken);
			SendToken.Clear();
			WriteLogN("[logic init] send sync link data [po_in_vuln_op][%d]", t_ManagePoInVulnOp->Count());	
			break;
		}
		case SS_POLICY_TYPE_IN_VULN_SCAN:
		{			
			PDB_PO_IN_VULN_SCAN pCurPolicy = (PDB_PO_IN_VULN_SCAN)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_IN_VULN_SCAN);
			if(!pCurPolicy)
			{
				WriteLogE("[%s] set po in vuln scan fail : not find cur policy", m_strLogicName.c_str());
				break;
			}

			t_ManagePoInVulnScan->SetPktHost(pCurPolicy->tDPH.nID, SendToken);
			SendData_Link(&tPktData, SendToken);
			SendToken.Clear();
			WriteLogN("[logic init] send sync link data [po_in_vuln_scan][%d]", t_ManagePoInVulnScan->Count());		
			break;
		}
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
	}
	if(m_nPolicyType)		return 0;

	switch(m_nPolicyUnitType)
	{
		case SS_POLICY_UNIT_TYPE_IN_PTN_SP_RULE:
		{
			t_ManagePoInPtnSPRule->SetPkt(SendToken);
			SendData_Link(G_TYPE_PO_IN_PTN_SP_RULE, G_CODE_COMMON_EDIT, SendToken);
			SendToken.Clear();
			WriteLogN("[logic init] send sync link data [po_in_ptn_sp_rule][%d]", t_ManagePoInPtnSPRule->Count());	
		}
	}
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
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------


