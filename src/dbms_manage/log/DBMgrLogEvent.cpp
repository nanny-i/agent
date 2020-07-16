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
#include "DBMgrLogEvent.h"

//---------------------------------------------------------------------------

CDBMgrLogEvent*		t_DBMgrLogEvent;

//---------------------------------------------------------------------------

CDBMgrLogEvent::CDBMgrLogEvent()
{
	m_strDBTName = "log_event";
}
//---------------------------------------------------------------------------

CDBMgrLogEvent::~CDBMgrLogEvent()
{
}
//---------------------------------------------------------------------------

INT32			CDBMgrLogEvent::SetInitalize()
{
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrLogEvent::LoadDB(TListDBLogEvent& tDBLogEventList)
{
    UINT32 nReadCnt = 0;
    DB_LOG_EVENT dle;

    INT32 nIndex = 0;

	m_strQuery = SPrintf("SELECT id, reg_date, evt_time, evt_ecode, "
						"notify_type, notify_id, "
						"subject_type, subject_id, subject_info, "
						"target_type, target_id, target_info, "
						"object_type, object_code, object_id, object_info, "
						"operation_type, evt_descr "
						"FROM log_event WHERE used_flag=1;");
    if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_SELECT_FAIL;

    do
    {
    	nIndex = 0;

        dle.nID						= GetDBField_Int(nIndex++);
		dle.nRegDate				= GetDBField_Int(nIndex++);
		dle.nEvtTime				= GetDBField_Int(nIndex++);
		dle.nEvtErrCode				= GetDBField_Int(nIndex++);

		dle.nNotifyType				= GetDBField_Int(nIndex++);
		dle.nNotifyID				= GetDBField_Int(nIndex++);

		dle.nSubjectType			= GetDBField_Int(nIndex++);
		dle.nSubjectID				= GetDBField_Int(nIndex++);
		dle.strSubjectInfo			= GetDBField_String(nIndex++);

		dle.nTargetType				= GetDBField_Int(nIndex++);
		dle.nTargetID				= GetDBField_Int(nIndex++);
		dle.strTargetInfo			= GetDBField_String(nIndex++);

		dle.nObjectType				= GetDBField_Int(nIndex++);
		dle.nObjectCode				= GetDBField_Int(nIndex++);
        dle.nObjectID				= GetDBField_Int(nIndex++);
        dle.strObjectInfo			= GetDBField_String(nIndex++);

		dle.nOperationType			= GetDBField_Int(nIndex++);
		dle.strEventDescr			= GetDBField_String(nIndex++);

        tDBLogEventList.push_back(dle);
        if(m_nLoadMaxID < UINT32(dle.nID))
			m_nLoadMaxID = dle.nID;
        nReadCnt++;
    }while(Next());
	m_nLoadNumber = (UINT32)tDBLogEventList.size();
	WriteLogN("load database : [%s][%u]", m_strDBTName.c_str(), m_nLoadNumber);
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrLogEvent::InsertLogEvent(DB_LOG_EVENT& dle)
{
	m_strQuery = SPrintf("INSERT INTO log_event(used_flag, reg_date, evt_time, evt_ecode, "
									"notify_type, notify_id, "
									"subject_type, subject_id, subject_info, "
									"target_type, target_id, target_info, "
									"object_type, object_code, object_id, object_info, "
									"operation_type, evt_descr)"
    								"VALUES"
									"(%u, %u, %u, %u, "
									"%u, %u, "
									"%u, %u, '%s', "
									"%u, %u, '%s', "
									"%u, %u, %u, '%s', "
									"%u, '%s');",
									dle.nUsedFlag, dle.nRegDate, dle.nEvtTime, dle.nEvtErrCode,
									dle.nNotifyType, dle.nNotifyID, 
									dle.nSubjectType, dle.nSubjectID, dle.strSubjectInfo.c_str(), 
									dle.nTargetType, dle.nTargetID, dle.strTargetInfo.c_str(), 
									dle.nObjectType, dle.nObjectCode, dle.nObjectID, dle.strObjectInfo.c_str(), 
									dle.nOperationType, dle.strEventDescr.c_str());

	if(DBOP_Check(ExecuteQuery(m_strQuery)))
		return ERR_DBMS_INSERT_FAIL;

    dle.nID      = GetLastID();

    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrLogEvent::UpdateLogEvent(DB_LOG_EVENT& dle)
{	
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrLogEvent::DeleteLogEvent(UINT32 nID)
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

INT32	CDBMgrLogEvent::LoadExecute(PVOID lpTempletList)
{
	TListDBLogEvent* ptDBList = (TListDBLogEvent*)lpTempletList;

    return LoadDB(*ptDBList);
}
//---------------------------------------------------------------------------

INT32	CDBMgrLogEvent::InsertExecute(PVOID lpTemplet)
{
	PDB_LOG_EVENT pd_t = (PDB_LOG_EVENT)lpTemplet;

    return InsertLogEvent(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrLogEvent::UpdateExecute(PVOID lpTemplet)
{
	PDB_LOG_EVENT pd_t = (PDB_LOG_EVENT)lpTemplet;

    return UpdateLogEvent(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrLogEvent::DeleteExecute(UINT32 nID)
{
	return DeleteLogEvent(nID);
}
//---------------------------------------------------------------------------






