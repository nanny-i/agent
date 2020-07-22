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

// MainRun.cpp: implementation of the CMainRun class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "com_struct.h"
#include "MainDlg.h"

INT32		CMainDlg::PreCreateSubClass()
{
	INT32 nRetVal = 0;
	CSystemInfo tSysInfo;

	do
	{
		t_EnvInfo = new CEnvironment();
		if(t_EnvInfo == NULL)
		{
			nRetVal = -1;
			break;
		}
		
		t_EnvInfoOp = new CEnvironmentOp();
		if(t_EnvInfo == NULL)
		{
			nRetVal = -2;
			break;
		}

		nRetVal = t_EnvInfo->LoadEnv(); 
		if(nRetVal != 0) 
		{
			nRetVal -= 1000;
			break;
		}	

		t_EnvInfoOp->SetMainHandle((HWND)this);
		
		nRetVal = t_EnvInfoOp->InitEnvOp();
		if(nRetVal != 0) 
		{
			nRetVal -= 2000;
			break;
		}

//		WriteLogN("SystemInfo : [%s] : %s", tSysInfo.GetCompName().c_str(), tSysInfo.GetSysName().c_str());

		nRetVal = 0;
	}while(FALSE);

	return nRetVal;
}

//--------------------------------------------------------------------

INT32		CMainDlg::CreateLoadLibrary()
{
	//	create dll util
	INT32 nRetVal = 0;
	do
	{
		t_ResInfoDLLUtil			= new CResInfoDLLUtil();		
		if(t_ResInfoDLLUtil == NULL)
		{
			nRetVal = -1;
			break;
		}

		t_ASICOMPDLLUtil			= new CASICOMPDLLUtil();
		if(t_ASICOMPDLLUtil == NULL)
		{
			nRetVal = -12;
			break;
		}

		t_RemoveLogDLLUtil			= new CRemoveLogDLLUtil();
		if(t_RemoveLogDLLUtil == NULL)
		{
			nRetVal = -2;
			break;
		}
		
		t_ASIFFDLLUtil				= new CASIFFDLLUtil();
		if(t_ASIFFDLLUtil == NULL)
		{
			nRetVal = -11;
			break;
		}
		/*
		t_ASIFDLDLLUtil				= new CASIFDLDLLUtil();
		if(t_ASIFDLDLLUtil == NULL)
		{
			nRetVal = -12;
			break;
		}
		*/

		t_NetworkDLLUtil			= new CNetworkDLLUtil();
		if(t_NetworkDLLUtil == NULL)
		{
			nRetVal = -3;
			break;
		}
		t_SeedDLLUtil				= new CSeedDLLUtil();
		if(t_SeedDLLUtil == NULL)
		{
			nRetVal = -4;
			break;
		}

//		t_ASIEPSAPPDLLUtil			= new CASIEPSAPPDLLUtil();

//		t_ASIWENGDLLUtil			= new CASIWEngDLLUtil();
		t_ProcInfoDLLUtil			= new CPROCINFODLLUtil();
		if(t_ProcInfoDLLUtil == NULL)
		{
			nRetVal = -5;
			break;
		}

		t_DevInfoDLLUtil			= new CDEVINFODLLUtil();
		if(t_DevInfoDLLUtil == NULL)
		{
			nRetVal = -6;
			break;
		}

		t_LgnCltUtil				= new CCltSocketUtil();
		if(t_LgnCltUtil == NULL)
		{
			nRetVal = -7;
			break;
		}	
		t_MgrCltUtil				= new CCltSocketUtil();
		if(t_MgrCltUtil == NULL)
		{
			nRetVal = -8;
			break;
		}		
		t_UdtCltUtil				= new CCltSocketUtil();
		if(t_UdtCltUtil == NULL)
		{
			nRetVal = -9;
			break;
		}			
		t_LinkSvrUtil				= new CSvrSocketUtil();
		if(t_LinkSvrUtil == NULL)
		{
			nRetVal = -10;
			break;
		}		
		nRetVal = 0;
	}while(FALSE);
	
	return nRetVal;
}
//--------------------------------------------------------------------

INT32		CMainDlg::CreateSubClass()
{
	int nRetVal	= 0;

	do{
	
		t_DBMS_Base = (CDBMgrBase*)new CDBMgrBase();
		if(t_DBMS_Base == NULL)
		{
			nRetVal = -1;
			break;
		}
		t_DBMS_Base->SetProperty(t_EnvInfo->t_DBAcInfoF);
		nRetVal = t_DBMS_Base->ConnectDB();
		if(nRetVal != 0)
		{
			nRetVal -= 2;
			break;
		}	  
		SyncDatabase();

		t_ValidTimeUtil = new CValidTimeUtil();
		if(t_ValidTimeUtil == NULL)
		{
			nRetVal = -11;
			break;
		}
		t_DeployPolicyUtil = new CDeployPolicyUtil();
		if(t_DeployPolicyUtil == NULL)
		{
			nRetVal = -12;
			break;
		}
		
		t_ExecuteFileUtil = new CExecuteFileUtil();
		if(t_ExecuteFileUtil == NULL)
		{
			nRetVal = -13;
			break;
		}
		
		t_DocBackupUtil = new CDocBackupUtil();
		if(t_DocBackupUtil == NULL)
		{
			nRetVal = -14;
			break;
		}
		
		t_FileDeleteUtil = new CFileDeleteUtil();
		if(t_FileDeleteUtil == NULL)
		{
			nRetVal = -15;
			break;
		}

		t_ComFuncUtil = new CComFuncUtil();
		if(t_ComFuncUtil == NULL)
		{
			nRetVal = -16;
			break;
		}

		t_ManageFileDown = new CManageFileDown();
		if(t_ManageFileDown == NULL)
		{
			nRetVal = -21;
			break;
		}

		t_ManageLogicTimer = new CManageLogicTimer();		
		if(t_ManageLogicTimer == NULL)
		{
			nRetVal = -22;
			break;
		}
		t_ManageBaseUtil = new CManageBaseUtil();
		if(t_ManageBaseUtil == NULL)
		{
			nRetVal = -24;
			break;
		}
		t_ManageHostPolicy = new CManageHostPolicy();
		if(t_ManageHostPolicy == NULL)
		{
			nRetVal = -25;
			break;
		}
		t_ManageUserPolicy = new CManageUserPolicy();
		if(t_ManageUserPolicy == NULL)
		{
			nRetVal = -26;
			break;
		}
		
		t_ManageErrorCode = new CManageErrorCode();
		if(t_ManageErrorCode == NULL)
		{
			nRetVal = -27;
			break;
		}

		t_ManageEnvPolicy = new CManageEnvPolicy();		
		if(t_ManageEnvPolicy == NULL)
		{
			nRetVal = -28;
			break;
		}
		
		t_ManageLinkLicense	= new CManageLinkLicense();
		if(t_ManageLinkLicense == NULL)
		{
			nRetVal = -29;
			break;
		}

		t_ManageHostPolicy->LoadDBMS();
		t_ManageUserPolicy->LoadDBMS();
		t_ManageErrorCode->LoadDBMS();
		t_ManageLinkLicense->LoadDBMS();

//userdel
// 		t_ManageGroupUserDel		= new CManageGroupUserDel();
// 		t_ManageUserDel				= new CManageUserDel();

        t_ThreadDBMSQuery = new CThreadDBMSQuery();
		if(t_ThreadDBMSQuery == NULL)
		{
			nRetVal = -51;
			break;
		}

		t_ThreadTimer = new CThreadTimer();
		if(t_ThreadTimer == NULL)
		{
			nRetVal = -52;
			break;
		}

		t_ThreadSocket = new CThreadSocket();
		if(t_ThreadSocket == NULL)
		{
			nRetVal = -53;
			break;
		}

		t_ThreadLog = new CThreadLog();
		if(t_ThreadLog == NULL)
		{
			nRetVal = -54;
			break;
		}

		t_ThreadPoFaClear = new CThreadPoFaClear();
		if(t_ThreadPoFaClear == NULL)
		{
			nRetVal = -55;
			break;
		}
		
		t_ThreadPoFeScan = new CThreadPoFeScan();
		if(t_ThreadPoFeScan == NULL)
		{
			nRetVal = -56;
			break;
		}

		t_ThreadPoFePtnLo = new CThreadPoFePtnLo();
		if(t_ThreadPoFePtnLo == NULL)
		{
			nRetVal = -57;
			break;
		}

		t_ThreadChkHkNoti = new CThreadChkHkNoti();
		if(t_ThreadChkHkNoti == NULL)
		{
			nRetVal = -58;
			break;
		}

		t_ThreadEvtMon = new CThreadEvtMon();
		if(t_ThreadEvtMon == NULL)
		{
			nRetVal = -59;
			break;
		}

		t_ThreadPoInPtnScan = new CThreadPoInPtnScan();
		if(t_ThreadPoInPtnScan == NULL)
		{
			nRetVal = -60;
			break;
		}

		
		t_LogicLocalEnvLog	= new CLogicLocalEnvLog();
		if(t_LogicLocalEnvLog == NULL)
		{
			nRetVal = -71;
			break;
		}

		t_LogicLocalEnvAuth = new CLogicLocalEnvAuth();
		if(t_LogicLocalEnvAuth == NULL)
		{
			nRetVal = -72;
			break;
		}

		t_LogicPWEvtMon = new CLogicPWEvtMon();
		if(t_LogicPWEvtMon == NULL)
		{
			nRetVal = -73;
			break;
		}

		t_LogicLgnAuth = new CLogicLgnAuth();
		if(t_LogicLgnAuth == NULL)
		{
			nRetVal = -74;
			break;
		}

		t_LogicUdtAuth = new CLogicUdtAuth();
		if(t_LogicUdtAuth == NULL)
		{
			nRetVal = -75;
			break;
		}

		t_LogicMgrAuth = new CLogicMgrAuth();
		if(t_LogicMgrAuth == NULL)
		{
			nRetVal = -81;
			break;
		}

		t_LogicMgrHost = new CLogicMgrHost();
		if(t_LogicMgrHost == NULL)
		{
			nRetVal = -82;
			break;
		}

		t_LogicMgrHostSys = new CLogicMgrHostSys();
		if(t_LogicMgrHostSys == NULL)
		{
			nRetVal = -83;
			break;
		}

		t_LogicMgrHostHw = new CLogicMgrHostHw();
		if(t_LogicMgrHostHw == NULL)
		{
			nRetVal = -84;
			break;
		}

		t_LogicMgrHostSw = new CLogicMgrHostSw();
		if(t_LogicMgrHostSw == NULL)
		{
			nRetVal = -85;
			break;
		}

		t_LogicMgrHostStatusPo = new CLogicMgrHostStatusPo();
		if(t_LogicMgrHostStatusPo == NULL)
		{
			nRetVal = -86;
			break;
		}
		
		t_LogicMgrHostKey = new CLogicMgrHostKey();
		if(t_LogicMgrHostKey == NULL)
		{
			nRetVal = -87;
			break;
		}

		t_LogicMgrUser = new CLogicMgrUser();
		if(t_LogicMgrUser == NULL)
		{
			nRetVal = -88;
			break;
		}

		t_LogicMgrSiteFile = new CLogicMgrSiteFile();
		if(t_LogicMgrSiteFile == NULL)
		{
			nRetVal = -89;
			break;
		}

		t_LogicMgrSiteVuln = new CLogicMgrSiteVuln();
		if(t_LogicMgrSiteVuln == NULL)
		{
			nRetVal = -90;
			break;
		}

		t_LogicMgrSiteVulnScan = new CLogicMgrSiteVulnScan();
		if(t_LogicMgrSiteVulnScan == NULL)
		{
			nRetVal = -91;
			break;
		}

		t_LogicMgrSiteVulnRepair = new CLogicMgrSiteVulnRepair();
		if(t_LogicMgrSiteVulnRepair == NULL)
		{
			nRetVal = -92;
			break;
		}

		t_LogicMgrSiteVulnLock = new CLogicMgrSiteVulnLock();
		if(t_LogicMgrSiteVulnLock == NULL)
		{
			nRetVal = -93;
			break;
		}

		t_LogicMgrEnvLicense = new CLogicMgrEnvLicense();
		if(t_LogicMgrEnvLicense == NULL)
		{
			nRetVal = -94;
			break;
		}

		t_LogicMgrEnvLog = new CLogicMgrEnvLog();
		if(t_LogicMgrEnvLog == NULL)
		{
			nRetVal = -95;
			break;
		}

		t_LogicMgrEnvLogUnit = new CLogicMgrEnvLogUnit();
		if(t_LogicMgrEnvLogUnit == NULL)
		{
			nRetVal = -95;
			break;
		}

		t_LogicMgrEnvNotifyInfo = new CLogicMgrEnvNotifyInfo();
		if(t_LogicMgrEnvNotifyInfo == NULL)
		{
			nRetVal = -96;
			break;
		}

		t_LogicMgrEnvSelfProtectAgt	= new CLogicMgrEnvSelfProtectAgt();
		if(t_LogicMgrEnvSelfProtectAgt == NULL)
		{
			nRetVal = -97;
			break;
		}

		t_LogicMgrEnvSOrgLink = new CLogicMgrEnvSOrgLink();
		if(t_LogicMgrEnvSOrgLink == NULL)
		{
			nRetVal = -98;
			break;
		}

		t_LogicMgrEnvTrustSubject = new CLogicMgrEnvTrustSubject();
		if(t_LogicMgrEnvTrustSubject == NULL)
		{
			nRetVal = -99;
			break;
		}
		
		t_LogicMgrPoHostRmInfo = new CLogicMgrPoHostRmInfo();
		if(t_LogicMgrPoHostRmInfo == NULL)
		{
			nRetVal = -100;
			break;
		}

		t_LogicMgrPoHostRun = new CLogicMgrPoHostRun();
		if(t_LogicMgrPoHostRun == NULL)
		{
			nRetVal = -101;
			break;
		}

		t_LogicMgrPoSvrInfoLgn = new CLogicMgrPoSvrInfoLgn();
		if(t_LogicMgrPoSvrInfoLgn == NULL)
		{
			nRetVal = -102;
			break;
		}

		t_LogicMgrPoSvrInfoUdt = new CLogicMgrPoSvrInfoUdt();
		if(t_LogicMgrPoSvrInfoUdt == NULL)
		{
			nRetVal = -103;
			break;
		}

		t_LogicMgrPoSch = new CLogicMgrPoSch();
		if(t_LogicMgrPoSch == NULL)
		{
			nRetVal = -104;
			break;
		}

		t_LogicMgrPoPower = new CLogicMgrPoPower();
		if(t_LogicMgrPoPower == NULL)
		{
			nRetVal = -105;
			break;
		}

		t_LogicMgrPoWinRun = new CLogicMgrPoWinRun();
		if(t_LogicMgrPoWinRun == NULL)
		{
			nRetVal = -106;
			break;
		}

		t_LogicMgrPoCtlPanel = new CLogicMgrPoCtlPanel();
		if(t_LogicMgrPoCtlPanel == NULL)
		{
			nRetVal = -107;
			break;
		}

		t_LogicMgrPoDeployFile = new CLogicMgrPoDeployFile();
		if(t_LogicMgrPoDeployFile == NULL)
		{
			nRetVal = -108;
			break;
		}
		
		t_LogicMgrPoCtlProc = new CLogicMgrPoCtlProc();
		if(t_LogicMgrPoCtlProc == NULL)
		{
			nRetVal = -109;
			break;
		}

		t_LogicMgrPoSelfProtect = new CLogicMgrPoSelfProtect();
		if(t_LogicMgrPoSelfProtect == NULL)
		{
			nRetVal = -110;
			break;
		}

		t_LogicMgrPoFaOp = new CLogicMgrPoFaOp();
		if(t_LogicMgrPoFaOp == NULL)
		{
			nRetVal = -111;
			break;
		}
		
		t_LogicMgrPoFaClear = new CLogicMgrPoFaClear();
		if(t_LogicMgrPoFaClear == NULL)
		{
			nRetVal = -112;
			break;
		}

		t_LogicMgrPoFaEnv = new CLogicMgrPoFaEnv();
		if(t_LogicMgrPoFaEnv == NULL)
		{
			nRetVal = -113;
			break;
		}

		t_LogicMgrPoFaProc = new CLogicMgrPoFaProc();
		if(t_LogicMgrPoFaProc == NULL)
		{
			nRetVal = -114;
			break;
		}
		
		t_LogicMgrPoFaBk = new CLogicMgrPoFaBk();
		if(t_LogicMgrPoFaBk == NULL)
		{
			nRetVal = -115;
			break;
		}

		t_LogicMgrPoFaNotify = new CLogicMgrPoFaNotify();
		if(t_LogicMgrPoFaNotify == NULL)
		{
			nRetVal = -116;
			break;
		}

		t_LogicMgrPoFePtnOp	= new CLogicMgrPoFePtnOp();
		if(t_LogicMgrPoFePtnOp == NULL)
		{
			nRetVal = -117;
			break;
		}

		t_LogicMgrPoFePtnLo = new CLogicMgrPoFePtnLo();
		if(t_LogicMgrPoFePtnLo == NULL)
		{
			nRetVal = -118;
			break;
		}

		t_LogicMgrPoFePtnBL = new CLogicMgrPoFePtnBL();	
		if(t_LogicMgrPoFePtnBL == NULL)
		{
			nRetVal = -119;
			break;
		}

		t_LogicMgrPoFePtnWL	= new CLogicMgrPoFePtnWL();	
		if(t_LogicMgrPoFePtnWL == NULL)
		{
			nRetVal = -120;
			break;
		}

		t_LogicMgrPoFeExclude = new CLogicMgrPoFeExclude();
		if(t_LogicMgrPoFeExclude == NULL)
		{
			nRetVal = -121;
			break;
		}

		t_LogicMgrPoFeNotify = new CLogicMgrPoFeNotify();
		if(t_LogicMgrPoFeNotify == NULL)
		{
			nRetVal = -122;
			break;
		}

		t_LogicMgrPoFeSinglePtn = new CLogicMgrPoFeSinglePtn();
		if(t_LogicMgrPoFeSinglePtn == NULL)
		{
			nRetVal = -123;
			break;
		}
		
		t_LogicMgrPoInPtnOp = new CLogicMgrPoInPtnOp();
		if(t_LogicMgrPoInPtnOp == NULL)
		{
			nRetVal = -124;
			break;
		}

		t_LogicMgrPoInPtnBL	= new CLogicMgrPoInPtnBL();
		if(t_LogicMgrPoInPtnBL == NULL)
		{
			nRetVal = -125;
			break;
		}

		t_LogicMgrPoInPtnWL	= new CLogicMgrPoInPtnWL();
		if(t_LogicMgrPoInPtnWL == NULL)
		{
			nRetVal = -126;
			break;
		}

		t_LogicMgrPoInPtnEx	= new CLogicMgrPoInPtnEx();
		if(t_LogicMgrPoInPtnEx == NULL)
		{
			nRetVal = -127;
			break;
		}
		
		t_LogicMgrPoInPtnExTrust = new CLogicMgrPoInPtnExTrust();
		if(t_LogicMgrPoInPtnExTrust == NULL)
		{
			nRetVal = -128;
			break;
		}

		t_LogicMgrPoInPtnSP	= new CLogicMgrPoInPtnSP();
		if(t_LogicMgrPoInPtnSP == NULL)
		{
			nRetVal = -129;
			break;
		}

		t_LogicMgrPoInPtnSPRule	= new CLogicMgrPoInPtnSPRule();
		if(t_LogicMgrPoInPtnSPRule == NULL)
		{
			nRetVal = -130;
			break;
		}

		t_LogicMgrPoInPtnNo	= new CLogicMgrPoInPtnNo();
		if(t_LogicMgrPoInPtnNo == NULL)
		{
			nRetVal = -131;
			break;
		}
		
		t_LogicMgrPoInAcDoc	= new CLogicMgrPoInAcDoc();
		if(t_LogicMgrPoInAcDoc == NULL)
		{
			nRetVal = -132;
			break;
		}

		t_LogicMgrPoInAcSf = new CLogicMgrPoInAcSf();
		if(t_LogicMgrPoInAcSf == NULL)
		{
			nRetVal = -133;
			break;
		}

		t_LogicMgrPoInAcFile = new CLogicMgrPoInAcFile();
		if(t_LogicMgrPoInAcFile == NULL)
		{
			nRetVal = -134;
			break;
		}

		t_LogicMgrPoInVulnOp = new CLogicMgrPoInVulnOp();
		if(t_LogicMgrPoInVulnOp == NULL)
		{
			nRetVal = -135;
			break;
		}

		t_LogicMgrPoInVulnScan = new CLogicMgrPoInVulnScan();
		if(t_LogicMgrPoInVulnScan == NULL)
		{
			nRetVal = -136;
			break;
		}

		t_LogicMgrLogDeployFile	= new CLogicMgrLogDeployFile();
		if(t_LogicMgrLogDeployFile == NULL)
		{
			nRetVal = -137;
			break;
		}

		t_LogicMgrLogDoc = new CLogicMgrLogDoc();
		if(t_LogicMgrLogDoc == NULL)
		{
			nRetVal = -138;
			break;
		}

		t_LogicMgrLogSecu = new CLogicMgrLogSecu();
		if(t_LogicMgrLogSecu == NULL)
		{
			nRetVal = -139;
			break;
		}

		t_LogicMgrLogStatus	= new CLogicMgrLogStatus();
		if(t_LogicMgrLogStatus == NULL)
		{
			nRetVal = -140;
			break;
		}

		t_LogicMgrCtrlRemoteCtrl = new CLogicMgrCtrlRemoteCtrl();
		if(t_LogicMgrCtrlRemoteCtrl == NULL)
		{
			nRetVal = -141;
			break;
		}

		t_LogicMgrCtrlRemotePower = new CLogicMgrCtrlRemotePower();
		if(t_LogicMgrCtrlRemotePower == NULL)
		{
			nRetVal = -142;
			break;
		}

		t_LogicMgrCtrlRemoteOrder = new CLogicMgrCtrlRemoteOrder();
		if(t_LogicMgrCtrlRemoteOrder == NULL)
		{
			nRetVal = -143;
			break;
		}

		t_LogicMgrCtrlInstantMsg = new CLogicMgrCtrlInstantMsg();
		if(t_LogicMgrCtrlInstantMsg == NULL)
		{
			nRetVal = -144;
			break;
		}

		t_LogicMgrCtrlHostRes = new CLogicMgrCtrlHostRes();
		if(t_LogicMgrCtrlHostRes == NULL)
		{
			nRetVal = -145;
			break;
		}

		t_LogicMgrCtrlRestore = new CLogicMgrCtrlRestore();
		if(t_LogicMgrCtrlRestore == NULL)
		{
			nRetVal = -145;
			break;
		}

		t_LogicAuth	= new CLogicAuth();
		if(t_LogicAuth == NULL)
		{
			nRetVal = -151;
			break;
		}

		t_LogicInitLink	= new CLogicInitLink();
		if(t_LogicInitLink == NULL)
		{
			nRetVal = -152;
			break;
		}

		t_LogicLogEvent	= new CLogicLogEvent();
		if(t_LogicLogEvent == NULL)
		{
			nRetVal = -153;
			break;
		}

		t_LogicLogDocDScan = new CLogicLogDocDScan();
		if(t_LogicLogDocDScan == NULL)
		{
			nRetVal = -154;
			break;
		}

		t_LogicApplyPolicy = new CLogicApplyPolicy();
		if(t_LogicApplyPolicy == NULL)
		{
			nRetVal = -155;
			break;
		}
		
		nRetVal = 0;
	}while(FALSE);
	
	return nRetVal;
}
//--------------------------------------------------------------------

INT32		CMainDlg::InitLoadLibrary()
{
	INT32 nRetVal = 0;
	CHAR szDLLName[CHAR_MAX_SIZE] = {0, };

	do
	{
		snprintf(szDLLName, CHAR_MAX_SIZE-1, "%s/asi_resinfo.so", t_EnvInfo->m_strDLLPath.c_str());
		nRetVal = t_ResInfoDLLUtil->LoadLibraryExt(szDLLName);
		if(nRetVal != 0)
		{
			WriteLogE("fail to load library : [%s][%d]", szDLLName, nRetVal);
			return -11;
		}
	
		snprintf(szDLLName, CHAR_MAX_SIZE-1, "%s/asi_comp.so", t_EnvInfo->m_strDLLPath.c_str());
		if(t_ASICOMPDLLUtil->LoadLibraryExt(szDLLName))
		{
			WriteLogE("load library fail : [%s][%d]", szDLLName, GetLastError());
			return -12;
		}
		
		snprintf(szDLLName, CHAR_MAX_SIZE-1, "%s/asi_rmlog.so", t_EnvInfo->m_strDLLPath.c_str());
		nRetVal = t_RemoveLogDLLUtil->LoadLibraryExt(szDLLName);
		if(nRetVal != 0)
		{
			WriteLogE("fail to load library : [%s][%d]", szDLLName, nRetVal);
			return -13;
		}
		snprintf(szDLLName, CHAR_MAX_SIZE-1, "%s/asi_ff.so", t_EnvInfo->m_strDLLPath.c_str());
		nRetVal = t_ASIFFDLLUtil->LoadLibraryExt(szDLLName);
		if(nRetVal != 0)
		{
			WriteLogE("fail to load library : [%s][%d]", szDLLName, nRetVal);
			return -14;
		}
/*
		snprintf(szDLLName, CHAR_MAX_SIZE-1, "%s/asi_fdl.so", t_EnvInfo->m_strDLLPath.c_str());
		if(t_ASIFDLDLLUtil->LoadLibraryExt(szDLLName)) 
		{
			WriteLogE("fail to load library : [%s][%d]", szDLLName, errno);
			return -15;
		}
*/

		snprintf(szDLLName, CHAR_MAX_SIZE-1, "%s/asi_network.so", t_EnvInfo->m_strDLLPath.c_str());
		nRetVal = t_NetworkDLLUtil->LoadLibraryExt(szDLLName);
		if(nRetVal != 0)
		{
			WriteLogE("fail to load library : [%s][%d]", szDLLName, nRetVal);
			return -16;
		}

		snprintf(szDLLName, CHAR_MAX_SIZE-1, "%s/asi_seed.so", t_EnvInfo->m_strDLLPath.c_str());
		nRetVal = t_SeedDLLUtil->LoadLibraryExt(szDLLName);
		if(nRetVal != 0) 
		{
			WriteLogE("fail to load library : [%s][%d] : %s", szDLLName, nRetVal, strerror(errno));
			return -17;
		}

		snprintf(szDLLName, CHAR_MAX_SIZE-1, "%s/asi_procinfo.so", t_EnvInfo->m_strDLLPath.c_str());
		nRetVal = t_ProcInfoDLLUtil->LoadLibraryExt(szDLLName);
		if(nRetVal != 0) 
		{
			WriteLogE("fail to load library : [%s][%d]", szDLLName, nRetVal);
			return -18;
		}

		snprintf(szDLLName, CHAR_MAX_SIZE-1, "%s/asi_devinfo.so", t_EnvInfo->m_strDLLPath.c_str());
		nRetVal = t_DevInfoDLLUtil->LoadLibraryExt(szDLLName);
		if(nRetVal != 0) 
		{
			WriteLogE("fail to load library : [%s][%d]", szDLLName, nRetVal);
			return -19;
		}

		snprintf(szDLLName, CHAR_MAX_SIZE-1, "%s/asi_cltsock.so", t_EnvInfo->m_strDLLPath.c_str());
		nRetVal = t_LgnCltUtil->LoadLibraryExt(szDLLName);
		if(nRetVal != 0)	
		{
			WriteLogE("fail to load library : [%s][%d]", szDLLName, nRetVal);
			return -20;
		}

		snprintf(szDLLName, CHAR_MAX_SIZE-1, "%s/asi_cltsock.so", t_EnvInfo->m_strDLLPath.c_str());
		nRetVal = t_MgrCltUtil->LoadLibraryExt(szDLLName);
		if(nRetVal != 0)	
		{
			WriteLogE("fail to load library : [%s][%d]", szDLLName, nRetVal);
			return -21;
		}

		snprintf(szDLLName, CHAR_MAX_SIZE-1, "%s/asi_cltsock.so", t_EnvInfo->m_strDLLPath.c_str());
		nRetVal = t_UdtCltUtil->LoadLibraryExt(szDLLName);
		if(nRetVal != 0)	
		{
			WriteLogE("fail to load library : [%s][%d]", szDLLName, nRetVal);
			return -22;
		}

		snprintf(szDLLName, CHAR_MAX_SIZE-1, "%s/asi_svrsock.so", t_EnvInfo->m_strDLLPath.c_str());
		nRetVal = t_LinkSvrUtil->LoadLibraryExt(szDLLName);
		if(nRetVal != 0)
		{
			WriteLogE("fail to load library : [%s][%d]", szDLLName, nRetVal);
			return -23;
		}
		nRetVal = 0;
	}while(FALSE);

	return nRetVal;
}
//--------------------------------------------------------------------

INT32		CMainDlg::InitSubClass() 
{

	{
		ASI_FDL_INIT tAFI;
		t_EnvInfoOp->GetDLFileInitData(tAFI);
		SetDLInit(&tAFI);
/*
		if(t_ASIFDLDLLUtil)
			t_ASIFDLDLLUtil->SetDLInit(&tAFI);		
*/
	}

	{
		ASI_FF_INIT_INFO tAFII;
		t_EnvInfoOp->GetFFInitData(tAFII);
		if(t_ASIFFDLLUtil)		
			t_ASIFFDLLUtil->ASIFF_Init(&tAFII);
	}

	{
		
		t_ProcInfoDLLUtil->Init();
		t_DevInfoDLLUtil->Init();
	}

	return 0;
}
//--------------------------------------------------------------------

INT32		CMainDlg::InitRunEnv()
{
	{
		PDB_PO_HOST_RUN pdphr = (PDB_PO_HOST_RUN)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_HOST_RUN);
		if(pdphr && pdphr->nBootChkType == SS_PO_HOST_RUN_BOOT_CHK_TYPE_START_SVC)
		{
			t_EnvInfoOp->SetSysBootMode();
			WriteLogN("set system boot mode on by host_run policy");
		}
	}

	{
		t_ManageSysDrive.InitSysDrive();
	}
	
	return 0;
}
//--------------------------------------------------------------------

INT32		CMainDlg::InitTimerID()
{
	t_ThreadTimer->t_TimerUtil.SetNotifyWnd((HWND)this, (UINT32)WM_GLOBAL_TIMER_EVT);

	{
		UINT32 nLgnPeriod = 5;
		PDB_PO_HOST_RUN pdphr = (PDB_PO_HOST_RUN)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_HOST_RUN);
		if(pdphr)
			nLgnPeriod = pdphr->nLgnConPeriod;

		t_ThreadTimer->t_TimerUtil.AddTimer(TIMER_ID_LOGIN_SVR_AUTH, TIMER_INTERVAL_TIME_SEC*nLgnPeriod, NULL, 1, 0, -1, 1);
	}
	
	t_ThreadTimer->t_TimerUtil.AddTimer(TIMER_ID_LOGIN_SVR_AUTH_LAST,			TIMER_INTERVAL_TIME_MIN*5, NULL, 1, 0);
	t_ThreadTimer->t_TimerUtil.AddTimer(TIMER_ID_MANAGER_SVR_AUTH,				TIMER_INTERVAL_TIME_SEC*5, NULL, 1, 0);
	t_ThreadTimer->t_TimerUtil.AddTimer(TIMER_ID_MANAGER_SVR_AUTH_LAST,			TIMER_INTERVAL_TIME_MIN*5, NULL, 1, 0);
	t_ThreadTimer->t_TimerUtil.AddTimer(TIMER_ID_UPDATE_SVR_AUTH,				TIMER_INTERVAL_TIME_SEC*5, NULL, 1, 0);
	t_ThreadTimer->t_TimerUtil.AddTimer(TIMER_ID_UPDATE_SVR_AUTH_LAST,			TIMER_INTERVAL_TIME_MIN*5, NULL, 1, 0);
	t_ThreadTimer->t_TimerUtil.AddTimer(TIMER_ID_DOWNLOAD_UPDATE_FILE,			TIMER_INTERVAL_TIME_SEC*1, NULL, 1, 0);
	t_ThreadTimer->t_TimerUtil.AddTimer(TIMER_ID_SYS_BOOT_OPERATION_END,		TIMER_INTERVAL_TIME_SEC*1, NULL, 1, 1);
	t_ThreadTimer->t_TimerUtil.AddTimer(TIMER_ID_SYS_OFF_OPERATION,				TIMER_INTERVAL_TIME_SEC, NULL, 1, 0);
	t_ThreadTimer->t_TimerUtil.AddTimer(TIMER_ID_SYS_OFF_OPERATION_END,			TIMER_INTERVAL_TIME_SEC*5, NULL, 1, 0);
	t_ThreadTimer->t_TimerUtil.AddTimer(TIMER_ID_SYS_OFF_OPERATION_CHG_SESSION,	TIMER_INTERVAL_TIME_SEC*2, NULL, 1, 1);
	t_ThreadTimer->t_TimerUtil.AddTimer(TIMER_ID_CHECK_CHANGE_NET_DRIVE,		TIMER_INTERVAL_TIME_SEC*10, NULL, 1, 0);
	t_ThreadTimer->t_TimerUtil.AddTimer(TIMER_ID_CHECK_CHANGE_FIX_DRIVE,		TIMER_INTERVAL_TIME_SEC*1, NULL, 1, 0);
	t_ThreadTimer->t_TimerUtil.AddTimer(TIMER_ID_CHECK_CHANGE_LOGIN_USER,		TIMER_INTERVAL_TIME_SEC*10, NULL, 1, 0);
	t_ThreadTimer->t_TimerUtil.AddTimer(TIMER_ID_POLICY_APPLY_EPS,			TIMER_INTERVAL_TIME_SEC*1, NULL, 1, 0);
	t_ThreadTimer->t_TimerUtil.AddTimer(TIMER_ID_WINDOWS_EVENT_HANDLER,		TIMER_INTERVAL_TIME_MIN, NULL, 1, 0);
	t_ThreadTimer->t_TimerUtil.AddTimer(TIMER_ID_TS_PROTECT_MODE,			TIMER_INTERVAL_TIME_MIN*1, NULL, 1, 1);
	t_ThreadTimer->t_TimerUtil.AddTimer(TIMER_ID_DP_FILE_EXCUTE_END,		TIMER_INTERVAL_TIME_SEC*10, NULL, 1, 0);


	{		
		t_ManageLogicTimer->AddLogicBase(t_LogicMgrPoHostRun,		TIMER_INTERVAL_TIME_MIN*1);
		t_ManageLogicTimer->AddLogicBase(t_LogicMgrPoDeployFile,	TIMER_INTERVAL_TIME_SEC*1);
		t_ManageLogicTimer->AddLogicBase(t_LogicMgrPoFePtnOp,		TIMER_INTERVAL_TIME_MIN*1);
		t_ThreadTimer->t_TimerUtil.AddTimer(TIMER_ID_POLICY_APPLY_CHECK,	TIMER_INTERVAL_TIME_SEC*1,	NULL, 1, 0);
	}

	{
		t_ThreadTimer->t_TimerUtil.AddTimer(TIMER_ID_POLICY_APPLY_FA_CLEAR,		TIMER_INTERVAL_TIME_SEC*1,	NULL, 1, 0);
		t_ThreadTimer->t_TimerUtil.AddTimer(TIMER_ID_POLICY_APPLY_FA_OP_CLEAR,	TIMER_INTERVAL_TIME_SEC*1,	NULL, 1, 0);
		t_ThreadTimer->t_TimerUtil.AddTimer(TIMER_ID_POLICY_APPLY_POWER,		TIMER_INTERVAL_TIME_MIN*1,	NULL, 1, 0);
		t_ThreadTimer->t_TimerUtil.AddTimer(TIMER_ID_POLICY_APPLY_IN_PTN_OP,	TIMER_INTERVAL_TIME_SEC*1,	NULL, 1, 0);

	}

	return 0;
}
//--------------------------------------------------------------------

INT32		CMainDlg::StartSubClass()
{
	BOOL bRetVal = TRUE;
		
	{
		bRetVal = t_ThreadDBMSQuery->CreateThreadExt("dbquery");
		if(bRetVal == FALSE)
		{
			WriteLogE("fail to start dbquery thread [%d]", errno);
			return -1;
		}
		bRetVal = t_ThreadTimer->CreateThreadExt("timer");
		if(bRetVal == FALSE)
		{
			WriteLogE("start [timer] thread result : fail [%d]", errno);
			return -2;
		}

		bRetVal = t_ThreadEvtMon->CreateThreadExt("evt_mon");
		if(bRetVal == FALSE)
		{
			WriteLogE("start [evt_mon] thread result : fail [%d]", errno);
			return -3;
		}

		bRetVal = t_ThreadSocket->CreateThreadExt("socket");
		if(bRetVal == FALSE)
		{
			WriteLogE("start [socket] thread result : fail [%d]", errno);
			return -4;
		}

		bRetVal = t_ThreadLog->CreateThreadExt("log");
		if(bRetVal == FALSE)
		{
			WriteLogE("start [log] thread result : fail [%d]", errno);
			return -5;
		}

		bRetVal = t_ThreadPoFaClear->CreateThreadExt("po_fa_clear");
		if(bRetVal == FALSE)
		{
			WriteLogE("start [po_fa_clear] thread result : fail [%d]", errno);
			return -6;
		}

		bRetVal = t_ThreadPoFePtnLo->CreateThreadExt("po_fe_ptn_lo");
		if(bRetVal == FALSE)
		{
			WriteLogE("start [po_fe_ptn_lo] thread result : fail [%d]", errno);
			return -7;
		}

		bRetVal = t_ThreadPoFeScan->CreateThreadExt("po_fe_scan");
		if(bRetVal == FALSE)
		{
			WriteLogE("start [po_fe_scan] thread result : fail [%d]", errno);
			return -8;
		}

		bRetVal = t_ThreadPoInPtnScan->CreateThreadExt("po_in_scan");
		if(bRetVal == FALSE)
		{
			WriteLogE("start [po_in_scan] thread result : fail [%d]", errno);
			return -9;
		}

		bRetVal = t_ThreadChkHkNoti->CreateThreadExt("chk_hk_noti");
		if(bRetVal == FALSE)
		{
			WriteLogE("start [chk_hk_noti] thread result : fail [%d]", errno);
			return -10;
		}
	}	

	{		
		SOCK_INIT_DATA tSID;
		{
			t_LinkSvrUtil->StopServer(1);
			t_LinkSvrUtil->CloseSocket(0, 0);
			t_LinkSvrUtil->FreeServer();
		}

		tSID = t_EnvInfoOp->GetSvrLinkSID();
		if( (SetER(t_LinkSvrUtil->StartServer(&tSID, NULL))))
		{
			WriteLogE("socket open fail for agent link connect! : [errcode:%d]", g_nErrRtn);			
		}
		else
		{
			WriteLogN("open socket for agent link success : [%u]", t_EnvInfo->m_nIFPort);
		}

		t_ThreadSocket->t_TimerUtil.SetNotifyWnd((HWND)this, 0);
		t_ThreadSocket->SetLogicStatus(SSA_SOCKET_THREAD_LOGIC_TYPE_SVR_LINK, SSA_SOCKET_THREAD_LOGIC_STATUS_BIT_ENABLE);
	}

	{
/*
		if(t_ASIFDLDLLUtil)
		{
			if(t_ASIFDLDLLUtil->RunDL())
			{
				WriteLogE("start file download thread result : fail");
			}
		}
*/
		if(RunDL())
		{
			WriteLogE("start file download thread result : fail");
		}

	}

	{
		Sleep(500);
	}	
	return 0;
}
//--------------------------------------------------------------------

INT32		CMainDlg::PreStartOperation()
{
	{
		t_LogicPWEvtMon->InitEnv();
	}

	{
		t_LogicApplyPolicy->ApplyBootPolicy();
	}
	
	if(t_EnvInfoOp->IsSysBootTime())
	{
		t_LogicPWEvtMon->RunBootTimeOp();

		WriteLogN("apply sys boot.");
	}

	{
		RemoveInvenFiles();
	}

	return 0;
}
//--------------------------------------------------------------------

INT32		CMainDlg::PreStartTimer()
{
	t_ThreadTimer->t_TimerUtil.EnableTimer(TIMER_ID_POLICY_APPLY_FA_CLEAR);
	t_ThreadTimer->t_TimerUtil.EnableTimer(TIMER_ID_POLICY_APPLY_FA_OP_CLEAR);		
	t_ThreadTimer->t_TimerUtil.EnableTimer(TIMER_ID_POLICY_APPLY_POWER);	
	t_ThreadTimer->t_TimerUtil.EnableTimer(TIMER_ID_POLICY_APPLY_IN_PTN_OP);	
	t_ThreadTimer->t_TimerUtil.EnableTimer(TIMER_ID_CHECK_CHANGE_NET_DRIVE);

	return 0;
}
//--------------------------------------------------------------------

INT32		CMainDlg::StartOperation()
{
	{
		t_ThreadTimer->t_TimerUtil.EnableTimer(TIMER_ID_WINDOWS_EVENT_HANDLER);
		t_ThreadTimer->t_TimerUtil.EnableTimer(TIMER_ID_LOGIN_SVR_AUTH);
	}
	return 0;
}
//--------------------------------------------------------------------

INT32		CMainDlg::StopSubClass()
{
	if(t_EnvInfoOp)
	{
		t_EnvInfoOp->SetMainContinue();
	}

	{
		StopDL();
		//if(t_ASIFDLDLLUtil)		t_ASIFDLDLLUtil->StopDL();
//		if(t_ASIEPSAPPDLLUtil)	t_ASIEPSAPPDLLUtil->Stop();
	}

	if(t_LogicApplyPolicy)
	{
		t_LogicApplyPolicy->SetEPSHookPolicy(1);
	}
	
	{
		t_ThreadTimer->SetContinue(0);
		SetER(StopThread_Common(t_ThreadTimer));
		WriteLogN("stop [timer] thread result : [%d]", g_nErrRtn);

		t_ThreadEvtMon->SetContinue(0);
		SetER(StopThread_Common(t_ThreadEvtMon));
		WriteLogN("stop [evt mon] thread result : [%d]", g_nErrRtn);

		t_ThreadSocket->SetContinue(0);
		SetER(StopThread_Common(t_ThreadSocket));
		WriteLogN("stop [socket] thread result : [%d]", g_nErrRtn);

		t_ThreadLog->SetContinue(0);
		SetER(StopThread_Common(t_ThreadLog));
		WriteLogN("stop [log] thread result : [%d]", g_nErrRtn);

		t_ThreadPoFaClear->SetContinue(0);
		SetER(StopThread_Common(t_ThreadPoFaClear));
		WriteLogN("stop [po_fa_clear] thread result : [%d]", g_nErrRtn);

		t_ThreadPoFePtnLo->SetContinue(0);
		SetER(StopThread_Common(t_ThreadPoFePtnLo));
		WriteLogN("stop [po_fe_ptn_lo] thread result : [%d]", g_nErrRtn);

		t_ThreadPoFeScan->SetContinue(0);
		SetER(StopThread_Common(t_ThreadPoFeScan));
		WriteLogN("stop [po_fe_scan] thread result : [%d]", g_nErrRtn);

		t_ThreadPoInPtnScan->SetContinue(0);
		SetER(StopThread_Common(t_ThreadPoInPtnScan));
		WriteLogN("stop [po_in_scan] thread result : [%d]", g_nErrRtn);
		
		t_ThreadChkHkNoti->SetContinue(0);
		SetER(StopThread_Common(t_ThreadChkHkNoti));
		WriteLogN("stop [chk_hk_noti] thread result : [%d]", g_nErrRtn);
	}

	return 0;
}
//--------------------------------------------------------------------

INT32		CMainDlg::DeleteSubClass()
{
	{
		SAFE_DELETE(t_LogicLgnAuth);
		SAFE_DELETE(t_LogicUdtAuth);
		SAFE_DELETE(t_LogicMgrAuth);
	}

	{
		SAFE_DELETE(t_LogicMgrCtrlRemoteCtrl);
		SAFE_DELETE(t_LogicMgrCtrlRemotePower);
		SAFE_DELETE(t_LogicMgrCtrlRemoteOrder);
		SAFE_DELETE(t_LogicMgrCtrlInstantMsg);
		SAFE_DELETE(t_LogicMgrCtrlHostRes);
		SAFE_DELETE(t_LogicMgrCtrlRestore);
	}

	{
		SAFE_DELETE(t_LogicMgrEnvLicense);
		SAFE_DELETE(t_LogicMgrEnvLog);
		SAFE_DELETE(t_LogicMgrEnvLogUnit);
		SAFE_DELETE(t_LogicMgrEnvNotifyInfo);
		SAFE_DELETE(t_LogicMgrEnvSelfProtectAgt);
		SAFE_DELETE(t_LogicMgrEnvSOrgLink);
		SAFE_DELETE(t_LogicMgrEnvTrustSubject);
	}

	{
		
		SAFE_DELETE(t_LogicMgrPoCtlPanel);
		SAFE_DELETE(t_LogicMgrPoDeployFile);
		SAFE_DELETE(t_LogicMgrPoPower);
		SAFE_DELETE(t_LogicMgrPoWinRun);

		SAFE_DELETE(t_LogicMgrPoHostRmInfo);
		SAFE_DELETE(t_LogicMgrPoHostRun);
		SAFE_DELETE(t_LogicMgrPoSvrInfoLgn);
		SAFE_DELETE(t_LogicMgrPoSvrInfoUdt);

		SAFE_DELETE(t_LogicMgrPoSch);

		SAFE_DELETE(t_LogicMgrPoCtlProc);
		SAFE_DELETE(t_LogicMgrPoSelfProtect);

		SAFE_DELETE(t_LogicMgrPoFaOp);
		SAFE_DELETE(t_LogicMgrPoFaClear);
		SAFE_DELETE(t_LogicMgrPoFaEnv);
		SAFE_DELETE(t_LogicMgrPoFaProc);
		SAFE_DELETE(t_LogicMgrPoFaBk);
		SAFE_DELETE(t_LogicMgrPoFaNotify);

		SAFE_DELETE(t_LogicMgrPoFePtnOp);
		SAFE_DELETE(t_LogicMgrPoFePtnLo);
		SAFE_DELETE(t_LogicMgrPoFePtnBL);
		SAFE_DELETE(t_LogicMgrPoFePtnWL);
		SAFE_DELETE(t_LogicMgrPoFeExclude);
		SAFE_DELETE(t_LogicMgrPoFeNotify);
		SAFE_DELETE(t_LogicMgrPoFeSinglePtn);
		
		{
			SAFE_DELETE(t_LogicMgrPoInPtnOp);
			SAFE_DELETE(t_LogicMgrPoInPtnBL);
			SAFE_DELETE(t_LogicMgrPoInPtnWL);
			SAFE_DELETE(t_LogicMgrPoInPtnEx);
			SAFE_DELETE(t_LogicMgrPoInPtnExTrust);
			SAFE_DELETE(t_LogicMgrPoInPtnSP);
			SAFE_DELETE(t_LogicMgrPoInPtnSPRule);
			SAFE_DELETE(t_LogicMgrPoInPtnNo);
			
			SAFE_DELETE(t_LogicMgrPoInAcDoc);
			SAFE_DELETE(t_LogicMgrPoInAcSf);
			SAFE_DELETE(t_LogicMgrPoInAcFile);

			SAFE_DELETE(t_LogicMgrPoInVulnOp);
			SAFE_DELETE(t_LogicMgrPoInVulnScan);
		}

	}

	{
		SAFE_DELETE(t_LogicMgrLogDeployFile);
		SAFE_DELETE(t_LogicMgrLogDoc);
		SAFE_DELETE(t_LogicMgrLogSecu);
		SAFE_DELETE(t_LogicMgrLogStatus);

		SAFE_DELETE(t_LogicMgrHost);
		SAFE_DELETE(t_LogicMgrHostSys);
		SAFE_DELETE(t_LogicMgrHostHw);
		SAFE_DELETE(t_LogicMgrHostSw);
		SAFE_DELETE(t_LogicMgrHostStatusPo);
		SAFE_DELETE(t_LogicMgrHostKey);

		SAFE_DELETE(t_LogicMgrUser);

	}

	{
		SAFE_DELETE(t_LogicMgrSiteFile);
		SAFE_DELETE(t_LogicMgrSiteVuln);
		SAFE_DELETE(t_LogicMgrSiteVulnScan);
		SAFE_DELETE(t_LogicMgrSiteVulnRepair);
		SAFE_DELETE(t_LogicMgrSiteVulnLock);
	}

	{
		SAFE_DELETE(t_LogicAuth);
		SAFE_DELETE(t_LogicInitLink);
		SAFE_DELETE(t_LogicLogEvent);
		SAFE_DELETE(t_LogicLogDocDScan);
	}

	{
		SAFE_DELETE(t_LogicApplyPolicy);
	}

	{
		SAFE_DELETE(t_LogicPWEvtMon);
		SAFE_DELETE(t_LogicLocalEnvLog);
		SAFE_DELETE(t_LogicLocalEnvAuth);
	}

	{
		SAFE_DELETE(t_ManageBaseUtil);

		SAFE_DELETE(t_ManageHostPolicy);
		SAFE_DELETE(t_ManageUserPolicy);

		SAFE_DELETE(t_ManageErrorCode);

		SAFE_DELETE(t_ManageEnvPolicy);		
		SAFE_DELETE(t_ManageLinkLicense);
	}

	{
		SAFE_DELETE(t_ThreadTimer);
		SAFE_DELETE(t_ThreadSocket);
		SAFE_DELETE(t_ThreadLog);
		SAFE_DELETE(t_ThreadPoFaClear);
		SAFE_DELETE(t_ThreadPoFePtnLo);
		SAFE_DELETE(t_ThreadPoFeScan);
		SAFE_DELETE(t_ThreadPoInPtnScan);
		SAFE_DELETE(t_ThreadChkHkNoti);
		SAFE_DELETE(t_ThreadEvtMon);
	}

	{
		SAFE_DELETE(t_ManageFileDown);
		SAFE_DELETE(t_ManageLogicTimer);
//		SAFE_DELETE(t_ManageDeviceMedia);
	}

	{
		SAFE_DELETE(t_ValidTimeUtil);
		SAFE_DELETE(t_DeployPolicyUtil);
		SAFE_DELETE(t_ExecuteFileUtil);
		SAFE_DELETE(t_DocBackupUtil);
		SAFE_DELETE(t_FileDeleteUtil);
		SAFE_DELETE(t_ComFuncUtil);
	}

	{
		SAFE_DELETE(t_EnvInfoOp);
		SAFE_DELETE(t_EnvInfo);
	}

	{
		SAFE_DELETE(t_LgnCltUtil);
		SAFE_DELETE(t_MgrCltUtil);
		SAFE_DELETE(t_UdtCltUtil);
		SAFE_DELETE(t_LinkSvrUtil);
	}

	{
		SAFE_DELETE(t_ASICOMPDLLUtil);
		SAFE_DELETE(t_RemoveLogDLLUtil);
		SAFE_DELETE(t_ASIFFDLLUtil);
//		SAFE_DELETE(t_ASIFDLDLLUtil);
		SAFE_DELETE(t_NetworkDLLUtil);
		SAFE_DELETE(t_SeedDLLUtil);
//		SAFE_DELETE(t_ASIEPSAPPDLLUtil);
//		SAFE_DELETE(t_ASIWENGDLLUtil);
		SAFE_DELETE(t_ProcInfoDLLUtil);
		SAFE_DELETE(t_DevInfoDLLUtil);
	}

	{
		SAFE_DELETE(t_ResInfoDLLUtil);
	}
	return 0;
}
//--------------------------------------------------------------------

INT32		CMainDlg::CheckIntegrity()
{
	return 0;
}
//--------------------------------------------------------------------
