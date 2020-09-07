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
#include "MatchFilterUtil.h"

//---------------------------------------------------------------------------

CMatchFilterUtil*		t_MatchFilterUtil = NULL;

//---------------------------------------------------------------------------

CMatchFilterUtil::CMatchFilterUtil()
{
}
//---------------------------------------------------------------------------

CMatchFilterUtil::~CMatchFilterUtil()
{
}
//---------------------------------------------------------------------------

INT32		CMatchFilterUtil::IsMatchFilter(PDB_SITE_FILE& pdata, DB_FILE_INFO& tTarDFI, UINT32 nFltChkType, CHAR chTok)
{
	DB_FILE_INFO tSrcDFI;

	{
		tSrcDFI.strName			= pdata->strFileName;
		tSrcDFI.strPath			= pdata->strFilePath;
		tSrcDFI.strHash			= pdata->strFileHash;
		tSrcDFI.strPublisher	= pdata->strPublisherName;
		tSrcDFI.strDescription	= pdata->strFileDescr;
		
		tSrcDFI.strSignPubName	= pdata->strPubName;
		tSrcDFI.strSignPubSN	= pdata->strPubSN;
		tSrcDFI.strSignCntName	= pdata->strCntName;
		tSrcDFI.strSignCntSN	= pdata->strCntSN;
	}

	return IsMatchFilter(tSrcDFI, tTarDFI, nFltChkType, chTok);
}
//---------------------------------------------------------------------------

INT32		CMatchFilterUtil::IsMatchFilter(DB_FILE_INFO& tSrcDFI, DB_FILE_INFO& tTarDFI, UINT32 nFltChkType, CHAR chTok)
{
	{
		UINT32 nMatchFind = STATUS_USED_MODE_OFF;
		String strTarget;
		do 
		{	
			if(IsMatchFilter(tSrcDFI.strName,			tTarDFI.strName,		nFltChkType, nMatchFind, chTok))		break;
			if(IsMatchFilter(tSrcDFI.strPath,			tTarDFI.strPath,		nFltChkType, nMatchFind, chTok))		break;
			if(IsMatchFilter(tSrcDFI.strDescription,	tTarDFI.strDescription,	nFltChkType, nMatchFind, chTok))		break;
			if(IsMatchFilter(tSrcDFI.strHash,			tTarDFI.strHash,		nFltChkType, nMatchFind, chTok))		break;
			if(IsMatchFilter(tSrcDFI.strPublisher,		tTarDFI.strPublisher,	nFltChkType, nMatchFind, chTok))		break;
			if(IsMatchFilter(tSrcDFI.strSignPubSN,		tTarDFI.strSignPubSN,	nFltChkType, nMatchFind, chTok))		break;
			if(IsMatchFilter(tSrcDFI.strSignPubName,	tTarDFI.strSignPubName,	nFltChkType, nMatchFind, chTok))		break;
			if(IsMatchFilter(tSrcDFI.strSignCntSN,		tTarDFI.strSignCntSN,	nFltChkType, nMatchFind, chTok))		break;
			if(IsMatchFilter(tSrcDFI.strSignCntName,	tTarDFI.strSignCntName,	nFltChkType, nMatchFind, chTok))		break;

		} while (FALSE);	

		if(nMatchFind == STATUS_USED_MODE_ON)	return 0;
	}
	return -10;
}
//---------------------------------------------------------------------------

INT32		CMatchFilterUtil::IsMatchFilter(String& strTarget, String& strSpec, UINT32 nChkType, UINT32& nMatchFind, CHAR chTok)
{
	if(strSpec.empty())
		return 0;

	INT32 nCellMatched = 0;
	CTokenString TokenSpec(strSpec.c_str(), strSpec.length(), chTok);
	while(TokenSpec.IsNextToken())
	{
		String strSpecCell = TokenSpec.NextToken();

		if(StrMatchSpec(strTarget.c_str(), strSpecCell.c_str()))
		{
			nCellMatched = STATUS_USED_MODE_ON;
			break;
		}
	}	

	if(nCellMatched)
	{
		nMatchFind = STATUS_USED_MODE_ON;
		if(nChkType == SS_MATCH_FILTER_CHK_TYPE_OR)			return 1;
	}
	else
	{
		nMatchFind = STATUS_USED_MODE_OFF;
		if(nChkType == SS_MATCH_FILTER_CHK_TYPE_AND)		return 1;
	}	
	return 0;
}
//---------------------------------------------------------------------------

