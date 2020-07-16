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
#include "ManagePoInAcFileUnit.h"

//---------------------------------------------------------------------------

CManagePoInAcFileUnit*	t_ManagePoInAcFileUnit = NULL;

//---------------------------------------------------------------------------

CManagePoInAcFileUnit::CManagePoInAcFileUnit()
{
	t_DBMgrPoInAcFileUnit	= new CDBMgrPoInAcFileUnit();
}
//---------------------------------------------------------------------------

CManagePoInAcFileUnit::~CManagePoInAcFileUnit()
{
	if(t_DBMgrPoInAcFileUnit)	{	delete t_DBMgrPoInAcFileUnit;	t_DBMgrPoInAcFileUnit = NULL;	}
}
//---------------------------------------------------------------------------

INT32		CManagePoInAcFileUnit::LoadDBMS()
{
	TListDBPoInAcFileUnit tDBPoInAcFileUnitList;
    TListDBPoInAcFileUnitItor begin, end;
	if(SetER(t_DBMgrPoInAcFileUnit->LoadExecute(&tDBPoInAcFileUnitList)))
    {
    	return g_nErrRtn;
    }

    begin = tDBPoInAcFileUnitList.begin();	end = tDBPoInAcFileUnitList.end();
    for(begin; begin != end; begin++)
    {
    	AddItem(begin->tDPH.nID, *begin);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFileUnit::GetHash(UINT32 nID, String& strOrgValue)
{
	PDB_PO_IN_AC_FILE_UNIT pdpiafu 			= NULL;
	{
		if( (pdpiafu = FindItem(nID)) == NULL)
		{
			WriteLogE("not find po_in_ac_file_unit by hash : [%d]", ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			return ERR_INFO_NOT_OP_BECAUSE_NOT_FIND;
		}
	}

	{
		String strLogMode;
		MapToHex_64(pdpiafu->tLogModeMap, strLogMode, SS_GLOBAL_LOG_REC_MODE_INDEX_TOTAL_NUMBER);
		
		m_strHashValue = SPrintf("%s,"
							"%s,", 
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
					case SS_PO_IN_AC_UNIT_KEY_TYPE_OBJECT:		t_ManagePoInAcFileUnitObjPkg->GetHash(nSubID, strPkgValue);		break;
					case SS_PO_IN_AC_UNIT_KEY_TYPE_SUBJECT:		t_ManagePoInAcFileUnitSubPkg->GetHash(nSubID, strPkgValue);		break;
					case SS_PO_IN_AC_UNIT_KEY_TYPE_SCHEDULE:	t_ManagePoInAcFileUnitSchPkg->GetHash(nSubID, strPkgValue);		break;
					case SS_PO_IN_AC_UNIT_KEY_TYPE_RULE:		t_ManagePoInAcFileUnitRulPkg->GetHash(nSubID, strPkgValue);		break;
				}

				m_strHashValue += strPkgValue;
			}
		}

		strOrgValue += m_strHashValue;
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFileUnit::AddPoInAcFileUnit(DB_PO_IN_AC_FILE_UNIT&	dpiafu)
{
	if(SetER(t_DBMgrPoInAcFileUnit->InsertExecute(&dpiafu)))
    {
    	return g_nErrRtn;
    }

    AddItem(dpiafu.tDPH.nID, dpiafu);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFileUnit::EditPoInAcFileUnit(DB_PO_IN_AC_FILE_UNIT&	dpiafu)
{
	PDB_PO_IN_AC_FILE_UNIT pdpiafu = FindItem(dpiafu.tDPH.nID);
	if(!pdpiafu)	return ERR_DBMS_UPDATE_FAIL;

	if(SetER(t_DBMgrPoInAcFileUnit->UpdateExecute(&dpiafu)))
    {
    	return g_nErrRtn;
    }

    EditItem(dpiafu.tDPH.nID, dpiafu);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFileUnit::DelPoInAcFileUnit(UINT32 nID)
{
	PDB_PO_IN_AC_FILE_UNIT pdpiafu = FindItem(nID);
	if(!pdpiafu)	return ERR_DBMS_DELETE_FAIL;

	if(SetER(t_DBMgrPoInAcFileUnit->DeleteExecute(pdpiafu->tDPH.nID)))
    {
    	return g_nErrRtn;
    }

    DeleteItem(nID);
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFileUnit::DelPoInAcFileUnitWithSubPkg(UINT32 nID)
{
	String strPkgValue;
	UINT8 nKey = 0;
	PDB_PO_IN_AC_FILE_UNIT pdpiafu = FindItem(nID);
	if(!pdpiafu)	return ERR_DBMS_DELETE_FAIL;
	
	TMapIDItor begin, end;
	begin = pdpiafu->tDPH.tSubIDMap.begin();	end = pdpiafu->tDPH.tSubIDMap.end();
	for(begin; begin != end; begin++)
	{
		nKey = pdpiafu->tDPH._get_id_to_key(begin->first);
//		UINT32 nSubID = pdpiafu->tDPH._get_id_to_subid(begin->first);

		switch(nKey)
		{
			case SS_PO_IN_AC_UNIT_KEY_TYPE_OBJECT:		t_ManagePoInAcFileUnitObjPkg->ClearPkgUnitByPolicyID(nID);		break;
			case SS_PO_IN_AC_UNIT_KEY_TYPE_SUBJECT:		t_ManagePoInAcFileUnitSubPkg->ClearPkgUnitByPolicyID(nID);		break;
			case SS_PO_IN_AC_UNIT_KEY_TYPE_SCHEDULE:	t_ManagePoInAcFileUnitSchPkg->ClearPkgUnitByPolicyID(nID);		break;
			case SS_PO_IN_AC_UNIT_KEY_TYPE_RULE:		t_ManagePoInAcFileUnitRulPkg->ClearPkgUnitByPolicyID(nID);		break;
		}
	}

	DelPoInAcFileUnit(nID);
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFileUnit::ApplyPoInAcFileUnit(DB_PO_IN_AC_FILE_UNIT&	dpiafu)
{
	if(FindItem(dpiafu.tDPH.nID))
	{
		return EditPoInAcFileUnit(dpiafu);
	}
	return AddPoInAcFileUnit(dpiafu);
}
//---------------------------------------------------------------------------

String					CManagePoInAcFileUnit::GetName(UINT32 nID)
{
	PDB_PO_IN_AC_FILE_UNIT pdpiafu = FindItem(nID);
    if(!pdpiafu)	return "";
    return pdpiafu->tDPH.strName;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManagePoInAcFileUnit::SetPkt(MemToken& SendToken)
{
    SendToken.TokenAdd_32(m_tMap.size());

	TMapDBPoInAcFileUnitItor begin, end;
    begin = m_tMap.begin();	end = m_tMap.end();
    for(begin; begin != end; begin++)
    {
    	SetPkt(&(begin->second), SendToken);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFileUnit::SetPkt(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_AC_FILE_UNIT pdpiafu = FindItem(nID);
	if(!pdpiafu)	return -1;

	return SetPkt(pdpiafu, SendToken);
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFileUnit::SetPkt(PDB_PO_IN_AC_FILE_UNIT pdpiafu, MemToken& SendToken)
{
	SendToken.TokenAdd_DPH(pdpiafu->tDPH);

	SendToken.TokenAdd_ID64Map(pdpiafu->tLogModeMap);	

	SendToken.TokenSet_Block();
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFileUnit::SetPktHost(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_AC_FILE_UNIT pdpiafu 			= NULL;
	{
		if( (pdpiafu = FindItem(nID)) == NULL)
		{
			WriteLogE("not find po_in_ac_file_unit by pkt : [%d]", ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
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
				t_ManagePoInAcFileUnitSubPkg->SetPktHost(nSubID, SendToken);
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
				t_ManagePoInAcFileUnitObjPkg->SetPktHost(nSubID, SendToken);
			}
			SendToken.TokenSet_Block();
			tIDList.clear();
		}
		{
			pdpiafu->tDPH._get_id_list_by_key(SS_PO_IN_AC_UNIT_KEY_TYPE_SCHEDULE, tIDList);
			SendToken.TokenAdd_32(tIDList.size());
			begin = tIDList.begin();	end = tIDList.end();
			for(begin; begin != end; begin++)
			{
				UINT32 nSubID = pdpiafu->tDPH._get_id_to_subid(*begin);
				t_ManagePoInAcFileUnitSchPkg->SetPktHost(nSubID, SendToken);
			}
			SendToken.TokenSet_Block();
			tIDList.clear();
		}
		{
			pdpiafu->tDPH._get_id_list_by_key(SS_PO_IN_AC_UNIT_KEY_TYPE_RULE, tIDList);
			SendToken.TokenAdd_32(tIDList.size());
			begin = tIDList.begin();	end = tIDList.end();
			for(begin; begin != end; begin++)
			{
				UINT32 nSubID = pdpiafu->tDPH._get_id_to_subid(*begin);
				t_ManagePoInAcFileUnitRulPkg->SetPktHost(nSubID, SendToken);
			}
			SendToken.TokenSet_Block();
			tIDList.clear();
		}
		SendToken.TokenSet_Block();
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFileUnit::GetPkt(MemToken& RecvToken, DB_PO_IN_AC_FILE_UNIT& dpiafu)
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



