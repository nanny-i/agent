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

#ifndef _COM_STRUCT_PO_FA_DEL_FILE_AFTER_BOOT__
#define _COM_STRUCT_PO_FA_DEL_FILE_AFTER_BOOT__

typedef struct _db_del_file_after_boot
{
    _db_del_file_after_boot()
    {
        nID 	= 0;
    }

    UINT32		nID;
    String		strDelFilePath;
}DB_DEL_FILE_AFTER_BOOT, *PDB_DEL_FILE_AFTER_BOOT;

typedef list<DB_DEL_FILE_AFTER_BOOT>				TListDelFileAfterBoot;
typedef TListDelFileAfterBoot::iterator				TListDelFileAfterBootItor;

typedef map<UINT32, DB_DEL_FILE_AFTER_BOOT>			TMapDelFileAfterBoot;
typedef TMapDelFileAfterBoot::iterator				TMapDelFileAfterBootItor;

#endif //_COM_STRUCT_PO_FA_DEL_FILE_AFTER_BOOT__



