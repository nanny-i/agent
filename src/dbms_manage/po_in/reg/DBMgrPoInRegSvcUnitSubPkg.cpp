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
#include "DBMgrPoInRegSvcUnitSubPkg.h"

//---------------------------------------------------------------------------

CDBMgrPoInRegSvcUnitSubPkg*		t_DBMgrPoInRegSvcUnitSubPkg = NULL;

//---------------------------------------------------------------------------

CDBMgrPoInRegSvcUnitSubPkg::CDBMgrPoInRegSvcUnitSubPkg()
{
	m_strDBTName = "po_in_reg_svc_unit_sub_pkg";
}
//---------------------------------------------------------------------------

CDBMgrPoInRegSvcUnitSubPkg::~CDBMgrPoInRegSvcUnitSubPkg()
{
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInRegSvcUnitSubPkg::SetInitalize()
{
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInRegSvcUnitSubPkg::LoadDB(TListDBPoInRegSvcUnitSubPkg& tDBPoInRegSvcUnitSubPkgList)
{
    UINT32 nReadCnt = 0;
    DB_PO_IN_REG_SVC_UNIT_SUB_PKG dpirsusp;

    INT32 nIndex = 0;

    m_strQuery = SPrintf(DBMS_POLICY_QUERY_PKG_HDR_SELECT
						", rule_order, ac_mode"
						" FROM po_in_reg_svc_unit_sub_pkg WHERE used_flag=1;");
    if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_SELECT_FAIL;

    do
    {
		nIndex = 0;
		DB_PO_HEADER& tDPH = dpirsusp.tDPH;

		tDPH						= GetDBField_PoPkgHDR(nIndex);

		dpirsusp.nRuleOrder			= GetDBField_UInt(nIndex++);
		dpirsusp.nAcMode			= GetDBField_UInt(nIndex++);
		
        tDBPoInRegSvcUnitSubPkgList.push_back(dpirsusp);
        if(m_nLoadMaxID < UINT32(tDPH.nID))
			m_nLoadMaxID = tDPH.nID;
        nReadCnt++;
    }while(Next());
	m_nLoadNumber = tDBPoInRegSvcUnitSubPkgList.size();
	WriteLogN("load database : [%s][%u]", m_strDBTName.c_str(), m_nLoadNumber);
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInRegSvcUnitSubPkg::InsertPoInRegSvcUnitSubPkg(DB_PO_IN_REG_SVC_UNIT_SUB_PKG& dpirsusp)
{
	DB_PO_HEADER& tDPH = dpirsusp.tDPH;

	m_strQuery = SPrintf("INSERT INTO po_in_reg_svc_unit_sub_pkg("
						DBMS_POLICY_QUERY_PKG_HDR_INSERT_NAME
						", rule_order, ac_mode ) VALUES (%s"
						", %u, %u);",
                        GetPoPkgHDRQuery_InsertValue(tDPH).c_str(),
						dpirsusp.nRuleOrder, dpirsusp.nAcMode);

	if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_INSERT_FAIL;

    tDPH.nID      = GetLastID();

    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInRegSvcUnitSubPkg::UpdatePoInRegSvcUnitSubPkg(DB_PO_IN_REG_SVC_UNIT_SUB_PKG& dpirsusp)
{
	DB_PO_HEADER& tDPH = dpirsusp.tDPH;

	m_strQuery = SPrintf("UPDATE po_in_reg_svc_unit_sub_pkg SET "
						"%s"
						", rule_order=%u, ac_mode=%u WHERE id=%u;",
						GetPoPkgHDRQuery_Update(tDPH).c_str(), 
						dpirsusp.nRuleOrder, dpirsusp.nAcMode,
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

INT32	CDBMgrPoInRegSvcUnitSubPkg::LoadExecute(PVOID lpTempletList)
{
	TListDBPoInRegSvcUnitSubPkg* ptDBList = (TListDBPoInRegSvcUnitSubPkg*)lpTempletList;

    return LoadDB(*ptDBList);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInRegSvcUnitSubPkg::InsertExecute(PVOID lpTemplet)
{
	PDB_PO_IN_REG_SVC_UNIT_SUB_PKG pd_t = (PDB_PO_IN_REG_SVC_UNIT_SUB_PKG)lpTemplet;

    return InsertPoInRegSvcUnitSubPkg(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInRegSvcUnitSubPkg::UpdateExecute(PVOID lpTemplet)
{
	PDB_PO_IN_REG_SVC_UNIT_SUB_PKG pd_t = (PDB_PO_IN_REG_SVC_UNIT_SUB_PKG)lpTemplet;

    return UpdatePoInRegSvcUnitSubPkg(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInRegSvcUnitSubPkg::DeleteExecute(UINT32 nID)
{
	return CDBMgrBase::DeleteExecute(nID);
}
//---------------------------------------------------------------------------






