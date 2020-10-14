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

#ifndef _COM_STRUCT_PO_FA_INOTIFY_FILE_H__
#define _COM_STRUCT_PO_FA_INOTIFY_FILE_H__

typedef struct _db_log_notify
{
    _db_log_notify()
    {
        nID 	= 0;
    }

	UINT32				nID ;
	UINT32				nUsedFlag;
	UINT32				nRegDate;
	UINT32				nOrderID;

	String				strNotifyFilePath;
}DB_LOG_NOTIFY_FILE, *PDB_LOG_NOTIFY_FILE;

typedef list<DB_LOG_NOTIFY_FILE>				TListLogNotifyFile;
typedef TListLogNotifyFile::iterator			TListLogNotifyFileItor;

typedef map<UINT32, DB_LOG_NOTIFY_FILE>			TMapLogNotifyFile;
typedef TMapLogNotifyFile::iterator			TMapLogNotifyFileItor;

#endif //_COM_STRUCT_PO_FA_INOTIFY_FILE_H__



