#pragma once

typedef struct _db_po_in_vuln_ax
{
	_db_po_in_vuln_ax()
	{
		nUnUseDay = 0;
	}

	DB_PO_HEADER		tDPH;
	INT32				nUnUseDay;
}DB_PO_IN_VULN_AX, *PDB_PO_IN_VULN_AX;

typedef list<DB_PO_IN_VULN_AX>				TListDBPoInVulnAx;
typedef TListDBPoInVulnAx::iterator		TListDBPoInVulnAxItor;

typedef map<UINT32, DB_PO_IN_VULN_AX>		TMapDBPoInVulnAx;
typedef TMapDBPoInVulnAx::iterator			TMapDBPoInVulnAxItor;
//---------------------------------------------------------------------------

typedef struct _db_po_in_vuln_ax_pkg
{
	_db_po_in_vuln_ax_pkg()
	{
	}

	DB_PO_HEADER		tDPH;

}DB_PO_IN_VULN_AX_PKG, *PDB_PO_IN_VULN_AX_PKG;

typedef list<DB_PO_IN_VULN_AX_PKG>				TListDBPoInVulnAxPkg;
typedef TListDBPoInVulnAxPkg::iterator			TListDBPoInVulnAxPkgItor;

typedef map<UINT32, DB_PO_IN_VULN_AX_PKG>		TMapDBPoInVulnAxPkg;
typedef TMapDBPoInVulnAxPkg::iterator			TMapDBPoInVulnAxPkgItor;
//---------------------------------------------------------------------------

typedef struct _db_po_in_vuln_ax_unit
{
	_db_po_in_vuln_ax_unit()
	{
		nFilter = 0;
		strName.empty();
		strClsId.empty();
		strDownloadedSite.empty();
		strPublisher.empty();
		strFileName.empty();
	}
	DB_PO_HEADER			tDPH;
	
	INT32					nFilter;
	String					strName;
	String					strClsId;
	String					strDownloadedSite;
	String					strPublisher;
	String					strFileName;

}DB_PO_IN_VULN_AX_UNIT, *PDB_PO_IN_VULN_AX_UNIT;

typedef list<DB_PO_IN_VULN_AX_UNIT>			TListDBPoInVulnAxUnit;
typedef TListDBPoInVulnAxUnit::iterator		TListDBPoInVulnAxUnitItor;

typedef map<UINT32, DB_PO_IN_VULN_AX_UNIT>		TMapDBPoInVulnAxUnit;
typedef TMapDBPoInVulnAxUnit::iterator			TMapDBPoInVulnAxUnitItor;
//---------------------------------------------------------------------------