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
#include "DBMgrPoInRegVulnPkg.h"

//---------------------------------------------------------------------------

CDBMgrPoInRegVulnPkg*		t_DBMgrPoInRegVulnPkg = NULL;

//---------------------------------------------------------------------------

CDBMgrPoInRegVulnPkg::CDBMgrPoInRegVulnPkg()
{
	m_strDBTName = "po_in_reg_vuln_pkg";
}
//---------------------------------------------------------------------------

CDBMgrPoInRegVulnPkg::~CDBMgrPoInRegVulnPkg()
{
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInRegVulnPkg::SetInitalize()
{
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInRegVulnPkg::LoadDB(TListDBPoInRegVulnPkg& tDBPoInRegVulnPkgList)
{
    UINT32 nReadCnt = 0;
    DB_PO_IN_REG_VULN_PKG dpirvp;

    INT32 nIndex = 0;

    m_strQuery = SPrintf(DBMS_POLICY_QUERY_PKG_HDR_SELECT
						" FROM po_in_reg_vuln_pkg WHERE used_flag=1;");
    if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_SELECT_FAIL;

    do
    {
		nIndex = 0;
		DB_PO_HEADER& tDPH = dpirvp.tDPH;

		tDPH						= GetDBField_PoPkgHDR(nIndex);
		
        tDBPoInRegVulnPkgList.push_back(dpirvp);
        if(m_nLoadMaxID < UINT32(tDPH.nID))
			m_nLoadMaxID = tDPH.nID;
        nReadCnt++;
    }while(Next());
	m_nLoadNumber = tDBPoInRegVulnPkgList.size();
	WriteLogN("load database : [%s][%u]", m_strDBTName.c_str(), m_nLoadNumber);
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInRegVulnPkg::InsertPoInRegVulnPkg(DB_PO_IN_REG_VULN_PKG& dpirvp)
{
	DB_PO_HEADER& tDPH = dpirvp.tDPH;

	m_strQuery = SPrintf("INSERT INTO po_in_reg_vuln_pkg("
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

INT32			CDBMgrPoInRegVulnPkg::UpdatePoInRegVulnPkg(DB_PO_IN_REG_VULN_PKG& dpirvp)
{
	DB_PO_HEADER& tDPH = dpirvp.tDPH;

	m_strQuery = SPrintf("UPDATE po_in_reg_vuln_pkg SET "
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

INT32	CDBMgrPoInRegVulnPkg::LoadExecute(PVOID lpTempletList)
{
	TListDBPoInRegVulnPkg* ptDBList = (TListDBPoInRegVulnPkg*)lpTempletList;

    return LoadDB(*ptDBList);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInRegVulnPkg::InsertExecute(PVOID lpTemplet)
{
	PDB_PO_IN_REG_VULN_PKG pd_t = (PDB_PO_IN_REG_VULN_PKG)lpTemplet;

    return InsertPoInRegVulnPkg(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInRegVulnPkg::UpdateExecute(PVOID lpTemplet)
{
	PDB_PO_IN_REG_VULN_PKG pd_t = (PDB_PO_IN_REG_VULN_PKG)lpTemplet;

    return UpdatePoInRegVulnPkg(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInRegVulnPkg::DeleteExecute(UINT32 nID)
{
	return CDBMgrBase::DeleteExecute(nID);
}
//---------------------------------------------------------------------------






