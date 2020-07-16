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
#include "DBMgrPoInAcSfObjUnit.h"

//---------------------------------------------------------------------------

CDBMgrPoInAcSfObjUnit*		t_DBMgrPoInAcSfObjUnit = NULL;

//---------------------------------------------------------------------------

CDBMgrPoInAcSfObjUnit::CDBMgrPoInAcSfObjUnit()
{
	m_strDBTName = "po_in_ac_sf_obj_unit";
}
//---------------------------------------------------------------------------

CDBMgrPoInAcSfObjUnit::~CDBMgrPoInAcSfObjUnit()
{
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInAcSfObjUnit::SetInitalize()
{
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInAcSfObjUnit::LoadDB(TListDBPoInAcSfObjUnit& tDBPoInAcSfObjUnitList)
{
    UINT32 nReadCnt = 0;
    DB_PO_IN_AC_SF_OBJ_UNIT dpiasou;

    INT32 nIndex = 0;

    m_strQuery = SPrintf(DBMS_POLICY_QUERY_HDR_SELECT
						", file_path, sf_mode"
						" FROM po_in_ac_sf_obj_unit WHERE used_flag=1;");
    if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_SELECT_FAIL;

    do
    {
		nIndex = 0;
		DB_PO_HEADER& tDPH = dpiasou.tDPH;

		tDPH						= GetDBField_PoHDR(nIndex);

		dpiasou.strFilePath			= GetDBField_String(nIndex++);
		dpiasou.nSFMode				= GetDBField_UInt(nIndex++);		
		
        tDBPoInAcSfObjUnitList.push_back(dpiasou);
        if(m_nLoadMaxID < UINT32(tDPH.nID))
			m_nLoadMaxID = tDPH.nID;
        nReadCnt++;
    }while(Next());
	m_nLoadNumber = tDBPoInAcSfObjUnitList.size();
	WriteLogN("load database : [%s][%u]", m_strDBTName.c_str(), m_nLoadNumber);
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInAcSfObjUnit::InsertPoInAcSfObjUnit(DB_PO_IN_AC_SF_OBJ_UNIT& dpiasou)
{
	DB_PO_HEADER& tDPH = dpiasou.tDPH;
	
	m_strQuery = SPrintf("INSERT INTO po_in_ac_sf_obj_unit("
						DBMS_POLICY_QUERY_HDR_INSERT_NAME
						", file_path, sf_mode"
						") VALUES (%s"
                        ", '%s', %u);",
                        GetPoHDRQuery_InsertValue(tDPH).c_str(), 
						dpiasou.strFilePath.c_str(), dpiasou.nSFMode);

	if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_INSERT_FAIL;

    tDPH.nID      = GetLastID();

    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInAcSfObjUnit::UpdatePoInAcSfObjUnit(DB_PO_IN_AC_SF_OBJ_UNIT& dpiasou)
{
	DB_PO_HEADER& tDPH = dpiasou.tDPH;

	m_strQuery = SPrintf("UPDATE po_in_ac_sf_obj_unit SET %s"
						", file_path='%s', sf_mode=%u"
						" WHERE id=%u;",
						GetPoHDRQuery_Update(tDPH).c_str(),
						dpiasou.strFilePath.c_str(), dpiasou.nSFMode,
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

INT32	CDBMgrPoInAcSfObjUnit::LoadExecute(PVOID lpTempletList)
{
	TListDBPoInAcSfObjUnit* ptDBList = (TListDBPoInAcSfObjUnit*)lpTempletList;

    return LoadDB(*ptDBList);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInAcSfObjUnit::InsertExecute(PVOID lpTemplet)
{
	PDB_PO_IN_AC_SF_OBJ_UNIT pd_t = (PDB_PO_IN_AC_SF_OBJ_UNIT)lpTemplet;

    return InsertPoInAcSfObjUnit(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInAcSfObjUnit::UpdateExecute(PVOID lpTemplet)
{
	PDB_PO_IN_AC_SF_OBJ_UNIT pd_t = (PDB_PO_IN_AC_SF_OBJ_UNIT)lpTemplet;

    return UpdatePoInAcSfObjUnit(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInAcSfObjUnit::DeleteExecute(UINT32 nID)
{
	return CDBMgrBase::DeleteExecute(nID);
}
//---------------------------------------------------------------------------






