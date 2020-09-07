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


#ifndef LogicMgrPtnVulnH
#define LogicMgrPtnVulnH
//---------------------------------------------------------------------------

class CLogicMgrPtnVuln	: public CLogicBase
{
private:
	INT32				m_nInitLogic;
	String				m_strDBFName;
	CSystemInfo			m_tSysInfo;

	INT32				m_nInitPatchUtil;
	INT32				m_nInitPatchWsus;
	INT32				m_nInitPtnDeploy;

	String				m_strWScanFileName;
	INT32				m_nIsLiveUpdate;

	volatile  LONG		m_nIsRunRBMode;

public:
	INT32	InitPtnVuln();
	INT32	FreePtnVuln();

	INT32	ReloadPtnVuln();
	INT32	IsInitLogic()	{	return m_nInitLogic;	};

	INT32	IsEnableRunMode(UINT32 nType);
	INT32	SetEnableRunMode(UINT32 nType, UINT32 nMode);

public:
	INT32	ChkPtnVulnWsus();
	INT32	ApplyPtnVulnWsus(UINT32 nID);

	INT32	GetVulnWsusStatus()						{	return m_nInitPatchWsus;		};
	INT32	SetVulnWsusStatus(UINT32 nStatus)		{	m_nInitPatchWsus = nStatus;	};
	String	GetLastVulnWsusFName()					{	return m_strWScanFileName;		};

	INT32	IsVulnWsusLive();

private:
	INT32	ChkPtnVulnWsusUnit(PDB_PTN_PATCH_WSUS pdata, UINT32 nChkOnly = 0);
	INT32	AddDpDownInfoWsus(PDB_PTN_PATCH_WSUS pdata);

public:
	INT32	InitPtnDeploy();
	INT32	ChkPtnDeploy();
	INT32	ApplyPtnDeploy(UINT32 nID);

	INT32	GetPtnDeployStatus()					{	return m_nInitPtnDeploy;	};
	INT32	SetPtnDeployStatus(UINT32 nStatus)		{	m_nInitPtnDeploy = nStatus;	};
	
private:
	INT32	ChkPtnDeployUnit(PDB_PTN_DEPLOY pdata, UINT32 nChkOnly = 0);
	INT32	AddDownloadPtnDeployUnit(PDB_PTN_DEPLOY pdata);

public:
	CLogicMgrPtnVuln();
    ~CLogicMgrPtnVuln();
};

extern CLogicMgrPtnVuln*		t_LogicMgrPtnVuln;

#endif
