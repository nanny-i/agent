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

#ifndef DB_PTN_PATCH_FILE_H_5DBB6BFC_032B_42a5_81C6_C86A909331BE
#define DB_PTN_PATCH_FILE_H_5DBB6BFC_032B_42a5_81C6_C86A909331BE


typedef struct _db_ptn_patch_file
{
	_db_ptn_patch_file()
	{
		nID					= 0;
		nUsedMode			= 1;
		nRevID				= 0;
		nFileRevID			= 0;
		nLanID				= 0;
		nPatchType			= 0;

		nFileSize			= 0;
	}

	UINT32		nID;
	UINT32		nUsedMode;
	UINT32		nRevID;
	UINT32		nFileRevID;
	UINT32		nLanID;
	UINT32		nPatchType;

	String		strFileName;
	String		strFileHash;
	UINT32		nFileSize;

	String		strDownURL;

}DB_PTN_PATCH_FILE, *PDB_PTN_PATCH_FILE;

typedef list<DB_PTN_PATCH_FILE>			TListDBPtnPatchFile;
typedef TListDBPtnPatchFile::iterator	TListDBPtnPatchFileItor;

typedef map<UINT32, DB_PTN_PATCH_FILE>	TMapDBPtnPatchFile;
typedef TMapDBPtnPatchFile::iterator	TMapDBPtnPatchFileItor;

#endif /*DB_PTN_PATCH_FILE_H_5DBB6BFC_032B_42a5_81C6_C86A909331BE*/



