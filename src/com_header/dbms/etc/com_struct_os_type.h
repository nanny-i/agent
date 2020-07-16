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

#ifndef DB_OS_TYPE_H_4D39CDDB_E289_4d56_9F98_FE42776F4467
#define DB_OS_TYPE_H_4D39CDDB_E289_4d56_9F98_FE42776F4467

typedef struct _db_os_type
{
	_db_os_type()
    {
        nID			= 0;
        nType		= 0;
        
    }

    UINT32				nID ;
    String				strName;
    INT32				nType;

}DB_OS_TYPE, *PDB_OS_TYPE;

typedef list<DB_OS_TYPE>				TListDBOsType;
typedef TListDBOsType::iterator			TListDBOsTypeItor;

typedef map<UINT32, DB_OS_TYPE>			TMapDBOsType;
typedef TMapDBOsType::iterator			TMapDBOsTypeItor;

#endif //DB_OS_TYPE_H_4D39CDDB_E289_4d56_9F98_FE42776F4467



