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
#include "DBMgrPoInAcFileUnit.h"

//---------------------------------------------------------------------------

CDBMgrPoInAcFileUnit*		t_DBMgrPoInAcFileUnit = NULL;

//---------------------------------------------------------------------------

CDBMgrPoInAcFileUnit::CDBMgrPoInAcFileUnit()
{
	m_strDBTName = "po_in_ac_file_unit";
}
//---------------------------------------------------------------------------

CDBMgrPoInAcFileUnit::~CDBMgrPoInAcFileUnit()
{
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInAcFileUnit::SetInitalize()
{
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInAcFileUnit::LoadDB(TListDBPoInAcFileUnit& tDBPoInAcFileUnitList)
{
    UINT32 nReadCnt = 0;
    DB_PO_IN_AC_FILE_UNIT dpiafu;

    INT32 nIndex = 0;

    m_strQuery = SPrintf(DBMS_POLICY_QUERY_HDR_SELECT
						", log_mode"
						" FROM po_in_ac_file_unit WHERE used_flag=1;");
    if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_SELECT_FAIL;

    do
    {
		nIndex = 0;
		DB_PO_HEADER& tDPH = dpiafu.tDPH;

		tDPH						= GetDBField_PoHDR(nIndex);

		m_strValue					= GetDBField_String(nIndex++);
		HexToMap_64(m_strValue, dpiafu.tLogModeMap, SS_GLOBAL_LOG_REC_MODE_INDEX_TOTAL_NUMBER);		
		
        tDBPoInAcFileUnitList.push_back(dpiafu);
        if(m_nLoadMaxID < UINT32(tDPH.nID))
			m_nLoadMaxID = tDPH.nID;
        nReadCnt++;
    }while(Next());
	m_nLoadNumber = tDBPoInAcFileUnitList.size();
	WriteLogN("load database : [%s][%u]", m_strDBTName.c_str(), m_nLoadNumber);
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInAcFileUnit::InsertPoInAcFileUnit(DB_PO_IN_AC_FILE_UNIT& dpiafu)
{
	DB_PO_HEADER& tDPH = dpiafu.tDPH;
	String strLogMode;
	MapToHex_64(dpiafu.tLogModeMap, strLogMode, SS_GLOBAL_LOG_REC_MODE_INDEX_TOTAL_NUMBER);

	m_strQuery = SPrintf("INSERT INTO po_in_ac_file_unit("
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

INT32			CDBMgrPoInAcFileUnit::UpdatePoInAcFileUnit(DB_PO_IN_AC_FILE_UNIT& dpiafu)
{
	DB_PO_HEADER& tDPH = dpiafu.tDPH;
	String strLogMode;
	MapToHex_64(dpiafu.tLogModeMap, strLogMode, SS_GLOBAL_LOG_REC_MODE_INDEX_TOTAL_NUMBER);

	m_strQuery = SPrintf("UPDATE po_in_ac_file_unit SET %s"
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

INT32	CDBMgrPoInAcFileUnit::LoadExecute(PVOID lpTempletList)
{
	TListDBPoInAcFileUnit* ptDBList = (TListDBPoInAcFileUnit*)lpTempletList;

    return LoadDB(*ptDBList);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInAcFileUnit::InsertExecute(PVOID lpTemplet)
{
	PDB_PO_IN_AC_FILE_UNIT pd_t = (PDB_PO_IN_AC_FILE_UNIT)lpTemplet;

    return InsertPoInAcFileUnit(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInAcFileUnit::UpdateExecute(PVOID lpTemplet)
{
	PDB_PO_IN_AC_FILE_UNIT pd_t = (PDB_PO_IN_AC_FILE_UNIT)lpTemplet;

    return UpdatePoInAcFileUnit(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInAcFileUnit::DeleteExecute(UINT32 nID)
{
	return CDBMgrBase::DeleteExecute(nID);
}
//---------------------------------------------------------------------------






