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

#ifndef DB_PO_IN_REG_SVC_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467
#define DB_PO_IN_REG_SVC_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467

typedef struct _db_po_in_reg_svc
{
	_db_po_in_reg_svc()
	{
	}

	DB_PO_HEADER		tDPH;

}DB_PO_IN_REG_SVC, *PDB_PO_IN_REG_SVC;

typedef list<DB_PO_IN_REG_SVC>				TListDBPoInRegSvc;
typedef TListDBPoInRegSvc::iterator			TListDBPoInRegSvcItor;

typedef map<UINT32, DB_PO_IN_REG_SVC>		TMapDBPoInRegSvc;
typedef TMapDBPoInRegSvc::iterator			TMapDBPoInRegSvcItor;
//---------------------------------------------------------------------------

typedef struct _db_po_in_reg_svc_pkg
{
	_db_po_in_reg_svc_pkg()
	{
	}

	DB_PO_HEADER		tDPH;

}DB_PO_IN_REG_SVC_PKG, *PDB_PO_IN_REG_SVC_PKG;

typedef list<DB_PO_IN_REG_SVC_PKG>			TListDBPoInRegSvcPkg;
typedef TListDBPoInRegSvcPkg::iterator		TListDBPoInRegSvcPkgItor;

typedef map<UINT32, DB_PO_IN_REG_SVC_PKG>	TMapDBPoInRegSvcPkg;
typedef TMapDBPoInRegSvcPkg::iterator		TMapDBPoInRegSvcPkgItor;
//---------------------------------------------------------------------------

typedef struct _db_po_in_reg_svc_unit
{
	_db_po_in_reg_svc_unit()
	{		
		
	}

	DB_PO_HEADER		tDPH;

	TMapID64			tLogModeMap;

}DB_PO_IN_REG_SVC_UNIT, *PDB_PO_IN_REG_SVC_UNIT;

typedef list<DB_PO_IN_REG_SVC_UNIT>			TListDBPoInRegSvcUnit;
typedef TListDBPoInRegSvcUnit::iterator		TListDBPoInRegSvcUnitItor;

typedef map<UINT32, DB_PO_IN_REG_SVC_UNIT>	TMapDBPoInRegSvcUnit;
typedef TMapDBPoInRegSvcUnit::iterator		TMapDBPoInRegSvcUnitItor;
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

typedef struct _db_po_in_reg_svc_unit_sub_pkg
{
	_db_po_in_reg_svc_unit_sub_pkg()
	{
		nRuleOrder		= 0;
		nAcMode			= 0;
	}

	DB_PO_HEADER		tDPH;

	UINT32				nRuleOrder;
	UINT32				nAcMode;

}DB_PO_IN_REG_SVC_UNIT_SUB_PKG, *PDB_PO_IN_REG_SVC_UNIT_SUB_PKG;

typedef list<DB_PO_IN_REG_SVC_UNIT_SUB_PKG>				TListDBPoInRegSvcUnitSubPkg;
typedef TListDBPoInRegSvcUnitSubPkg::iterator			TListDBPoInRegSvcUnitSubPkgItor;

typedef map<UINT32, DB_PO_IN_REG_SVC_UNIT_SUB_PKG>		TMapDBPoInRegSvcUnitSubPkg;
typedef TMapDBPoInRegSvcUnitSubPkg::iterator			TMapDBPoInRegSvcUnitSubPkgItor;
//---------------------------------------------------------------------------

typedef struct _db_po_in_reg_svc_unit_obj_pkg
{
	_db_po_in_reg_svc_unit_obj_pkg()
	{
	}

	DB_PO_HEADER		tDPH;

}DB_PO_IN_REG_SVC_UNIT_OBJ_PKG, *PDB_PO_IN_REG_SVC_UNIT_OBJ_PKG;

typedef list<DB_PO_IN_REG_SVC_UNIT_OBJ_PKG>				TListDBPoInRegSvcUnitObjPkg;
typedef TListDBPoInRegSvcUnitObjPkg::iterator			TListDBPoInRegSvcUnitObjPkgItor;

typedef map<UINT32, DB_PO_IN_REG_SVC_UNIT_OBJ_PKG>		TMapDBPoInRegSvcUnitObjPkg;
typedef TMapDBPoInRegSvcUnitObjPkg::iterator			TMapDBPoInRegSvcUnitObjPkgItor;
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

typedef struct _db_po_in_reg_svc_sub_unit
{
	_db_po_in_reg_svc_sub_unit()
	{	
		nSbType			= 0;		
	}

	DB_PO_HEADER		tDPH;

	UINT32				nSbType;	
	String				strSbName;
	String				strSbProc;

}DB_PO_IN_REG_SVC_SUB_UNIT, *PDB_PO_IN_REG_SVC_SUB_UNIT;

typedef list<DB_PO_IN_REG_SVC_SUB_UNIT>				TListDBPoInRegSvcSubUnit;
typedef TListDBPoInRegSvcSubUnit::iterator			TListDBPoInRegSvcSubUnitItor;

typedef map<UINT32, DB_PO_IN_REG_SVC_SUB_UNIT>		TMapDBPoInRegSvcSubUnit;
typedef TMapDBPoInRegSvcSubUnit::iterator			TMapDBPoInRegSvcSubUnitItor;
//---------------------------------------------------------------------------

typedef struct _db_po_in_reg_svc_obj_unit
{
	_db_po_in_reg_svc_obj_unit()
	{
		
	}

	DB_PO_HEADER		tDPH;

	String				strSvcName;	

}DB_PO_IN_REG_SVC_OBJ_UNIT, *PDB_PO_IN_REG_SVC_OBJ_UNIT;

typedef list<DB_PO_IN_REG_SVC_OBJ_UNIT>				TListDBPoInRegSvcObjUnit;
typedef TListDBPoInRegSvcObjUnit::iterator			TListDBPoInRegSvcObjUnitItor;

typedef map<UINT32, DB_PO_IN_REG_SVC_OBJ_UNIT>		TMapDBPoInRegSvcObjUnit;
typedef TMapDBPoInRegSvcObjUnit::iterator			TMapDBPoInRegSvcObjUnitItor;
//---------------------------------------------------------------------------


#endif //DB_PO_IN_REG_SVC_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467



