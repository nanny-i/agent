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
#include "LogicLogEvent.h"

//---------------------------------------------------------------------------

CLogicLogEvent*		t_LogicLogEvent = NULL;

//---------------------------------------------------------------------------

CLogicLogEvent::CLogicLogEvent()
{
	t_ManageLogEvent	= new CManageLogEvent();

    t_ManageLogEvent->LoadDBMS();

	m_strLogicName = "logic log event";
}
//---------------------------------------------------------------------------

CLogicLogEvent::~CLogicLogEvent()
{
	SAFE_DELETE(t_ManageLogEvent);
}
//---------------------------------------------------------------------------

void		CLogicLogEvent::AnalyzePkt_LogEvent(PPKT_DATA pkt_data)
{
	InitBaseMember(pkt_data);
	switch(m_nPktCode)
    {
        default:
        {
        	WriteLogE("[%s] not define pkt code from console : [%d][%d]", m_strLogicName.c_str(), m_nPktType, m_nPktCode);
            break;
        }
    }
	InitBaseMember();
    return;
}
//---------------------------------------------------------------------------

void		CLogicLogEvent::InitDLEALL(UINT32 nOpType, UINT32 nSType, UINT32 nSID, UINT32 nTType, UINT32 nTID, UINT32 nOType, UINT32 nOCode, UINT32 nOID, String strOInfo, String strDesc)
{
	CLogicBase::InitDLEALL(nOpType, nSType, nSID, nTType, nTID, nOType, nOCode, nOID, strOInfo, strDesc);
	return;
}
//---------------------------------------------------------------------------

void		CLogicLogEvent::SetLogEvent()
{
	return SetLogEvent(m_tDLE);
}
//---------------------------------------------------------------------------

void		CLogicLogEvent::SetLogEvent(TListDBLogEvent& tDELNList)
{
	TListDBLogEventItor begin, end;
	begin = tDELNList.begin();	end = tDELNList.end();
	for(begin; begin != end; begin++)
	{
		SetLogEvent(*begin);
	}
	return;
}
//---------------------------------------------------------------------------

void		CLogicLogEvent::SetLogEvent(DB_LOG_EVENT& dle)
{
	{
		WriteLogN("[logic log event] remain evt log to file : op[%d]:s[%d:%d][%s]:t[%d:%d][%s]:o[%d:%d][%d:%s]:[%s]", 
																			dle.nOperationType, 
																			dle.nSubjectType, dle.nSubjectID, dle.strSubjectInfo.c_str(), 
																			dle.nTargetType, dle.nTargetID, dle.strTargetInfo.c_str(), 
																			dle.nObjectType, dle.nObjectCode, dle.nObjectID, dle.strObjectInfo.c_str(),
																			dle.strEventDescr.c_str());
	}


	
	{
		t_ManageLogEvent->AddLogEvent(dle);
	}

	{	
		SendToken.Set(1024);
		SendToken.TokenAdd_32(ERR_SUCCESS);
		t_ManageLogEvent->SetPkt(&dle, SendToken);
		SendData_Link(G_TYPE_LOG_EVENT, G_CODE_COMMON_ADD, SendToken);
		SendToken.Clear();
	}
	return;
}
//---------------------------------------------------------------------------



