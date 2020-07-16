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
#include "DBMgrPoInRegSvc.h"

//---------------------------------------------------------------------------

CDBMgrPoInRegSvc*		t_DBMgrPoInRegSvc = NULL;

//---------------------------------------------------------------------------

CDBMgrPoInRegSvc::CDBMgrPoInRegSvc()
{
	m_strDBTName = "po_in_reg_svc";
}
//---------------------------------------------------------------------------

CDBMgrPoInRegSvc::~CDBMgrPoInRegSvc()
{
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInRegSvc::SetInitalize()
{
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInRegSvc::LoadDB(TListDBPoInRegSvc& tDBPoInRegSvcList)
{
    UINT32 nReadCnt = 0;
    DB_PO_IN_REG_SVC dpirs;

    INT32 nIndex = 0;

    m_strQuery = SPrintf(DBMS_POLICY_QUERY_HDR_SELECT
						" FROM po_in_reg_svc WHERE used_flag=1;");
    if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_SELECT_FAIL;

    do
    {
		nIndex = 0;
		DB_PO_HEADER& tDPH = dpirs.tDPH;

		tDPH						= GetDBField_PoHDR(nIndex);
		
        tDBPoInRegSvcList.push_back(dpirs);
        if(m_nLoadMaxID < UINT32(tDPH.nID))
			m_nLoadMaxID = tDPH.nID;
        nReadCnt++;
    }while(Next());
	m_nLoadNumber = tDBPoInRegSvcList.size();
	WriteLogN("load database : [%s][%u]", m_strDBTName.c_str(), m_nLoadNumber);
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInRegSvc::InsertPoInRegSvc(DB_PO_IN_REG_SVC& dpirs)
{
	DB_PO_HEADER& tDPH = dpirs.tDPH;

	m_strQuery = SPrintf("INSERT INTO po_in_reg_svc("
						DBMS_POLICY_QUERY_HDR_INSERT_NAME
						") VALUES (%s"
						");",
                        GetPoHDRQuery_InsertValue(tDPH).c_str());

	if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_INSERT_FAIL;

    tDPH.nID      = GetLastID();

    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInRegSvc::UpdatePoInRegSvc(DB_PO_IN_REG_SVC& dpirs)
{
	DB_PO_HEADER& tDPH = dpirs.tDPH;

	m_strQuery = SPrintf("UPDATE po_in_reg_svc SET %s"
						" WHERE id=%u;",
						GetPoHDRQuery_Update(tDPH).c_str(),
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

INT32	CDBMgrPoInRegSvc::LoadExecute(PVOID lpTempletList)
{
	TListDBPoInRegSvc* ptDBList = (TListDBPoInRegSvc*)lpTempletList;

    return LoadDB(*ptDBList);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInRegSvc::InsertExecute(PVOID lpTemplet)
{
	PDB_PO_IN_REG_SVC pd_t = (PDB_PO_IN_REG_SVC)lpTemplet;

    return InsertPoInRegSvc(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInRegSvc::UpdateExecute(PVOID lpTemplet)
{
	PDB_PO_IN_REG_SVC pd_t = (PDB_PO_IN_REG_SVC)lpTemplet;

    return UpdatePoInRegSvc(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInRegSvc::DeleteExecute(UINT32 nID)
{
	return CDBMgrBase::DeleteExecute(nID);
}
//---------------------------------------------------------------------------






