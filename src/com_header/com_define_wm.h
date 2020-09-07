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


#ifndef COM_DEFINE_WM_H_938EF200_F60B_452A_BD30_A10E8507EDCC
#define COM_DEFINE_WM_H_938EF200_F60B_452A_BD30_A10E8507EDCC


#define		SENDMESSAGE_DEFAULT_WAITING				15000

#define		WM_GLOBAL_CLT_LGN_SOCK_EVT				WM_USER + 0x0001
#define		WM_GLOBAL_CLT_MGR_SOCK_EVT				WM_USER + 0x0002
#define		WM_GLOBAL_CLT_UDT_SOCK_EVT				WM_USER + 0x0003
#define		WM_GLOBAL_SVR_LINK_SOCK_EVT				WM_USER + 0x0004

#define		WM_GLOBAL_TIMER_EVT				        WM_USER + 0x0010
#define		WM_GLOBAL_TIMER_EVT_SUB					WM_USER + 0x0011
#define     WM_AGENT_INITIALIZE						WM_USER + 0x0012
#define     WM_AGENT_AUTO_DESTORY					WM_USER + 0x0013
#define     WM_AGENT_TERMINATED						WM_USER + 0x0014
#define		WM_GLOBAL_PKT_OP_EVT					WM_USER + 0x0015

#define		WM_GLOBAL_FDL_NOTIFY					WM_USER + 0x0020
#define		WM_GLOBAL_KERNEL_LOG_EVT				WM_USER + 0x0030
#define		WM_GLOBAL_THREAD_LOG_EVT				WM_USER + 0x0031
#define		WM_GLOBAL_THREAD_END					WM_USER + 0x0040
#define		WM_GLOBAL_THREAD_FA_CLEAR_UNIT			WM_USER + 0x0041
#define		WM_GLOBAL_THREAD_FA_CLEAR_END			WM_USER + 0x0042
#define		WM_GLOBAL_THREAD_FA_CLEAR_PROGRESS		WM_USER + 0x0043
#define		WM_GLOBAL_THREAD_WORK_EXECUTE			WM_USER + 0x0044
#define		WM_GLOBAL_THREAD_PMS_WORK_NEW			WM_USER + 0x0045
#define		WM_GLOBAL_THREAD_PMS_WORK_OLD			WM_USER + 0x0046
#define		WM_GLOBAL_THREAD_VULN_PMS_WORK_NEW		WM_USER + 0x0047


#define		WM_GLOBAL_MEDIA_CHANGED					WM_USER + 0x0100

#define		WM_GLOBAL_DEBUG_MSG_TEST				WM_USER + 0x0500


#endif	//COM_DEFINE_WM_H_938EF200_F60B_452A_BD30_A10E8507EDCC
