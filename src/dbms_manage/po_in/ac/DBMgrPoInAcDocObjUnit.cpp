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
#include "DBMgrPoInAcDocObjUnit.h"

//---------------------------------------------------------------------------

CDBMgrPoInAcDocObjUnit*		t_DBMgrPoInAcDocObjUnit = NULL;

//---------------------------------------------------------------------------

CDBMgrPoInAcDocObjUnit::CDBMgrPoInAcDocObjUnit()
{
	m_strDBTName = "po_in_ac_doc_obj_unit";
}
//---------------------------------------------------------------------------

CDBMgrPoInAcDocObjUnit::~CDBMgrPoInAcDocObjUnit()
{
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInAcDocObjUnit::SetInitalize()
{
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInAcDocObjUnit::LoadDB(TListDBPoInAcDocObjUnit& tDBPoInAcDocObjUnitList)
{
    UINT32 nReadCnt = 0;
    DB_PO_IN_AC_DOC_OBJ_UNIT dpiadou;

    INT32 nIndex = 0;

    m_strQuery = SPrintf(DBMS_POLICY_QUERY_HDR_SELECT
						", file_path"
						" FROM po_in_ac_doc_obj_unit WHERE used_flag=1;");
    if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_SELECT_FAIL;

    do
    {
		nIndex = 0;
		DB_PO_HEADER& tDPH = dpiadou.tDPH;

		tDPH						= GetDBField_PoHDR(nIndex);

		dpiadou.strFilePath			= GetDBField_String(nIndex++);		
		
        tDBPoInAcDocObjUnitList.push_back(dpiadou);
        if(m_nLoadMaxID < UINT32(tDPH.nID))	m_nLoadMaxID = tDPH.nID;
        nReadCnt++;
    }while(Next());
	m_nLoadNumber = tDBPoInAcDocObjUnitList.size();
	WriteLogN("load database : [%s][%u]", m_strDBTName.c_str(), m_nLoadNumber);
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInAcDocObjUnit::InsertPoInAcDocObjUnit(DB_PO_IN_AC_DOC_OBJ_UNIT& dpiadou)
{
	DB_PO_HEADER& tDPH = dpiadou.tDPH;
	
	m_strQuery = SPrintf("INSERT INTO po_in_ac_doc_obj_unit("
						DBMS_POLICY_QUERY_HDR_INSERT_NAME
						", file_path"
						") VALUES (%s"
                        ", '%s');",
                        GetPoHDRQuery_InsertValue(tDPH).c_str(), 
						dpiadou.strFilePath.c_str());

	if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_INSERT_FAIL;

    tDPH.nID      = GetLastID();

    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInAcDocObjUnit::UpdatePoInAcDocObjUnit(DB_PO_IN_AC_DOC_OBJ_UNIT& dpiadou)
{
	DB_PO_HEADER& tDPH = dpiadou.tDPH;

	m_strQuery = SPrintf("UPDATE po_in_ac_doc_obj_unit SET %s"
						", file_path='%s'"
						" WHERE id=%u;",
						GetPoHDRQuery_Update(tDPH).c_str(),
						dpiadou.strFilePath.c_str(),
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

INT32	CDBMgrPoInAcDocObjUnit::LoadExecute(PVOID lpTempletList)
{
	TListDBPoInAcDocObjUnit* ptDBList = (TListDBPoInAcDocObjUnit*)lpTempletList;

    return LoadDB(*ptDBList);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInAcDocObjUnit::InsertExecute(PVOID lpTemplet)
{
	PDB_PO_IN_AC_DOC_OBJ_UNIT pd_t = (PDB_PO_IN_AC_DOC_OBJ_UNIT)lpTemplet;

    return InsertPoInAcDocObjUnit(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInAcDocObjUnit::UpdateExecute(PVOID lpTemplet)
{
	PDB_PO_IN_AC_DOC_OBJ_UNIT pd_t = (PDB_PO_IN_AC_DOC_OBJ_UNIT)lpTemplet;

    return UpdatePoInAcDocObjUnit(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInAcDocObjUnit::DeleteExecute(UINT32 nID)
{
	return CDBMgrBase::DeleteExecute(nID);
}
//---------------------------------------------------------------------------






