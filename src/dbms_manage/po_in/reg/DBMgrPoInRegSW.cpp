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
#include "DBMgrPoInRegSW.h"

//---------------------------------------------------------------------------

CDBMgrPoInRegSW*		t_DBMgrPoInRegSW = NULL;

//---------------------------------------------------------------------------

CDBMgrPoInRegSW::CDBMgrPoInRegSW()
{
	m_strDBTName = "po_in_reg_sw";
}
//---------------------------------------------------------------------------

CDBMgrPoInRegSW::~CDBMgrPoInRegSW()
{
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInRegSW::SetInitalize()
{
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInRegSW::LoadDB(TListDBPoInRegSW& tDBPoInRegSWList)
{
    UINT32 nReadCnt = 0;
    DB_PO_IN_REG_SW dpirs;

    INT32 nIndex = 0;

    m_strQuery = SPrintf(DBMS_POLICY_QUERY_HDR_SELECT
						" FROM po_in_reg_sw WHERE used_flag=1;");
    if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_SELECT_FAIL;

    do
    {
		nIndex = 0;
		DB_PO_HEADER& tDPH = dpirs.tDPH;

		tDPH						= GetDBField_PoHDR(nIndex);
		
        tDBPoInRegSWList.push_back(dpirs);
        if(m_nLoadMaxID < UINT32(tDPH.nID))
			m_nLoadMaxID = tDPH.nID;
        nReadCnt++;
    }while(Next());
	m_nLoadNumber = tDBPoInRegSWList.size();
	WriteLogN("load database : [%s][%u]", m_strDBTName.c_str(), m_nLoadNumber);
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInRegSW::InsertPoInRegSW(DB_PO_IN_REG_SW& dpirs)
{
	DB_PO_HEADER& tDPH = dpirs.tDPH;

	m_strQuery = SPrintf("INSERT INTO po_in_reg_sw("
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

INT32			CDBMgrPoInRegSW::UpdatePoInRegSW(DB_PO_IN_REG_SW& dpirs)
{
	DB_PO_HEADER& tDPH = dpirs.tDPH;

	m_strQuery = SPrintf("UPDATE po_in_reg_sw SET %s"
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

INT32	CDBMgrPoInRegSW::LoadExecute(PVOID lpTempletList)
{
	TListDBPoInRegSW* ptDBList = (TListDBPoInRegSW*)lpTempletList;

    return LoadDB(*ptDBList);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInRegSW::InsertExecute(PVOID lpTemplet)
{
	PDB_PO_IN_REG_SW pd_t = (PDB_PO_IN_REG_SW)lpTemplet;

    return InsertPoInRegSW(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInRegSW::UpdateExecute(PVOID lpTemplet)
{
	PDB_PO_IN_REG_SW pd_t = (PDB_PO_IN_REG_SW)lpTemplet;

    return UpdatePoInRegSW(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInRegSW::DeleteExecute(UINT32 nID)
{
	return CDBMgrBase::DeleteExecute(nID);
}
//---------------------------------------------------------------------------






