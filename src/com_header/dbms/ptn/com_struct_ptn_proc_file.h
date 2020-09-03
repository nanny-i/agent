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

#ifndef DB_PTN_PROC_FILE_H_348683B5_F316_4a4d_842D_63E68B189A5D
#define DB_PTN_PROC_FILE_H_348683B5_F316_4a4d_842D_63E68B189A5D

typedef struct _db_ptn_proc_file
{
    _db_ptn_proc_file()
    {
        _init();        
    }

	void _init()
	{
		nID 				= 0;
		nRegDate			= 0;
		nUsedMode			= 0;

		nFileSize			= 0;

		nOsID				= 0;
		nBuildSN			= 0;

		nPeType				= 0;
		nPeBit				= 0;

		nPtnSrcType			= 0;
		nPtnType			= 0;
		nPtnRisk			= 0;

		nChecked			= 0;
	}
  
	UINT32		nID;
	UINT32		nRegDate;
	UINT32		nUsedMode;

	String		strFeKey;
	String		strFileHash;

	String		strFilePath;
	String		strFileName;
	String		strFileDescr;
	String		strFileVersion;
	UINT32		nFileSize;
	String		strPubName;
	String		strPubSN;
	String		strCntName;
	String		strCntSN;
	String		strPublisherName;
	String		strProductName;
	UINT64		nOsID;
	UINT32		nBuildSN;
	UINT32		nPeType;
	UINT32		nPeBit;

	UINT32		nPtnSrcType;
	UINT32		nPtnType;
	UINT32		nPtnRisk;

	UINT32		nChecked;

}DB_PTN_PROC_FILE, *PDB_PTN_PROC_FILE;

typedef list<DB_PTN_PROC_FILE>					TListDBPtnProcFile;
typedef TListDBPtnProcFile::iterator			TListDBPtnProcFileItor;

typedef map<UINT32, DB_PTN_PROC_FILE>			TMapDBPtnProcFile;
typedef TMapDBPtnProcFile::iterator				TMapDBPtnProcFileItor;
typedef TMapDBPtnProcFile::reverse_iterator		TMapDBPtnProcFileRItor;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

#endif //DB_PTN_PROC_FILE_H_348683B5_F316_4a4d_842D_63E68B189A5D



