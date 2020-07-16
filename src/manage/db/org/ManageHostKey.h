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

#ifndef ManageHostKeyH
#define ManageHostKeyH
//---------------------------------------------------------------------------

class CManageHostKey : public CManageBase<DB_HOST_KEY>
{
public:
	INT32			LoadDBMS();

public:
	String			GetHash();

public:
	INT32			AddHostKey(DB_HOST_KEY& data);
    INT32			EditHostKey(DB_HOST_KEY& data);
    INT32			DelHostKey(UINT32 nID);

public:
	String			GetEncBkKey(String strDecKey);
	String			GetDecBkKey(String strEncKey = "");
	String			GetDecRcKey(String strEncKey = "");
	INT32			ClearHostKey_RcKey();

public:
	String			GetEncCrKey(String strDecKey);
	String			GetDecCrKey(String strEncKey = "");

public:
	INT32			GetPkt(MemToken& RecvToken, DB_HOST_KEY& data, UINT32 nPktType);
	INT32			SetPkt(MemToken& SendToken);
    INT32			SetPkt(PDB_HOST_KEY pdata, MemToken& SendToken);

public:
	CManageHostKey();
    ~CManageHostKey();

};

extern CManageHostKey*	t_ManageHostKey;

#endif
