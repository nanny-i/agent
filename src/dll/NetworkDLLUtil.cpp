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

// NetworkDLLUtil.cpp: implementation of the CNetworkDLLUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "com_struct.h"
#include "NetworkDLLUtil.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNetworkDLLUtil*	t_NetworkDLLUtil;

CNetworkDLLUtil::CNetworkDLLUtil()
{
	m_hDLL	= NULL;
}
//---------------------------------------------------------------------

CNetworkDLLUtil::~CNetworkDLLUtil()
{
	if(m_hDLL)
	{
		FreeLibrary(m_hDLL);
		m_hDLL	= NULL;
	}
}
//---------------------------------------------------------------------

INT32		CNetworkDLLUtil::LoadLibraryExt(LPCSTR lpDLLName)
{
	if(m_hDLL)
		return 0;

	if(lpDLLName == NULL)
	{
		WriteLogE("[LoadLibraryExt] invalid input data");
		return -1;
	}
	
	m_hDLL = LoadLibrary(lpDLLName);
	if(m_hDLL == NULL)
	{
		WriteLogE("[LoadLibraryExt] fail to load library %s [%d]", lpDLLName, errno);
		return -1;
	}

	f_GetInterfaceCount = (GetInterfaceCountType)GetProcAddress(m_hDLL, "GetInterfaceCount");
	if(f_GetInterfaceCount == 0)
	{
		WriteLogE("[LoadLibraryExt] fail to get GetInterfaceCount address [%d]", errno);
		FreeLibrary(m_hDLL);
		m_hDLL	= NULL;
		return -2;
	}

	f_GetIPAddr = (GetIPAddrType)GetProcAddress(m_hDLL, "GetIPAddr");
	if(f_GetIPAddr == 0)
	{
		WriteLogE("[LoadLibraryExt] fail to get GetIPAddr address [%d]", errno);
		FreeLibrary(m_hDLL);
		m_hDLL	= NULL;
		return -3;
	}

	f_GetMacAddress = (GetMacAddressType)GetProcAddress(m_hDLL, "GetMacAddress");
	if(f_GetMacAddress == 0)
	{
		WriteLogE("[LoadLibraryExt] fail to get GetMacAddress address [%d]", errno);
		FreeLibrary(m_hDLL);
		m_hDLL	= NULL;
		return -4;
	}

	f_GetInterfaceSubNet = (GetInterfaceSubNetType)GetProcAddress(m_hDLL, "GetInterfaceSubNet");
	if(f_GetInterfaceSubNet == 0)
	{
		WriteLogE("[LoadLibraryExt] fail to get GetInterfaceSubNet address [%d]", errno);
		FreeLibrary(m_hDLL);
		m_hDLL	= NULL;
		return -5;
	}

	f_GetNetWorkGroup = (GetNetWorkGroupType)GetProcAddress(m_hDLL, "GetNetWorkGroup");
	if(f_GetNetWorkGroup == 0)
	{
		WriteLogE("[LoadLibraryExt] fail to get GetNetWorkGroup address [%d]", errno);
		FreeLibrary(m_hDLL);
		m_hDLL	= NULL;
		return -6;
	}

	f_GetHostByNameAddress = (GetHostByNameAddressType)GetProcAddress(m_hDLL, "GetHostByNameAddress");
	if(f_GetHostByNameAddress == 0)
	{
		WriteLogE("[LoadLibrarySo_Ext] fail to get GetHostByNameAddress address [%d]", errno);
		FreeLibrary(m_hDLL);
		m_hDLL	= NULL;
		return -7;
	}

	f_GetSubNetByAddress = (GetSubNetByAddressType)GetProcAddress(m_hDLL, "GetSubNetByAddress");
	if(f_GetSubNetByAddress == 0)
	{
		WriteLogE("[LoadLibraryExt] fail to get GetSubNetByAddress address [%d]", errno);
		FreeLibrary(m_hDLL);
		m_hDLL	= NULL;
		return -8;
	}

	return 0;
}
//---------------------------------------------------------------------

INT32   CNetworkDLLUtil::GetInterfaceCount()
{
	if(!m_hDLL)	return -100;

	return f_GetInterfaceCount();
}
//---------------------------------------------------------------------

INT32   CNetworkDLLUtil::GetIPAddr(INT32 nIndex, LPSTR buf, INT32 bufLen)
{
	if(!m_hDLL)	return -100;

	return f_GetIPAddr(nIndex, buf, bufLen);
}
//---------------------------------------------------------------------

INT32   CNetworkDLLUtil::GetMacAddress(INT32 nIndex, LPSTR buf, INT32 bufLen)
{
	if(!m_hDLL)	return -100;

	return f_GetMacAddress(nIndex, buf, bufLen);
}
//---------------------------------------------------------------------

INT32   CNetworkDLLUtil::GetInterfaceSubNet(INT32 nIndex, LPSTR buf, INT32 bufLen)
{
	if(!m_hDLL)	return -100;

	return f_GetInterfaceSubNet(nIndex, buf, bufLen);
}
//---------------------------------------------------------------------

INT32	CNetworkDLLUtil::GetNetWorkGroup(LPSTR buf, INT32 nBufLen)
{
	if(!m_hDLL)	return -100;

	return f_GetNetWorkGroup(buf, nBufLen);
}
//---------------------------------------------------------------------

INT32	CNetworkDLLUtil::GetHostByNameAddress(LPSTR buf, INT32 nBufLen) 
{
	if(!m_hDLL)	return -100;

	return f_GetHostByNameAddress(buf, nBufLen);
}
//---------------------------------------------------------------------

INT32	CNetworkDLLUtil::GetSubNetByAddress(LPTSTR lpAddress, LPSTR lpSubNet, INT32 nLen) 
{
	if(!m_hDLL)	return -100;

	return f_GetSubNetByAddress(lpAddress, lpSubNet, nLen);
}
//---------------------------------------------------------------------

