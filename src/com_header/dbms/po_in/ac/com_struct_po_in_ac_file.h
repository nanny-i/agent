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

#ifndef DB_PO_IN_AC_FILE_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467
#define DB_PO_IN_AC_FILE_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467

typedef struct _db_po_in_ac_file
{
	_db_po_in_ac_file()
	{
		
	}

	DB_PO_HEADER		tDPH;

}DB_PO_IN_AC_FILE, *PDB_PO_IN_AC_FILE;

typedef list<DB_PO_IN_AC_FILE>					TListDBPoInAcFile;
typedef TListDBPoInAcFile::iterator				TListDBPoInAcFileItor;

typedef map<UINT32, DB_PO_IN_AC_FILE>			TMapDBPoInAcFile;
typedef TMapDBPoInAcFile::iterator				TMapDBPoInAcFileItor;
//---------------------------------------------------------------------------

typedef struct _db_po_in_ac_file_pkg
{
	_db_po_in_ac_file_pkg()
	{
		
	}

	DB_PO_HEADER		tDPH;

}DB_PO_IN_AC_FILE_PKG, *PDB_PO_IN_AC_FILE_PKG;

typedef list<DB_PO_IN_AC_FILE_PKG>				TListDBPoInAcFilePkg;
typedef TListDBPoInAcFilePkg::iterator			TListDBPoInAcFilePkgItor;

typedef map<UINT32, DB_PO_IN_AC_FILE_PKG>		TMapDBPoInAcFilePkg;
typedef TMapDBPoInAcFilePkg::iterator			TMapDBPoInAcFilePkgItor;
//---------------------------------------------------------------------------

typedef struct _db_po_in_ac_file_unit
{
	_db_po_in_ac_file_unit()
	{
		
	}

	DB_PO_HEADER		tDPH;

	TMapID64			tLogModeMap;
}DB_PO_IN_AC_FILE_UNIT, *PDB_PO_IN_AC_FILE_UNIT;

typedef list<DB_PO_IN_AC_FILE_UNIT>				TListDBPoInAcFileUnit;
typedef TListDBPoInAcFileUnit::iterator			TListDBPoInAcFileUnitItor;

typedef map<UINT32, DB_PO_IN_AC_FILE_UNIT>		TMapDBPoInAcFileUnit;
typedef TMapDBPoInAcFileUnit::iterator			TMapDBPoInAcFileUnitItor;
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

typedef struct _db_po_in_ac_file_unit_sub_pkg
{
	_db_po_in_ac_file_unit_sub_pkg()
	{
	}

	DB_PO_HEADER		tDPH;

}DB_PO_IN_AC_FILE_UNIT_SUB_PKG, *PDB_PO_IN_AC_FILE_UNIT_SUB_PKG;

typedef list<DB_PO_IN_AC_FILE_UNIT_SUB_PKG>			TListDBPoInAcFileUnitSubPkg;
typedef TListDBPoInAcFileUnitSubPkg::iterator		TListDBPoInAcFileUnitSubPkgItor;

typedef map<UINT32, DB_PO_IN_AC_FILE_UNIT_SUB_PKG>	TMapDBPoInAcFileUnitSubPkg;
typedef TMapDBPoInAcFileUnitSubPkg::iterator		TMapDBPoInAcFileUnitSubPkgItor;
//---------------------------------------------------------------------------

typedef struct _db_po_in_ac_file_unit_obj_pkg
{
	_db_po_in_ac_file_unit_obj_pkg()
	{
	}

	DB_PO_HEADER		tDPH;

}DB_PO_IN_AC_FILE_UNIT_OBJ_PKG, *PDB_PO_IN_AC_FILE_UNIT_OBJ_PKG;

typedef list<DB_PO_IN_AC_FILE_UNIT_OBJ_PKG>			TListDBPoInAcFileUnitObjPkg;
typedef TListDBPoInAcFileUnitObjPkg::iterator		TListDBPoInAcFileUnitObjPkgItor;

typedef map<UINT32, DB_PO_IN_AC_FILE_UNIT_OBJ_PKG>	TMapDBPoInAcFileUnitObjPkg;
typedef TMapDBPoInAcFileUnitObjPkg::iterator		TMapDBPoInAcFileUnitObjPkgItor;
//---------------------------------------------------------------------------

typedef struct _db_po_in_ac_file_unit_sch_pkg
{
	_db_po_in_ac_file_unit_sch_pkg()
	{
	}

	DB_PO_HEADER		tDPH;

}DB_PO_IN_AC_FILE_UNIT_SCH_PKG, *PDB_PO_IN_AC_FILE_UNIT_SCH_PKG;

typedef list<DB_PO_IN_AC_FILE_UNIT_SCH_PKG>			TListDBPoInAcFileUnitSchPkg;
typedef TListDBPoInAcFileUnitSchPkg::iterator		TListDBPoInAcFileUnitSchPkgItor;

typedef map<UINT32, DB_PO_IN_AC_FILE_UNIT_SCH_PKG>	TMapDBPoInAcFileUnitSchPkg;
typedef TMapDBPoInAcFileUnitSchPkg::iterator		TMapDBPoInAcFileUnitSchPkgItor;
//---------------------------------------------------------------------------

typedef struct _db_po_in_ac_file_unit_rul_pkg
{
	_db_po_in_ac_file_unit_rul_pkg()
	{
		nRuleOrder	= 0;
		nAcMode		= 0;
	}

	DB_PO_HEADER		tDPH;

	UINT32				nRuleOrder;
	UINT32				nAcMode;

}DB_PO_IN_AC_FILE_UNIT_RUL_PKG, *PDB_PO_IN_AC_FILE_UNIT_RUL_PKG;

typedef list<DB_PO_IN_AC_FILE_UNIT_RUL_PKG>			TListDBPoInAcFileUnitRulPkg;
typedef TListDBPoInAcFileUnitRulPkg::iterator		TListDBPoInAcFileUnitRulPkgItor;

typedef map<UINT32, DB_PO_IN_AC_FILE_UNIT_RUL_PKG>	TMapDBPoInAcFileUnitRulPkg;
typedef TMapDBPoInAcFileUnitRulPkg::iterator		TMapDBPoInAcFileUnitRulPkgItor;
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

typedef struct _db_po_in_ac_file_sub_unit
{
	_db_po_in_ac_file_sub_unit()
	{	
		nSbType			= 0;		
	}

	DB_PO_HEADER		tDPH;

	UINT32				nSbType;	
	String				strSbName;
	String				strSbProc;
}DB_PO_IN_AC_FILE_SUB_UNIT, *PDB_PO_IN_AC_FILE_SUB_UNIT;

typedef list<DB_PO_IN_AC_FILE_SUB_UNIT>				TListDBPoInAcFileSubUnit;
typedef TListDBPoInAcFileSubUnit::iterator			TListDBPoInAcFileSubUnitItor;

typedef map<UINT32, DB_PO_IN_AC_FILE_SUB_UNIT>		TMapDBPoInAcFileSubUnit;
typedef TMapDBPoInAcFileSubUnit::iterator			TMapDBPoInAcFileSubUnitItor;
//---------------------------------------------------------------------------

typedef struct _db_po_in_ac_file_obj_unit
{
	_db_po_in_ac_file_obj_unit()
	{
		
	}

	DB_PO_HEADER		tDPH;

	String				strFilePath;
}DB_PO_IN_AC_FILE_OBJ_UNIT, *PDB_PO_IN_AC_FILE_OBJ_UNIT;

typedef list<DB_PO_IN_AC_FILE_OBJ_UNIT>				TListDBPoInAcFileObjUnit;
typedef TListDBPoInAcFileObjUnit::iterator			TListDBPoInAcFileObjUnitItor;

typedef map<UINT32, DB_PO_IN_AC_FILE_OBJ_UNIT>		TMapDBPoInAcFileObjUnit;
typedef TMapDBPoInAcFileObjUnit::iterator			TMapDBPoInAcFileObjUnitItor;
//---------------------------------------------------------------------------

typedef struct _db_po_in_ac_file_sch_unit
{
	_db_po_in_ac_file_sch_unit()
	{	
		nSchMon		= 0;
		nSchDay		= 0;
		nSchWeek	= 0;
		nSchHour	= 0;
		nSchMin		= 0;
	}

	DB_PO_HEADER		tDPH;

	UINT32				nSchMon;
	UINT32				nSchDay;
	UINT32				nSchWeek;
	UINT32				nSchHour;
	UINT32				nSchMin;
}DB_PO_IN_AC_FILE_SCH_UNIT, *PDB_PO_IN_AC_FILE_SCH_UNIT;

typedef list<DB_PO_IN_AC_FILE_SCH_UNIT>				TListDBPoInAcFileSchUnit;
typedef TListDBPoInAcFileSchUnit::iterator			TListDBPoInAcFileSchUnitItor;

typedef map<UINT32, DB_PO_IN_AC_FILE_SCH_UNIT>		TMapDBPoInAcFileSchUnit;
typedef TMapDBPoInAcFileSchUnit::iterator			TMapDBPoInAcFileSchUnitItor;
//---------------------------------------------------------------------------

#endif //DB_PO_IN_AC_FILE_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467



