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
#include "LogUtil.h"


CMutexExt	glbm_MutexLog;
char		glbm_LogFilePath[MAX_PATH] = {0, };
char		glbm_LogFileName[MAX_FILE_NAME] = {0, };
UINT32		glbm_nRemainLog = 1;
UINT32		glbm_nLogSKey = 0;

void	WriteLogN(char* fmt,...)
{
	FILE *fp = NULL;
	va_list args;
	char acSaveFile[MAX_PATH] = {0, };
	char acTimeBuf[MAX_TIME_STR] = {0, };
	return;
/*
	if(!glbm_nRemainLog)
		return;
*/
	GetCurrentDateTime(0, acTimeBuf);

	if(glbm_LogFilePath[0] == 0)
	{
		char acRootPath[MAX_PATH] = {0, };
		if(get_nanny_agent_root(acRootPath, MAX_PATH) != 0)
			return;
		snprintf(glbm_LogFilePath, MAX_PATH-1, "%s/nanny/log", acRootPath);
	}
	if(glbm_LogFileName[0] == 0)
		strncpy(glbm_LogFileName, "/nanny_agt_sys_log_", MAX_FILE_NAME-1);
	snprintf(acSaveFile, MAX_PATH-1, "%s%s%s.txt", glbm_LogFilePath, glbm_LogFileName, acTimeBuf);
	
    glbm_MutexLog.Lock();

	fp = fopen(acSaveFile, "at");
	if(fp != NULL)
	{
		char acLogBuf[CHAR_MAX_SIZE] = {0, };
		GetCurrentDateTime(1, acTimeBuf);
		
		va_start(args,fmt);
		vsnprintf(acLogBuf, CHAR_MAX_SIZE - 1, fmt, args);		
		va_end(args);

		fprintf(fp, "%s\t[Info]\t%s\n", acTimeBuf, acLogBuf);

		fclose(fp);
	}
	glbm_MutexLog.UnLock();
}
//-------------------------------------------------------------------------

void	WriteLogE(char* fmt,...)
{
/*
	if(!glbm_nRemainLog)
		return;
*/
	FILE *fp = NULL;
	va_list args;
	char	acSaveFile[MAX_PATH] = {0, };
	char	acTimeBuf[MAX_TIME_STR] = {0, };
	
	GetCurrentDateTime(0, acTimeBuf);

	if(glbm_LogFilePath[0] == 0)
	{
		char acRootPath[MAX_PATH] = {0, };
		if(get_nanny_agent_root(acRootPath, MAX_PATH) != 0)
			return;
		snprintf(glbm_LogFilePath, MAX_PATH-1, "%s/nanny/log", acRootPath);
	}
	if(glbm_LogFileName[0] == 0)
		strncpy(glbm_LogFileName, "/nanny_agt_sys_log_", MAX_FILE_NAME-1);

	snprintf(acSaveFile, MAX_PATH-1, "%s%s%s.txt", glbm_LogFilePath, glbm_LogFileName, acTimeBuf);

	glbm_MutexLog.Lock();

	fp =fopen(acSaveFile, "at");
	if(fp != NULL)
	{
		char acLogBuf[CHAR_MAX_SIZE] = {0, };
		GetCurrentDateTime(1, acTimeBuf);
		
		va_start(args,fmt);
		vsnprintf(acLogBuf, CHAR_MAX_SIZE - 1, fmt, args);		
		va_end(args);

		fprintf(fp, "%s\t[Error]\t%s\n", acTimeBuf, acLogBuf);

		fclose(fp);
	}
	glbm_MutexLog.UnLock();
}

void	Encrypt_Log(UINT32	key, PBYTE SrcData,	INT32 SrcLen)
{	
	INT32 count = SrcLen / 4,
		remainCount = SrcLen % 4;
	INT32 i ;
	BYTE t ;
	UINT32 data ;
	UINT32 *p    = (UINT32 *)SrcData ;
	BYTE *p2   = (BYTE *)&key ;
	for( i = 0; i < count; i++ )
	{
		data = (p[i] ^ key) ;
		p[i] = ((data >> 24L) & 0x000000FF)
			| ((data << 8L)  & 0xFF000000)
			| ((data << 8L)  & 0x00FF0000)
			| ((data << 8L)  & 0x0000FF00);
	}
	for( i = 0; i < count; i++ )
	{
		data = (p[i] ^ key) ;
		p[i] = ((data >> 16L) & 0x000000FF)
			| ((data >> 16L) & 0x0000FF00)
			| ((data << 16L) & 0x00FF0000)
			| ((data << 16L) & 0xFF000000);
	}
	SrcData += 4*count ;

	for( i = 0; i < remainCount/2; i++ )
	{
		t = SrcData[i] ;

		SrcData[i] = SrcData[remainCount-i-1] ^ p2[i] ;
		SrcData[remainCount-i-1] = t ^ p2[i] ;
	}
	if( remainCount%2 != 0 )
	{
		SrcData[i] = SrcData[i] ^ p2[i] ;
	}
	return;
}
//--------------------------------------------------------------------

void		Decrypt_Log(UINT32	key, PBYTE SrcData,	INT32 SrcLen)
{
	INT32	count = SrcLen / 4,	remainCount = SrcLen % 4;
	INT32	i ;
	BYTE	t ;
	UINT32 data ;
	UINT32 *p    = (UINT32 *)SrcData ;
	BYTE *p2   = (BYTE *)&key ;
	for( i = 0; i < count; i++ )
	{
		data = p[i] ;
		p[i] = ((data << 16L) & 0xFF000000)
			| ((data << 16L) & 0x00FF0000)
			| ((data >> 16L) & 0x0000FF00)
			| ((data >> 16L) & 0x000000FF);
		p[i] = (p[i] ^ key) ;
	}
	for( i = 0; i < count; i++ )
	{
		data = p[i] ;
		p[i] = ((data << 24L) & 0xFF000000)
			| ((data >> 8L)  & 0x00FF0000)
			| ((data >> 8L)  & 0x0000FF00)
			| ((data >> 8L)  & 0x000000FF);
		p[i] = (p[i] ^ key) ;
	}
	SrcData += 4*count ;

	for( i = 0; i < remainCount/2; i++ )
	{
		t = SrcData[i] ;

		SrcData[i] = SrcData[remainCount-i-1] ^ p2[i] ;
		SrcData[remainCount-i-1] = t ^ p2[i] ;
	}
	if( remainCount%2 != 0 )
	{
		SrcData[i] = SrcData[i] ^ p2[i] ;
	}
	return;
}
//-------------------------------------------------------------------- 

void		WriteLog_Enc(LPTSTR lpLog, FILE* fp)
{
	BYTE lpEncBuff[CHAR_MAX_SIZE + 2] = {0, };
	INT16 nEncLen = strlen(lpLog);
	if(nEncLen <= 0)
		return;

	Encrypt_Log(glbm_nLogSKey, (PBYTE)lpLog, nEncLen);	

	memcpy(lpEncBuff, &nEncLen, sizeof(INT16));
	memcpy(lpEncBuff + 2, lpLog, nEncLen);
	
	{
		UINT32 nWEndLen = 0;
		UINT32 nWToLen = nEncLen + 2;

		while(nWEndLen != nWToLen)
		{
			INT32 nWOneLen = fwrite(lpEncBuff + nWEndLen, sizeof(BYTE), nWToLen-nWEndLen, fp);
			if(nWOneLen < 0)	break;

			nWEndLen += nWOneLen;
		}
	}
	return;
}
//-------------------------------------------------------------------------------------------

void	SetLogSKey(UINT32 nSKey)
{
	glbm_nLogSKey = nSKey;
	return;
}
//-------------------------------------------------------------------------------------------

void    WriteLogN_Size(UINT32 nSize, LPCTSTR lpFileName, char* fmt,...)
{
/*
	if(!glbm_nRemainLog)	return;
*/
	
	FILE *fp = NULL;
	va_list args;
	char acSaveFile[MAX_PATH] = {0, };
	char acTimeBuf[MAX_TIME_STR] = {0, };

	GetCurrentDateTime(0, acTimeBuf);


	if(glbm_LogFilePath[0] == 0)
	{
		char acRootPath[MAX_PATH] = {0, };
		if(get_nanny_agent_root(acRootPath, MAX_PATH) != 0)
			return;
		snprintf(glbm_LogFilePath, MAX_PATH-1, "%s/nanny/log", acRootPath);
	}

	snprintf(acSaveFile, MAX_PATH-1, "%s%s%s.txt", glbm_LogFilePath, lpFileName, acTimeBuf);

	if(GetFileSizeExt(acSaveFile) > (ASI_MEGABYTE * nSize))
	{
		unlink(acSaveFile);
	}

	glbm_MutexLog.Lock();
	if((fp =fopen(acSaveFile, "a")) !=NULL)
	{
		char acLogBuf[CHAR_MAX_SIZE] = {0, };
		GetCurrentDateTime(1, acTimeBuf);

		va_start(args,fmt);
		vsnprintf(acLogBuf, CHAR_MAX_SIZE - 1, fmt, args);		
		va_end(args);

		fprintf(fp, "%s\t[Info]\t%s\n", acTimeBuf, acLogBuf);

		fclose(fp);
	}
	glbm_MutexLog.UnLock();
}
//-------------------------------------------------------------------------

void	SetLogFileInfo(LPSTR lpLogPath, LPSTR lpLogName, INT32 nRmLog)
{
	glbm_nRemainLog = nRmLog;

	memset(glbm_LogFilePath, 0, MAX_PATH);
	memset(glbm_LogFileName, 0, MAX_FILE_NAME);
	if(lpLogPath != NULL && lpLogPath[0] != 0)
		strncpy(glbm_LogFilePath, lpLogPath, MAX_PATH-1);
	if(lpLogName != NULL && lpLogName[0] != 0)
		strncpy(glbm_LogFileName, lpLogName, MAX_FILE_NAME-1);
}
//-------------------------------------------------------------------------
