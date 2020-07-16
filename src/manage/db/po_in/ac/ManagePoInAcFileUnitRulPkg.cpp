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
#include "ManagePoInAcFileUnitRulPkg.h"

//---------------------------------------------------------------------------

CManagePoInAcFileUnitRulPkg*	t_ManagePoInAcFileUnitRulPkg = NULL;

//---------------------------------------------------------------------------

CManagePoInAcFileUnitRulPkg::CManagePoInAcFileUnitRulPkg()
{
	t_DBMgrPoInAcFileUnitRulPkg	= new CDBMgrPoInAcFileUnitRulPkg();
}
//---------------------------------------------------------------------------

CManagePoInAcFileUnitRulPkg::~CManagePoInAcFileUnitRulPkg()
{
	if(t_DBMgrPoInAcFileUnitRulPkg)	{	delete t_DBMgrPoInAcFileUnitRulPkg;	t_DBMgrPoInAcFileUnitRulPkg = NULL;	}
}
//---------------------------------------------------------------------------

INT32		CManagePoInAcFileUnitRulPkg::LoadDBMS()
{
	TListDBPoInAcFileUnitRulPkg tDBPoInAcFileUnitRulPkgList;
    TListDBPoInAcFileUnitRulPkgItor begin, end;
	if(SetER(t_DBMgrPoInAcFileUnitRulPkg->LoadExecute(&tDBPoInAcFileUnitRulPkgList)))
    {
    	return g_nErrRtn;
    }

    begin = tDBPoInAcFileUnitRulPkgList.begin();	end = tDBPoInAcFileUnitRulPkgList.end();
    for(begin; begin != end; begin++)
    {
		AddItem(begin->tDPH.nID, *begin);
		AddKeyIDList(&(*begin));
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFileUnitRulPkg::InitPkg()
{
	TMapDBPoInAcFileUnitRulPkgItor begin, end;
	begin = m_tMap.begin();		end = m_tMap.end();
	for(begin; begin != end; begin++)
	{
		PDB_PO_IN_AC_FILE_UNIT pdpfou = t_ManagePoInAcFileUnit->FindItem(begin->second.tDPH.nPolicyID);
		if(!pdpfou)
		{
			WriteLogE("not find po_in_ac_file_unit information [%d]:po_id[%d]:[%d]", begin->second.tDPH.nPolicyID, begin->first, ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			continue;
		}

		pdpfou->tDPH._add_key_id_value(SS_PO_IN_AC_UNIT_KEY_TYPE_RULE, begin->first, begin->second.tDPH.nUnitID);
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFileUnitRulPkg::GetHash(UINT32 nID, String& strOrgValue)
{
	PDB_PO_IN_AC_FILE_UNIT_RUL_PKG pdpiafurp 			= NULL;
	{
		if( (pdpiafurp = FindItem(nID)) == NULL)
		{
			WriteLogE("not find po_in_ac_file_unit_rul_pkg by hash : [%d]", ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			return ERR_INFO_NOT_OP_BECAUSE_NOT_FIND;
		}
	}

	{
		EmptyStr(m_strHashValue);
		m_strHashValue = SPrintf("%u,%u,", pdpiafurp->nRuleOrder, pdpiafurp->nAcMode);
		
		t_ManagePoInAcFileSubUnit->GetHash(pdpiafurp->tDPH.nUnitID, m_strHashValue);		
		strOrgValue += m_strHashValue;
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFileUnitRulPkg::AddPoInAcFileUnitRulPkg(DB_PO_IN_AC_FILE_UNIT_RUL_PKG&	dpiafurp)
{
	if(SetER(t_DBMgrPoInAcFileUnitRulPkg->InsertExecute(&dpiafurp)))
    {
    	return g_nErrRtn;
    }

	AddItem(dpiafurp.tDPH.nID, dpiafurp);
	AddKeyIDList(&dpiafurp);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFileUnitRulPkg::EditPoInAcFileUnitRulPkg(DB_PO_IN_AC_FILE_UNIT_RUL_PKG&	dpiafurp)
{
	PDB_PO_IN_AC_FILE_UNIT_RUL_PKG pdpiafurp = FindItem(dpiafurp.tDPH.nID);
	if(!pdpiafurp)	return ERR_DBMS_UPDATE_FAIL;

	if(SetER(t_DBMgrPoInAcFileUnitRulPkg->UpdateExecute(&dpiafurp)))
    {
    	return g_nErrRtn;
    }

    EditItem(dpiafurp.tDPH.nID, dpiafurp);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFileUnitRulPkg::DelPoInAcFileUnitRulPkg(UINT32 nID)
{
	PDB_PO_IN_AC_FILE_UNIT_RUL_PKG pdpiafurp = FindItem(nID);
	if(!pdpiafurp)	return ERR_DBMS_DELETE_FAIL;

	if(SetER(t_DBMgrPoInAcFileUnitRulPkg->DeleteExecute(pdpiafurp->tDPH.nID)))
    {
    	return g_nErrRtn;
    }

	DelKeyIDList(pdpiafurp);
    DeleteItem(nID);
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFileUnitRulPkg::GetPoIDListFromUnitPkg(UINT32 nUnitID, TListID& tListID)
{
	TMapID tPoIDMap;
	TListID tUnitIDList;
	GetPoIDFromPkgList(nUnitID, tUnitIDList);

	{
		TListIDItor begin, end;
		begin = tUnitIDList.begin();	end = tUnitIDList.end();
		for(begin; begin != end; begin++)
		{
			t_ManagePoInAcFilePkg->GetPoIDFromPkgMap(*begin, tPoIDMap);	
		}
	}
	ConvertMapToList(tPoIDMap, tListID);
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFileUnitRulPkg::ClearItemByPolicyID(UINT32 nPolicyID)
{
	TListID tIDList;
	GetItemIDList(tIDList);

	TListIDItor begin, end;
	begin = tIDList.begin();	end = tIDList.end();
	for(begin; begin != end; begin++)
	{
		PDB_PO_IN_AC_FILE_UNIT_RUL_PKG pdpiafurp = FindItem(*begin);
		if(pdpiafurp->tDPH.nPolicyID != nPolicyID)	continue;

		DelPoInAcFileUnitRulPkg(*begin);
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFileUnitRulPkg::ClearPkgUnitByPolicyID(UINT32 nPolicyID)
{	
	TListID tIDList;
	GetItemIDList(tIDList);

	TListIDItor begin, end;
	begin = tIDList.begin();	end = tIDList.end();
	for(begin; begin != end; begin++)
	{
		PDB_PO_HEADER pDPH = GetPoHdr(*begin);
		if(!pDPH || pDPH->nPolicyID != nPolicyID)		continue;

		if(IsMultiUsedUnit(nPolicyID, pDPH->nUnitID) == 0 &&
			t_ManagePoInAcFileSubUnit->IsMultiUsedUnit(nPolicyID, pDPH->nUnitID) == 0)
		{
			t_ManagePoInAcFileSubUnit->DelPoInAcFileSubUnit(pDPH->nUnitID);
		}

		DelPoInAcFileUnitRulPkg(*begin);
	}
	return 0;
}
//---------------------------------------------------------------------------

String					CManagePoInAcFileUnitRulPkg::GetName(UINT32 nID)
{
	PDB_PO_IN_AC_FILE_UNIT_RUL_PKG pdpiafurp = FindItem(nID);
    if(!pdpiafurp)	return "";
    return pdpiafurp->tDPH.strName;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManagePoInAcFileUnitRulPkg::SetPkt(MemToken& SendToken)
{
    SendToken.TokenAdd_32(m_tMap.size());

	TMapDBPoInAcFileUnitRulPkgItor begin, end;
    begin = m_tMap.begin();	end = m_tMap.end();
    for(begin; begin != end; begin++)
    {
    	SetPkt(&(begin->second), SendToken);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFileUnitRulPkg::SetPkt(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_AC_FILE_UNIT_RUL_PKG pdpiafurp = FindItem(nID);
	if(!pdpiafurp)	return -1;

	return SetPkt(pdpiafurp, SendToken);
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFileUnitRulPkg::SetPkt(PDB_PO_IN_AC_FILE_UNIT_RUL_PKG pdpiafurp, MemToken& SendToken)
{
	SendToken.TokenAdd_DPH(pdpiafurp->tDPH);

	SendToken.TokenAdd_32(pdpiafurp->nRuleOrder);
	SendToken.TokenAdd_32(pdpiafurp->nAcMode);

	SendToken.TokenSet_Block();
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFileUnitRulPkg::GetPkt(MemToken& RecvToken, DB_PO_IN_AC_FILE_UNIT_RUL_PKG& dpiafurp)
{
	if (!RecvToken.TokenDel_DPH(dpiafurp.tDPH))				goto	INVALID_PKT;

	if (!RecvToken.TokenDel_32(dpiafurp.nRuleOrder))			goto	INVALID_PKT;
	if (!RecvToken.TokenDel_32(dpiafurp.nAcMode))			goto	INVALID_PKT;

	RecvToken.TokenSkip_Block();
	return 0;
INVALID_PKT:
	return -1;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManagePoInAcFileUnitRulPkg::SetPktHost(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_AC_FILE_UNIT_RUL_PKG pdpiafurp = FindItem(nID);
	if(!pdpiafurp)	return -1;

	SetPkt(pdpiafurp, SendToken);

	return t_ManagePoInAcFileSubUnit->SetPkt(pdpiafurp->tDPH.nUnitID, SendToken);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------



