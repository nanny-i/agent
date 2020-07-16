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
#include "ManagePoInAcFile.h"

//---------------------------------------------------------------------------

CManagePoInAcFile*	t_ManagePoInAcFile = NULL;

//---------------------------------------------------------------------------

CManagePoInAcFile::CManagePoInAcFile()
{
	t_DBMgrPoInAcFile	= new CDBMgrPoInAcFile();
}
//---------------------------------------------------------------------------

CManagePoInAcFile::~CManagePoInAcFile()
{
	if(t_DBMgrPoInAcFile)	{	delete t_DBMgrPoInAcFile;	t_DBMgrPoInAcFile = NULL;	}
}
//---------------------------------------------------------------------------

INT32		CManagePoInAcFile::LoadDBMS()
{
	TListDBPoInAcFile tDBPoInAcFileList;
    TListDBPoInAcFileItor begin, end;
	if(SetER(t_DBMgrPoInAcFile->LoadExecute(&tDBPoInAcFileList)))
    {
    	return g_nErrRtn;
    }

    begin = tDBPoInAcFileList.begin();	end = tDBPoInAcFileList.end();
    for(begin; begin != end; begin++)
    {
    	AddItem(begin->tDPH.nID, *begin);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFile::InitHash()
{
	t_ManagePoInAcFilePkg->InitPkg();
	
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

INT32					CManagePoInAcFile::InitHash(UINT32 nID)
{
	String strOrgValue;

	PDB_PO_IN_AC_FILE pdpiaf 			= NULL;
	{
		if( (pdpiaf = FindItem(nID)) == NULL)
		{
			WriteLogE("not find po_in_ac_file by hash : [%d]", ERR_INFO_NOT_OP_BECAUSE_NOT_FIND);
			return ERR_INFO_NOT_OP_BECAUSE_NOT_FIND;
		}
	}

	{
		strOrgValue = SPrintf("%s,", 
							GetHdrHashInfo(pdpiaf).c_str());

		{
			TMapIDItor begin, end;
			begin = pdpiaf->tDPH.tSubIDMap.begin();	end = pdpiaf->tDPH.tSubIDMap.end();
			for(begin; begin != end; begin++)
			{
				t_ManagePoInAcFilePkg->GetHash(begin->first, EmptyStr(m_strHashValue));
				strOrgValue += m_strHashValue;
			}
		}
	}

	{
		char pszHashValue[CHAR_MAX_SIZE] = {0, };
		SHAString(ASIHASH_SHA_LEN_TYPE_128, strOrgValue.c_str(), strOrgValue.length(), pszHashValue, CHAR_MAX_SIZE);
		pdpiaf->tDPH.strHash = pszHashValue;
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFile::AddPoInAcFile(DB_PO_IN_AC_FILE&	dpiaf)
{
	if(SetER(t_DBMgrPoInAcFile->InsertExecute(&dpiaf)))
    {
    	return g_nErrRtn;
    }

    AddItem(dpiaf.tDPH.nID, dpiaf);
	InitHash(dpiaf.tDPH.nID);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFile::EditPoInAcFile(DB_PO_IN_AC_FILE&	dpiaf)
{
	PDB_PO_IN_AC_FILE pdpiaf = FindItem(dpiaf.tDPH.nID);
	if(!pdpiaf)	return ERR_DBMS_UPDATE_FAIL;

	if(SetER(t_DBMgrPoInAcFile->UpdateExecute(&dpiaf)))
    {
    	return g_nErrRtn;
    }

    EditItem(dpiaf.tDPH.nID, dpiaf);
	InitHash(dpiaf.tDPH.nID);

    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFile::DelPoInAcFile(UINT32 nID)
{
	PDB_PO_IN_AC_FILE pdpiaf = FindItem(nID);
	if(!pdpiaf)	return ERR_DBMS_DELETE_FAIL;

	if(SetER(t_DBMgrPoInAcFile->DeleteExecute(pdpiaf->tDPH.nID)))
    {
    	return g_nErrRtn;
    }

    DeleteItem(nID);
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFile::ApplyPoInAcFile(DB_PO_IN_AC_FILE&	dpiaf)
{
	if(FindItem(dpiaf.tDPH.nID))
	{
		return EditPoInAcFile(dpiaf);
	}
	return AddPoInAcFile(dpiaf);
}
//---------------------------------------------------------------------------

String					CManagePoInAcFile::GetName(UINT32 nID)
{
	PDB_PO_IN_AC_FILE pdpiaf = FindItem(nID);
    if(!pdpiaf)	return "";
    return pdpiaf->tDPH.strName;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32					CManagePoInAcFile::SetPkt(MemToken& SendToken)
{
    SendToken.TokenAdd_32(m_tMap.size());

	TMapDBPoInAcFileItor begin, end;
    begin = m_tMap.begin();	end = m_tMap.end();
    for(begin; begin != end; begin++)
    {
    	SetPkt(&(begin->second), SendToken);
    }
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFile::SetPkt(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_AC_FILE pdpiaf = FindItem(nID);
	if(!pdpiaf)	return -1;

	SetPkt(pdpiaf, SendToken);
	
	{
		SendToken.TokenAdd_32(pdpiaf->tDPH.tSubIDMap.size());

		TMapIDItor begin, end;
		begin = pdpiaf->tDPH.tSubIDMap.begin();	end = pdpiaf->tDPH.tSubIDMap.end();
		for(begin; begin != end; begin++)
		{
			t_ManagePoInAcFilePkg->SetPkt(begin->first, SendToken);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFile::SetPktHost(UINT32 nID, MemToken& SendToken)
{
	PDB_PO_IN_AC_FILE pdpiaf = FindItem(nID);
	if(!pdpiaf)	return -1;
	
	SetPkt(pdpiaf, SendToken);

	{		
		SendToken.TokenAdd_32(pdpiaf->tDPH.tSubIDMap.size());

		TMapIDItor begin, end;
		begin = pdpiaf->tDPH.tSubIDMap.begin();	end = pdpiaf->tDPH.tSubIDMap.end();
		for(begin; begin != end; begin++)
		{
			t_ManagePoInAcFilePkg->SetPktHost(begin->first, SendToken);
		}
	}

	return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFile::SetPkt(PDB_PO_IN_AC_FILE pdpiaf, MemToken& SendToken)
{
	SendToken.TokenAdd_DPH(pdpiaf->tDPH);

	SendToken.TokenSet_Block();
    return 0;
}
//---------------------------------------------------------------------------

INT32					CManagePoInAcFile::GetPkt(MemToken& RecvToken, DB_PO_IN_AC_FILE& dpiaf)
{
	if (!RecvToken.TokenDel_DPH(dpiaf.tDPH))				goto	INVALID_PKT;	

	RecvToken.TokenSkip_Block();
	return 0;
INVALID_PKT:
	return -1;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------



