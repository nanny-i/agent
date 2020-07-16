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

#ifndef DB_PO_IN_PTN_SP_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467
#define DB_PO_IN_PTN_SP_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467

typedef struct _db_po_in_ptn_sp
{
	_db_po_in_ptn_sp()
	{
		nConfirmLevel	= 0;
		nConfirmDay		= 0;	
		
	}

	DB_PO_HEADER		tDPH;

	UINT32				nConfirmLevel;
	UINT32				nConfirmDay;
		
}DB_PO_IN_PTN_SP, *PDB_PO_IN_PTN_SP;

typedef list<DB_PO_IN_PTN_SP>				TListDBPoInPtnSP;
typedef TListDBPoInPtnSP::iterator			TListDBPoInPtnSPItor;

typedef map<UINT32, DB_PO_IN_PTN_SP>		TMapDBPoInPtnSP;
typedef TMapDBPoInPtnSP::iterator			TMapDBPoInPtnSPItor;
//---------------------------------------------------------------------------

typedef struct _db_po_in_ptn_sp_pkg
{
	_db_po_in_ptn_sp_pkg()
	{
	}

	DB_PO_HEADER		tDPH;

}DB_PO_IN_PTN_SP_PKG, *PDB_PO_IN_PTN_SP_PKG;

typedef list<DB_PO_IN_PTN_SP_PKG>			TListDBPoInPtnSPPkg;
typedef TListDBPoInPtnSPPkg::iterator		TListDBPoInPtnSPPkgItor;

typedef map<UINT32, DB_PO_IN_PTN_SP_PKG>	TMapDBPoInPtnSPPkg;
typedef TMapDBPoInPtnSPPkg::iterator		TMapDBPoInPtnSPPkgItor;
//---------------------------------------------------------------------------

typedef struct _db_po_in_ptn_sp_unit
{
	_db_po_in_ptn_sp_unit()
	{
		nBlockMode		= 0;
		nUseDay			= 0;

		nFltChkType		= 0;
	}

	DB_PO_HEADER		tDPH;

	UINT32				nBlockMode;
	UINT32				nUseDay;

	UINT32				nFltChkType;
	DB_FILE_INFO		tDFI;

}DB_PO_IN_PTN_SP_UNIT, *PDB_PO_IN_PTN_SP_UNIT;

typedef list<DB_PO_IN_PTN_SP_UNIT>			TListDBPoInPtnSPUnit;
typedef TListDBPoInPtnSPUnit::iterator		TListDBPoInPtnSPUnitItor;

typedef map<UINT32, DB_PO_IN_PTN_SP_UNIT>	TMapDBPoInPtnSPUnit;
typedef TMapDBPoInPtnSPUnit::iterator		TMapDBPoInPtnSPUnitItor;
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------


#endif //DB_PO_IN_PTN_SP_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467



