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
#include "ManagePoInAcSfUnitSubPkg.h"

//---------------------------------------------------------------------------

CManagePoInAcSfUnitSubPkg*	t_ManagePoInAcSfUnitSubPkg = NULL;

//---------------------------------------------------------------------------

CManagePoInAcSfUnitSubPkg::CManagePoInAcSfUnitSubPkg()
{
	t_DBMgrPoInAcSfUnitSubPkg	= new CDBMgrPoInAcSfUnitSubPkg();
}
//---------------------------------------------------------------------------

CManagePoInAcSfUnitSubPkg::~CManagePoInAcSfUnitSubPkg()
{
	if(t_DBMgrPoInAcSfUnitSubPkg)	{	delete t_DBMgrPoInAcSfUnitSubPkg;	t_DBMgrPoInAcSfUnitSubPkg = NULL;	}
}
//---------------------------------------------------------------------------

INT32		CManagePoInAcSfUnitSubPkg::LoadDBMS()
{
	TListDBPoInAcSfUnitSubPkg tDBPoInAcSfUnitSubPkgList;
    TListDBPoInAcSfUnitSubPkgItor begin, end;
	if(SetER(t_DBMgrPoInAcSfUnitSubPkg->LoadExecute(&tDBPoInAcSfUnitSubPkgList)))
    {
    	return g_nErrRtn;
    }

    begin = tDBPoInAcSfUnitSubPkgList.begin();	end = tDBPoInAcSfUnitSubPkgList.end();
    for(begin; begin != end; begin++)
    {
		AddItem(begin->tDPH.nID, *begin);
		AddKeyIDList(&(*begin));
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfUnitSubPkg::InitPkg()
{
	TMapDBPoInAcSfUnitSubPkgItor begin, end;
	begin = m_tMap.begin();		end = m_tMap.end();
	for(begin; begin != end; begin++)
	{
		PDB_PO_IN_AC_SF_UNIT pdpfou = t_ManagePoInAcSfUnit->FindItem(begin->second.tDPH.nPolicyID);
		if(!pdpfou)
		{
			WriteLogE("not find po_in_ac_sf_unit information [%d]:po_id[%d]:[%d]", begin->second.tDPH.nPolicyID, begin->first, ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			continue;
		}

		pdpfou->tDPH._add_key_id_value(SS_PO_IN_AC_UNIT_KEY_TYPE_SUBJECT, begin->first, begin->second.tDPH.nUnitID);
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfUnitSubPkg::GetHash(UINT32 nID, String& strOrgValue)
{
	PDB_PO_IN_AC_SF_UNIT_SUB_PKG pdpiafusp 			= NULL;
	{
		if( (pdpiafusp = FindItem(nID)) == NULL)
		{
			WriteLogE("not find po_in_ac_sf_unit_sub_pkg by hash : [%d]", ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			return ERR_INFO_NOT_OP_BECAUSE_NOT_FIND;
		}
	}

	{
		EmptyStr(m_strHashValue);
		m_strHashValue = SPrintf("%u,%u,", pdpiafusp->nRuleOrder, pdpiafusp->nAcMode);

		t_ManagePoInAcSfSubUnit->GetHash(pdpiafusp->tDPH.nUnitID, m_strHashValue);
		strOrgValue += m_strHashValue;
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfUnitSubPkg::AddPoInAcSfUnitSubPkg(DB_PO_IN_AC_SF_UNIT_SUB_PKG&	dpiafusp)
{
	if(SetER(t_DBMgrPoInAcSfUnitSubPkg->InsertExecute(&dpiafusp)))
    {
    	return g_nErrRtn;
    }

	AddItem(dpiafusp.tDPH.nID, dpiafusp);
	AddKeyIDList(&dpiafusp);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfUnitSubPkg::EditPoInAcSfUnitSubPkg(DB_PO_IN_AC_SF_UNIT_SUB_PKG&	dpiafusp)
{
	PDB_PO_IN_AC_SF_UNIT_SUB_PKG pdpiafusp = FindItem(dpiafusp.tDPH.nID);
	if(!pdpiafusp)	return ERR_DBMS_UPDATE_FAIL;

	if(SetER(t_DBMgrPoInAcSfUnitSubPkg->UpdateExecute(&dpiafusp)))
    {
    	return g_nErrRtn;
    }

    EditItem(dpiafusp.tDPH.nID, dpiafusp);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfUnitSubPkg::DelPoInAcSfUnitSubPkg(UINT32 nID)
{
	PDB_PO_IN_AC_SF_UNIT_SUB_PKG pdpiafusp = FindItem(nID);
	if(!pdpiafusp)	return ERR_DBMS_DELETE_FAIL;

	if(SetER(t_DBMgrPoInAcSfUnitSubPkg->DeleteExecute(pdpiafusp->tDPH.nID)))
    {
    	return g_nErrRtn;
    }

	DelKeyIDList(pdpiafusp);
    DeleteItem(nID);
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfUnitSubPkg::GetPoIDListFromUnitPkg(UINT32 nUnitID, TListID& tListID)
{
	TMapID tPoIDMap;
	TListID tUnitIDList;
	GetPoIDFromPkgList(nUnitID, tUnitIDList);

	{
		TListIDItor begin, end;
		begin = tUnitIDList.begin();	end = tUnitIDList.end();
		for(begin; begin != end; begin++)
		{
			t_ManagePoInAcSfPkg->GetPoIDFromPkgMap(*begin, tPoIDMap);	
		}
	}
	ConvertMapToList(tPoIDMap, tListID);
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfUnitSubPkg::ClearItemByPolicyID(UINT32 nPolicyID)
{
	TListID tIDList;
	GetItemIDList(tIDList);

	TListIDItor begin, end;
	begin = tIDList.begin();	end = tIDList.end();
	for(begin; begin != end; begin++)
	{
		PDB_PO_IN_AC_SF_UNIT_SUB_PKG pdpiafusp = FindItem(*begin);
		if(pdpiafusp->tDPH.nPolicyID != nPolicyID)	continue;

		DelPoInAcSfUnitSubPkg(*begin);
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfUnitSubPkg::ClearPkgUnitByPolicyID(UINT32 nPolicyID)
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
			t_ManagePoInAcSfSubUnit->DelPoInAcSfSubUnit(pDPH->nUnitID);
		}

		DelPoInAcSfUnitSubPkg(*begin);
	}
	return 0;
}
//---------------------------------------------------------------------------

String					CManagePoInAcSfUnitSubPkg::GetName(UINT32 nID)
{
	PDB_PO_IN_AC_SF_UNIT_SUB_PKG pdpiafusp = FindItem(nID);
    if(!pdpiafusp)	return "";
    return pdpiafusp->tDPH.strName;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfUnitSubPkg::SetPkt(MemToken& SendToken)
{
    SendToken.TokenAdd_32(m_tMap.size());

	TMapDBPoInAcSfUnitSubPkgItor begin, end;
    begin = m_tMap.begin();	end = m_tMap.end();
    for(begin; begin != end; begin++)
    {
    	SetPkt(&(begin->second), SendToken);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfUnitSubPkg::SetPkt(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_AC_SF_UNIT_SUB_PKG pdpiafusp = FindItem(nID);
	if(!pdpiafusp)	return -1;

	return SetPkt(pdpiafusp, SendToken);
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfUnitSubPkg::SetPkt(PDB_PO_IN_AC_SF_UNIT_SUB_PKG pdpiafusp, MemToken& SendToken)
{
	SendToken.TokenAdd_DPH(pdpiafusp->tDPH);

	SendToken.TokenAdd_32(pdpiafusp->nRuleOrder);
	SendToken.TokenAdd_32(pdpiafusp->nAcMode);

	SendToken.TokenSet_Block();
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfUnitSubPkg::GetPkt(MemToken& RecvToken, DB_PO_IN_AC_SF_UNIT_SUB_PKG& dpiafusp)
{
	if (!RecvToken.TokenDel_DPH(dpiafusp.tDPH))				goto	INVALID_PKT;

	if (!RecvToken.TokenDel_32(dpiafusp.nRuleOrder))		goto	INVALID_PKT;
	if (!RecvToken.TokenDel_32(dpiafusp.nAcMode))			goto	INVALID_PKT;

	RecvToken.TokenSkip_Block();
	return 0;
INVALID_PKT:
	return -1;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfUnitSubPkg::SetPktHost(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_AC_SF_UNIT_SUB_PKG pdpiafusp = FindItem(nID);
	if(!pdpiafusp)	return -1;

	SetPkt(pdpiafusp, SendToken);

	return t_ManagePoInAcSfSubUnit->SetPkt(pdpiafusp->tDPH.nUnitID, SendToken);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------



