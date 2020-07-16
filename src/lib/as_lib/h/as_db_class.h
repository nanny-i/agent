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

#ifndef _AS_DB_UTIL_H__
#define _AS_DB_UTIL_H__

#define QUERY_SELECT "select "
#define QUERY_SELECT_LEN 7

#define SQL_QUERY_LENGTH 32

#define COLUMN_TYPE_NULL	0
#define COLUMN_TYPE_INT		1
#define COLUMN_TYPE_TEXT	2
#define COLUMN_TYPE_FLOAT	3
#define COLUMN_TYPE_BLOB	4

class CASIDBUtil
{
private:
	void *m_pStmt;
public:
	CASIDBUtil();
	~CASIDBUtil();

	int OpenDatabase(char *pcDBName, char *pcLogMsg=NULL);
	int CreateDatabase(char *pcDBName, char *pcLogMsg=NULL);
	int CloseDatabase(char *pcLogMsg=NULL);
	int	ExecuteQuery(char *pcQuery, char *pcLogMsg=NULL);
	int	IsTableExist(char *pcQuery, char *pcLogMsg=NULL);
	bool Next();
	int GetDBFieldCount();
	int GetDBFieldType(int nIndex);
	int GetDBFieldInt(int nIndex);
	char *GetDBFieldString(int nIndex);
	float GetDBFieldFloat(int nIndex);
	int GetDBFieldBytes(int nIndex);
	char *GetDBFieldBlob(int nIndex);
private:
	int ExecuteQuerySelect(char *pcQuery, char *pcLogMsg=NULL);
	int ExecuteQueryExe(char *pcQuery, char *pcLogMsg=NULL);
	int	Execute(char *pcQuery, char *pcLogMsg);
	int Begin(char *pcLogMsg=NULL);
	int Commit(char *pcLogMsg=NULL);
	int Rollback(char *pcLogMsg=NULL);
};

#endif /*_ASI_DB_UTIL_H__*/

