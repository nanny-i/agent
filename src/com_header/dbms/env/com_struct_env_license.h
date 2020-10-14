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

#ifndef DB_ENV_LICENSE_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467
#define DB_ENV_LICENSE_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467

typedef struct _db_env_license
{
	_db_env_license()
	{		
	}

	DB_PO_HEADER		tDPH;

	String				strLicenseKey;
	UINT32				nSupportOs;
	TMapID64			tRightPackageMap;
	TMapID64			tRightClassMap;
	TMapID64			tRightPolicyMap;
	TMapID64			tRightControlMap;

}DB_ENV_LICENSE, *PDB_ENV_LICENSE;

typedef list<DB_ENV_LICENSE>				TListDBEnvLicense;
typedef TListDBEnvLicense::iterator			TListDBEnvLicenseItor;

typedef map<UINT32, DB_ENV_LICENSE>			TMapDBEnvLicense;
typedef TMapDBEnvLicense::iterator			TMapDBEnvLicenseItor;

#endif //DB_ENV_LICENSE_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467



