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
#include "DBMgrPoInRegSysUnit.h"

//---------------------------------------------------------------------------

CDBMgrPoInRegSysUnit*		t_DBMgrPoInRegSysUnit = NULL;

//---------------------------------------------------------------------------

CDBMgrPoInRegSysUnit::CDBMgrPoInRegSysUnit()
{
	m_strDBTName = "po_in_reg_sys_unit";
}
//---------------------------------------------------------------------------

CDBMgrPoInRegSysUnit::~CDBMgrPoInRegSysUnit()
{
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInRegSysUnit::SetInitalize()
{
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInRegSysUnit::LoadDB(TListDBPoInRegSysUnit& tDBPoInRegSysUnitList)
{
    UINT32 nReadCnt = 0;
    DB_PO_IN_REG_SYS_UNIT dpirsu;

    INT32 nIndex = 0;

    m_strQuery = SPrintf(DBMS_POLICY_QUERY_HDR_SELECT
						", sys_type, sys_perm, sys_name"						
						" FROM po_in_reg_sys_unit WHERE used_flag=1;");
    if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_SELECT_FAIL;

    do
    {
		nIndex = 0;
		DB_PO_HEADER& tDPH = dpirsu.tDPH;

		tDPH						= GetDBField_PoHDR(nIndex);

		dpirsu.nSysType				= GetDBField_UInt(nIndex++);		
		dpirsu.nSysPerm				= GetDBField_UInt(nIndex++);		
		dpirsu.strSysName			= GetDBField_String(nIndex++);		
		
        tDBPoInRegSysUnitList.push_back(dpirsu);
        if(m_nLoadMaxID < UINT32(tDPH.nID))
			m_nLoadMaxID = tDPH.nID;
        nReadCnt++;
    }while(Next());
	m_nLoadNumber = tDBPoInRegSysUnitList.size();
	WriteLogN("load database : [%s][%u]", m_strDBTName.c_str(), m_nLoadNumber);
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInRegSysUnit::InsertPoInRegSysUnit(DB_PO_IN_REG_SYS_UNIT& dpirsu)
{
	DB_PO_HEADER& tDPH = dpirsu.tDPH;

	m_strQuery = SPrintf("INSERT INTO po_in_reg_sys_unit("
						DBMS_POLICY_QUERY_HDR_INSERT_NAME
						", sys_type, sys_perm, sys_name"						
						") VALUES (%s"
						", %u, %u, %s);",
						GetPoHDRQuery_InsertValue(tDPH).c_str(), 
						dpirsu.nSysType, dpirsu.nSysPerm, dpirsu.strSysName.c_str());

	if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_INSERT_FAIL;

    tDPH.nID      = GetLastID();

    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInRegSysUnit::UpdatePoInRegSysUnit(DB_PO_IN_REG_SYS_UNIT& dpirsu)
{
	DB_PO_HEADER& tDPH = dpirsu.tDPH;

	m_strQuery = SPrintf("UPDATE po_in_reg_sys_unit SET %s"
						", sys_type=%u,, sys_perm=%u, sys_name=%s"
						" WHERE id=%u;",
						GetPoHDRQuery_Update(tDPH).c_str(), 
						dpirsu.nSysType, dpirsu.nSysPerm, dpirsu.strSysName.c_str(),
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

INT32	CDBMgrPoInRegSysUnit::LoadExecute(PVOID lpTempletList)
{
	TListDBPoInRegSysUnit* ptDBList = (TListDBPoInRegSysUnit*)lpTempletList;

    return LoadDB(*ptDBList);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInRegSysUnit::InsertExecute(PVOID lpTemplet)
{
	PDB_PO_IN_REG_SYS_UNIT pd_t = (PDB_PO_IN_REG_SYS_UNIT)lpTemplet;

    return InsertPoInRegSysUnit(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInRegSysUnit::UpdateExecute(PVOID lpTemplet)
{
	PDB_PO_IN_REG_SYS_UNIT pd_t = (PDB_PO_IN_REG_SYS_UNIT)lpTemplet;

    return UpdatePoInRegSysUnit(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInRegSysUnit::DeleteExecute(UINT32 nID)
{
	return CDBMgrBase::DeleteExecute(nID);
}
//---------------------------------------------------------------------------






