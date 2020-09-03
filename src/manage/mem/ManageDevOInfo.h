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

#ifndef ManageDevOInfoH
#define ManageDevOInfoH
//---------------------------------------------------------------------------

class CManageDevOInfo : public CManageBase<MEM_DEVO_INFO>
{
private:
	UINT32				GetMaxID();

public:
	INT32				AddDevOInfo(String strDvInstanceID, String strDvPaInstanceID, UINT32 nPolType, BOOL bIsDefPol = FALSE);
	INT32				CheckDvPolicy(BOOL bDefReset = FALSE);
	UINT32				GetDvType(String strClassName);

public:
	INT32				SetPkt(MemToken& SendToken);
	INT32				SetPkt(UINT32 nID, MemToken& SendToken);
	INT32				SetPkt(PMEM_DEVO_INFO pdata, MemToken& SendToken);

public:
	CManageDevOInfo();
    ~CManageDevOInfo();

};

extern CManageDevOInfo*	t_ManageDevOInfo;

#endif
