#ifndef DB_PO_PM_SCAN_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467
#define DB_PO_PM_SCAN_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467

typedef struct _db_po_pm_scan
{
	_db_po_pm_scan()
	{
	}

	DB_PO_HEADER		tDPH;

}DB_PO_PM_SCAN, *PDB_PO_PM_SCAN;

typedef list<DB_PO_PM_SCAN>					TListDBPoPmScan;
typedef TListDBPoPmScan::iterator			TListDBPoPmScanItor;

typedef map<UINT32, DB_PO_PM_SCAN>			TMapDBPoPmScan;
typedef TMapDBPoPmScan::iterator			TMapDBPoPmScanItor;
//---------------------------------------------------------------------------

typedef struct _db_po_pm_scan_pkg
{
	_db_po_pm_scan_pkg()
	{
	}

	DB_PO_HEADER		tDPH;

}DB_PO_PM_SCAN_PKG, *PDB_PO_PM_SCAN_PKG;

typedef list<DB_PO_PM_SCAN_PKG>				TListDBPoPmScanPkg;
typedef TListDBPoPmScanPkg::iterator		TListDBPoPmScanPkgItor;

typedef map<UINT32, DB_PO_PM_SCAN_PKG>		TMapDBPoPmScanPkg;
typedef TMapDBPoPmScanPkg::iterator			TMapDBPoPmScanPkgItor;
//---------------------------------------------------------------------------

typedef struct _db_po_pm_scan_unit
{
	_db_po_pm_scan_unit()
	{
		nScanType		= 0;
		nScanTime		= 0;	
		nScanSvrType	= 0;

		nScanLastTime	= 0;
	}

	DB_PO_HEADER		tDPH;

	UINT32				nScanType;
	UINT64				nScanTime;
	UINT32				nScanSvrType;

	UINT32				nScanLastTime;

}DB_PO_PM_SCAN_UNIT, *PDB_PO_PM_SCAN_UNIT;

typedef list<DB_PO_PM_SCAN_UNIT>			TListDBPoPmScanUnit;
typedef TListDBPoPmScanUnit::iterator		TListDBPoPmScanUnitItor;

typedef map<UINT32, DB_PO_PM_SCAN_UNIT>		TMapDBPoPmScanUnit;
typedef TMapDBPoPmScanUnit::iterator		TMapDBPoPmScanUnitItor;
//---------------------------------------------------------------------------

#endif //DB_PO_PM_SCAN_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467



