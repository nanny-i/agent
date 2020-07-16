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

#ifndef DB_SITE_VULN_SCAN_H_4D39CDDB_E289_4d56_9F98_FE42776F4467
#define DB_SITE_VULN_SCAN_H_4D39CDDB_E289_4d56_9F98_FE42776F4467

typedef struct _db_site_vuln_scan
{
	_db_site_vuln_scan()
	{
		nID				= 0;
		nUsedFlag		= STATUS_USED_MODE_ON;
		nRegDate		= 0;
		nUsedMode		= 0;
		nAdminID		= 0;
		nExtOption		= 0;

		nOsType			= ASI_SYSTEM_TYPE_ALL;
		nOsID			= ASI_SYSTEM_ID_ALL;
		nOsPa			= ASI_SYSTEM_ARCH_ALL;	

		nSVulnID		= 0;
		nSVulnSubID		= 0;
		nScanOrder		= 0;

		nScanType		= SS_SITE_VULN_TYPE_NONE;		
		nCustomID		= SS_SITE_VULN_CUSTOM_ID_NONE;
		
		nValueType		= SS_SITE_VULN_VALUE_TYPE_UNKNOWN;
		nCompType		= SS_SITE_VULN_COMPARE_TYPE_UNKNOWN;
		nDecisionType	= SS_SITE_VULN_DECISION_CRITERIA_AND;
	} 

	UINT32			nID ;
	UINT32			nUsedFlag;
	UINT32			nRegDate;
	UINT32			nUsedMode;
	UINT32			nAdminID;
	UINT32			nExtOption;

	String			strName;
	String			strDescr;

	UINT32			nOsType;		// ASI_SYSTEM_TYPE_XXXX
	UINT64			nOsID;			// ASI_SYSTEM_ID_XXXX	
	UINT32			nOsPa;			// ASI_SYSTEM_ARCH_XXXX	

	UINT32			nSVulnID;
	UINT32			nSVulnSubID;
	UINT32			nScanOrder;
	
	UINT32			nScanType;		// SS_SITE_VULN_TYPE_XXXX
	UINT32			nCustomID;		// SS_SITE_VULN_CUSTOM_ID_XXXX

	String			strScanPath;		
	UINT32			nValueType;		// SS_SITE_VULN_VALUE_TYPE_XXXX
	UINT32			nDecisionType;	// SS_SITE_VULN_DECISION_CRITERIA_XXXX
	UINT32			nCompType;		// SS_SITE_VULN_COMPARE_TYPE_XXXX
	String			strCompValue;	

	void CopyTo(_mem_site_vuln_scan_dll &rhs)
	{
		rhs.nID				= nID;
		rhs.nUsedFlag		= nUsedFlag;
		rhs.nRegDate		= nRegDate;
		rhs.nUsedMode		= nUsedMode;
		rhs.nAdminID		= nAdminID;
		rhs.nExtOption		= nExtOption;

		rhs.strName			= strName;
		rhs.strDescr		= strDescr;

		rhs.nOsType			= nOsType;
		rhs.nOsID			= nOsID;
		rhs.nOsPa			= nOsPa;	

		rhs.nSVulnID		= nSVulnID;
		rhs.nSVulnSubID		= nSVulnSubID;
		rhs.nScanOrder		= nScanOrder;

		rhs.nScanType		= nScanType;		
		rhs.nCustomID		= nCustomID;

		rhs.strScanPath		= strScanPath;
		rhs.nValueType		= nValueType;
		rhs.nCompType		= nCompType;
		rhs.nDecisionType	= nDecisionType;
		rhs.strCompValue	= strCompValue;
	}

}DB_SITE_VULN_SCAN, *PDB_SITE_VULN_SCAN;



typedef list<DB_SITE_VULN_SCAN>				TListDBSiteVulnScan;
typedef TListDBSiteVulnScan::iterator		TListDBSiteVulnScanItor;

typedef map<UINT32, DB_SITE_VULN_SCAN>		TMapDBSiteVulnScan;
typedef TMapDBSiteVulnScan::iterator		TMapDBSiteVulnScanItor;

//---------------------------------------------------------------------------------------

#endif //DB_SITE_VULN_SCAN_H_4D39CDDB_E289_4d56_9F98_FE42776F4467




