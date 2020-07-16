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
#include "DBMgrPoInAcSfSubUnit.h"

//---------------------------------------------------------------------------

CDBMgrPoInAcSfSubUnit*		t_DBMgrPoInAcSfSubUnit = NULL;

//---------------------------------------------------------------------------

CDBMgrPoInAcSfSubUnit::CDBMgrPoInAcSfSubUnit()
{
	m_strDBTName = "po_in_ac_sf_sub_unit";
}
//---------------------------------------------------------------------------

CDBMgrPoInAcSfSubUnit::~CDBMgrPoInAcSfSubUnit()
{
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInAcSfSubUnit::SetInitalize()
{
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInAcSfSubUnit::LoadDB(TListDBPoInAcSfSubUnit& tDBPoInAcSfSubUnitList)
{
    UINT32 nReadCnt = 0;
    DB_PO_IN_AC_SF_SUB_UNIT dpiassu;

    INT32 nIndex = 0;

    m_strQuery = SPrintf(DBMS_POLICY_QUERY_HDR_SELECT
						", sb_type, sb_name, sb_proc"
						" FROM po_in_ac_sf_sub_unit WHERE used_flag=1;");
    if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_SELECT_FAIL;

    do
    {
		nIndex = 0;
		DB_PO_HEADER& tDPH = dpiassu.tDPH;

		tDPH						= GetDBField_PoHDR(nIndex);
		
		dpiassu.nSbType				= GetDBField_UInt(nIndex++);		
		dpiassu.strSbName			= GetDBField_String(nIndex++);
		dpiassu.strSbProc			= GetDBField_String(nIndex++);		
		
        tDBPoInAcSfSubUnitList.push_back(dpiassu);
        if(m_nLoadMaxID < UINT32(tDPH.nID))
			m_nLoadMaxID = tDPH.nID;
        nReadCnt++;
    }while(Next());
	m_nLoadNumber = tDBPoInAcSfSubUnitList.size();
	WriteLogN("load database : [%s][%u]", m_strDBTName.c_str(), m_nLoadNumber);
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInAcSfSubUnit::InsertPoInAcSfSubUnit(DB_PO_IN_AC_SF_SUB_UNIT& dpiassu)
{
	DB_PO_HEADER& tDPH = dpiassu.tDPH;	

	m_strQuery = SPrintf("INSERT INTO po_in_ac_sf_sub_unit("
						DBMS_POLICY_QUERY_HDR_INSERT_NAME
						", sb_type, sb_name, sb_proc,"
						") VALUES (%s"
                        ", %u, '%s', '%s');",
                        GetPoHDRQuery_InsertValue(tDPH).c_str(), 
						dpiassu.nSbType, dpiassu.strSbName.c_str(), dpiassu.strSbProc.c_str());

	if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_INSERT_FAIL;

    tDPH.nID      = GetLastID();

    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInAcSfSubUnit::UpdatePoInAcSfSubUnit(DB_PO_IN_AC_SF_SUB_UNIT& dpiassu)
{
	DB_PO_HEADER& tDPH = dpiassu.tDPH;	

	m_strQuery = SPrintf("UPDATE po_in_ac_sf_sub_unit SET %s"
						", sb_type=%u, sb_name='%s', sb_proc='%s'"
						" WHERE id=%u;",
						GetPoHDRQuery_Update(tDPH).c_str(),
						dpiassu.nSbType, dpiassu.strSbName.c_str(), dpiassu.strSbProc.c_str(),
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

INT32	CDBMgrPoInAcSfSubUnit::LoadExecute(PVOID lpTempletList)
{
	TListDBPoInAcSfSubUnit* ptDBList = (TListDBPoInAcSfSubUnit*)lpTempletList;

    return LoadDB(*ptDBList);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInAcSfSubUnit::InsertExecute(PVOID lpTemplet)
{
	PDB_PO_IN_AC_SF_SUB_UNIT pd_t = (PDB_PO_IN_AC_SF_SUB_UNIT)lpTemplet;

    return InsertPoInAcSfSubUnit(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInAcSfSubUnit::UpdateExecute(PVOID lpTemplet)
{
	PDB_PO_IN_AC_SF_SUB_UNIT pd_t = (PDB_PO_IN_AC_SF_SUB_UNIT)lpTemplet;

    return UpdatePoInAcSfSubUnit(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInAcSfSubUnit::DeleteExecute(UINT32 nID)
{
	return CDBMgrBase::DeleteExecute(nID);
}
//---------------------------------------------------------------------------






