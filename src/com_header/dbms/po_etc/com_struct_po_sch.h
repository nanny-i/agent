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

#ifndef DB_PO_SCH_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467
#define DB_PO_SCH_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467

typedef struct _db_po_sch
{
	_db_po_sch()
	{
	}

	DB_PO_HEADER		tDPH;

}DB_PO_SCH, *PDB_PO_SCH;

typedef list<DB_PO_SCH>				TListDBPoSch;
typedef TListDBPoSch::iterator		TListDBPoSchItor;

typedef map<UINT32, DB_PO_SCH>		TMapDBPoSch;
typedef TMapDBPoSch::iterator		TMapDBPoSchItor;	
//----------------------------------------------------------------------------	

typedef struct _db_po_sch_pkg
{
	_db_po_sch_pkg()
	{
		nScanLastTime				= 0;
	}

	DB_PO_HEADER		tDPH;

	UINT32				nScanLastTime;

}DB_PO_SCH_PKG, *PDB_PO_SCH_PKG;

typedef list<DB_PO_SCH_PKG>				TListDBPoSchPkg;
typedef TListDBPoSchPkg::iterator			TListDBPoSchPkgItor;

typedef map<UINT32, DB_PO_SCH_PKG>		TMapDBPoSchPkg;
typedef TMapDBPoSchPkg::iterator			TMapDBPoSchPkgItor;
//----------------------------------------------------------------------------

typedef struct _db_po_sch_unit
{
	_db_po_sch_unit()
	{
		nPackageType			= 0;
		nStDate					= 0;
		nEdDate					= 0;
	}

	DB_PO_HEADER		tDPH;

	UINT64				nPackageType;				
	TMapID64			tPoInfoMap;
	UINT32				nStDate;
	UINT32				nEdDate;

}DB_PO_SCH_UNIT, *PDB_PO_SCH_UNIT;  

typedef list<DB_PO_SCH_UNIT>		TListDBPoSchUnit;
typedef TListDBPoSchUnit::iterator	TListDBPoSchUnitItor;

typedef map<UINT32, DB_PO_SCH_UNIT>	TMapDBPoSchUnit;
typedef TMapDBPoSchUnit::iterator		TMapDBPoSchUnitItor;
//----------------------------------------------------------------------------	


#endif //DB_PO_HOST_CLEAR_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467
