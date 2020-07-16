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
#include "DBMgrPoInRegSWSubUnit.h"

//---------------------------------------------------------------------------

CDBMgrPoInRegSWSubUnit*		t_DBMgrPoInRegSWSubUnit = NULL;

//---------------------------------------------------------------------------

CDBMgrPoInRegSWSubUnit::CDBMgrPoInRegSWSubUnit()
{
	m_strDBTName = "po_in_reg_sw_sub_unit";
}
//---------------------------------------------------------------------------

CDBMgrPoInRegSWSubUnit::~CDBMgrPoInRegSWSubUnit()
{
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInRegSWSubUnit::SetInitalize()
{
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInRegSWSubUnit::LoadDB(TListDBPoInRegSWSubUnit& tDBPoInRegSWSubUnitList)
{
    UINT32 nReadCnt = 0;
    DB_PO_IN_REG_SW_SUB_UNIT dpirssu;

    INT32 nIndex = 0;

    m_strQuery = SPrintf(DBMS_POLICY_QUERY_HDR_SELECT
						", sb_type, sb_name, sb_proc"
						" FROM po_in_reg_sw_sub_unit WHERE used_flag=1;");
    if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_SELECT_FAIL;

    do
    {
		nIndex = 0;
		DB_PO_HEADER& tDPH = dpirssu.tDPH;

		tDPH						= GetDBField_PoHDR(nIndex);

		dpirssu.nSbType				= GetDBField_UInt(nIndex++);		
		dpirssu.strSbName			= GetDBField_String(nIndex++);
		dpirssu.strSbProc			= GetDBField_String(nIndex++);		
		
        tDBPoInRegSWSubUnitList.push_back(dpirssu);
        if(m_nLoadMaxID < UINT32(tDPH.nID))
			m_nLoadMaxID = tDPH.nID;
        nReadCnt++;
    }while(Next());
	m_nLoadNumber = tDBPoInRegSWSubUnitList.size();
	WriteLogN("load database : [%s][%u]", m_strDBTName.c_str(), m_nLoadNumber);
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInRegSWSubUnit::InsertPoInRegSWSubUnit(DB_PO_IN_REG_SW_SUB_UNIT& dpirssu)
{
	DB_PO_HEADER& tDPH = dpirssu.tDPH;	

	m_strQuery = SPrintf("INSERT INTO po_in_reg_sw_sub_unit("
						DBMS_POLICY_QUERY_HDR_INSERT_NAME
						", sb_type, sb_name, sb_proc"
						") VALUES (%s"
                        ", %u, '%s', '%s');",
                        GetPoHDRQuery_InsertValue(tDPH).c_str(), 
						dpirssu.nSbType, dpirssu.strSbName.c_str(), dpirssu.strSbProc.c_str());

	if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_INSERT_FAIL;

    tDPH.nID      = GetLastID();

    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInRegSWSubUnit::UpdatePoInRegSWSubUnit(DB_PO_IN_REG_SW_SUB_UNIT& dpirssu)
{
	DB_PO_HEADER& tDPH = dpirssu.tDPH;	

	m_strQuery = SPrintf("UPDATE po_in_reg_sw_sub_unit SET %s"
						", sb_type=%u, sb_name='%s', sb_proc='%s'"
						" WHERE id=%u;",
						GetPoHDRQuery_Update(tDPH).c_str(),
						dpirssu.nSbType, dpirssu.strSbName.c_str(), dpirssu.strSbProc.c_str(),
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

INT32	CDBMgrPoInRegSWSubUnit::LoadExecute(PVOID lpTempletList)
{
	TListDBPoInRegSWSubUnit* ptDBList = (TListDBPoInRegSWSubUnit*)lpTempletList;

    return LoadDB(*ptDBList);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInRegSWSubUnit::InsertExecute(PVOID lpTemplet)
{
	PDB_PO_IN_REG_SW_SUB_UNIT pd_t = (PDB_PO_IN_REG_SW_SUB_UNIT)lpTemplet;

    return InsertPoInRegSWSubUnit(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInRegSWSubUnit::UpdateExecute(PVOID lpTemplet)
{
	PDB_PO_IN_REG_SW_SUB_UNIT pd_t = (PDB_PO_IN_REG_SW_SUB_UNIT)lpTemplet;

    return UpdatePoInRegSWSubUnit(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInRegSWSubUnit::DeleteExecute(UINT32 nID)
{
	return CDBMgrBase::DeleteExecute(nID);
}
//---------------------------------------------------------------------------






