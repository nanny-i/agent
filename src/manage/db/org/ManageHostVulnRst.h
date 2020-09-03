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

#ifndef ManageHostVulnRstH
#define ManageHostVulnRstH
//---------------------------------------------------------------------------

class CManageHostVulnRst : public CManageBase<DB_HOST_VULN_RST>
{

public:
	INT32				LoadDBMS();

public:
	INT32				AddHostVulnRst(DB_HOST_VULN_RST& data);
    INT32				EditHostVulnRst(DB_HOST_VULN_RST& data);
    INT32				DelHostVulnRst(UINT32 nID);

	void				SetRstMapToStr(PDB_HOST_VULN_RST pdata);

public:
	INT32				SetPktSync(MemToken& SendToken);

	INT32				GetPkt(MemToken& RecvToken, DB_HOST_VULN_RST& data);
	INT32				SetPkt(MemToken& SendToken);
	INT32				SetPkt(TListDBHostVulnRst& tDBHostVulnRstList, MemToken& SendToken);
	INT32				SetPkt(PDB_HOST_VULN_RST pdata, MemToken& SendToken);	

public:
	INT32				GetPkt_Link(MemToken& RecvToken, DB_HOST_VULN_RST& data);
	INT32				SetPkt_Link(MemToken& SendToken);
	INT32				SetPkt_Link(PDB_HOST_VULN_RST pdata, MemToken& SendToken);	

	INT32				SetPkt_Link(UINT32 nID, MemToken& SendToken);	

public:
	void 				RemainDBG_ItemCnt(UINT32 nIdx);

public:
	CManageHostVulnRst();
    ~CManageHostVulnRst();

};

extern CManageHostVulnRst*	t_ManageHostVulnRst;

#endif
