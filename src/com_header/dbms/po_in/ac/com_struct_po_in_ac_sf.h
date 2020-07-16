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

#ifndef DB_PO_IN_AC_SF_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467
#define DB_PO_IN_AC_SF_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467

typedef struct _db_po_in_ac_sf
{
	_db_po_in_ac_sf()
	{
		
	}

	DB_PO_HEADER		tDPH;

}DB_PO_IN_AC_SF, *PDB_PO_IN_AC_SF;

typedef list<DB_PO_IN_AC_SF>					TListDBPoInAcSf;
typedef TListDBPoInAcSf::iterator				TListDBPoInAcSfItor;

typedef map<UINT32, DB_PO_IN_AC_SF>				TMapDBPoInAcSf;
typedef TMapDBPoInAcSf::iterator				TMapDBPoInAcSfItor;
//---------------------------------------------------------------------------

typedef struct _db_po_in_ac_sf_pkg
{
	_db_po_in_ac_sf_pkg()
	{
		
	}

	DB_PO_HEADER		tDPH;

}DB_PO_IN_AC_SF_PKG, *PDB_PO_IN_AC_SF_PKG;

typedef list<DB_PO_IN_AC_SF_PKG>				TListDBPoInAcSfPkg;
typedef TListDBPoInAcSfPkg::iterator			TListDBPoInAcSfPkgItor;

typedef map<UINT32, DB_PO_IN_AC_SF_PKG>			TMapDBPoInAcSfPkg;
typedef TMapDBPoInAcSfPkg::iterator				TMapDBPoInAcSfPkgItor;
//---------------------------------------------------------------------------

typedef struct _db_po_in_ac_sf_unit
{
	_db_po_in_ac_sf_unit()
	{
		
	}

	DB_PO_HEADER		tDPH;

	TMapID64			tLogModeMap;	

}DB_PO_IN_AC_SF_UNIT, *PDB_PO_IN_AC_SF_UNIT;

typedef list<DB_PO_IN_AC_SF_UNIT>				TListDBPoInAcSfUnit;
typedef TListDBPoInAcSfUnit::iterator			TListDBPoInAcSfUnitItor;

typedef map<UINT32, DB_PO_IN_AC_SF_UNIT>		TMapDBPoInAcSfUnit;
typedef TMapDBPoInAcSfUnit::iterator			TMapDBPoInAcSfUnitItor;
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

typedef struct _db_po_in_ac_sf_unit_sub_pkg
{
	_db_po_in_ac_sf_unit_sub_pkg()
	{
		nRuleOrder		= 0;
		nAcMode			= 0;
	}

	DB_PO_HEADER		tDPH;

	UINT32				nRuleOrder;
	UINT32				nAcMode;

}DB_PO_IN_AC_SF_UNIT_SUB_PKG, *PDB_PO_IN_AC_SF_UNIT_SUB_PKG;

typedef list<DB_PO_IN_AC_SF_UNIT_SUB_PKG>			TListDBPoInAcSfUnitSubPkg;
typedef TListDBPoInAcSfUnitSubPkg::iterator			TListDBPoInAcSfUnitSubPkgItor;

typedef map<UINT32, DB_PO_IN_AC_SF_UNIT_SUB_PKG>	TMapDBPoInAcSfUnitSubPkg;
typedef TMapDBPoInAcSfUnitSubPkg::iterator			TMapDBPoInAcSfUnitSubPkgItor;
//---------------------------------------------------------------------------

typedef struct _db_po_in_ac_sf_unit_obj_pkg
{
	_db_po_in_ac_sf_unit_obj_pkg()
	{
	}

	DB_PO_HEADER		tDPH;

}DB_PO_IN_AC_SF_UNIT_OBJ_PKG, *PDB_PO_IN_AC_SF_UNIT_OBJ_PKG;

typedef list<DB_PO_IN_AC_SF_UNIT_OBJ_PKG>			TListDBPoInAcSfUnitObjPkg;
typedef TListDBPoInAcSfUnitObjPkg::iterator			TListDBPoInAcSfUnitObjPkgItor;

typedef map<UINT32, DB_PO_IN_AC_SF_UNIT_OBJ_PKG>	TMapDBPoInAcSfUnitObjPkg;
typedef TMapDBPoInAcSfUnitObjPkg::iterator			TMapDBPoInAcSfUnitObjPkgItor;
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
//---------------------------------------------------------------------------

typedef struct _db_po_in_ac_sf_sub_unit
{
	_db_po_in_ac_sf_sub_unit()
	{	
		nSbType		= 0;
		
	}

	DB_PO_HEADER		tDPH;
	
	UINT32				nSbType;	
	String				strSbName;
	String				strSbProc;
}DB_PO_IN_AC_SF_SUB_UNIT, *PDB_PO_IN_AC_SF_SUB_UNIT;

typedef list<DB_PO_IN_AC_SF_SUB_UNIT>				TListDBPoInAcSfSubUnit;
typedef TListDBPoInAcSfSubUnit::iterator			TListDBPoInAcSfSubUnitItor;

typedef map<UINT32, DB_PO_IN_AC_SF_SUB_UNIT>		TMapDBPoInAcSfSubUnit;
typedef TMapDBPoInAcSfSubUnit::iterator			TMapDBPoInAcSfSubUnitItor;
//---------------------------------------------------------------------------

typedef struct _db_po_in_ac_sf_obj_unit
{
	_db_po_in_ac_sf_obj_unit()
	{
		nSFMode = 0;
	}

	DB_PO_HEADER		tDPH;

	String				strFilePath;
	UINT32				nSFMode;
}DB_PO_IN_AC_SF_OBJ_UNIT, *PDB_PO_IN_AC_SF_OBJ_UNIT;

typedef list<DB_PO_IN_AC_SF_OBJ_UNIT>				TListDBPoInAcSfObjUnit;
typedef TListDBPoInAcSfObjUnit::iterator			TListDBPoInAcSfObjUnitItor;

typedef map<UINT32, DB_PO_IN_AC_SF_OBJ_UNIT>		TMapDBPoInAcSfObjUnit;
typedef TMapDBPoInAcSfObjUnit::iterator			TMapDBPoInAcSfObjUnitItor;
//---------------------------------------------------------------------------
#endif //DB_PO_IN_AC_SF_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467



