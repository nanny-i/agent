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
#include "ManagePoInAcDocPkg.h"

//---------------------------------------------------------------------------

CManagePoInAcDocPkg*	t_ManagePoInAcDocPkg = NULL;

//---------------------------------------------------------------------------

CManagePoInAcDocPkg::CManagePoInAcDocPkg()
{
	t_DBMgrPoInAcDocPkg	= new CDBMgrPoInAcDocPkg();
}
//---------------------------------------------------------------------------

CManagePoInAcDocPkg::~CManagePoInAcDocPkg()
{
	if(t_DBMgrPoInAcDocPkg)	{	delete t_DBMgrPoInAcDocPkg;	t_DBMgrPoInAcDocPkg = NULL;	}
}
//---------------------------------------------------------------------------

INT32		CManagePoInAcDocPkg::LoadDBMS()
{
	TListDBPoInAcDocPkg tDBPoInAcDocPkgList;
    TListDBPoInAcDocPkgItor begin, end;
	if(SetER(t_DBMgrPoInAcDocPkg->LoadExecute(&tDBPoInAcDocPkgList)))
    {
    	return g_nErrRtn;
    }

    begin = tDBPoInAcDocPkgList.begin();	end = tDBPoInAcDocPkgList.end();
    for(begin; begin != end; begin++)
    {
		AddItem(begin->tDPH.nID, *begin);
		AddKeyIDList(&(*begin));
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocPkg::InitPkg()
{
	TMapDBPoInAcDocPkgItor begin, end;
	begin = m_tMap.begin();		end = m_tMap.end();
	for(begin; begin != end; begin++)
	{
		PDB_PO_IN_AC_DOC pdpfp = t_ManagePoInAcDoc->FindItem(begin->second.tDPH.nPolicyID);
		if(!pdpfp)
		{
			WriteLogE("not find po_in_ac_doc_pkg information [%d]:po_id[%d]:[%d]", begin->second.tDPH.nPolicyID, begin->first, ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			continue;
		}

		pdpfp->tDPH._add_id_value(begin->first, begin->second.tDPH.nUnitID);
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocPkg::GetHash(UINT32 nID, String& strOrgValue)
{
	PDB_PO_IN_AC_DOC_PKG pdpiadp 			= NULL;
	{
		if( (pdpiadp = FindItem(nID)) == NULL)
		{
			WriteLogE("not find po_in_ac_doc_pkg by hash : [%d]", ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			return ERR_INFO_NOT_OP_BECAUSE_NOT_FIND;
		}
	}

	{
		t_ManagePoInAcDocUnit->GetHash(pdpiadp->tDPH.nUnitID, EmptyStr(m_strHashValue));		
		strOrgValue += m_strHashValue;
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocPkg::AddPoInAcDocPkg(DB_PO_IN_AC_DOC_PKG&	dpiadp)
{
	if(SetER(t_DBMgrPoInAcDocPkg->InsertExecute(&dpiadp)))
    {
    	return g_nErrRtn;
    }

	AddItem(dpiadp.tDPH.nID, dpiadp);
	AddKeyIDList(&dpiadp);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocPkg::EditPoInAcDocPkg(DB_PO_IN_AC_DOC_PKG&	dpiadp)
{
	PDB_PO_IN_AC_DOC_PKG pdpiadp = FindItem(dpiadp.tDPH.nID);
	if(!pdpiadp)	return ERR_DBMS_UPDATE_FAIL;

	if(SetER(t_DBMgrPoInAcDocPkg->UpdateExecute(&dpiadp)))
    {
    	return g_nErrRtn;
    }

    EditItem(dpiadp.tDPH.nID, dpiadp);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocPkg::DelPoInAcDocPkg(UINT32 nID)
{
	PDB_PO_IN_AC_DOC_PKG pdpiadp = FindItem(nID);
	if(!pdpiadp)	return ERR_DBMS_DELETE_FAIL;

	if(SetER(t_DBMgrPoInAcDocPkg->DeleteExecute(pdpiadp->tDPH.nID)))
    {
    	return g_nErrRtn;
    }

	DelKeyIDList(pdpiadp);
    DeleteItem(nID);
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocPkg::ClearItemByPolicyID(UINT32 nPolicyID)
{
	TListID tIDList;
	GetItemIDList(tIDList);

	TListIDItor begin, end;
	begin = tIDList.begin();	end = tIDList.end();
	for(begin; begin != end; begin++)
	{
		PDB_PO_IN_AC_DOC_PKG pdpiadp = FindItem(*begin);
		if(pdpiadp->tDPH.nPolicyID != nPolicyID)	continue;

		DelPoInAcDocPkg(*begin);
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocPkg::ClearPkgUnitByPolicyID(UINT32 nPolicyID)
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
			t_ManagePoInAcDocUnit->DelPoInAcDocUnitWithSubPkg(pDPH->nUnitID);
		}

		DelPoInAcDocPkg(*begin);
	}
	return 0;
}
//---------------------------------------------------------------------------

String					CManagePoInAcDocPkg::GetName(UINT32 nID)
{
	PDB_PO_IN_AC_DOC_PKG pdpiadp = FindItem(nID);
    if(!pdpiadp)	return "";
    return pdpiadp->tDPH.strName;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocPkg::SetPkt(MemToken& SendToken)
{
    SendToken.TokenAdd_32(m_tMap.size());

	TMapDBPoInAcDocPkgItor begin, end;
    begin = m_tMap.begin();	end = m_tMap.end();
    for(begin; begin != end; begin++)
    {
    	SetPkt(&(begin->second), SendToken);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocPkg::SetPkt(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_AC_DOC_PKG pdpiadp = FindItem(nID);
	if(!pdpiadp)	return -1;

	return SetPkt(pdpiadp, SendToken);
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocPkg::SetPkt(PDB_PO_IN_AC_DOC_PKG pdpiadp, MemToken& SendToken)
{
	SendToken.TokenAdd_DPH(pdpiadp->tDPH);	

	SendToken.TokenSet_Block();
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocPkg::GetPkt(MemToken& RecvToken, DB_PO_IN_AC_DOC_PKG& dpiadp)
{
	if (!RecvToken.TokenDel_DPH(dpiadp.tDPH))				goto	INVALID_PKT;

	RecvToken.TokenSkip_Block();
	return 0;
INVALID_PKT:
	return -1;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocPkg::SetPktHost(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_AC_DOC_PKG pdpiadp = FindItem(nID);
	if(!pdpiadp)	return -1;

	SetPkt(pdpiadp, SendToken);

	return t_ManagePoInAcDocUnit->SetPktHost(pdpiadp->tDPH.nUnitID, SendToken);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------



