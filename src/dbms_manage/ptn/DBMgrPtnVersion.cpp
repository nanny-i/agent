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
#include "DBMgrPtnVersion.h"

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

CDBMgrPtnVersion::CDBMgrPtnVersion()
{
	m_strDBTName = "ptn_version";
	//SetInitalize();
}
//---------------------------------------------------------------------------

CDBMgrPtnVersion::~CDBMgrPtnVersion()
{
}
//---------------------------------------------------------------------------

INT32			CDBMgrPtnVersion::SetInitalize()
{
    {
    	
	}
	//WriteLogN("current file dbms : [site][%d]", m_nDBSVer);
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPtnVersion::LoadDB(TListDBPtnVersion& tDBPtnVersionList)
{
    UINT32 nReadCnt = 0;
    DB_PTN_VERSION data;

    INT32 nIndex = 0;

	m_strQuery = SPrintf("SELECT id"
						", ptn_version"
						" FROM ptn_version;");

	if(DBOP_Check(ExecuteQuery(m_strQuery)))        return ERR_DBMS_SELECT_FAIL;
    
    do
    {
    	nIndex = 0;
    	
		data.nID					= GetDBField_Int(nIndex++);

		data.strPtnVersion				= GetDBField_String(nIndex++);
				
        tDBPtnVersionList.push_back(data);
        if(m_nLoadMaxID < UINT32(data.nID))	m_nLoadMaxID = data.nID;
        nReadCnt++;
    }while(Next());

	m_nLoadNumber = (UINT32)tDBPtnVersionList.size();
	WriteLogN("load database : [%s][%u]", m_strDBTName.c_str(), m_nLoadNumber);
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPtnVersion::InsertPtnVersion(DB_PTN_VERSION& data)
{
	m_strQuery = SPrintf("INSERT INTO ptn_version (id"
						", ptn_version)"
						"VALUES ( %u"
						"'%s'"
						");",
						data.nID, 
						data.strPtnVersion.c_str());

	if(DBOP_Check(ExecuteQuery(m_strQuery)))		return ERR_DBMS_INSERT_FAIL;

    data.nID      = GetLastID();
    
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPtnVersion::UpdatePtnVersion(DB_PTN_VERSION& data)
{
	m_strQuery = SPrintf("UPDATE ptn_version SET "
						" ptn_version='%s'"
						" WHERE id=%u;",
						data.strPtnVersion.c_str(),
						data.nID);

	if(DBOP_Check(ExecuteQuery(m_strQuery)))		return ERR_DBMS_UPDATE_FAIL;

	return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPtnVersion::DeletePtnVersion(UINT32 nID)
{
	m_strQuery = SPrintf("DELETE FROM ptn_version WHERE id=%u;", nID);

	if(DBOP_Check(ExecuteQuery(m_strQuery)))		return ERR_DBMS_DELETE_FAIL;
    return 0;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32	CDBMgrPtnVersion::LoadExecute(PVOID lpTempletList)
{
	TListDBPtnVersion* ptDBList = (TListDBPtnVersion*)lpTempletList;

    return LoadDB(*ptDBList);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPtnVersion::InsertExecute(PVOID lpTemplet)
{
	PDB_PTN_VERSION pd_t = (PDB_PTN_VERSION)lpTemplet;

    return InsertPtnVersion(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPtnVersion::UpdateExecute(PVOID lpTemplet)
{
	PDB_PTN_VERSION pd_t = (PDB_PTN_VERSION)lpTemplet;

    return UpdatePtnVersion(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPtnVersion::DeleteExecute(UINT32 nID)
{
	return DeletePtnVersion(nID);
}
//---------------------------------------------------------------------------






