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
#include "ManagePoInAcSfUnit.h"

//---------------------------------------------------------------------------

CManagePoInAcSfUnit*	t_ManagePoInAcSfUnit = NULL;

//---------------------------------------------------------------------------

CManagePoInAcSfUnit::CManagePoInAcSfUnit()
{
	t_DBMgrPoInAcSfUnit	= new CDBMgrPoInAcSfUnit();
}
//---------------------------------------------------------------------------

CManagePoInAcSfUnit::~CManagePoInAcSfUnit()
{
	if(t_DBMgrPoInAcSfUnit)	{	delete t_DBMgrPoInAcSfUnit;	t_DBMgrPoInAcSfUnit = NULL;	}
}
//---------------------------------------------------------------------------

INT32		CManagePoInAcSfUnit::LoadDBMS()
{
	TListDBPoInAcSfUnit tDBPoInAcSfUnitList;
    TListDBPoInAcSfUnitItor begin, end;
	if(SetER(t_DBMgrPoInAcSfUnit->LoadExecute(&tDBPoInAcSfUnitList)))
    {
    	return g_nErrRtn;
    }

    begin = tDBPoInAcSfUnitList.begin();	end = tDBPoInAcSfUnitList.end();
    for(begin; begin != end; begin++)
    {
    	AddItem(begin->tDPH.nID, *begin);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfUnit::GetHash(UINT32 nID, String& strOrgValue)
{
	PDB_PO_IN_AC_SF_UNIT pdpiafu 			= NULL;
	{
		if( (pdpiafu = FindItem(nID)) == NULL)
		{
			WriteLogE("not find po_in_ac_sf_unit by hash : [%d]", ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			return ERR_INFO_NOT_OP_BECAUSE_NOT_FIND;
		}
	}

	{
		String strLogMode;
		MapToHex_64(pdpiafu->tLogModeMap, strLogMode, SS_GLOBAL_LOG_REC_MODE_INDEX_TOTAL_NUMBER);
/*		
		m_strHashValue = SPrintf("%s,"
							"%s,%u,", 
							GetHdrHashInfo(pdpiafu).c_str(),
							strLogMode);
*/
		m_strHashValue = SPrintf("%s,%s,", 
							GetHdrHashInfo(pdpiafu).c_str(),
							strLogMode.c_str());
		{
			TMapIDItor begin, end;
			begin = pdpiafu->tDPH.tSubIDMap.begin();	end = pdpiafu->tDPH.tSubIDMap.end();
			for(begin; begin != end; begin++)
			{
				String strPkgValue;
				UINT8 nKey = pdpiafu->tDPH._get_id_to_key(begin->first);
				UINT32 nSubID = pdpiafu->tDPH._get_id_to_subid(begin->first);

				switch(nKey)
				{
					case SS_PO_IN_AC_UNIT_KEY_TYPE_OBJECT:		t_ManagePoInAcSfUnitObjPkg->GetHash(nSubID, strPkgValue);		break;
					case SS_PO_IN_AC_UNIT_KEY_TYPE_SUBJECT:		t_ManagePoInAcSfUnitSubPkg->GetHash(nSubID, strPkgValue);		break;					
				}

				m_strHashValue += strPkgValue;
			}
		}

		strOrgValue += m_strHashValue;
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfUnit::AddPoInAcSfUnit(DB_PO_IN_AC_SF_UNIT&	dpiafu)
{
	if(SetER(t_DBMgrPoInAcSfUnit->InsertExecute(&dpiafu)))
    {
    	return g_nErrRtn;
    }

    AddItem(dpiafu.tDPH.nID, dpiafu);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfUnit::EditPoInAcSfUnit(DB_PO_IN_AC_SF_UNIT&	dpiafu)
{
	PDB_PO_IN_AC_SF_UNIT pdpiafu = FindItem(dpiafu.tDPH.nID);
	if(!pdpiafu)	return ERR_DBMS_UPDATE_FAIL;

	if(SetER(t_DBMgrPoInAcSfUnit->UpdateExecute(&dpiafu)))
    {
    	return g_nErrRtn;
    }

    EditItem(dpiafu.tDPH.nID, dpiafu);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfUnit::DelPoInAcSfUnit(UINT32 nID)
{
	PDB_PO_IN_AC_SF_UNIT pdpiafu = FindItem(nID);
	if(!pdpiafu)	return ERR_DBMS_DELETE_FAIL;

	if(SetER(t_DBMgrPoInAcSfUnit->DeleteExecute(pdpiafu->tDPH.nID)))
    {
    	return g_nErrRtn;
    }

    DeleteItem(nID);
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfUnit::DelPoInAcSfUnitWithSubPkg(UINT32 nID)
{
	String strPkgValue;
	UINT8 nKey = 0;
	PDB_PO_IN_AC_SF_UNIT pdpiafu = FindItem(nID);
	if(!pdpiafu)	return ERR_DBMS_DELETE_FAIL;
	
	TMapIDItor begin, end;
	begin = pdpiafu->tDPH.tSubIDMap.begin();	end = pdpiafu->tDPH.tSubIDMap.end();
	for(begin; begin != end; begin++)
	{
		nKey = pdpiafu->tDPH._get_id_to_key(begin->first);
//		UINT32 nSubID = pdpiafu->tDPH._get_id_to_subid(begin->first);

		switch(nKey)
		{
			case SS_PO_IN_AC_UNIT_KEY_TYPE_OBJECT:
				t_ManagePoInAcSfUnitObjPkg->ClearPkgUnitByPolicyID(nID);
				break;
			case SS_PO_IN_AC_UNIT_KEY_TYPE_SUBJECT:
				t_ManagePoInAcSfUnitSubPkg->ClearPkgUnitByPolicyID(nID);
				break;
		}
	}

	DelPoInAcSfUnit(nID);
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfUnit::ApplyPoInAcSfUnit(DB_PO_IN_AC_SF_UNIT&	dpiafu)
{
	if(FindItem(dpiafu.tDPH.nID))
	{
		return EditPoInAcSfUnit(dpiafu);
	}
	return AddPoInAcSfUnit(dpiafu);
}
//---------------------------------------------------------------------------

String					CManagePoInAcSfUnit::GetName(UINT32 nID)
{
	PDB_PO_IN_AC_SF_UNIT pdpiafu = FindItem(nID);
    if(!pdpiafu)	return "";
    return pdpiafu->tDPH.strName;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfUnit::SetPkt(MemToken& SendToken)
{
    SendToken.TokenAdd_32(m_tMap.size());

	TMapDBPoInAcSfUnitItor begin, end;
    begin = m_tMap.begin();	end = m_tMap.end();
    for(begin; begin != end; begin++)
    {
    	SetPkt(&(begin->second), SendToken);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfUnit::SetPkt(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_AC_SF_UNIT pdpiafu = FindItem(nID);
	if(!pdpiafu)	return -1;

	return SetPkt(pdpiafu, SendToken);
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfUnit::SetPkt(PDB_PO_IN_AC_SF_UNIT pdpiafu, MemToken& SendToken)
{
	SendToken.TokenAdd_DPH(pdpiafu->tDPH);

	SendToken.TokenAdd_ID64Map(pdpiafu->tLogModeMap);

	SendToken.TokenSet_Block();
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfUnit::SetPktHost(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_AC_SF_UNIT pdpiafu 			= NULL;
	{
		if( (pdpiafu = FindItem(nID)) == NULL)
		{
			WriteLogE("not find po_in_ac_sf_unit by pkt : [%d]", ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			return ERR_INFO_NOT_OP_BECAUSE_NOT_FIND;
		}
	}

	{
		SetPkt(pdpiafu, SendToken);
	}

	{
		TListID tIDList;
		TListIDItor begin, end;

		{
			pdpiafu->tDPH._get_id_list_by_key(SS_PO_IN_AC_UNIT_KEY_TYPE_SUBJECT, tIDList);
			SendToken.TokenAdd_32(tIDList.size());
			begin = tIDList.begin();	end = tIDList.end();
			for(begin; begin != end; begin++)
			{
				UINT32 nSubID = pdpiafu->tDPH._get_id_to_subid(*begin);
				t_ManagePoInAcSfUnitSubPkg->SetPktHost(nSubID, SendToken);
			}
			SendToken.TokenSet_Block();
			tIDList.clear();
		}
		{
			pdpiafu->tDPH._get_id_list_by_key(SS_PO_IN_AC_UNIT_KEY_TYPE_OBJECT, tIDList);
			SendToken.TokenAdd_32(tIDList.size());
			begin = tIDList.begin();	end = tIDList.end();
			for(begin; begin != end; begin++)
			{
				UINT32 nSubID = pdpiafu->tDPH._get_id_to_subid(*begin);
				t_ManagePoInAcSfUnitObjPkg->SetPktHost(nSubID, SendToken);
			}
			SendToken.TokenSet_Block();
			tIDList.clear();
		}		
		SendToken.TokenSet_Block();
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcSfUnit::GetPkt(MemToken& RecvToken, DB_PO_IN_AC_SF_UNIT& dpiafu)
{
	if (!RecvToken.TokenDel_DPH(dpiafu.tDPH))					goto	INVALID_PKT;

	if ( RecvToken.TokenDel_ID64Map(dpiafu.tLogModeMap) < 0)		goto	INVALID_PKT;	

	RecvToken.TokenSkip_Block();
	return 0;
INVALID_PKT:
	return -1;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------



