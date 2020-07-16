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

#ifndef DB_PO_IN_REG_VULN_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467
#define DB_PO_IN_REG_VULN_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467

typedef struct _db_po_in_reg_vuln
{
	_db_po_in_reg_vuln()
	{
	}

	DB_PO_HEADER		tDPH;

}DB_PO_IN_REG_VULN, *PDB_PO_IN_REG_VULN;

typedef list<DB_PO_IN_REG_VULN>				TListDBPoInRegVuln;
typedef TListDBPoInRegVuln::iterator		TListDBPoInRegVulnItor;

typedef map<UINT32, DB_PO_IN_REG_VULN>		TMapDBPoInRegVuln;
typedef TMapDBPoInRegVuln::iterator			TMapDBPoInRegVulnItor;
//---------------------------------------------------------------------------

typedef struct _db_po_in_reg_vuln_pkg
{
	_db_po_in_reg_vuln_pkg()
	{
	}

	DB_PO_HEADER		tDPH;

}DB_PO_IN_REG_VULN_PKG, *PDB_PO_IN_REG_VULN_PKG;

typedef list<DB_PO_IN_REG_VULN_PKG>			TListDBPoInRegVulnPkg;
typedef TListDBPoInRegVulnPkg::iterator		TListDBPoInRegVulnPkgItor;

typedef map<UINT32, DB_PO_IN_REG_VULN_PKG>	TMapDBPoInRegVulnPkg;
typedef TMapDBPoInRegVulnPkg::iterator		TMapDBPoInRegVulnPkgItor;
//---------------------------------------------------------------------------

typedef struct _db_po_in_reg_vuln_unit
{
	_db_po_in_reg_vuln_unit()
	{		
		nVulnValue			= 0;
	}

	DB_PO_HEADER		tDPH;
	
	String				strVulnName;	
	UINT32				nVulnValue;
}DB_PO_IN_REG_VULN_UNIT, *PDB_PO_IN_REG_VULN_UNIT;

typedef list<DB_PO_IN_REG_VULN_UNIT>			TListDBPoInRegVulnUnit;
typedef TListDBPoInRegVulnUnit::iterator		TListDBPoInRegVulnUnitItor;

typedef map<UINT32, DB_PO_IN_REG_VULN_UNIT>	TMapDBPoInRegVulnUnit;
typedef TMapDBPoInRegVulnUnit::iterator		TMapDBPoInRegVulnUnitItor;
//---------------------------------------------------------------------------

#endif //DB_PO_IN_REG_VULN_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467



