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

#include "ManagePoInRegSWUnit.h"
#include "ManagePoInRegSWSubUnit.h"
#include "ManagePoInRegSWPkg.h"
#include "ManagePoInRegSWUnitSubPkg.h"

//---------------------------------------------------------------------------

CManagePoInRegSWUnitSubPkg*	t_ManagePoInRegSWUnitSubPkg = NULL;

//---------------------------------------------------------------------------

CManagePoInRegSWUnitSubPkg::CManagePoInRegSWUnitSubPkg()
{
	t_DBMgrPoInRegSWUnitSubPkg	= new CDBMgrPoInRegSWUnitSubPkg();
}
//---------------------------------------------------------------------------

CManagePoInRegSWUnitSubPkg::~CManagePoInRegSWUnitSubPkg()
{
	if(t_DBMgrPoInRegSWUnitSubPkg)	{	delete t_DBMgrPoInRegSWUnitSubPkg;	t_DBMgrPoInRegSWUnitSubPkg = NULL;	}
}
//---------------------------------------------------------------------------

INT32		CManagePoInRegSWUnitSubPkg::LoadDBMS()
{
	TListDBPoInRegSWUnitSubPkg tDBPoInRegSWUnitSubPkgList;
    TListDBPoInRegSWUnitSubPkgItor begin, end;
	if(SetER(t_DBMgrPoInRegSWUnitSubPkg->LoadExecute(&tDBPoInRegSWUnitSubPkgList)))
    {
    	return g_nErrRtn;
    }

    begin = tDBPoInRegSWUnitSubPkgList.begin();	end = tDBPoInRegSWUnitSubPkgList.end();
    for(begin; begin != end; begin++)
    {
		AddItem(begin->tDPH.nID, *begin);
		AddKeyIDList(&(*begin));
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSWUnitSubPkg::InitPkg()
{
	TMapDBPoInRegSWUnitSubPkgItor begin, end;
	begin = m_tMap.begin();		end = m_tMap.end();
	for(begin; begin != end; begin++)
	{
		PDB_PO_IN_REG_SW_UNIT pdpfou = t_ManagePoInRegSWUnit->FindItem(begin->second.tDPH.nPolicyID);
		if(!pdpfou)
		{
			WriteLogE("not find po_in_reg_sw_unit information [%d]:po_id[%d]:[%d]", begin->second.tDPH.nPolicyID, begin->first, ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			continue;
		}

		pdpfou->tDPH._add_key_id_value(SS_PO_IN_AC_UNIT_KEY_TYPE_SUBJECT, begin->first, begin->second.tDPH.nUnitID);
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSWUnitSubPkg::GetHash(UINT32 nID, String& strOrgValue)
{
	PDB_PO_IN_REG_SW_UNIT_SUB_PKG pdpirsusp 			= NULL;
	{
		if( (pdpirsusp = FindItem(nID)) == NULL)
		{
			WriteLogE("not find po_in_reg_sw_unit_sub_pkg by hash : [%d]", ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			return ERR_INFO_NOT_OP_BECAUSE_NOT_FIND;
		}
	}

	{
		EmptyStr(m_strHashValue);
		m_strHashValue = SPrintf("%u,%u,", pdpirsusp->nRuleOrder, pdpirsusp->nAcMode);

		t_ManagePoInRegSWSubUnit->GetHash(pdpirsusp->tDPH.nUnitID, m_strHashValue);
		strOrgValue += m_strHashValue;
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSWUnitSubPkg::AddPoInRegSWUnitSubPkg(DB_PO_IN_REG_SW_UNIT_SUB_PKG&	dpirsusp)
{
	if(SetER(t_DBMgrPoInRegSWUnitSubPkg->InsertExecute(&dpirsusp)))
    {
    	return g_nErrRtn;
    }

	AddItem(dpirsusp.tDPH.nID, dpirsusp);
	AddKeyIDList(&dpirsusp);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSWUnitSubPkg::EditPoInRegSWUnitSubPkg(DB_PO_IN_REG_SW_UNIT_SUB_PKG&	dpirsusp)
{
	PDB_PO_IN_REG_SW_UNIT_SUB_PKG pdpirsusp = FindItem(dpirsusp.tDPH.nID);
	if(!pdpirsusp)	return ERR_DBMS_UPDATE_FAIL;

	if(SetER(t_DBMgrPoInRegSWUnitSubPkg->UpdateExecute(&dpirsusp)))
    {
    	return g_nErrRtn;
    }

    EditItem(dpirsusp.tDPH.nID, dpirsusp);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSWUnitSubPkg::DelPoInRegSWUnitSubPkg(UINT32 nID)
{
	PDB_PO_IN_REG_SW_UNIT_SUB_PKG pdpirsusp = FindItem(nID);
	if(!pdpirsusp)	return ERR_DBMS_DELETE_FAIL;

	if(SetER(t_DBMgrPoInRegSWUnitSubPkg->DeleteExecute(pdpirsusp->tDPH.nID)))
    {
    	return g_nErrRtn;
    }

	DelKeyIDList(pdpirsusp);
    DeleteItem(nID);
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSWUnitSubPkg::GetPoIDListFromUnitPkg(UINT32 nUnitID, TListID& tListID)
{
	TMapID tPoIDMap;
	TListID tUnitIDList;
	GetPoIDFromPkgList(nUnitID, tUnitIDList);

	{
		TListIDItor begin, end;
		begin = tUnitIDList.begin();	end = tUnitIDList.end();
		for(begin; begin != end; begin++)
		{
			t_ManagePoInRegSWPkg->GetPoIDFromPkgMap(*begin, tPoIDMap);	
		}
	}
	ConvertMapToList(tPoIDMap, tListID);
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSWUnitSubPkg::ClearItemByPolicyID(UINT32 nPolicyID)
{
	TListID tIDList;
	GetItemIDList(tIDList);

	TListIDItor begin, end;
	begin = tIDList.begin();	end = tIDList.end();
	for(begin; begin != end; begin++)
	{
		PDB_PO_IN_REG_SW_UNIT_SUB_PKG pdpirsusp = FindItem(*begin);
		if(pdpirsusp->tDPH.nPolicyID != nPolicyID)	continue;

		DelPoInRegSWUnitSubPkg(*begin);
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSWUnitSubPkg::ClearPkgUnitByPolicyID(UINT32 nPolicyID)
{	
	TListID tIDList;
	GetItemIDList(tIDList);

	TListIDItor begin, end;
	begin = tIDList.begin();	end = tIDList.end();
	for(begin; begin != end; begin++)
	{
		PDB_PO_HEADER pDPH = GetPoHdr(*begin);
		if(!pDPH || pDPH->nPolicyID != nPolicyID)		continue;

		if(IsMultiUsedUnit(nPolicyID, pDPH->nUnitID) == 0)
		{
			t_ManagePoInRegSWSubUnit->DelPoInRegSWSubUnit(pDPH->nUnitID);
		}

		DelPoInRegSWUnitSubPkg(*begin);
	}
	return 0;
}
//---------------------------------------------------------------------------

String					CManagePoInRegSWUnitSubPkg::GetName(UINT32 nID)
{
	PDB_PO_IN_REG_SW_UNIT_SUB_PKG pdpirsusp = FindItem(nID);
    if(!pdpirsusp)	return "";
    return pdpirsusp->tDPH.strName;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManagePoInRegSWUnitSubPkg::SetPkt(MemToken& SendToken)
{
    SendToken.TokenAdd_32(m_tMap.size());

	TMapDBPoInRegSWUnitSubPkgItor begin, end;
    begin = m_tMap.begin();	end = m_tMap.end();
    for(begin; begin != end; begin++)
    {
    	SetPkt(&(begin->second), SendToken);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSWUnitSubPkg::SetPkt(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_REG_SW_UNIT_SUB_PKG pdpirsusp = FindItem(nID);
	if(!pdpirsusp)	return -1;

	return SetPkt(pdpirsusp, SendToken);
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSWUnitSubPkg::SetPkt(PDB_PO_IN_REG_SW_UNIT_SUB_PKG pdpirsusp, MemToken& SendToken)
{
	SendToken.TokenAdd_DPH(pdpirsusp->tDPH);

	SendToken.TokenAdd_32(pdpirsusp->nRuleOrder);
	SendToken.TokenAdd_32(pdpirsusp->nAcMode);

	SendToken.TokenSet_Block();
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSWUnitSubPkg::GetPkt(MemToken& RecvToken, DB_PO_IN_REG_SW_UNIT_SUB_PKG& dpirsusp)
{
	if (!RecvToken.TokenDel_DPH(dpirsusp.tDPH))				goto	INVALID_PKT;

	if (!RecvToken.TokenDel_32(dpirsusp.nRuleOrder))		goto	INVALID_PKT;
	if (!RecvToken.TokenDel_32(dpirsusp.nAcMode))			goto	INVALID_PKT;

	RecvToken.TokenSkip_Block();
	return 0;
INVALID_PKT:
	return -1;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManagePoInRegSWUnitSubPkg::SetPktHost(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_REG_SW_UNIT_SUB_PKG pdpirsusp = FindItem(nID);
	if(!pdpirsusp)	return -1;

	SetPkt(pdpirsusp, SendToken);

	return t_ManagePoInRegSWSubUnit->SetPkt(pdpirsusp->tDPH.nUnitID, SendToken);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------



