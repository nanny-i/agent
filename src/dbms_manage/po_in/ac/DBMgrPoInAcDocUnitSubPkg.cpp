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
#include "DBMgrPoInAcDocUnitSubPkg.h"

//---------------------------------------------------------------------------

CDBMgrPoInAcDocUnitSubPkg*		t_DBMgrPoInAcDocUnitSubPkg = NULL;

//---------------------------------------------------------------------------

CDBMgrPoInAcDocUnitSubPkg::CDBMgrPoInAcDocUnitSubPkg()
{
	m_strDBTName = "po_in_ac_doc_unit_sub_pkg";
}
//---------------------------------------------------------------------------

CDBMgrPoInAcDocUnitSubPkg::~CDBMgrPoInAcDocUnitSubPkg()
{
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInAcDocUnitSubPkg::SetInitalize()
{
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInAcDocUnitSubPkg::LoadDB(TListDBPoInAcDocUnitSubPkg& tDBPoInAcDocUnitSubPkgList)
{
    UINT32 nReadCnt = 0;
    DB_PO_IN_AC_DOC_UNIT_SUB_PKG dpiadusp;

    INT32 nIndex = 0;

    m_strQuery = SPrintf(DBMS_POLICY_QUERY_PKG_HDR_SELECT
						", rule_order, ac_mode"
						" FROM po_in_ac_doc_unit_sub_pkg WHERE used_flag=1;");
    if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_SELECT_FAIL;

    do
    {
		nIndex = 0;
		DB_PO_HEADER& tDPH = dpiadusp.tDPH;

		tDPH						= GetDBField_PoPkgHDR(nIndex);

		dpiadusp.nRuleOrder			= GetDBField_UInt(nIndex++);
		dpiadusp.nAcMode			= GetDBField_UInt(nIndex++);
		
        tDBPoInAcDocUnitSubPkgList.push_back(dpiadusp);
        if(m_nLoadMaxID < UINT32(tDPH.nID))
			m_nLoadMaxID = tDPH.nID;
        nReadCnt++;
    }while(Next());
	m_nLoadNumber = tDBPoInAcDocUnitSubPkgList.size();
	WriteLogN("load database : [%s][%u]", m_strDBTName.c_str(), m_nLoadNumber);
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInAcDocUnitSubPkg::InsertPoInAcDocUnitSubPkg(DB_PO_IN_AC_DOC_UNIT_SUB_PKG& dpiadusp)
{
	DB_PO_HEADER& tDPH = dpiadusp.tDPH;

	m_strQuery = SPrintf("INSERT INTO po_in_ac_doc_unit_sub_pkg("
						DBMS_POLICY_QUERY_PKG_HDR_INSERT_NAME
						", rule_order, ac_mode ) VALUES (%s"
						", %u, %u);",
                        GetPoPkgHDRQuery_InsertValue(tDPH).c_str(),
						dpiadusp.nRuleOrder, dpiadusp.nAcMode);

	if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_INSERT_FAIL;

    tDPH.nID      = GetLastID();

    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInAcDocUnitSubPkg::UpdatePoInAcDocUnitSubPkg(DB_PO_IN_AC_DOC_UNIT_SUB_PKG& dpiadusp)
{
	DB_PO_HEADER& tDPH = dpiadusp.tDPH;

	m_strQuery = SPrintf("UPDATE po_in_ac_doc_unit_sub_pkg SET "
						"%s"
						", rule_order=%u, ac_mode=%u WHERE id=%u;",
						GetPoPkgHDRQuery_Update(tDPH).c_str(), 
						dpiadusp.nRuleOrder, dpiadusp.nAcMode,
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

INT32	CDBMgrPoInAcDocUnitSubPkg::LoadExecute(PVOID lpTempletList)
{
	TListDBPoInAcDocUnitSubPkg* ptDBList = (TListDBPoInAcDocUnitSubPkg*)lpTempletList;

    return LoadDB(*ptDBList);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInAcDocUnitSubPkg::InsertExecute(PVOID lpTemplet)
{
	PDB_PO_IN_AC_DOC_UNIT_SUB_PKG pd_t = (PDB_PO_IN_AC_DOC_UNIT_SUB_PKG)lpTemplet;

    return InsertPoInAcDocUnitSubPkg(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInAcDocUnitSubPkg::UpdateExecute(PVOID lpTemplet)
{
	PDB_PO_IN_AC_DOC_UNIT_SUB_PKG pd_t = (PDB_PO_IN_AC_DOC_UNIT_SUB_PKG)lpTemplet;

    return UpdatePoInAcDocUnitSubPkg(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInAcDocUnitSubPkg::DeleteExecute(UINT32 nID)
{
	return CDBMgrBase::DeleteExecute(nID);
}
//---------------------------------------------------------------------------






