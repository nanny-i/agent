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

#ifndef DB_PO_CTL_PROC_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467
#define DB_PO_CTL_PROC_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467

typedef struct _db_po_ctl_proc
{
	_db_po_ctl_proc()
	{
		nBlockMode		= 0;
	}

	DB_PO_HEADER		tDPH;

	UINT32				nBlockMode;

}DB_PO_CTL_PROC, *PDB_PO_CTL_PROC;

typedef list<DB_PO_CTL_PROC>			TListDBPoCtlProc;
typedef TListDBPoCtlProc::iterator		TListDBPoCtlProcItor;

typedef map<UINT32, DB_PO_CTL_PROC>		TMapDBPoCtlProc;
typedef TMapDBPoCtlProc::iterator		TMapDBPoCtlProcItor;

#include "com_struct_po_ctl_proc_pkg.h"
#include "com_struct_po_ctl_proc_unit.h"

#endif //DB_PO_CTL_PROC_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467



