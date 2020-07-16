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

#ifndef DB_PO_IN_REG_SW_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467
#define DB_PO_IN_REG_SW_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467

typedef struct _db_po_in_reg_sw
{
	_db_po_in_reg_sw()
	{
	}

	DB_PO_HEADER		tDPH;

}DB_PO_IN_REG_SW, *PDB_PO_IN_REG_SW;

typedef list<DB_PO_IN_REG_SW>				TListDBPoInRegSW;
typedef TListDBPoInRegSW::iterator			TListDBPoInRegSWItor;

typedef map<UINT32, DB_PO_IN_REG_SW>		TMapDBPoInRegSW;
typedef TMapDBPoInRegSW::iterator			TMapDBPoInRegSWItor;
//---------------------------------------------------------------------------

typedef struct _db_po_in_reg_sw_pkg
{
	_db_po_in_reg_sw_pkg()
	{
	}

	DB_PO_HEADER		tDPH;

}DB_PO_IN_REG_SW_PKG, *PDB_PO_IN_REG_SW_PKG;

typedef list<DB_PO_IN_REG_SW_PKG>			TListDBPoInRegSWPkg;
typedef TListDBPoInRegSWPkg::iterator		TListDBPoInRegSWPkgItor;

typedef map<UINT32, DB_PO_IN_REG_SW_PKG>	TMapDBPoInRegSWPkg;
typedef TMapDBPoInRegSWPkg::iterator		TMapDBPoInRegSWPkgItor;
//---------------------------------------------------------------------------

typedef struct _db_po_in_reg_sw_unit
{
	_db_po_in_reg_sw_unit()
	{		
		
	}

	DB_PO_HEADER		tDPH;

	TMapID64			tLogModeMap;

}DB_PO_IN_REG_SW_UNIT, *PDB_PO_IN_REG_SW_UNIT;

typedef list<DB_PO_IN_REG_SW_UNIT>			TListDBPoInRegSWUnit;
typedef TListDBPoInRegSWUnit::iterator		TListDBPoInRegSWUnitItor;

typedef map<UINT32, DB_PO_IN_REG_SW_UNIT>	TMapDBPoInRegSWUnit;
typedef TMapDBPoInRegSWUnit::iterator		TMapDBPoInRegSWUnitItor;
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

typedef struct _db_po_in_reg_sw_unit_sub_pkg
{
	_db_po_in_reg_sw_unit_sub_pkg()
	{
		nRuleOrder		= 0;
		nAcMode			= 0;
	}

	DB_PO_HEADER		tDPH;

	UINT32				nRuleOrder;
	UINT32				nAcMode;

}DB_PO_IN_REG_SW_UNIT_SUB_PKG, *PDB_PO_IN_REG_SW_UNIT_SUB_PKG;

typedef list<DB_PO_IN_REG_SW_UNIT_SUB_PKG>				TListDBPoInRegSWUnitSubPkg;
typedef TListDBPoInRegSWUnitSubPkg::iterator			TListDBPoInRegSWUnitSubPkgItor;

typedef map<UINT32, DB_PO_IN_REG_SW_UNIT_SUB_PKG>		TMapDBPoInRegSWUnitSubPkg;
typedef TMapDBPoInRegSWUnitSubPkg::iterator			TMapDBPoInRegSWUnitSubPkgItor;
//---------------------------------------------------------------------------

typedef struct _db_po_in_reg_sw_unit_obj_pkg
{
	_db_po_in_reg_sw_unit_obj_pkg()
	{
	}

	DB_PO_HEADER		tDPH;

}DB_PO_IN_REG_SW_UNIT_OBJ_PKG, *PDB_PO_IN_REG_SW_UNIT_OBJ_PKG;

typedef list<DB_PO_IN_REG_SW_UNIT_OBJ_PKG>				TListDBPoInRegSWUnitObjPkg;
typedef TListDBPoInRegSWUnitObjPkg::iterator			TListDBPoInRegSWUnitObjPkgItor;

typedef map<UINT32, DB_PO_IN_REG_SW_UNIT_OBJ_PKG>		TMapDBPoInRegSWUnitObjPkg;
typedef TMapDBPoInRegSWUnitObjPkg::iterator			TMapDBPoInRegSWUnitObjPkgItor;
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

typedef struct _db_po_in_reg_sw_sub_unit
{
	_db_po_in_reg_sw_sub_unit()
	{	
		nSbType			= 0;		
	}

	DB_PO_HEADER		tDPH;

	UINT32				nSbType;	
	String				strSbName;
	String				strSbProc;

}DB_PO_IN_REG_SW_SUB_UNIT, *PDB_PO_IN_REG_SW_SUB_UNIT;

typedef list<DB_PO_IN_REG_SW_SUB_UNIT>				TListDBPoInRegSWSubUnit;
typedef TListDBPoInRegSWSubUnit::iterator			TListDBPoInRegSWSubUnitItor;

typedef map<UINT32, DB_PO_IN_REG_SW_SUB_UNIT>		TMapDBPoInRegSWSubUnit;
typedef TMapDBPoInRegSWSubUnit::iterator			TMapDBPoInRegSWSubUnitItor;
//---------------------------------------------------------------------------

typedef struct _db_po_in_reg_sw_obj_unit
{
	_db_po_in_reg_sw_obj_unit()
	{

	}

	DB_PO_HEADER		tDPH;

	String				strSWName;	

}DB_PO_IN_REG_SW_OBJ_UNIT, *PDB_PO_IN_REG_SW_OBJ_UNIT;

typedef list<DB_PO_IN_REG_SW_OBJ_UNIT>				TListDBPoInRegSWObjUnit;
typedef TListDBPoInRegSWObjUnit::iterator			TListDBPoInRegSWObjUnitItor;

typedef map<UINT32, DB_PO_IN_REG_SW_OBJ_UNIT>		TMapDBPoInRegSWObjUnit;
typedef TMapDBPoInRegSWObjUnit::iterator			TMapDBPoInRegSWObjUnitItor;
//---------------------------------------------------------------------------

#endif //DB_PO_IN_REG_SW_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467



