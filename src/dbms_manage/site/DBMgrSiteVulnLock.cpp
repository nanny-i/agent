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
#include "DBMgrSiteVulnLock.h"

//---------------------------------------------------------------------------

CDBMgrSiteVulnLock*		t_DBMgrSiteVulnLock = NULL;

//---------------------------------------------------------------------------

CDBMgrSiteVulnLock::CDBMgrSiteVulnLock()
{
	m_strDBTName = "site_vuln_lock";
}
//---------------------------------------------------------------------------

CDBMgrSiteVulnLock::~CDBMgrSiteVulnLock()
{
}
//---------------------------------------------------------------------------

INT32			CDBMgrSiteVulnLock::SetInitalize()
{
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrSiteVulnLock::LoadDB(TListDBSiteVulnLock& tDBSiteVulnLockList)
{
    UINT32 nReadCnt = 0;
    DB_SITE_VULN_LOCK data;

    INT32 nIndex = 0;

	m_strQuery = SPrintf("SELECT "
						"  id, used_flag, reg_date, used_mode, admin_id, ext_option"
						", name, descr"
						", os_type, os_id, os_pa"
						", vuln_id, vuln_sub_id"
						", lock_type, custom_id"
						", lock_path, lock_any_perm, ex_proc_path, ex_proc_perm"
						" FROM site_vuln_lock;");

	if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_SELECT_FAIL;

    do
    {
    	nIndex = 0;
    	
		data.nID						= GetDBField_UInt(nIndex++);
		data.nUsedFlag					= GetDBField_UInt(nIndex++);
		data.nRegDate					= GetDBField_UInt(nIndex++);
		data.nUsedMode					= GetDBField_UInt(nIndex++);
		data.nAdminID					= GetDBField_UInt(nIndex++);
		data.nExtOption					= GetDBField_UInt(nIndex++);

		data.strName					= GetDBField_String(nIndex++);
		data.strDescr					= GetDBField_String(nIndex++);

		data.nOsType					= GetDBField_UInt(nIndex++);
		data.nOsID						= GetDBField_UInt64(nIndex++);
		data.nOsPa						= GetDBField_UInt(nIndex++);

		data.nSVulnID					= GetDBField_UInt(nIndex++);
		data.nSVulnSubID				= GetDBField_UInt(nIndex++);
		
		data.nLockType					= GetDBField_UInt(nIndex++);
		data.nCustomID					= GetDBField_UInt(nIndex++);

		data.strLockPath				= GetDBField_String(nIndex++);
		data.nLockAnyPerm				= GetDBField_UInt(nIndex++);
		data.strExProcPath				= GetDBField_String(nIndex++);
		data.nExProcPerm				= GetDBField_UInt(nIndex++);
		
		{
			PathUnixToWin(data.strLockPath);
		}
		
        tDBSiteVulnLockList.push_back(data);
        if(m_nLoadMaxID < UINT32(data.nID))	m_nLoadMaxID = data.nID;
        nReadCnt++;
    }while(Next());
	m_nLoadNumber = (UINT32)tDBSiteVulnLockList.size();
	WriteLogN("load database : [%s][%u]", m_strDBTName.c_str(), m_nLoadNumber);
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrSiteVulnLock::InsertSiteVulnLock(DB_SITE_VULN_LOCK& data)
{
	String strLockPath = PathWinToUnix(data.strLockPath);

	m_strQuery = SPrintf("INSERT INTO site_vuln_lock ("
									"  id, reg_date, used_mode, admin_id, ext_option" //1
									", name, descr" //2
									", os_type, os_id, os_pa" //3
									", vuln_id, vuln_sub_id" //4
									", lock_type, custom_id" //5
									", lock_path, lock_any_perm, ex_proc_path, ex_proc_perm" //6
									") VALUES ("
									"  %u, %u, %u, %u, %u" //1
									", '%s', '%s'" //2
									", %u, '%I64u', %u" //3
									", %u, %u" //4
									", %u, %u" //5
									", '%s', %u, '%s', %u" //6
									");",
                                    data.nID, data.nRegDate, data.nUsedMode, data.nAdminID, data.nExtOption,
									data.strName.c_str(), data.strDescr.c_str(), 
									data.nOsType, data.nOsID, data.nOsPa,
									data.nSVulnID, data.nSVulnSubID,
									data.nLockType, data.nCustomID,
									strLockPath.c_str(), data.nLockAnyPerm, data.strExProcPath.c_str(), data.nExProcPerm);

	if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_INSERT_FAIL;

    data.nID      = GetLastID();
    
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrSiteVulnLock::UpdateSiteVulnLock(DB_SITE_VULN_LOCK& data)
{
	String strLockPath = PathWinToUnix(data.strLockPath);

	m_strQuery = SPrintf("UPDATE site_vuln_lock SET "
						"  reg_date=%u, used_mode=%u, admin_id=%u, ext_option=%u"
						", name='%s', descr='%s'"
						", os_type=%u, os_id='%I64u', os_pa=%u"
						", vuln_id=%u, vuln_sub_id=%u" //4
						", lock_type=%u, custom_id=%u" //5
						", lock_path='%s', lock_any_perm=%u, ex_proc_path='%s', ex_proc_perm=%u" //6
						" WHERE id=%u;",
						data.nRegDate, data.nUsedMode, data.nAdminID, data.nExtOption,
						data.strName.c_str(), data.strDescr.c_str(), 
						data.nOsType, data.nOsID, data.nOsPa,
						data.nSVulnID, data.nSVulnSubID,
						data.nLockType, data.nCustomID,
						strLockPath.c_str(), data.nLockAnyPerm, data.strExProcPath.c_str(), data.nExProcPerm, 
						data.nID);

	if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_UPDATE_FAIL;

	return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrSiteVulnLock::DeleteSiteVulnLock(UINT32 nID)
{
	m_strQuery = SPrintf("DELETE FROM site_vuln_lock WHERE id=%u;", nID);

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

INT32	CDBMgrSiteVulnLock::LoadExecute(PVOID lpTempletList)
{
	TListDBSiteVulnLock* ptDBList = (TListDBSiteVulnLock*)lpTempletList;

    return LoadDB(*ptDBList);
}
//---------------------------------------------------------------------------

INT32	CDBMgrSiteVulnLock::InsertExecute(PVOID lpTemplet)
{
	PDB_SITE_VULN_LOCK pd_t = (PDB_SITE_VULN_LOCK)lpTemplet;

    return InsertSiteVulnLock(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrSiteVulnLock::UpdateExecute(PVOID lpTemplet)
{
	PDB_SITE_VULN_LOCK pd_t = (PDB_SITE_VULN_LOCK)lpTemplet;

    return UpdateSiteVulnLock(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrSiteVulnLock::DeleteExecute(UINT32 nID)
{
	return DeleteSiteVulnLock(nID);
}
//---------------------------------------------------------------------------






