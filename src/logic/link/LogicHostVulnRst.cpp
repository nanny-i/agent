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
#include "LogicHostVulnRst.h"

//---------------------------------------------------------------------------

CLogicHostVulnRst*		t_LogicHostVulnRst = NULL;

//---------------------------------------------------------------------------

CLogicHostVulnRst::CLogicHostVulnRst()
{	
	m_strLogicName		= "link host vuln rst";
		
	m_nEvtSubType		= EVENT_SUBJECT_TYPE_USER;
	m_nEvtObjType		= EVENT_OBJECT_TYPE_USER;
	m_nEvtObjCode		= EVENT_OBJECT_CODE_HOST_VULN_RST;
}
//---------------------------------------------------------------------------

CLogicHostVulnRst::~CLogicHostVulnRst()
{

}
//---------------------------------------------------------------------------

INT32	CLogicHostVulnRst::AnalyzePkt_FromLink_Ext()
{
	switch(m_nPktCode)
	{
		case G_CODE_COMMON_SYNC:		AnalyzePkt_FromLink_Ext_Sync();		break;
		default:						break;		
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32		CLogicHostVulnRst::AnalyzePkt_FromLink_Ext_Sync()
{	
	m_nEvtOpType = EVENT_OPERATION_TYPE_SYNC;
	DB_HOST_VULN_RST data;
	PDB_HOST_VULN_RST pdata = NULL;
	TListDBHostVulnRstUnit tUnitList;

	if(t_ManageHostVulnRst->GetPkt(RecvToken, data) < 0)			return AZPKT_CB_RTN_PKT_INVALID;
	if(!RecvToken.TokenDel_32(m_nRecvNum))							return AZPKT_CB_RTN_PKT_INVALID;
	while(m_nRecvNum--)
	{
		DB_HOST_VULN_RST_UNIT data_unit;
		if(t_ManageHostVulnRstUnit->GetPkt_Link(RecvToken, data_unit) < 0)	return AZPKT_CB_RTN_PKT_INVALID;

		tUnitList.push_back(data_unit);
	}

	{
		if(data.nScanMon == 0)			data.nScanMon = GetCurrentYearMon();
		if(data.strVersion.empty())
		{
			PDB_PO_IN_VULN_OP pdata_op = (PDB_PO_IN_VULN_OP)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_IN_VULN_OP);
			if(pdata_op)
				data.strVersion = SPrintf("%s : %s", t_EnvInfo->m_strHostBinVer.c_str(), pdata_op->tDPIVOPF.strPtnVersion.c_str());
			else
				data.strVersion = SPrintf("%s", t_EnvInfo->m_strHostBinVer.c_str());
		}


		data.nScanDate = GetCurrentDateTimeInt();

		pdata = t_ManageHostVulnRst->FindKeyItem(data.nScanMon);
		if(!pdata)
		{
			if(SetER(t_ManageHostVulnRst->AddHostVulnRst(data)))
			{
				WriteLogE("[%s] add vuln rst fail : [%d]", m_strLogicName.c_str(), g_nErrRtn);
				return AZPKT_CB_RTN_DBMS_FAIL;
			}
			pdata = t_ManageHostVulnRst->FindKeyItem(data.nScanMon);
		}
		else
		{
			data.nID = pdata->nID;
			t_ManageHostVulnRst->EditHostVulnRst(data);	
		}

		pdata->tRstUnitMap.clear();
	}


	{
		TMapID tOIDMap, tNIDMap;
		t_ManageHostVulnRstUnit->GetKeySubIDMap(data.nScanMon, tOIDMap);

		{
			TListDBHostVulnRstUnitItor begin, end;
			begin = tUnitList.begin();	end = tUnitList.end();
			for(begin; begin != end; begin++)
			{
				PDB_HOST_VULN_RST_UNIT pdata_unit = t_ManageHostVulnRstUnit->FindKeySubIDMapItem(pdata->nID, begin->tDHVRUS.nVulnID);
				if(pdata_unit)
				{
					begin->nID = pdata_unit->nID;
					pdata_unit->tDHVRUS = begin->tDHVRUS;
					pdata_unit->strRstInfo = begin->strRstInfo;

					if(SetER(t_ManageHostVulnRstUnit->EditHostVulnRstUnit(*begin)))
					{
						WriteLogE("[%s] edit vuln rst unit fail : [%d]", m_strLogicName.c_str(), g_nErrRtn);
						return AZPKT_CB_RTN_DBMS_FAIL;
					}

					tNIDMap[begin->nID] = 0;
					pdata->tRstUnitMap[begin->tDHVRUS.nVulnID] = begin->tDHVRUS;
				}
				else
				{
					begin->nID = 0;
					begin->nVulnRstID = pdata->nID;
					begin->nRegDate	= GetCurrentDateTimeInt();

					if(SetER(t_ManageHostVulnRstUnit->AddHostVulnRstUnit(*begin)))
					{
						WriteLogE("[%s] add vuln rst unit fail : [%d]", m_strLogicName.c_str(), g_nErrRtn);
						return AZPKT_CB_RTN_DBMS_FAIL;
					}

					tNIDMap[begin->nID] = 0;
					pdata->tRstUnitMap[begin->tDHVRUS.nVulnID] = begin->tDHVRUS;
				}
			}
		}

		{
			TMapIDItor begin, end;
			begin = tOIDMap.begin();	end = tOIDMap.end();
			for(begin; begin != end; begin++)
			{
				if(IsExistsIDFromMap(tNIDMap, begin->second))	continue;

				if(SetER(t_ManageHostVulnRstUnit->DelHostVulnRstUnit(begin->second)))
				{
					WriteLogE("[%s] del vuln rst unit fail : [%d]", m_strLogicName.c_str(), g_nErrRtn);
					return AZPKT_CB_RTN_DBMS_FAIL;
				}
			}
		}
	}

	{
		t_ManageHostVulnRst->SetRstMapToStr(pdata);
		HISYNCSTEPUP(pdata->nSyncSvrStep);
		if(SetER(t_ManageHostVulnRst->EditHostVulnRst(*pdata)))
		{
			WriteLogE("[%s] edit vuln rst fail : [%d]", m_strLogicName.c_str(), g_nErrRtn);
			return AZPKT_CB_RTN_DBMS_FAIL;
		}
		t_LogicMgrHostVulnRst->SetHostVulnRst(*pdata);
	}
	
	return AZPKT_CB_RTN_SUCCESS;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
