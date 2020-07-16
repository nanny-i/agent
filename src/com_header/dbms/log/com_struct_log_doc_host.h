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

#ifndef DB_LOG_DOC_HOST_H_348683B5_F316_4a4d_842D_63E68B189A5D
#define DB_LOG_DOC_HOST_H_348683B5_F316_4a4d_842D_63E68B189A5D

typedef struct _db_log_doc_host
{
    _db_log_doc_host()
    {
        _init();        
    }

	void _init()
	{
		nID 				= 0;
		nUsedFlag			= STATUS_USED_MODE_ON;
		nLogID				= 0;
		nEvtTime 			= 0;		
	}
  
	UINT32		nID;
	UINT32		nUsedFlag;
	UINT32		nLogID;
	UINT32		nEvtTime;

}DB_LOG_DOC_HOST, *PDB_LOG_DOC_HOST;

typedef list<DB_LOG_DOC_HOST>					TListDBLogDocHost;
typedef TListDBLogDocHost::iterator				TListDBLogDocHostItor;

typedef map<UINT32, DB_LOG_DOC_HOST>			TMapDBLogDocHost;
typedef TMapDBLogDocHost::iterator				TMapDBLogDocHostItor;
typedef TMapDBLogDocHost::reverse_iterator		TMapDBLogDocHostRItor;

#endif //DB_LOG_DOC_HOST_H_348683B5_F316_4a4d_842D_63E68B189A5D



