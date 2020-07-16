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
#include "DBMgrPoInRegSvcUnitObjPkg.h"

//---------------------------------------------------------------------------

CDBMgrPoInRegSvcUnitObjPkg*		t_DBMgrPoInRegSvcUnitObjPkg = NULL;

//---------------------------------------------------------------------------

CDBMgrPoInRegSvcUnitObjPkg::CDBMgrPoInRegSvcUnitObjPkg()
{
	m_strDBTName = "po_in_reg_svc_unit_obj_pkg";
}
//---------------------------------------------------------------------------

CDBMgrPoInRegSvcUnitObjPkg::~CDBMgrPoInRegSvcUnitObjPkg()
{
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInRegSvcUnitObjPkg::SetInitalize()
{
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInRegSvcUnitObjPkg::LoadDB(TListDBPoInRegSvcUnitObjPkg& tDBPoInRegSvcUnitObjPkgList)
{
    UINT32 nReadCnt = 0;
    DB_PO_IN_REG_SVC_UNIT_OBJ_PKG dpirsuop;

    INT32 nIndex = 0;

    m_strQuery = SPrintf(DBMS_POLICY_QUERY_PKG_HDR_SELECT
						" FROM po_in_reg_svc_unit_obj_pkg WHERE used_flag=1;");
    if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_SELECT_FAIL;

    do
    {
		nIndex = 0;
		DB_PO_HEADER& tDPH = dpirsuop.tDPH;

		tDPH						= GetDBField_PoPkgHDR(nIndex);
		
        tDBPoInRegSvcUnitObjPkgList.push_back(dpirsuop);
        if(m_nLoadMaxID < UINT32(tDPH.nID))
			m_nLoadMaxID = tDPH.nID;
        nReadCnt++;
    }while(Next());
	m_nLoadNumber = tDBPoInRegSvcUnitObjPkgList.size();
	WriteLogN("load database : [%s][%u]", m_strDBTName.c_str(), m_nLoadNumber);
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInRegSvcUnitObjPkg::InsertPoInRegSvcUnitObjPkg(DB_PO_IN_REG_SVC_UNIT_OBJ_PKG& dpirsuop)
{
	DB_PO_HEADER& tDPH = dpirsuop.tDPH;

	m_strQuery = SPrintf("INSERT INTO po_in_reg_svc_unit_obj_pkg("
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

INT32			CDBMgrPoInRegSvcUnitObjPkg::UpdatePoInRegSvcUnitObjPkg(DB_PO_IN_REG_SVC_UNIT_OBJ_PKG& dpirsuop)
{
	DB_PO_HEADER& tDPH = dpirsuop.tDPH;

	m_strQuery = SPrintf("UPDATE po_in_reg_svc_unit_obj_pkg SET "
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

INT32	CDBMgrPoInRegSvcUnitObjPkg::LoadExecute(PVOID lpTempletList)
{
	TListDBPoInRegSvcUnitObjPkg* ptDBList = (TListDBPoInRegSvcUnitObjPkg*)lpTempletList;

    return LoadDB(*ptDBList);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInRegSvcUnitObjPkg::InsertExecute(PVOID lpTemplet)
{
	PDB_PO_IN_REG_SVC_UNIT_OBJ_PKG pd_t = (PDB_PO_IN_REG_SVC_UNIT_OBJ_PKG)lpTemplet;

    return InsertPoInRegSvcUnitObjPkg(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInRegSvcUnitObjPkg::UpdateExecute(PVOID lpTemplet)
{
	PDB_PO_IN_REG_SVC_UNIT_OBJ_PKG pd_t = (PDB_PO_IN_REG_SVC_UNIT_OBJ_PKG)lpTemplet;

    return UpdatePoInRegSvcUnitObjPkg(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInRegSvcUnitObjPkg::DeleteExecute(UINT32 nID)
{
	return CDBMgrBase::DeleteExecute(nID);
}
//---------------------------------------------------------------------------






