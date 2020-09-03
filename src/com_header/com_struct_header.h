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


#ifndef _COM_STRUCT_HEADER_H__
#define _COM_STRUCT_HEADER_H__

typedef struct _dl_svr_info
{
	_dl_svr_info()
	{
		nPort		= 0;
	}
	String			strAddress;
	UINT32			nPort;
}DL_SVR_INFO, *PDL_SVR_INFO;

typedef list<DL_SVR_INFO>			TListDLSvrInfo;
typedef TListDLSvrInfo::iterator	TListDLSvrInfoItor;

//**********************************************************************************************//

typedef list<UINT32>			TListID;
typedef TListID::iterator		TListIDItor;

typedef map<UINT32, UINT32>		TMapID;
typedef TMapID::iterator		TMapIDItor;

typedef list<String>			TListStr;
typedef TListStr::iterator		TListStrItor;
//**********************************************************************************************//

#endif //_COM_STRUCT_HEADER_H__