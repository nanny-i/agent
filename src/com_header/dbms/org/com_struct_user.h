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

#ifndef DB_USER_H_4D39CDDB_E289_4d56_9F98_FE42776F4467
#define DB_USER_H_4D39CDDB_E289_4d56_9F98_FE42776F4467

typedef struct _db_user
{
	_db_user()
	{
		nID						= 0;
		nRegDate				= 0;
		nUsedFlag				= USED_FLAG_TYPE_USED;
		nInsType				= 0;

		nGroupID				= 0;
		nUGroupID				= 0;

		nExtOption				= 0;
	}  

	UINT32				nID ; 
	UINT32				nUsedFlag;
	UINT32				nRegDate;     
	UINT32				nInsType;

	UINT32				nGroupID;
	UINT32				nUGroupID;
	String				strUniCode;
	String				strAccountID;
	String				strAccountPW;

	String				strGCode;
	String				strName;
	String				strCoID;
	String				strCoRank;
	String				strCoRespon;
	String				strCoEMail;
	String				strCoPhone;
	String				strUserHPhone;
    String				strSrcGroupName;

	String				strDescr;

	String				strHash;

	UINT32				nExtOption;
}DB_USER, *PDB_USER;

typedef list<DB_USER>				TListDBUser;
typedef TListDBUser::iterator		TListDBUserItor;

typedef map<UINT32, DB_USER>		TMapDBUser;
typedef TMapDBUser::iterator		TMapDBUserItor;

#endif //DB_USER_H_4D39CDDB_E289_4d56_9F98_FE42776F4467



