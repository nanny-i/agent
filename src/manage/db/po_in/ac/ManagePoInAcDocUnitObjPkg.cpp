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
#include "ManagePoInAcDocUnitObjPkg.h"

//---------------------------------------------------------------------------

CManagePoInAcDocUnitObjPkg*	t_ManagePoInAcDocUnitObjPkg = NULL;

//---------------------------------------------------------------------------

CManagePoInAcDocUnitObjPkg::CManagePoInAcDocUnitObjPkg()
{
	t_DBMgrPoInAcDocUnitObjPkg	= new CDBMgrPoInAcDocUnitObjPkg();
}
//---------------------------------------------------------------------------

CManagePoInAcDocUnitObjPkg::~CManagePoInAcDocUnitObjPkg()
{
	if(t_DBMgrPoInAcDocUnitObjPkg)	{	delete t_DBMgrPoInAcDocUnitObjPkg;	t_DBMgrPoInAcDocUnitObjPkg = NULL;	}
}
//---------------------------------------------------------------------------

INT32		CManagePoInAcDocUnitObjPkg::LoadDBMS()
{
	TListDBPoInAcDocUnitObjPkg tDBPoInAcDocUnitObjPkgList;
    TListDBPoInAcDocUnitObjPkgItor begin, end;
	if(SetER(t_DBMgrPoInAcDocUnitObjPkg->LoadExecute(&tDBPoInAcDocUnitObjPkgList)))
    {
    	return g_nErrRtn;
    }

    begin = tDBPoInAcDocUnitObjPkgList.begin();	end = tDBPoInAcDocUnitObjPkgList.end();
    for(begin; begin != end; begin++)
    {
		AddItem(begin->tDPH.nID, *begin);
		AddKeyIDList(&(*begin));
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocUnitObjPkg::InitPkg()
{
	TMapDBPoInAcDocUnitObjPkgItor begin, end;
	begin = m_tMap.begin();		end = m_tMap.end();
	for(begin; begin != end; begin++)
	{
		PDB_PO_IN_AC_DOC_UNIT pdpfou = t_ManagePoInAcDocUnit->FindItem(begin->second.tDPH.nPolicyID);
		if(!pdpfou)
		{
			WriteLogE("not find po_in_ac_doc_unit information [%d]:po_id[%d]:[%d]", begin->second.tDPH.nPolicyID, begin->first, ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			continue;
		}

		pdpfou->tDPH._add_key_id_value(SS_PO_IN_AC_UNIT_KEY_TYPE_OBJECT, begin->first, begin->second.tDPH.nUnitID);
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocUnitObjPkg::GetHash(UINT32 nID, String& strOrgValue)
{
	PDB_PO_IN_AC_DOC_UNIT_OBJ_PKG pdpiaduop 			= NULL;
	{
		if( (pdpiaduop = FindItem(nID)) == NULL)
		{
			WriteLogE("not find po_in_ac_doc_unit_obj_pkg by hash : [%d]", ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			return ERR_INFO_NOT_OP_BECAUSE_NOT_FIND;
		}
	}

	{
		t_ManagePoInAcDocObjUnit->GetHash(pdpiaduop->tDPH.nUnitID, EmptyStr(m_strHashValue));
		strOrgValue += m_strHashValue;
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocUnitObjPkg::AddPoInAcDocUnitObjPkg(DB_PO_IN_AC_DOC_UNIT_OBJ_PKG&	dpiaduop)
{
	if(SetER(t_DBMgrPoInAcDocUnitObjPkg->InsertExecute(&dpiaduop)))
    {
    	return g_nErrRtn;
    }

	AddItem(dpiaduop.tDPH.nID, dpiaduop);
	AddKeyIDList(&dpiaduop);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocUnitObjPkg::EditPoInAcDocUnitObjPkg(DB_PO_IN_AC_DOC_UNIT_OBJ_PKG&	dpiaduop)
{
	PDB_PO_IN_AC_DOC_UNIT_OBJ_PKG pdpiaduop = FindItem(dpiaduop.tDPH.nID);
	if(!pdpiaduop)	return ERR_DBMS_UPDATE_FAIL;

	if(SetER(t_DBMgrPoInAcDocUnitObjPkg->UpdateExecute(&dpiaduop)))
    {
    	return g_nErrRtn;
    }

    EditItem(dpiaduop.tDPH.nID, dpiaduop);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocUnitObjPkg::DelPoInAcDocUnitObjPkg(UINT32 nID)
{
	PDB_PO_IN_AC_DOC_UNIT_OBJ_PKG pdpiaduop = FindItem(nID);
	if(!pdpiaduop)	return ERR_DBMS_DELETE_FAIL;

	if(SetER(t_DBMgrPoInAcDocUnitObjPkg->DeleteExecute(pdpiaduop->tDPH.nID)))
    {
    	return g_nErrRtn;
    }

	DelKeyIDList(pdpiaduop);
    DeleteItem(nID);
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocUnitObjPkg::GetPoIDListFromUnitPkg(UINT32 nUnitID, TListID& tListID)
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

INT32					CManagePoInAcDocUnitObjPkg::ClearItemByPolicyID(UINT32 nPolicyID)
{
	TListID tIDList;
	GetItemIDList(tIDList);

	TListIDItor begin, end;
	begin = tIDList.begin();	end = tIDList.end();
	for(begin; begin != end; begin++)
	{
		PDB_PO_IN_AC_DOC_UNIT_OBJ_PKG pdpiaduop = FindItem(*begin);
		if(pdpiaduop->tDPH.nPolicyID != nPolicyID)	continue;

		DelPoInAcDocUnitObjPkg(*begin);
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocUnitObjPkg::ClearPkgUnitByPolicyID(UINT32 nPolicyID)
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
			t_ManagePoInAcDocObjUnit->DelPoInAcDocObjUnit(pDPH->nUnitID);
		}

		DelPoInAcDocUnitObjPkg(*begin);
	}
	return 0;
}
//---------------------------------------------------------------------------

String					CManagePoInAcDocUnitObjPkg::GetName(UINT32 nID)
{
	PDB_PO_IN_AC_DOC_UNIT_OBJ_PKG pdpiaduop = FindItem(nID);
    if(!pdpiaduop)	return "";
    return pdpiaduop->tDPH.strName;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocUnitObjPkg::SetPkt(MemToken& SendToken)
{
    SendToken.TokenAdd_32(m_tMap.size());

	TMapDBPoInAcDocUnitObjPkgItor begin, end;
    begin = m_tMap.begin();	end = m_tMap.end();
    for(begin; begin != end; begin++)
    {
    	SetPkt(&(begin->second), SendToken);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocUnitObjPkg::SetPkt(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_AC_DOC_UNIT_OBJ_PKG pdpiaduop = FindItem(nID);
	if(!pdpiaduop)	return -1;

	return SetPkt(pdpiaduop, SendToken);
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocUnitObjPkg::SetPkt(PDB_PO_IN_AC_DOC_UNIT_OBJ_PKG pdpiaduop, MemToken& SendToken)
{
	SendToken.TokenAdd_DPH(pdpiaduop->tDPH);

	SendToken.TokenSet_Block();
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocUnitObjPkg::GetPkt(MemToken& RecvToken, DB_PO_IN_AC_DOC_UNIT_OBJ_PKG& dpiaduop)
{
	if (!RecvToken.TokenDel_DPH(dpiaduop.tDPH))				goto	INVALID_PKT;

	RecvToken.TokenSkip_Block();
	return 0;
INVALID_PKT:
	return -1;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocUnitObjPkg::SetPktHost(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_AC_DOC_UNIT_OBJ_PKG pdpiaduop = FindItem(nID);
	if(!pdpiaduop)	return -1;

	SetPkt(pdpiaduop, SendToken);

	return t_ManagePoInAcDocObjUnit->SetPkt(pdpiaduop->tDPH.nUnitID, SendToken);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------



