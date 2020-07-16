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


#ifndef COM_DEFINE_DB_PO_HOST_CLEAR_H_938EF200_F60B_452A_BD30_A10E8507EDCC
#define COM_DEFINE_DB_PO_HOST_CLEAR_H_938EF200_F60B_452A_BD30_A10E8507EDCC

//-------------------------------------------------------------------
//host clear [ nChkType ]

#define SS_PO_HOST_CLEAR_CHECK_OPTION_DISCON_DT				0x00000001 // 접근 종료 날짜
#define SS_PO_HOST_CLEAR_CHECK_OPTION_IP_ADDRESS			0x00000002 // 에이전트 주소 중복
//#define SS_PO_HOST_CLEAR_CHECK_OPTION_MAC_ADDRESS			0x00000004 // 에이전트 Mac 주소 중복

//-------------------------------------------------------------------
//host clear [ nDisposalType ]

#define SS_PO_HOST_CLEAR_DISPOSAL_TYPE_SLEEP				0x00000001 // 휴면 처리만 사용
#define SS_PO_HOST_CLEAR_DISPOSAL_TYPE_REMOVE				0x00000002 // 삭제 처리만 사용
#define SS_PO_HOST_CLEAR_DISPOSAL_TYPE_SLEEP_AND_REMOVE		0x00000004 // 휴면 후 삭제 처리 사용

//--------------------------------------------------------------------
#endif	//COM_DEFINE_DB_PO_HOST_CLEAR_H_938EF200_F60B_452A_BD30_A10E8507EDCC