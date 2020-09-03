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
#include "DBMgrPoPmScan.h"

//---------------------------------------------------------------------------

CDBMgrPoPmScan*		t_DBMgrPoPmScan;

//---------------------------------------------------------------------------

CDBMgrPoPmScan::CDBMgrPoPmScan()
{
	m_strDBTName = "po_pm_scan";
}
//---------------------------------------------------------------------------

CDBMgrPoPmScan::~CDBMgrPoPmScan()
{
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoPmScan::SetInitalize()
{
    {
    	
	}
	//WriteLogN("current file dbms : [po_pm_scan][%d]", m_nDBSVer);
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoPmScan::LoadDB(TListDBPoPmScan& tDBPoPmScanList)
{
    UINT32 nReadCnt = 0;
    DB_PO_PM_SCAN data;

    INT32 nIndex = 0;

    m_strQuery = SPrintf(DBMS_POLICY_QUERY_HDR_SELECT
						" FROM po_pm_scan WHERE used_flag=1;");
    if(DBOP_Check(ExecuteQuery(m_strQuery)))		return ERR_DBMS_SELECT_FAIL;

    do
    {
		nIndex = 0;
		DB_PO_HEADER& tDPH = data.tDPH;

		tDPH						= GetDBField_PoHDR(nIndex);
		
        tDBPoPmScanList.push_back(data);
        if(m_nLoadMaxID < UINT32(tDPH.nID))	m_nLoadMaxID = tDPH.nID;
        nReadCnt++;
    }while(Next());

	m_nLoadNumber = tDBPoPmScanList.size();
	WriteLogN("load database : [%s][%u]", m_strDBTName.c_str(), m_nLoadNumber);
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoPmScan::InsertPoPmScan(DB_PO_PM_SCAN& data)
{
	DB_PO_HEADER& tDPH = data.tDPH;

	m_strQuery = SPrintf("INSERT INTO po_pm_scan("
						DBMS_POLICY_QUERY_HDR_INSERT_NAME
						") VALUES (%s"
						");",
                        GetPoHDRQuery_InsertValue(tDPH).c_str());

	if(DBOP_Check(ExecuteQuery(m_strQuery)))		return ERR_DBMS_INSERT_FAIL;

    tDPH.nID      = GetLastID();

    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoPmScan::UpdatePoPmScan(DB_PO_PM_SCAN& data)
{
	DB_PO_HEADER& tDPH = data.tDPH;

	m_strQuery = SPrintf("UPDATE po_pm_scan SET %s"
						" WHERE id=%u;",
						GetPoHDRQuery_Update(tDPH).c_str(),
						tDPH.nID);

	if(DBOP_Check(ExecuteQuery(m_strQuery)))		return ERR_DBMS_UPDATE_FAIL;

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

INT32	CDBMgrPoPmScan::LoadExecute(PVOID lpTempletList)
{
	TListDBPoPmScan* ptDBList = (TListDBPoPmScan*)lpTempletList;

    return LoadDB(*ptDBList);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoPmScan::InsertExecute(PVOID lpTemplet)
{
	PDB_PO_PM_SCAN pd_t = (PDB_PO_PM_SCAN)lpTemplet;

    return InsertPoPmScan(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoPmScan::UpdateExecute(PVOID lpTemplet)
{
	PDB_PO_PM_SCAN pd_t = (PDB_PO_PM_SCAN)lpTemplet;

    return UpdatePoPmScan(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoPmScan::DeleteExecute(UINT32 nID)
{
	return CDBMgrBase::DeleteExecute(nID);
}
//---------------------------------------------------------------------------






