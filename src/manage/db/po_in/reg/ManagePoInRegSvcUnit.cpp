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

#include "ManagePoInRegSvcUnitObjPkg.h"
#include "ManagePoInRegSvcUnitSubPkg.h"
#include "ManagePoInRegSvcUnit.h"

//---------------------------------------------------------------------------

CManagePoInRegSvcUnit*	t_ManagePoInRegSvcUnit = NULL;

//---------------------------------------------------------------------------

CManagePoInRegSvcUnit::CManagePoInRegSvcUnit()
{
	t_DBMgrPoInRegSvcUnit	= new CDBMgrPoInRegSvcUnit();
}
//---------------------------------------------------------------------------

CManagePoInRegSvcUnit::~CManagePoInRegSvcUnit()
{
	if(t_DBMgrPoInRegSvcUnit)	{	delete t_DBMgrPoInRegSvcUnit;	t_DBMgrPoInRegSvcUnit = NULL;	}
}
//---------------------------------------------------------------------------

INT32		CManagePoInRegSvcUnit::LoadDBMS()
{
	TListDBPoInRegSvcUnit tDBPoInRegSvcUnitList;
    TListDBPoInRegSvcUnitItor begin, end;
	if(SetER(t_DBMgrPoInRegSvcUnit->LoadExecute(&tDBPoInRegSvcUnitList)))
    {
    	return g_nErrRtn;
    }

    begin = tDBPoInRegSvcUnitList.begin();	end = tDBPoInRegSvcUnitList.end();
    for(begin; begin != end; begin++)
    {
    	AddItem(begin->tDPH.nID, *begin);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvcUnit::GetHash(UINT32 nID, String& strOrgValue)
{
	PDB_PO_IN_REG_SVC_UNIT pdpirsu 			= NULL;
	{
		if( (pdpirsu = FindItem(nID)) == NULL)
		{
			WriteLogE("not find po_in_reg_svc_unit by hash : [%d]", ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			return ERR_INFO_NOT_OP_BECAUSE_NOT_FIND;
		}
	}

	{
		String strLogMode;
		MapToHex_64(pdpirsu->tLogModeMap, strLogMode, SS_GLOBAL_LOG_REC_MODE_INDEX_TOTAL_NUMBER);
		
		m_strHashValue = SPrintf("%s,%s,", 
							GetHdrHashInfo(pdpirsu).c_str(),
							strLogMode.c_str());

		{
			TMapIDItor begin, end;
			begin = pdpirsu->tDPH.tSubIDMap.begin();	end = pdpirsu->tDPH.tSubIDMap.end();
			for(begin; begin != end; begin++)
			{
				String strPkgValue;
				UINT8 nKey = pdpirsu->tDPH._get_id_to_key(begin->first);
				UINT32 nSubID = pdpirsu->tDPH._get_id_to_subid(begin->first);

				switch(nKey)
				{
					case SS_PO_IN_REG_UNIT_KEY_TYPE_OBJECT:		t_ManagePoInRegSvcUnitObjPkg->GetHash(nSubID, strPkgValue);		break;
					case SS_PO_IN_REG_UNIT_KEY_TYPE_SUBJECT:	t_ManagePoInRegSvcUnitSubPkg->GetHash(nSubID, strPkgValue);		break;										
				}

				m_strHashValue += strPkgValue;
			}
		}

		strOrgValue += m_strHashValue;
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvcUnit::AddPoInRegSvcUnit(DB_PO_IN_REG_SVC_UNIT&	dpirsu)
{
	if(SetER(t_DBMgrPoInRegSvcUnit->InsertExecute(&dpirsu)))
    {
    	return g_nErrRtn;
    }

    AddItem(dpirsu.tDPH.nID, dpirsu);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvcUnit::EditPoInRegSvcUnit(DB_PO_IN_REG_SVC_UNIT&	dpirsu)
{
	PDB_PO_IN_REG_SVC_UNIT pdpirsu = FindItem(dpirsu.tDPH.nID);
	if(!pdpirsu)	return ERR_DBMS_UPDATE_FAIL;

	if(SetER(t_DBMgrPoInRegSvcUnit->UpdateExecute(&dpirsu)))
    {
    	return g_nErrRtn;
    }

    EditItem(dpirsu.tDPH.nID, dpirsu);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvcUnit::DelPoInRegSvcUnit(UINT32 nID)
{
	PDB_PO_IN_REG_SVC_UNIT pdpirsu = FindItem(nID);
	if(!pdpirsu)	return ERR_DBMS_DELETE_FAIL;

	if(SetER(t_DBMgrPoInRegSvcUnit->DeleteExecute(pdpirsu->tDPH.nID)))
    {
    	return g_nErrRtn;
    }

    DeleteItem(nID);
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvcUnit::DelPoInRegSvcUnitWithSubPkg(UINT32 nID)
{
	PDB_PO_IN_REG_SVC_UNIT pdpirsu = FindItem(nID);
	if(!pdpirsu)	return ERR_DBMS_DELETE_FAIL;
	
	TMapIDItor begin, end;
	begin = pdpirsu->tDPH.tSubIDMap.begin();	end = pdpirsu->tDPH.tSubIDMap.end();
	for(begin; begin != end; begin++)
	{
		String strPkgValue;
		UINT8 nKey = pdpirsu->tDPH._get_id_to_key(begin->first);
//		UINT32 nSubID = pdpirsu->tDPH._get_id_to_subid(begin->first);

		switch(nKey)
		{
			case SS_PO_IN_REG_UNIT_KEY_TYPE_OBJECT:
				t_ManagePoInRegSvcUnitObjPkg->ClearPkgUnitByPolicyID(nID);
				break;
			case SS_PO_IN_REG_UNIT_KEY_TYPE_SUBJECT:
				t_ManagePoInRegSvcUnitSubPkg->ClearPkgUnitByPolicyID(nID);
				break;
		}
	}

	DelPoInRegSvcUnit(nID);
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvcUnit::ApplyPoInRegSvcUnit(DB_PO_IN_REG_SVC_UNIT&	dpirsu)
{
	if(FindItem(dpirsu.tDPH.nID))
	{
		return EditPoInRegSvcUnit(dpirsu);
	}
	return AddPoInRegSvcUnit(dpirsu);
}
//---------------------------------------------------------------------------

String					CManagePoInRegSvcUnit::GetName(UINT32 nID)
{
	PDB_PO_IN_REG_SVC_UNIT pdpirsu = FindItem(nID);
    if(!pdpirsu)	return "";
    return pdpirsu->tDPH.strName;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvcUnit::SetPkt(MemToken& SendToken)
{
    SendToken.TokenAdd_32(m_tMap.size());

	TMapDBPoInRegSvcUnitItor begin, end;
    begin = m_tMap.begin();	end = m_tMap.end();
    for(begin; begin != end; begin++)
    {
    	SetPkt(&(begin->second), SendToken);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvcUnit::SetPkt(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_REG_SVC_UNIT pdpirsu = FindItem(nID);
	if(!pdpirsu)	return -1;

	return SetPkt(pdpirsu, SendToken);
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvcUnit::SetPkt(PDB_PO_IN_REG_SVC_UNIT pdpirsu, MemToken& SendToken)
{
	SendToken.TokenAdd_DPH(pdpirsu->tDPH);

	SendToken.TokenAdd_ID64Map(pdpirsu->tLogModeMap);	

	SendToken.TokenSet_Block();
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvcUnit::SetPktHost(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_REG_SVC_UNIT pdpirsu = NULL;
	UINT32 nSubID = 0;
	TListID tIDList;
	TListIDItor begin, end;

	if( (pdpirsu = FindItem(nID)) == NULL)
	{
		WriteLogE("not find po_in_reg_svc_unit by pkt : [%d]", ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
		return ERR_INFO_NOT_OP_BECAUSE_NOT_FIND;
	}

	SetPkt(pdpirsu, SendToken);


	{
		pdpirsu->tDPH._get_id_list_by_key(SS_PO_IN_REG_UNIT_KEY_TYPE_SUBJECT, tIDList);
		SendToken.TokenAdd_32(tIDList.size());
		begin = tIDList.begin();	end = tIDList.end();
		for(begin; begin != end; begin++)
		{
			nSubID = pdpirsu->tDPH._get_id_to_subid(*begin);
			t_ManagePoInRegSvcUnitSubPkg->SetPktHost(nSubID, SendToken);
		}
		SendToken.TokenSet_Block();
		tIDList.clear();
	}
	{
		pdpirsu->tDPH._get_id_list_by_key(SS_PO_IN_REG_UNIT_KEY_TYPE_OBJECT, tIDList);
		SendToken.TokenAdd_32(tIDList.size());
		begin = tIDList.begin();	end = tIDList.end();
		for(begin; begin != end; begin++)
		{
			nSubID = pdpirsu->tDPH._get_id_to_subid(*begin);
			t_ManagePoInRegSvcUnitObjPkg->SetPktHost(nSubID, SendToken);
		}
		SendToken.TokenSet_Block();
		tIDList.clear();
	}				
	SendToken.TokenSet_Block();
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSvcUnit::GetPkt(MemToken& RecvToken, DB_PO_IN_REG_SVC_UNIT& dpirsu)
{
	if (!RecvToken.TokenDel_DPH(dpirsu.tDPH))					goto	INVALID_PKT;

	if ( RecvToken.TokenDel_ID64Map(dpirsu.tLogModeMap) < 0)		goto	INVALID_PKT;	

	RecvToken.TokenSkip_Block();
	return 0;
INVALID_PKT:
	return -1;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------



