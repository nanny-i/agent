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
#include "DBMgrPoInAcFileUnitSchPkg.h"

//---------------------------------------------------------------------------

CDBMgrPoInAcFileUnitSchPkg*		t_DBMgrPoInAcFileUnitSchPkg = NULL;

//---------------------------------------------------------------------------

CDBMgrPoInAcFileUnitSchPkg::CDBMgrPoInAcFileUnitSchPkg()
{
	m_strDBTName = "po_in_ac_file_unit_sch_pkg";
}
//---------------------------------------------------------------------------

CDBMgrPoInAcFileUnitSchPkg::~CDBMgrPoInAcFileUnitSchPkg()
{
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInAcFileUnitSchPkg::SetInitalize()
{
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInAcFileUnitSchPkg::LoadDB(TListDBPoInAcFileUnitSchPkg& tDBPoInAcFileUnitSchPkgList)
{
    UINT32 nReadCnt = 0;
    DB_PO_IN_AC_FILE_UNIT_SCH_PKG dpiafusp;

    INT32 nIndex = 0;

    m_strQuery = SPrintf(DBMS_POLICY_QUERY_PKG_HDR_SELECT
						" FROM po_in_ac_file_unit_sch_pkg WHERE used_flag=1;");
    if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_SELECT_FAIL;

    do
    {
		nIndex = 0;
		DB_PO_HEADER& tDPH = dpiafusp.tDPH;

		tDPH						= GetDBField_PoPkgHDR(nIndex);
		
        tDBPoInAcFileUnitSchPkgList.push_back(dpiafusp);
        if(m_nLoadMaxID < UINT32(tDPH.nID))	m_nLoadMaxID = tDPH.nID;
        nReadCnt++;
    }while(Next());
	m_nLoadNumber = tDBPoInAcFileUnitSchPkgList.size();
	WriteLogN("load database : [%s][%u]", m_strDBTName.c_str(), m_nLoadNumber);
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInAcFileUnitSchPkg::InsertPoInAcFileUnitSchPkg(DB_PO_IN_AC_FILE_UNIT_SCH_PKG& dpiafusp)
{
	DB_PO_HEADER& tDPH = dpiafusp.tDPH;

	m_strQuery = SPrintf("INSERT INTO po_in_ac_file_unit_sch_pkg("
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

INT32			CDBMgrPoInAcFileUnitSchPkg::UpdatePoInAcFileUnitSchPkg(DB_PO_IN_AC_FILE_UNIT_SCH_PKG& dpiafusp)
{
	DB_PO_HEADER& tDPH = dpiafusp.tDPH;

	m_strQuery = SPrintf("UPDATE po_in_ac_file_unit_sch_pkg SET "
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

INT32	CDBMgrPoInAcFileUnitSchPkg::LoadExecute(PVOID lpTempletList)
{
	TListDBPoInAcFileUnitSchPkg* ptDBList = (TListDBPoInAcFileUnitSchPkg*)lpTempletList;

    return LoadDB(*ptDBList);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInAcFileUnitSchPkg::InsertExecute(PVOID lpTemplet)
{
	PDB_PO_IN_AC_FILE_UNIT_SCH_PKG pd_t = (PDB_PO_IN_AC_FILE_UNIT_SCH_PKG)lpTemplet;

    return InsertPoInAcFileUnitSchPkg(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInAcFileUnitSchPkg::UpdateExecute(PVOID lpTemplet)
{
	PDB_PO_IN_AC_FILE_UNIT_SCH_PKG pd_t = (PDB_PO_IN_AC_FILE_UNIT_SCH_PKG)lpTemplet;

    return UpdatePoInAcFileUnitSchPkg(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInAcFileUnitSchPkg::DeleteExecute(UINT32 nID)
{
	return CDBMgrBase::DeleteExecute(nID);
}
//---------------------------------------------------------------------------






