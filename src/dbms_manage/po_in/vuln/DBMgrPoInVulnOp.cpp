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
#include "DBMgrPoInVulnOp.h"

//---------------------------------------------------------------------------

CDBMgrPoInVulnOp*		t_DBMgrPoInVulnOp = NULL;

//---------------------------------------------------------------------------

CDBMgrPoInVulnOp::CDBMgrPoInVulnOp()
{
	m_strDBTName = "po_in_vuln_op";
}
//---------------------------------------------------------------------------

CDBMgrPoInVulnOp::~CDBMgrPoInVulnOp()
{
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInVulnOp::SetInitalize()
{
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInVulnOp::LoadDB(TListDBPoInVulnOp& tDBPoInVulnOpList)
{
    UINT32 nReadCnt = 0;
    DB_PO_IN_VULN_OP data;

    INT32 nIndex = 0;

    m_strQuery = SPrintf(DBMS_POLICY_QUERY_HDR_SELECT
						" FROM po_in_vuln_op WHERE used_flag=1;");
    if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_SELECT_FAIL;

    do
    {
		nIndex = 0;
		DB_PO_HEADER& tDPH = data.tDPH;

		tDPH					= GetDBField_PoHDR(nIndex);
		
        tDBPoInVulnOpList.push_back(data);
        if(m_nLoadMaxID < UINT32(tDPH.nID))
			m_nLoadMaxID = tDPH.nID;
        nReadCnt++;
    }while(Next());
	m_nLoadNumber = tDBPoInVulnOpList.size();
	WriteLogN("load database : [%s][%u]", m_strDBTName.c_str(), m_nLoadNumber);
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInVulnOp::InsertPoInVulnOp(DB_PO_IN_VULN_OP& data)
{
	DB_PO_HEADER& tDPH = data.tDPH;

	m_strQuery = SPrintf("INSERT INTO po_in_vuln_op("
						DBMS_POLICY_QUERY_HDR_INSERT_NAME
						") VALUES (%s);",
                        GetPoHDRQuery_InsertValue(tDPH).c_str());

	if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_INSERT_FAIL;

    tDPH.nID      = GetLastID();

    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInVulnOp::UpdatePoInVulnOp(DB_PO_IN_VULN_OP& data)
{
	DB_PO_HEADER& tDPH = data.tDPH;

	m_strQuery = SPrintf("UPDATE po_in_vuln_op SET %s"
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

INT32	CDBMgrPoInVulnOp::LoadExecute(PVOID lpTempletList)
{
	TListDBPoInVulnOp* ptDBList = (TListDBPoInVulnOp*)lpTempletList;

    return LoadDB(*ptDBList);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInVulnOp::InsertExecute(PVOID lpTemplet)
{
	PDB_PO_IN_VULN_OP pd_t = (PDB_PO_IN_VULN_OP)lpTemplet;

    return InsertPoInVulnOp(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInVulnOp::UpdateExecute(PVOID lpTemplet)
{
	PDB_PO_IN_VULN_OP pd_t = (PDB_PO_IN_VULN_OP)lpTemplet;

    return UpdatePoInVulnOp(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInVulnOp::DeleteExecute(UINT32 nID)
{
	return CDBMgrBase::DeleteExecute(nID);
}
//---------------------------------------------------------------------------






