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


#ifndef ManageVulnFileProtectH
#define ManageVulnFileProtectH
//---------------------------------------------------------------------------

class CManageVulnFileProtect : public CManageBase<DB_VULN_FILE_PROTECT>
{

public:
	INT32			LoadDBMS();

public:
	INT32			AddVulnFileProtect(DB_VULN_FILE_PROTECT& data);
    INT32			EditVulnFileProtect(DB_VULN_FILE_PROTECT& data);
    INT32			DelVulnFileProtect(UINT32 nID);
	INT32			ApplyVulnFileProtect(DB_VULN_FILE_PROTECT&	data);

public:
	String			GetName(UINT32 nID);
	INT32			MakeObject(UINT32 nID, POBJECT_ENTRY* pObjList, UINT32& nObjRulNum, UINT32 nType);

public:
	INT32			GetPkt(MemToken& RecvToken, DB_VULN_FILE_PROTECT& data);
	INT32			SetPkt(MemToken& SendToken);
    INT32			SetPkt(PDB_VULN_FILE_PROTECT pdata, MemToken& SendToken);
	INT32			SetPktHost(UINT32 nID, MemToken& SendToken);

public:
	void 			RemainDBG_ItemCnt(UINT32 nIdx);

public:
	CManageVulnFileProtect();
    ~CManageVulnFileProtect();

};

extern CManageVulnFileProtect*	t_ManageVulnFileProtect;

#endif
