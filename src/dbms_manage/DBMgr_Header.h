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
#include "DBMgrHostPatch.h"
#include "DBMgrHostVulnRst.h"
#include "DBMgrHostVulnRstUnit.h"

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
#include "DBMgrEnvLocal.h"
#include "DBMgrEnvSocket.h"

#include "DBMgrErrorCode.h"
#include "DBMgrOsType.h"
#include "DBMgrDocDeleteInfo.h"

#include "DBMgrSiteFile.h"
#include "DBMgrSiteVuln.h"
#include "DBMgrSiteVulnScan.h"

#include "DBMgrLinkLicense.h"

#include "DBMgrLogDeployFile.h"
#include "DBMgrLogDoc.h"
#include "DBMgrLogEvent.h"
#include "DBMgrLogSecu.h"
#include "DBMgrLogDocDScan.h"
#include "DBMgrLogDocHost.h"
#include "DBMgrLogPatch.h"
#include "DBMgrLogDevice.h"
#include "DBMgrLogRs.h"
#include "DBMgrLogRsBk.h"

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
#include "DBMgrPoHostNotify.h"
#include "DBMgrPoHostNotifyPkg.h"
#include "DBMgrPoHostNotifyUnit.h"

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
#include "DBMgrPoFaDelFileAfterBoot.h"
#include "DBMgrPoFaInotifyFile.h"

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

#include "DBMgrPoInVulnOp.h"
#include "DBMgrPoInVulnOpPkg.h"
#include "DBMgrPoInVulnScan.h"
#include "DBMgrPoInVulnScanPkg.h"
#include "DBMgrPoInVulnScanUnit.h"
#include "DBMgrPoInVulnScanUnitPkg.h"

#include "DBMgrPoInVulnAx.h"
#include "DBMgrPoInVulnAxPkg.h"
#include "DBMgrPoInVulnAxUnit.h"
#include "DBMgrPoInVulnEditApp.h"
#include "DBMgrPoInVulnEditAppPkg.h"
#include "DBMgrPoInVulnEditAppUnit.h"
#include "DBMgrPoInVulnSw.h"
#include "DBMgrPoInVulnSwPkg.h"
#include "DBMgrPoInVulnSwUnit.h"
#include "DBMgrPoInVulnSecuUsb.h"
#include "DBMgrPoInVulnSecuUsbPkg.h"
#include "DBMgrPoInVulnSecuUsbUnit.h"
#include "DBMgrPoInVulnQna.h"
#include "DBMgrPoInVulnQnaPkg.h"
#include "DBMgrPoInVulnQnaUnit.h"
#include "DBMgrPoInVulnPatchException.h"
#include "DBMgrPoInVulnPatchExceptionPkg.h"
#include "DBMgrPoInVulnPatchExceptionUnit.h"

#include "DBMgrPoInRsOp.h"
#include "DBMgrPoInRsOpPkg.h"
#include "DBMgrPoInRsOpUnit.h"
#include "DBMgrPoInRsOpUnitSubPkg.h"
#include "DBMgrPoInRsOpUnitObjPkg.h"
#include "DBMgrPoInRsOpSubUnit.h"
#include "DBMgrPoInRsOpObjUnit.h"
#include "DBMgrPoInRsBk.h"
#include "DBMgrPoInRsNo.h"
#include "DBMgrPoInRsNoPkg.h"

#include "DBMgrPoInDevOOp.h"
#include "DBMgrPoInDevOBL.h"
#include "DBMgrPoInDevOBLPkg.h"
#include "DBMgrPoInDevOWL.h"
#include "DBMgrPoInDevOWLPkg.h"
#include "DBMgrPoInDevOEx.h"
#include "DBMgrPoInDevOExPkg.h"
#include "DBMgrPoInDevOExUnit.h"
#include "DBMgrPoInDevOInfo.h"
#include "DBMgrPoInDevONotify.h"
#include "DBMgrPoInDevONotifyPkg.h"
#include "DBMgrPoDvDefault.h"

#include "DBMgrPoPmOp.h"
#include "DBMgrPoPmDm.h"
#include "DBMgrPoPmDmPkg.h"
#include "DBMgrPoPmDmUnit.h"
#include "DBMgrPoPmScan.h"
#include "DBMgrPoPmScanPkg.h"
#include "DBMgrPoPmScanUnit.h"
#include "DBMgrPoPmEx.h"
#include "DBMgrPoPmExPkg.h"
#include "DBMgrPoPmExUnit.h"
#include "DBMgrPoPmNo.h"
#include "DBMgrPoPmNoPkg.h"

//------------------------------------------------------------------------------------------

#include "DBMgrPtnVersion.h"

#include "DBMgrPtnPatch.h"
#include "DBMgrPtnPatchFile.h"
#include "DBMgrPtnPatchWsus.h"
#include "DBMgrPtnPatchScan.h"
#include "DBMgrPtnPatchScanEnv.h"
#include "DBMgrPtnPatchScanEnvUnit.h"
#include "DBMgrPtnDeploy.h"
#include "DBMgrPtnVuln.h"
#include "DBMgrPtnVulnScan.h"
#include "DBMgrPtnVulnMP.h"

#include "DBMgrPtnProcFile.h"




#endif //DBMGR_HEADER_H_80603AB4_2E87_426E_B9AC_25AF77D0ECEF
