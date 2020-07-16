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
#include "ManagePoInRegSys.h"
#include "ManagePoInRegSysUnit.h"
#include "ManagePoInRegSysPkg.h"

//---------------------------------------------------------------------------

CManagePoInRegSysPkg*	t_ManagePoInRegSysPkg = NULL;

//---------------------------------------------------------------------------

CManagePoInRegSysPkg::CManagePoInRegSysPkg()
{
	t_DBMgrPoInRegSysPkg	= new CDBMgrPoInRegSysPkg();
}
//---------------------------------------------------------------------------

CManagePoInRegSysPkg::~CManagePoInRegSysPkg()
{
	if(t_DBMgrPoInRegSysPkg)	{	delete t_DBMgrPoInRegSysPkg;	t_DBMgrPoInRegSysPkg = NULL;	}
}
//---------------------------------------------------------------------------

INT32		CManagePoInRegSysPkg::LoadDBMS()
{
	TListDBPoInRegSysPkg tDBPoInRegSysPkgList;
    TListDBPoInRegSysPkgItor begin, end;
	if(SetER(t_DBMgrPoInRegSysPkg->LoadExecute(&tDBPoInRegSysPkgList)))
    {
    	return g_nErrRtn;
    }

    begin = tDBPoInRegSysPkgList.begin();	end = tDBPoInRegSysPkgList.end();
    for(begin; begin != end; begin++)
    {
		AddItem(begin->tDPH.nID, *begin);
		AddKeyIDList(&(*begin));
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSysPkg::InitPkg()
{
	TMapDBPoInRegSysPkgItor begin, end;
	begin = m_tMap.begin();		end = m_tMap.end();
	for(begin; begin != end; begin++)
	{
		PDB_PO_IN_REG_SYS pdpfe = t_ManagePoInRegSys->FindItem(begin->second.tDPH.nPolicyID);
		if(!pdpfe)
		{
			WriteLogE("not find po_in_reg_sys_pkg information [%d]:po_id[%d]:[%d]", begin->second.tDPH.nPolicyID, begin->first, ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			continue;
		}

		pdpfe->tDPH._add_id_value(begin->first, begin->second.tDPH.nUnitID);
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSysPkg::GetHash(UINT32 nID, String& strOrgValue)
{
	PDB_PO_IN_REG_SYS_PKG pdpirsp 			= NULL;
	{
		if( (pdpirsp = FindItem(nID)) == NULL)
		{
			WriteLogE("not find po_in_reg_sys_pkg by hash : [%d]", ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			return ERR_INFO_NOT_OP_BECAUSE_NOT_FIND;
		}
	}

	{
		t_ManagePoInRegSysUnit->GetHash(pdpirsp->tDPH.nUnitID, strOrgValue);
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSysPkg::AddPoInRegSysPkg(DB_PO_IN_REG_SYS_PKG&	dpirsp)
{
	if(SetER(t_DBMgrPoInRegSysPkg->InsertExecute(&dpirsp)))
    {
    	return g_nErrRtn;
    }

	AddItem(dpirsp.tDPH.nID, dpirsp);
	AddKeyIDList(&dpirsp);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSysPkg::EditPoInRegSysPkg(DB_PO_IN_REG_SYS_PKG&	dpirsp)
{
	PDB_PO_IN_REG_SYS_PKG pdpirsp = FindItem(dpirsp.tDPH.nID);
	if(!pdpirsp)	return ERR_DBMS_UPDATE_FAIL;

	if(SetER(t_DBMgrPoInRegSysPkg->UpdateExecute(&dpirsp)))
    {
    	return g_nErrRtn;
    }

    EditItem(dpirsp.tDPH.nID, dpirsp);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSysPkg::DelPoInRegSysPkg(UINT32 nID)
{
	PDB_PO_IN_REG_SYS_PKG pdpirsp = FindItem(nID);
	if(!pdpirsp)	return ERR_DBMS_DELETE_FAIL;

	if(SetER(t_DBMgrPoInRegSysPkg->DeleteExecute(pdpirsp->tDPH.nID)))
    {
    	return g_nErrRtn;
    }

	DelKeyIDList(pdpirsp);
    DeleteItem(nID);
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSysPkg::ClearItemByPolicyID(UINT32 nPolicyID)
{
	TListID tIDList;
	GetItemIDList(tIDList);

	TListIDItor begin, end;
	begin = tIDList.begin();	end = tIDList.end();
	for(begin; begin != end; begin++)
	{
		PDB_PO_IN_REG_SYS_PKG pdpirsp = FindItem(*begin);
		if(pdpirsp->tDPH.nPolicyID != nPolicyID)	continue;

		DelPoInRegSysPkg(*begin);
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSysPkg::ClearPkgUnitByPolicyID(UINT32 nPolicyID)
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
			t_ManagePoInRegSysUnit->DelPoInRegSysUnit(pDPH->nUnitID);
		}

		DelPoInRegSysPkg(*begin);
	}
	return 0;
}
//---------------------------------------------------------------------------

String					CManagePoInRegSysPkg::GetName(UINT32 nID)
{
	PDB_PO_IN_REG_SYS_PKG pdpirsp = FindItem(nID);
    if(!pdpirsp)	return "";
    return pdpirsp->tDPH.strName;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManagePoInRegSysPkg::SetPkt(MemToken& SendToken)
{
    SendToken.TokenAdd_32(m_tMap.size());

	TMapDBPoInRegSysPkgItor begin, end;
    begin = m_tMap.begin();	end = m_tMap.end();
    for(begin; begin != end; begin++)
    {
    	SetPkt(&(begin->second), SendToken);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSysPkg::SetPkt(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_REG_SYS_PKG pdpirsp = FindItem(nID);
	if(!pdpirsp)	return -1;

	return SetPkt(pdpirsp, SendToken);
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSysPkg::SetPkt(PDB_PO_IN_REG_SYS_PKG pdpirsp, MemToken& SendToken)
{
	SendToken.TokenAdd_DPH(pdpirsp->tDPH);

	SendToken.TokenSet_Block();
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSysPkg::GetPkt(MemToken& RecvToken, DB_PO_IN_REG_SYS_PKG& dpirsp)
{
	if (!RecvToken.TokenDel_DPH(dpirsp.tDPH))				goto	INVALID_PKT;

	RecvToken.TokenSkip_Block();
	return 0;
INVALID_PKT:
	return -1;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManagePoInRegSysPkg::SetPktHost(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_REG_SYS_PKG pdpirsp = FindItem(nID);
	if(!pdpirsp)	return -1;

	SetPkt(pdpirsp, SendToken);

	return t_ManagePoInRegSysUnit->SetPkt(pdpirsp->tDPH.nUnitID, SendToken);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------



