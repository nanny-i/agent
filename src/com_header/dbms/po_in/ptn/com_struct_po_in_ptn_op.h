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

#ifndef DB_PO_IN_PTN_OP_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467
#define DB_PO_IN_PTN_OP_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467

typedef struct _db_po_in_ptn_op
{
	_db_po_in_ptn_op()
	{	  
		nBlockMode				= 0;	
		nRTFGMode				= 0;
	}

	DB_PO_HEADER		tDPH;		

	UINT32				nBlockMode;		
	UINT32				nRTFGMode;

}DB_PO_IN_PTN_OP, *PDB_PO_IN_PTN_OP;

typedef list<DB_PO_IN_PTN_OP>				TListDBPoInPtnOp;
typedef TListDBPoInPtnOp::iterator			TListDBPoInPtnOpItor;

typedef map<UINT32, DB_PO_IN_PTN_OP>		TMapDBPoInPtnOp;
typedef TMapDBPoInPtnOp::iterator			TMapDBPoInPtnOpItor;
//---------------------------------------------------------------------------

typedef struct _db_po_in_ptn_op_pkg
{
	_db_po_in_ptn_op_pkg()
	{
	}

	DB_PO_HEADER		tDPH;

}DB_PO_IN_PTN_OP_PKG, *PDB_PO_IN_PTN_OP_PKG;

typedef list<DB_PO_IN_PTN_OP_PKG>			TListDBPoInPtnOpPkg;
typedef TListDBPoInPtnOpPkg::iterator		TListDBPoInPtnOpPkgItor;

typedef map<UINT32, DB_PO_IN_PTN_OP_PKG>	TMapDBPoInPtnOpPkg;
typedef TMapDBPoInPtnOpPkg::iterator		TMapDBPoInPtnOpPkgItor;
//---------------------------------------------------------------------------

typedef struct _db_po_in_ptn_op_unit
{
	_db_po_in_ptn_op_unit()
	{
		nLastScanTime		= 0;
		nSchTime			= 0;
		nFileGatherType		= 0;
	}

	DB_PO_HEADER		tDPH;

	UINT64				nSchTime;
	UINT32				nLastScanTime;
	UINT32				nFileGatherType;
	String				strScanPath;

}DB_PO_IN_PTN_OP_UNIT, *PDB_PO_IN_PTN_OP_UNIT;

typedef list<DB_PO_IN_PTN_OP_UNIT>			TListDBPoInPtnOpUnit;
typedef TListDBPoInPtnOpUnit::iterator		TListDBPoInPtnOpUnitItor;

typedef map<UINT32, DB_PO_IN_PTN_OP_UNIT>	TMapDBPoInPtnOpUnit;
typedef TMapDBPoInPtnOpUnit::iterator		TMapDBPoInPtnOpUnitItor;
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

#endif //DB_PO_IN_PTN_OP_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467



