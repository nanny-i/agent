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
#include "DBMgrPoInAcFileSubUnit.h"

//---------------------------------------------------------------------------

CDBMgrPoInAcFileSubUnit*		t_DBMgrPoInAcFileSubUnit = NULL;

//---------------------------------------------------------------------------

CDBMgrPoInAcFileSubUnit::CDBMgrPoInAcFileSubUnit()
{
	m_strDBTName = "po_in_ac_file_sub_unit";
}
//---------------------------------------------------------------------------

CDBMgrPoInAcFileSubUnit::~CDBMgrPoInAcFileSubUnit()
{
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInAcFileSubUnit::SetInitalize()
{
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInAcFileSubUnit::LoadDB(TListDBPoInAcFileSubUnit& tDBPoInAcFileSubUnitList)
{
    UINT32 nReadCnt = 0;
    DB_PO_IN_AC_FILE_SUB_UNIT dpiafsu;

    INT32 nIndex = 0;

    m_strQuery = SPrintf(DBMS_POLICY_QUERY_HDR_SELECT
						", sb_type, sb_name, sb_proc"
						" FROM po_in_ac_file_sub_unit WHERE used_flag=1;");
    if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_SELECT_FAIL;

    do
    {
		nIndex = 0;
		DB_PO_HEADER& tDPH = dpiafsu.tDPH;

		tDPH						= GetDBField_PoHDR(nIndex);

		dpiafsu.nSbType				= GetDBField_UInt(nIndex++);		
		dpiafsu.strSbName			= GetDBField_String(nIndex++);
		dpiafsu.strSbProc			= GetDBField_String(nIndex++);		
		
        tDBPoInAcFileSubUnitList.push_back(dpiafsu);
        if(m_nLoadMaxID < UINT32(tDPH.nID))
			m_nLoadMaxID = tDPH.nID;
        nReadCnt++;
    }while(Next());
	m_nLoadNumber = tDBPoInAcFileSubUnitList.size();
	WriteLogN("load database : [%s][%u]", m_strDBTName.c_str(), m_nLoadNumber);
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInAcFileSubUnit::InsertPoInAcFileSubUnit(DB_PO_IN_AC_FILE_SUB_UNIT& dpiafsu)
{
	DB_PO_HEADER& tDPH = dpiafsu.tDPH;

	m_strQuery = SPrintf("INSERT INTO po_in_ac_file_sub_unit("
						DBMS_POLICY_QUERY_HDR_INSERT_NAME
						", sb_type, sb_name, sb_proc,"
						") VALUES (%s"
                        ", %u, '%s', '%s');",
                        GetPoHDRQuery_InsertValue(tDPH).c_str(), 
						dpiafsu.nSbType, dpiafsu.strSbName.c_str(), dpiafsu.strSbProc.c_str());

	if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_INSERT_FAIL;

    tDPH.nID      = GetLastID();

    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInAcFileSubUnit::UpdatePoInAcFileSubUnit(DB_PO_IN_AC_FILE_SUB_UNIT& dpiafsu)
{
	DB_PO_HEADER& tDPH = dpiafsu.tDPH;	

	m_strQuery = SPrintf("UPDATE po_in_ac_file_sub_unit SET %s"
						", sb_type=%u, sb_name='%s', sb_proc='%s'"
						" WHERE id=%u;",
						GetPoHDRQuery_Update(tDPH).c_str(),
						dpiafsu.nSbType, dpiafsu.strSbName.c_str(), dpiafsu.strSbProc.c_str(),
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

INT32	CDBMgrPoInAcFileSubUnit::LoadExecute(PVOID lpTempletList)
{
	TListDBPoInAcFileSubUnit* ptDBList = (TListDBPoInAcFileSubUnit*)lpTempletList;

    return LoadDB(*ptDBList);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInAcFileSubUnit::InsertExecute(PVOID lpTemplet)
{
	PDB_PO_IN_AC_FILE_SUB_UNIT pd_t = (PDB_PO_IN_AC_FILE_SUB_UNIT)lpTemplet;

    return InsertPoInAcFileSubUnit(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInAcFileSubUnit::UpdateExecute(PVOID lpTemplet)
{
	PDB_PO_IN_AC_FILE_SUB_UNIT pd_t = (PDB_PO_IN_AC_FILE_SUB_UNIT)lpTemplet;

    return UpdatePoInAcFileSubUnit(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInAcFileSubUnit::DeleteExecute(UINT32 nID)
{
	return CDBMgrBase::DeleteExecute(nID);
}
//---------------------------------------------------------------------------






