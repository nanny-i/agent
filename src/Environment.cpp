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


//---------------------------------------------------------------------------


#include "stdafx.h"
#include "com_struct.h"
#include "TokenString.h"
#include "Environment.h"


//---------------------------------------------------------------------------

CEnvironment *t_EnvInfo;


CEnvironment::CEnvironment()
{
	m_nContinueOP				= 1;     
	m_hThreadEvent				= 0;

	m_dwEvntThreadID			= 0;

	m_nLastOffType				= 0;
	m_nLastOffTime				= 0;
	m_nTsDebugMode				= 0;

	t_RegUtil.SetRootPath(STR_REG_DEFAULT_SVC_PATH);

	m_nHostSysType				= ASI_SYSTEM_OS_TYPE_ALL;
}
//---------------------------------------------------------------------------

CEnvironment::~CEnvironment()
{

}
//---------------------------------------------------------------------------

INT32       CEnvironment::LoadEnv()
{  
	INT32 nRtn = 0;

	if((nRtn = LoadEnv_Local()) != 0)
	{
		WriteLogE("not find reg_value : local information [%d]", nRtn);
		return nRtn;
	}

	if((nRtn = LoadEnv_Con()) != 0)
	{
		WriteLogE("not find reg_value : con information [%d]", nRtn);
		return nRtn;
	}

	if((nRtn = LoadEnv_DB()) != 0)
	{
		WriteLogE("not find reg_value : db information [%d]", nRtn);
		return nRtn;
	}

	t_RegUtil.SetRootPath(STR_REG_DEFAULT_SVC_PATH);
	return 0;
}
//---------------------------------------------------------------------------

INT32       CEnvironment::LoadEnv_Local()
{  
	INT32 nRtn = 0;
	INT32 nLen = 0;

	memset(m_pszBuf, 0, CHAR_MAX_SIZE); 

	t_RegUtil.SetRootPath(STR_REG_DEFAULT_SVC_LOCAL_PATH);

	nRtn = t_RegUtil.RegReadString(HKEY_LOCAL_MACHINE, "", "root_path", m_pszBuf, CHAR_MAX_SIZE);
	if(nRtn != 0)
	{
		WriteLogE("fail to load local env [%d]", nRtn);
		return -1;
	}
	m_pszBuf[CHAR_MAX_SIZE-1] = 0;
	nLen = strlen(m_pszBuf);
	if(nLen < 1)
	{
		WriteLogE("invalid root path");
		return -2;
	}
	
	if(m_pszBuf[nLen-1] == '/')
	{
		m_pszBuf[nLen-1] = 0;
	}

	m_strRootPath = SPrintf("%s/%s", m_pszBuf, NANNY_AGENT_DIR);

	m_strUtilPath = SPrintf("%s/%s", m_pszBuf, NANNY_UTIL_DIR);

	{
		m_strLogPath = SPrintf("%s/log", m_strRootPath.c_str());
		CreateDirectory(m_strLogPath.c_str(), NULL);
		SetLogFileInfo((char *)m_strLogPath.c_str(), "/nanny_agt_sys_log_");
	}
	
	{
		m_strDLLPath = SPrintf("%s/dll", m_strRootPath.c_str());
		m_strPemCertFileName = SPrintf("%s/pem/nanny_agent_cert.pem", m_strRootPath.c_str());
		m_strPemKeyFileName = SPrintf("%s/pem/nanny_agent_key.pem", m_strRootPath.c_str());
	}

	if(t_RegUtil.RegReadString(HKEY_LOCAL_MACHINE, "", "host_key", m_pszBuf, CHAR_MAX_SIZE))
	{
		strncpy(m_pszBuf, GetGUID().c_str(), CHAR_MAX_SIZE-1);
		t_RegUtil.RegWriteString(HKEY_LOCAL_MACHINE, "", "host_key", m_pszBuf);
	}
	m_strHostKey = m_pszBuf;

	if(t_RegUtil.RegReadString(HKEY_LOCAL_MACHINE, "", "host_bin_ver", m_pszBuf, CHAR_MAX_SIZE))
	{
		strncpy(m_pszBuf, "2.0.0.1", CHAR_MAX_SIZE-1);
		t_RegUtil.RegWriteString(HKEY_LOCAL_MACHINE, "", "host_bin_ver", m_pszBuf);
	}
	m_strHostBinVer = m_pszBuf;

	if(t_RegUtil.RegReadString(HKEY_LOCAL_MACHINE, "", "host_ptn_ver", m_pszBuf, CHAR_MAX_SIZE))
	{
		strncpy(m_pszBuf, "200101", CHAR_MAX_SIZE-1);
		t_RegUtil.RegWriteString(HKEY_LOCAL_MACHINE, "", "host_ptn_ver", m_pszBuf);
	}
	m_strHostPtnVer = m_pszBuf;

	if(t_RegUtil.RegReadInt(HKEY_LOCAL_MACHINE, "", "host_reg_time", m_nValue))
	{
		m_nValue = 0;
		t_RegUtil.RegWriteInt(HKEY_LOCAL_MACHINE, "", "host_reg_time", m_nValue);
	}
	m_nHostRegTime = m_nValue;

	if(t_RegUtil.RegReadInt(HKEY_LOCAL_MACHINE, "", "boot_chk_time", m_nValue))
	{
		m_nValue = 0;
		t_RegUtil.RegWriteInt(HKEY_LOCAL_MACHINE, "", "boot_chk_time", m_nValue);
	}
	m_nBootChkTime = m_nValue;

	t_RegUtil.SetRootPath(STR_REG_DEFAULT_SVC_PATH);
	return 0;
}
//---------------------------------------------------------------------------

INT32		CEnvironment::LoadEnv_Con()
{
	INT32 nRtn = 0;
	
	memset(m_pszBuf, 0, CHAR_MAX_SIZE); 

	t_RegUtil.SetRootPath(STR_REG_DEFAULT_SVC_CON_PATH);

	nRtn = t_RegUtil.RegReadString(HKEY_LOCAL_MACHINE, "", "lgn_svr_list", m_pszBuf, CHAR_MAX_SIZE);
	if(nRtn != 0)
	{
		WriteLogE("fail to get lgn svr list [%d]", nRtn);
		return -1;
	}
	m_strLgnSvrInfoList = m_pszBuf;
	

	m_nLgnSvrInfoListMode = 0;
	if(t_RegUtil.RegReadInt(HKEY_LOCAL_MACHINE, "", "lgn_svr_list_mode", m_nValue))
	{
		m_nValue = 0;
		t_RegUtil.RegWriteInt(HKEY_LOCAL_MACHINE, "", "lgn_svr_list_mode", m_nValue);
	}
	m_nLgnSvrInfoListMode = m_nValue;	

	if(t_RegUtil.RegReadInt(HKEY_LOCAL_MACHINE, "", "remain_sock_log", m_nValue))
	{
		m_nValue = 1;
		t_RegUtil.RegWriteInt(HKEY_LOCAL_MACHINE, "", "remain_sock_log", m_nValue);
	}
	m_nRemainSockLog = m_nValue;	

	if(t_RegUtil.RegReadInt(HKEY_LOCAL_MACHINE, "", "dl_ptp_port", m_nValue))
	{
		m_nValue = OPEN_PORT_TYPE_AGT_PTOP;
		t_RegUtil.RegWriteInt(HKEY_LOCAL_MACHINE, "", "dl_ptp_port", m_nValue);
	}
	m_nDLPTPPort = m_nValue;	
	
	if(t_RegUtil.RegReadInt(HKEY_LOCAL_MACHINE, "", "if_port", m_nValue))
	{
		m_nValue = OPEN_PORT_TYPE_AGT_INTERFACE;
		t_RegUtil.RegWriteInt(HKEY_LOCAL_MACHINE, "", "if_port", m_nValue);
	}
	m_nIFPort = m_nValue;	

	if(t_RegUtil.RegReadString(HKEY_LOCAL_MACHINE, "", "logical_mac_info", m_pszBuf, CHAR_MAX_SIZE) == 0)
	{
		m_strLogicalMacAddr = m_pszBuf;	
	}	

	t_RegUtil.SetRootPath(STR_REG_DEFAULT_SVC_PATH);

	return 0;
}
//---------------------------------------------------------------------------

INT32		CEnvironment::LoadEnv_DB()
{
	memset(m_pszBuf, 0, CHAR_MAX_SIZE); 

	t_RegUtil.SetRootPath(STR_REG_DEFAULT_SVC_DB_PATH);
	if(t_RegUtil.RegReadString(HKEY_LOCAL_MACHINE, "", "main_db_name", m_pszBuf))
	{
		strncpy(m_pszBuf, "nanny_info", CHAR_MAX_SIZE-1);
		m_pszBuf[CHAR_MAX_SIZE-1] = 0;
		t_RegUtil.RegWriteString(HKEY_LOCAL_MACHINE, "", "main_db_name", m_pszBuf);
	}
	t_DBAcInfoF.strDB = m_pszBuf;
	
    if(t_RegUtil.RegReadString(HKEY_LOCAL_MACHINE, "", "main_db_account_id", m_pszBuf))
    {
		strncpy(m_pszBuf, "nai", CHAR_MAX_SIZE-1);
		m_pszBuf[CHAR_MAX_SIZE-1] = 0;
		t_RegUtil.RegWriteString(HKEY_LOCAL_MACHINE, "", "main_db_account_id", m_pszBuf);
    }
	t_DBAcInfoF.strID = m_pszBuf;
	
	

	t_RegUtil.SetRootPath(STR_REG_DEFAULT_SVC_PATH);
	return 0;
}
//---------------------------------------------------------------------------

INT32		CEnvironment::SetReg_HostRegTime(UINT32 nTime)
{
	t_RegUtil.SetRootPath(STR_REG_DEFAULT_SVC_LOCAL_PATH);

	t_RegUtil.RegWriteInt(HKEY_LOCAL_MACHINE, "", "host_reg_time", nTime);
	m_nHostRegTime = nTime;

	t_RegUtil.SetRootPath(STR_REG_DEFAULT_SVC_PATH);
	return 0;
}
//---------------------------------------------------------------------------

INT32		CEnvironment::SetReg_BootChkTime(UINT32 nTime)
{
	t_RegUtil.SetRootPath(STR_REG_DEFAULT_SVC_LOCAL_PATH);

	t_RegUtil.RegWriteInt(HKEY_LOCAL_MACHINE, "", "boot_chk_time", nTime);
	m_nBootChkTime = nTime;

	t_RegUtil.SetRootPath(STR_REG_DEFAULT_SVC_PATH);
	return 0;
}
//---------------------------------------------------------------------------

INT32		CEnvironment::GetReg_LastOffInfo()
{
	t_RegUtil.SetRootPath(STR_REG_DEFAULT_SVC_LOCAL_PATH);

	if(t_RegUtil.RegReadInt(HKEY_LOCAL_MACHINE, "", "last_off_type", m_nValue))
	{
		m_nValue = 0;
	}
	m_nLastOffType = m_nValue;

	if(t_RegUtil.RegReadInt(HKEY_LOCAL_MACHINE, "", "last_off_time", m_nValue))
	{
		m_nValue = 0;
	}
	m_nLastOffTime = m_nValue;

	t_RegUtil.SetRootPath(STR_REG_DEFAULT_SVC_PATH);

	return 0;
}
//---------------------------------------------------------------------------

INT32		CEnvironment::SetReg_LastOffInfo(ASI_BOOT_TYPE eBootType)
{
	t_RegUtil.SetRootPath(STR_REG_DEFAULT_SVC_LOCAL_PATH);

	t_RegUtil.RegWriteInt(HKEY_LOCAL_MACHINE, "", "last_off_type", INT32(eBootType));
	t_RegUtil.RegWriteInt(HKEY_LOCAL_MACHINE, "", "last_off_time", 0);

	return 0;
}
//---------------------------------------------------------------------------

INT32		CEnvironment::SetReg_HostKey(String strHostKey)
{
	t_RegUtil.SetRootPath(STR_REG_DEFAULT_SVC_LOCAL_PATH);

	t_RegUtil.RegWriteString(HKEY_LOCAL_MACHINE, "", "host_key", strHostKey.c_str());
	m_strHostKey = strHostKey;

	t_RegUtil.SetRootPath(STR_REG_DEFAULT_SVC_PATH);
	return 0;
}
//---------------------------------------------------------------------------
INT32		CEnvironment::SetReg_LastOffHookInfo(UINT32 nMode)
{
	t_RegUtil.SetRootPath(STR_REG_DEFAULT_SVC_LOCAL_PATH);
	t_RegUtil.RegWriteInt(HKEY_LOCAL_MACHINE, "", "last_off_hook", nMode);
	return 0;
}
//---------------------------------------------------------------------------

INT32		CEnvironment::SetReg_RmKey(String strRmKey)
{
	t_RegUtil.SetRootPath(STR_REG_DEFAULT_SVC_UNINS_PATH);

	t_RegUtil.RegWriteString(HKEY_LOCAL_MACHINE, "", "rm_key", strRmKey.c_str());	
	t_RegUtil.SetRootPath(STR_REG_DEFAULT_SVC_PATH);
	return 0;
}
//---------------------------------------------------------------------------

INT32		CEnvironment::SetReg_LgnSvrInfoListMode(UINT32 nMode)
{
	t_RegUtil.SetRootPath(STR_REG_DEFAULT_SVC_CON_PATH);

	t_RegUtil.RegWriteInt(HKEY_LOCAL_MACHINE, "", "lgn_svr_list_mode", nMode);	
	m_nLgnSvrInfoListMode = nMode;

	t_RegUtil.SetRootPath(STR_REG_DEFAULT_SVC_PATH);
	return 0;
}
//---------------------------------------------------------------------------

INT32		CEnvironment::GetReg_LocalEnv_TSProtectMode()
{
	INT32 nRtn = 0;
	t_RegUtil.SetRootPath(STR_REG_DEFAULT_SVC_LOCAL_PATH);

	t_RegUtil.RegReadInt(HKEY_LOCAL_MACHINE, "", "ts_pm", nRtn);	

	t_RegUtil.SetRootPath(STR_REG_DEFAULT_SVC_PATH);
	return nRtn;
}
//---------------------------------------------------------------------------

INT32		CEnvironment::SetReg_LocalEnv_TSProtectMode(UINT32 nMode)
{
	UINT32 nRtn = 0;
	t_RegUtil.SetRootPath(STR_REG_DEFAULT_SVC_LOCAL_PATH);

	t_RegUtil.RegWriteInt(HKEY_LOCAL_MACHINE, "", "ts_pm", nMode);	

	t_RegUtil.SetRootPath(STR_REG_DEFAULT_SVC_PATH);
	return nRtn;
}
//---------------------------------------------------------------------------

INT32		CEnvironment::GetReg_EnableServiceOpt()
{
	INT32 nRet = 0;
	t_RegUtil.SetRootPath(STR_REG_DEFAULT_SVC_LOCAL_PATH);
	t_RegUtil.RegReadInt(HKEY_LOCAL_MACHINE, "", "set_service_opt", nRet);

	return nRet;
}
//---------------------------------------------------------------------------

INT32		CEnvironment::SetReg_EnableServiceOpt(UINT32 nMode)
{
	t_RegUtil.SetRootPath(STR_REG_DEFAULT_SVC_LOCAL_PATH);
	t_RegUtil.RegWriteInt(HKEY_LOCAL_MACHINE, "", "set_service_opt", nMode);

	return 0;
}
//---------------------------------------------------------------------------
String		CEnvironment::GetReg_DbgEnv_DLLPath()
{
	String strRtn;
	t_RegUtil.SetRootPath(STR_REG_DEFAULT_SVC_DEBUG_PATH);

	t_RegUtil.RegReadString(HKEY_LOCAL_MACHINE, "", "dll_path", m_pszBuf);
	strRtn = m_pszBuf;

	t_RegUtil.SetRootPath(STR_REG_DEFAULT_SVC_PATH);
	return strRtn;
}
//---------------------------------------------------------------------------

UINT32		CEnvironment::GetReg_DbgEnv_SysBoot()
{
	INT32 nRtn = 0;
	t_RegUtil.SetRootPath(STR_REG_DEFAULT_SVC_DEBUG_PATH);

	t_RegUtil.RegReadInt(HKEY_LOCAL_MACHINE, "", "sys_boot", nRtn);	

	t_RegUtil.SetRootPath(STR_REG_DEFAULT_SVC_PATH);
	return (UINT32)nRtn;
}
//---------------------------------------------------------------------------

INT32		CEnvironment::GetReg_LocalEnv_TSDebugMode()
{
	t_RegUtil.SetRootPath(STR_REG_DEFAULT_SVC_LOCAL_PATH);
	t_RegUtil.RegReadInt(HKEY_LOCAL_MACHINE, "", "ts_dbg", m_nTsDebugMode);	
	t_RegUtil.SetRootPath(STR_REG_DEFAULT_SVC_PATH);
	return m_nTsDebugMode;
}

//---------------------------------------------------------------------------

INT32		CEnvironment::SetReg_LocalEnv_TSDebugMode(UINT32 nMode)
{
	m_nTsDebugMode = nMode;

	t_RegUtil.SetRootPath(STR_REG_DEFAULT_SVC_LOCAL_PATH);
	t_RegUtil.RegWriteInt(HKEY_LOCAL_MACHINE, "", "ts_dbg", m_nTsDebugMode);	
	t_RegUtil.SetRootPath(STR_REG_DEFAULT_SVC_PATH);
	return 0;
}
//---------------------------------------------------------------------------

INT32		CEnvironment::SetReg_TimeStamp(INT64 nTimeStamp)
{
	t_RegUtil.SetRootPath(STR_REG_DEFAULT_SVC_LOCAL_PATH);
	t_RegUtil.RegWriteInt64(HKEY_LOCAL_MACHINE, "", "time_stamp", nTimeStamp);
	return 0;
}
//---------------------------------------------------------------------------
