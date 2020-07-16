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


#ifndef COM_DEFINE_DB_PO_IN_VULN_SCAN_H_938EF200_F60B_452A_BD30_A10E8507EDCC
#define COM_DEFINE_DB_PO_IN_VULN_SCAN_H_938EF200_F60B_452A_BD30_A10E8507EDCC

//-------------------------------------------------------------------

#define SS_PO_IN_VULN_SCAN_SCAN_TYPE_NONE					0x00000000
#define SS_PO_IN_VULN_SCAN_SCAN_TYPE_AUTO					0x00000001
#define SS_PO_IN_VULN_SCAN_SCAN_TYPE_DEMAND					0x00000002
#define SS_PO_IN_VULN_SCAN_SCAN_TYPE_ALL					(SS_PO_IN_VULN_SCAN_SCAN_TYPE_AUTO | SS_PO_IN_VULN_SCAN_SCAN_TYPE_DEMAND)
//--------------------------------------------------------------------

#define SS_PO_IN_VULN_SCAN_RESULT_NONE						0x00000000
#define SS_PO_IN_VULN_SCAN_RESULT_SAFE						0x00000001
#define SS_PO_IN_VULN_SCAN_RESULT_DANGER					0x00000010
#define SS_PO_IN_VULN_SCAN_RESULT_CHK_FAIL					0x00000100

#define SS_PO_IN_VULN_REPAIR_RESULT_SUCCESS					0x00001000
#define SS_PO_IN_VULN_REPAIR_RESULT_FAIL					0x00010000

#define SS_PO_IN_VULN_RESULT_UNKNOWN						0xFFFFFFFF

//--------------------------------------------------------------------

#endif	//COM_DEFINE_DB_PO_IN_VULN_SCAN_H_938EF200_F60B_452A_BD30_A10E8507EDCC