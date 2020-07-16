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
#include "LogicBase.h"

//---------------------------------------------------------------------------


void	CLogicBase::InitDLEALL(UINT32 nOpType, UINT32 nSType, UINT32 nSID, UINT32 nTType, UINT32 nTID, UINT32 nOType, UINT32 nOCode, UINT32 nOID, String strOInfo, String strDesc)
{
	return InitDLE(EVENT_NOTIFY_TYPE_ALL, 0, nSType, nSID, nTType, nTID, nOType, nOCode, nOID, strOInfo, nOpType, strDesc);
}
//---------------------------------------------------------------------------

void	CLogicBase::InitDLE_PE(UINT32 nOID, String strOInfo, String strDesc)
{
	return InitDLEALL(EVENT_OPERATION_TYPE_EDIT, EVENT_SUBJECT_TYPE_HOST, 0, EVENT_TARGET_TYPE_HOST, 0, m_nEvtObjType, m_nEvtObjCode, nOID, strOInfo, strDesc);
}
//---------------------------------------------------------------------------

void	CLogicBase::InitDLEA_EC()
{	
	InitDLEALL(m_nEvtOpType, m_nEvtSubType, m_nSessionID, m_nEvtTarType, 0, m_nEvtObjType, m_nEvtObjCode, 0, "", "");
	return;
}
//---------------------------------------------------------------------------

void	CLogicBase::SetDLEA_EC(UINT32 nErrCode, INT32 nApplyPkt)
{
	if(nErrCode)	m_nLastErrCode = nErrCode;
	InitDLEA_EC();
	t_LogicLogEvent->SetLogEvent(m_tDLE);

	if(nApplyPkt)
	{
		SendToken.Clear();
		SendToken.TokenAdd_32(nErrCode);
	}
	return;
}
//---------------------------------------------------------------------------

void	CLogicBase::InitDLE(UINT32 nNType, UINT32 nNID, UINT32 nSType, UINT32 nSID, UINT32 nTType, UINT32 nTID, UINT32 nOType, UINT32 nOCode, UINT32 nOID, String strOInfo, UINT32 nOpType, String strDesc, String strSInfo, String strTInfo)
{
	m_tDLE._init();
	String strSubjectName = "";

	m_tDLE.nRegDate			= GetCurrentDateTimeInt();
	m_tDLE.nEvtTime			= GetCurrentDateTimeInt();
	m_tDLE.nEvtErrCode		= m_nLastErrCode;

	m_tDLE.nNotifyType		= nNType;
	m_tDLE.nNotifyID		= nNID;

	m_tDLE.nSubjectType		= nSType;
	m_tDLE.nSubjectID		= nSID;
	m_tDLE.strSubjectInfo	= strSInfo;

	m_tDLE.nTargetType		= nTType;
	m_tDLE.nTargetID		= nTID;
	m_tDLE.strTargetInfo	= strTInfo;

	m_tDLE.nObjectType		= nOType;
	m_tDLE.nObjectCode		= nOCode;
	m_tDLE.nObjectID		= nOID;
	m_tDLE.strObjectInfo	= strOInfo;

	m_tDLE.nOperationType	= nOpType;
	m_tDLE.strEventDescr	= strDesc;

	if(m_tDLE.strSubjectInfo.empty())
	{
		switch(nSType)
		{
			case EVENT_SUBJECT_TYPE_ADMIN:		m_tDLE.strSubjectInfo = "admin";		break;
			case EVENT_SUBJECT_TYPE_GROUP:		m_tDLE.strSubjectInfo = "group";		break;
			case EVENT_SUBJECT_TYPE_HOST:		m_tDLE.strSubjectInfo = "host";			break;
			case EVENT_SUBJECT_TYPE_USER:		m_tDLE.strSubjectInfo = "user";			break;		// USER로 변경
			case EVENT_SUBJECT_TYPE_SVR:		m_tDLE.strSubjectInfo = "system";		break;
		}
	}

	if(m_tDLE.strTargetInfo.empty())
	{
		switch(nTType)
		{
			case EVENT_TARGET_TYPE_ADMIN:		m_tDLE.strTargetInfo = "admin";			break;
			case EVENT_TARGET_TYPE_GROUP:		m_tDLE.strTargetInfo = "group";			break;
			case EVENT_TARGET_TYPE_HOST:		m_tDLE.strTargetInfo = "host";			break;
			case EVENT_TARGET_TYPE_USER:		m_tDLE.strTargetInfo = "user";			break;		// USER로 변경
			case EVENT_TARGET_TYPE_SVR:			m_tDLE.strTargetInfo = "system";		break;
		}
	}

	if(strDesc.empty() == FALSE)	m_tDLE.strEventDescr += SPrintf("%c", CHAR_TOKEN_F);
}
//---------------------------------------------------------------------------

void	CLogicBase::AppendDLEDesc(String strValue)
{
	if(strValue.empty())	return;

	m_tDLE.strEventDescr += strValue;
	m_tDLE.strEventDescr += SPrintf("%c", CHAR_TOKEN_F);
	return;
}
//---------------------------------------------------------------------------

void	CLogicBase::AppendDLEDesc(UINT32 nValue)
{
	String strValue;
	strValue = SPrintf("%u", nValue);

	m_tDLE.strEventDescr += strValue;
	m_tDLE.strEventDescr += SPrintf("%c", CHAR_TOKEN_F);
	return;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void	CLogicBase::InitDLSTALL(UINT32 nOpType, UINT32 nSType, UINT32 nSID, UINT32 nTType, UINT32 nTID, UINT32 nOType, UINT32 nOCode, UINT32 nOID, String strOInfo, UINT32 nKeyDesc, String strValueDesc)
{
	return InitDLST(EVENT_NOTIFY_TYPE_ALL, 0, nSType, nSID, nTType, nTID, nOType, nOCode, nOID, strOInfo, nOpType, nKeyDesc, strValueDesc);
}
//---------------------------------------------------------------------------

void	CLogicBase::InitDLST_PoOp(UINT32 nOID, String strOInfo, UINT32 nOpType, UINT32 nKeyDesc, String strValueDesc)
{
	return InitDLSTALL(nOpType, EVENT_SUBJECT_TYPE_HOST, m_nSessionID, EVENT_TARGET_TYPE_HOST, m_nSessionID, m_nEvtObjType, m_nEvtObjCode, nOID, strOInfo, nKeyDesc, strValueDesc);
}
//---------------------------------------------------------------------------

void	CLogicBase::InitDLST(UINT32 nNType, UINT32 nNID, UINT32 nSType, UINT32 nSID, UINT32 nTType, UINT32 nTID, UINT32 nOType, UINT32 nOCode, UINT32 nOID, String strOInfo, UINT32 nOpType, UINT32 nKeyDesc, String strValueDesc, String strSInfo, String strTInfo)
{
	m_tDLST._init();
	String strSubjectName = "";

	m_tDLST.nRegDate		= 0;
	m_tDLST.nEvtTime		= 0;
	m_tDLST.nEvtErrCode		= m_nLastErrCode;

	m_tDLST.nNotifyType		= nNType;
	m_tDLST.nNotifyID		= nNID;

	m_tDLST.nSyncSvrStep	= 0;

	m_tDLST.nSubjectType	= nSType;
	m_tDLST.nSubjectID		= nSID;
	m_tDLST.strSubjectInfo	= strSInfo;

	m_tDLST.nTargetType		= nTType;
	m_tDLST.nTargetID		= nTID;
	m_tDLST.strTargetInfo	= strTInfo;

	m_tDLST.nObjectType		= nOType;
	m_tDLST.nObjectCode		= nOCode;
	m_tDLST.nObjectID		= nOID;
	m_tDLST.strObjectInfo	= strOInfo;

	m_tDLST.nOperationType	= nOpType;
	AppendDLStDesc(nKeyDesc, strValueDesc);

	if(m_tDLST.strSubjectInfo.empty())
	{
		switch(nSType)
		{
		case EVENT_SUBJECT_TYPE_ADMIN:		m_tDLST.strSubjectInfo = "admin";		break;
		case EVENT_SUBJECT_TYPE_GROUP:		m_tDLST.strSubjectInfo = "group";		break;
		case EVENT_SUBJECT_TYPE_HOST:		m_tDLST.strSubjectInfo = "host";		break;
		case EVENT_SUBJECT_TYPE_USER:		m_tDLST.strSubjectInfo = "user";		break;		// USER로 변경
		case EVENT_SUBJECT_TYPE_SVR:		m_tDLST.strSubjectInfo = "system";		break;
		}
	}

	if(m_tDLST.strTargetInfo.empty())
	{
		switch(nTType)
		{
		case EVENT_TARGET_TYPE_ADMIN:		m_tDLST.strTargetInfo = "admin";		break;
		case EVENT_TARGET_TYPE_GROUP:		m_tDLST.strTargetInfo = "group";		break;
		case EVENT_TARGET_TYPE_HOST:		m_tDLST.strTargetInfo = "host";			break;
		case EVENT_TARGET_TYPE_USER:		m_tDLST.strTargetInfo = "user";			break;		// USER로 변경
		case EVENT_TARGET_TYPE_SVR:			m_tDLST.strTargetInfo = "system";		break;
		}
	}
}
//---------------------------------------------------------------------------

void	CLogicBase::AppendDLStDesc(UINT32 nKey, String strValue)
{



	if(!nKey)	return;

	m_tDLST._set_desc_info(nKey, strValue);
	return;
}
//---------------------------------------------------------------------------

void	CLogicBase::AppendDLStDesc(UINT32 nKey, UINT32 nValue)
{
	if(!nKey)	return;

	String strValue;
	strValue = SPrintf("%u", nValue);

	AppendDLStDesc(nKey, strValue);
	return;
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
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------







