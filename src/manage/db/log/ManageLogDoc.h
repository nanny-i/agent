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

#ifndef ManageLogDocH
#define ManageLogDocH
//---------------------------------------------------------------------------

class CManageLogDoc : public CManageBase<DB_LOG_DOC>
{
public:
	INT32		LoadDBMS();

public:
	INT32					AddLogDoc(DB_LOG_DOC&	dld);
    INT32					EditLogDoc(DB_LOG_DOC&	dld);
    INT32					DelLogDoc(UINT32 nID);

public:
	INT32					AddLogDocWithHost(DB_LOG_DOC&	dld);
	INT32					EditLogDocWithHost(DB_LOG_DOC&	dld);

public:
	INT32					IsExistLogDoc(DB_LOG_DOC&	dld);
	PDB_LOG_DOC				GetExistLogDoc(DB_LOG_DOC&	dld);

	INT32					IsExistLogDocByBkName(String strBkName, UINT32 nChkRmTime = 0, UINT32 nChkBkTime = 0);

public:
	INT32					SetPkt(MemToken& SendToken);
	INT32					SetPkt(PDB_LOG_DOC pdld, MemToken& SendToken);
	INT32					GetPkt(MemToken& RecvToken, DB_LOG_DOC& dld);

	INT32					SetPkt_Link(MemToken& SendToken);
	INT32					SetPkt_Link(PDB_LOG_DOC pdld, MemToken& SendToken);
	INT32					GetPkt_Link(MemToken& RecvToken, DB_LOG_DOC& dld);

public:
	CManageLogDoc();
    ~CManageLogDoc();

};

extern CManageLogDoc*	t_ManageLogDoc;

#endif
