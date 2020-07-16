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
#include "ManagePoInRegSvc.h"
#include "ManagePoInRegSvcUnit.h"
#include "ManagePoInRegSvcPkg.h"

//---------------------------------------------------------------------------

CManagePoInRegSvcPkg*	t_ManagePoInRegSvcPkg = NULL;

//---------------------------------------------------------------------------

CManagePoInRegSvcPkg::CManagePoInRegSvcPkg()
{
	t_DBMgrPoInRegSvcPkg	= new CDBMgrPoInRegSvcPkg();
}
//---------------------------------------------------------------------------

CManagePoInRegSvcPkg::~CManagePoInRegSvcPkg()
{
	if(t_DBMgrPoInRegSvcPkg)	{	delete t_DBMgrPoInRegSvcPkg;	t_DBMgrPoInRegSvcPkg = NULL;	}
}
//---------------------------------------------------------------------------

INT32		CManagePoInRegSvcPkg::LoadDBMS()
{
	TListDBPoInRegSvcPkg tDBPoInRegSvcPkgList;
    TListDBPoInRegSvcPkgItor begin, end;
	if(SetER(t_DBMgrPoInRegSvcPkg->LoadExecute(&tDBPoInRegSvcPkgList)))
    {
    	return g_nErrRtn;
    }

    begin = tDBPoInRegSvcPkgList.begin();	end = tDBPoInRegSvcPkgList.end();
    for(begin; begin != end; begin++)
    {
		AddItem(begin->tDPH.nID, *begin);
		AddKeyIDList(&(*begin));
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvcPkg::InitPkg()
{
	TMapDBPoInRegSvcPkgItor begin, end;
	begin = m_tMap.begin();		end = m_tMap.end();
	for(begin; begin != end; begin++)
	{
		PDB_PO_IN_REG_SVC pdpfp = t_ManagePoInRegSvc->FindItem(begin->second.tDPH.nPolicyID);
		if(!pdpfp)
		{
			WriteLogE("not find po_in_reg_svc_pkg information [%d]:po_id[%d]:[%d]", begin->second.tDPH.nPolicyID, begin->first, ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			continue;
		}

		pdpfp->tDPH._add_id_value(begin->first, begin->second.tDPH.nUnitID);
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvcPkg::GetHash(UINT32 nID, String& strOrgValue)
{
	PDB_PO_IN_REG_SVC_PKG pdpirsp 			= NULL;
	{
		if( (pdpirsp = FindItem(nID)) == NULL)
		{
			WriteLogE("not find po_in_reg_svc_pkg by hash : [%d]", ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			return ERR_INFO_NOT_OP_BECAUSE_NOT_FIND;
		}
	}

	{
		EmptyStr(m_strHashValue);		

		t_ManagePoInRegSvcUnit->GetHash(pdpirsp->tDPH.nUnitID, m_strHashValue);		
		strOrgValue += m_strHashValue;
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvcPkg::AddPoInRegSvcPkg(DB_PO_IN_REG_SVC_PKG&	dpirsp)
{
	if(SetER(t_DBMgrPoInRegSvcPkg->InsertExecute(&dpirsp)))
    {
    	return g_nErrRtn;
    }

	AddItem(dpirsp.tDPH.nID, dpirsp);
	AddKeyIDList(&dpirsp);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvcPkg::EditPoInRegSvcPkg(DB_PO_IN_REG_SVC_PKG&	dpirsp)
{
	PDB_PO_IN_REG_SVC_PKG pdpirsp = FindItem(dpirsp.tDPH.nID);
	if(!pdpirsp)	return ERR_DBMS_UPDATE_FAIL;

	if(SetER(t_DBMgrPoInRegSvcPkg->UpdateExecute(&dpirsp)))
    {
    	return g_nErrRtn;
    }

    EditItem(dpirsp.tDPH.nID, dpirsp);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvcPkg::DelPoInRegSvcPkg(UINT32 nID)
{
	PDB_PO_IN_REG_SVC_PKG pdpirsp = FindItem(nID);
	if(!pdpirsp)	return ERR_DBMS_DELETE_FAIL;

	if(SetER(t_DBMgrPoInRegSvcPkg->DeleteExecute(pdpirsp->tDPH.nID)))
    {
    	return g_nErrRtn;
    }

	DelKeyIDList(pdpirsp);
    DeleteItem(nID);
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvcPkg::ClearItemByPolicyID(UINT32 nPolicyID)
{
	TListID tIDList;
	GetItemIDList(tIDList);

	TListIDItor begin, end;
	begin = tIDList.begin();	end = tIDList.end();
	for(begin; begin != end; begin++)
	{
		PDB_PO_IN_REG_SVC_PKG pdpirsp = FindItem(*begin);
		if(pdpirsp->tDPH.nPolicyID != nPolicyID)	continue;

		DelPoInRegSvcPkg(*begin);
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvcPkg::ClearPkgUnitByPolicyID(UINT32 nPolicyID)
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
			t_ManagePoInRegSvcUnit->DelPoInRegSvcUnitWithSubPkg(pDPH->nUnitID);
		}

		DelPoInRegSvcPkg(*begin);
	}
	return 0;
}
//---------------------------------------------------------------------------

String					CManagePoInRegSvcPkg::GetName(UINT32 nID)
{
	PDB_PO_IN_REG_SVC_PKG pdpirsp = FindItem(nID);
    if(!pdpirsp)	return "";
    return pdpirsp->tDPH.strName;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvcPkg::SetPkt(MemToken& SendToken)
{
    SendToken.TokenAdd_32(m_tMap.size());

	TMapDBPoInRegSvcPkgItor begin, end;
    begin = m_tMap.begin();	end = m_tMap.end();
    for(begin; begin != end; begin++)
    {
    	SetPkt(&(begin->second), SendToken);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvcPkg::SetPkt(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_REG_SVC_PKG pdpirsp = FindItem(nID);
	if(!pdpirsp)	return -1;

	return SetPkt(pdpirsp, SendToken);
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvcPkg::SetPkt(PDB_PO_IN_REG_SVC_PKG pdpirsp, MemToken& SendToken)
{
	SendToken.TokenAdd_DPH(pdpirsp->tDPH);	

	SendToken.TokenSet_Block();
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvcPkg::GetPkt(MemToken& RecvToken, DB_PO_IN_REG_SVC_PKG& dpirsp)
{
	if (!RecvToken.TokenDel_DPH(dpirsp.tDPH))				goto	INVALID_PKT;	

	RecvToken.TokenSkip_Block();
	return 0;
INVALID_PKT:
	return -1;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvcPkg::SetPktHost(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_REG_SVC_PKG pdpirsp = FindItem(nID);
	if(!pdpirsp)	return -1;

	SetPkt(pdpirsp, SendToken);

	return t_ManagePoInRegSvcUnit->SetPktHost(pdpirsp->tDPH.nUnitID, SendToken);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------



