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
#include "ManagePoInAcSfPkg.h"

//---------------------------------------------------------------------------

CManagePoInAcSfPkg*	t_ManagePoInAcSfPkg = NULL;

//---------------------------------------------------------------------------

CManagePoInAcSfPkg::CManagePoInAcSfPkg()
{
	t_DBMgrPoInAcSfPkg	= new CDBMgrPoInAcSfPkg();
}
//---------------------------------------------------------------------------

CManagePoInAcSfPkg::~CManagePoInAcSfPkg()
{
	if(t_DBMgrPoInAcSfPkg)	{	delete t_DBMgrPoInAcSfPkg;	t_DBMgrPoInAcSfPkg = NULL;	}
}
//---------------------------------------------------------------------------

INT32		CManagePoInAcSfPkg::LoadDBMS()
{
	TListDBPoInAcSfPkg tDBPoInAcSfPkgList;
    TListDBPoInAcSfPkgItor begin, end;
	if(SetER(t_DBMgrPoInAcSfPkg->LoadExecute(&tDBPoInAcSfPkgList)))
    {
    	return g_nErrRtn;
    }

    begin = tDBPoInAcSfPkgList.begin();	end = tDBPoInAcSfPkgList.end();
    for(begin; begin != end; begin++)
    {
		AddItem(begin->tDPH.nID, *begin);
		AddKeyIDList(&(*begin));
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfPkg::InitPkg()
{
	TMapDBPoInAcSfPkgItor begin, end;
	begin = m_tMap.begin();		end = m_tMap.end();
	for(begin; begin != end; begin++)
	{
		PDB_PO_IN_AC_SF pdpfp = t_ManagePoInAcSf->FindItem(begin->second.tDPH.nPolicyID);
		if(!pdpfp)
		{
			WriteLogE("not find po_in_ac_sf_pkg information [%d]:po_id[%d]:[%d]", begin->second.tDPH.nPolicyID, begin->first, ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			continue;
		}

		pdpfp->tDPH._add_id_value(begin->first, begin->second.tDPH.nUnitID);
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfPkg::GetHash(UINT32 nID, String& strOrgValue)
{
	PDB_PO_IN_AC_SF_PKG pdpiafp 			= NULL;
	{
		if( (pdpiafp = FindItem(nID)) == NULL)
		{
			WriteLogE("not find po_in_ac_sf_pkg by hash : [%d]", ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			return ERR_INFO_NOT_OP_BECAUSE_NOT_FIND;
		}
	}

	{
		t_ManagePoInAcSfUnit->GetHash(pdpiafp->tDPH.nUnitID, EmptyStr(m_strHashValue));		
		strOrgValue += m_strHashValue;
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfPkg::AddPoInAcSfPkg(DB_PO_IN_AC_SF_PKG&	dpiafp)
{
	if(SetER(t_DBMgrPoInAcSfPkg->InsertExecute(&dpiafp)))
    {
    	return g_nErrRtn;
    }

	AddItem(dpiafp.tDPH.nID, dpiafp);
	AddKeyIDList(&dpiafp);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfPkg::EditPoInAcSfPkg(DB_PO_IN_AC_SF_PKG&	dpiafp)
{
	PDB_PO_IN_AC_SF_PKG pdpiafp = FindItem(dpiafp.tDPH.nID);
	if(!pdpiafp)	return ERR_DBMS_UPDATE_FAIL;

	if(SetER(t_DBMgrPoInAcSfPkg->UpdateExecute(&dpiafp)))
    {
    	return g_nErrRtn;
    }

    EditItem(dpiafp.tDPH.nID, dpiafp);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfPkg::DelPoInAcSfPkg(UINT32 nID)
{
	PDB_PO_IN_AC_SF_PKG pdpiafp = FindItem(nID);
	if(!pdpiafp)	return ERR_DBMS_DELETE_FAIL;

	if(SetER(t_DBMgrPoInAcSfPkg->DeleteExecute(pdpiafp->tDPH.nID)))
    {
    	return g_nErrRtn;
    }

	DelKeyIDList(pdpiafp);
    DeleteItem(nID);
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfPkg::ClearItemByPolicyID(UINT32 nPolicyID)
{
	TListID tIDList;
	GetItemIDList(tIDList);

	TListIDItor begin, end;
	begin = tIDList.begin();	end = tIDList.end();
	for(begin; begin != end; begin++)
	{
		PDB_PO_IN_AC_SF_PKG pdpiafp = FindItem(*begin);
		if(pdpiafp->tDPH.nPolicyID != nPolicyID)	continue;

		DelPoInAcSfPkg(*begin);
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfPkg::ClearPkgUnitByPolicyID(UINT32 nPolicyID)
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
			t_ManagePoInAcSfUnit->DelPoInAcSfUnitWithSubPkg(pDPH->nUnitID);
		}

		DelPoInAcSfPkg(*begin);
	}
	return 0;
}
//---------------------------------------------------------------------------

String					CManagePoInAcSfPkg::GetName(UINT32 nID)
{
	PDB_PO_IN_AC_SF_PKG pdpiafp = FindItem(nID);
    if(!pdpiafp)	return "";
    return pdpiafp->tDPH.strName;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfPkg::SetPkt(MemToken& SendToken)
{
    SendToken.TokenAdd_32(m_tMap.size());

	TMapDBPoInAcSfPkgItor begin, end;
    begin = m_tMap.begin();	end = m_tMap.end();
    for(begin; begin != end; begin++)
    {
    	SetPkt(&(begin->second), SendToken);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfPkg::SetPkt(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_AC_SF_PKG pdpiafp = FindItem(nID);
	if(!pdpiafp)	return -1;

	return SetPkt(pdpiafp, SendToken);
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfPkg::SetPkt(PDB_PO_IN_AC_SF_PKG pdpiafp, MemToken& SendToken)
{
	SendToken.TokenAdd_DPH(pdpiafp->tDPH);

	SendToken.TokenSet_Block();
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfPkg::GetPkt(MemToken& RecvToken, DB_PO_IN_AC_SF_PKG& dpiafp)
{
	if (!RecvToken.TokenDel_DPH(dpiafp.tDPH))				goto	INVALID_PKT;	

	RecvToken.TokenSkip_Block();
	return 0;
INVALID_PKT:
	return -1;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfPkg::SetPktHost(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_AC_SF_PKG pdpiafp = FindItem(nID);
	if(!pdpiafp)	return -1;

	SetPkt(pdpiafp, SendToken);

	return t_ManagePoInAcSfUnit->SetPktHost(pdpiafp->tDPH.nUnitID, SendToken);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------



