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

#ifndef ManageEnvLogUnitH
#define ManageEnvLogUnitH
//---------------------------------------------------------------------------

class CManageEnvLogUnit : public CManagePoBase<DB_ENV_LOG_UNIT>
{
public:
	INT32					LoadDBMS();

public:
	INT32					InitHash();
	String					GetHash();

public:
	INT32					AddEnvLogUnit(DB_ENV_LOG_UNIT&	deleu);
    INT32					EditEnvLogUnit(DB_ENV_LOG_UNIT&	deleu);
    INT32					DelEnvLogUnit(UINT32 nID);
	INT32					ApplyEnvLogUnit(DB_ENV_LOG_UNIT&	deleu);

public:
	String					GetName(UINT32 nID);   

public:
	PDB_ENV_LOG_UNIT	FindRecordLogEvtUnit(PDB_LOG_EVENT pdle);
	PDB_ENV_LOG_UNIT	FindRecordLogStatusUnit(PDB_LOG_STATUS pdls);
	PDB_ENV_LOG_UNIT	FindRecordLogDocUnit(PDB_LOG_DOC pdld);
	PDB_ENV_LOG_UNIT	FindRecordLogSecuUnit(PDB_LOG_SECU pdls);
	PDB_ENV_LOG_UNIT	FindRecordLogDeployFileUnit(PDB_LOG_DEPLOY_FILE pdldf);

public:
	INT32					SetPkt(MemToken& SendToken);
	INT32					SetPkt(UINT32 nID, MemToken& SendToken);
	INT32					SetPkt(PDB_ENV_LOG_UNIT pdeleu, MemToken& SendToken);
	INT32					GetPkt(MemToken& RecvToken, DB_ENV_LOG_UNIT& deleu);

public:
	CManageEnvLogUnit();
    ~CManageEnvLogUnit();

};

extern CManageEnvLogUnit*	t_ManageEnvLogUnit;

#endif
