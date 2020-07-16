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


#ifndef COM_DEFINE_DB_PO_FE_PTN_LO_H_938EF200_F60B_452A_BD30_A10E8507EDCC
#define COM_DEFINE_DB_PO_FE_PTN_LO_H_938EF200_F60B_452A_BD30_A10E8507EDCC

//-------------------------------------------------------------------
//block type
#define SS_PO_FE_PTN_LO_PTN_TYPE_NORMAL					0
#define SS_PO_FE_PTN_LO_PTN_TYPE_STANDARD				1

#define SS_PO_FE_PTN_LO_PTN_RANGE_TYPE_ALL_FILE			0x00000000 // 
#define SS_PO_FE_PTN_LO_PTN_RANGE_TYPE_CUR_EXECUTE		0x00000001 // 
#define SS_PO_FE_PTN_LO_PTN_RANGE_TYPE_SYS_DRIVE		0x00000002 // 

#define SS_PO_FE_PTN_LO_PTN_OBJECT_TYPE_EXECUTE			0x00000001 // 
#define SS_PO_FE_PTN_LO_PTN_OBJECT_TYPE_DLL				0x00000002 // 
#define SS_PO_FE_PTN_LO_PTN_OBJECT_TYPE_ALL				(SS_PO_FE_PTN_LO_PTN_OBJECT_TYPE_EXECUTE | SS_PO_FE_PTN_LO_PTN_OBJECT_TYPE_DLL) // 

#define SS_PO_FE_PTN_LO_NEW_FILE_SEND_TYPE_NONE			0x00000000 // 
#define SS_PO_FE_PTN_LO_NEW_FILE_SEND_TYPE_INFO			0x00000001 // 
#define SS_PO_FE_PTN_LO_NEW_FILE_SEND_TYPE_FILE			0x00000002 // 


//--------------------------------------------------------------------
#endif	//COM_DEFINE_DB_PO_FE_PTN_LO_H_938EF200_F60B_452A_BD30_A10E8507EDCC