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

#ifndef LogicMgrPoInPtnExTrustH
#define LogicMgrPoInPtnExTrustH
//---------------------------------------------------------------------------

class CLogicMgrPoInPtnExTrust	: public CLogicBase
{
private:
	INT32		AnalyzePkt_FromMgr_Ext();
	INT32		AnalyzePkt_FromMgr_Add_Ext();

public:
	INT32		CheckPtnLifeCycle();
//	INT32		LoadWEngPtn(CASIWEngDLLUtil* pWEDLLUtil, String strFileName, String strFileHash);

public:
	void		SetPoInPtnExTrsut(DB_PO_IN_PTN_EX_TRUST& data);

public:
	CLogicMgrPoInPtnExTrust();
    ~CLogicMgrPoInPtnExTrust();
};

extern CLogicMgrPoInPtnExTrust*		t_LogicMgrPoInPtnExTrust;

#endif
