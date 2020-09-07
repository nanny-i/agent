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
#include "LogicMgrPtnGBO.h"

//---------------------------------------------------------------------------

CLogicMgrPtnGBO*		t_LogicMgrPtnGBO = NULL;

//---------------------------------------------------------------------------

CLogicMgrPtnGBO::CLogicMgrPtnGBO()
{
	m_strLogicName		= "mgr agt ptn gbo";
	
	m_nPackageType		= SS_PACKAGE_TYPE_NOMS;
	m_nPolicyType		= SS_POLICY_TYPE_IN_PTN_BL;
	m_nSSPoSeqIdx		= 0;
	m_nAgtPktEditCode	= G_CODE_COMMON_EDIT;	
	
	m_nEvtObjType		= 0;
	m_nEvtObjCode		= 0;

	m_nInitLogic		= 0;	
}
//---------------------------------------------------------------------------

CLogicMgrPtnGBO::~CLogicMgrPtnGBO()
{
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32	CLogicMgrPtnGBO::InitPtnGBO()
{	
	m_nInitLogic = 1;
	return 0;
}
//---------------------------------------------------------------------------

INT32	CLogicMgrPtnGBO::FreePtnGBO()
{
	m_nInitLogic = 0;
	return 0;
}
//---------------------------------------------------------------------------

INT32	CLogicMgrPtnGBO::ReloadPtnGBO()
{
	FreePtnGBO();
	return InitPtnGBO();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------