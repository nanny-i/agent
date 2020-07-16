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
#include "DBMgrPoInPtnExPkg.h"

//---------------------------------------------------------------------------

CDBMgrPoInPtnExPkg*		t_DBMgrPoInPtnExPkg = NULL;

//---------------------------------------------------------------------------

CDBMgrPoInPtnExPkg::CDBMgrPoInPtnExPkg()
{
	m_strDBTName = "po_in_ptn_ex_pkg";
}
//---------------------------------------------------------------------------

CDBMgrPoInPtnExPkg::~CDBMgrPoInPtnExPkg()
{
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInPtnExPkg::SetInitalize()
{
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInPtnExPkg::LoadDB(TListDBPoInPtnExPkg& tDBPoInPtnExPkgList)
{
    UINT32 nReadCnt = 0;
    DB_PO_IN_PTN_EX_PKG datap;

    INT32 nIndex = 0;

    m_strQuery = SPrintf(DBMS_POLICY_QUERY_PKG_HDR_SELECT
						" FROM po_in_ptn_ex_pkg WHERE used_flag=1;");
    if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_SELECT_FAIL;

    do
    {
		nIndex = 0;
		DB_PO_HEADER& tDPH = datap.tDPH;

		tDPH						= GetDBField_PoPkgHDR(nIndex);
		
        tDBPoInPtnExPkgList.push_back(datap);
        if(m_nLoadMaxID < UINT32(tDPH.nID))
			m_nLoadMaxID = tDPH.nID;
        nReadCnt++;
    }while(Next());
	m_nLoadNumber = tDBPoInPtnExPkgList.size();
	WriteLogN("load database : [%s][%u]", m_strDBTName.c_str(), m_nLoadNumber);
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInPtnExPkg::InsertPoInPtnExPkg(DB_PO_IN_PTN_EX_PKG& datap)
{
	DB_PO_HEADER& tDPH = datap.tDPH;

	m_strQuery = SPrintf("INSERT INTO po_in_ptn_ex_pkg("
						DBMS_POLICY_QUERY_PKG_HDR_INSERT_NAME
						") VALUES (%s"
						");",
                        GetPoPkgHDRQuery_InsertValue(tDPH).c_str());

	if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_INSERT_FAIL;

    tDPH.nID      = GetLastID();

    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoInPtnExPkg::UpdatePoInPtnExPkg(DB_PO_IN_PTN_EX_PKG& datap)
{
	DB_PO_HEADER& tDPH = datap.tDPH;

	m_strQuery = SPrintf("UPDATE po_in_ptn_ex_pkg SET "
						"%s"
						" WHERE id=%u;",
						GetPoPkgHDRQuery_Update(tDPH).c_str(), 
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

INT32	CDBMgrPoInPtnExPkg::LoadExecute(PVOID lpTempletList)
{
	TListDBPoInPtnExPkg* ptDBList = (TListDBPoInPtnExPkg*)lpTempletList;

    return LoadDB(*ptDBList);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInPtnExPkg::InsertExecute(PVOID lpTemplet)
{
	PDB_PO_IN_PTN_EX_PKG pd_t = (PDB_PO_IN_PTN_EX_PKG)lpTemplet;

    return InsertPoInPtnExPkg(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInPtnExPkg::UpdateExecute(PVOID lpTemplet)
{
	PDB_PO_IN_PTN_EX_PKG pd_t = (PDB_PO_IN_PTN_EX_PKG)lpTemplet;

    return UpdatePoInPtnExPkg(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoInPtnExPkg::DeleteExecute(UINT32 nID)
{
	return CDBMgrBase::DeleteExecute(nID);
}
//---------------------------------------------------------------------------






