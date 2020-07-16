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


#ifndef COM_DEFINE_TASK_SCHEDULE_INFO_H_938EF200_F60B_452A_BD30_A10E8507EDCC
#define COM_DEFINE_TASK_SCHEDULE_INFO_H_938EF200_F60B_452A_BD30_A10E8507EDCC

//-------------------------------------------------------------------
// task schedule excute wait mode

#define TS_EXCUTE_WAIT_MODE_EXIST_TASK					1	//  작업 스케줄러가 존재할때까지 대기.
#define TS_EXCUTE_WAIT_MODE_EXCUTE_PROC					2	//  작업 스케줄러에 등록된 프로세스가 실행 될때까지 대기
#define TS_EXCUTE_WAIT_MODE_EXCUTE_PROC_CHILD			3	//  작업 스케줄러에 등록된 프로세스가 실행한 하위프로세스가 실행 될때까지 대기

//-------------------------------------------------------------------
// task schedule excute wait time
#define TS_EXCUTE_LIMIT_WAIT_TIME						20  // 작업 스케줄러 대기 모드 최대 대기 시간.

//-------------------------------------------------------------------
//-------------------------------------------------------------------
//-------------------------------------------------------------------
//-------------------------------------------------------------------
//-------------------------------------------------------------------
//--------------------------------------------------------------------
#endif	//COM_DEFINE_TASK_SCHEDULE_INFO_H_938EF200_F60B_452A_BD30_A10E8507EDCC