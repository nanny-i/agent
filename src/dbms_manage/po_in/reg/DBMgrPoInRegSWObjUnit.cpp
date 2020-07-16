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
#include "DBMgrPoInRegSWObjUnit.h"

//---------------------------------------------------------------------------

CDBMgrPoInRegSWObjUnit*		t_DBMgrPoInRegSWObjUnit = NULL;

//---------------------------------------------------------------------------

CDBMgrPoInRegSWObjUnit::CDBMgrPoInRegSWObjUnit()
{
	m_strDBTName = "po_in_reg_sw_obj_unit";
}
//---------------------------------------------------------------------------

CDBMgrPoInRegSWObjUnit::~CDBMgrPoInRegSWObjUnit()
{
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInRegSWObjUnit::SetInitalize()
{
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInRegSWObjUnit::LoadDB(TListDBPoInRegSWObjUnit& tDBPoInRegSWObjUnitList)
{
    UINT32 nReadCnt = 0;
    DB_PO_IN_REG_SW_OBJ_UNIT dpirsou;

    INT32 nIndex = 0;

    m_strQuery = SPrintf(DBMS_POLICY_QUERY_HDR_SELECT
						", sw_name"
						" FROM po_in_reg_sw_obj_unit WHERE used_flag=1;");
    if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_SELECT_FAIL;

    do
    {
		nIndex = 0;
		DB_PO_HEADER& tDPH = dpirsou.tDPH;

		tDPH						= GetDBField_PoHDR(nIndex);

		dpirsou.strSWName			= GetDBField_String(nIndex++);		
		
        tDBPoInRegSWObjUnitList.push_back(dpirsou);
        if(m_nLoadMaxID < UINT32(tDPH.nID))
			m_nLoadMaxID = tDPH.nID;
        nReadCnt++;
    }while(Next());
	m_nLoadNumber = tDBPoInRegSWObjUnitList.size();
	WriteLogN("load database : [%s][%u]", m_strDBTName.c_str(), m_nLoadNumber);
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInRegSWObjUnit::InsertPoInRegSWObjUnit(DB_PO_IN_REG_SW_OBJ_UNIT& dpirsou)
{
	DB_PO_HEADER& tDPH = dpirsou.tDPH;
	
	m_strQuery = SPrintf("INSERT INTO po_in_reg_sw_obj_unit("
						DBMS_POLICY_QUERY_HDR_INSERT_NAME
						", sw_name"
						") VALUES (%s"
                        ", '%s');",
                        GetPoHDRQuery_InsertValue(tDPH).c_str(), 
						dpirsou.strSWName.c_str());

	if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_INSERT_FAIL;

    tDPH.nID      = GetLastID();

    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInRegSWObjUnit::UpdatePoInRegSWObjUnit(DB_PO_IN_REG_SW_OBJ_UNIT& dpirsou)
{
	DB_PO_HEADER& tDPH = dpirsou.tDPH;

	m_strQuery = SPrintf("UPDATE po_in_reg_sw_obj_unit SET %s"
						", sw_name='%s'"
						" WHERE id=%u;",
						GetPoHDRQuery_Update(tDPH).c_str(),
						dpirsou.strSWName.c_str(),
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

INT32	CDBMgrPoInRegSWObjUnit::LoadExecute(PVOID lpTempletList)
{
	TListDBPoInRegSWObjUnit* ptDBList = (TListDBPoInRegSWObjUnit*)lpTempletList;

    return LoadDB(*ptDBList);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInRegSWObjUnit::InsertExecute(PVOID lpTemplet)
{
	PDB_PO_IN_REG_SW_OBJ_UNIT pd_t = (PDB_PO_IN_REG_SW_OBJ_UNIT)lpTemplet;

    return InsertPoInRegSWObjUnit(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInRegSWObjUnit::UpdateExecute(PVOID lpTemplet)
{
	PDB_PO_IN_REG_SW_OBJ_UNIT pd_t = (PDB_PO_IN_REG_SW_OBJ_UNIT)lpTemplet;

    return UpdatePoInRegSWObjUnit(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInRegSWObjUnit::DeleteExecute(UINT32 nID)
{
	return CDBMgrBase::DeleteExecute(nID);
}
//---------------------------------------------------------------------------






