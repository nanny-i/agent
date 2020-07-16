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

#ifndef DB_PTN_FILE_INFO_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467
#define DB_PTN_FILE_INFO_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467


typedef struct _db_ptn_file_info
{
	_db_ptn_file_info()
	{
		
	}

	String				strSavePath;
	String				strSaveName;
	String				strFileHash;
	String				strPtnVersion;
	UINT32				nPtnUnitNum;
	UINT32				nPtnChkValue;

}DB_PTN_FILE_INFO, *PDB_PTN_FILE_INFO;

typedef list<DB_PTN_FILE_INFO>			TListDBPtnFileInfo;
typedef TListDBPtnFileInfo::iterator	TListDBPtnFileInfoItor;
//---------------------------------------------------------------------------

#endif //DB_PTN_FILE_INFO_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467



