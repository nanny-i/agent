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
#include "DBMgrPoInAcFileUnitSubPkg.h"

//---------------------------------------------------------------------------

CDBMgrPoInAcFileUnitSubPkg*		t_DBMgrPoInAcFileUnitSubPkg = NULL;

//---------------------------------------------------------------------------

CDBMgrPoInAcFileUnitSubPkg::CDBMgrPoInAcFileUnitSubPkg()
{
	m_strDBTName = "po_in_ac_file_unit_sub_pkg";
}
//---------------------------------------------------------------------------

CDBMgrPoInAcFileUnitSubPkg::~CDBMgrPoInAcFileUnitSubPkg()
{
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInAcFileUnitSubPkg::SetInitalize()
{
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInAcFileUnitSubPkg::LoadDB(TListDBPoInAcFileUnitSubPkg& tDBPoInAcFileUnitSubPkgList)
{
    UINT32 nReadCnt = 0;
    DB_PO_IN_AC_FILE_UNIT_SUB_PKG dpiafusp;

    INT32 nIndex = 0;

    m_strQuery = SPrintf(DBMS_POLICY_QUERY_PKG_HDR_SELECT
						" FROM po_in_ac_file_unit_sub_pkg WHERE used_flag=1;");
    if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_SELECT_FAIL;

    do
    {
		nIndex = 0;
		DB_PO_HEADER& tDPH = dpiafusp.tDPH;

		tDPH						= GetDBField_PoPkgHDR(nIndex);
		
        tDBPoInAcFileUnitSubPkgList.push_back(dpiafusp);
        if(m_nLoadMaxID < UINT32(tDPH.nID))	m_nLoadMaxID = tDPH.nID;
        nReadCnt++;
    }while(Next());
	m_nLoadNumber = tDBPoInAcFileUnitSubPkgList.size();
	WriteLogN("load database : [%s][%u]", m_strDBTName.c_str(), m_nLoadNumber);
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInAcFileUnitSubPkg::InsertPoInAcFileUnitSubPkg(DB_PO_IN_AC_FILE_UNIT_SUB_PKG& dpiafusp)
{
	DB_PO_HEADER& tDPH = dpiafusp.tDPH;

	m_strQuery = SPrintf("INSERT INTO po_in_ac_file_unit_sub_pkg("
						DBMS_POLICY_QUERY_PKG_HDR_INSERT_NAME
						") VALUES (%s"
						");",
                        GetPoPkgHDRQuery_InsertValue(tDPH).c_str());

	if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_INSERT_FAIL;

    tDPH.nID      = GetLastID();

    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInAcFileUnitSubPkg::UpdatePoInAcFileUnitSubPkg(DB_PO_IN_AC_FILE_UNIT_SUB_PKG& dpiafusp)
{
	DB_PO_HEADER& tDPH = dpiafusp.tDPH;

	m_strQuery = SPrintf("UPDATE po_in_ac_file_unit_sub_pkg SET "
						"%s"
						" WHERE id=%u;",
						GetPoPkgHDRQuery_Update(tDPH).c_str(), 
						tDPH.nID);

	if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_UPDATE_FAIL;

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
//---------------------------------------------------------------------------

INT32	CDBMgrPoInAcFileUnitSubPkg::LoadExecute(PVOID lpTempletList)
{
	TListDBPoInAcFileUnitSubPkg* ptDBList = (TListDBPoInAcFileUnitSubPkg*)lpTempletList;

    return LoadDB(*ptDBList);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInAcFileUnitSubPkg::InsertExecute(PVOID lpTemplet)
{
	PDB_PO_IN_AC_FILE_UNIT_SUB_PKG pd_t = (PDB_PO_IN_AC_FILE_UNIT_SUB_PKG)lpTemplet;

    return InsertPoInAcFileUnitSubPkg(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInAcFileUnitSubPkg::UpdateExecute(PVOID lpTemplet)
{
	PDB_PO_IN_AC_FILE_UNIT_SUB_PKG pd_t = (PDB_PO_IN_AC_FILE_UNIT_SUB_PKG)lpTemplet;

    return UpdatePoInAcFileUnitSubPkg(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInAcFileUnitSubPkg::DeleteExecute(UINT32 nID)
{
	return CDBMgrBase::DeleteExecute(nID);
}
//---------------------------------------------------------------------------






