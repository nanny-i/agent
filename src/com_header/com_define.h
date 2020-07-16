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


#ifndef COM_DEFINE_H_938EF200_F60B_452A_BD30_A10E8507EDCC
#define COM_DEFINE_H_938EF200_F60B_452A_BD30_A10E8507EDCC

/*
#undef  RT_MANIFEST
#define RT_MANIFEST 24
#define APP_MANIFEST 1
*/
                            
/////////////////////////////////////////////////////////////////////////
//WM define header
#include "com_define_wm.h"

//String define header
#include "com_define_string.h"

//ErrCode define header
#include "com_define_error.h"

//Socket define header
#include "com_define_socket.h"

//policy define header
#include "com_define_policy.h"

//Common status define header
#include "com_define_status.h"

//Common status event define header
#include "com_define_status_event.h"

//web server define
#include "com_define_web_svr.h"

//timer define header
#include "com_define_timer.h"

#include "com_define_db.h"
#include "com_define_mem.h"

#include "com_define_dbms.h"
#include "com_define_dbms_query.h"
//#include "com_define_dbf.h"
#include "com_define_host_auth.h"
#include "com_define_pw_mon.h"


#include "com_define_socket_thread.h"

#include "com_define_find_order_info.h"
#include "com_define_task_schedule_info.h"

/////////////////////////////////////////////////////////////////////////
// Number Define
#define	RTN_ERROR_NON_LINK_LIBRARY					-10000 
#define DEFAULT_AGENT_GUI_SESSIONKEY				0x3F3D2A37


/////////////////////////////////////////////////////////////////////////
//Environment Global ID
#define	DEFAULT_ENV_INDEX			1
#define ADMIN_INDEX_DEFAULT			1
#define GROUP_INDEX_DEFAULT			1
#define DEFAULT_POLICY_ID			1
#define DEFAULT_ID					1


#define PATH_USED_NONE		        0
#define PATH_USED_PCMS		        1
#define PATH_USED_VC		        2
#define PATH_USED_ALL		        3

#define ADMIN_RIGHT_ALL				0
#define ADMIN_RIGHT_PCMS			1
#define ADMIN_RIGHT_VC				2

#define GLOBAL_LICENSE 				"F0AC7871-0C4B-4D17-8F66-2FA88B0763CD"

namespace NS_SITE_ITEMS_TYPE
{
	enum _ITEMS_TYPE
    {
    	SITE_ITEM_TYPE_SERVER		= 1,
        SITE_ITEM_TYPE_CONSOLE,
        SITE_ITEM_TYPE_SVR_LGN,
        SITE_ITEM_TYPE_SVR_MGR,
        SITE_ITEM_TYPE_SVR_UDT,
        SITE_ITEM_TYPE_SVR_RPT
	};//enum

};
using namespace NS_SITE_ITEMS_TYPE;


#define NA_RUN_THREAD_TYPE_MAIN			0x00000001
#define NA_RUN_THREAD_TYPE_DBMS_QUERY	0x00000002


#endif	//COM_DEFINE_H_938EF200_F60B_452A_BD30_A10E8507EDCC




