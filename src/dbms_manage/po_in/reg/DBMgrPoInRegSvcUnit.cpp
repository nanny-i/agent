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
#include "DBMgrPoInRegSvcUnit.h"

//---------------------------------------------------------------------------

CDBMgrPoInRegSvcUnit*		t_DBMgrPoInRegSvcUnit = NULL;

//---------------------------------------------------------------------------

CDBMgrPoInRegSvcUnit::CDBMgrPoInRegSvcUnit()
{
	m_strDBTName = "po_in_reg_svc_unit";
}
//---------------------------------------------------------------------------

CDBMgrPoInRegSvcUnit::~CDBMgrPoInRegSvcUnit()
{
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInRegSvcUnit::SetInitalize()
{
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInRegSvcUnit::LoadDB(TListDBPoInRegSvcUnit& tDBPoInRegSvcUnitList)
{
    UINT32 nReadCnt = 0;
    DB_PO_IN_REG_SVC_UNIT dpirsu;

    INT32 nIndex = 0;

    m_strQuery = SPrintf(DBMS_POLICY_QUERY_HDR_SELECT
						", log_mode"
						" FROM po_in_reg_svc_unit WHERE used_flag=1;");
    if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_SELECT_FAIL;

    do
    {
		nIndex = 0;
		DB_PO_HEADER& tDPH = dpirsu.tDPH;

		tDPH						= GetDBField_PoHDR(nIndex);

		m_strValue					= GetDBField_String(nIndex++);
		HexToMap_64(m_strValue, dpirsu.tLogModeMap, SS_GLOBAL_LOG_REC_MODE_INDEX_TOTAL_NUMBER);		
		
        tDBPoInRegSvcUnitList.push_back(dpirsu);
        if(m_nLoadMaxID < UINT32(tDPH.nID))
			m_nLoadMaxID = tDPH.nID;
        nReadCnt++;
    }while(Next());
	m_nLoadNumber = tDBPoInRegSvcUnitList.size();
	WriteLogN("load database : [%s][%u]", m_strDBTName.c_str(), m_nLoadNumber);
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInRegSvcUnit::InsertPoInRegSvcUnit(DB_PO_IN_REG_SVC_UNIT& dpirsu)
{
	DB_PO_HEADER& tDPH = dpirsu.tDPH;
	String strLogMode;
	MapToHex_64(dpirsu.tLogModeMap, strLogMode, SS_GLOBAL_LOG_REC_MODE_INDEX_TOTAL_NUMBER);

	m_strQuery = SPrintf("INSERT INTO po_in_reg_svc_unit("
						DBMS_POLICY_QUERY_HDR_INSERT_NAME
						", log_mode"
						") VALUES (%s"
                        ", '%s');",
                        GetPoHDRQuery_InsertValue(tDPH).c_str(), 
						strLogMode.c_str());

	if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_INSERT_FAIL;

    tDPH.nID      = GetLastID();

    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInRegSvcUnit::UpdatePoInRegSvcUnit(DB_PO_IN_REG_SVC_UNIT& dpirsu)
{
	DB_PO_HEADER& tDPH = dpirsu.tDPH;
	String strLogMode;
	MapToHex_64(dpirsu.tLogModeMap, strLogMode, SS_GLOBAL_LOG_REC_MODE_INDEX_TOTAL_NUMBER);

	m_strQuery = SPrintf("UPDATE po_in_reg_svc_unit SET %s"
						", log_mode='%s'"
						" WHERE id=%u;",
						GetPoHDRQuery_Update(tDPH).c_str(), 
						strLogMode.c_str(),
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

INT32	CDBMgrPoInRegSvcUnit::LoadExecute(PVOID lpTempletList)
{
	TListDBPoInRegSvcUnit* ptDBList = (TListDBPoInRegSvcUnit*)lpTempletList;

    return LoadDB(*ptDBList);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInRegSvcUnit::InsertExecute(PVOID lpTemplet)
{
	PDB_PO_IN_REG_SVC_UNIT pd_t = (PDB_PO_IN_REG_SVC_UNIT)lpTemplet;

    return InsertPoInRegSvcUnit(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInRegSvcUnit::UpdateExecute(PVOID lpTemplet)
{
	PDB_PO_IN_REG_SVC_UNIT pd_t = (PDB_PO_IN_REG_SVC_UNIT)lpTemplet;

    return UpdatePoInRegSvcUnit(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInRegSvcUnit::DeleteExecute(UINT32 nID)
{
	return CDBMgrBase::DeleteExecute(nID);
}
//---------------------------------------------------------------------------






