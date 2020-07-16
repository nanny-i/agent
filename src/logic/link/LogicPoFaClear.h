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

#ifndef LogicPoFaClearH
#define LogicPoFaClearH
//---------------------------------------------------------------------------

class CLogicPoFaClear	: public CLogicBase
{
private:
	INT32		AnalyzePkt_FromLink_Ext();
	INT32		AnalyzePkt_FromLink_Ext_Init();

	INT32		AnalyzePkt_FromLink_Del_Ext();

public:
	void		SendPkt_Init(UINT32 nID, UINT32 nLastChkTime);
	void		SendPkt_Find(PDB_LOG_DOC pdld);
	void		SendPkt_Progress(PMEM_FIND_ORDER_INFO pMFOI);
	void		SendPkt_End(MEM_FIND_ORDER_INFO& tMFOI);

	void		SendPkt_Del_Last(MEM_FIND_ORDER_INFO& tMFOI);
	void		SendPkt_Del_Last(UINT32 nPolicyType, UINT32 nOpType, UINT32 nTotalDelCnt);

public:
	CLogicPoFaClear();
    ~CLogicPoFaClear();
};

extern CLogicPoFaClear*		t_LogicPoFaClear;

#endif
