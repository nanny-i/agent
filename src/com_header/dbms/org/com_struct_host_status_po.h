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

#ifndef DB_HOST_STATUS_PO_H_4D39CDDB_E289_4d56_9F98_FE42776F4467
#define DB_HOST_STATUS_PO_H_4D39CDDB_E289_4d56_9F98_FE42776F4467

typedef struct _db_host_status_po
{
	_db_host_status_po()
	{
		nID					= 0;
		nUsedFlag			= USED_FLAG_TYPE_USED;

		nHostID				= 0;
		nFaODrv				= 0;
		nFaCUnit			= 0;
		nDfRun				= 0;
		nDfUnit				= 0;

		nFeOpDrv			= 0;
		nFeLoDrv			= 0;
		nFeLoRun			= 0;
		nFeGbDrv			= 0;
		nFeGbRun			= 0;
		nFeGwDrv			= 0;
		nFeGwRun			= 0;
	} 

	UINT32				nID ;
	UINT32				nUsedFlag;
	UINT32				nHostID;
	UINT32				nFaODrv;
	UINT32				nFaCUnit;
	
	UINT32				nDfRun;
	UINT32				nDfUnit;

	UINT32				nFeOpDrv;
	UINT32				nFeLoDrv;
	UINT32				nFeLoRun;
	String				strFeLoPtn;
	UINT32				nFeGbDrv;
	UINT32				nFeGbRun;
	String				strFeGbPtn;
	UINT32				nFeGwDrv;
	UINT32				nFeGwRun;
	String				strFeGwPtn;
}DB_HOST_STATUS_PO, *PDB_HOST_STATUS_PO;

typedef list<DB_HOST_STATUS_PO>				TListDBHostStatusPo;
typedef TListDBHostStatusPo::iterator		TListDBHostStatusPoItor;

typedef map<UINT32, DB_HOST_STATUS_PO>		TMapDBHostStatusPo;
typedef TMapDBHostStatusPo::iterator		TMapDBHostStatusPoItor;

#endif //DB_HOST_STATUS_PO_H_4D39CDDB_E289_4d56_9F98_FE42776F4467



