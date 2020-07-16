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

#ifndef DB_LOG_DOC_DSCAN_H_4D39CDDB_E289_4d56_9F98_FE42776F4467
#define DB_LOG_DOC_DSCAN_H_4D39CDDB_E289_4d56_9F98_FE42776F4467

typedef struct _db_log_doc_dscan
{
	_db_log_doc_dscan()
    {
		nID				= 0;
		nUsedFlag		= 1;
		nRegDate		= 0;
		nExtOption		= 0;
		
		nFindNum		= 0;
		nDelNum			= 0;
    }
	
	UINT32				nID;
	UINT32				nUsedFlag;
	UINT32				nRegDate;
	UINT32				nExtOption;

	String				strScanPath;
	String				strScanPtn;
	
	UINT32				nFindNum;
	UINT32				nDelNum;

}DB_LOG_DOC_DSCAN, *PDB_LOG_DOC_DSCAN;

typedef list<DB_LOG_DOC_DSCAN>				TListDBLogDocDScan;
typedef TListDBLogDocDScan::iterator		TListDBLogDocDScanItor;

typedef map<UINT32, DB_LOG_DOC_DSCAN>		TMapDBLogDocDScan;
typedef TMapDBLogDocDScan::iterator			TMapDBLogDocDScanItor;

#endif //DB_LOG_DOC_DSCAN_H_4D39CDDB_E289_4d56_9F98_FE42776F4467



