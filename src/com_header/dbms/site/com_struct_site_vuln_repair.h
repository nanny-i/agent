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

#ifndef DB_SITE_VULN_REPAIR_H_4D39CDDB_E289_4d56_9F98_FE42776F4467
#define DB_SITE_VULN_REPAIR_H_4D39CDDB_E289_4d56_9F98_FE42776F4467

typedef struct _db_site_vuln_repair
{
	_db_site_vuln_repair()
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
		nRepairOrder	= 0;

		nRepairType		= SS_SITE_VULN_TYPE_NONE;
		nCustomID		= SS_SITE_VULN_CUSTOM_ID_NONE;

		nRepairOpType	= SS_SITE_VULN_OP_TYPE_NONE;		
		nValueType		= SS_SITE_VULN_VALUE_TYPE_UNKNOWN;		
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
	UINT32			nRepairOrder;

	UINT32			nRepairType;	// SS_SITE_VULN_TYPE_XXXX
	UINT32			nCustomID;		// SS_SITE_VULN_CUSTOM_ID_XXXX

	String			strRepairPath;		
	UINT32			nValueType;		// SS_SITE_VULN_VALUE_TYPE_XXXX	
	UINT32			nRepairOpType;	// SS_SITE_VULN_OP_TYPE_XXXX
	String			strRepairValue;

}DB_SITE_VULN_REPAIR, *PDB_SITE_VULN_REPAIR;

typedef list<DB_SITE_VULN_REPAIR>				TListDBSiteVulnRepair;
typedef TListDBSiteVulnRepair::iterator			TListDBSiteVulnRepairItor;

typedef map<UINT32, DB_SITE_VULN_REPAIR>		TMapDBSiteVulnRepair;
typedef TMapDBSiteVulnRepair::iterator			TMapDBSiteVulnRepairItor;

//---------------------------------------------------------------------------------------

#endif //DB_SITE_VULN_REPAIR_H_4D39CDDB_E289_4d56_9F98_FE42776F4467




