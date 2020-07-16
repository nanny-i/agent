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

#ifndef ManageSiteFileH
#define ManageSiteFileH
//---------------------------------------------------------------------------

class CManageSiteFile : public CManageBase<DB_SITE_FILE>
{

public:
	INT32			LoadDBMS();

public:
	INT32						AddSiteFile(DB_SITE_FILE& dsf);
	INT32						EditSiteFile(DB_SITE_FILE& dsf);
    INT32						DelSiteFile(UINT32 nID);
	PDB_SITE_FILE				FindSiteFileKey(String strName);
	INT32						ApplySiteFile(DB_SITE_FILE& dsf);

public:
	INT32			GetPkt(MemToken& RecvToken, DB_SITE_FILE& dsf);
	INT32			GetPktSync(MemToken& RecvToken, DB_SITE_FILE& dsf);

	INT32			SetPkt(MemToken& SendToken);
	INT32			SetPkt(TListID& tIDList, MemToken& SendToken);
	INT32			SetPkt(UINT32 nID, MemToken& SendToken);
    INT32			SetPkt(PDB_SITE_FILE pdsf, MemToken& SendToken);

	INT32			SetPktSync(MemToken& SendToken);
	INT32			SetPktSync(TListPVOID& tIDList);

public:
	void 			RemainDBG_ItemCnt(UINT32 nIdx);

public:
	CManageSiteFile();
    ~CManageSiteFile();

};

extern CManageSiteFile*	t_ManageSiteFile;

#endif
