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

#ifndef LogicInitLinkH
#define LogicInitLinkH
//---------------------------------------------------------------------------

class CLogicInitLink	: CLogicBase
{

public:
	void		AnalyzePkt_Init(PPKT_DATA pkt_data);

private:
	void		AnalyzePkt_Init_Request();
	void		AnalyzePkt_Init_Last();

private:
	void		SendPkt_Init_Common();

	void		SendPkt_Init_Admin();
	void		SendPkt_Init_Host();
	void		SendPkt_Init_Group();
	void		SendPkt_Init_User();
	void		SendPkt_Init_Env();
	void		SendPkt_Init_Ptn();
	void		SendPkt_Init_LocalEnv();
	void		SendPkt_Init_Policy();
	void		SendPkt_Init_Data();

private:
	void		SendPkt_Init_Policy_SA();
	void		SendPkt_Init_Policy_AC();
	void		SendPkt_Init_Policy_FA();
	void		SendPkt_Init_Policy_FE();
	void		SendPkt_Init_Policy_IN();
	void		SendPkt_Init_Policy_IN_VULN();
	void		SendPkt_Init_Policy_IN_RS();
	void		SendPkt_Init_Policy_IN_DEVO();
	void		SendPkt_Init_Policy_PM();

    
public:
	CLogicInitLink();
    ~CLogicInitLink();
};

extern CLogicInitLink*		t_LogicInitLink;

#endif
