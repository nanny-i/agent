#pragma once

typedef struct _db_po_in_vuln_patch_exception
{
	_db_po_in_vuln_patch_exception()
	{
	}

	DB_PO_HEADER		tDPH;
}DB_PO_IN_VULN_PATCH_EXCEPTION, *PDB_PO_IN_VULN_PATCH_EXCEPTION;

typedef list<DB_PO_IN_VULN_PATCH_EXCEPTION>				TListDBPoInVulnPatchException;
typedef TListDBPoInVulnPatchException::iterator		TListDBPoInVulnPatchExceptionItor;

typedef map<UINT32, DB_PO_IN_VULN_PATCH_EXCEPTION>		TMapDBPoInVulnPatchException;
typedef TMapDBPoInVulnPatchException::iterator			TMapDBPoInVulnPatchExceptionItor;
//---------------------------------------------------------------------------

typedef struct _db_po_in_vuln_patch_exception_pkg
{
	_db_po_in_vuln_patch_exception_pkg()
	{
	}

	DB_PO_HEADER		tDPH;

}DB_PO_IN_VULN_PATCH_EXCEPTION_PKG, *PDB_PO_IN_VULN_PATCH_EXCEPTION_PKG;

typedef list<DB_PO_IN_VULN_PATCH_EXCEPTION_PKG>				TListDBPoInVulnPatchExceptionPkg;
typedef TListDBPoInVulnPatchExceptionPkg::iterator			TListDBPoInVulnPatchExceptionPkgItor;

typedef map<UINT32, DB_PO_IN_VULN_PATCH_EXCEPTION_PKG>		TMapDBPoInVulnPatchExceptionPkg;
typedef TMapDBPoInVulnPatchExceptionPkg::iterator			TMapDBPoInVulnPatchExceptionPkgItor;
//---------------------------------------------------------------------------

typedef struct _db_po_in_vuln_patch_exception_unit
{
	_db_po_in_vuln_patch_exception_unit()
	{
	}
	DB_PO_HEADER			tDPH;
	
	String					strPatchInfo;
}DB_PO_IN_VULN_PATCH_EXCEPTION_UNIT, *PDB_PO_IN_VULN_PATCH_EXCEPTION_UNIT;

typedef list<DB_PO_IN_VULN_PATCH_EXCEPTION_UNIT>			TListDBPoInVulnPatchExceptionUnit;
typedef TListDBPoInVulnPatchExceptionUnit::iterator		TListDBPoInVulnPatchExceptionUnitItor;

typedef map<UINT32, DB_PO_IN_VULN_PATCH_EXCEPTION_UNIT>		TMapDBPoInVulnPatchExceptionUnit;
typedef TMapDBPoInVulnPatchExceptionUnit::iterator			TMapDBPoInVulnPatchExceptionUnitItor;
//---------------------------------------------------------------------------