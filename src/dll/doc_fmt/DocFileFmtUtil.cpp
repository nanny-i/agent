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

#include "stdafx.h"
#include "com_struct.h"
#include "DocFmtDefine.h"
#include "DocFileFmtUtil.h"

CDocFileFmtUtil::CDocFileFmtUtil(void)
{
	m_n_zip_Count = 0;
	m_n_pptx_Han_Count = 0;
	m_n_pptx_Office_Count = 0;
	m_n_pptx2_Office_Count = 0;	
	m_n_odt_Office_Count = 0;
	m_n_odt_Han_Count = 0;
	m_n_odp_Office_Count = 0;
	m_n_odp_Han_Count = 0;
	m_n_xlsx_Office_Count = 0;
	m_n_xlsx_Han_Count = 0;
	m_n_docx_Office_Count = 0;
	m_n_docx_Han_Count = 0;
	m_n_ods_Han_Count = 0;
	m_n_ppsx_Han_Count = 0;
	m_n_ppsx_Office_Count = 0;
	m_n_show_Han_Count = 0;
	m_n_doc_Han_Count = 0;
	m_n_doc_Office_Count = 0;
	m_n_pps_Office_Count = 0;
	m_n_ppt_Han_Count = 0;
	m_n_ppt_Office_Count = 0;
	m_n_xls_Office_Count = 0;
	m_n_xls_Han_Count = 0;
	m_n_cell_Han_Count = 0;
	m_n_nxl_Han_Count = 0;
	m_n_hwp2_Han_Count = 0;
	m_n_hwp_Han_Count = 0;
	m_n_pdf_Count = 0;
	m_n_hml_Han_Count = 0;
	m_n_hpt_Han_Count = 0;
	m_n_hwp3_Han_Count = 0;
	m_n_xlsx_unKnown_Count = 0;    
	
	m_n_nxt_Han_Count = 0;
	m_n_odb_Han_Count = 0;
	m_n_odg_Han_Count = 0;

	m_n_pptx_Known_Count = 0;
	m_n_odt_Known_Count = 0;
	m_n_odp_Known_Count = 0;
	m_n_xlsx_Known_Count = 0;
	m_n_docx_Known_Count = 0;
	m_n_ods_Known_Count = 0;
	m_n_ppsx_Known_Count = 0;
	m_n_show_Known_Count = 0;
	m_n_doc_Known_Count = 0;
	m_n_xls_Known_Count = 0;
	m_n_ppt_Known_Count = 0;
	m_n_pps_Known_Count = 0;
	m_n_cell_Known_Count = 0;
	m_n_nxl_Known_Count = 0;
	m_n_pdf_Known_Count = 0;
	m_n_hml_Known_Count = 0;
	m_n_hwp_Known_Count = 0;
	m_n_hpt_Known_Count = 0;
	m_n_nxt_Known_Count = 0;
	m_n_odb_Known_Count = 0;
	m_n_odg_Known_Count = 0;
	m_n_user_define_Count = 0;

	m_n_ods_Office_Count = 0;
	pthread_mutex_init(&m_mutex, NULL);
}
//-----------------------------------------------------------------------------------------------


CDocFileFmtUtil::~CDocFileFmtUtil(void)
{
	pthread_mutex_destroy(&m_mutex);
}

//-----------------------------------------------------------------------------------------------

INT32 CDocFileFmtUtil::ProcAnalysis(PASI_DFILE_FMT_INFO pADFFI, char *acLogMsg)
{
	INT32 nRetVal = 0;
	if(pADFFI == NULL)
		return -1;

	pthread_mutex_lock (&m_mutex);
	nRetVal = SetSearchFileList(pADFFI, acLogMsg);
	pthread_mutex_unlock(&m_mutex);

	return nRetVal;
}
//-----------------------------------------------------------------------------------------------

INT32 CDocFileFmtUtil::SetSearchFileList(PASI_DFILE_FMT_INFO pADFFI, char *acLogMsg)
{
	if(pADFFI == NULL)
		return -1;

	if(pADFFI->szFileName[0] == 0)
	{
		if(pADFFI->wszFileName[0] == L'\0')
		{
			return -2;
		}
		wcstombs((char *)pADFFI->szFileName, (wchar_t *)pADFFI->wszFileName, CHAR_MAX_SIZE);
	}
	pADFFI->nFmtType = CheckDocumentFile(pADFFI->szFileName, acLogMsg);    
	return ConvertFmtTypeToName(pADFFI);
}
//-----------------------------------------------------------------------------------------------

INT32	CDocFileFmtUtil::ConvertFmtTypeToName(PASI_DFILE_FMT_INFO pADFFI)
{
	if(pADFFI == NULL)
		return -1;
	
	switch(pADFFI->nFmtType)
	{
		case ASIDFF_FILE_FMT_TYPE_PPT:		strncpy(pADFFI->szFmtType, "ppt", CHAR_MAX_SIZE-1);		break;
		case ASIDFF_FILE_FMT_TYPE_PPTX:		strncpy(pADFFI->szFmtType, "pptx", CHAR_MAX_SIZE-1);	break;
		case ASIDFF_FILE_FMT_TYPE_PPS:		strncpy(pADFFI->szFmtType, "pps", CHAR_MAX_SIZE-1);		break;
		case ASIDFF_FILE_FMT_TYPE_PPSX:		strncpy(pADFFI->szFmtType, "ppsx", CHAR_MAX_SIZE-1);	break;
		case ASIDFF_FILE_FMT_TYPE_XLS:		strncpy(pADFFI->szFmtType, "xls", CHAR_MAX_SIZE-1);		break;
		case ASIDFF_FILE_FMT_TYPE_XLSX:		strncpy(pADFFI->szFmtType, "xlsx", CHAR_MAX_SIZE-1);	break;
		case ASIDFF_FILE_FMT_TYPE_DOC:		strncpy(pADFFI->szFmtType, "doc", CHAR_MAX_SIZE-1);		break;
		case ASIDFF_FILE_FMT_TYPE_DOCX:		strncpy(pADFFI->szFmtType, "docx", CHAR_MAX_SIZE-1);	break;

		case ASIDFF_FILE_FMT_TYPE_ZIP:		strncpy(pADFFI->szFmtType, "zip", CHAR_MAX_SIZE-1);		break;

		case ASIDFF_FILE_FMT_TYPE_PDF:		strncpy(pADFFI->szFmtType, "pdf", CHAR_MAX_SIZE-1);		break;
		case ASIDFF_FILE_FMT_TYPE_HWP:		strncpy(pADFFI->szFmtType, "hwp", CHAR_MAX_SIZE-1);		break;
		case ASIDFF_FILE_FMT_TYPE_HPT:		strncpy(pADFFI->szFmtType, "hpt", CHAR_MAX_SIZE-1);		break;

		case ASIDFF_FILE_FMT_TYPE_HML:		strncpy(pADFFI->szFmtType, "hml", CHAR_MAX_SIZE-1);		break;

		case ASIDFF_FILE_FMT_TYPE_ODT:		strncpy(pADFFI->szFmtType, "odt", CHAR_MAX_SIZE-1);		break;
		case ASIDFF_FILE_FMT_TYPE_ODP:		strncpy(pADFFI->szFmtType, "odp", CHAR_MAX_SIZE-1);		break;
		case ASIDFF_FILE_FMT_TYPE_ODS:		strncpy(pADFFI->szFmtType, "ods", CHAR_MAX_SIZE-1);		break;
		case ASIDFF_FILE_FMT_TYPE_ODB:		strncpy(pADFFI->szFmtType, "odb", CHAR_MAX_SIZE-1);		break;
		case ASIDFF_FILE_FMT_TYPE_ODG:		strncpy(pADFFI->szFmtType, "odg", CHAR_MAX_SIZE-1);		break;

		case ASIDFF_FILE_FMT_TYPE_SHOW:		strncpy(pADFFI->szFmtType, "show", CHAR_MAX_SIZE-1);	break;
		case ASIDFF_FILE_FMT_TYPE_CELL:		strncpy(pADFFI->szFmtType, "cell", CHAR_MAX_SIZE-1);	break;
		case ASIDFF_FILE_FMT_TYPE_NXL:		strncpy(pADFFI->szFmtType, "nxl", CHAR_MAX_SIZE-1);		break;
		case ASIDFF_FILE_FMT_TYPE_NXT:		strncpy(pADFFI->szFmtType, "nxt", CHAR_MAX_SIZE-1);		break;

		default:		pADFFI->szFmtType[0] = 0;		break;
	}
	return 0;
}
//-----------------------------------------------------------------------------------------------

INT32 CDocFileFmtUtil::CheckFileExtAnalysis(char *pcFilePath, INT32 *pnFileFmtType)
{
	char *pExt = NULL;
	if(pcFilePath == NULL || pnFileFmtType == NULL)
		return -1;
	pExt = strrchr(pcFilePath, '.');
	if(pExt == NULL)
		return -2;
	if(_stricmp(pExt, ".ppt")==0)
	{
		m_n_ppt_Office_Count++;
		*pnFileFmtType = ASIDFF_FILE_FMT_TYPE_PPT;
		return 0;
	}
	else if(_stricmp(pExt, ".pptx")==0)
	{
		m_n_pptx_Office_Count++;
		*pnFileFmtType = ASIDFF_FILE_FMT_TYPE_PPTX;
		return 0;
	}
	else if(_stricmp(pExt, ".doc")==0)
	{
		m_n_doc_Office_Count++;
		*pnFileFmtType = ASIDFF_FILE_FMT_TYPE_DOC;
		return 0;
	}
	else if(_stricmp(pExt, ".docx")==0)
	{
		m_n_docx_Office_Count++;
		*pnFileFmtType = ASIDFF_FILE_FMT_TYPE_DOCX;
		return 0;
	}
	else if(_stricmp(pExt, ".pps")==0)
	{
		m_n_pps_Office_Count++;
		*pnFileFmtType = ASIDFF_FILE_FMT_TYPE_PPS;
		return 0;
	}
	else if(_stricmp(pExt, ".ppsx")==0)
	{
		m_n_ppsx_Office_Count++;
		*pnFileFmtType = ASIDFF_FILE_FMT_TYPE_PPSX;
		return 0;
	}
	else if(_stricmp(pExt, ".xls")==0)
	{
		m_n_xls_Office_Count++;
		*pnFileFmtType = ASIDFF_FILE_FMT_TYPE_XLS;
		return 0;
	}
	else if(_stricmp(pExt, ".xlsx")==0)
	{
		m_n_xlsx_Office_Count++;
		*pnFileFmtType = ASIDFF_FILE_FMT_TYPE_XLSX;
		return 0;
	}	
	else if(_stricmp(pExt, ".pdf")==0)
	{
		m_n_pdf_Count++;
		*pnFileFmtType = ASIDFF_FILE_FMT_TYPE_PDF;
		return 0;
	}	
	else if(_stricmp(pExt, ".hwp")==0)
	{
		m_n_hwp_Han_Count++;
		*pnFileFmtType = ASIDFF_FILE_FMT_TYPE_HWP;
		return 0;
	}
	else if(_stricmp(pExt, ".hpt")==0)
	{
		m_n_hpt_Han_Count++;
		*pnFileFmtType = ASIDFF_FILE_FMT_TYPE_HPT;
		return 0;
	}
	else if(_stricmp(pExt, ".hml")==0)
	{
		m_n_hml_Han_Count++;
		*pnFileFmtType = ASIDFF_FILE_FMT_TYPE_HML;
		return 0;
	}
	else if(_stricmp(pExt, ".odt")==0)
	{
		m_n_odt_Office_Count++;
		*pnFileFmtType = ASIDFF_FILE_FMT_TYPE_ODT;
		return 0;
	}
	else if(_stricmp(pExt, ".odp")==0)
	{
		m_n_odp_Office_Count++;
		*pnFileFmtType = ASIDFF_FILE_FMT_TYPE_ODP;
		return 0;
	}
	else if(_stricmp(pExt, ".ods")==0)
	{
		m_n_ods_Han_Count++;
		*pnFileFmtType = ASIDFF_FILE_FMT_TYPE_ODS;
		return 0;
	}
	else if(_stricmp(pExt, ".odb")==0)
	{
		m_n_odb_Han_Count++;
		*pnFileFmtType = ASIDFF_FILE_FMT_TYPE_ODB;
		return 0;
	}
	else if(_stricmp(pExt, ".odg")==0)
	{
		m_n_odg_Han_Count++;
		*pnFileFmtType = ASIDFF_FILE_FMT_TYPE_ODG;
		return 0;
	}
	else if(_stricmp(pExt, ".show")==0)
	{
		m_n_show_Han_Count++;
		*pnFileFmtType = ASIDFF_FILE_FMT_TYPE_SHOW;
		return 0;
	}
	else if(_stricmp(pExt, ".cell")==0)
	{
		m_n_cell_Han_Count++;
		*pnFileFmtType = ASIDFF_FILE_FMT_TYPE_CELL;
		return 0;
	}
	else if(_stricmp(pExt, ".nxl")==0)
	{
		m_n_nxl_Han_Count++;
		*pnFileFmtType = ASIDFF_FILE_FMT_TYPE_NXL;
		return 0;
	}
	else if(_stricmp(pExt, ".nxt")==0)
	{
		m_n_nxt_Han_Count++;
		*pnFileFmtType = ASIDFF_FILE_FMT_TYPE_NXT;
		return 0;
	}
	return -3;
}


INT32 CDocFileFmtUtil::CheckPkFmtAnalysis(char *pcFilePath, char *szFmt, char *acLogMsg)
{
	FILE* fp = NULL;
	BYTE *pData = NULL; 
	INT32 nRead = 0;
	INT32 nErrCode = 0;
	INT32 nFileFmt = ASIDFF_FILE_FMT_TYPE_UNKNOW;
	if(pcFilePath == NULL || szFmt == NULL)
	{
		if(acLogMsg)
			snprintf(acLogMsg, MAX_LOGMSG, "invalid input data");
		return ASIDFF_FILE_FMT_TYPE_UNKNOW;
	}

	if(_stricmp(szFmt, DOCUFORMAT_pptx_office_16)==0)
	{
		m_n_pptx_Office_Count++;
		return ASIDFF_FILE_FMT_TYPE_PPTX;
	}
	
	if(_stricmp(szFmt, DOCUFORMAT_pptx_officeppt_16)==0)
	{
		m_n_pptx2_Office_Count++;
		return ASIDFF_FILE_FMT_TYPE_PPTX;
	}

	if(_stricmp(szFmt, DOCUFORMAT_odt_office_16)==0)
	{
		m_n_odt_Office_Count++;
		return ASIDFF_FILE_FMT_TYPE_ODT;
	}
	
	if(_stricmp(szFmt, DOCUFORMAT_odt_han_16)==0)
	{
		m_n_odt_Han_Count++;
		return ASIDFF_FILE_FMT_TYPE_ODT;
	}
	
	if(_stricmp(szFmt, DOCUFORMAT_odp_officeppt_16)==0)
	{
		m_n_odp_Office_Count++;
		return ASIDFF_FILE_FMT_TYPE_ODP;
	}
	
	if(_stricmp(szFmt, DOCUFORMAT_odp_han_16)==0)
	{
		m_n_odp_Han_Count++;
		return ASIDFF_FILE_FMT_TYPE_ODP;
	}
	
	if(_stricmp(szFmt, DOCUFORMAT_xlsx_office_16)==0)
	{
		m_n_xlsx_Office_Count++;
		return ASIDFF_FILE_FMT_TYPE_XLSX;
	}
	
	if(_stricmp(szFmt, DOCUFORMAT_xlsx_han_16)==0)
	{
		m_n_xlsx_Han_Count++;
		return ASIDFF_FILE_FMT_TYPE_XLSX;
	}
	
	if(_stricmp(szFmt, DOCUFORMAT_docx_office_16)==0)
	{
		m_n_docx_Office_Count++;
		return ASIDFF_FILE_FMT_TYPE_DOCX;
	}
	
	if(_stricmp(szFmt, DOCUFORMAT_docx_han_16)==0)
	{
		m_n_docx_Han_Count++;
		return ASIDFF_FILE_FMT_TYPE_DOCX;
	}

	if(_stricmp(szFmt, DOCUFORMAT_ods_han_16)==0)
	{
		m_n_ods_Han_Count++;
		return ASIDFF_FILE_FMT_TYPE_ODS;
	}
	
	if(_stricmp(szFmt, DOCUFORMAT_ppsx_han_16)==0)
	{
		m_n_ppsx_Han_Count++;
		return ASIDFF_FILE_FMT_TYPE_PPSX;
	}

	if(_stricmp(szFmt, DOCUFORMAT_xlsx_office_16_unknown)==0)
	{
		m_n_xlsx_unKnown_Count++;
		return ASIDFF_FILE_FMT_TYPE_XLSX;
	}
	
	if(_stricmp(szFmt, DOCUFORMAT_xlsx_office_16_unknown2)==0)
	{
		m_n_xlsx_unKnown_Count++;
		return ASIDFF_FILE_FMT_TYPE_XLSX;
	}
	
	if(_stricmp(szFmt, DOCUFORMAT_docx_office2007_16)==0)
	{
		m_n_docx_Office_Count++;
		return ASIDFF_FILE_FMT_TYPE_DOCX;
	}
	
	if(_stricmp(szFmt, DOCUFORMAT_pptx_office2007_16)==0)
	{
		m_n_pptx_Office_Count++;
		return ASIDFF_FILE_FMT_TYPE_PPTX;
	}

	if(_stricmp(szFmt, DOCUFORMAT_xlsx_office2007_16)==0)
	{
		m_n_xlsx_Office_Count++;
		return ASIDFF_FILE_FMT_TYPE_XLSX;
	}
	
	if(_stricmp(szFmt, DOCUFORMAT_docx2_office2007_16)==0)
	{
		m_n_docx_Office_Count++;
		return ASIDFF_FILE_FMT_TYPE_DOCX;
	}
	
	if(_stricmp(szFmt, DOCUFORMAT_ppsx_office2007_16)==0)
	{
		m_n_ppsx_Office_Count++;
		return ASIDFF_FILE_FMT_TYPE_PPSX;
	}
	
	if(_stricmp(szFmt, DOCUFORMAT_xlsx2_office2007_16)==0)
	{
		m_n_xlsx_Office_Count++;
		return ASIDFF_FILE_FMT_TYPE_XLSX;
	}
	
	if(_stricmp(szFmt, DOCUFORMAT_odt_han2014_16)==0)
	{
		m_n_odt_Han_Count++;
		return ASIDFF_FILE_FMT_TYPE_ODT;
	}
	
	if(_stricmp(szFmt, DOCUFORMAT_docx_han2014_16)==0)
	{
		m_n_docx_Han_Count++;
		return ASIDFF_FILE_FMT_TYPE_DOCX;
	}
	
	if(_stricmp(szFmt, DOCUFORMAT_ods_han2014_16)==0)
	{
		m_n_ods_Han_Count++;
		return ASIDFF_FILE_FMT_TYPE_ODS;
	}

	if(_stricmp(szFmt, DOCUFORMAT_cell_han2014_16)==0)
	{
		m_n_cell_Han_Count++;
		return ASIDFF_FILE_FMT_TYPE_CELL;
	}
	
	if(_stricmp(szFmt, DOCUFORMAT_xlsx_office2013_16)==0)
	{
		m_n_xlsx_Office_Count++;
		return ASIDFF_FILE_FMT_TYPE_XLSX;
	}

	if(_stricmp(szFmt, DOCUFORMAT_ods_office2013_16)==0)
	{
		m_n_ods_Office_Count++;
		return ASIDFF_FILE_FMT_TYPE_ODS;
	}
	
	if(_stricmp(szFmt, DOCUFORMAT_odp_office2013ppt_16)==0)
	{
		m_n_odp_Office_Count++;
		return ASIDFF_FILE_FMT_TYPE_ODP;
	}
	
	if(_stricmp(szFmt, DOCUFORMAT_ppsx_office2013ppt_16)==0)
	{
		m_n_ppsx_Office_Count++;
		return ASIDFF_FILE_FMT_TYPE_PPSX;
	}
	
	if(_stricmp(szFmt, DOCUFORMAT_docx_office2013pub_16)==0)
	{
		m_n_docx_Office_Count++;
		return ASIDFF_FILE_FMT_TYPE_DOCX;
	}

	if(_stricmp(szFmt, DOCUFORMAT_xlsx_office_16_uknwn)==0)
	{
		m_n_xlsx_Office_Count++;
		return ASIDFF_FILE_FMT_TYPE_XLSX;
	}
	
	if(_stricmp(szFmt, DOCUFORMAT_xlsx_office_16_uknwn_02)==0)
	{
		m_n_xlsx_Office_Count++;
		return ASIDFF_FILE_FMT_TYPE_XLSX;
	}

	if(_stricmp(szFmt, DOCUFORMAT_pptx_office_16_uknwn)==0)
	{
		m_n_pptx_Office_Count++;
		return ASIDFF_FILE_FMT_TYPE_PPTX;
	}

	if(_stricmp(szFmt, DOCUFORMAT_docx_office_16_uknwn)==0)
	{
		m_n_docx_Office_Count++;
		return ASIDFF_FILE_FMT_TYPE_DOCX;
	}

	if(_stricmp(szFmt, DOCUFORMAT_docx_office_16_365V18)==0)
	{
		m_n_docx_Office_Count++;
		return ASIDFF_FILE_FMT_TYPE_DOCX;
	}

	if(_stricmp(szFmt, DOCUFORMAT_pptx_office_16_365V18)==0)
	{
		m_n_pptx_Office_Count++;
		return ASIDFF_FILE_FMT_TYPE_PPTX;
	}

	if(_stricmp(szFmt, DOCUFORMAT_xlsx_office_16_365V18)==0)
	{	m_n_xlsx_Office_Count++;
		return ASIDFF_FILE_FMT_TYPE_XLSX;
	}

	pData = (BYTE *)malloc(READ_PK_FMT_BIN_MAX+1);
	if(pData == NULL)
	{
		if(acLogMsg)
			snprintf(acLogMsg, MAX_LOGMSG, "fail to allocate memory (%d)", errno);
		return ASIDFF_FILE_FMT_TYPE_UNKNOW;
	}
	memset(pData, 0x00, READ_PK_FMT_BIN_MAX+1);	
	
	fp = fopen(pcFilePath, "rb");
	if(fp==NULL)
	{
		if(acLogMsg)
			snprintf(acLogMsg, MAX_LOGMSG, "fail to open %s (%d)", pcFilePath, errno);	
		safe_free(pData);
		return ASIDFF_FILE_FMT_TYPE_UNKNOW;
	}

	fseek(fp, 1146L, SEEK_SET);

	nRead = (INT32)fread(pData, 1, READ_PK_FMT_BIN_MAX, fp);
	if ((!feof(fp) || (nErrCode =  ferror(fp))) && nRead != READ_PK_FMT_BIN_MAX)
	{
		if(acLogMsg)
			snprintf(acLogMsg, MAX_LOGMSG, "fail to read from %s (%d)", pcFilePath, errno);	
		fclose(fp);
		safe_free(pData);
		return ASIDFF_FILE_FMT_TYPE_UNKNOW;
	}
	memset(szFmt, 0, MAX_QQBUFF+1);
	snprintf(szFmt, MAX_QQBUFF, "%02X%02X%02X%02X", (BYTE)pData[0], (BYTE)pData[1], (BYTE)pData[2], (BYTE)pData[3]);	

	fclose(fp);
	safe_free(pData);
	
	if(_stricmp(szFmt, DOCUFORMAT_pptx_han_4)==0)
	{
		m_n_pptx_Han_Count++;
		return ASIDFF_FILE_FMT_TYPE_PPTX;
	}
	else if(_stricmp(szFmt, DOCUFORMAT_show_han_4)==0)
	{
		m_n_show_Han_Count++;
		return ASIDFF_FILE_FMT_TYPE_SHOW;
	}
	else if(_stricmp(szFmt, DOCUFORMAT_xlsx_han2014_4)==0)	//2015.10.01
	{
		m_n_xlsx_Han_Count++;
		return ASIDFF_FILE_FMT_TYPE_XLSX;
	}

	if(CheckFileExtAnalysis(pcFilePath, &nFileFmt) == 0)
		return nFileFmt;

	if(CheckZipFileContentAnalysis(pcFilePath, &nFileFmt) == 0)
		return nFileFmt;
	m_n_doc_Office_Count++;
	return ASIDFF_FILE_FMT_TYPE_DOC;
}

INT32 CDocFileFmtUtil::CheckHmlFmtAnalysis(char *pcFilePath, char *szFmt, char *acLogMsg)
{
	FILE* fp = NULL;
	BYTE *pData = NULL; 
	INT32 nRead = 0;
	INT32 nErrCode = 0;
	INT32 nFileFmt = ASIDFF_FILE_FMT_TYPE_UNKNOW;
	if(pcFilePath == NULL || szFmt == NULL)
	{
		if(acLogMsg)
			snprintf(acLogMsg, MAX_LOGMSG, "invalid input data");
		return ASIDFF_FILE_FMT_TYPE_UNKNOW;
	}

	pData = (BYTE *)malloc(READ_HML_FMT_BIN_MAX+1);
	if(pData == NULL)
	{
		if(acLogMsg)
			snprintf(acLogMsg, MAX_LOGMSG, "fail to allocate memory (%d)", errno);
		return ASIDFF_FILE_FMT_TYPE_UNKNOW;
	}
	memset(pData, 0x00, READ_HML_FMT_BIN_MAX+1);	

	fp = fopen(pcFilePath, "rb");
	if(fp==NULL)
	{
		if(acLogMsg)
			snprintf(acLogMsg, MAX_LOGMSG, "fail to open %s (%d)", pcFilePath, errno);	
		safe_free(pData);
		return ASIDFF_FILE_FMT_TYPE_UNKNOW;
	}

	fseek(fp, 58L, SEEK_SET);

	nRead = (INT32)fread(pData, 1, READ_HML_FMT_BIN_MAX, fp);
	if ((!feof(fp) || (nErrCode =  ferror(fp))) && nRead != READ_HML_FMT_BIN_MAX)
	{
		if(acLogMsg)
			snprintf(acLogMsg, MAX_LOGMSG, "fail to read from %s (%d)", pcFilePath, errno);	
		fclose(fp);
		safe_free(pData);
		return ASIDFF_FILE_FMT_TYPE_UNKNOW;
	}
	memset(szFmt, 0, MAX_QQBUFF+1);
	
	snprintf(szFmt, MAX_QQBUFF, "%02X%02X%02X%02X%02X%02X", 
		(BYTE)pData[0], (BYTE)pData[1], (BYTE)pData[2], (BYTE)pData[3], (BYTE)pData[4], (BYTE)pData[5]);

	fclose(fp);
	safe_free(pData);
	
	if(_stricmp(szFmt, DOCUFORMAT_hml_han_6_adbit)==0)
	{	m_n_hml_Han_Count++;
		return ASIDFF_FILE_FMT_TYPE_HML;
	}

	if(CheckFileExtAnalysis(pcFilePath, &nFileFmt) == 0)
		return nFileFmt;

	m_n_hml_Han_Count++;
	return ASIDFF_FILE_FMT_TYPE_HML;
}



INT32 CDocFileFmtUtil::CheckHwpFmtAnalysis(char *pcFilePath, char *szFmt, char *acLogMsg)
{
	FILE* fp = NULL;
	BYTE *pData = NULL; 
	INT32 nRead = 0;
	INT32 nErrCode = 0;
	INT32 nFileFmt = ASIDFF_FILE_FMT_TYPE_UNKNOW;
	if(pcFilePath == NULL || szFmt == NULL)
	{
		if(acLogMsg)
			snprintf(acLogMsg, MAX_LOGMSG, "invalid input data");
		return ASIDFF_FILE_FMT_TYPE_UNKNOW;
	}

	pData = (BYTE *)malloc(READ_HWP_FMT_BIN_MAX+1);
	if(pData == NULL)
	{
		if(acLogMsg)
			snprintf(acLogMsg, MAX_LOGMSG, "fail to allocate memory (%d)", errno);
		return ASIDFF_FILE_FMT_TYPE_UNKNOW;
	}
	memset(pData, 0x00, READ_HWP_FMT_BIN_MAX+1);	

	fp = fopen(pcFilePath, "rb");
	if(fp==NULL)
	{
		if(acLogMsg)
			snprintf(acLogMsg, MAX_LOGMSG, "fail to open %s (%d)", pcFilePath, errno);	
		safe_free(pData);
		return ASIDFF_FILE_FMT_TYPE_UNKNOW;
	}
	fseek(fp, 0L, SEEK_SET);

	nRead = (INT32)fread(pData, 1, READ_HWP_FMT_BIN_MAX, fp);
	if ((!feof(fp) || (nErrCode =  ferror(fp))) && nRead != READ_HWP_FMT_BIN_MAX)
	{
		if(acLogMsg)
			snprintf(acLogMsg, MAX_LOGMSG, "fail to read from %s (%d)", pcFilePath, errno);	
		fclose(fp);
		safe_free(pData);
		return ASIDFF_FILE_FMT_TYPE_UNKNOW;
	}
	memset(szFmt, 0, MAX_QQBUFF+1);

	snprintf(szFmt, MAX_QQBUFF, "%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X", 
		(BYTE)pData[0], (BYTE)pData[1], (BYTE)pData[2], (BYTE)pData[3], (BYTE)pData[4], (BYTE)pData[5],
		(BYTE)pData[6], (BYTE)pData[7], (BYTE)pData[8], (BYTE)pData[9], (BYTE)pData[10], (BYTE)pData[11],
		(BYTE)pData[12], (BYTE)pData[13], (BYTE)pData[14], (BYTE)pData[15]); 
	
	fclose(fp);
	safe_free(pData);
	
	if(_stricmp(szFmt, DOCUFORMAT_hml_han_6_adbit)==0)
	{
		m_n_hml_Han_Count++;
		return ASIDFF_FILE_FMT_TYPE_HML;
	}
	if(CheckFileExtAnalysis(pcFilePath, &nFileFmt) == 0)
		return nFileFmt;

	m_n_hwp_Han_Count++;
	return ASIDFF_FILE_FMT_TYPE_HWP;
}


INT32 CDocFileFmtUtil::CheckDocFmtAnalysis(char *pcFilePath, char *szFmt, char *acLogMsg)
{
	FILE* fp = NULL;
	BYTE *pData = NULL; 
	INT32 nRead = 0;
	INT32 nErrCode = 0;
	INT32 nFileFmt = ASIDFF_FILE_FMT_TYPE_UNKNOW;	
	if(pcFilePath == NULL || szFmt == NULL)
	{
		if(acLogMsg)
			snprintf(acLogMsg, MAX_LOGMSG, "invalid input data");
		return ASIDFF_FILE_FMT_TYPE_UNKNOW;
	}

	pData = (BYTE *)malloc(READ_DOC_FMT_BIN_MAX+1);
	if(pData == NULL)
	{
		if(acLogMsg)
			snprintf(acLogMsg, MAX_LOGMSG, "fail to allocate memory (%d)", errno);
		return ASIDFF_FILE_FMT_TYPE_UNKNOW;
	}
	memset(pData, 0x00, READ_DOC_FMT_BIN_MAX+1);	

	fp = fopen(pcFilePath, "rb");
	if(fp==NULL)
	{
		if(acLogMsg)
			snprintf(acLogMsg, MAX_LOGMSG, "fail to open %s (%d)", pcFilePath, errno);	
		safe_free(pData);
		return ASIDFF_FILE_FMT_TYPE_UNKNOW;
	}

	fseek(fp, 0L, SEEK_SET);

	nRead = (INT32)fread(pData, 1, READ_DOC_FMT_BIN_MAX, fp);
	if ((!feof(fp) || (nErrCode =  ferror(fp))) && nRead != READ_DOC_FMT_BIN_MAX)
	{
		if(acLogMsg)
			snprintf(acLogMsg, MAX_LOGMSG, "fail to read from %s (%d)", pcFilePath, errno);	
		fclose(fp);
		safe_free(pData);
		return ASIDFF_FILE_FMT_TYPE_UNKNOW;
	}
	memset(szFmt, 0, MAX_QQBUFF+1);

	snprintf(szFmt, MAX_QQBUFF, "%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X",
		(BYTE)pData[48], (BYTE)pData[1132], (BYTE)pData[1133], (BYTE)pData[1134], (BYTE)pData[1135], (BYTE)pData[1644], (BYTE)pData[1645], (BYTE)pData[1646], (BYTE)pData[1647], (BYTE)pData[648],
		(BYTE)pData[649], (BYTE)pData[650], (BYTE)pData[651], (BYTE)pData[1664], (BYTE)pData[1666], (BYTE)pData[1668], (BYTE)pData[1670], (BYTE)pData[1672], (BYTE)pData[1674], (BYTE)pData[1676],
		(BYTE)pData[1678], (BYTE)pData[1152], (BYTE)pData[1154], (BYTE)pData[1156], (BYTE)pData[1158], (BYTE)pData[1160], (BYTE)pData[1162], (BYTE)pData[1164], (BYTE)pData[1166]);
	
	fclose(fp);
	safe_free(pData);
	
	if(_strnicmp(szFmt, DOCUFORMAT_doc_office_1_adbit, 2)==0)
	{
		m_n_doc_Office_Count++;
		return ASIDFF_FILE_FMT_TYPE_DOC;
	}
	
	if(_strnicmp(szFmt, DOCUFORMAT_doc_office_1_adbit_unk, 1)==0)
	{
		m_n_doc_Office_Count++;
		return ASIDFF_FILE_FMT_TYPE_DOC;
	}
	if(_strnicmp(szFmt, DOCUFORMAT_xls_office_1_adbit, 2)==0)
	{	m_n_xls_Office_Count++;
		return ASIDFF_FILE_FMT_TYPE_XLS;
	}
	if(_strnicmp(szFmt, DOCUFORMAT_ppt_han_1_adbit, 2)==0)
	{
		m_n_ppt_Han_Count++;
		return ASIDFF_FILE_FMT_TYPE_PPT;
	}
	if(_strnicmp(szFmt, DOCUFORMAT_doc_office2007_1_adbit, 2)==0)
	{
		m_n_doc_Office_Count++;
		return ASIDFF_FILE_FMT_TYPE_DOC;
	}
	if(_strnicmp(szFmt, DOCUFORMAT_doc2_office2007_1_adbit, 2)==0)
	{
		m_n_doc_Office_Count++;
		return ASIDFF_FILE_FMT_TYPE_DOC;
	}
	if(strstr(szFmt, DOCUFORMAT_xls_han_4_adbit))
	{
		m_n_xls_Han_Count++;
		return ASIDFF_FILE_FMT_TYPE_XLS;
	}
	if(strstr(szFmt, DOCUFORMAT_pps_office_4_adbit))
	{
		m_n_pps_Office_Count++;
		return ASIDFF_FILE_FMT_TYPE_PPS;
	}
	if(strstr(szFmt, DOCUFORMAT_ppt_office_4_adbit))
	{
		m_n_ppt_Office_Count++;
		return ASIDFF_FILE_FMT_TYPE_PPT;
	}
	if(strstr(szFmt, DOCUFORMAT_hwp2_han_4_adbit))
	{
		m_n_hwp2_Han_Count++;
		return ASIDFF_FILE_FMT_TYPE_HWP;
	}
	if(strstr(szFmt, DOCUFORMAT_cell_han_4_adbit))
	{
		m_n_cell_Han_Count++;
		return ASIDFF_FILE_FMT_TYPE_CELL;
	}
	if(strstr(szFmt, DOCUFORMAT_nxl_han_4_adbit))
	{
		m_n_nxl_Han_Count++;
		return ASIDFF_FILE_FMT_TYPE_NXL;
	}
	if(strstr(szFmt, DOCUFORMAT_hwp3_han_4_adbit))
	{
		m_n_hwp3_Han_Count++;
		return ASIDFF_FILE_FMT_TYPE_HWP;
	}
	if(strstr(szFmt, DOCUFORMAT_hwp3_1_han_4_adbit))
	{
		m_n_hwp3_Han_Count++;
		return ASIDFF_FILE_FMT_TYPE_HWP;
	}
	if(strstr(szFmt, DOCUFORMAT_hwp4_han_4_adbit))
	{
		m_n_hwp3_Han_Count++;
		return ASIDFF_FILE_FMT_TYPE_HWP;
	}
	if(strstr(szFmt, DOCUFORMAT_hwp5_han_4_adbit))
	{
		m_n_hwp3_Han_Count++;
		return ASIDFF_FILE_FMT_TYPE_HWP;
	}
	if(strstr(szFmt, DOCUFORMAT_ppt_office2007_4_adbit))
	{
		m_n_ppt_Office_Count++;
		return ASIDFF_FILE_FMT_TYPE_PPT;
	}		
	if(strstr(szFmt, DOCUFORMAT_pps_office2007_4_adbit))
	{
		m_n_pps_Office_Count++;
		return ASIDFF_FILE_FMT_TYPE_PPS;
	}	
	if(strstr(szFmt, DOCUFORMAT_xls_office2007_4_adbit))
	{
		m_n_xls_Office_Count++;
		return ASIDFF_FILE_FMT_TYPE_XLS;
	}
	if(strstr(szFmt, DOCUFORMAT_xls2_office2007_4_adbit))
	{
		m_n_xls_Office_Count++;
		return ASIDFF_FILE_FMT_TYPE_XLS;
	}
	if(strstr(szFmt, DOCUFORMAT_hwp6_han_4_adbit))
	{
		m_n_hwp3_Han_Count++;
		return ASIDFF_FILE_FMT_TYPE_HWP;
	}
	if(strstr(szFmt, DOCUFORMAT_hwp7_han_4_adbit))
	{
		m_n_hwp3_Han_Count++;
		return ASIDFF_FILE_FMT_TYPE_HWP;
	}

	if(strstr(szFmt, DOCUFORMAT_hwp_han2014_4_adbit))
	{
		m_n_hwp3_Han_Count++;
		return ASIDFF_FILE_FMT_TYPE_HWP;
	}
	
	if(strstr(szFmt, DOCUFORMAT_nxl_han2014_4_adbit)) 
	{
		m_n_nxl_Han_Count++;
		return ASIDFF_FILE_FMT_TYPE_NXL;
	}

	if(strstr(szFmt, DOCUFORMAT_xls_han2014_4_adbit)) 
	{
		m_n_xls_Han_Count++;
		return ASIDFF_FILE_FMT_TYPE_XLS;
	}
	
	if(strstr(szFmt, DOCUFORMAT_cell_han2014_4_adbit))
	{
		m_n_cell_Han_Count++;
		return ASIDFF_FILE_FMT_TYPE_CELL;
	}
	
	if(_strnicmp(szFmt, DOCUFORMAT_ppt_han2014_1_adbit, 2)==0)
	{
		m_n_ppt_Han_Count++;
		return ASIDFF_FILE_FMT_TYPE_PPT;
	}

	if(strstr(szFmt, DOCUFORMAT_xls_office2013_4_adbit)) 
	{
		m_n_xls_Office_Count++;
		return ASIDFF_FILE_FMT_TYPE_XLS;
	}
	
	if(strstr(szFmt, DOCUFORMAT_xls2_office2013_4_adbit)) 
	{
		m_n_xls_Office_Count++;
		return ASIDFF_FILE_FMT_TYPE_XLS;
	}
	if(strstr(szFmt, DOCUFORMAT_pps_office2013ppt_4_adbit))
	{
		m_n_pps_Office_Count++;
		return ASIDFF_FILE_FMT_TYPE_PPS;
	}

	if(strstr(szFmt, DOCUFORMAT_ppt_office2013ppt_4_adbit)) 
	{
		m_n_ppt_Office_Count++;
		return ASIDFF_FILE_FMT_TYPE_PPT;
	}

	if(_strnicmp(szFmt, DOCUFORMAT_doc_office2013pub_1_adbit, 2)==0)
	{
		m_n_doc_Office_Count++;
		return ASIDFF_FILE_FMT_TYPE_DOC;
	}

	if(_strnicmp(szFmt, DOCUFORMAT_doc_office2013_1_adbit, 2)==0)
	{
		m_n_doc_Office_Count++;
		return ASIDFF_FILE_FMT_TYPE_DOC;
	}

	if(strstr(szFmt, DOCUFORMAT_hwp_han2010_8_adbit))
	{
		m_n_hwp3_Han_Count++;
		return ASIDFF_FILE_FMT_TYPE_HWP;
	}

	if(strstr(szFmt, DOCUFORMAT_xls_han2010_8_adbit))
	{
		m_n_xls_Han_Count++;
		return ASIDFF_FILE_FMT_TYPE_XLS;
	}
	if(strstr(szFmt, DOCUFORMAT_xls_chinese_8_adbit))
	{
		m_n_xls_Han_Count++;
		return ASIDFF_FILE_FMT_TYPE_XLS;
	}		

	if(strstr(szFmt, DOCUFORMAT_cell_han2010_8_adbit))
	{
		m_n_cell_Han_Count++;
		return ASIDFF_FILE_FMT_TYPE_CELL;
	}

	if(CheckFileExtAnalysis(pcFilePath, &nFileFmt) == 0)
		return nFileFmt;

	if(CheckZipFileContentAnalysis(pcFilePath, &nFileFmt) == 0)
		return nFileFmt;

	m_n_doc_Office_Count++;
	return ASIDFF_FILE_FMT_TYPE_DOC;
}

INT32 CDocFileFmtUtil::CheckZipFileContentAnalysis(char *pcFilePath, INT32 *pnFileFmtType)
{
	FILE* fp = NULL;
	char *pData = NULL; 
	INT32 nErrCode = 0;
	UINT32 dwMagicNumber = 0;
	ZIP_FILE_HEADER stZipHeader;
	if(pcFilePath == NULL || pnFileFmtType == NULL)
	{
		return -1;
	}

	fp = fopen(pcFilePath, "rb");
	if(fp==NULL)
	{
		return -2;
	}

	fread( &dwMagicNumber, sizeof(UINT32), 1, fp );

	if(ASIDFF_LOCAL_HEADER_MAGIC!=dwMagicNumber)
	{
		fclose(fp);
		return -3;
	}

	fread( &stZipHeader, sizeof(stZipHeader), 1, fp );
	if(stZipHeader.wNameSize < 1 || stZipHeader.wNameSize > 65535)
	{
		fclose(fp);
		return -4;
	}
	pData = (char *)malloc(stZipHeader.wNameSize + 1);
	if(pData == NULL)
	{
		fclose(fp);
		return -5;
	}
	fread(pData, stZipHeader.wNameSize, 1, fp );
	fclose(fp);
	
	if(!_stricmp(pData, DOCUFORMAT_office_open_xml))
	{
		m_n_docx_Office_Count++;
		*pnFileFmtType = ASIDFF_FILE_FMT_TYPE_DOCX;
	}
	else
	{
		m_n_zip_Count++;
		*pnFileFmtType = ASIDFF_FILE_FMT_TYPE_ZIP;
	}

	safe_free(pData);
	return 0;
}



INT32 CDocFileFmtUtil::CheckDocumentFile(char *pcFilePath, char *acLogMsg)
{
	FILE* fp = NULL;	
	BYTE *pData = NULL;  
	INT32 nRetVal = 0;
	INT32 nRead = 0;
	INT32 nErrCode = 0;
	char szFmt[MAX_QQBUFF+1] = {0,};
	char *pExt = NULL;


	if(pcFilePath == NULL)
	{
		if(acLogMsg)
			snprintf(acLogMsg, MAX_LOGMSG, "invalid input data");
		return ASIDFF_FILE_FMT_TYPE_UNKNOW;
	}
	fp = fopen(pcFilePath, "rb");
	if(fp==NULL)
	{
		if(acLogMsg)
			snprintf(acLogMsg, MAX_LOGMSG, "fail to open %s (%d)", pcFilePath, errno);
		return ASIDFF_FILE_FMT_TYPE_UNKNOW;
	}

	fseek(fp, 0L, SEEK_SET);
	
	pData = (BYTE *)malloc(READ_FIRST_FMT_BIN_MAX+1);
	if(pData == NULL)
	{
		if(acLogMsg)
			snprintf(acLogMsg, MAX_LOGMSG, "fail to allocate memory (%d)", errno);
		fclose(fp);
		return ASIDFF_FILE_FMT_TYPE_UNKNOW;
	}
	
	memset(pData, 0, READ_FIRST_FMT_BIN_MAX+1);

	nRead = (INT32)fread(pData, 1, READ_FIRST_FMT_BIN_MAX, fp);
	if ((!feof(fp) || (nErrCode = ferror(fp))) && nRead != READ_FIRST_FMT_BIN_MAX)
	{
		if(acLogMsg)
			snprintf(acLogMsg, MAX_LOGMSG, "fail to allocate memory (%d)", errno);
		fclose(fp);
		safe_free(pData);
		return ASIDFF_FILE_FMT_TYPE_UNKNOW;
	}
	pData[READ_FIRST_FMT_BIN_MAX] = 0;

	snprintf(szFmt, MAX_QQBUFF, "%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X",
		(BYTE)pData[0], (BYTE)pData[1], (BYTE)pData[2], (BYTE)pData[3], (BYTE)pData[4], (BYTE)pData[5], (BYTE)pData[6], (BYTE)pData[7],
		(BYTE)pData[8], (BYTE)pData[9], (BYTE)pData[10], (BYTE)pData[11], (BYTE)pData[12], (BYTE)pData[13], (BYTE)pData[14], (BYTE)pData[15]);

	fclose(fp);
	safe_free(pData);

	/***************************************************************************
		1.                               PK... 
     ***************************************************************************/
	if(_strnicmp(szFmt, HEADER_PK_COMMON_VAL, 8)==0) 
	{
		nRetVal = CheckPkFmtAnalysis(pcFilePath, szFmt, acLogMsg);
	}	
	/***************************************************************************
		2.          %PDF.. or 25504446..
     ***************************************************************************/
	else if(_strnicmp(szFmt, DOCUFORMAT_pdf_ALL_4, 8)==0) 
	{
		pExt = (char *)strrchr(pcFilePath, '.');
		if(pExt != NULL)
		{
			if(_stricmp(pExt, ".ai")==0)
			{
				return ASIDFF_FILE_FMT_TYPE_UNKNOW;
			}	
		}		
		m_n_pdf_Count++;
		nRetVal = ASIDFF_FILE_FMT_TYPE_PDF;
	}
	/***************************************************************************
		3.          {\rtf..
     ***************************************************************************/
	else if(_strnicmp(szFmt, DOCUFORMAT_doc_han_16, 32)==0)
	{
		m_n_doc_Han_Count++;
		nRetVal = ASIDFF_FILE_FMT_TYPE_DOC;
	}
	/***************************************************************************
		4.          <?xml..
     ***************************************************************************/
	else if(_strnicmp(szFmt, DOCUFORMAT_hml_han_8, 16)==0)
	{
		nRetVal = CheckHmlFmtAnalysis(pcFilePath, szFmt, acLogMsg);
	}
	/***************************************************************************
		5.          HWP(ฐ๘น้)..
     ***************************************************************************/	
	else if(_strnicmp(szFmt, DOCUFORMAT_hwp_han_4, 8)==0) 
	{
		nRetVal = CheckHwpFmtAnalysis(pcFilePath, szFmt, acLogMsg);
  	}
	/***************************************************************************
		6.          Robu..
     ***************************************************************************/
	else if(_strnicmp(szFmt, DOCUFORMAT_hpt_han_16, 32)==0)
	{
		m_n_hpt_Han_Count++;
		nRetVal = ASIDFF_FILE_FMT_TYPE_HPT;
	}
	/***************************************************************************
		7.          D0CF11E0A1B11AE1
     ***************************************************************************/
	else if(_strnicmp(szFmt, HEADER_D0CF_COMMON_VAL, 16)==0)
	{
		nRetVal = CheckDocFmtAnalysis(pcFilePath, szFmt, acLogMsg);
	}
	else
	{
		nRetVal = ASIDFF_FILE_FMT_TYPE_UNKNOW;
	}
	return nRetVal;
}
//-----------------------------------------------------------------------------------------------
