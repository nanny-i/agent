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
#include "ManagePoInRegSWUnitObjPkg.h"
#include "ManagePoInRegSWUnitSubPkg.h"
#include "ManagePoInRegSWUnit.h"

//---------------------------------------------------------------------------

CManagePoInRegSWUnit*	t_ManagePoInRegSWUnit = NULL;

//---------------------------------------------------------------------------

CManagePoInRegSWUnit::CManagePoInRegSWUnit()
{
	t_DBMgrPoInRegSWUnit	= new CDBMgrPoInRegSWUnit();
}
//---------------------------------------------------------------------------

CManagePoInRegSWUnit::~CManagePoInRegSWUnit()
{
	if(t_DBMgrPoInRegSWUnit)	{	delete t_DBMgrPoInRegSWUnit;	t_DBMgrPoInRegSWUnit = NULL;	}
}
//---------------------------------------------------------------------------

INT32		CManagePoInRegSWUnit::LoadDBMS()
{
	TListDBPoInRegSWUnit tDBPoInRegSWUnitList;
    TListDBPoInRegSWUnitItor begin, end;
	if(SetER(t_DBMgrPoInRegSWUnit->LoadExecute(&tDBPoInRegSWUnitList)))
    {
    	return g_nErrRtn;
    }

    begin = tDBPoInRegSWUnitList.begin();	end = tDBPoInRegSWUnitList.end();
    for(begin; begin != end; begin++)
    {
    	AddItem(begin->tDPH.nID, *begin);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSWUnit::GetHash(UINT32 nID, String& strOrgValue)
{
	PDB_PO_IN_REG_SW_UNIT pdpirsu 			= NULL;
	{
		if( (pdpirsu = FindItem(nID)) == NULL)
		{
			WriteLogE("not find po_in_reg_sw_unit by hash : [%d]", ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
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
					case SS_PO_IN_REG_UNIT_KEY_TYPE_OBJECT:		t_ManagePoInRegSWUnitObjPkg->GetHash(nSubID, strPkgValue);		break;
					case SS_PO_IN_REG_UNIT_KEY_TYPE_SUBJECT:	t_ManagePoInRegSWUnitSubPkg->GetHash(nSubID, strPkgValue);		break;					
				}

				m_strHashValue += strPkgValue;
			}
		}

		strOrgValue += m_strHashValue;
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSWUnit::AddPoInRegSWUnit(DB_PO_IN_REG_SW_UNIT&	dpirsu)
{
	if(SetER(t_DBMgrPoInRegSWUnit->InsertExecute(&dpirsu)))
    {
    	return g_nErrRtn;
    }

    AddItem(dpirsu.tDPH.nID, dpirsu);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSWUnit::EditPoInRegSWUnit(DB_PO_IN_REG_SW_UNIT&	dpirsu)
{
	PDB_PO_IN_REG_SW_UNIT pdpirsu = FindItem(dpirsu.tDPH.nID);
	if(!pdpirsu)	return ERR_DBMS_UPDATE_FAIL;

	if(SetER(t_DBMgrPoInRegSWUnit->UpdateExecute(&dpirsu)))
    {
    	return g_nErrRtn;
    }

    EditItem(dpirsu.tDPH.nID, dpirsu);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSWUnit::DelPoInRegSWUnit(UINT32 nID)
{
	PDB_PO_IN_REG_SW_UNIT pdpirsu = FindItem(nID);
	if(!pdpirsu)	return ERR_DBMS_DELETE_FAIL;

	if(SetER(t_DBMgrPoInRegSWUnit->DeleteExecute(pdpirsu->tDPH.nID)))
    {
    	return g_nErrRtn;
    }

    DeleteItem(nID);
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSWUnit::DelPoInRegSWUnitWithSubPkg(UINT32 nID)
{
	PDB_PO_IN_REG_SW_UNIT pdpirsu = FindItem(nID);
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
				t_ManagePoInRegSWUnitObjPkg->ClearPkgUnitByPolicyID(nID);
				break;
			case SS_PO_IN_REG_UNIT_KEY_TYPE_SUBJECT:
				t_ManagePoInRegSWUnitSubPkg->ClearPkgUnitByPolicyID(nID);
				break;
		}
	}

	DelPoInRegSWUnit(nID);
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSWUnit::ApplyPoInRegSWUnit(DB_PO_IN_REG_SW_UNIT&	dpirsu)
{
	if(FindItem(dpirsu.tDPH.nID))
	{
		return EditPoInRegSWUnit(dpirsu);
	}
	return AddPoInRegSWUnit(dpirsu);
}
//---------------------------------------------------------------------------

String					CManagePoInRegSWUnit::GetName(UINT32 nID)
{
	PDB_PO_IN_REG_SW_UNIT pdpirsu = FindItem(nID);
    if(!pdpirsu)	return "";
    return pdpirsu->tDPH.strName;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManagePoInRegSWUnit::SetPkt(MemToken& SendToken)
{
    SendToken.TokenAdd_32(m_tMap.size());

	TMapDBPoInRegSWUnitItor begin, end;
    begin = m_tMap.begin();	end = m_tMap.end();
    for(begin; begin != end; begin++)
    {
    	SetPkt(&(begin->second), SendToken);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSWUnit::SetPkt(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_REG_SW_UNIT pdpirsu = FindItem(nID);
	if(!pdpirsu)	return -1;

	return SetPkt(pdpirsu, SendToken);
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSWUnit::SetPkt(PDB_PO_IN_REG_SW_UNIT pdpirsu, MemToken& SendToken)
{
	SendToken.TokenAdd_DPH(pdpirsu->tDPH);

	SendToken.TokenAdd_ID64Map(pdpirsu->tLogModeMap);	

	SendToken.TokenSet_Block();
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSWUnit::SetPktHost(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_REG_SW_UNIT pdpirsu = NULL;
	TListID tIDList;
	TListIDItor begin, end;
	UINT32 nSubID = 0;
	if( (pdpirsu = FindItem(nID)) == NULL)
	{
		WriteLogE("not find po_in_reg_sw_unit by pkt : [%d]", ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
		return ERR_INFO_NOT_OP_BECAUSE_NOT_FIND;
	}

	SetPkt(pdpirsu, SendToken);


	{
		pdpirsu->tDPH._get_id_list_by_key(SS_PO_IN_REG_UNIT_KEY_TYPE_SUBJECT, tIDList);
		SendToken.TokenAdd_32(tIDList.size());
		begin = tIDList.begin();	end = tIDList.end();
		for(begin; begin != end; begin++)
		{
			UINT32 nSubID = pdpirsu->tDPH._get_id_to_subid(*begin);
			t_ManagePoInRegSWUnitSubPkg->SetPktHost(nSubID, SendToken);
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
			UINT32 nSubID = pdpirsu->tDPH._get_id_to_subid(*begin);
			t_ManagePoInRegSWUnitObjPkg->SetPktHost(nSubID, SendToken);
		}
		SendToken.TokenSet_Block();
		tIDList.clear();
	}				
	SendToken.TokenSet_Block();
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInRegSWUnit::GetPkt(MemToken& RecvToken, DB_PO_IN_REG_SW_UNIT& dpirsu)
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



