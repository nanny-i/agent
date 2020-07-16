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

#ifndef LogicUserH
#define LogicUserH
//---------------------------------------------------------------------------

class CLogicUser	: public CLogicBase
{
private:	
	INT32		AnalyzePkt_FromLink_Ext_Auth();
	INT32		AnalyzePkt_FromLink_Ext_End();

	INT32		AnalyzePkt_FromLink_Ext_ChgPW();

public:
	INT32		AnalyzePkt_FromLink_User(PPKT_DATA pkt_data);

public:
	void		SendPkt_Auth(UINT32 nRtn, DB_USER& du);
	void		SendPkt_Logout(UINT32 nRtn);
	
	void		SendPkt_UserChgPW(UINT32 nRtn, DB_USER& du);

public:
	CLogicUser();
    ~CLogicUser();
};

extern CLogicUser*		t_LogicUser;

#endif
