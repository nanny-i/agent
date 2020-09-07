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

#ifndef ManageEnvLogH
#define ManageEnvLogH
//---------------------------------------------------------------------------

class CManageEnvLog : public CManagePoBase<DB_ENV_LOG>
{
public:
	INT32					LoadDBMS();

public:
	INT32					InitHash();
	String					GetHash();

public:
	INT32					AddEnvLog(DB_ENV_LOG&	dele);
    INT32					EditEnvLog(DB_ENV_LOG&	dele);
	INT32					DelEnvLog(UINT32 nID);
	INT32					ApplyEnvLog(DB_ENV_LOG&	dele);

public:
	String					GetName(UINT32 nID);   

public:
	UINT32					GetLogValue(TMapID& tValueMap, UINT32 nIdx);

public:
	INT32					IsRecordLogEvt(PDB_LOG_EVENT pdle, DB_ENV_LOG_UNIT& deleu);
	INT32					IsRecordLogDoc(PDB_LOG_DOC pdld, DB_ENV_LOG_UNIT& deleu);
	INT32					IsRecordLogSecu(PDB_LOG_SECU pdls, DB_ENV_LOG_UNIT& deleu);
	INT32					IsRecordLogDeployFile(PDB_LOG_DEPLOY_FILE pdldf, DB_ENV_LOG_UNIT& deleu);
	INT32					IsRecordLogPatch(PDB_LOG_PATCH pdlp, DB_ENV_LOG_UNIT& deleu);

public:
	INT32					SetPkt(MemToken& SendToken);
	INT32					SetPkt(UINT32 nID, MemToken& SendToken);
	INT32					SetPkt(PDB_ENV_LOG pdele, MemToken& SendToken);
	INT32					GetPkt(MemToken& RecvToken, DB_ENV_LOG& dele);

public:
	CManageEnvLog();
    ~CManageEnvLog();

};

extern CManageEnvLog*	t_ManageEnvLog;

#endif
