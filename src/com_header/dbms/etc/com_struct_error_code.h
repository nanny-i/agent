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

#ifndef DB_ERROR_CODE_H_348683B5_F316_4a4d_842D_63E68B189A5D
#define DB_ERROR_CODE_H_348683B5_F316_4a4d_842D_63E68B189A5D

typedef struct _db_error_code_lan
{
	String		strType;
    String		strDescr;
}DB_ERROR_CODE_LAN, *PDB_ERROR_CODE_LAN;

typedef struct _db_error_code
{
    _db_error_code()
    {
        nID 	= 0;        
    }
  
    UINT32		nID;
    DB_ERROR_CODE_LAN	lan_kor;
    DB_ERROR_CODE_LAN	lan_eng;    
}DB_ERROR_CODE, *PDB_ERROR_CODE;

typedef list<DB_ERROR_CODE>					TListDBErrorCode;
typedef TListDBErrorCode::iterator			TListDBErrorCodeItor;

typedef map<UINT32, DB_ERROR_CODE>			TMapDBErrorCode;
typedef TMapDBErrorCode::iterator			TMapDBErrorCodeItor;

#endif //DB_ERROR_CODE_H_348683B5_F316_4a4d_842D_63E68B189A5D



