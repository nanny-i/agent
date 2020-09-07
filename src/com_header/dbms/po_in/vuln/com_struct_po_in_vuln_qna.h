#pragma once

typedef struct _db_po_in_vuln_qna
{
	_db_po_in_vuln_qna()
	{
	}

	DB_PO_HEADER		tDPH;
}DB_PO_IN_VULN_QNA, *PDB_PO_IN_VULN_QNA;

typedef list<DB_PO_IN_VULN_QNA>				TListDBPoInVulnQna;
typedef TListDBPoInVulnQna::iterator		TListDBPoInVulnQnaItor;

typedef map<UINT32, DB_PO_IN_VULN_QNA>		TMapDBPoInVulnQna;
typedef TMapDBPoInVulnQna::iterator			TMapDBPoInVulnQnaItor;
//---------------------------------------------------------------------------

typedef struct _db_po_in_vuln_qna_pkg
{
	_db_po_in_vuln_qna_pkg()
	{
	}

	DB_PO_HEADER		tDPH;

}DB_PO_IN_VULN_QNA_PKG, *PDB_PO_IN_VULN_QNA_PKG;

typedef list<DB_PO_IN_VULN_QNA_PKG>				TListDBPoInVulnQnaPkg;
typedef TListDBPoInVulnQnaPkg::iterator			TListDBPoInVulnQnaPkgItor;

typedef map<UINT32, DB_PO_IN_VULN_QNA_PKG>		TMapDBPoInVulnQnaPkg;
typedef TMapDBPoInVulnQnaPkg::iterator			TMapDBPoInVulnQnaPkgItor;
//---------------------------------------------------------------------------

typedef struct _db_po_in_vuln_qna_unit
{
	_db_po_in_vuln_qna_unit()
	{
		strQuestion.empty();
		strAnswer.empty();
	}
	DB_PO_HEADER			tDPH;

	String					strQuestion;
	String					strAnswer;
}DB_PO_IN_VULN_QNA_UNIT, *PDB_PO_IN_VULN_QNA_UNIT;

typedef list<DB_PO_IN_VULN_QNA_UNIT>			TListDBPoInVulnQnaUnit;
typedef TListDBPoInVulnQnaUnit::iterator		TListDBPoInVulnQnaUnitItor;

typedef map<UINT32, DB_PO_IN_VULN_QNA_UNIT>		TMapDBPoInVulnQnaUnit;
typedef TMapDBPoInVulnQnaUnit::iterator			TMapDBPoInVulnQnaUnitItor;
//---------------------------------------------------------------------------