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

#ifndef ManageWinSessionH
#define ManageWinSessionH
//---------------------------------------------------------------------------

class CManageWinSession : public CManageBase<MEM_WIN_SESSION>
{
private:
	TListID				m_tSessionChangeList;
	TListID				m_tSessionChgHKList;

public:
	INT32				InitWinSession();
	INT32				AddWinSession(UINT32 nID, UINT32 nAddEvt = 1, UINT32 nLoginTime = 0);
	INT32				DelWinSession(UINT32 nID);
	INT32				EdistrUserName(MEM_WIN_SESSION& tMWS);

public:
	String				GetLogonUserName();

public:
	INT32				IsWinSessionChange();
	INT32				IsWinSessionChgHK();
	INT32				AddWinSessionChange(UINT32 nMode);

public:
	CManageWinSession();
    ~CManageWinSession();

};

extern CManageWinSession	t_ManageWinSession;

#endif
