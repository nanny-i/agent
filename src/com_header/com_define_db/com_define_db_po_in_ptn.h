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


#ifndef COM_DEFINE_DB_PO_IN_PTN_H_938EF200_F60B_452A_BD30_A10E8507EDCC
#define COM_DEFINE_DB_PO_IN_PTN_H_938EF200_F60B_452A_BD30_A10E8507EDCC

//-------------------------------------------------------------------

#define SS_PO_IN_PTN_OBJECT_TYPE_EXECUTE			0x00000001 // 
#define SS_PO_IN_PTN_OBJECT_TYPE_DLL				0x00000002 //
#define SS_PO_IN_PTN_OBJECT_TYPE_ALL				(SS_PO_IN_PTN_OBJECT_TYPE_EXECUTE | SS_PO_IN_PTN_OBJECT_TYPE_DLL) // 

#define SS_PO_IN_PTN_REALTIME_TARGET_TYPE_SVR		0
#define SS_PO_IN_PTN_REALTIME_TARGET_TYPE_AGT		1

#define SS_PO_IN_PTN_REGISTER_TYPE_UNKNOW			0x00000000 // 
#define SS_PO_IN_PTN_REGISTER_TYPE_AUTO				0x00000001 // 
#define SS_PO_IN_PTN_REGISTER_TYPE_ADMIN_ADD		0x00000002 // 
#define SS_PO_IN_PTN_REGISTER_TYPE_ADMIN_DEL		0x00000003 // 

#define SS_PO_IN_PTN_AGE_FILE_MODE_NONE				0x00000000 //
#define SS_PO_IN_PTN_AGE_FILE_MODE_INITIAL			0x00000001 // 
#define SS_PO_IN_PTN_AGE_FILE_MODE_MERGE			0x00000002 //

#define SS_PO_IN_PTN_NOTIFY_TYPE_NONE				0x00000000 // 
#define SS_PO_IN_PTN_NOTIFY_TYPE_BLOCK				0x00000001 // 
#define SS_PO_IN_PTN_NOTIFY_TYPE_REQ_ALLOW			0x00000002 // 
#define SS_PO_IN_PTN_NOTIFY_TYPE_CHG_STATUS			0x00000004 // 
#define SS_PO_IN_PTN_NOTIFY_TYPE_RES_ALLOW			0x00000008 // 
#define SS_PO_IN_PTN_NOTIFY_TYPE_RES_DENY			0x00000010 // 
#define SS_PO_IN_PTN_NOTIFY_TYPE_END_TIME			0x00000020 // 

//--------------------------------------------------------------------
#endif	//COM_DEFINE_DB_PO_IN_PTN_PTN_OP_H_938EF200_F60B_452A_BD30_A10E8507EDCC