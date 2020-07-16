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

#ifndef DB_PO_IN_VULN_OP_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467
#define DB_PO_IN_VULN_OP_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467

typedef struct _db_po_in_vuln_op
{
	_db_po_in_vuln_op()
	{
	}

	DB_PO_HEADER		tDPH;

}DB_PO_IN_VULN_OP, *PDB_PO_IN_VULN_OP;

typedef list<DB_PO_IN_VULN_OP>				TListDBPoInVulnOp;
typedef TListDBPoInVulnOp::iterator			TListDBPoInVulnOpItor;

typedef map<UINT32, DB_PO_IN_VULN_OP>		TMapDBPoInVulnOp;
typedef TMapDBPoInVulnOp::iterator			TMapDBPoInVulnOpItor;
//---------------------------------------------------------------------------

typedef struct _db_po_in_vuln_op_pkg
{
	_db_po_in_vuln_op_pkg()
	{
		nSiteScore		= 0;
	}

	DB_PO_HEADER		tDPH;
	UINT32				nSiteScore;

}DB_PO_IN_VULN_OP_PKG, *PDB_PO_IN_VULN_OP_PKG;

typedef list<DB_PO_IN_VULN_OP_PKG>				TListDBPoInVulnOpPkg;
typedef TListDBPoInVulnOpPkg::iterator			TListDBPoInVulnOpPkgItor;

typedef map<UINT32, DB_PO_IN_VULN_OP_PKG>		TMapDBPoInVulnOpPkg;
typedef TMapDBPoInVulnOpPkg::iterator			TMapDBPoInVulnOpPkgItor;
//---------------------------------------------------------------------------

#endif //DB_PO_IN_VULN_OP_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467



