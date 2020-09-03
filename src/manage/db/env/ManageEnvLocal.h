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

#ifndef ManageEnvLocalH
#define ManageEnvLocalH
//---------------------------------------------------------------------------

class CManageEnvLocal : public CManageBase<DB_ENV_LOCAL>
{
public:
	INT32		LoadDBMS();

public:
	INT32					AddEnvLocal(DB_ENV_LOCAL&	data);
    INT32					EditEnvLocal(DB_ENV_LOCAL&	data);
    INT32					DelEnvLocal(UINT32 nID);

public:
	PDB_ENV_LOCAL			GetEnvLocal(UINT32 nChkType, UINT32 nChkCode);

public:
	void					SetEnvLocalNumber(UINT32 nChkType, UINT32 nChkCode, UINT32 nKey, UINT32 nValue);
	UINT32					GetEnvLocalNumber(UINT32 nChkType, UINT32 nChkCode, UINT32 nKey);
	void					SetEnvLocalString(UINT32 nChkType, UINT32 nChkCode, UINT32 nKey, String strValue);
	String					GetEnvLocalString(UINT32 nChkType, UINT32 nChkCode, UINT32 nKey);
	INT32					IsExistLargeThenValue(UINT32 nChkType, UINT32 nChkCode, UINT32 nValue);

public:
	CManageEnvLocal();
    ~CManageEnvLocal();

};

extern CManageEnvLocal*	t_ManageEnvLocal;

#endif
