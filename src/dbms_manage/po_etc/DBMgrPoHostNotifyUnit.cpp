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



#include "stdafx.h"
#include "com_struct.h"
#include "DBMgrPoHostNotifyUnit.h"

//---------------------------------------------------------------------------

CDBMgrPoHostNotifyUnit*		t_DBMgrPoHostNotifyUnit;

//---------------------------------------------------------------------------

CDBMgrPoHostNotifyUnit::CDBMgrPoHostNotifyUnit()
{
	m_strDBTName = "po_host_notify_unit";
}
//---------------------------------------------------------------------------

CDBMgrPoHostNotifyUnit::~CDBMgrPoHostNotifyUnit()
{
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoHostNotifyUnit::SetInitalize()
{
    {
    	
	}
	//WriteLogN("current file dbms : [po_host_clear_unit][%d]", m_nDBSVer);
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoHostNotifyUnit::LoadDB(TListDBPoHostNotifyUnit& tDBPoHostNotifyUnitList)
{
	TMapStr tStrMap;
    UINT32 nReadCnt = 0;
    DB_PO_HOST_NOTIFY_UNIT dphnu;

    INT32 nIndex = 0;

	m_strQuery = SPrintf(DBMS_POLICY_QUERY_HDR_SELECT
		", sch_time, pos_type, show_size, show_pos, show_time, msg_fmt_type, msg_info"
		" FROM po_host_notify_unit WHERE used_flag=1;");
    if(DBOP_Check(ExecuteQuery(m_strQuery)))		return ERR_DBMS_SELECT_FAIL;

    do
    {
		nIndex = 0;
		DB_PO_HEADER& tDPH = dphnu.tDPH;

		tDPH						= GetDBField_PoHDR(nIndex);

		dphnu.nSchTime				= GetDBField_UInt(nIndex++);
		dphnu.nPosType				= GetDBField_UInt(nIndex++);
		dphnu.nShowSize				= GetDBField_UInt(nIndex++);
		dphnu.nShowPos				= GetDBField_UInt(nIndex++);
		dphnu.nShowTime				= GetDBField_UInt(nIndex++);
		dphnu.nMsgFmtType			= GetDBField_UInt(nIndex++);
		dphnu.strMsgInfo			= GetDBField_String(nIndex++);
		
        tDBPoHostNotifyUnitList.push_back(dphnu);
        if(m_nLoadMaxID < UINT32(tDPH.nID))	m_nLoadMaxID = tDPH.nID;
        nReadCnt++;
    }while(Next());
	m_nLoadNumber = tDBPoHostNotifyUnitList.size();
	WriteLogN("load database : [%s][%u]", m_strDBTName.c_str(), m_nLoadNumber);
    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoHostNotifyUnit::InsertPoHostNotifyUnit(DB_PO_HOST_NOTIFY_UNIT& dphnu)
{
	DB_PO_HEADER& tDPH = dphnu.tDPH;

	m_strQuery = SPrintf("INSERT INTO po_host_notify_unit("
		DBMS_POLICY_QUERY_HDR_INSERT_NAME
		", sch_time, pos_type, show_size, show_pos, show_time, msg_fmt_type, msg_info"
		") VALUES (%s"
		", %u, %u, %u, %u, %u, %u, '%s');",
		GetPoHDRQuery_InsertValue(tDPH).c_str(), 
		dphnu.nSchTime, dphnu.nPosType, 
		dphnu.nShowSize, dphnu.nShowPos, dphnu.nShowTime,
		dphnu.nMsgFmtType, dphnu.strMsgInfo.c_str());


	if(DBOP_Check(ExecuteQuery(m_strQuery)))		return ERR_DBMS_INSERT_FAIL;

	tDPH.nID      = GetLastID();


    return 0;
}
//---------------------------------------------------------------------------

INT32			CDBMgrPoHostNotifyUnit::UpdatePoHostNotifyUnit(DB_PO_HOST_NOTIFY_UNIT& dphnu)
{
	DB_PO_HEADER& tDPH = dphnu.tDPH;

	m_strQuery = SPrintf("UPDATE po_host_notify_unit SET %s"
		", sch_time=%u, pos_type=%u, show_size=%u, show_pos=%u, show_time=%u"
		", msg_fmt_type=%u, msg_info='%s'"
		" WHERE id=%u;",
		GetPoHDRQuery_Update(tDPH).c_str(), 
		dphnu.nSchTime, dphnu.nPosType, 
		dphnu.nShowSize, dphnu.nShowPos, dphnu.nShowTime,
		dphnu.nMsgFmtType, dphnu.strMsgInfo.c_str(),
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

INT32	CDBMgrPoHostNotifyUnit::LoadExecute(PVOID lpTempletList)
{
	TListDBPoHostNotifyUnit* ptDBList = (TListDBPoHostNotifyUnit*)lpTempletList;

    return LoadDB(*ptDBList);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoHostNotifyUnit::InsertExecute(PVOID lpTemplet)
{
	PDB_PO_HOST_NOTIFY_UNIT pd_t = (PDB_PO_HOST_NOTIFY_UNIT)lpTemplet;

    return InsertPoHostNotifyUnit(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoHostNotifyUnit::UpdateExecute(PVOID lpTemplet)
{
	PDB_PO_HOST_NOTIFY_UNIT pd_t = (PDB_PO_HOST_NOTIFY_UNIT)lpTemplet;

    return UpdatePoHostNotifyUnit(*pd_t);
}
//---------------------------------------------------------------------------

INT32	CDBMgrPoHostNotifyUnit::DeleteExecute(UINT32 nID)
{
	return CDBMgrBase::DeleteExecute(nID);
}
//---------------------------------------------------------------------------






