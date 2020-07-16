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
#include "ManagePoInRegSvcUnit.h"
#include "ManagePoInRegSvcObjUnit.h"
#include "ManagePoInRegSvcPkg.h"
#include "ManagePoInRegSvcUnitObjPkg.h"

//---------------------------------------------------------------------------

CManagePoInRegSvcUnitObjPkg*	t_ManagePoInRegSvcUnitObjPkg = NULL;

//---------------------------------------------------------------------------

CManagePoInRegSvcUnitObjPkg::CManagePoInRegSvcUnitObjPkg()
{
	t_DBMgrPoInRegSvcUnitObjPkg	= new CDBMgrPoInRegSvcUnitObjPkg();
}
//---------------------------------------------------------------------------

CManagePoInRegSvcUnitObjPkg::~CManagePoInRegSvcUnitObjPkg()
{
	if(t_DBMgrPoInRegSvcUnitObjPkg)	{	delete t_DBMgrPoInRegSvcUnitObjPkg;	t_DBMgrPoInRegSvcUnitObjPkg = NULL;	}
}
//---------------------------------------------------------------------------

INT32		CManagePoInRegSvcUnitObjPkg::LoadDBMS()
{
	TListDBPoInRegSvcUnitObjPkg tDBPoInRegSvcUnitObjPkgList;
    TListDBPoInRegSvcUnitObjPkgItor begin, end;
	if(SetER(t_DBMgrPoInRegSvcUnitObjPkg->LoadExecute(&tDBPoInRegSvcUnitObjPkgList)))
    {
    	return g_nErrRtn;
    }

    begin = tDBPoInRegSvcUnitObjPkgList.begin();	end = tDBPoInRegSvcUnitObjPkgList.end();
    for(begin; begin != end; begin++)
    {
		AddItem(begin->tDPH.nID, *begin);
		AddKeyIDList(&(*begin));
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvcUnitObjPkg::InitPkg()
{
	TMapDBPoInRegSvcUnitObjPkgItor begin, end;
	begin = m_tMap.begin();		end = m_tMap.end();
	for(begin; begin != end; begin++)
	{
		PDB_PO_IN_REG_SVC_UNIT pdpfou = t_ManagePoInRegSvcUnit->FindItem(begin->second.tDPH.nPolicyID);
		if(!pdpfou)
		{
			WriteLogE("not find po_in_reg_svc_unit information [%d]:po_id[%d]:[%d]", begin->second.tDPH.nPolicyID, begin->first, ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			continue;
		}

		pdpfou->tDPH._add_key_id_value(SS_PO_IN_REG_UNIT_KEY_TYPE_OBJECT, begin->first, begin->second.tDPH.nUnitID);
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvcUnitObjPkg::GetHash(UINT32 nID, String& strOrgValue)
{
	PDB_PO_IN_REG_SVC_UNIT_OBJ_PKG pdpirsuop 			= NULL;
	{
		if( (pdpirsuop = FindItem(nID)) == NULL)
		{
			WriteLogE("not find po_in_reg_svc_unit_obj_pkg by hash : [%d]", ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			return ERR_INFO_NOT_OP_BECAUSE_NOT_FIND;
		}
	}

	{
		t_ManagePoInRegSvcObjUnit->GetHash(pdpirsuop->tDPH.nUnitID, EmptyStr(m_strHashValue));
		strOrgValue += m_strHashValue;
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvcUnitObjPkg::AddPoInRegSvcUnitObjPkg(DB_PO_IN_REG_SVC_UNIT_OBJ_PKG&	dpirsuop)
{
	if(SetER(t_DBMgrPoInRegSvcUnitObjPkg->InsertExecute(&dpirsuop)))
    {
    	return g_nErrRtn;
    }

	AddItem(dpirsuop.tDPH.nID, dpirsuop);
	AddKeyIDList(&dpirsuop);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvcUnitObjPkg::EditPoInRegSvcUnitObjPkg(DB_PO_IN_REG_SVC_UNIT_OBJ_PKG&	dpirsuop)
{
	PDB_PO_IN_REG_SVC_UNIT_OBJ_PKG pdpirsuop = FindItem(dpirsuop.tDPH.nID);
	if(!pdpirsuop)	return ERR_DBMS_UPDATE_FAIL;

	if(SetER(t_DBMgrPoInRegSvcUnitObjPkg->UpdateExecute(&dpirsuop)))
    {
    	return g_nErrRtn;
    }

    EditItem(dpirsuop.tDPH.nID, dpirsuop);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvcUnitObjPkg::DelPoInRegSvcUnitObjPkg(UINT32 nID)
{
	PDB_PO_IN_REG_SVC_UNIT_OBJ_PKG pdpirsuop = FindItem(nID);
	if(!pdpirsuop)	return ERR_DBMS_DELETE_FAIL;

	if(SetER(t_DBMgrPoInRegSvcUnitObjPkg->DeleteExecute(pdpirsuop->tDPH.nID)))
    {
    	return g_nErrRtn;
    }

	DelKeyIDList(pdpirsuop);
    DeleteItem(nID);
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvcUnitObjPkg::GetPoIDListFromUnitPkg(UINT32 nUnitID, TListID& tListID)
{
	TMapID tPoIDMap;
	TListID tUnitIDList;
	GetPoIDFromPkgList(nUnitID, tUnitIDList);
	
	{
		TListIDItor begin, end;
		begin = tUnitIDList.begin();	end = tUnitIDList.end();
		for(begin; begin != end; begin++)
		{
			t_ManagePoInRegSvcPkg->GetPoIDFromPkgMap(*begin, tPoIDMap);	
		}
	}
	ConvertMapToList(tPoIDMap, tListID);
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvcUnitObjPkg::ClearItemByPolicyID(UINT32 nPolicyID)
{
	TListID tIDList;
	GetItemIDList(tIDList);

	TListIDItor begin, end;
	begin = tIDList.begin();	end = tIDList.end();
	for(begin; begin != end; begin++)
	{
		PDB_PO_IN_REG_SVC_UNIT_OBJ_PKG pdpirsuop = FindItem(*begin);
		if(pdpirsuop->tDPH.nPolicyID != nPolicyID)	continue;

		DelPoInRegSvcUnitObjPkg(*begin);
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvcUnitObjPkg::ClearPkgUnitByPolicyID(UINT32 nPolicyID)
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
			t_ManagePoInRegSvcObjUnit->DelPoInRegSvcObjUnit(pDPH->nUnitID);
		}

		DelPoInRegSvcUnitObjPkg(*begin);
	}
	return 0;
}
//---------------------------------------------------------------------------

String					CManagePoInRegSvcUnitObjPkg::GetName(UINT32 nID)
{
	PDB_PO_IN_REG_SVC_UNIT_OBJ_PKG pdpirsuop = FindItem(nID);
    if(!pdpirsuop)	return "";
    return pdpirsuop->tDPH.strName;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvcUnitObjPkg::SetPkt(MemToken& SendToken)
{
    SendToken.TokenAdd_32(m_tMap.size());

	TMapDBPoInRegSvcUnitObjPkgItor begin, end;
    begin = m_tMap.begin();	end = m_tMap.end();
    for(begin; begin != end; begin++)
    {
    	SetPkt(&(begin->second), SendToken);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvcUnitObjPkg::SetPkt(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_REG_SVC_UNIT_OBJ_PKG pdpirsuop = FindItem(nID);
	if(!pdpirsuop)	return -1;

	return SetPkt(pdpirsuop, SendToken);
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvcUnitObjPkg::SetPkt(PDB_PO_IN_REG_SVC_UNIT_OBJ_PKG pdpirsuop, MemToken& SendToken)
{
	SendToken.TokenAdd_DPH(pdpirsuop->tDPH);

	SendToken.TokenSet_Block();
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvcUnitObjPkg::GetPkt(MemToken& RecvToken, DB_PO_IN_REG_SVC_UNIT_OBJ_PKG& dpirsuop)
{
	if (!RecvToken.TokenDel_DPH(dpirsuop.tDPH))				goto	INVALID_PKT;

	RecvToken.TokenSkip_Block();
	return 0;
INVALID_PKT:
	return -1;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvcUnitObjPkg::SetPktHost(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_REG_SVC_UNIT_OBJ_PKG pdpirsuop = FindItem(nID);
	if(!pdpirsuop)	return -1;

	SetPkt(pdpirsuop, SendToken);

	return t_ManagePoInRegSvcObjUnit->SetPkt(pdpirsuop->tDPH.nUnitID, SendToken);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------



