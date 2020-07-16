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


#ifndef	COM_STRUCT_DBMS_H_6AB3CD45_6B1E_4bCB_9AE9_F7924A2FF8B8
#define COM_STRUCT_DBMS_H_6AB3CD45_6B1E_4bCB_9AE9_F7924A2FF8B8


//DBMS Account Info
////////////////////////////////////////////////////////////////////////////////

typedef struct _dbms_account_info
{
	_dbms_account_info()
    {
    	nDBLocal		= 1;
    	nDBType 		= 0;
        nPort			= 0;
        nUsedADO		= 0;
        nUsedQueryPool  = 0;
    }

    INT32 	nDBLocal;
    INT32 	nDBType;
    String	strIP;
    INT32	nPort;
    String	strDB;
    String	strID;
    String	strPw;
    String	strCharSet;
    INT32	nUsedADO;
    INT32	nUsedQueryPool;
}DBMS_ACCOUNT_INFO, *PDBMS_ACCOUNT_INFO;


#endif //COM_STRUCT_DBMS_H_6AB3CD45_6B1E_4bCB_9AE9_F7924A2FF8B8
