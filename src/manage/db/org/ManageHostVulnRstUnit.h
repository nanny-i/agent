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

#ifndef ManageHostVulnRstUnitH
#define ManageHostVulnRstUnitH
//---------------------------------------------------------------------------

class CManageHostVulnRstUnit : public CManageBase<DB_HOST_VULN_RST_UNIT>
{

public:
	INT32				LoadDBMS();

public:
	INT32				AddHostVulnRstUnit(DB_HOST_VULN_RST_UNIT& data);
    INT32				EditHostVulnRstUnit(DB_HOST_VULN_RST_UNIT& data);
    INT32				DelHostVulnRstUnit(UINT32 nID);

public:
	INT32				GetPkt_Link(MemToken& RecvToken, DB_HOST_VULN_RST_UNIT& data);
	INT32				SetPkt_Link(MemToken& SendToken);
	INT32				SetPkt_Link(TListID& tIDList, MemToken& SendToken);
	INT32				SetPkt_Link(PDB_HOST_VULN_RST_UNIT pdata, MemToken& SendToken);	

public:
	void 				RemainDBG_ItemCnt(UINT32 nIdx);

public:
	CManageHostVulnRstUnit();
    ~CManageHostVulnRstUnit();

};

extern CManageHostVulnRstUnit*	t_ManageHostVulnRstUnit;

#endif
