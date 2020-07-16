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
#include "ManagePoInAcFileUnitSchPkg.h"

//---------------------------------------------------------------------------

CManagePoInAcFileUnitSchPkg*	t_ManagePoInAcFileUnitSchPkg = NULL;

//---------------------------------------------------------------------------

CManagePoInAcFileUnitSchPkg::CManagePoInAcFileUnitSchPkg()
{
	t_DBMgrPoInAcFileUnitSchPkg	= new CDBMgrPoInAcFileUnitSchPkg();
}
//---------------------------------------------------------------------------

CManagePoInAcFileUnitSchPkg::~CManagePoInAcFileUnitSchPkg()
{
	if(t_DBMgrPoInAcFileUnitSchPkg)	{	delete t_DBMgrPoInAcFileUnitSchPkg;	t_DBMgrPoInAcFileUnitSchPkg = NULL;	}
}
//---------------------------------------------------------------------------

INT32		CManagePoInAcFileUnitSchPkg::LoadDBMS()
{
	TListDBPoInAcFileUnitSchPkg tDBPoInAcFileUnitSchPkgList;
    TListDBPoInAcFileUnitSchPkgItor begin, end;
	if(SetER(t_DBMgrPoInAcFileUnitSchPkg->LoadExecute(&tDBPoInAcFileUnitSchPkgList)))
    {
    	return g_nErrRtn;
    }

    begin = tDBPoInAcFileUnitSchPkgList.begin();	end = tDBPoInAcFileUnitSchPkgList.end();
    for(begin; begin != end; begin++)
    {
		AddItem(begin->tDPH.nID, *begin);
		AddKeyIDList(&(*begin));
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFileUnitSchPkg::InitPkg()
{
	TMapDBPoInAcFileUnitSchPkgItor begin, end;
	begin = m_tMap.begin();		end = m_tMap.end();
	for(begin; begin != end; begin++)
	{
		PDB_PO_IN_AC_FILE_UNIT pdpfou = t_ManagePoInAcFileUnit->FindItem(begin->second.tDPH.nPolicyID);
		if(!pdpfou)
		{
			WriteLogE("not find po_in_ac_file_unit information [%d]:po_id[%d]:[%d]", begin->second.tDPH.nPolicyID, begin->first, ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			continue;
		}

		pdpfou->tDPH._add_key_id_value(SS_PO_IN_AC_UNIT_KEY_TYPE_SCHEDULE, begin->first, begin->second.tDPH.nUnitID);
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFileUnitSchPkg::GetHash(UINT32 nID, String& strOrgValue)
{
	PDB_PO_IN_AC_FILE_UNIT_SCH_PKG pdpiafusp 			= NULL;
	{
		if( (pdpiafusp = FindItem(nID)) == NULL)
		{
			WriteLogE("not find po_in_ac_file_unit_sch_pkg by hash : [%d]", ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			return ERR_INFO_NOT_OP_BECAUSE_NOT_FIND;
		}
	}

	{
		t_ManagePoInAcFileSchUnit->GetHash(pdpiafusp->tDPH.nUnitID, EmptyStr(m_strHashValue));
		strOrgValue += m_strHashValue;
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFileUnitSchPkg::AddPoInAcFileUnitSchPkg(DB_PO_IN_AC_FILE_UNIT_SCH_PKG&	dpiafusp)
{
	if(SetER(t_DBMgrPoInAcFileUnitSchPkg->InsertExecute(&dpiafusp)))
    {
    	return g_nErrRtn;
    }

	AddItem(dpiafusp.tDPH.nID, dpiafusp);
	AddKeyIDList(&dpiafusp);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFileUnitSchPkg::EditPoInAcFileUnitSchPkg(DB_PO_IN_AC_FILE_UNIT_SCH_PKG&	dpiafusp)
{
	PDB_PO_IN_AC_FILE_UNIT_SCH_PKG pdpiafusp = FindItem(dpiafusp.tDPH.nID);
	if(!pdpiafusp)	return ERR_DBMS_UPDATE_FAIL;

	if(SetER(t_DBMgrPoInAcFileUnitSchPkg->UpdateExecute(&dpiafusp)))
    {
    	return g_nErrRtn;
    }

    EditItem(dpiafusp.tDPH.nID, dpiafusp);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFileUnitSchPkg::DelPoInAcFileUnitSchPkg(UINT32 nID)
{
	PDB_PO_IN_AC_FILE_UNIT_SCH_PKG pdpiafusp = FindItem(nID);
	if(!pdpiafusp)	return ERR_DBMS_DELETE_FAIL;

	if(SetER(t_DBMgrPoInAcFileUnitSchPkg->DeleteExecute(pdpiafusp->tDPH.nID)))
    {
    	return g_nErrRtn;
    }

	DelKeyIDList(pdpiafusp);
    DeleteItem(nID);
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFileUnitSchPkg::GetPoIDListFromUnitPkg(UINT32 nUnitID, TListID& tListID)
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

INT32					CManagePoInAcFileUnitSchPkg::ClearItemByPolicyID(UINT32 nPolicyID)
{
	TListID tIDList;
	GetItemIDList(tIDList);

	TListIDItor begin, end;
	begin = tIDList.begin();	end = tIDList.end();
	for(begin; begin != end; begin++)
	{
		PDB_PO_IN_AC_FILE_UNIT_SCH_PKG pdpiafusp = FindItem(*begin);
		if(pdpiafusp->tDPH.nPolicyID != nPolicyID)	continue;

		DelPoInAcFileUnitSchPkg(*begin);
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFileUnitSchPkg::ClearPkgUnitByPolicyID(UINT32 nPolicyID)
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
			t_ManagePoInAcFileSchUnit->DelPoInAcFileSchUnit(pDPH->nUnitID);
		}

		DelPoInAcFileUnitSchPkg(*begin);
	}
	return 0;
}
//---------------------------------------------------------------------------

String					CManagePoInAcFileUnitSchPkg::GetName(UINT32 nID)
{
	PDB_PO_IN_AC_FILE_UNIT_SCH_PKG pdpiafusp = FindItem(nID);
    if(!pdpiafusp)	return "";
    return pdpiafusp->tDPH.strName;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManagePoInAcFileUnitSchPkg::SetPkt(MemToken& SendToken)
{
    SendToken.TokenAdd_32(m_tMap.size());

	TMapDBPoInAcFileUnitSchPkgItor begin, end;
    begin = m_tMap.begin();	end = m_tMap.end();
    for(begin; begin != end; begin++)
    {
    	SetPkt(&(begin->second), SendToken);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFileUnitSchPkg::SetPkt(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_AC_FILE_UNIT_SCH_PKG pdpiafusp = FindItem(nID);
	if(!pdpiafusp)	return -1;

	return SetPkt(pdpiafusp, SendToken);
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFileUnitSchPkg::SetPkt(PDB_PO_IN_AC_FILE_UNIT_SCH_PKG pdpiafusp, MemToken& SendToken)
{
	SendToken.TokenAdd_DPH(pdpiafusp->tDPH);

	SendToken.TokenSet_Block();
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFileUnitSchPkg::GetPkt(MemToken& RecvToken, DB_PO_IN_AC_FILE_UNIT_SCH_PKG& dpiafusp)
{
	if (!RecvToken.TokenDel_DPH(dpiafusp.tDPH))				goto	INVALID_PKT;

	RecvToken.TokenSkip_Block();
	return 0;
INVALID_PKT:
	return -1;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManagePoInAcFileUnitSchPkg::SetPktHost(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_AC_FILE_UNIT_SCH_PKG pdpiafusp = FindItem(nID);
	if(!pdpiafusp)	return -1;

	SetPkt(pdpiafusp, SendToken);

	return t_ManagePoInAcFileSchUnit->SetPkt(pdpiafusp->tDPH.nUnitID, SendToken);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------



