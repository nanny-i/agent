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
#include "DBMgrPoHostRun.h"

//---------------------------------------------------------------------------

CDBMgrPoHostRun*		t_DBMgrPoHostRun = NULL;

//---------------------------------------------------------------------------

CDBMgrPoHostRun::CDBMgrPoHostRun()
{
	m_strDBTName = "po_host_run";
}
//---------------------------------------------------------------------------

CDBMgrPoHostRun::~CDBMgrPoHostRun()
{
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoHostRun::SetInitalize()
{
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoHostRun::LoadDB(TListDBPoHostRun& tDBPoHostRunList)
{
    UINT32 nReadCnt = 0;
    DB_PO_HOST_RUN dphr;

    INT32 nIndex = 0;

    m_strQuery = SPrintf(DBMS_POLICY_QUERY_HDR_SELECT
						", run_option, rm_log_day, lgn_con_period, mgr_show_type, show_log_day, boot_chk_type"
						", integrity_mode, cross_auth_mode "
						" FROM po_host_run WHERE used_flag=1;");
    if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_SELECT_FAIL;

    do
    {
		nIndex = 0;
		DB_PO_HEADER& tDPH = dphr.tDPH;

		tDPH						= GetDBField_PoHDR(nIndex);

		dphr.nRunOption				= GetDBField_UInt(nIndex++);
		dphr.nRmLogDay				= GetDBField_UInt(nIndex++);
		dphr.nLgnConPeriod			= GetDBField_UInt(nIndex++);
		dphr.nMgrShowType			= GetDBField_UInt(nIndex++);
		dphr.nShowLogDay			= GetDBField_UInt(nIndex++);
		dphr.nBootChkType			= GetDBField_UInt(nIndex++);
		dphr.nIntegrityMode			= GetDBField_UInt(nIndex++);
		dphr.nCrossAuthMode			= GetDBField_UInt(nIndex++);
        
        tDBPoHostRunList.push_back(dphr);
        if(m_nLoadMaxID < UINT32(tDPH.nID))
			m_nLoadMaxID = tDPH.nID;
        nReadCnt++;
    }while(Next());
	m_nLoadNumber = tDBPoHostRunList.size();
	WriteLogN("load database : [%s][%u]", m_strDBTName.c_str(), m_nLoadNumber);
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoHostRun::InsertPoHostRun(DB_PO_HOST_RUN& dphr)
{
	DB_PO_HEADER& tDPH = dphr.tDPH;

	m_strQuery = SPrintf("INSERT INTO po_host_run("
						DBMS_POLICY_QUERY_HDR_INSERT_NAME
						", run_option, rm_log_day, lgn_con_period, mgr_show_type, show_log_day, boot_chk_type"
						", integrity_mode, cross_auth_mode "
						") VALUES (%s"
                        ", %u, %u, %u, %u, %u, %u"
						", %u, %u);",
                        GetPoHDRQuery_InsertValue(tDPH).c_str(), 
						dphr.nRunOption, dphr.nRmLogDay, dphr.nLgnConPeriod, dphr.nMgrShowType, dphr.nShowLogDay, dphr.nBootChkType, 
						dphr.nIntegrityMode, dphr.nCrossAuthMode);

	if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_INSERT_FAIL;

    tDPH.nID      = GetLastID();

    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoHostRun::UpdatePoHostRun(DB_PO_HOST_RUN& dphr)
{
	DB_PO_HEADER& tDPH = dphr.tDPH;

	m_strQuery = SPrintf("UPDATE po_host_run SET %s"
						", run_option=%u, rm_log_day=%u, lgn_con_period=%u, mgr_show_type=%u"
						", show_log_day=%u, boot_chk_type=%u"
						", integrity_mode=%u, cross_auth_mode=%u "
						" WHERE id=%u;",
						GetPoHDRQuery_Update(tDPH).c_str(), 
						dphr.nRunOption, dphr.nRmLogDay, dphr.nLgnConPeriod, dphr.nMgrShowType, 
						dphr.nShowLogDay, dphr.nBootChkType,
						dphr.nIntegrityMode, dphr.nCrossAuthMode,
                        tDPH.nID);

	if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_UPDATE_FAIL;

    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoHostRun::DeletePoHostRun(UINT32 nID)
{
	m_strQuery = SPrintf(DBMS_DEFAULT_QUERY_TYPE_DELETE, m_strDBTName.c_str(), nID);
    
	if(DBOP_Check(ExecuteQuery(m_strQuery)))		return ERR_DBMS_DELETE_FAIL;

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

INT32	CDBMgrPoHostRun::LoadExecute(PVOID lpTempletList)
{
	TListDBPoHostRun* ptDBList = (TListDBPoHostRun*)lpTempletList;

    return LoadDB(*ptDBList);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoHostRun::InsertExecute(PVOID lpTemplet)
{
	PDB_PO_HOST_RUN pd_t = (PDB_PO_HOST_RUN)lpTemplet;

    return InsertPoHostRun(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoHostRun::UpdateExecute(PVOID lpTemplet)
{
	PDB_PO_HOST_RUN pd_t = (PDB_PO_HOST_RUN)lpTemplet;

    return UpdatePoHostRun(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoHostRun::DeleteExecute(UINT32 nID)
{
	return DeletePoHostRun(nID);
}
//---------------------------------------------------------------------------






