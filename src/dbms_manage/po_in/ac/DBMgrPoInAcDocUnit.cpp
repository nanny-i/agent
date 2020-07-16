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
#include "DBMgrPoInAcDocUnit.h"

//---------------------------------------------------------------------------

CDBMgrPoInAcDocUnit*		t_DBMgrPoInAcDocUnit;

//---------------------------------------------------------------------------

CDBMgrPoInAcDocUnit::CDBMgrPoInAcDocUnit()
{
	m_strDBTName = "po_in_ac_doc_unit";
}
//---------------------------------------------------------------------------

CDBMgrPoInAcDocUnit::~CDBMgrPoInAcDocUnit()
{
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInAcDocUnit::SetInitalize()
{
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInAcDocUnit::LoadDB(TListDBPoInAcDocUnit& tDBPoInAcDocUnitList)
{
    UINT32 nReadCnt = 0;
    DB_PO_IN_AC_DOC_UNIT dpiadu;

    INT32 nIndex = 0;

    m_strQuery = SPrintf(DBMS_POLICY_QUERY_HDR_SELECT
						", log_mode, aid_type"
						" FROM po_in_ac_doc_unit WHERE used_flag=1;");
    if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_SELECT_FAIL;

    do
    {
		nIndex = 0;
		DB_PO_HEADER& tDPH = dpiadu.tDPH;

		tDPH						= GetDBField_PoHDR(nIndex);

		m_strValue					= GetDBField_String(nIndex++);
		HexToMap_64(m_strValue, dpiadu.tLogModeMap, SS_GLOBAL_LOG_REC_MODE_INDEX_TOTAL_NUMBER);
		dpiadu.nAidType				= GetDBField_UInt(nIndex++);
		
        tDBPoInAcDocUnitList.push_back(dpiadu);
        if(m_nLoadMaxID < UINT32(tDPH.nID))	m_nLoadMaxID = tDPH.nID;
        nReadCnt++;
    }while(Next());
	m_nLoadNumber = tDBPoInAcDocUnitList.size();
	WriteLogN("load database : [%s][%u]", m_strDBTName.c_str(), m_nLoadNumber);
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInAcDocUnit::InsertPoInAcDocUnit(DB_PO_IN_AC_DOC_UNIT& dpiadu)
{
	DB_PO_HEADER& tDPH = dpiadu.tDPH;
	String strLogMode;
	MapToHex_64(dpiadu.tLogModeMap, strLogMode, SS_GLOBAL_LOG_REC_MODE_INDEX_TOTAL_NUMBER);

	m_strQuery = SPrintf("INSERT INTO po_in_ac_doc_unit("
						DBMS_POLICY_QUERY_HDR_INSERT_NAME
						", log_mode, aid_type"
						") VALUES (%s"
                        ", '%s', %u);",
                        GetPoHDRQuery_InsertValue(tDPH).c_str(), 
						strLogMode.c_str(), dpiadu.nAidType);

	if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_INSERT_FAIL;

    tDPH.nID      = GetLastID();

    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInAcDocUnit::UpdatePoInAcDocUnit(DB_PO_IN_AC_DOC_UNIT& dpiadu)
{
	DB_PO_HEADER& tDPH = dpiadu.tDPH;
	String strLogMode;
	MapToHex_64(dpiadu.tLogModeMap, strLogMode, SS_GLOBAL_LOG_REC_MODE_INDEX_TOTAL_NUMBER);

	m_strQuery = SPrintf("UPDATE po_in_ac_doc_unit SET %s"
						", log_mode='%s', aid_type=%u"
						" WHERE id=%u;",
						GetPoHDRQuery_Update(tDPH).c_str(), 
						strLogMode.c_str(), dpiadu.nAidType,
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

INT32	CDBMgrPoInAcDocUnit::LoadExecute(PVOID lpTempletList)
{
	TListDBPoInAcDocUnit* ptDBList = (TListDBPoInAcDocUnit*)lpTempletList;

    return LoadDB(*ptDBList);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInAcDocUnit::InsertExecute(PVOID lpTemplet)
{
	PDB_PO_IN_AC_DOC_UNIT pd_t = (PDB_PO_IN_AC_DOC_UNIT)lpTemplet;

    return InsertPoInAcDocUnit(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInAcDocUnit::UpdateExecute(PVOID lpTemplet)
{
	PDB_PO_IN_AC_DOC_UNIT pd_t = (PDB_PO_IN_AC_DOC_UNIT)lpTemplet;

    return UpdatePoInAcDocUnit(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInAcDocUnit::DeleteExecute(UINT32 nID)
{
	return CDBMgrBase::DeleteExecute(nID);
}
//---------------------------------------------------------------------------






