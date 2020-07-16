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
#include "LogicMgrPoCtlProc.h"

//---------------------------------------------------------------------------

CLogicMgrPoCtlProc*		t_LogicMgrPoCtlProc = NULL;

//---------------------------------------------------------------------------

CLogicMgrPoCtlProc::CLogicMgrPoCtlProc()
{
	t_ManagePoCtlProc		= new CManagePoCtlProc();
	t_ManagePoCtlProcPkg	= new CManagePoCtlProcPkg();
	t_ManagePoCtlProcUnit	= new CManagePoCtlProcUnit();

	t_ManagePoCtlProc->LoadDBMS();
	t_ManagePoCtlProcPkg->LoadDBMS();
	t_ManagePoCtlProcUnit->LoadDBMS();

	t_ManagePoCtlProc->InitHash();

	m_strLogicName		= "mgr agt po ctl proc";
	
	m_nPolicyType		= SS_POLICY_TYPE_CTL_PROC;
	m_nSSPoSeqIdx		= SS_POLICY_INDEX_CTL_PROC;
	m_nAgtPktEditCode	= G_CODE_COMMON_EDIT;	
	
	m_nEvtObjType		= EVENT_OBJECT_TYPE_POLICY;
	m_nEvtObjCode		= EVENT_OBJECT_CODE_POLICY_CTL_PROC;
}
//---------------------------------------------------------------------------

CLogicMgrPoCtlProc::~CLogicMgrPoCtlProc()
{
	SAFE_DELETE(t_ManagePoCtlProc);
	SAFE_DELETE(t_ManagePoCtlProcPkg);
	SAFE_DELETE(t_ManagePoCtlProcUnit);
}
//---------------------------------------------------------------------------
INT32		CLogicMgrPoCtlProc::AnalyzePkt_FromMgr_Ext()
{
	return SetHdrAndRtn(AZPKT_CB_RTN_SUCCESS);
}
//---------------------------------------------------------------------------

INT32		CLogicMgrPoCtlProc::AnalyzePkt_FromMgr_Edit_Ext()
{
	PDB_PO_CTL_PROC ppcp = NULL;
	DB_PO_CTL_PROC dpcp;

	m_tDPH = &(dpcp.tDPH);

	TListDBPoCtlProcPkg		tPkgList;
	TListDBPoCtlProcUnit	tUnitList;

	if( t_ManagePoCtlProc->GetPkt(RecvToken, dpcp))			return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
	if(!RecvToken.TokenDel_32(m_nRecvNum))					return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
	while(m_nRecvNum--)
	{
		DB_PO_CTL_PROC_PKG	dppp;		
		DB_PO_CTL_PROC_UNIT dppu;

		if( t_ManagePoCtlProcPkg->GetPkt(RecvToken, dppp))	return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);
		if( t_ManagePoCtlProcUnit->GetPkt(RecvToken, dppu)) return SetHdrAndRtn(AZPKT_CB_RTN_PKT_INVALID);

		tPkgList.push_back(dppp);
		tUnitList.push_back(dppu);

		dpcp.tDPH._add_id(dppp.tDPH.nID);
	}

	ppcp = (PDB_PO_CTL_PROC)t_DeployPolicyUtil->GetCurPoPtr(m_nPolicyType);
	if(ppcp)
	{
		t_ManagePoCtlProcPkg->ClearItemByPolicyID(ppcp->tDPH.nID);		
		t_ManagePoCtlProc->DelPoCtlProc(ppcp->tDPH.nID);
	}

	{
		{
			TListDBPoCtlProcUnitItor begin, end;
			begin = tUnitList.begin();	end = tUnitList.end();
			for(begin; begin != end; begin++)
			{
				if(t_ManagePoCtlProcUnit->ApplyPoCtlProcUnit(*begin))
				{
					SetDLEA_EC(g_nErrRtn);
					WriteLogE("[%s] apply policy unit information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
					continue;
				}
			}
		}

		{
			TListDBPoCtlProcPkgItor begin, end;
			begin = tPkgList.begin();	end = tPkgList.end();
			for(begin; begin != end; begin++)
			{
				if(t_ManagePoCtlProcPkg->FindItem(begin->tDPH.nID))
				{
					SetDLEA_EC(g_nErrRtn);
					WriteLogE("[%s] add policy pkg information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
					continue;
				}

				t_ManagePoCtlProcPkg->AddPoCtlProcPkg(*begin);
			}
		}

		if(SetER(t_ManagePoCtlProc->ApplyPoCtlProc(dpcp)))
		{
			SetDLEA_EC(g_nErrRtn);
			WriteLogE("[%s] apply policy information : [%d]", m_strLogicName.c_str(), g_nErrRtn);
			return SetHdrAndRtn(AZPKT_CB_RTN_DBMS_FAIL);
		}
	}

	{
		t_ThreadTimer->t_TimerUtil.EnableTimer(TIMER_ID_POLICY_APPLY_EPS);
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
