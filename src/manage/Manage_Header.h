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


#ifndef	MANAGE_HEADER_H_12CC793F_06F3_411C_9419_61F453A83EDC
#define	MANAGE_HEADER_H_12CC793F_06F3_411C_9419_61F453A83EDC

#include "ManageBase.h"
#include "ManagePoBase.h"

#include "ManageBaseUtil.h"

#include "ManageHost.h"
#include "ManageHostHw.h"
#include "ManageHostSys.h"
#include "ManageHostSw.h"
#include "ManageHostStatusPo.h"
#include "ManageHostPolicy.h"
#include "ManageHostKey.h"

#include "ManageUser.h"
#include "ManageUserPolicy.h"

#include "ManageEnvLicense.h"
#include "ManageEnvLog.h"
#include "ManageEnvLogUnit.h"
#include "ManageEnvNotifyInfo.h"
#include "ManageEnvSelfProtectAgt.h"
#include "ManageEnvSOrgLink.h"
#include "ManageEnvTrustSubject.h"
#include "ManageEnvPolicy.h"

#include "ManageErrorCode.h"
#include "ManageOsType.h"
#include "ManageSiteFile.h"
#include "ManageSiteVuln.h"
#include "ManageSiteVulnScan.h"
#include "ManageSiteVulnRepair.h"
#include "ManageSiteVulnLock.h"

#include "ManageLinkLicense.h"

#include "ManageLogDeployFile.h"
#include "ManageLogDoc.h"
#include "ManageLogEvent.h"
#include "ManageLogSecu.h"
#include "ManageLogDocDScan.h"
#include "ManageLogDocHost.h"
#include "ManageLogStatus.h"

#include "ManagePoCtlPanel.h"
#include "ManagePoCtlPanelPkg.h"
#include "ManagePoCtlPanelUnit.h"
#include "ManagePoCtlProc.h"
#include "ManagePoCtlProcPkg.h"
#include "ManagePoCtlProcUnit.h"
#include "ManagePoDeployFile.h"
#include "ManagePoDeployFilePkg.h"
#include "ManagePoDeployFileUnit.h"
#include "ManagePoDeployFileUnitInfoPkg.h"
#include "ManagePoDeployFileUnitChkPkg.h"
#include "ManagePoDeployFileUnitTarPkg.h"
#include "ManagePoDeployFileUnitSchPkg.h"
#include "ManagePoDeployFileInfoUnit.h"
#include "ManagePoDeployFileChkUnit.h"
#include "ManagePoDeployFileTarUnit.h"
#include "ManagePoDeployFileSchUnit.h"
#include "ManagePoHostRmInfo.h"
#include "ManagePoHostRun.h"

#include "ManagePoSch.h"
#include "ManagePoSchPkg.h"
#include "ManagePoSchUnit.h"

#include "ManagePoPower.h"
#include "ManagePoPowerPkg.h"
#include "ManagePoPowerUnit.h"
#include "ManagePoWinRun.h"
#include "ManagePoSelfProtect.h"
#include "ManagePoSelfProtectPkg.h"
#include "ManagePoSelfProtectUnit.h"
#include "ManagePoSvrInfoLgn.h"
#include "ManagePoSvrInfoUdt.h"
#include "ManagePoFaOp.h"
#include "ManagePoFaOpPkg.h"
#include "ManagePoFaOpUnit.h"
#include "ManagePoFaOpUnitObjPkg.h"
#include "ManagePoFaOpUnitSubPkg.h"
#include "ManagePoFaOpUnitSchPkg.h"
#include "ManagePoFaOpUnitRulPkg.h"
#include "ManagePoFaOpObjUnit.h"
#include "ManagePoFaOpSubUnit.h"
#include "ManagePoFaOpSchUnit.h"
#include "ManagePoFaClear.h"
#include "ManagePoFaClearPkg.h"
#include "ManagePoFaClearUnit.h"
#include "ManagePoFaProc.h"
#include "ManagePoFaProcPkg.h"
#include "ManagePoFaProcUnit.h"
#include "ManagePoFaEnv.h"
#include "ManagePoFaEnvPkg.h"
#include "ManagePoFaEnvUnit.h"
#include "ManagePoFaBk.h"
#include "ManagePoFaNotify.h"
#include "ManagePoFaNotifyPkg.h"

#include "ManagePoFePtnOp.h"
#include "ManagePoFePtnLo.h"
#include "ManagePoFePtnBL.h"
#include "ManagePoFePtnWL.h"
#include "ManagePoFeNotify.h"
#include "ManagePoFeNotifyPkg.h"
#include "ManagePoFeExclude.h"
#include "ManagePoFeExcludePkg.h"
#include "ManagePoFeExcludeUnit.h"
#include "ManagePoFeSinglePtn.h"
#include "ManagePoFeSinglePtnUnit.h"

#include "ManageLocalEnvLog.h"
#include "ManageLocalEnvAuth.h"

#include "ManageFileDown.h"
#include "ManageLogicTimer.h"
#include "ManageWinSession.h"
#include "ManageSysDrive.h"
#include "ManageEvtMon.h"
//#include "ManageDeviceMedia.h"

// Nanny-On Manage
#include "ManagePoInPtnOp.h"
#include "ManagePoInPtnOpPkg.h"
#include "ManagePoInPtnOpUnit.h"
#include "ManagePoInPtnBL.h"
#include "ManagePoInPtnBLPkg.h"
#include "ManagePoInPtnBLUnit.h"
#include "ManagePoInPtnWL.h"
#include "ManagePoInPtnWLPkg.h"
#include "ManagePoInPtnWLUnit.h"
#include "ManagePoInPtnEx.h"
#include "ManagePoInPtnExPkg.h"
#include "ManagePoInPtnExUnit.h"
#include "ManagePoInPtnExTrust.h"
#include "ManagePoInPtnSP.h"
#include "ManagePoInPtnSPPkg.h"
#include "ManagePoInPtnSPUnit.h"
#include "ManagePoInPtnSPRule.h"
#include "ManagePoInPtnNo.h"
#include "ManagePoInPtnNoPkg.h"

#include "ManagePoInAcDoc.h"
#include "ManagePoInAcDocPkg.h"
#include "ManagePoInAcDocUnit.h"
#include "ManagePoInAcDocUnitObjPkg.h"
#include "ManagePoInAcDocUnitSubPkg.h"
#include "ManagePoInAcDocObjUnit.h"
#include "ManagePoInAcDocSubUnit.h"
#include "ManagePoInAcSf.h"
#include "ManagePoInAcSfPkg.h"
#include "ManagePoInAcSfUnit.h"
#include "ManagePoInAcSfUnitObjPkg.h"
#include "ManagePoInAcSfUnitSubPkg.h"
#include "ManagePoInAcSfObjUnit.h"
#include "ManagePoInAcSfSubUnit.h"
#include "ManagePoInAcFile.h"
#include "ManagePoInAcFilePkg.h"
#include "ManagePoInAcFileUnit.h"
#include "ManagePoInAcFileUnitObjPkg.h"
#include "ManagePoInAcFileUnitSubPkg.h"
#include "ManagePoInAcFileUnitSchPkg.h"
#include "ManagePoInAcFileUnitRulPkg.h"
#include "ManagePoInAcFileObjUnit.h"
#include "ManagePoInAcFileSubUnit.h"
#include "ManagePoInAcFileSchUnit.h"

#include "ManagePoInVulnOp.h"
#include "ManagePoInVulnOpPkg.h"
#include "ManagePoInVulnScan.h"
#include "ManagePoInVulnScanPkg.h"
#include "ManagePoInVulnScanUnit.h"
#include "ManagePoInVulnScanUnitPkg.h"

#endif //MANAGE_HEADER_H_12CC793F_06F3_411C_9419_61F453A83EDC
