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

#ifndef LogicEnvNotifyInfoH
#define LogicEnvNotifyInfoH
//---------------------------------------------------------------------------

class CLogicEnvNotifyInfo	: public CLogicBase
{
private:
	INT32		AnalyzePkt_FromLink_Ext();

public:
	INT32		AnalyzePkt_FromLink_Ext_Notify_Sch_info();

public:
	void		SendPkt_Notify_Sch_info(MEM_ENV_NOTIFY_INFO_SCH& menis);


public:
	CLogicEnvNotifyInfo();
    ~CLogicEnvNotifyInfo();
};

extern CLogicEnvNotifyInfo*		t_LogicEnvNotifyInfo;

#endif
