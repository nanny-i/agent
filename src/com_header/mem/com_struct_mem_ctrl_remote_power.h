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

#ifndef MEM_CTRL_REMOTE_POWER_H_4D39CDDB_CTL_E289_4d56_9F98_FE42776F4467
#define MEM_CTRL_REMOTE_POWER_H_4D39CDDB_CTL_E289_4d56_9F98_FE42776F4467

typedef struct _mem_ctrl_remote_power
{
	_mem_ctrl_remote_power()
	{
		nControlType		= 0;
		nAreaType			= 0;
	}

	UINT32			nControlType;	
	UINT32			nAreaType;
}MEM_CTRL_REMOTE_POWER, *PMEM_CTRL_REMOTE_POWER;

typedef list<MEM_CTRL_REMOTE_POWER>				TListMemCtrlRemotePower;
typedef TListMemCtrlRemotePower::iterator		TListMemCtrlRemotePowerItor;

#endif //MEM_CTRL_COMMON_REMOTE_POWER_H_4D39CDDB_CTL_E289_4d56_9F98_FE42776F4467



