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
#include "DBMgrLogStatus.h"

//---------------------------------------------------------------------------

CDBMgrLogStatus*		t_DBMgrLogStatus;

//---------------------------------------------------------------------------

CDBMgrLogStatus::CDBMgrLogStatus()
{
	m_strDBTName = "log_status";
}
//---------------------------------------------------------------------------

CDBMgrLogStatus::~CDBMgrLogStatus()
{
}
//---------------------------------------------------------------------------

INT32			CDBMgrLogStatus::SetInitalize()
{
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrLogStatus::LoadDB(TListDBLogStatus& tDBLogStatusList)
{
    UINT32 nReadCnt = 0;
    DB_LOG_STATUS dls;

    INT32 nIndex = 0;

	m_strQuery = SPrintf("SELECT id, reg_date, evt_time, evt_ecode, skip_target, "
						"notify_type, notify_id, "
						"host_id, reg_svr_id, sync_svr_step, "
						"subject_type, subject_id, subject_info, "
						"target_type, target_id, target_info, "
						"object_type, object_code, object_id, object_info, "
						"operation_type, evt_descr, ext_option "
						"FROM log_status WHERE used_flag=1;");
    if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_SELECT_FAIL;

    do
    {
    	nIndex = 0;

        dls.nID					= GetDBField_Int(nIndex++);
		dls.nRegDate			= GetDBField_Int(nIndex++);
		dls.nEvtTime			= GetDBField_Int(nIndex++);
		dls.nEvtErrCode			= GetDBField_Int(nIndex++);
		dls.nSkipTarget			= GetDBField_Int(nIndex++);

		dls.nNotifyType			= GetDBField_Int(nIndex++);
		dls.nNotifyID			= GetDBField_Int(nIndex++);

		dls.nHostID				= GetDBField_Int(nIndex++);
		dls.nRegSvrID			= GetDBField_Int(nIndex++);
		dls.nSyncSvrStep		= GetDBField_Int(nIndex++);

		dls.nSubjectType		= GetDBField_Int(nIndex++);
		dls.nSubjectID			= GetDBField_Int(nIndex++);
		dls.strSubjectInfo		= GetDBField_String(nIndex++);

		dls.nTargetType			= GetDBField_Int(nIndex++);
		dls.nTargetID			= GetDBField_Int(nIndex++);
		dls.strTargetInfo		= GetDBField_String(nIndex++);

		dls.nObjectType			= GetDBField_Int(nIndex++);
		dls.nObjectCode			= GetDBField_Int(nIndex++);
        dls.nObjectID			= GetDBField_Int(nIndex++);
        dls.strObjectInfo		= GetDBField_String(nIndex++);

		dls.nOperationType		= GetDBField_Int(nIndex++);

		{
			m_strValue			= GetDBField_String(nIndex++);
			StrToMapID_Str(m_strValue, dls.tDescIDStrMap);
		}

		dls.nExtOption			= GetDBField_Int(nIndex++);

        tDBLogStatusList.push_back(dls);
        if(m_nLoadMaxID < UINT32(dls.nID))
			m_nLoadMaxID = dls.nID;
        nReadCnt++;
    }while(Next());
	m_nLoadNumber = (UINT32)tDBLogStatusList.size();
	WriteLogN("load database : [%s][%u]", m_strDBTName.c_str(), m_nLoadNumber);
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrLogStatus::InsertLogStatus(DB_LOG_STATUS& dls)
{
	String strDesc;
	strDesc = MapID_StrToStr(dls.tDescIDStrMap);

	m_strQuery = SPrintf("INSERT INTO log_status (used_flag, reg_date, evt_time, evt_ecode, skip_target, "
									"notify_type, notify_id, "
									"host_id, reg_svr_id, sync_svr_step, "
									"subject_type, subject_id, subject_info, "
									"target_type, target_id, target_info, "
									"object_type, object_code, object_id, object_info, "
									"operation_type, evt_descr, ext_option)"
    								"VALUES"
									"(%u, %u, %u, %u, %u, "
									"%u, %u, "
									"%u, %u, %u,"
									"%u, %u, '%s', "
									"%u, %u, '%s', "
									"%u, %u, %u, '%s', "
									"%u, '%s', %u);",
									dls.nUsedFlag,	dls.nRegDate, dls.nEvtTime, dls.nEvtErrCode, dls.nSkipTarget,
									dls.nNotifyType, dls.nNotifyID, 
									dls.nHostID, dls.nRegSvrID, dls.nSyncSvrStep,
									dls.nSubjectType, dls.nSubjectID, dls.strSubjectInfo.c_str(), 
									dls.nTargetType, dls.nTargetID, dls.strTargetInfo.c_str(), 
									dls.nObjectType, dls.nObjectCode, dls.nObjectID, dls.strObjectInfo.c_str(), 
									dls.nOperationType, strDesc.c_str(), dls.nExtOption);

	if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_INSERT_FAIL;

    dls.nID      = GetLastID();

    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrLogStatus::UpdateLogStatus(DB_LOG_STATUS& dls)
{	
	String strDesc;
	strDesc = MapID_StrToStr(dls.tDescIDStrMap);

	m_strQuery = SPrintf("UPDATE log_status SET reg_date=%u, evt_time=%u, evt_ecode=%u, skip_target=%u, "
		"notify_type=%u, notify_id=%u, "
		"host_id=%u, reg_svr_id=%u, sync_svr_step=%u, "
		"subject_type=%u, subject_id=%u, subject_info=%u, "
		"target_type=%u, target_id=%u, target_info='%s', "
		"object_type=%u, object_code=%u, object_id=%u, object_info='%s', "
		"operation_type=%u, evt_descr='%s', ext_option=%u "
		"WHERE id=%u;",
		dls.nRegDate, dls.nEvtTime, dls.nEvtErrCode, dls.nSkipTarget,
		dls.nNotifyType, dls.nNotifyID, 
		dls.nHostID, dls.nRegSvrID, dls.nSyncSvrStep,
		dls.nSubjectType, dls.nSubjectID, dls.strSubjectInfo.c_str(), 
		dls.nTargetType, dls.nTargetID, dls.strTargetInfo.c_str(), 
		dls.nObjectType, dls.nObjectCode, dls.nObjectID, dls.strObjectInfo.c_str(), 
		dls.nOperationType, strDesc.c_str(), dls.nExtOption,
		dls.nID);

	if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_UPDATE_FAIL;
	return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrLogStatus::DeleteLogStatus(UINT32 nID)
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

INT32	CDBMgrLogStatus::LoadExecute(PVOID lpTempletList)
{
	TListDBLogStatus* ptDBList = (TListDBLogStatus*)lpTempletList;

    return LoadDB(*ptDBList);
}
//---------------------------------------------------------------------------

INT32	CDBMgrLogStatus::InsertExecute(PVOID lpTemplet)
{
	PDB_LOG_STATUS pd_t = (PDB_LOG_STATUS)lpTemplet;

    return InsertLogStatus(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrLogStatus::UpdateExecute(PVOID lpTemplet)
{
	PDB_LOG_STATUS pd_t = (PDB_LOG_STATUS)lpTemplet;

    return UpdateLogStatus(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrLogStatus::DeleteExecute(UINT32 nID)
{
	return DeleteLogStatus(nID);
}
//---------------------------------------------------------------------------






