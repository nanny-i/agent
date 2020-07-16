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
#include "ManagePoInRegVuln.h"
#include "ManagePoInRegVulnUnit.h"
#include "ManagePoInRegVulnPkg.h"

//---------------------------------------------------------------------------

CManagePoInRegVulnPkg*	t_ManagePoInRegVulnPkg = NULL;

//---------------------------------------------------------------------------

CManagePoInRegVulnPkg::CManagePoInRegVulnPkg()
{
	t_DBMgrPoInRegVulnPkg	= new CDBMgrPoInRegVulnPkg();
}
//---------------------------------------------------------------------------

CManagePoInRegVulnPkg::~CManagePoInRegVulnPkg()
{
	if(t_DBMgrPoInRegVulnPkg)	{	delete t_DBMgrPoInRegVulnPkg;	t_DBMgrPoInRegVulnPkg = NULL;	}
}
//---------------------------------------------------------------------------

INT32		CManagePoInRegVulnPkg::LoadDBMS()
{
	TListDBPoInRegVulnPkg tDBPoInRegVulnPkgList;
    TListDBPoInRegVulnPkgItor begin, end;
	if(SetER(t_DBMgrPoInRegVulnPkg->LoadExecute(&tDBPoInRegVulnPkgList)))
    {
    	return g_nErrRtn;
    }

    begin = tDBPoInRegVulnPkgList.begin();	end = tDBPoInRegVulnPkgList.end();
    for(begin; begin != end; begin++)
    {
		AddItem(begin->tDPH.nID, *begin);
		AddKeyIDList(&(*begin));
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegVulnPkg::InitPkg()
{
	TMapDBPoInRegVulnPkgItor begin, end;
	begin = m_tMap.begin();		end = m_tMap.end();
	for(begin; begin != end; begin++)
	{
		PDB_PO_IN_REG_VULN pdpirv = t_ManagePoInRegVuln->FindItem(begin->second.tDPH.nPolicyID);
		if(!pdpirv)
		{
			WriteLogE("not find po_in_reg_vuln_pkg information [%d]:po_id[%d]:[%d]", begin->second.tDPH.nPolicyID, begin->first, ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			continue;
		}

		pdpirv->tDPH._add_id_value(begin->first, begin->second.tDPH.nUnitID);
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegVulnPkg::GetHash(UINT32 nID, String& strOrgValue)
{
	PDB_PO_IN_REG_VULN_PKG pdpirvp 			= NULL;
	{
		if( (pdpirvp = FindItem(nID)) == NULL)
		{
			WriteLogE("not find po_in_reg_vuln_pkg by hash : [%d]", ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			return ERR_INFO_NOT_OP_BECAUSE_NOT_FIND;
		}
	}

	{
		t_ManagePoInRegVulnUnit->GetHash(pdpirvp->tDPH.nUnitID, strOrgValue);
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegVulnPkg::AddPoInRegVulnPkg(DB_PO_IN_REG_VULN_PKG&	dpirvp)
{
	if(SetER(t_DBMgrPoInRegVulnPkg->InsertExecute(&dpirvp)))
    {
    	return g_nErrRtn;
    }

	AddItem(dpirvp.tDPH.nID, dpirvp);
	AddKeyIDList(&dpirvp);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegVulnPkg::EditPoInRegVulnPkg(DB_PO_IN_REG_VULN_PKG&	dpirvp)
{
	PDB_PO_IN_REG_VULN_PKG pdpirvp = FindItem(dpirvp.tDPH.nID);
	if(!pdpirvp)	return ERR_DBMS_UPDATE_FAIL;

	if(SetER(t_DBMgrPoInRegVulnPkg->UpdateExecute(&dpirvp)))
    {
    	return g_nErrRtn;
    }

    EditItem(dpirvp.tDPH.nID, dpirvp);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegVulnPkg::DelPoInRegVulnPkg(UINT32 nID)
{
	PDB_PO_IN_REG_VULN_PKG pdpirvp = FindItem(nID);
	if(!pdpirvp)	return ERR_DBMS_DELETE_FAIL;

	if(SetER(t_DBMgrPoInRegVulnPkg->DeleteExecute(pdpirvp->tDPH.nID)))
    {
    	return g_nErrRtn;
    }

	DelKeyIDList(pdpirvp);
    DeleteItem(nID);
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegVulnPkg::ClearItemByPolicyID(UINT32 nPolicyID)
{
	TListID tIDList;
	GetItemIDList(tIDList);

	TListIDItor begin, end;
	begin = tIDList.begin();	end = tIDList.end();
	for(begin; begin != end; begin++)
	{
		PDB_PO_IN_REG_VULN_PKG pdpirvp = FindItem(*begin);
		if(pdpirvp->tDPH.nPolicyID != nPolicyID)	continue;

		DelPoInRegVulnPkg(*begin);
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegVulnPkg::ClearPkgUnitByPolicyID(UINT32 nPolicyID)
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
			t_ManagePoInRegVulnUnit->DelPoInRegVulnUnit(pDPH->nUnitID);
		}

		DelPoInRegVulnPkg(*begin);
	}
	return 0;
}
//---------------------------------------------------------------------------

String					CManagePoInRegVulnPkg::GetName(UINT32 nID)
{
	PDB_PO_IN_REG_VULN_PKG pdpirvp = FindItem(nID);
    if(!pdpirvp)	return "";
    return pdpirvp->tDPH.strName;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManagePoInRegVulnPkg::SetPkt(MemToken& SendToken)
{
    SendToken.TokenAdd_32(m_tMap.size());

	TMapDBPoInRegVulnPkgItor begin, end;
    begin = m_tMap.begin();	end = m_tMap.end();
    for(begin; begin != end; begin++)
    {
    	SetPkt(&(begin->second), SendToken);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegVulnPkg::SetPkt(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_REG_VULN_PKG pdpirvp = FindItem(nID);
	if(!pdpirvp)	return -1;

	return SetPkt(pdpirvp, SendToken);
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegVulnPkg::SetPkt(PDB_PO_IN_REG_VULN_PKG pdpirvp, MemToken& SendToken)
{
	SendToken.TokenAdd_DPH(pdpirvp->tDPH);

	SendToken.TokenSet_Block();
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegVulnPkg::GetPkt(MemToken& RecvToken, DB_PO_IN_REG_VULN_PKG& dpirvp)
{
	if (!RecvToken.TokenDel_DPH(dpirvp.tDPH))				goto	INVALID_PKT;

	RecvToken.TokenSkip_Block();
	return 0;
INVALID_PKT:
	return -1;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManagePoInRegVulnPkg::SetPktHost(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_REG_VULN_PKG pdpirvp = FindItem(nID);
	if(!pdpirvp)	return -1;

	SetPkt(pdpirvp, SendToken);

	return t_ManagePoInRegVulnUnit->SetPkt(pdpirvp->tDPH.nUnitID, SendToken);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------



