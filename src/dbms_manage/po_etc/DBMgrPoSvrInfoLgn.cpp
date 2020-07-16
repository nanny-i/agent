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
#include "DBMgrPoSvrInfoLgn.h"

//---------------------------------------------------------------------------

CDBMgrPoSvrInfoLgn*		t_DBMgrPoSvrInfoLgn = NULL;

//---------------------------------------------------------------------------

CDBMgrPoSvrInfoLgn::CDBMgrPoSvrInfoLgn()
{
	m_strDBTName = "po_svr_info_lgn";
}
//---------------------------------------------------------------------------

CDBMgrPoSvrInfoLgn::~CDBMgrPoSvrInfoLgn()
{
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoSvrInfoLgn::SetInitalize()
{
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoSvrInfoLgn::LoadDB(TListDBPoSvrInfoLgn& tDBPoSvrInfoLgnList)
{
    UINT32 nReadCnt = 0;
    DB_PO_SVR_INFO_LGN dpsil;

    INT32 nIndex = 0;

    m_strQuery = SPrintf("%s, svr_info_list FROM po_svr_info_lgn WHERE used_flag=1;", DBMS_POLICY_QUERY_HDR_SELECT);
    if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_SELECT_FAIL;

    do
    {
		nIndex = 0;
		DB_PO_HEADER& tDPH = dpsil.tDPH;

		tDPH						= GetDBField_PoHDR(nIndex);

		dpsil.strSvrInfoList		= GetDBField_String(nIndex++);
        
        tDBPoSvrInfoLgnList.push_back(dpsil);
        if(m_nLoadMaxID < UINT32(tDPH.nID))
			m_nLoadMaxID = tDPH.nID;
        nReadCnt++;
    }while(Next());
	m_nLoadNumber = tDBPoSvrInfoLgnList.size();
	WriteLogN("load database : [%s][%u]", m_strDBTName.c_str(), m_nLoadNumber);
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoSvrInfoLgn::InsertPoSvrInfoLgn(DB_PO_SVR_INFO_LGN& dpsil)
{
	DB_PO_HEADER& tDPH = dpsil.tDPH;

	m_strQuery = SPrintf("INSERT INTO po_svr_info_lgn("
						DBMS_POLICY_QUERY_HDR_INSERT_NAME
						", svr_info_list"
						") VALUES (%s"
                        ", '%s');",
                        GetPoHDRQuery_InsertValue(tDPH).c_str(), 
						dpsil.strSvrInfoList.c_str());

	if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_INSERT_FAIL;

    tDPH.nID      = GetLastID();

    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoSvrInfoLgn::UpdatePoSvrInfoLgn(DB_PO_SVR_INFO_LGN& dpsil)
{
	DB_PO_HEADER& tDPH = dpsil.tDPH;

	m_strQuery = SPrintf("UPDATE po_svr_info_lgn SET %s"
						", svr_info_list='%s'"
						" WHERE id=%u;",
						GetPoHDRQuery_Update(tDPH).c_str(),
						dpsil.strSvrInfoList.c_str(),
                        tDPH.nID);

	if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_UPDATE_FAIL;

    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoSvrInfoLgn::DeletePoSvrInfoLgn(UINT32 nID)
{
	m_strQuery = SPrintf(DBMS_DEFAULT_QUERY_TYPE_DELETE, m_strDBTName.c_str(), nID);
    
	if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_DELETE_FAIL;

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

INT32	CDBMgrPoSvrInfoLgn::LoadExecute(PVOID lpTempletList)
{
	TListDBPoSvrInfoLgn* ptDBList = (TListDBPoSvrInfoLgn*)lpTempletList;

    return LoadDB(*ptDBList);
}
//---------------------------------------------------------------------------


INT32	CDBMgrPoSvrInfoLgn::InsertExecute(PVOID lpTemplet)
{
	PDB_PO_SVR_INFO_LGN pd_t = (PDB_PO_SVR_INFO_LGN)lpTemplet;

    return InsertPoSvrInfoLgn(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoSvrInfoLgn::UpdateExecute(PVOID lpTemplet)
{
	PDB_PO_SVR_INFO_LGN pd_t = (PDB_PO_SVR_INFO_LGN)lpTemplet;

    return UpdatePoSvrInfoLgn(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoSvrInfoLgn::DeleteExecute(UINT32 nID)
{
	return DeletePoSvrInfoLgn(nID);
}
//---------------------------------------------------------------------------






