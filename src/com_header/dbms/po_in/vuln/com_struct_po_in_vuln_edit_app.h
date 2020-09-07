#pragma once

typedef struct _db_po_in_vuln_edit_app
{
	_db_po_in_vuln_edit_app()
	{
	}

	DB_PO_HEADER		tDPH;
}DB_PO_IN_VULN_EDIT_APP, *PDB_PO_IN_VULN_EDIT_APP;

typedef list<DB_PO_IN_VULN_EDIT_APP>				TListDBPoInVulnEditApp;
typedef TListDBPoInVulnEditApp::iterator		TListDBPoInVulnEditAppItor;

typedef map<UINT32, DB_PO_IN_VULN_EDIT_APP>		TMapDBPoInVulnEditApp;
typedef TMapDBPoInVulnEditApp::iterator			TMapDBPoInVulnEditAppItor;
//---------------------------------------------------------------------------

typedef struct _db_po_in_vuln_edit_app_pkg
{
	_db_po_in_vuln_edit_app_pkg()
	{
	}

	DB_PO_HEADER		tDPH;

}DB_PO_IN_VULN_EDIT_APP_PKG, *PDB_PO_IN_VULN_EDIT_APP_PKG;

typedef list<DB_PO_IN_VULN_EDIT_APP_PKG>				TListDBPoInVulnEditAppPkg;
typedef TListDBPoInVulnEditAppPkg::iterator			TListDBPoInVulnEditAppPkgItor;

typedef map<UINT32, DB_PO_IN_VULN_EDIT_APP_PKG>		TMapDBPoInVulnEditAppPkg;
typedef TMapDBPoInVulnEditAppPkg::iterator			TMapDBPoInVulnEditAppPkgItor;
//---------------------------------------------------------------------------

typedef struct _db_po_in_vuln_edit_app_unit
{
	_db_po_in_vuln_edit_app_unit()
	{
		strClassName.empty();
		strName.empty();
		strRegKey.empty();
	}
	
	String		strClassName;
	String		strName;
	String		strRegKey;
	
	DB_PO_HEADER			tDPH;

}DB_PO_IN_VULN_EDIT_APP_UNIT, *PDB_PO_IN_VULN_EDIT_APP_UNIT;

typedef list<DB_PO_IN_VULN_EDIT_APP_UNIT>			TListDBPoInVulnEditAppUnit;
typedef TListDBPoInVulnEditAppUnit::iterator		TListDBPoInVulnEditAppUnitItor;

typedef map<UINT32, DB_PO_IN_VULN_EDIT_APP_UNIT>		TMapDBPoInVulnEditAppUnit;
typedef TMapDBPoInVulnEditAppUnit::iterator			TMapDBPoInVulnEditAppUnitItor;
//---------------------------------------------------------------------------