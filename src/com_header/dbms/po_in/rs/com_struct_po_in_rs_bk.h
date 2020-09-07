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

#ifndef DB_PO_IN_RS_BK_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467
#define DB_PO_IN_RS_BK_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467

typedef struct _db_po_in_rs_bk
{
	_db_po_in_rs_bk()
	{	  
		nKeepSize			= 0;
		nFreeSize			= 0;
		nFileMaxSize		= 0;
		nFileKeppNum		= 0;

		nFExtType			= 0;
	}

	DB_PO_HEADER		tDPH;		

	UINT32				nKeepSize;
	UINT32				nFreeSize;
	UINT32				nFileMaxSize;
	UINT32				nFileKeppNum;

	UINT32				nFExtType;
	String				strFExtInfo;
}DB_PO_IN_RS_BK, *PDB_PO_IN_RS_BK;

typedef list<DB_PO_IN_RS_BK>				TListDBPoInRsBk;
typedef TListDBPoInRsBk::iterator			TListDBPoInRsBkItor;

typedef map<UINT32, DB_PO_IN_RS_BK>			TMapDBPoInRsBk;
typedef TMapDBPoInRsBk::iterator			TMapDBPoInRsBkItor;

#endif //DB_PO_IN_RS_BK_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467



