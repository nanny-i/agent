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
#include "DBMgrEnvLicense.h"

//---------------------------------------------------------------------------

CDBMgrEnvLicense*		t_DBMgrEnvLicense;

//---------------------------------------------------------------------------

CDBMgrEnvLicense::CDBMgrEnvLicense()
{
	m_strDBTName = "env_license";
}
//---------------------------------------------------------------------------

CDBMgrEnvLicense::~CDBMgrEnvLicense()
{
}
//---------------------------------------------------------------------------

INT32			CDBMgrEnvLicense::SetInitalize()
{
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrEnvLicense::LoadDB(TListDBEnvLicense& tDBEnvLicenseList)
{
    UINT32 nReadCnt = 0;
    DB_ENV_LICENSE del;

    INT32 nIndex = 0;

    m_strQuery = SPrintf(DBMS_POLICY_QUERY_HDR_SELECT
						", license_key"
						", right_package, right_policy, right_control "
						" FROM env_license WHERE used_flag=1;");
    if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_SELECT_FAIL;

    do
    {
		nIndex = 0;
		
		DB_PO_HEADER& tDPH = del.tDPH;

		tDPH					= GetDBField_PoHDR(nIndex);

		del.strLicenseKey		= GetDBField_String(nIndex++);
		m_strValue				= GetDBField_String(nIndex++);
		HexToMap_64(m_strValue, del.tRightPackageMap,	SS_ADMIN_RIGHT_TYPE_CLASS_NUM_PACKAGE);
		m_strValue				= GetDBField_String(nIndex++);
		HexToMap_64(m_strValue, del.tRightPolicyMap,	SS_ADMIN_RIGHT_TYPE_CLASS_NUM_POLICY);
		m_strValue				= GetDBField_String(nIndex++);
		HexToMap_64(m_strValue, del.tRightControlMap,	SS_ADMIN_RIGHT_TYPE_CLASS_NUM_CONTROL);

        tDBEnvLicenseList.push_back(del);
        if(m_nLoadMaxID < UINT32(tDPH.nID))
			m_nLoadMaxID = tDPH.nID;
        nReadCnt++;
    }while(Next());
	m_nLoadNumber = tDBEnvLicenseList.size();
	WriteLogN("load database : [%s][%u]", m_strDBTName.c_str(), m_nLoadNumber);
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrEnvLicense::InsertEnvLicense(DB_ENV_LICENSE& del)
{
	DB_PO_HEADER& tDPH = del.tDPH;
	
	String strRightPackage, strRightPolicy, strRightControl;

	MapToHex_64(del.tRightPackageMap, strRightPackage,	SS_ADMIN_RIGHT_TYPE_CLASS_NUM_PACKAGE);
	MapToHex_64(del.tRightPolicyMap,  strRightPolicy,	SS_ADMIN_RIGHT_TYPE_CLASS_NUM_POLICY);
	MapToHex_64(del.tRightControlMap, strRightControl,	SS_ADMIN_RIGHT_TYPE_CLASS_NUM_CONTROL);

	m_strQuery = SPrintf("INSERT INTO env_license("
						DBMS_POLICY_QUERY_HDR_INSERT_NAME
						", license_key, "
						"right_package, right_policy, right_control"
						") VALUES (%s"
						", '%s', "
						"'%s', '%s', '%s'"
						");",                        
						GetPoHDRQuery_InsertValue(tDPH).c_str(), 
						del.strLicenseKey.c_str(), 
						strRightPackage.c_str(), strRightPolicy.c_str(), strRightControl.c_str());

	if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_INSERT_FAIL;

    tDPH.nID      = GetLastID();

    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrEnvLicense::UpdateEnvLicense(DB_ENV_LICENSE& del)
{
	DB_PO_HEADER& tDPH = del.tDPH;

	String strRightPackage, strRightPolicy, strRightControl;

	MapToHex_64(del.tRightPackageMap, strRightPackage, SS_ADMIN_RIGHT_TYPE_CLASS_NUM_PACKAGE);
	MapToHex_64(del.tRightPolicyMap,  strRightPolicy, SS_ADMIN_RIGHT_TYPE_CLASS_NUM_POLICY);
	MapToHex_64(del.tRightControlMap, strRightControl, SS_ADMIN_RIGHT_TYPE_CLASS_NUM_CONTROL);

	m_strQuery = SPrintf("UPDATE env_license SET %s"
						", license_key='%s', "
						"right_package='%s', right_policy='%s', right_control='%s'"
						" WHERE id=%u;",
						GetPoHDRQuery_Update(tDPH).c_str(),
						del.strLicenseKey.c_str(), 
						strRightPackage.c_str(), strRightPolicy.c_str(), strRightControl.c_str(),
                        tDPH.nID);

	if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_UPDATE_FAIL;

    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrEnvLicense::DeleteEnvLicense(UINT32 nID)
{
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

INT32	CDBMgrEnvLicense::LoadExecute(PVOID lpTempletList)
{
	TListDBEnvLicense* ptDBList = (TListDBEnvLicense*)lpTempletList;

    return LoadDB(*ptDBList);
}

//---------------------------------------------------------------------------

INT32	CDBMgrEnvLicense::InsertExecute(PVOID lpTemplet)
{
	PDB_ENV_LICENSE pd_t = (PDB_ENV_LICENSE)lpTemplet;

    return InsertEnvLicense(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrEnvLicense::UpdateExecute(PVOID lpTemplet)
{
	PDB_ENV_LICENSE pd_t = (PDB_ENV_LICENSE)lpTemplet;

    return UpdateEnvLicense(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrEnvLicense::DeleteExecute(UINT32 nID)
{
	return DeleteEnvLicense(nID);
}
//---------------------------------------------------------------------------






