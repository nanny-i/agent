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
#include "ManagePoInAcDoc.h"

//---------------------------------------------------------------------------

CManagePoInAcDoc*	t_ManagePoInAcDoc = NULL;

//---------------------------------------------------------------------------

CManagePoInAcDoc::CManagePoInAcDoc()
{
	t_DBMgrPoInAcDoc	= new CDBMgrPoInAcDoc();
}
//---------------------------------------------------------------------------

CManagePoInAcDoc::~CManagePoInAcDoc()
{
	if(t_DBMgrPoInAcDoc)	{	delete t_DBMgrPoInAcDoc;	t_DBMgrPoInAcDoc = NULL;	}
}
//---------------------------------------------------------------------------

INT32		CManagePoInAcDoc::LoadDBMS()
{
	UINT32 nID = 0;
	TListDBPoInAcDoc tDBPoInAcDocList;
    TListDBPoInAcDocItor begin, end;
	if(SetER(t_DBMgrPoInAcDoc->LoadExecute(&tDBPoInAcDocList)))
    {
    	return g_nErrRtn;
    }

    begin = tDBPoInAcDocList.begin();	end = tDBPoInAcDocList.end();
    for(begin; begin != end; begin++)
    {
		nID = begin->tDPH.nID;
    	AddItem(begin->tDPH.nID, *begin);
    }

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDoc::InitHash()
{
	t_ManagePoInAcDocPkg->InitPkg();
	
	TListID tIDList;
	TListIDItor begin, end;

	GetItemIDList(tIDList);
	begin = tIDList.begin();		end = tIDList.end();
	for(begin; begin != end; begin++)
	{
		InitHash(*begin);
	}	
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDoc::InitHash(UINT32 nID)
{
	String strOrgValue;

	PDB_PO_IN_AC_DOC pdpiad 			= NULL;
	{
		if( (pdpiad = FindItem(nID)) == NULL)
		{
			WriteLogE("not find po_in_ac_doc by hash : [%d]", ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			return ERR_INFO_NOT_OP_BECAUSE_NOT_FIND;
		}
	}

	{
		strOrgValue = SPrintf("%s,", 
							GetHdrHashInfo(pdpiad).c_str());

		{
			TMapIDItor begin, end;
			begin = pdpiad->tDPH.tSubIDMap.begin();	end = pdpiad->tDPH.tSubIDMap.end();
			for(begin; begin != end; begin++)
			{
				t_ManagePoInAcDocPkg->GetHash(begin->first, EmptyStr(m_strHashValue));
				strOrgValue += m_strHashValue;
			}
		}
	}

	{
		char pszHashValue[CHAR_MAX_SIZE] = {0, };
		SHAString(ASIHASH_SHA_LEN_TYPE_128, strOrgValue.c_str(), strOrgValue.length(), pszHashValue, CHAR_MAX_SIZE);
		pdpiad->tDPH.strHash = pszHashValue;
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDoc::AddPoInAcDoc(DB_PO_IN_AC_DOC&	dpiad)
{
	if(SetER(t_DBMgrPoInAcDoc->InsertExecute(&dpiad)))
    {
    	return g_nErrRtn;
    }

    AddItem(dpiad.tDPH.nID, dpiad);
	InitHash(dpiad.tDPH.nID);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDoc::EditPoInAcDoc(DB_PO_IN_AC_DOC&	dpiad)
{
	PDB_PO_IN_AC_DOC pdpiad = FindItem(dpiad.tDPH.nID);
	if(!pdpiad)	return ERR_DBMS_UPDATE_FAIL;

	if(SetER(t_DBMgrPoInAcDoc->UpdateExecute(&dpiad)))
    {
    	return g_nErrRtn;
    }

    EditItem(dpiad.tDPH.nID, dpiad);
	InitHash(dpiad.tDPH.nID);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDoc::DelPoInAcDoc(UINT32 nID)
{
	PDB_PO_IN_AC_DOC pdpiad = FindItem(nID);
	if(!pdpiad)	return ERR_DBMS_DELETE_FAIL;

	if(SetER(t_DBMgrPoInAcDoc->DeleteExecute(pdpiad->tDPH.nID)))
    {
    	return g_nErrRtn;
    }

    DeleteItem(nID);
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDoc::ApplyPoInAcDoc(DB_PO_IN_AC_DOC&	dpiad)
{
	if(FindItem(dpiad.tDPH.nID))
	{
		return EditPoInAcDoc(dpiad);
	}
	return AddPoInAcDoc(dpiad);
}
//---------------------------------------------------------------------------

String					CManagePoInAcDoc::GetName(UINT32 nID)
{
	PDB_PO_IN_AC_DOC pdpiad = FindItem(nID);
    if(!pdpiad)	return "";
    return pdpiad->tDPH.strName;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManagePoInAcDoc::SetPkt(MemToken& SendToken)
{
    SendToken.TokenAdd_32(m_tMap.size());

	TMapDBPoInAcDocItor begin, end;
    begin = m_tMap.begin();	end = m_tMap.end();
    for(begin; begin != end; begin++)
    {
    	SetPkt(&(begin->second), SendToken);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDoc::SetPkt(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_AC_DOC pdpiad = FindItem(nID);
	if(!pdpiad)	return -1;

	SetPkt(pdpiad, SendToken);
	
	{
		SendToken.TokenAdd_32(pdpiad->tDPH.tSubIDMap.size());

		TMapIDItor begin, end;
		begin = pdpiad->tDPH.tSubIDMap.begin();	end = pdpiad->tDPH.tSubIDMap.end();
		for(begin; begin != end; begin++)
		{
			t_ManagePoInAcDocPkg->SetPkt(begin->first, SendToken);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDoc::SetPktHost(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_AC_DOC pdpiad = FindItem(nID);
	if(!pdpiad)	return -1;
	
	SetPkt(pdpiad, SendToken);

	{		
		SendToken.TokenAdd_32(pdpiad->tDPH.tSubIDMap.size());

		TMapIDItor begin, end;
		begin = pdpiad->tDPH.tSubIDMap.begin();	end = pdpiad->tDPH.tSubIDMap.end();
		for(begin; begin != end; begin++)
		{
			t_ManagePoInAcDocPkg->SetPktHost(begin->first, SendToken);
		}
	}

	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDoc::SetPkt(PDB_PO_IN_AC_DOC pdpiad, MemToken& SendToken)
{
	SendToken.TokenAdd_DPH(pdpiad->tDPH);

	SendToken.TokenSet_Block();
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcDoc::GetPkt(MemToken& RecvToken, DB_PO_IN_AC_DOC& dpiad)
{
	if (!RecvToken.TokenDel_DPH(dpiad.tDPH))				goto	INVALID_PKT;	

	RecvToken.TokenSkip_Block();
	return 0;
INVALID_PKT:
	return -1;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------



