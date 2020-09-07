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
#include "LogicCtrlVuln.h"

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------


INT32		CLogicCtrlVuln::ScanEditProg()
{
	TListMemVulnRst tNotiList;

	PDB_PO_IN_VULN_EDIT_APP pCurPolicy = (PDB_PO_IN_VULN_EDIT_APP)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_IN_VULN_EDIT_APP);
	if(!pCurPolicy)
	{
		SendPkt_Scan(m_nRecvID, SS_PTN_VULN_SCAN_RESULT_CHK_FAIL, NULL);
		return SS_PTN_VULN_SCAN_RESULT_CHK_FAIL;
	}
	if(pCurPolicy->tDPH.nUsedMode != STATUS_USED_MODE_ON)
	{
		SendPkt_Scan(m_nRecvID, SS_PTN_VULN_SCAN_RESULT_SAFE, NULL);
		return SS_PTN_VULN_SCAN_RESULT_SAFE;
	}

	TListID tIDList;
	t_ManagePoInVulnEditAppPkg->GetKeyIDList(pCurPolicy->tDPH.nID, tIDList);
	TListIDItor begin, end;
	begin = tIDList.begin();	end = tIDList.end();
	for(begin; begin != end; begin++)
	{
		UINT8	nType = LOTYPEID32(*begin);
		UINT32	nUID = HITYPEID32(*begin);

		switch(nType)
		{
			case SS_COMMON_UNIT_TYPE_GLOBAL:	ScanEditProg_Global(nUID, tNotiList);		break;
			case SS_COMMON_UNIT_TYPE_SITE:		ScanEditProg_Site(nUID, tNotiList);			break;
		}
	}

	{
		if(tNotiList.size())	SendPkt_Scan(m_nRecvID, SS_PTN_VULN_SCAN_RESULT_DANGER, &tNotiList);
		else					SendPkt_Scan(m_nRecvID, SS_PTN_VULN_SCAN_RESULT_SAFE, NULL);
	}
	return SS_PTN_VULN_SCAN_RESULT_SCANNING;

}
//---------------------------------------------------------------------------

INT32		CLogicCtrlVuln::ScanEditProg_Global(UINT32 nID, TListMemVulnRst& tNotiList)
{
	return -1;
}
//---------------------------------------------------------------------------

INT32		CLogicCtrlVuln::ScanEditProg_Site(UINT32 nID, TListMemVulnRst& tNotiList)
{
	return 0;
}
//---------------------------------------------------------------------------


