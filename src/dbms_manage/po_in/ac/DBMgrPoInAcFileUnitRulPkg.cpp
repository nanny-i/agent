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
#include "DBMgrPoInAcFileUnitRulPkg.h"

//---------------------------------------------------------------------------

CDBMgrPoInAcFileUnitRulPkg*		t_DBMgrPoInAcFileUnitRulPkg = NULL;

//---------------------------------------------------------------------------

CDBMgrPoInAcFileUnitRulPkg::CDBMgrPoInAcFileUnitRulPkg()
{
	m_strDBTName = "po_in_ac_file_unit_rul_pkg";
}
//---------------------------------------------------------------------------

CDBMgrPoInAcFileUnitRulPkg::~CDBMgrPoInAcFileUnitRulPkg()
{
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInAcFileUnitRulPkg::SetInitalize()
{
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInAcFileUnitRulPkg::LoadDB(TListDBPoInAcFileUnitRulPkg& tDBPoInAcFileUnitRulPkgList)
{
    UINT32 nReadCnt = 0;
    DB_PO_IN_AC_FILE_UNIT_RUL_PKG dpiafurp;

    INT32 nIndex = 0;

    m_strQuery = SPrintf(DBMS_POLICY_QUERY_PKG_HDR_SELECT
						", rule_order, ac_mode"
						" FROM po_in_ac_file_unit_rul_pkg WHERE used_flag=1;");
    if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_SELECT_FAIL;

    do
    {
		nIndex = 0;
		DB_PO_HEADER& tDPH = dpiafurp.tDPH;

		tDPH						= GetDBField_PoPkgHDR(nIndex); 
		
		dpiafurp.nRuleOrder			= GetDBField_UInt(nIndex++);
		dpiafurp.nAcMode				= GetDBField_UInt(nIndex++);
		
        tDBPoInAcFileUnitRulPkgList.push_back(dpiafurp);
        if(m_nLoadMaxID < UINT32(tDPH.nID))
			m_nLoadMaxID = tDPH.nID;
        nReadCnt++;
    }while(Next());
	m_nLoadNumber = tDBPoInAcFileUnitRulPkgList.size();
	WriteLogN("load database : [%s][%u]", m_strDBTName.c_str(), m_nLoadNumber);
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInAcFileUnitRulPkg::InsertPoInAcFileUnitRulPkg(DB_PO_IN_AC_FILE_UNIT_RUL_PKG& dpiafurp)
{
	DB_PO_HEADER& tDPH = dpiafurp.tDPH;

	m_strQuery = SPrintf("INSERT INTO po_in_ac_file_unit_rul_pkg("
						DBMS_POLICY_QUERY_PKG_HDR_INSERT_NAME
						", rule_order, ac_mode ) VALUES (%s"
						", %u, %u);",
                        GetPoPkgHDRQuery_InsertValue(tDPH).c_str(),
						dpiafurp.nRuleOrder, dpiafurp.nAcMode);

	if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_INSERT_FAIL;

    tDPH.nID      = GetLastID();

    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInAcFileUnitRulPkg::UpdatePoInAcFileUnitRulPkg(DB_PO_IN_AC_FILE_UNIT_RUL_PKG& dpiafurp)
{
	DB_PO_HEADER& tDPH = dpiafurp.tDPH;

	m_strQuery = SPrintf("UPDATE po_in_ac_file_unit_rul_pkg SET "
						"%s"
						", rule_order=%u, ac_mode=%u WHERE id=%u;",
						GetPoPkgHDRQuery_Update(tDPH).c_str(), 
						dpiafurp.nRuleOrder, dpiafurp.nAcMode,
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

INT32	CDBMgrPoInAcFileUnitRulPkg::LoadExecute(PVOID lpTempletList)
{
	TListDBPoInAcFileUnitRulPkg* ptDBList = (TListDBPoInAcFileUnitRulPkg*)lpTempletList;

    return LoadDB(*ptDBList);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInAcFileUnitRulPkg::InsertExecute(PVOID lpTemplet)
{
	PDB_PO_IN_AC_FILE_UNIT_RUL_PKG pd_t = (PDB_PO_IN_AC_FILE_UNIT_RUL_PKG)lpTemplet;

    return InsertPoInAcFileUnitRulPkg(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInAcFileUnitRulPkg::UpdateExecute(PVOID lpTemplet)
{
	PDB_PO_IN_AC_FILE_UNIT_RUL_PKG pd_t = (PDB_PO_IN_AC_FILE_UNIT_RUL_PKG)lpTemplet;

    return UpdatePoInAcFileUnitRulPkg(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInAcFileUnitRulPkg::DeleteExecute(UINT32 nID)
{
	return CDBMgrBase::DeleteExecute(nID);
}
//---------------------------------------------------------------------------






