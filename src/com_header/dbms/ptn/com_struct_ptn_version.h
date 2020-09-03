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

#ifndef DB_PTN_VERSION_H_5DBB6BFC_032B_42a5_81C6_C86A909331BE
#define DB_PTN_VERSION_H_5DBB6BFC_032B_42a5_81C6_C86A909331BE

typedef struct _db_ptn_version
{
	_db_ptn_version()
	{
		nID					= 0;		
	}

	UINT32		nID;
	String		strPtnVersion;

}DB_PTN_VERSION, *PDB_PTN_VERSION;

typedef list<DB_PTN_VERSION>			TListDBPtnVersion;
typedef TListDBPtnVersion::iterator	TListDBPtnVersionItor;

typedef map<UINT32, DB_PTN_VERSION>	TMapDBPtnVersion;
typedef TMapDBPtnVersion::iterator		TMapDBPtnVersionItor;

#endif /*DB_PTN_VERSION_H_5DBB6BFC_032B_42a5_81C6_C86A909331BE*/



