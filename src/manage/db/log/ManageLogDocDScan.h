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

#pragma once

class CManageLogDocDScan : public CManageBase<DB_LOG_DOC_DSCAN>
{

public:
	INT32		LoadDBMS();

public:
	INT32		AddLogDocDScan(DB_LOG_DOC_DSCAN& dldd);
	INT32		EditLogDocDScan(DB_LOG_DOC_DSCAN& dldd);
	INT32		ClearItem();

public:
	INT32		SetPkt(PDB_LOG_DOC_DSCAN pdldd, MemToken& SendToken);
	INT32		GetPkt(MemToken& RecvToken, DB_LOG_DOC_DSCAN& dldd);

public:
	INT32		SetPkt_Link(MemToken& SendToken);

public:
	CManageLogDocDScan(void);
	~CManageLogDocDScan(void);
};

extern CManageLogDocDScan*	t_ManageLogDocDScan;
