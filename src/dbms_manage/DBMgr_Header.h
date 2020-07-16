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


#ifndef	DBMGR_HEADER_H_80603AB4_2E87_426E_B9AC_25AF77D0ECEF
#define DBMGR_HEADER_H_80603AB4_2E87_426E_B9AC_25AF77D0ECEF


#include "DBMgrHost.h"
#include "DBMgrHostHw.h"
#include "DBMgrHostSys.h"
#include "DBMgrHostSw.h"
#include "DBMgrHostStatusPo.h"
#include "DBMgrHostPolicy.h"
#include "DBMgrHostKey.h"

#include "DBMgrUser.h"
#include "DBMgrUserPolicy.h"

#include "DBMgrEnvLicense.h"
#include "DBMgrEnvLog.h"
#include "DBMgrEnvLogUnit.h"
#include "DBMgrEnvNotifyInfo.h"
#include "DBMgrEnvSelfProtectAgt.h"
#include "DBMgrEnvSOrgLink.h"
#include "DBMgrEnvTrustSubject.h"
#include "DBMgrEnvPolicy.h"

#include "DBMgrErrorCode.h"
#include "DBMgrOsType.h"

#include "DBMgrSiteFile.h"
#include "DBMgrSiteVuln.h"
#include "DBMgrSiteVulnScan.h"
#include "DBMgrSiteVulnRepair.h"
#include "DBMgrSiteVulnLock.h"

#include "DBMgrLinkLicense.h"

#include "DBMgrLogDeployFile.h"
#include "DBMgrLogDoc.h"
#include "DBMgrLogEvent.h"
#include "DBMgrLogSecu.h"
#include "DBMgrLogDocDScan.h"
#include "DBMgrLogDocHost.h"
#include "DBMgrLogStatus.h"

#include "DBMgrPoCtlPanel.h"
#include "DBMgrPoCtlPanelPkg.h"
#include "DBMgrPoCtlPanelUnit.h"
#include "DBMgrPoCtlProc.h"
#include "DBMgrPoCtlProcPkg.h"
#include "DBMgrPoCtlProcUnit.h"
#include "DBMgrPoDeployFile.h"
#include "DBMgrPoDeployFilePkg.h"
#include "DBMgrPoDeployFileUnit.h"
#include "DBMgrPoDeployFileUnitInfoPkg.h"
#include "DBMgrPoDeployFileUnitChkPkg.h"
#include "DBMgrPoDeployFileUnitTarPkg.h"
#include "DBMgrPoDeployFileUnitSchPkg.h"
#include "DBMgrPoDeployFileInfoUnit.h"
#include "DBMgrPoDeployFileChkUnit.h"
#include "DBMgrPoDeployFileTarUnit.h"
#include "DBMgrPoDeployFileSchUnit.h"
#include "DBMgrPoHostRmInfo.h"
#include "DBMgrPoHostRun.h"

#include "DBMgrPoSch.h"
#include "DBMgrPoSchPkg.h"
#include "DBMgrPoSchUnit.h"

#include "DBMgrPoPower.h"
#include "DBMgrPoPowerPkg.h"
#include "DBMgrPoPowerUnit.h"
#include "DBMgrPoWinRun.h"
#include "DBMgrPoSelfProtect.h"
#include "DBMgrPoSelfProtectPkg.h"
#include "DBMgrPoSelfProtectUnit.h"
#include "DBMgrPoSvrInfoLgn.h"
#include "DBMgrPoSvrInfoUdt.h"

#include "DBMgrPoFaOp.h"
#include "DBMgrPoFaOpPkg.h"
#include "DBMgrPoFaOpUnit.h"
#include "DBMgrPoFaOpUnitObjPkg.h"
#include "DBMgrPoFaOpUnitSubPkg.h"
#include "DBMgrPoFaOpUnitSchPkg.h"
#include "DBMgrPoFaOpUnitRulPkg.h"
#include "DBMgrPoFaOpObjUnit.h"
#include "DBMgrPoFaOpSubUnit.h"
#include "DBMgrPoFaOpSchUnit.h"
#include "DBMgrPoFaClear.h"
#include "DBMgrPoFaClearPkg.h"
#include "DBMgrPoFaClearUnit.h"
#include "DBMgrPoFaProc.h"
#include "DBMgrPoFaProcPkg.h"
#include "DBMgrPoFaProcUnit.h"
#include "DBMgrPoFaEnv.h"
#include "DBMgrPoFaEnvPkg.h"
#include "DBMgrPoFaEnvUnit.h"
#include "DBMgrPoFaBk.h"
#include "DBMgrPoFaNotify.h"
#include "DBMgrPoFaNotifyPkg.h"

#include "DBMgrPoFePtnOp.h"
#include "DBMgrPoFePtnLo.h"
#include "DBMgrPoFePtnBL.h"
#include "DBMgrPoFePtnWL.h"
#include "DBMgrPoFeNotify.h"
#include "DBMgrPoFeNotifyPkg.h"
#include "DBMgrPoFeExclude.h"
#include "DBMgrPoFeExcludePkg.h"
#include "DBMgrPoFeExcludeUnit.h"
#include "DBMgrPoFeSinglePtn.h"
#include "DBMgrPoFeSinglePtnUnit.h"

#include "DBMgrSchemaInfo.h"
#include "DBMgrLocalEnvLog.h"
#include "DBMgrLocalEnvAuth.h"

#include "DBMgrPoInPtnOp.h"
#include "DBMgrPoInPtnOpPkg.h"
#include "DBMgrPoInPtnOpUnit.h"
#include "DBMgrPoInPtnBL.h"
#include "DBMgrPoInPtnBLPkg.h"
#include "DBMgrPoInPtnBLUnit.h"
#include "DBMgrPoInPtnWL.h"
#include "DBMgrPoInPtnWLPkg.h"
#include "DBMgrPoInPtnWLUnit.h"
#include "DBMgrPoInPtnEx.h"
#include "DBMgrPoInPtnExPkg.h"
#include "DBMgrPoInPtnExUnit.h"
#include "DBMgrPoInPtnExTrust.h"
#include "DBMgrPoInPtnSP.h"
#include "DBMgrPoInPtnSPPkg.h"
#include "DBMgrPoInPtnSPUnit.h"
#include "DBMgrPoInPtnSPRule.h"
#include "DBMgrPoInPtnNo.h"
#include "DBMgrPoInPtnNoPkg.h"

#include "DBMgrPoInAcDoc.h"
#include "DBMgrPoInAcDocPkg.h"
#include "DBMgrPoInAcDocUnit.h"
#include "DBMgrPoInAcDocUnitObjPkg.h"
#include "DBMgrPoInAcDocUnitSubPkg.h"
#include "DBMgrPoInAcDocObjUnit.h"
#include "DBMgrPoInAcDocSubUnit.h"
#include "DBMgrPoInAcSf.h"
#include "DBMgrPoInAcSfPkg.h"
#include "DBMgrPoInAcSfUnit.h"
#include "DBMgrPoInAcSfUnitObjPkg.h"
#include "DBMgrPoInAcSfUnitSubPkg.h"
#include "DBMgrPoInAcSfObjUnit.h"
#include "DBMgrPoInAcSfSubUnit.h"
#include "DBMgrPoInAcFile.h"
#include "DBMgrPoInAcFilePkg.h"
#include "DBMgrPoInAcFileUnit.h"
#include "DBMgrPoInAcFileUnitObjPkg.h"
#include "DBMgrPoInAcFileUnitSubPkg.h"
#include "DBMgrPoInAcFileUnitSchPkg.h"
#include "DBMgrPoInAcFileUnitRulPkg.h"
#include "DBMgrPoInAcFileObjUnit.h"
#include "DBMgrPoInAcFileSubUnit.h"
#include "DBMgrPoInAcFileSchUnit.h"

#include "DBMgrPoInVulnOp.h"
#include "DBMgrPoInVulnOpPkg.h"
#include "DBMgrPoInVulnScan.h"
#include "DBMgrPoInVulnScanPkg.h"
#include "DBMgrPoInVulnScanUnit.h"
#include "DBMgrPoInVulnScanUnitPkg.h"

#include "DBMgrPoInRegVuln.h"
#include "DBMgrPoInRegVulnPkg.h"
#include "DBMgrPoInRegVulnUnit.h"
#include "DBMgrPoInRegSvc.h"
#include "DBMgrPoInRegSvcUnit.h"
#include "DBMgrPoInRegSvcSubUnit.h"
#include "DBMgrPoInRegSvcPkg.h"
#include "DBMgrPoInRegSvcUnitObjPkg.h"
#include "DBMgrPoInRegSvcUnitSubPkg.h"
#include "DBMgrPoInRegSvcObjUnit.h"
#include "DBMgrPoInRegSW.h"
#include "DBMgrPoInRegSWPkg.h"
#include "DBMgrPoInRegSWUnit.h"
#include "DBMgrPoInRegSWSubUnit.h"
#include "DBMgrPoInRegSWObjUnit.h"
#include "DBMgrPoInRegSWUnitSubPkg.h"
#include "DBMgrPoInRegSWUnitObjPkg.h"
#include "DBMgrPoInRegSys.h"
#include "DBMgrPoInRegSysPkg.h"
#include "DBMgrPoInRegSysUnit.h"




#endif //DBMGR_HEADER_H_80603AB4_2E87_426E_B9AC_25AF77D0ECEF
