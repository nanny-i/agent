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

#ifndef _AS_ODBC_UTIL_H__
#define _AS_ODBC_UTIL_H__

void GetErrorMessage(SQLSMALLINT, SQLHANDLE, SQLRETURN, char *);
void StmtResourcesFree(SQLHANDLE);
void TransRollback(SQLHANDLE);
void MultiConnTransRollback(SQLHANDLE);

extern int CheckReturnValue(SQLRETURN);
extern int CLIAppInitLocal(char *, char *, char *, SQLHANDLE *, SQLHANDLE *, SQLPOINTER, char *);
extern void CLIAppTerm(SQLHANDLE *, SQLHANDLE *);
extern void FreeStmtHandle(SQLHANDLE&);
extern int StmtExecDirectFromFile(SQLHANDLE, const char *, char *);



inline int ENV_HANDLE_CHECK(SQLHANDLE hEnv, SQLRETURN cliRC, char *acLogMsg)
{
	int rc = 0;
	rc = CheckReturnValue(cliRC);
	if (rc != 0)
	{
		GetErrorMessage(SQL_HANDLE_ENV, hEnv, cliRC, acLogMsg);
	}
	return rc;
}

inline int DBC_HANDLE_CHECK(SQLHANDLE hDbc, SQLRETURN cliRC, char *acLogMsg)
{
	int rc = 0;
	rc = CheckReturnValue(cliRC);
	if (rc != 0)
	{
		GetErrorMessage(SQL_HANDLE_DBC, hDbc, cliRC, acLogMsg);
	}
	return rc;
	
}

inline int STMT_HANDLE_CHECK(SQLHANDLE hStmt, SQLHANDLE hDbc, SQLRETURN cliRC, char *acLogMsg)
{
	int rc = 0;
	rc = CheckReturnValue(cliRC);
	if (rc != 0)
	{
		GetErrorMessage(SQL_HANDLE_STMT, hStmt, cliRC, acLogMsg);
		if (rc == -2)
			StmtResourcesFree(hStmt);
		TransRollback(hDbc);
	}
	return rc;
}

inline int MC_STMT_HANDLE_CHECK(SQLHANDLE hStmt, SQLHANDLE hEnv, SQLRETURN cliRC, char *acLogMsg)
{
	int rc = 0;
	rc = CheckReturnValue(cliRC);
	if (rc != 0)
	{
		GetErrorMessage(SQL_HANDLE_STMT, hStmt, cliRC, acLogMsg);
		if (rc == -2)
			StmtResourcesFree(hStmt);
		MultiConnTransRollback(hEnv);
	}
	return rc;
}

#endif /*_AS_ODBC_UTIL_H__*/

