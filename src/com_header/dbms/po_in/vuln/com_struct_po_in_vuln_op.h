#ifndef DB_PO_IN_VULN_OP_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467
#define DB_PO_IN_VULN_OP_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467

typedef struct _db_po_vuln_op_ptn_file
{
	_db_po_vuln_op_ptn_file()
	{
		nPtnDnFileType	= 0;
	}

	String				strPtnFileSvName;

	String				strPtnVersion;
	String				strPtnFileName;
	String				strPtnFileHash;

	UINT32				nPtnDnFileType;
	String				strPtnDnFileName;
	String				strPtnDnFileHash;

}DB_PO_IN_VULN_OP_PTN_FILE, *PDB_PO_IN_VULN_OP_PTN_FILE;
//---------------------------------------------------------------------------

typedef struct _db_po_in_vuln_op
{
	_db_po_in_vuln_op()
	{
		nPtnFileID	= 0;
	}

	DB_PO_HEADER				tDPH;

	UINT32						nPtnFileID;
	DB_PO_IN_VULN_OP_PTN_FILE	tDPIVOPF;

}DB_PO_IN_VULN_OP, *PDB_PO_IN_VULN_OP;

typedef list<DB_PO_IN_VULN_OP>				TListDBPoInVulnOp;
typedef TListDBPoInVulnOp::iterator			TListDBPoInVulnOpItor;

typedef map<UINT32, DB_PO_IN_VULN_OP>		TMapDBPoInVulnOp;
typedef TMapDBPoInVulnOp::iterator			TMapDBPoInVulnOpItor;
//---------------------------------------------------------------------------

typedef struct _db_po_in_vuln_op_pkg
{
	_db_po_in_vuln_op_pkg()
	{
		nScore			= 0;
	}

	DB_PO_HEADER		tDPH;

	UINT32				nScore;

}DB_PO_IN_VULN_OP_PKG, *PDB_PO_IN_VULN_OP_PKG;

typedef list<DB_PO_IN_VULN_OP_PKG>				TListDBPoInVulnOpPkg;
typedef TListDBPoInVulnOpPkg::iterator			TListDBPoInVulnOpPkgItor;

typedef map<UINT32, DB_PO_IN_VULN_OP_PKG>		TMapDBPoInVulnOpPkg;
typedef TMapDBPoInVulnOpPkg::iterator			TMapDBPoInVulnOpPkgItor;
//---------------------------------------------------------------------------

#endif //DB_PO_IN_VULN_OP_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467



