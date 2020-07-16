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

#ifndef DB_PO_POWER_UNIT_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467
#define DB_PO_POWER_UNIT_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467

typedef struct _db_po_power_unit
{
	_db_po_power_unit()
	{
		nScPeriodType		= 0;
		nScStartTime		= 0;
		nScEndTime			= 0;
		nCtlMode			= 0;
		nCtlWaitTime		= 0;

		nRunWaitTime		= 0;
	}

	DB_PO_HEADER			tDPH;

	UINT32					nScPeriodType;
	UINT32					nScStartTime;
	UINT32					nScEndTime;
	UINT32					nCtlMode;
	UINT32					nCtlWaitTime;

	UINT32					nRunWaitTime;

}DB_PO_POWER_UNIT, *PDB_PO_POWER_UNIT;

typedef list<DB_PO_POWER_UNIT>			TListDBPoPowerUnit;
typedef TListDBPoPowerUnit::iterator	TListDBPoPowerUnitItor;

typedef map<UINT32, DB_PO_POWER_UNIT>	TMapDBPoPowerUnit;
typedef TMapDBPoPowerUnit::iterator		TMapDBPoPowerUnitItor;

#endif //DB_PO_POWER_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467



