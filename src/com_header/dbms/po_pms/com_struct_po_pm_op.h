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

#ifndef DB_PO_PM_OP_H_4D39CDDB_E289_4d56_9F98_FE42776F4467
#define DB_PO_PM_OP_H_4D39CDDB_E289_4d56_9F98_FE42776F4467

typedef struct _db_po_pm_op
{
	_db_po_pm_op()
    {
		nLogSyncMode		= 0;
		nDnTryNum			= 0;
		nMonRmPatch			= 0;
		nAutoPatchType		= 0;

		nPtnDnFileType		= 0;
    }

    DB_PO_HEADER		tDPH;
    
	UINT32		nLogSyncMode;
	UINT32		nDnTryNum;
	UINT64		nMonRmPatch;
	UINT32		nAutoPatchType;

	String		strPtnFileSvName;

	String		strPtnVersion;
	String		strPtnFileName;
	String		strPtnFileHash;

	UINT32		nPtnDnFileType;
	String		strPtnDnFileName;
	String		strPtnDnFileHash;

}DB_PO_PM_OP, *PDB_PO_PM_OP;

typedef list<DB_PO_PM_OP>				TListDBPoPmOp;
typedef TListDBPoPmOp::iterator			TListDBPoPmOpItor;

typedef map<UINT32, DB_PO_PM_OP>		TMapDBPoPmOp;
typedef TMapDBPoPmOp::iterator			TMapDBPoPmOpItor;

#endif //DB_PO_PM_OP_H_4D39CDDB_E289_4d56_9F98_FE42776F4467



