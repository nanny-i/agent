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
#include "ManagePoInRegSWObjUnit.h"
#include "ManagePoInRegSWPkg.h"
#include "ManagePoInRegSWUnitObjPkg.h"

//---------------------------------------------------------------------------

CManagePoInRegSWUnitObjPkg*	t_ManagePoInRegSWUnitObjPkg = NULL;

//---------------------------------------------------------------------------

CManagePoInRegSWUnitObjPkg::CManagePoInRegSWUnitObjPkg()
{
	t_DBMgrPoInRegSWUnitObjPkg	= new CDBMgrPoInRegSWUnitObjPkg();
}
//---------------------------------------------------------------------------

CManagePoInRegSWUnitObjPkg::~CManagePoInRegSWUnitObjPkg()
{
	if(t_DBMgrPoInRegSWUnitObjPkg)	{	delete t_DBMgrPoInRegSWUnitObjPkg;	t_DBMgrPoInRegSWUnitObjPkg = NULL;	}
}
//---------------------------------------------------------------------------

INT32		CManagePoInRegSWUnitObjPkg::LoadDBMS()
{
	TListDBPoInRegSWUnitObjPkg tDBPoInRegSWUnitObjPkgList;
    TListDBPoInRegSWUnitObjPkgItor begin, end;
	if(SetER(t_DBMgrPoInRegSWUnitObjPkg->LoadExecute(&tDBPoInRegSWUnitObjPkgList)))
    {
    	return g_nErrRtn;
    }

    begin = tDBPoInRegSWUnitObjPkgList.begin();	end = tDBPoInRegSWUnitObjPkgList.end();
    for(begin; begin != end; begin++)
    {
		AddItem(begin->tDPH.nID, *begin);
		AddKeyIDList(&(*begin));
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSWUnitObjPkg::InitPkg()
{
	TMapDBPoInRegSWUnitObjPkgItor begin, end;
	begin = m_tMap.begin();		end = m_tMap.end();
	for(begin; begin != end; begin++)
	{
		PDB_PO_IN_REG_SW_UNIT pdpfou = t_ManagePoInRegSWUnit->FindItem(begin->second.tDPH.nPolicyID);
		if(!pdpfou)
		{
			WriteLogE("not find po_in_reg_sw_unit information [%d]:po_id[%d]:[%d]", begin->second.tDPH.nPolicyID, begin->first, ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			continue;
		}

		pdpfou->tDPH._add_key_id_value(SS_PO_IN_REG_UNIT_KEY_TYPE_OBJECT, begin->first, begin->second.tDPH.nUnitID);
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSWUnitObjPkg::GetHash(UINT32 nID, String& strOrgValue)
{
	PDB_PO_IN_REG_SW_UNIT_OBJ_PKG pdpirsuop 			= NULL;
	{
		if( (pdpirsuop = FindItem(nID)) == NULL)
		{
			WriteLogE("not find po_in_reg_sw_unit_obj_pkg by hash : [%d]", ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			return ERR_INFO_NOT_OP_BECAUSE_NOT_FIND;
		}
	}

	{
		t_ManagePoInRegSWObjUnit->GetHash(pdpirsuop->tDPH.nUnitID, EmptyStr(m_strHashValue));
		strOrgValue += m_strHashValue;
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSWUnitObjPkg::AddPoInRegSWUnitObjPkg(DB_PO_IN_REG_SW_UNIT_OBJ_PKG&	dpirsuop)
{
	if(SetER(t_DBMgrPoInRegSWUnitObjPkg->InsertExecute(&dpirsuop)))
    {
    	return g_nErrRtn;
    }

	AddItem(dpirsuop.tDPH.nID, dpirsuop);
	AddKeyIDList(&dpirsuop);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSWUnitObjPkg::EditPoInRegSWUnitObjPkg(DB_PO_IN_REG_SW_UNIT_OBJ_PKG&	dpirsuop)
{
	PDB_PO_IN_REG_SW_UNIT_OBJ_PKG pdpirsuop = FindItem(dpirsuop.tDPH.nID);
	if(!pdpirsuop)	return ERR_DBMS_UPDATE_FAIL;

	if(SetER(t_DBMgrPoInRegSWUnitObjPkg->UpdateExecute(&dpirsuop)))
    {
    	return g_nErrRtn;
    }

    EditItem(dpirsuop.tDPH.nID, dpirsuop);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSWUnitObjPkg::DelPoInRegSWUnitObjPkg(UINT32 nID)
{
	PDB_PO_IN_REG_SW_UNIT_OBJ_PKG pdpirsuop = FindItem(nID);
	if(!pdpirsuop)	return ERR_DBMS_DELETE_FAIL;

	if(SetER(t_DBMgrPoInRegSWUnitObjPkg->DeleteExecute(pdpirsuop->tDPH.nID)))
    {
    	return g_nErrRtn;
    }

	DelKeyIDList(pdpirsuop);
    DeleteItem(nID);
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSWUnitObjPkg::GetPoIDListFromUnitPkg(UINT32 nUnitID, TListID& tListID)
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

INT32					CManagePoInRegSWUnitObjPkg::ClearItemByPolicyID(UINT32 nPolicyID)
{
	TListID tIDList;
	GetItemIDList(tIDList);

	TListIDItor begin, end;
	begin = tIDList.begin();	end = tIDList.end();
	for(begin; begin != end; begin++)
	{
		PDB_PO_IN_REG_SW_UNIT_OBJ_PKG pdpirsuop = FindItem(*begin);
		if(pdpirsuop->tDPH.nPolicyID != nPolicyID)	continue;

		DelPoInRegSWUnitObjPkg(*begin);
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSWUnitObjPkg::ClearPkgUnitByPolicyID(UINT32 nPolicyID)
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
			t_ManagePoInRegSWObjUnit->DelPoInRegSWObjUnit(pDPH->nUnitID);
		}

		DelPoInRegSWUnitObjPkg(*begin);
	}
	return 0;
}
//---------------------------------------------------------------------------

String					CManagePoInRegSWUnitObjPkg::GetName(UINT32 nID)
{
	PDB_PO_IN_REG_SW_UNIT_OBJ_PKG pdpirsuop = FindItem(nID);
    if(!pdpirsuop)	return "";
    return pdpirsuop->tDPH.strName;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManagePoInRegSWUnitObjPkg::SetPkt(MemToken& SendToken)
{
    SendToken.TokenAdd_32(m_tMap.size());

	TMapDBPoInRegSWUnitObjPkgItor begin, end;
    begin = m_tMap.begin();	end = m_tMap.end();
    for(begin; begin != end; begin++)
    {
    	SetPkt(&(begin->second), SendToken);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSWUnitObjPkg::SetPkt(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_REG_SW_UNIT_OBJ_PKG pdpirsuop = FindItem(nID);
	if(!pdpirsuop)	return -1;

	return SetPkt(pdpirsuop, SendToken);
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSWUnitObjPkg::SetPkt(PDB_PO_IN_REG_SW_UNIT_OBJ_PKG pdpirsuop, MemToken& SendToken)
{
	SendToken.TokenAdd_DPH(pdpirsuop->tDPH);

	SendToken.TokenSet_Block();
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSWUnitObjPkg::GetPkt(MemToken& RecvToken, DB_PO_IN_REG_SW_UNIT_OBJ_PKG& dpirsuop)
{
	if (!RecvToken.TokenDel_DPH(dpirsuop.tDPH))				goto	INVALID_PKT;

	RecvToken.TokenSkip_Block();
	return 0;
INVALID_PKT:
	return -1;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManagePoInRegSWUnitObjPkg::SetPktHost(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_REG_SW_UNIT_OBJ_PKG pdpirsuop = FindItem(nID);
	if(!pdpirsuop)	return -1;

	SetPkt(pdpirsuop, SendToken);

	return t_ManagePoInRegSWObjUnit->SetPkt(pdpirsuop->tDPH.nUnitID, SendToken);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------



