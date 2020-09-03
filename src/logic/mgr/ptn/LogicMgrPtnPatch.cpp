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
#include "LogicMgrPtnPatch.h"

//---------------------------------------------------------------------------

CLogicMgrPtnPatch*		t_LogicMgrPtnPatch = NULL;

//---------------------------------------------------------------------------

CLogicMgrPtnPatch::CLogicMgrPtnPatch()
{
	t_LogicPtnPatch			= new CLogicPtnPatch();
	
	m_strLogicName		= "mgr agt ptn patch";
	
	m_nPackageType		= SS_PACKAGE_TYPE_NPMS;
	m_nPolicyType		= 0;
	m_nSSPoSeqIdx		= 0;
	m_nAgtPktEditCode	= G_CODE_COMMON_EDIT;	
	
	m_nEvtObjType		= 0;
	m_nEvtObjCode		= 0;

	m_nInitLogic		= 0;
	//m_nInitPatchUtil	= SS_PTN_PATCH_UTIL_STATUS_NONE;
	m_nInitPatchWsus	= SS_PTN_PATCH_WSUS_STATUS_NONE;
	m_nInitPtnDeploy	= SS_PTN_DEPLOY_STATUS_NONE;
}
//---------------------------------------------------------------------------

CLogicMgrPtnPatch::~CLogicMgrPtnPatch()
{
	SAFE_DELETE(t_LogicPtnPatch);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32	CLogicMgrPtnPatch::InitPtnPatch()
{	
	return 0;
}
//---------------------------------------------------------------------------

INT32	CLogicMgrPtnPatch::FreePtnPatch()
{
	m_nInitLogic = 0;
//	m_nInitPatchUtil = SS_PTN_PATCH_UTIL_STATUS_NONE;
	m_nInitPatchWsus = SS_PTN_PATCH_WSUS_STATUS_NONE;
	m_nInitPtnDeploy = SS_PTN_DEPLOY_STATUS_NONE;
	m_strWScanFileName = "";
	return 0;
}
//---------------------------------------------------------------------------

INT32	CLogicMgrPtnPatch::ReloadPtnPatch()
{
	FreePtnPatch();
	return InitPtnPatch();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32	CLogicMgrPtnPatch::IsEnableRunMode(UINT32 nType)
{
	return 0;
}
//---------------------------------------------------------------------------

INT32	CLogicMgrPtnPatch::SetEnableRunMode(UINT32 nType, UINT32 nMode)
{
	return 0;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32	CLogicMgrPtnPatch::ChkPtnPatchWsus()
{
	return 0;
}
//---------------------------------------------------------------------------

INT32	CLogicMgrPtnPatch::ChkPtnPatchWsusUnit(PDB_PTN_PATCH_WSUS pdata, UINT32 nChkOnly)
{
	return 0;
}
//---------------------------------------------------------------------------

INT32	CLogicMgrPtnPatch::ApplyPtnPatchWsus(UINT32 nID)
{	
	return 0;
}
//---------------------------------------------------------------------------

INT32		CLogicMgrPtnPatch::AddDpDownInfoWsus(PDB_PTN_PATCH_WSUS pdata)
{
	return 0;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32	CLogicMgrPtnPatch::InitPtnDeploy()
{
	return 0;
}
//---------------------------------------------------------------------------

INT32	CLogicMgrPtnPatch::ChkPtnDeploy()
{
	return 0;
}
//---------------------------------------------------------------------------

INT32	CLogicMgrPtnPatch::ChkPtnDeployUnit(PDB_PTN_DEPLOY pdata, UINT32 nChkOnly)
{
	return 0;
}
//---------------------------------------------------------------------------

INT32		CLogicMgrPtnPatch::AddDownloadPtnDeployUnit(PDB_PTN_DEPLOY pdata)
{
	return 0;
}
//---------------------------------------------------------------------------

INT32	CLogicMgrPtnPatch::ApplyPtnDeploy(UINT32 nID)
{	
	return 0;
}
//---------------------------------------------------------------------------
