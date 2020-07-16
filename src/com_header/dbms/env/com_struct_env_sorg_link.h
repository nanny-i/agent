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

#ifndef DB_ENV_SORG_LINK_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467
#define DB_ENV_SORG_LINK_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467

typedef struct _db_env_sorg_link
{
	_db_env_sorg_link()
	{
		nUserCatchType		= 0;
	}

	DB_PO_HEADER		tDPH;

	UINT32				nUserCatchType;
	String				strUserCatchValue;
}DB_ENV_SORG_LINK, *PDB_ENV_SORG_LINK;

typedef list<DB_ENV_SORG_LINK>					TListDBEnvSOrgLink;
typedef TListDBEnvSOrgLink::iterator			TListDBEnvSOrgLinkItor;

typedef map<UINT32, DB_ENV_SORG_LINK>			TMapDBEnvSOrgLink;
typedef TMapDBEnvSOrgLink::iterator				TMapDBEnvSOrgLinkItor;

#endif //DB_ENV_SORG_LINK_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467



