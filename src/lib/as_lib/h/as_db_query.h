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

#ifndef _AS_SQLITE_QUERY_H__
#define _AS_SQLITE_QUERY_H__

#include "sqlite3.h"

typedef void *PVOID;	

class CASISQLiteQuery
{
private:
	sqlite3 *m_pSqlite;
public:
	int Open(char *pcDBName);
	int Close();
	int Prepare(char *pInQuery, PVOID* ppOutStmt);
	int Step(PVOID pInStmt);
	int ColumnCount(PVOID pInStmt);
	int ColumnType(PVOID pInStmt, int nIndex);
	char *ColumnText(PVOID pInStmt, int nIndex);
	int ColumnInt(PVOID pInStmt, int nIndex);
	float ColumnFloat(PVOID pInStmt, int nIndex);
	int ColumnBytes(PVOID pInStmt, int nIndex);
	char *ColumnBlob(PVOID pInStmt, int nIndex);
	void Finalize(PVOID pInStmt);
public:
	CASISQLiteQuery();
	~CASISQLiteQuery();
};

extern CASISQLiteQuery* t_SqliteQuery;


#endif /*_AS_SQLITE_QUERY_H__*/

