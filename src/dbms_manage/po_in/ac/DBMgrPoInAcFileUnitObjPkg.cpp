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
#include "DBMgrPoInAcFileUnitObjPkg.h"

//---------------------------------------------------------------------------

CDBMgrPoInAcFileUnitObjPkg*		t_DBMgrPoInAcFileUnitObjPkg = NULL;

//---------------------------------------------------------------------------

CDBMgrPoInAcFileUnitObjPkg::CDBMgrPoInAcFileUnitObjPkg()
{
	m_strDBTName = "po_in_ac_file_unit_obj_pkg";
}
//---------------------------------------------------------------------------

CDBMgrPoInAcFileUnitObjPkg::~CDBMgrPoInAcFileUnitObjPkg()
{
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInAcFileUnitObjPkg::SetInitalize()
{
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInAcFileUnitObjPkg::LoadDB(TListDBPoInAcFileUnitObjPkg& tDBPoInAcFileUnitObjPkgList)
{
    UINT32 nReadCnt = 0;
    DB_PO_IN_AC_FILE_UNIT_OBJ_PKG dpiafuop;

    INT32 nIndex = 0;

    m_strQuery = SPrintf(DBMS_POLICY_QUERY_PKG_HDR_SELECT
						" FROM po_in_ac_file_unit_obj_pkg WHERE used_flag=1;");
    if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_SELECT_FAIL;

    do
    {
		nIndex = 0;
		DB_PO_HEADER& tDPH = dpiafuop.tDPH;

		tDPH						= GetDBField_PoPkgHDR(nIndex);
		
        tDBPoInAcFileUnitObjPkgList.push_back(dpiafuop);
        if(m_nLoadMaxID < UINT32(tDPH.nID))
			m_nLoadMaxID = tDPH.nID;
        nReadCnt++;
    }while(Next());
	m_nLoadNumber = tDBPoInAcFileUnitObjPkgList.size();
	WriteLogN("load database : [%s][%u]", m_strDBTName.c_str(), m_nLoadNumber);
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInAcFileUnitObjPkg::InsertPoInAcFileUnitObjPkg(DB_PO_IN_AC_FILE_UNIT_OBJ_PKG& dpiafuop)
{
	DB_PO_HEADER& tDPH = dpiafuop.tDPH;

	m_strQuery = SPrintf("INSERT INTO po_in_ac_file_unit_obj_pkg("
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

INT32			CDBMgrPoInAcFileUnitObjPkg::UpdatePoInAcFileUnitObjPkg(DB_PO_IN_AC_FILE_UNIT_OBJ_PKG& dpiafuop)
{
	DB_PO_HEADER& tDPH = dpiafuop.tDPH;

	m_strQuery = SPrintf("UPDATE po_in_ac_file_unit_obj_pkg SET "
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

INT32	CDBMgrPoInAcFileUnitObjPkg::LoadExecute(PVOID lpTempletList)
{
	TListDBPoInAcFileUnitObjPkg* ptDBList = (TListDBPoInAcFileUnitObjPkg*)lpTempletList;

    return LoadDB(*ptDBList);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInAcFileUnitObjPkg::InsertExecute(PVOID lpTemplet)
{
	PDB_PO_IN_AC_FILE_UNIT_OBJ_PKG pd_t = (PDB_PO_IN_AC_FILE_UNIT_OBJ_PKG)lpTemplet;

    return InsertPoInAcFileUnitObjPkg(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInAcFileUnitObjPkg::UpdateExecute(PVOID lpTemplet)
{
	PDB_PO_IN_AC_FILE_UNIT_OBJ_PKG pd_t = (PDB_PO_IN_AC_FILE_UNIT_OBJ_PKG)lpTemplet;

    return UpdatePoInAcFileUnitObjPkg(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInAcFileUnitObjPkg::DeleteExecute(UINT32 nID)
{
	return CDBMgrBase::DeleteExecute(nID);
}
//---------------------------------------------------------------------------






