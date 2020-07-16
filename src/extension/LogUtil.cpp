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
char		glbm_LogFilePath[CHAR_MAX_SIZE] = {0, };
char		glbm_LogFileName[CHAR_MAX_SIZE] = {0, };
UINT32		glbm_nRemainLog = 1;
UINT32		glbm_nLogSKey = 0;

void	WriteLogN(char* fmt,...)
{
	FILE *fp;
	va_list args;
	char	lpSaveFile[CHAR_MAX_SIZE] = {0, };
	char	lpTimeBuf[CHAR_MAX_SIZE] = {0, };

	if(!glbm_nRemainLog)
		return;

	GetCurrentDateTime(0, lpTimeBuf);

    if(glbm_LogFilePath[0])
		strncpy(lpSaveFile, glbm_LogFilePath, CHAR_MAX_SIZE-1);
	else
		strncpy(lpSaveFile, "./log", CHAR_MAX_SIZE-1);
	
	make_dir(lpSaveFile);

	if(glbm_LogFileName[0])
		strcat_ext(lpSaveFile, glbm_LogFileName, CHAR_MAX_SIZE-1);
	else
		strcat_ext(lpSaveFile, "/system_log_", CHAR_MAX_SIZE-1);

    strcat_ext(lpSaveFile, lpTimeBuf, CHAR_MAX_SIZE-1);
    strcat_ext(lpSaveFile, ".txt", CHAR_MAX_SIZE-1);
	
    glbm_MutexLog.Lock();

	fp = fopen(lpSaveFile, "a");
	if(fp != NULL)
	{
		char lpLogBuf[CHAR_MAX_SIZE] = {0, };
		char lpBuf[CHAR_MAX_SIZE] = {0, };
		ZeroMemoryExt(lpTimeBuf);
		GetCurrentDateTime(1, lpTimeBuf);
		
		va_start(args,fmt);
		vsnprintf(lpBuf, CHAR_MAX_SIZE - 1, fmt, args);		
		va_end(args);

		if(!lpTimeBuf[0])
			sprintf_ext(CHAR_MAX_SIZE, lpTimeBuf, "time value is null(%d).", errno);

		sprintf_ext(CHAR_MAX_SIZE, lpLogBuf, "%s \t[Info]\t%s\r\n", lpTimeBuf, lpBuf);

		fwrite(lpLogBuf, sizeof(CHAR), strlen(lpLogBuf), fp);

		fclose(fp);
	}
	glbm_MutexLog.UnLock();
}
//-------------------------------------------------------------------------

void	WriteLogE(char* fmt,...)
{
	if(!glbm_nRemainLog)
		return;

    glbm_MutexLog.Lock();
	FILE *fp;
	va_list args;
	char	lpSaveFile[CHAR_MAX_SIZE] = {0, };
	char	lpTimeBuf[CHAR_MAX_SIZE] = {0, };
	
	GetCurrentDateTime(0, lpTimeBuf);

    if(glbm_LogFilePath[0])
		strncpy(lpSaveFile, glbm_LogFilePath, CHAR_MAX_SIZE-1);
	else
		strncpy(lpSaveFile, "./log", CHAR_MAX_SIZE-1);

	make_dir(lpSaveFile);
	
	if(glbm_LogFileName[0])
		strcat_ext(lpSaveFile, glbm_LogFileName, CHAR_MAX_SIZE-1);
	else
		strcat_ext(lpSaveFile, "/system_log_", CHAR_MAX_SIZE-1);

    strcat_ext(lpSaveFile, lpTimeBuf, CHAR_MAX_SIZE-1);
    strcat_ext(lpSaveFile, ".txt", CHAR_MAX_SIZE-1);
	
	if((fp =fopen(lpSaveFile, (glbm_nLogSKey ? "ab":"a"))) !=NULL)
	{
		char lpLogBuf[CHAR_MAX_SIZE] = {0, };
		char lpBuf[CHAR_MAX_SIZE] = {0, };
		ZeroMemoryExt(lpTimeBuf);
		GetCurrentDateTime(1, lpTimeBuf);
		
		va_start(args,fmt);
		vsnprintf(lpBuf, CHAR_MAX_SIZE - 1, fmt, args);		
		va_end(args);

		if(!lpTimeBuf[0])
			sprintf_ext(CHAR_MAX_SIZE, lpTimeBuf, "time value is null(%d).", errno);

		sprintf_ext(CHAR_MAX_SIZE, lpLogBuf, "%s \t[Error]\t%s\r\n", lpTimeBuf, lpBuf);

		if(glbm_nLogSKey)	WriteLog_Enc(lpLogBuf, fp);
		else				fwrite(lpLogBuf, sizeof(CHAR), strlen(lpLogBuf), fp);

		fclose(fp);
	}
	glbm_MutexLog.UnLock();
}
//-------------------------------------------------------------------------

/*
void	WriteLogN(UINT32 nID,...)
{
	char lpfmt[CHAR_MAX_SIZE] = {0, };
	char lpBuf[CHAR_MAX_SIZE] = {0, };

	LoadStringExt(lpfmt, nID);
	va_list args;
	va_start(args, nID);
	vsnprintf(lpBuf, CHAR_MAX_SIZE - 1, lpfmt, args);		
	va_end(args);

	WriteLogN(lpBuf);	
}
//-------------------------------------------------------------------------

void	WriteLogE(UINT32 nID,...)
{
	char lpfmt[CHAR_MAX_SIZE] = {0, };
	char lpBuf[CHAR_MAX_SIZE] = {0, };

	LoadStringExt(lpfmt, nID);
	va_list args;
	va_start(args, nID);
	vsnprintf(lpBuf, CHAR_MAX_SIZE - 1, lpfmt, args);		
	va_end(args);

	WriteLogE(lpBuf);
}
*/
//-------------------------------------------------------------------------

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
	if(!glbm_nRemainLog)	return;

	glbm_MutexLog.Lock();
	FILE *fp;
	va_list args;
	char	lpSaveFile[CHAR_MAX_SIZE] = {0, };
	char	lpTimeBuf[CHAR_MAX_SIZE] = {0, };

	GetCurrentDateTime(0, lpTimeBuf);

	if(glbm_LogFilePath[0])
		strncpy(lpSaveFile, glbm_LogFilePath, CHAR_MAX_SIZE-1);
	else
		strncpy(lpSaveFile, "./log", CHAR_MAX_SIZE-1);

	make_dir(lpSaveFile);

	strcat_ext(lpSaveFile, lpFileName, CHAR_MAX_SIZE-1);
	strcat_ext(lpSaveFile, lpTimeBuf, CHAR_MAX_SIZE-1);
	strcat_ext(lpSaveFile, ".txt", CHAR_MAX_SIZE-1);

	if(GetFileSizeExt(lpSaveFile) > (1024 * 1024 * nSize))
	{
		unlink(lpSaveFile);
	}

	if((fp =fopen(lpSaveFile, "a")) !=NULL)
	{
		char lpLogBuf[CHAR_MAX_SIZE] = {0, };
		char lpBuf[CHAR_MAX_SIZE] = {0, };
		ZeroMemoryExt(lpTimeBuf);
		GetCurrentDateTime(1, lpTimeBuf);

		va_start(args,fmt);
		vsnprintf(lpBuf, CHAR_MAX_SIZE - 1, fmt, args);		
		va_end(args);

		sprintf_ext(CHAR_MAX_SIZE, lpLogBuf, "%s \t[Info]\t%s\r\n", lpTimeBuf, lpBuf);

		fwrite(lpLogBuf, sizeof(CHAR), strlen(lpLogBuf), fp);
		fclose(fp);
	}
	glbm_MutexLog.UnLock();
}
//-------------------------------------------------------------------------

void	SetLogFileInfo(LPSTR lpLogPath, LPSTR lpLogName, INT32 nRmLog)
{
	glbm_nRemainLog = nRmLog;

	memset(glbm_LogFilePath, 0, CHAR_MAX_SIZE);
	memset(glbm_LogFileName, 0, CHAR_MAX_SIZE);
	if(lpLogPath != NULL && lpLogPath[0] != 0)
		strncpy(glbm_LogFilePath, lpLogPath, CHAR_MAX_SIZE-1);
	if(lpLogName != NULL && lpLogName[0] != 0)
		strncpy(glbm_LogFileName, lpLogName, CHAR_MAX_SIZE-1);
}
//-------------------------------------------------------------------------
