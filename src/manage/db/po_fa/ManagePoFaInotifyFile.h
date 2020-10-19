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

//---------------------------------------------------------------------------

#ifndef _MANAGE_PO_FA_INOTIFY_FILE_H__
#define _MANAGE_PO_FA_INOTIFY_FILE_H__
//---------------------------------------------------------------------------

class CManagePoFaInotifyFile : public CManageBase<DB_LOG_NOTIFY_FILE>
{
public:
	INT32		LoadDBMS();
	INT32		GetInotifyPathCount();
	INT32		FindID(char *pPath);
	INT32		InsertInotifyPath(PNOTIFY_PATH pNotifyPath);
	INT32		DeleteInotifyPath(PNOTIFY_PATH pNotifyPath);
	INT32		GetAllInotifyPath(PNOTIFY_PATH pNotifyPath, INT32 nTotalCount);
	VOID		DelAllInotifyPath(PNOTIFY_PATH pNotifyPath, INT32 nCount);
public:
	CManagePoFaInotifyFile();
    ~CManagePoFaInotifyFile();

};

extern CManagePoFaInotifyFile*	t_ManagePoFaInotifyFile;

#endif /*_MANAGE_PO_FA_INOTIFY_FILE_H__*/
