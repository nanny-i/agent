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


#ifndef COM_DEFINE_DN_FILE_H_938EF200_F60B_452A_BD30_A10E8507EDCC
#define COM_DEFINE_DN_FILE_H_938EF200_F60B_452A_BD30_A10E8507EDCC

//-------------------------------------------------------------------

typedef enum _SS_DN_FILE_TYPE
{
	SS_DN_FILE_TYPE_UPDATE			= 1,
	SS_DN_FILE_TYPE_DEPLOY,
	SS_DN_FILE_TYPE_WPTN_GBL,
	SS_DN_FILE_TYPE_WPTN_GWL,
	SS_DN_FILE_TYPE_WPTN_GBO,
	SS_DN_FILE_TYPE_WPTN_GWO,
	
	SS_DN_FILE_TYPE_PPTN_ASP,
	SS_DN_FILE_TYPE_PPTN_WSUS,
	SS_DN_FILE_TYPE_PPTN_PATCH,
	SS_DN_FILE_TYPE_PPTN_PATCH_UTIL,
	SS_DN_FILE_TYPE_PPTN_DEPLOY,

	SS_DN_FILE_TYPE_VPTN_ASV,
	SS_DN_FILE_TYPE_VPTN_WSUS,
	SS_DN_FILE_TYPE_VPTN_PATCH,
	SS_DN_FILE_TYPE_VPTN_DEPLOY,

}SS_DN_FILE_TYPE;


//-------------------------------------------------------------------





#endif	//COM_DEFINE_DN_FILE_H_938EF200_F60B_452A_BD30_A10E8507EDCC