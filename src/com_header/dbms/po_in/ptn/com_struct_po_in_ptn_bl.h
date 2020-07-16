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

#ifndef DB_PO_IN_PTN_BL_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467
#define DB_PO_IN_PTN_BL_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467

typedef struct _db_po_in_ptn_bl
{
	_db_po_in_ptn_bl()
	{		
	}

	DB_PO_HEADER		tDPH;
	DB_PTN_FILE_INFO	tDPFI;
}DB_PO_IN_PTN_BL, *PDB_PO_IN_PTN_BL;

typedef list<DB_PO_IN_PTN_BL>				TListDBPoInPtnBL;
typedef TListDBPoInPtnBL::iterator			TListDBPoInPtnBLItor;

typedef map<UINT32, DB_PO_IN_PTN_BL>		TMapDBPoInPtnBL;
typedef TMapDBPoInPtnBL::iterator			TMapDBPoInPtnBLItor;
//---------------------------------------------------------------------------

typedef struct _db_po_in_ptn_bl_pkg
{
	_db_po_in_ptn_bl_pkg()
	{
	}

	DB_PO_HEADER		tDPH;

}DB_PO_IN_PTN_BL_PKG, *PDB_PO_IN_PTN_BL_PKG;

typedef list<DB_PO_IN_PTN_BL_PKG>			TListDBPoInPtnBLPkg;
typedef TListDBPoInPtnBLPkg::iterator		TListDBPoInPtnBLPkgItor;

typedef map<UINT32, DB_PO_IN_PTN_BL_PKG>	TMapDBPoInPtnBLPkg;
typedef TMapDBPoInPtnBLPkg::iterator		TMapDBPoInPtnBLPkgItor;
//---------------------------------------------------------------------------

typedef struct _db_po_in_ptn_bl_unit
{
	_db_po_in_ptn_bl_unit()
	{
		nRTMode		= 0;
	}

	DB_PO_HEADER		tDPH;

	UINT32				nRTMode;
	UINT32				nFltChkType;
	DB_FILE_INFO		tDFI;

}DB_PO_IN_PTN_BL_UNIT, *PDB_PO_IN_PTN_BL_UNIT;

typedef list<DB_PO_IN_PTN_BL_UNIT>			TListDBPoInPtnBLUnit;
typedef TListDBPoInPtnBLUnit::iterator		TListDBPoInPtnBLUnitItor;

typedef map<UINT32, DB_PO_IN_PTN_BL_UNIT>	TMapDBPoInPtnBLUnit;
typedef TMapDBPoInPtnBLUnit::iterator		TMapDBPoInPtnBLUnitItor;
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------


#endif //DB_PO_IN_PTN_BL_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467



