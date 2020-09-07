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

#ifndef ManageLogSecuH
#define ManageLogSecuH
//---------------------------------------------------------------------------

class CManageLogSecu : public CManageBase<DB_LOG_SECU>
{
public:
	INT32		LoadDBMS();

public:
	INT32					AddLogSecu(DB_LOG_SECU&	dls);
    INT32					EditLogSecu(DB_LOG_SECU&	dls);
    INT32					DelLogSecu(UINT32 nID);

public:
	INT32					SetPktSync(TListPVOID& tIDList);

public:
	INT32					SetPkt(MemToken& SendToken);
	INT32					SetPkt(PDB_LOG_SECU pdls, MemToken& SendToken);
	INT32					GetPkt(MemToken& RecvToken, DB_LOG_SECU& dls);

	INT32					SetPkt_Link(MemToken& SendToken);

public:
	CManageLogSecu();
    ~CManageLogSecu();

};

extern CManageLogSecu*	t_ManageLogSecu;

#endif
