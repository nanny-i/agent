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
#include "DBMgrSiteVuln.h"

//---------------------------------------------------------------------------

CDBMgrSiteVuln*		t_DBMgrSiteVuln = NULL;

//---------------------------------------------------------------------------

CDBMgrSiteVuln::CDBMgrSiteVuln()
{
	m_strDBTName = "site_vuln";
}
//---------------------------------------------------------------------------

CDBMgrSiteVuln::~CDBMgrSiteVuln()
{
}
//---------------------------------------------------------------------------

INT32			CDBMgrSiteVuln::SetInitalize()
{
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrSiteVuln::LoadDB(TListDBSiteVuln& tDBSiteVulnList)
{
    UINT32 nReadCnt = 0;
    DB_SITE_VULN data;

    INT32 nIndex = 0;

	m_strQuery = SPrintf("SELECT "
						"  id, used_flag, reg_date, used_mode, admin_id, ext_option"
						", name, descr"
						", os_type, os_id, os_pa"
						", risk_level, def_score"
						" FROM site_vuln;");

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

		data.nRiskLevel					= GetDBField_UInt(nIndex++);
		data.nDefScore					= GetDBField_UInt(nIndex++);
		
        tDBSiteVulnList.push_back(data);
        if(m_nLoadMaxID < UINT32(data.nID))
			m_nLoadMaxID = data.nID;
        nReadCnt++;
    }while(Next());
	m_nLoadNumber = (UINT32)tDBSiteVulnList.size();
	WriteLogN("load database : [%s][%u]", m_strDBTName.c_str(), m_nLoadNumber);
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrSiteVuln::InsertSiteVuln(DB_SITE_VULN& data)
{
	m_strQuery = SPrintf("INSERT INTO site_vuln ("
									"  id, reg_date, used_mode, admin_id, ext_option"
									", name, descr"
									", os_type, os_id, os_pa"
									", risk_level, def_score"
									") VALUES ("
									"  %u, %u, %u, %u, %u"
									", '%s', '%s'"
									", %u, '%I64u', %u"
									", %u, %u"
									");",
                                    data.nID, data.nRegDate, data.nUsedMode, data.nAdminID, data.nExtOption,
									data.strName.c_str(), data.strDescr.c_str(), 
									data.nOsType, data.nOsID, data.nOsPa,
									data.nRiskLevel, data.nDefScore);

	if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_INSERT_FAIL;

    data.nID      = GetLastID();
    
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrSiteVuln::UpdateSiteVuln(DB_SITE_VULN& data)
{
	m_strQuery = SPrintf("UPDATE site_vuln SET "
						"  reg_date=%u, used_mode=%u, admin_id=%u, ext_option=%u"
						", name='%s', descr='%s'"
						", os_type=%u, os_id='%I64u', os_pa=%u"
						", risk_level=%u, def_score=%u"
						" WHERE id=%u;",
						data.nRegDate, data.nUsedMode, data.nAdminID, data.nExtOption,
						data.strName.c_str(), data.strDescr.c_str(), 
						data.nOsType, data.nOsID, data.nOsPa,
						data.nRiskLevel, data.nDefScore, 
						data.nID);

	if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_UPDATE_FAIL;

	return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrSiteVuln::DeleteSiteVuln(UINT32 nID)
{
	m_strQuery = SPrintf("DELETE FROM site_vuln WHERE id=%u;", nID);

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

INT32	CDBMgrSiteVuln::LoadExecute(PVOID lpTempletList)
{
	TListDBSiteVuln* ptDBList = (TListDBSiteVuln*)lpTempletList;

    return LoadDB(*ptDBList);
}
//---------------------------------------------------------------------------

INT32	CDBMgrSiteVuln::InsertExecute(PVOID lpTemplet)
{
	PDB_SITE_VULN pd_t = (PDB_SITE_VULN)lpTemplet;

    return InsertSiteVuln(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrSiteVuln::UpdateExecute(PVOID lpTemplet)
{
	PDB_SITE_VULN pd_t = (PDB_SITE_VULN)lpTemplet;

    return UpdateSiteVuln(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrSiteVuln::DeleteExecute(UINT32 nID)
{
	return DeleteSiteVuln(nID);
}
//---------------------------------------------------------------------------






