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

#ifndef DB_PO_IN_AC_DOC_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467
#define DB_PO_IN_AC_DOC_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467

typedef struct _db_po_in_ac_doc
{
	_db_po_in_ac_doc()
	{
		
	}

	DB_PO_HEADER		tDPH;

}DB_PO_IN_AC_DOC, *PDB_PO_IN_AC_DOC;

typedef list<DB_PO_IN_AC_DOC>					TListDBPoInAcDoc;
typedef TListDBPoInAcDoc::iterator				TListDBPoInAcDocItor;

typedef map<UINT32, DB_PO_IN_AC_DOC>			TMapDBPoInAcDoc;
typedef TMapDBPoInAcDoc::iterator				TMapDBPoInAcDocItor;
//---------------------------------------------------------------------------

typedef struct _db_po_in_ac_doc_pkg
{
	_db_po_in_ac_doc_pkg()
	{
		
	}

	DB_PO_HEADER		tDPH;
}DB_PO_IN_AC_DOC_PKG, *PDB_PO_IN_AC_DOC_PKG;

typedef list<DB_PO_IN_AC_DOC_PKG>				TListDBPoInAcDocPkg;
typedef TListDBPoInAcDocPkg::iterator			TListDBPoInAcDocPkgItor;

typedef map<UINT32, DB_PO_IN_AC_DOC_PKG>		TMapDBPoInAcDocPkg;
typedef TMapDBPoInAcDocPkg::iterator			TMapDBPoInAcDocPkgItor;
//---------------------------------------------------------------------------

typedef struct _db_po_in_ac_doc_unit
{
	_db_po_in_ac_doc_unit()
	{
		nAidType		= 0;
	}

	DB_PO_HEADER		tDPH;

	TMapID64			tLogModeMap;
	UINT32				nAidType;

}DB_PO_IN_AC_DOC_UNIT, *PDB_PO_IN_AC_DOC_UNIT;

typedef list<DB_PO_IN_AC_DOC_UNIT>				TListDBPoInAcDocUnit;
typedef TListDBPoInAcDocUnit::iterator			TListDBPoInAcDocUnitItor;

typedef map<UINT32, DB_PO_IN_AC_DOC_UNIT>		TMapDBPoInAcDocUnit;
typedef TMapDBPoInAcDocUnit::iterator			TMapDBPoInAcDocUnitItor;
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

typedef struct _db_po_in_ac_doc_unit_sub_pkg
{
	_db_po_in_ac_doc_unit_sub_pkg()
	{
		nRuleOrder		= 0;
		nAcMode			= 0;
	}

	DB_PO_HEADER		tDPH;

	UINT32				nRuleOrder;
	UINT32				nAcMode;

}DB_PO_IN_AC_DOC_UNIT_SUB_PKG, *PDB_PO_IN_AC_DOC_UNIT_SUB_PKG;

typedef list<DB_PO_IN_AC_DOC_UNIT_SUB_PKG>				TListDBPoInAcDocUnitSubPkg;
typedef TListDBPoInAcDocUnitSubPkg::iterator			TListDBPoInAcDocUnitSubPkgItor;

typedef map<UINT32, DB_PO_IN_AC_DOC_UNIT_SUB_PKG>		TMapDBPoInAcDocUnitSubPkg;
typedef TMapDBPoInAcDocUnitSubPkg::iterator			TMapDBPoInAcDocUnitSubPkgItor;
//---------------------------------------------------------------------------

typedef struct _db_po_in_ac_doc_unit_obj_pkg
{
	_db_po_in_ac_doc_unit_obj_pkg()
	{
	}

	DB_PO_HEADER		tDPH;

}DB_PO_IN_AC_DOC_UNIT_OBJ_PKG, *PDB_PO_IN_AC_DOC_UNIT_OBJ_PKG;

typedef list<DB_PO_IN_AC_DOC_UNIT_OBJ_PKG>				TListDBPoInAcDocUnitObjPkg;
typedef TListDBPoInAcDocUnitObjPkg::iterator			TListDBPoInAcDocUnitObjPkgItor;

typedef map<UINT32, DB_PO_IN_AC_DOC_UNIT_OBJ_PKG>		TMapDBPoInAcDocUnitObjPkg;
typedef TMapDBPoInAcDocUnitObjPkg::iterator			TMapDBPoInAcDocUnitObjPkgItor;
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
//---------------------------------------------------------------------------

typedef struct _db_po_in_ac_doc_sub_unit
{
	_db_po_in_ac_doc_sub_unit()
	{	
		nSbType	= 0;
	}

	DB_PO_HEADER		tDPH;

	UINT32				nSbType;	
	String				strSbName;
	String				strSbProc;
}DB_PO_IN_AC_DOC_SUB_UNIT, *PDB_PO_IN_AC_DOC_SUB_UNIT;

typedef list<DB_PO_IN_AC_DOC_SUB_UNIT>				TListDBPoInAcDocSubUnit;
typedef TListDBPoInAcDocSubUnit::iterator			TListDBPoInAcDocSubUnitItor;

typedef map<UINT32, DB_PO_IN_AC_DOC_SUB_UNIT>		TMapDBPoInAcDocSubUnit;
typedef TMapDBPoInAcDocSubUnit::iterator			TMapDBPoInAcDocSubUnitItor;
//---------------------------------------------------------------------------

typedef struct _db_po_in_ac_doc_obj_unit
{
	_db_po_in_ac_doc_obj_unit()
	{
		
	}

	DB_PO_HEADER		tDPH;

	String				strFilePath;	

}DB_PO_IN_AC_DOC_OBJ_UNIT, *PDB_PO_IN_AC_DOC_OBJ_UNIT;

typedef list<DB_PO_IN_AC_DOC_OBJ_UNIT>				TListDBPoInAcDocObjUnit;
typedef TListDBPoInAcDocObjUnit::iterator			TListDBPoInAcDocObjUnitItor;

typedef map<UINT32, DB_PO_IN_AC_DOC_OBJ_UNIT>		TMapDBPoInAcDocObjUnit;
typedef TMapDBPoInAcDocObjUnit::iterator			TMapDBPoInAcDocObjUnitItor;
//---------------------------------------------------------------------------

#endif //DB_PO_IN_AC_DOC_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467



