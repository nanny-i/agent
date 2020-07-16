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
#include "LogicMgrPoInPtnExTrust.h"

//---------------------------------------------------------------------------

CLogicMgrPoInPtnExTrust*		t_LogicMgrPoInPtnExTrust = NULL;

//---------------------------------------------------------------------------

CLogicMgrPoInPtnExTrust::CLogicMgrPoInPtnExTrust()
{
	t_ManagePoInPtnExTrust		= new CManagePoInPtnExTrust();
	
	t_ManagePoInPtnExTrust->LoadDBMS();
	
	m_strLogicName		= "mgr agt po in ptn ex trust";
	
	m_nPolicyUnitType	= SS_POLICY_UNIT_TYPE_IN_PTN_EX_TRUST;
	m_nAgtPktEditCode	= G_CODE_COMMON_EDIT;	
	
	m_nEvtObjType		= EVENT_OBJECT_TYPE_POLICY_UNIT;
	m_nEvtObjCode		= EVENT_OBJECT_CODE_POLICY_UNIT_IN_PTN_EX_TRUST;
}
//---------------------------------------------------------------------------

CLogicMgrPoInPtnExTrust::~CLogicMgrPoInPtnExTrust()
{
	SAFE_DELETE(t_ManagePoInPtnExTrust);
}
//---------------------------------------------------------------------------
INT32		CLogicMgrPoInPtnExTrust::AnalyzePkt_FromMgr_Ext()
{
	return SetHdrAndRtn(AZPKT_CB_RTN_SUCCESS);
}
//---------------------------------------------------------------------------

INT32		CLogicMgrPoInPtnExTrust::AnalyzePkt_FromMgr_Add_Ext()
{
	DB_PO_IN_PTN_EX_TRUST data;

	if(t_ManagePoInPtnExTrust->GetPkt(RecvToken, data))		return AZPKT_CB_RTN_PKT_INVALID;

	data.tDPH.nRegDate = GetCurrentDateTimeInt();
	SetPoInPtnExTrsut(data);
	
	return AZPKT_CB_RTN_SUCCESS_END;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

INT32		CLogicMgrPoInPtnExTrust::CheckPtnLifeCycle()
{
/*
	CHAR szDLLName[CHAR_MAX_SIZE] = {0, };
	CASIWEngDLLUtil tWEDLLUtil;
	TListWEngWLEx tWEngWLExList;

	TListID tDelIDList;

	if(tWEDLLUtil.LoadLibraryExt(FormatString(szDLLName, "%s/dll/asi_weng.dll", t_EnvInfo->m_strRootPath.c_str())))
	{
		WriteLogE("load library fail : [%s][%d]", szDLLName, errno);
		return -16;
	}

	{
		tWEDLLUtil.Init();
		tWEDLLUtil.InitDB();
	}

	{
		PDB_PO_IN_PTN_BL pCurPolicy = (PDB_PO_IN_PTN_BL)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_IN_PTN_BL);
		if(!pCurPolicy)
		{
			return -1;
		}

		if(LoadWEngPtn(&tWEDLLUtil, pCurPolicy->tDPFI.strSaveName, pCurPolicy->tDPFI.strFileHash))
		{
			return -2;
		}
	}

	{
		PDB_PO_IN_PTN_WL pCurPolicy = (PDB_PO_IN_PTN_WL)t_DeployPolicyUtil->GetCurPoPtr(SS_POLICY_TYPE_IN_PTN_WL);
		if(!pCurPolicy)
		{
			return -11;
		}
		if(LoadWEngPtn(&tWEDLLUtil, pCurPolicy->tDPFI.strSaveName, pCurPolicy->tDPFI.strFileHash))
		{
			return -12;
		}
	}

	{
		TListID tIDList;
		t_ManagePoInPtnExTrust->GetItemIDList(tIDList);

		TListIDItor begin, end;
		begin = tIDList.begin();	end = tIDList.end();
		for(begin; begin != end; begin++)
		{
			PDB_PO_IN_PTN_EX_TRUST pdata = t_ManagePoInPtnExTrust->FindItem(*begin);
			if(!pdata)	continue;
			
			ASI_WENG_WL_EX tAWWE;
			memset(&tAWWE, 0, sizeof(ASI_WENG_WL_EX));
			HexToBinLen(pdata->strFileKey.c_str(), (PBYTE)(tAWWE.acWhiteHash), SHA512_BLOCK_SIZE);

			DWORD dwFileType = WE_INVALID_FILE;
			tWEDLLUtil.GetWL(NULL, &tAWWE, sizeof(ASI_WENG_WL_EX), &dwFileType);

			switch(tAWWE.dwCategory)
			{		
				case WE_GLOBAL_WHITE:
				case WE_GLOBAL_BLACK: 
				{
					WriteLogN("[%s] find file key in admin make ptn[%s]... remote key from auto ptn data : [%s]:[%d]->[%d]", m_strLogicName.c_str(), tAWWE.acDbName, pdata->strOFName, pdata->nBlockMode, tAWWE.dwCategory);
					tDelIDList.push_back(*begin);
					break;
				}
				default:		break;
			}
		}
	}

	{
		tWEDLLUtil.UnInitDB();
		tWEDLLUtil.FreeLibraryExt();
	}

	if(tDelIDList.size())
	{
		TListIDItor begin, end;
		begin = tDelIDList.begin();	end = tDelIDList.end();
		for(begin; begin != end; begin++)
		{
			t_ManagePoInPtnExTrust->DelPoInPtnExTrust(*begin);
		}
		WriteLogN("[%s] remote key from auto ptn data success : [%d]", m_strLogicName.c_str(), tDelIDList.size());
	}
*/	
	return 0;

}
//---------------------------------------------------------------------------


/*
INT32		CLogicMgrPoInPtnExTrust::LoadWEngPtn(CASIWEngDLLUtil* pWEDLLUtil, String strFileName, String strFileHash)
{
	DWORD dwPtnCnt = 0;
	int nRetVal = 0;
	String strFullPath;
	CHAR szFileHash[CHAR_MAX_SIZE] = {0, };
	strFullPath = SPrintf("%s/%s/%s", t_EnvInfo->m_strRootPath.c_str(), STR_WENG_PTN_FILE, strFileName.c_str());
	if(is_file(strFullPath.c_str()) == 0)
	{
		WriteLogE("[%s] not find op ptn file [%s]", m_strLogicName.c_str(), strFullPath.c_str());
		return -1;
	}

	
	nRetVal = SHAFile(ASIHASH_SHA_LEN_TYPE_256, strFullPath.c_str(), szFileHash, CHAR_MAX_SIZE);
	if(nRetVal != 0)
	{
		WriteLogE("[%s] fail to get hash value [%d]", m_strLogicName.c_str(), nRetVal);
		return -2;
	}

	if(strFileHash.compare(szFileHash))
	{
		WriteLogE("[%s] invalid ptn op pattern file hash : [%s][%s]", m_strLogicName.c_str(), strFullPath.c_str(), szFileHash);
		return -100;
	}

	if(SetER(pWEDLLUtil->LoadWL(strFullPath.c_str(), NULL, 0, &dwPtnCnt)))
	{
		WriteLogE("[%s] load ptn op fail : [%s]", m_strLogicName.c_str(), pWEDLLUtil->GetLastError());
		return -200;
	}	
	return 0;
}
*/
//--------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void		CLogicMgrPoInPtnExTrust::SetPoInPtnExTrsut(DB_PO_IN_PTN_EX_TRUST& data)
{
	{
		if(data.strOFName.find("%") == string::npos && data.strSFName.find("%") == string::npos)
		{
			WriteLogN("[%s] remain ptn ex trust log to file : of[%s]:sf[%s]:bm:[%d]", 
				m_strLogicName.c_str(), data.strOFName.c_str(), data.strSFName.c_str(), data.nBlockMode);
		}
	}
	
	{
		if(t_ManagePoInPtnExTrust->FindStrKeyID(data.strFileKey) == 0)
			t_ManagePoInPtnExTrust->AddPoInPtnExTrust(data);
	}

// 	{	
// 		SendToken.Set(1024);
// 		SendToken.TokenAdd_32(1);
// 		t_ManagePoInPtnExTrust->SetPkt(&data, SendToken);
// 		{
// 			SendData_Link(G_TYPE_PO_IN_PTN_EX_TRUST, G_CODE_COMMON_SYNC, SendToken);
// 		}
// 		SendToken.Clear();
// 	}
	return;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
