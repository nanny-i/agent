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
#include "DBMgrPoInAcFileSchUnit.h"

//---------------------------------------------------------------------------

CDBMgrPoInAcFileSchUnit*		t_DBMgrPoInAcFileSchUnit = NULL;

//---------------------------------------------------------------------------

CDBMgrPoInAcFileSchUnit::CDBMgrPoInAcFileSchUnit()
{
	m_strDBTName = "po_in_ac_file_sch_unit";
}
//---------------------------------------------------------------------------

CDBMgrPoInAcFileSchUnit::~CDBMgrPoInAcFileSchUnit()
{
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInAcFileSchUnit::SetInitalize()
{
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInAcFileSchUnit::LoadDB(TListDBPoInAcFileSchUnit& tDBPoInAcFileSchUnitList)
{
    UINT32 nReadCnt = 0;
    DB_PO_IN_AC_FILE_SCH_UNIT dpiafsu;

    INT32 nIndex = 0;

    m_strQuery = SPrintf(DBMS_POLICY_QUERY_HDR_SELECT
						", sch_mon, sch_day, sch_week, sch_hour, sch_min"
						" FROM po_in_ac_file_sch_unit WHERE used_flag=1;");
    if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_SELECT_FAIL;

    do
    {
		nIndex = 0;
		DB_PO_HEADER& tDPH = dpiafsu.tDPH;

		tDPH						= GetDBField_PoHDR(nIndex);

		dpiafsu.nSchMon				= GetDBField_UInt(nIndex++);
		dpiafsu.nSchDay				= GetDBField_UInt(nIndex++);
		dpiafsu.nSchWeek				= GetDBField_UInt(nIndex++);
		dpiafsu.nSchHour				= GetDBField_UInt(nIndex++);
		dpiafsu.nSchMin				= GetDBField_UInt(nIndex++);
		
        tDBPoInAcFileSchUnitList.push_back(dpiafsu);
        if(m_nLoadMaxID < UINT32(tDPH.nID))	m_nLoadMaxID = tDPH.nID;
        nReadCnt++;
    }while(Next());
	m_nLoadNumber = tDBPoInAcFileSchUnitList.size();
	WriteLogN("load database : [%s][%u]", m_strDBTName.c_str(), m_nLoadNumber);
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInAcFileSchUnit::InsertPoInAcFileSchUnit(DB_PO_IN_AC_FILE_SCH_UNIT& dpiafsu)
{
	DB_PO_HEADER& tDPH = dpiafsu.tDPH;

	m_strQuery = SPrintf("INSERT INTO po_in_ac_file_sch_unit("
						DBMS_POLICY_QUERY_HDR_INSERT_NAME
						", sch_mon, sch_day, sch_week, sch_hour, sch_min"
						") VALUES (%s"
                        ", %u, %u, %u, %u, %u);",
                        GetPoHDRQuery_InsertValue(tDPH).c_str(), 
						dpiafsu.nSchMon, dpiafsu.nSchDay, dpiafsu.nSchWeek, dpiafsu.nSchHour, dpiafsu.nSchMin);

	if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_INSERT_FAIL;

    tDPH.nID      = GetLastID();

    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInAcFileSchUnit::UpdatePoInAcFileSchUnit(DB_PO_IN_AC_FILE_SCH_UNIT& dpiafsu)
{
	DB_PO_HEADER& tDPH = dpiafsu.tDPH;

	m_strQuery = SPrintf("UPDATE po_in_ac_file_sch_unit SET %s"
						", sch_mon=%u, sch_day=%u, sch_week=%u, sch_hour=%u, sch_min=%u"
						" WHERE id=%u;",
						GetPoHDRQuery_Update(tDPH).c_str(),
						dpiafsu.nSchMon, dpiafsu.nSchDay, dpiafsu.nSchWeek, dpiafsu.nSchHour, dpiafsu.nSchMin,
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

INT32	CDBMgrPoInAcFileSchUnit::LoadExecute(PVOID lpTempletList)
{
	TListDBPoInAcFileSchUnit* ptDBList = (TListDBPoInAcFileSchUnit*)lpTempletList;

    return LoadDB(*ptDBList);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInAcFileSchUnit::InsertExecute(PVOID lpTemplet)
{
	PDB_PO_IN_AC_FILE_SCH_UNIT pd_t = (PDB_PO_IN_AC_FILE_SCH_UNIT)lpTemplet;

    return InsertPoInAcFileSchUnit(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInAcFileSchUnit::UpdateExecute(PVOID lpTemplet)
{
	PDB_PO_IN_AC_FILE_SCH_UNIT pd_t = (PDB_PO_IN_AC_FILE_SCH_UNIT)lpTemplet;

    return UpdatePoInAcFileSchUnit(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInAcFileSchUnit::DeleteExecute(UINT32 nID)
{
	return CDBMgrBase::DeleteExecute(nID);
}
//---------------------------------------------------------------------------






