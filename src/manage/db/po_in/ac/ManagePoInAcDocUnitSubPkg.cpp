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
#include "ManagePoInAcDocUnitSubPkg.h"

//---------------------------------------------------------------------------

CManagePoInAcDocUnitSubPkg*	t_ManagePoInAcDocUnitSubPkg = NULL;

//---------------------------------------------------------------------------

CManagePoInAcDocUnitSubPkg::CManagePoInAcDocUnitSubPkg()
{
	t_DBMgrPoInAcDocUnitSubPkg	= new CDBMgrPoInAcDocUnitSubPkg();
}
//---------------------------------------------------------------------------

CManagePoInAcDocUnitSubPkg::~CManagePoInAcDocUnitSubPkg()
{
	if(t_DBMgrPoInAcDocUnitSubPkg)	{	delete t_DBMgrPoInAcDocUnitSubPkg;	t_DBMgrPoInAcDocUnitSubPkg = NULL;	}
}
//---------------------------------------------------------------------------

INT32		CManagePoInAcDocUnitSubPkg::LoadDBMS()
{
	TListDBPoInAcDocUnitSubPkg tDBPoInAcDocUnitSubPkgList;
    TListDBPoInAcDocUnitSubPkgItor begin, end;
	if(SetER(t_DBMgrPoInAcDocUnitSubPkg->LoadExecute(&tDBPoInAcDocUnitSubPkgList)))
    {
    	return g_nErrRtn;
    }

    begin = tDBPoInAcDocUnitSubPkgList.begin();	end = tDBPoInAcDocUnitSubPkgList.end();
    for(begin; begin != end; begin++)
    {
		AddItem(begin->tDPH.nID, *begin);
		AddKeyIDList(&(*begin));
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocUnitSubPkg::InitPkg()
{
	TMapDBPoInAcDocUnitSubPkgItor begin, end;
	begin = m_tMap.begin();		end = m_tMap.end();
	for(begin; begin != end; begin++)
	{
		PDB_PO_IN_AC_DOC_UNIT pdpfou = t_ManagePoInAcDocUnit->FindItem(begin->second.tDPH.nPolicyID);
		if(!pdpfou)
		{
			WriteLogE("not find po_in_ac_doc_unit information [%d]:po_id[%d]:[%d]", begin->second.tDPH.nPolicyID, begin->first, ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			continue;
		}

		pdpfou->tDPH._add_key_id_value(SS_PO_IN_AC_UNIT_KEY_TYPE_SUBJECT, begin->first, begin->second.tDPH.nUnitID);
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocUnitSubPkg::GetHash(UINT32 nID, String& strOrgValue)
{
	PDB_PO_IN_AC_DOC_UNIT_SUB_PKG pdpiadusp 			= NULL;
	{
		if( (pdpiadusp = FindItem(nID)) == NULL)
		{
			WriteLogE("not find po_in_ac_doc_unit_sub_pkg by hash : [%d]", ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			return ERR_INFO_NOT_OP_BECAUSE_NOT_FIND;
		}
	}

	{
		t_ManagePoInAcDocSubUnit->GetHash(pdpiadusp->tDPH.nUnitID, EmptyStr(m_strHashValue));
		strOrgValue += m_strHashValue;
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocUnitSubPkg::AddPoInAcDocUnitSubPkg(DB_PO_IN_AC_DOC_UNIT_SUB_PKG&	dpiadusp)
{
	if(SetER(t_DBMgrPoInAcDocUnitSubPkg->InsertExecute(&dpiadusp)))
    {
    	return g_nErrRtn;
    }

	AddItem(dpiadusp.tDPH.nID, dpiadusp);
	AddKeyIDList(&dpiadusp);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocUnitSubPkg::EditPoInAcDocUnitSubPkg(DB_PO_IN_AC_DOC_UNIT_SUB_PKG&	dpiadusp)
{
	PDB_PO_IN_AC_DOC_UNIT_SUB_PKG pdpiadusp = FindItem(dpiadusp.tDPH.nID);
	if(!pdpiadusp)	return ERR_DBMS_UPDATE_FAIL;

	if(SetER(t_DBMgrPoInAcDocUnitSubPkg->UpdateExecute(&dpiadusp)))
    {
    	return g_nErrRtn;
    }

    EditItem(dpiadusp.tDPH.nID, dpiadusp);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocUnitSubPkg::DelPoInAcDocUnitSubPkg(UINT32 nID)
{
	PDB_PO_IN_AC_DOC_UNIT_SUB_PKG pdpiadusp = FindItem(nID);
	if(!pdpiadusp)	return ERR_DBMS_DELETE_FAIL;

	if(SetER(t_DBMgrPoInAcDocUnitSubPkg->DeleteExecute(pdpiadusp->tDPH.nID)))
    {
    	return g_nErrRtn;
    }

	DelKeyIDList(pdpiadusp);
    DeleteItem(nID);
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocUnitSubPkg::GetPoIDListFromUnitPkg(UINT32 nUnitID, TListID& tListID)
{
	TMapID tPoIDMap;
	TListID tUnitIDList;
	GetPoIDFromPkgList(nUnitID, tUnitIDList);

	{
		TListIDItor begin, end;
		begin = tUnitIDList.begin();	end = tUnitIDList.end();
		for(begin; begin != end; begin++)
		{
			t_ManagePoInAcDocPkg->GetPoIDFromPkgMap(*begin, tPoIDMap);	
		}
	}
	ConvertMapToList(tPoIDMap, tListID);
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocUnitSubPkg::ClearItemByPolicyID(UINT32 nPolicyID)
{
	TListID tIDList;
	GetItemIDList(tIDList);

	TListIDItor begin, end;
	begin = tIDList.begin();	end = tIDList.end();
	for(begin; begin != end; begin++)
	{
		PDB_PO_IN_AC_DOC_UNIT_SUB_PKG pdpiadusp = FindItem(*begin);
		if(pdpiadusp->tDPH.nPolicyID != nPolicyID)	continue;

		DelPoInAcDocUnitSubPkg(*begin);
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocUnitSubPkg::ClearPkgUnitByPolicyID(UINT32 nPolicyID)
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
			t_ManagePoInAcDocSubUnit->DelPoInAcDocSubUnit(pDPH->nUnitID);
		}

		DelPoInAcDocUnitSubPkg(*begin);
	}
	return 0;
}
//---------------------------------------------------------------------------

String					CManagePoInAcDocUnitSubPkg::GetName(UINT32 nID)
{
	PDB_PO_IN_AC_DOC_UNIT_SUB_PKG pdpiadusp = FindItem(nID);
    if(!pdpiadusp)	return "";
    return pdpiadusp->tDPH.strName;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocUnitSubPkg::SetPkt(MemToken& SendToken)
{
    SendToken.TokenAdd_32(m_tMap.size());

	TMapDBPoInAcDocUnitSubPkgItor begin, end;
    begin = m_tMap.begin();	end = m_tMap.end();
    for(begin; begin != end; begin++)
    {
    	SetPkt(&(begin->second), SendToken);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocUnitSubPkg::SetPkt(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_AC_DOC_UNIT_SUB_PKG pdpiadusp = FindItem(nID);
	if(!pdpiadusp)	return -1;

	return SetPkt(pdpiadusp, SendToken);
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocUnitSubPkg::SetPkt(PDB_PO_IN_AC_DOC_UNIT_SUB_PKG pdpiadusp, MemToken& SendToken)
{
	SendToken.TokenAdd_DPH(pdpiadusp->tDPH);

	SendToken.TokenAdd_32(pdpiadusp->nRuleOrder);
	SendToken.TokenAdd_32(pdpiadusp->nAcMode);

	SendToken.TokenSet_Block();
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocUnitSubPkg::GetPkt(MemToken& RecvToken, DB_PO_IN_AC_DOC_UNIT_SUB_PKG& dpiadusp)
{
	if (!RecvToken.TokenDel_DPH(dpiadusp.tDPH))				goto	INVALID_PKT;

	if (!RecvToken.TokenDel_32(dpiadusp.nRuleOrder))		goto	INVALID_PKT;
	if (!RecvToken.TokenDel_32(dpiadusp.nAcMode))			goto	INVALID_PKT;

	RecvToken.TokenSkip_Block();
	return 0;
INVALID_PKT:
	return -1;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocUnitSubPkg::SetPktHost(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_AC_DOC_UNIT_SUB_PKG pdpiadusp = FindItem(nID);
	if(!pdpiadusp)	return -1;

	SetPkt(pdpiadusp, SendToken);

	return t_ManagePoInAcDocSubUnit->SetPkt(pdpiadusp->tDPH.nUnitID, SendToken);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------



