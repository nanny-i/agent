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

#ifndef ManageLogRsBkH
#define ManageLogRsBkH
//---------------------------------------------------------------------------

class CManageLogRsBk : public CManageBase<DB_LOG_RS_BK>
{

private:
	UINT64					m_nTBkSize;

public:
	INT32					LoadDBMS();

public:
	INT32					AddLogRsBk(DB_LOG_RS_BK&	data);
    INT32					EditLogRsBk(DB_LOG_RS_BK&	data);
    INT32					DelLogRsBk(UINT32 nID);
	INT32					ApplyLogRsBk(DB_LOG_RS_BK&	data);

public:
	INT32					IsExistLogRsBk(DB_LOG_RS_BK&	data);
	PDB_LOG_RS_BK			GetExistLogRsBk(DB_LOG_RS_BK&	data);

	INT32					GetOldRsBk(PDB_LOG_RS_BK pdata, TListID& tIDList, UINT32 nRemainNum = 5);
	INT32					GetOldRsBk(String strKey, TListID& tIDList, UINT32 nRemainNum = 5);
	INT32					GetFirstRsBk(String strKey, TListID& tIDList, UINT32 nRemainNum = 1);
	UINT64					GetTBkSize()	{	return m_nTBkSize;	};

public:
	INT32					GetInitPktList(UINT64 nKey, TListDBLogRsBk& tInitPktList, UINT32 nOnceNum);
	INT32					SetPkt(MemToken& SendToken, UINT64 nKey, UINT32 nOnceNum);
	
public:
	INT32					SetPkt(MemToken& SendToken);
	INT32					SetPkt(PDB_LOG_RS_BK pdata, MemToken& SendToken);
	INT32					GetPkt(MemToken& RecvToken, DB_LOG_RS_BK& data);

public:
	CManageLogRsBk();
    ~CManageLogRsBk();

};

extern CManageLogRsBk*	t_ManageLogRsBk;

#endif
