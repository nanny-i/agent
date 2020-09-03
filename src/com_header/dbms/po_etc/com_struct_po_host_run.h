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

#ifndef DB_PO_HOST_RUN_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467
#define DB_PO_HOST_RUN_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467

typedef struct _db_po_host_run
{
	_db_po_host_run()
	{
		nRunOption		= 0;
		nRmLogDay		= 0;
		nLgnConPeriod	= 0;
		nMgrShowType	= 0;
		nShowLogDay		= 0;
		nBootChkType	= 0;
		nIntegrityMode	= 0;
		nCrossAuthMode	= 0;
		nOncePktNum		= 0;
	}

	DB_PO_HEADER		tDPH;

	UINT32				nRunOption;
	UINT32				nRmLogDay;
	UINT32				nLgnConPeriod;
	UINT32				nMgrShowType;
	UINT32				nShowLogDay;
	UINT32				nBootChkType;
	UINT32				nIntegrityMode;
	UINT32				nCrossAuthMode;
	UINT32				nOncePktNum;

}DB_PO_HOST_RUN, *PDB_PO_HOST_RUN;

typedef list<DB_PO_HOST_RUN>				TListDBPoHostRun;
typedef TListDBPoHostRun::iterator			TListDBPoHostRunItor;

typedef map<UINT32, DB_PO_HOST_RUN>			TMapDBPoHostRun;
typedef TMapDBPoHostRun::iterator			TMapDBPoHostRunItor;

#endif //DB_PO_HOST_RUN_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467



