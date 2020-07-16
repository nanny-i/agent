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

#ifndef MEM_FIND_ORDER_INFO_H_4D39CDDB_CTL_E289_4d56_9F98_FE42776F4467
#define MEM_FIND_ORDER_INFO_H_4D39CDDB_CTL_E289_4d56_9F98_FE42776F4467

typedef struct _mem_find_order_info
{
	_mem_find_order_info()
	{
		nID					= 0;
		nPoType				= 0;
		nPoID				= 0;
		nOpType				= 0;
		nNextOp				= 0;
		nNetDrv				= 0;

		nNotiPg				= 0;
		nNotiPgSend			= 0;
		nNotiPgTotal		= 0;
		nNotiPgEnd			= 0;

		nNotiTotalFind		= 0;
	}
	_mem_find_order_info(UINT32 _nID, UINT32 _nPoID, UINT32 _nOpType, UINT32 _nNextOp)
	{
		nID			= _nID;
		nPoID		= _nPoID;
		nOpType		= _nOpType;
		nNextOp		= _nNextOp;
	}

	UINT32			nID;	
	UINT64			nPoType;
	UINT32			nPoID;
	UINT32			nOpType;
	UINT32			nNextOp;
	UINT32			nNetDrv;

	UINT32			nNotiPg;
	UINT32			nNotiPgSend;
	UINT32			nNotiPgTotal;
	UINT32			nNotiPgEnd;

	UINT32			nNotiTotalFind;

}MEM_FIND_ORDER_INFO, *PMEM_FIND_ORDER_INFO;

typedef list<MEM_FIND_ORDER_INFO>				TListMemFindOrderInfo;
typedef TListMemFindOrderInfo::iterator			TListMemFindOrderInfoItor;

typedef map<UINT32, MEM_FIND_ORDER_INFO>		TMapMemFindOrderInfo;
typedef TMapMemFindOrderInfo::iterator			TMapMemFindOrderInfoItor;

#endif //MEM_FIND_ORDER_INFO_H_4D39CDDB_CTL_E289_4d56_9F98_FE42776F4467



