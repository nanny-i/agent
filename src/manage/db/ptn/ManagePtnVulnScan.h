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

#ifndef ManagePtnVulnScanH
#define ManagePtnVulnScanH
//---------------------------------------------------------------------------

class CManagePtnVulnScan : public CManageBase<DB_PTN_VULN_SCAN>
{
private:
	CDBMgrPtnVulnScan*	m_tDBMgrPtnVulnScan;

public:
	INT32			LoadDBMS();

public:
	INT32			AddPtnVulnScan(DB_PTN_VULN_SCAN& data);
    INT32			EditPtnVulnScan(DB_PTN_VULN_SCAN& data);
    INT32			DelPtnVulnScan(UINT32 nID);

public:
	INT32			GetPkt(MemToken& RecvToken, DB_PTN_VULN_SCAN& data);
	INT32			SetPkt(MemToken& SendToken);
    INT32			SetPkt(PDB_PTN_VULN_SCAN pdata, MemToken& SendToken);

public:
	void 			RemainDBG_ItemCnt(UINT32 nIdx);

public:
	CManagePtnVulnScan();
    ~CManagePtnVulnScan();

};

#endif
