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
#include "DBMgrPoInRegSvcObjUnit.h"

//---------------------------------------------------------------------------

CDBMgrPoInRegSvcObjUnit*		t_DBMgrPoInRegSvcObjUnit = NULL;

//---------------------------------------------------------------------------

CDBMgrPoInRegSvcObjUnit::CDBMgrPoInRegSvcObjUnit()
{
	m_strDBTName = "po_in_reg_svc_obj_unit";
}
//---------------------------------------------------------------------------

CDBMgrPoInRegSvcObjUnit::~CDBMgrPoInRegSvcObjUnit()
{
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInRegSvcObjUnit::SetInitalize()
{
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInRegSvcObjUnit::LoadDB(TListDBPoInRegSvcObjUnit& tDBPoInRegSvcObjUnitList)
{
    UINT32 nReadCnt = 0;
    DB_PO_IN_REG_SVC_OBJ_UNIT dpirsou;

    INT32 nIndex = 0;

    m_strQuery = SPrintf(DBMS_POLICY_QUERY_HDR_SELECT
						", svc_name"
						" FROM po_in_reg_svc_obj_unit WHERE used_flag=1;");
    if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_SELECT_FAIL;

    do
    {
		nIndex = 0;
		DB_PO_HEADER& tDPH = dpirsou.tDPH;

		tDPH						= GetDBField_PoHDR(nIndex);

		dpirsou.strSvcName			= GetDBField_String(nIndex++);		
		
        tDBPoInRegSvcObjUnitList.push_back(dpirsou);
        if(m_nLoadMaxID < UINT32(tDPH.nID))
			m_nLoadMaxID = tDPH.nID;
        nReadCnt++;
    }while(Next());
		
	m_nLoadNumber = tDBPoInRegSvcObjUnitList.size();
	WriteLogN("load database : [%s][%u]", m_strDBTName.c_str(), m_nLoadNumber);
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInRegSvcObjUnit::InsertPoInRegSvcObjUnit(DB_PO_IN_REG_SVC_OBJ_UNIT& dpirsou)
{
	DB_PO_HEADER& tDPH = dpirsou.tDPH;
	
	m_strQuery = SPrintf("INSERT INTO po_in_reg_svc_obj_unit("
						DBMS_POLICY_QUERY_HDR_INSERT_NAME
						", svc_name"
						") VALUES (%s"
                        ", '%s');",
                        GetPoHDRQuery_InsertValue(tDPH).c_str(), 
						dpirsou.strSvcName.c_str());

	if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_INSERT_FAIL;

    tDPH.nID      = GetLastID();

    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInRegSvcObjUnit::UpdatePoInRegSvcObjUnit(DB_PO_IN_REG_SVC_OBJ_UNIT& dpirsou)
{
	DB_PO_HEADER& tDPH = dpirsou.tDPH;

	m_strQuery = SPrintf("UPDATE po_in_reg_svc_obj_unit SET %s"
						", svc_name='%s'"
						" WHERE id=%u;",
						GetPoHDRQuery_Update(tDPH).c_str(),
						dpirsou.strSvcName.c_str(),
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

INT32	CDBMgrPoInRegSvcObjUnit::LoadExecute(PVOID lpTempletList)
{
	TListDBPoInRegSvcObjUnit* ptDBList = (TListDBPoInRegSvcObjUnit*)lpTempletList;

    return LoadDB(*ptDBList);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInRegSvcObjUnit::InsertExecute(PVOID lpTemplet)
{
	PDB_PO_IN_REG_SVC_OBJ_UNIT pd_t = (PDB_PO_IN_REG_SVC_OBJ_UNIT)lpTemplet;

    return InsertPoInRegSvcObjUnit(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInRegSvcObjUnit::UpdateExecute(PVOID lpTemplet)
{
	PDB_PO_IN_REG_SVC_OBJ_UNIT pd_t = (PDB_PO_IN_REG_SVC_OBJ_UNIT)lpTemplet;

    return UpdatePoInRegSvcObjUnit(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInRegSvcObjUnit::DeleteExecute(UINT32 nID)
{
	return CDBMgrBase::DeleteExecute(nID);
}
//---------------------------------------------------------------------------






