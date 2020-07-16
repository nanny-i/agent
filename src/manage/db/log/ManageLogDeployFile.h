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

#ifndef ManageLogDeployFileH
#define ManageLogDeployFileH
//---------------------------------------------------------------------------

class CManageLogDeployFile : public CManageBase<DB_LOG_DEPLOY_FILE>
{
public:
	INT32		LoadDBMS();

public:
	INT32					AddLogDeployFile(DB_LOG_DEPLOY_FILE&	dldf);
    INT32					EditLogDeployFile(DB_LOG_DEPLOY_FILE&	dldf);
    INT32					DelLogDeployFile(UINT32 nID);

public:
	INT32					IsExistLogDeployFile(DB_LOG_DEPLOY_FILE&	dldf);
	PDB_LOG_DEPLOY_FILE		FindItemByDFInfo(DB_LOG_DEPLOY_FILE&	dldf);

public:
	INT32					SetPkt(MemToken& SendToken);
	INT32					SetPkt(PDB_LOG_DEPLOY_FILE pdldf, MemToken& SendToken);
	INT32					GetPkt(MemToken& RecvToken, DB_LOG_DEPLOY_FILE& dldf);

	INT32					SetPkt_Link(MemToken& SendToken);

public:
	CManageLogDeployFile();
    ~CManageLogDeployFile();

};

extern CManageLogDeployFile*	t_ManageLogDeployFile;

#endif
