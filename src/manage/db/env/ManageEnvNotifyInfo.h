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

#ifndef ManageEnvNotifyInfoH
#define ManageEnvNotifyInfoH
//---------------------------------------------------------------------------

class CManageEnvNotifyInfo : public CManagePoBase<DB_ENV_NOTIFY_INFO>
{
public:
	INT32					LoadDBMS();

public:
	INT32					InitHash();
	String					GetHash();
	INT32					GetHash(UINT32 nID, String& strOrgValue);

public:
	INT32					AddEnvNotifyInfo(DB_ENV_NOTIFY_INFO&	deni);
    INT32					EditEnvNotifyInfo(DB_ENV_NOTIFY_INFO&	deni);
	INT32					DelEnvNotifyInfo(UINT32 nID);
	INT32					ApplyEnvNotifyInfo(DB_ENV_NOTIFY_INFO&	deni);

public:
	void					AddEnvNotifyInfoNotiTime(UINT32 nPos, UINT32 nID, UINT32 nNotifyID, UINT32 nTimeStamp);
	INT32					GetEnvNotifyInfoNotiTime(UINT32 nPos, UINT32 nID, UINT32 nNotifyID);

public:
	String					GetName(UINT32 nID);    

public:
	INT32					SetPkt(MemToken& SendToken);
	INT32					SetPkt(UINT32 nID, MemToken& SendToken);
	INT32					SetPkt(PDB_ENV_NOTIFY_INFO pdeni, MemToken& SendToken);
	INT32					GetPkt(MemToken& RecvToken, DB_ENV_NOTIFY_INFO& deni);

	INT32					SetPkt_Link(MemToken& SendToken);
	INT32					SetPkt_Link(PDB_ENV_NOTIFY_INFO pdeni, MemToken& SendToken);


public:
	INT32					IsExcludeNotifySchdule(UINT32 nPolType, UINT32 nPoUnitID = 0);
	INT32					GetIDLIstByNotifyPolType(UINT32 nNotifyPolType, TListID& tIDList);

public:
	CManageEnvNotifyInfo();
    ~CManageEnvNotifyInfo();

};

extern CManageEnvNotifyInfo*	t_ManageEnvNotifyInfo;

#endif
