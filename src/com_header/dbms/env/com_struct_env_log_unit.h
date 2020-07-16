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

#ifndef DB_ENV_LOG_UNIT_H_348683B5_F316_4a4d_842D_63E68B189A5D
#define DB_ENV_LOG_UNIT_H_348683B5_F316_4a4d_842D_63E68B189A5D

typedef struct _db_env_log_event_unit
{
	_db_env_log_event_unit()
	{
		nEvtType				= 0;
		nEvtCode				= 0;
		nEvtErrCode				= 0;
		nSubjectType 			= 0;
		nTargetType 			= 0;	
		nObjectType				= 0;
		nObjectCode				= 0;
		nOperationType			= 0;

		nRecordMode				= 0;
	}

	DB_PO_HEADER		tDPH;

	UINT32				nEvtType;
	UINT32				nEvtCode;
	UINT32				nEvtErrCode;

	UINT32				nSubjectType;
	String				strSubjectInfo;

	UINT32				nTargetType;
	String				strTargetInfo;

	UINT32				nObjectType;
	UINT32				nObjectCode;
	String				strObjectInfo;

	UINT32				nOperationType;
	String				strEvtDescr;

	UINT32				nRecordMode;
	String				strSMSValue;

}DB_ENV_LOG_UNIT, *PDB_ENV_LOG_UNIT;

typedef list<DB_ENV_LOG_UNIT>				TListDBEnvLogUnit;
typedef TListDBEnvLogUnit::iterator		TListDBEnvLogUnitItor;

typedef map<UINT32, DB_ENV_LOG_UNIT>		TMapDBEnvLogUnit;
typedef TMapDBEnvLogUnit::iterator			TMapDBEnvLogUnitItor;

#endif //DB_ENV_LOG_UNIT_H_348683B5_F316_4a4d_842D_63E68B189A5D



