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

#ifndef LogicLogEventH
#define LogicLogEventH
//---------------------------------------------------------------------------

class CLogicLogEvent	: CLogicBase
{          
private:

public:
	void		AnalyzePkt_LogEvent(PPKT_DATA pkt_data);

public:
	void		InitDLEALL(UINT32 nOpType, UINT32 nSType, UINT32 nSID, UINT32 nTType, UINT32 nTID, UINT32 nOType, UINT32 nOCode, UINT32 nOID, String strOInfo, String strDesc = "");
	void		SetLogEvent();
	void		SetLogEvent(DB_LOG_EVENT& dle);
	void		SetLogEvent(TListDBLogEvent& tDELNList);


public:
	CLogicLogEvent();
    ~CLogicLogEvent();
};

extern CLogicLogEvent*		t_LogicLogEvent;

#endif
