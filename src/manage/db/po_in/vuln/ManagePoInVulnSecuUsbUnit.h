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


#ifndef ManagePoInVulnSecuUsbUnitH
#define ManagePoInVulnSecuUsbUnitH
//---------------------------------------------------------------------------

class CManagePoInVulnSecuUsbUnit : public CManagePoBase<DB_PO_IN_VULN_SECU_USB_UNIT>
{
public:
	INT32					LoadDBMS();

public:
	INT32					GetHash(UINT32 nID, String& strOrgValue);

public:
	INT32					AddPoInVulnSecuUsbUnit(DB_PO_IN_VULN_SECU_USB_UNIT&	data);
    INT32					EditPoInVulnSecuUsbUnit(DB_PO_IN_VULN_SECU_USB_UNIT&	data);
	INT32					DelPoInVulnSecuUsbUnit(UINT32 nID);
	INT32					ApplyPoInVulnSecuUsbUnit(DB_PO_IN_VULN_SECU_USB_UNIT&	data);

public:
	String					GetName(UINT32 nID);    

public:
	INT32					SetPkt(MemToken& SendToken);
	INT32					SetPkt(UINT32 nID, MemToken& SendToken);
	INT32					SetPkt(PDB_PO_IN_VULN_SECU_USB_UNIT pdata, MemToken& SendToken);
	INT32					GetPkt(MemToken& RecvToken, DB_PO_IN_VULN_SECU_USB_UNIT& data);

public:
	CManagePoInVulnSecuUsbUnit();
    ~CManagePoInVulnSecuUsbUnit();

};

extern CManagePoInVulnSecuUsbUnit*	t_ManagePoInVulnSecuUsbUnit;

#endif
