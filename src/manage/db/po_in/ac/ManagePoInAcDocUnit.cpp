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
#include "ManagePoInAcDocUnit.h"

//---------------------------------------------------------------------------

CManagePoInAcDocUnit*	t_ManagePoInAcDocUnit = NULL;

//---------------------------------------------------------------------------

CManagePoInAcDocUnit::CManagePoInAcDocUnit()
{
	t_DBMgrPoInAcDocUnit	= new CDBMgrPoInAcDocUnit();
}
//---------------------------------------------------------------------------

CManagePoInAcDocUnit::~CManagePoInAcDocUnit()
{
	if(t_DBMgrPoInAcDocUnit)	{	delete t_DBMgrPoInAcDocUnit;	t_DBMgrPoInAcDocUnit = NULL;	}
}
//---------------------------------------------------------------------------

INT32		CManagePoInAcDocUnit::LoadDBMS()
{
	TListDBPoInAcDocUnit tDBPoInAcDocUnitList;
    TListDBPoInAcDocUnitItor begin, end;
	if(SetER(t_DBMgrPoInAcDocUnit->LoadExecute(&tDBPoInAcDocUnitList)))
    {
    	return g_nErrRtn;
    }

    begin = tDBPoInAcDocUnitList.begin();	end = tDBPoInAcDocUnitList.end();
    for(begin; begin != end; begin++)
    {
    	AddItem(begin->tDPH.nID, *begin);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocUnit::GetHash(UINT32 nID, String& strOrgValue)
{
	PDB_PO_IN_AC_DOC_UNIT pdpiadu 			= NULL;
	{
		if( (pdpiadu = FindItem(nID)) == NULL)
		{
			WriteLogE("not find po_in_ac_doc_unit by hash : [%d]", ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			return ERR_INFO_NOT_OP_BECAUSE_NOT_FIND;
		}
	}

	{
		String strLogMode;
		MapToHex_64(pdpiadu->tLogModeMap, strLogMode, SS_GLOBAL_LOG_REC_MODE_INDEX_TOTAL_NUMBER);
		
		m_strHashValue = SPrintf("%s,"
							"%s,%u,", 
							GetHdrHashInfo(pdpiadu).c_str(),
							strLogMode.c_str(), pdpiadu->nAidType);

		{
			TMapIDItor begin, end;
			begin = pdpiadu->tDPH.tSubIDMap.begin();	end = pdpiadu->tDPH.tSubIDMap.end();
			for(begin; begin != end; begin++)
			{
				String strPkgValue;
				UINT8 nKey = pdpiadu->tDPH._get_id_to_key(begin->first);
				UINT32 nSubID = pdpiadu->tDPH._get_id_to_subid(begin->first);

				switch(nKey)
				{
					case SS_PO_IN_AC_UNIT_KEY_TYPE_OBJECT:		t_ManagePoInAcDocUnitObjPkg->GetHash(nSubID, strPkgValue);		break;
					case SS_PO_IN_AC_UNIT_KEY_TYPE_SUBJECT:		t_ManagePoInAcDocUnitSubPkg->GetHash(nSubID, strPkgValue);		break;					
				}

				m_strHashValue += strPkgValue;
			}
		}

		strOrgValue += m_strHashValue;
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocUnit::AddPoInAcDocUnit(DB_PO_IN_AC_DOC_UNIT&	dpiadu)
{
	if(SetER(t_DBMgrPoInAcDocUnit->InsertExecute(&dpiadu)))
    {
    	return g_nErrRtn;
    }

    AddItem(dpiadu.tDPH.nID, dpiadu);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocUnit::EditPoInAcDocUnit(DB_PO_IN_AC_DOC_UNIT&	dpiadu)
{
	PDB_PO_IN_AC_DOC_UNIT pdpiadu = FindItem(dpiadu.tDPH.nID);
	if(!pdpiadu)	return ERR_DBMS_UPDATE_FAIL;

	if(SetER(t_DBMgrPoInAcDocUnit->UpdateExecute(&dpiadu)))
    {
    	return g_nErrRtn;
    }

    EditItem(dpiadu.tDPH.nID, dpiadu);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocUnit::DelPoInAcDocUnit(UINT32 nID)
{
	PDB_PO_IN_AC_DOC_UNIT pdpiadu = FindItem(nID);
	if(!pdpiadu)	return ERR_DBMS_DELETE_FAIL;

	if(SetER(t_DBMgrPoInAcDocUnit->DeleteExecute(pdpiadu->tDPH.nID)))
    {
    	return g_nErrRtn;
    }

    DeleteItem(nID);
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocUnit::DelPoInAcDocUnitWithSubPkg(UINT32 nID)
{
	String strPkgValue;
	UINT8 nKey = 0;
	PDB_PO_IN_AC_DOC_UNIT pdpiadu = FindItem(nID);
	if(!pdpiadu)
		return ERR_DBMS_DELETE_FAIL;
	
	TMapIDItor begin, end;
	begin = pdpiadu->tDPH.tSubIDMap.begin();	end = pdpiadu->tDPH.tSubIDMap.end();
	for(begin; begin != end; begin++)
	{
		nKey = pdpiadu->tDPH._get_id_to_key(begin->first);
//		UINT32 nSubID = pdpiadu->tDPH._get_id_to_subid(begin->first);

		switch(nKey)
		{
			case SS_PO_IN_AC_UNIT_KEY_TYPE_OBJECT:		t_ManagePoInAcDocUnitObjPkg->ClearPkgUnitByPolicyID(nID);		break;
			case SS_PO_IN_AC_UNIT_KEY_TYPE_SUBJECT:		t_ManagePoInAcDocUnitSubPkg->ClearPkgUnitByPolicyID(nID);		break;			
		}
	}

	DelPoInAcDocUnit(nID);
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocUnit::ApplyPoInAcDocUnit(DB_PO_IN_AC_DOC_UNIT&	dpiadu)
{
	if(FindItem(dpiadu.tDPH.nID))
	{
		return EditPoInAcDocUnit(dpiadu);
	}
	return AddPoInAcDocUnit(dpiadu);
}
//---------------------------------------------------------------------------

String					CManagePoInAcDocUnit::GetName(UINT32 nID)
{
	PDB_PO_IN_AC_DOC_UNIT pdpiadu = FindItem(nID);
    if(!pdpiadu)	return "";
    return pdpiadu->tDPH.strName;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocUnit::SetPkt(MemToken& SendToken)
{
    SendToken.TokenAdd_32(m_tMap.size());

	TMapDBPoInAcDocUnitItor begin, end;
    begin = m_tMap.begin();	end = m_tMap.end();
    for(begin; begin != end; begin++)
    {
    	SetPkt(&(begin->second), SendToken);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocUnit::SetPkt(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_AC_DOC_UNIT pdpiadu = FindItem(nID);
	if(!pdpiadu)	return -1;

	return SetPkt(pdpiadu, SendToken);
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocUnit::SetPkt(PDB_PO_IN_AC_DOC_UNIT pdpiadu, MemToken& SendToken)
{
	SendToken.TokenAdd_DPH(pdpiadu->tDPH);

	SendToken.TokenAdd_ID64Map(pdpiadu->tLogModeMap);
	SendToken.TokenAdd_32(pdpiadu->nAidType);

	SendToken.TokenSet_Block();
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocUnit::SetPktHost(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_AC_DOC_UNIT pdpiadu 			= NULL;
	{
		if( (pdpiadu = FindItem(nID)) == NULL)
		{
			WriteLogE("not find po_in_ac_doc_unit by pkt : [%d]", ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			return ERR_INFO_NOT_OP_BECAUSE_NOT_FIND;
		}
	}

	{
		SetPkt(pdpiadu, SendToken);
	}

	{
		TListID tIDList;
		TListIDItor begin, end;

		{
			pdpiadu->tDPH._get_id_list_by_key(SS_PO_IN_AC_UNIT_KEY_TYPE_SUBJECT, tIDList);
			SendToken.TokenAdd_32(tIDList.size());
			begin = tIDList.begin();	end = tIDList.end();
			for(begin; begin != end; begin++)
			{
				UINT32 nSubID = pdpiadu->tDPH._get_id_to_subid(*begin);
				t_ManagePoInAcDocUnitSubPkg->SetPktHost(nSubID, SendToken);
			}
			SendToken.TokenSet_Block();
			tIDList.clear();
		}
		{
			pdpiadu->tDPH._get_id_list_by_key(SS_PO_IN_AC_UNIT_KEY_TYPE_OBJECT, tIDList);
			SendToken.TokenAdd_32(tIDList.size());
			begin = tIDList.begin();	end = tIDList.end();
			for(begin; begin != end; begin++)
			{
				UINT32 nSubID = pdpiadu->tDPH._get_id_to_subid(*begin);
				t_ManagePoInAcDocUnitObjPkg->SetPktHost(nSubID, SendToken);
			}
			SendToken.TokenSet_Block();
			tIDList.clear();
		}		
		SendToken.TokenSet_Block();
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDocUnit::GetPkt(MemToken& RecvToken, DB_PO_IN_AC_DOC_UNIT& dpiadu)
{
	if (!RecvToken.TokenDel_DPH(dpiadu.tDPH))					goto	INVALID_PKT;

	if ( RecvToken.TokenDel_ID64Map(dpiadu.tLogModeMap) < 0)		goto	INVALID_PKT;
	if (!RecvToken.TokenDel_32(dpiadu.nAidType))				goto	INVALID_PKT;

	RecvToken.TokenSkip_Block();
	return 0;
INVALID_PKT:
	return -1;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------



