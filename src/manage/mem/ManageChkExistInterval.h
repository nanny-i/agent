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

#ifndef ManageChkExistIntervalH
#define ManageChkExistIntervalH
//---------------------------------------------------------------------------

class CManageChkExistInterval : public CManageBase<MEM_CHK_EXIST_INTERVAL>
{
private:
	CMutexExt			m_tMutex;
	UINT32				m_nGlobalID;

public:
	INT32				InitChkExistInterval();
	INT32				AddChkExistInterval(MEM_CHK_EXIST_INTERVAL tMCEI);
	INT32				SetChkExistStatus(String strChkName, UINT32 nStatus);

public:
	INT32				IsChkExistStatus(String strChkName);

public:
	CManageChkExistInterval();
    ~CManageChkExistInterval();

};

extern CManageChkExistInterval	t_ManageChkExistInterval;

#endif
