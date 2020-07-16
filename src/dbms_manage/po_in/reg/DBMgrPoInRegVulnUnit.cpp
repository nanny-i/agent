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
#include "DBMgrPoInRegVulnUnit.h"

//---------------------------------------------------------------------------

CDBMgrPoInRegVulnUnit*		t_DBMgrPoInRegVulnUnit = NULL;

//---------------------------------------------------------------------------

CDBMgrPoInRegVulnUnit::CDBMgrPoInRegVulnUnit()
{
	m_strDBTName = "po_in_reg_vuln_unit";
}
//---------------------------------------------------------------------------

CDBMgrPoInRegVulnUnit::~CDBMgrPoInRegVulnUnit()
{
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInRegVulnUnit::SetInitalize()
{
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInRegVulnUnit::LoadDB(TListDBPoInRegVulnUnit& tDBPoInRegVulnUnitList)
{
    UINT32 nReadCnt = 0;
    DB_PO_IN_REG_VULN_UNIT dpirvu;

    INT32 nIndex = 0;

    m_strQuery = SPrintf(DBMS_POLICY_QUERY_HDR_SELECT
						", vuln_name, vuln_value"						
						" FROM po_in_reg_vuln_unit WHERE used_flag=1;");
    if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_SELECT_FAIL;

    do
    {
		nIndex = 0;
		DB_PO_HEADER& tDPH = dpirvu.tDPH;

		tDPH						= GetDBField_PoHDR(nIndex);
		
		dpirvu.strVulnName			= GetDBField_String(nIndex++);		
		dpirvu.nVulnValue			= GetDBField_UInt(nIndex++);		
		
        tDBPoInRegVulnUnitList.push_back(dpirvu);
        if(m_nLoadMaxID < UINT32(tDPH.nID))
			m_nLoadMaxID = tDPH.nID;
        nReadCnt++;
    }while(Next());
	m_nLoadNumber = tDBPoInRegVulnUnitList.size();
	WriteLogN("load database : [%s][%u]", m_strDBTName.c_str(), m_nLoadNumber);
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInRegVulnUnit::InsertPoInRegVulnUnit(DB_PO_IN_REG_VULN_UNIT& dpirvu)
{
	DB_PO_HEADER& tDPH = dpirvu.tDPH;

	m_strQuery = SPrintf("INSERT INTO po_in_reg_vuln_unit("
						DBMS_POLICY_QUERY_HDR_INSERT_NAME
						", vuln_name, vuln_value"						
						") VALUES (%s"
						", %s, %u);",
						GetPoHDRQuery_InsertValue(tDPH).c_str(), 
						dpirvu.strVulnName.c_str(), dpirvu.nVulnValue);

	if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_INSERT_FAIL;

    tDPH.nID      = GetLastID();

    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInRegVulnUnit::UpdatePoInRegVulnUnit(DB_PO_IN_REG_VULN_UNIT& dpirvu)
{
	DB_PO_HEADER& tDPH = dpirvu.tDPH;

	m_strQuery = SPrintf("UPDATE po_in_reg_vuln_unit SET %s"
						", vuln_name=%s, vuln_value=%u"
						" WHERE id=%u;",
						GetPoHDRQuery_Update(tDPH).c_str(), 
						dpirvu.strVulnName.c_str(), dpirvu.nVulnValue,
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

INT32	CDBMgrPoInRegVulnUnit::LoadExecute(PVOID lpTempletList)
{
	TListDBPoInRegVulnUnit* ptDBList = (TListDBPoInRegVulnUnit*)lpTempletList;

    return LoadDB(*ptDBList);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInRegVulnUnit::InsertExecute(PVOID lpTemplet)
{
	PDB_PO_IN_REG_VULN_UNIT pd_t = (PDB_PO_IN_REG_VULN_UNIT)lpTemplet;

    return InsertPoInRegVulnUnit(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInRegVulnUnit::UpdateExecute(PVOID lpTemplet)
{
	PDB_PO_IN_REG_VULN_UNIT pd_t = (PDB_PO_IN_REG_VULN_UNIT)lpTemplet;

    return UpdatePoInRegVulnUnit(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInRegVulnUnit::DeleteExecute(UINT32 nID)
{
	return CDBMgrBase::DeleteExecute(nID);
}
//---------------------------------------------------------------------------






