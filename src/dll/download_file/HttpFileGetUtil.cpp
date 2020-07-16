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
#include "HttpFileGetUtil.h"

CHttpFileGetUtil::CHttpFileGetUtil()
{
	memset (m_lpRootPath, 0, CHAR_MAX_SIZE);
	m_nContinue = 1;
}

CHttpFileGetUtil::~CHttpFileGetUtil()
{
}

void  CHttpFileGetUtil::EnableHttpUtil(INT32 nEnable)
{
    m_nContinue = nEnable;
}

INT32 CHttpFileGetUtil::GetFile_Address(LPSTR lpAddress, LPSTR lpFile, LPSTR lpSaveedFileName, INT32 nPort)
{
	int nSock = -1;
	sockaddr_in       sin;

	WriteLog("");
	WriteLog("---------------- Get File Recv Operation Start !! ---------------------------------------");
	WriteLog("DateTime : %s", GetCurrentDateTime(1).c_str());
	WriteLog("[%s]:[%d]", lpAddress, nPort);
	WriteLog("[%s]", lpFile);

	nSock = socket (AF_INET, SOCK_STREAM, 0);
    if (nSock == -1)
	{
		WriteLog("Error : [%d]", -100);
		return -100;
	}
    sin.sin_family = AF_INET;
    sin.sin_port = htons( (unsigned short)nPort);	
    sin.sin_addr.s_addr = inet_addr(lpAddress) ;    
	
    if( connect (nSock,(const struct sockaddr *)&sin, sizeof(sockaddr_in) ) == -1 ) 
	{
		WriteLog("connect failed : [%d][%d]", -101, errno) ;
		CLOSE_SOCK(nSock);
		return -101;
    }

	String send_str;

	SEND_RQ(nSock, "GET ");
	SEND_RQ(nSock,lpFile);
	SEND_RQ(nSock," HTTP/1.1\r\n");
	SEND_RQ(nSock,"Accept: */*\r\n");
	SEND_RQ(nSock,"Accept-Language: ko\r\n");
	SEND_RQ(nSock,"Accept-Encoding: gzip, deflate\r\n");	
	SEND_RQ(nSock,"User-Agent: Mozilla/4.0\r\n");
	SEND_RQ(nSock,"Host: ");
	SEND_RQ(nSock,lpAddress);
	SEND_RQ(nSock,"\r\n");
	SEND_RQ(nSock,"Connection: Keep-Alive\r\n");	
	SEND_RQ(nSock,"\r\n");
	SEND_RQ(nSock,"\r\n");
	SEND_RQ(nSock,"");
	SEND_RQ(nSock,"\r\n");
	
	char c1[1];
	int l,line_length;
	BOOL bLoop = TRUE;
	String strMessage;

	INT32 nLoopCnt = 100;
	
	while(bLoop && nLoopCnt) 
	{
		l = recv(nSock, c1, 1, 0);
		
		if(l == SOCKET_ERROR) 
		{
			if(errno == EAGAIN || errno == EWOULDBLOCK)
			{
				Sleep(10);
				nLoopCnt--;
			}
			else
				bLoop = false;
		}
		else if(l == 0)
		{
			if(nLoopCnt)
			{
				Sleep(10);
				nLoopCnt--;
				continue;
			}
			WriteLog("=========================   Recv Header Gracefully Closed Socket =========================");
            CLOSE_SOCK(nSock);
            return -890;		
		}

		if(c1[0]=='\n')
		{
			if(line_length == 0) 
				bLoop = FALSE;			
			line_length = 0;
		}
		else if(c1[0]!='\r') 
			line_length++;		

		strMessage += c1[0];
		nLoopCnt = 100;
	}

	WriteLog("HEADER INFO");
	WriteLog("[\n");	
	WriteLog((char *)strMessage.c_str());
	WriteLog("]");
	WriteLog("");

	
	DWORD dwWriteTotal = 0;
	DWORD dwRecvTotal = 0;
	DWORD dwRecvedTotal = 0;
    INT32 dwRecvLen;
    DWORD dwRecvOnceLen;
	INT32 nHeaderRtn;

    if(is_file(lpSaveedFileName) == 0)
        unlink(lpSaveedFileName);

	FILE *fp = fopen(lpSaveedFileName, "w+");
	if(fp == NULL)
	{
		WriteLog("fail to open %s : [%d]", lpSaveedFileName, errno);
		CLOSE_SOCK(nSock);
		return -666;
	}

	if(( nHeaderRtn = GetHeaderResult(strMessage)) == 200)
	{
		dwRecvTotal = GetRecvFileSize(strMessage);
		DWORD dwWaitTime = 0;
		UCHAR pszData[RECV_FILE_MAX_SIZE] = {0,};

		while(dwRecvTotal > 0 && dwRecvTotal > dwRecvedTotal && m_nContinue)
        {
            if(nSock == -1)
            {
                fclose(fp);
                WriteLog("Socket Handle is NULL");
                return -888;
            }

            if(dwRecvTotal - dwRecvedTotal > RECV_FILE_MAX_SIZE)
                dwRecvOnceLen = RECV_FILE_MAX_SIZE;
            else
                dwRecvOnceLen = dwRecvTotal - dwRecvedTotal;

            ZeroMemory(pszData, RECV_FILE_MAX_SIZE);
			dwRecvLen = recv(nSock, (char*)pszData, dwRecvOnceLen, 0);
            if(dwRecvLen == SOCKET_ERROR)
            {
                if((errno == EAGAIN || errno == EWOULDBLOCK) && dwWaitTime != 3000)
				{
					Sleep(10);
					dwWaitTime++;
				}
				else
				{
                    fclose(fp);
                    CLOSE_SOCK(nSock);
                    return -889;
                }
            }
			else if(dwRecvLen == 0)
			{
				fclose(fp);
				CLOSE_SOCK(nSock);
				WriteLog("=========================   Recv Gracefully Closed Socket =========================");
				return -890;	
			}
			else
			{
			    dwRecvedTotal += dwRecvLen;
                DWORD dwWriteLen = 0;
				dwWriteLen = (DWORD)fwrite(pszData, 1, (DWORD)dwRecvLen, fp);
				dwWriteTotal += dwWriteLen;
				dwWaitTime = 0;                
			}
        }
		fclose(fp);
        CLOSE_SOCK(nSock);

        if(dwRecvTotal == 0)
        {
            unlink(lpSaveedFileName);
        }

        if(m_nContinue== 0)
        {
            WriteLog("Operation stop by user");
            return -988;
        }

		CHAR acFileName[MAX_PATH] = {0, };
		
		get_basename(lpSaveedFileName, acFileName, MAX_PATH);

		WriteLog("BODY INFO");
		WriteLog("[\r\n");		
		WriteLog("File Saved : [%d] [%s]", dwWriteTotal, acFileName);
		WriteLog("\r\n]");
		WriteLog("");
	} 
	else 
	{
		CLOSE_SOCK(nSock);
		fclose(fp);
        unlink(lpSaveedFileName);
		WriteLog("Header Information Recv Fails : [%d]", (nHeaderRtn));
		return -102;
	}
	
	WriteLog("");
	WriteLog("DateTime : %s", GetCurrentDateTime(1).c_str());
	WriteLog("**************** Get File Operation Success !! ***************************************");
    WriteLog("");
	
	return 0;
}

INT32 CHttpFileGetUtil::GetFile_Host(LPSTR lpHostName, LPSTR lpFile, LPSTR lpSaveedFileName, INT32 nPort)
{
    CHAR lpAddress[MAX_PATH] = {0, };
	
	struct hostent * host_addr = gethostbyname(lpHostName);
    if(host_addr) 
	{
		struct in_addr ia;
		ia.s_addr = *((int*)*host_addr->h_addr_list);
		
		snprintf(lpAddress, MAX_PATH-1, "%s", inet_ntoa(ia));
		
		if(_stricmp(lpHostName, lpAddress))
		{
			WriteLog("host name to addr : [%s][%s]", lpHostName, lpAddress);
		}
    }
	else
	{
		WriteLog("Unable to locate host : %d", -103);
		strncpy(lpAddress, lpHostName, MAX_PATH-1);
	}
	    
	return GetFile_Address(lpAddress, lpFile, lpSaveedFileName, nPort);
}

void CHttpFileGetUtil::WriteLog(char *fmt,...)
{
	FILE *fp = NULL;
	va_list args;
	char acLogPath[CHAR_MAX_SIZE] = {0, };
	char acLogFile[CHAR_MAX_SIZE] = {0, };
	if(m_lpRootPath[0] == 0)
	{
		return;
	}

	snprintf(acLogPath, CHAR_MAX_SIZE-1,  "%s/log", m_lpRootPath);
	
	if(DirectoryExists(acLogPath) == FALSE)
	{
		CreateDirectory(acLogPath, NULL);
	}

	snprintf(acLogFile, CHAR_MAX_SIZE-1,  "%s/dm_http_download_%s.log", acLogPath, GetCurrentDateTime().c_str());
	
	if((fp =fopen(acLogFile, "a")) !=NULL)
	{		
		va_start(args,fmt);
		
		vfprintf(fp, fmt, args);
		fprintf(fp, "\n");
		fclose(fp);
		
		va_end(args);
	}
}

String CHttpFileGetUtil::GetCurrentDateTime(INT32 nDateTime)
{
	String strResult;
    time_t tTime = 0;
    struct tm *pTime = NULL;
	char acDate[16] = {0,} ;
    char acTime[16] = {0,} ;

	tTime = time(NULL);
	pTime = localtime(&tTime);
	if(pTime)
	{
		snprintf(acDate, 15, "%.4d_%.2d_%.2d", pTime->tm_year + 1900, pTime->tm_mon + 1, pTime->tm_mday);
		snprintf(acTime, 15, "%.2d:%.2d:%.2d", pTime->tm_hour, pTime->tm_min, pTime->tm_sec);
	}
    
    if(nDateTime)
        strResult = SPrintf("%s %s", acDate, acTime);
    else
        strResult = SPrintf("%s", acDate);

    return strResult;
}

void CHttpFileGetUtil::SetRootPath(LPSTR lpRootPath)
{
	if(lpRootPath != NULL)
	{
		strncpy(m_lpRootPath, lpRootPath, CHAR_MAX_SIZE-1);
	}
}

INT32 CHttpFileGetUtil::GetRecvFileSize(string strHeader)
{	
	INT32 nPos = 0;
    INT32 nRtn = -1;
	CHAR *pStr = NULL;
	CHAR *pStart = NULL;

	if(strHeader.length() == 0)
	{
		return -1;
	}

	String strHeaderValue = _strlwr((char *)strHeader.c_str());

	pStart = (char *)strHeaderValue.c_str();
	pStr = strstr(pStart, "content-length:");
	if(pStr == NULL)
		nPos = -1;
	else
		nPos = (INT32)(pStr - pStart);

    strHeader = strHeaderValue;

    if(nPos > -1)
    {
        nPos += 15;
        const char* lpFind = strHeader.c_str();
		CHAR lpNum[CHAR_MAX_SIZE] = {0, };
		
		int nIndex = nPos;
		int nSaveIndex = 0;
		while(lpFind[nIndex] != '\r')
		{
			if(lpFind[nIndex] != ' ')
			{
				lpNum[nSaveIndex] = lpFind[nIndex];
				nSaveIndex += 1;
			}
			nIndex += 1;
		}

		if(lpNum[0] != 0)
			nRtn = atoi(lpNum);
	}
	return nRtn;
}

INT32 CHttpFileGetUtil::GetHeaderResult(String strHeader)
{
	INT32 nPos = 0;
    INT32 nRtn = -1;
	CHAR *pStr = NULL;
	CHAR *pStart = NULL;

    String strHeaderValue = _strlwr((char *)strHeader.c_str());

	pStr = strstr((char *)strHeaderValue.c_str(), "http/");
	if(pStr == NULL)
	{
		nPos = -1;
	}
	else
		nPos = (INT32)(pStr - pStart);

    strHeader = strHeaderValue;

    if(nPos > -1)
    {
        nPos += 5;
        const char* lpFind = strHeader.c_str();
		CHAR lpNum[CHAR_MAX_SIZE] = {0, };
		
		int nFind	= 0;
		int nIndex = nPos;
		int nSaveIndex = 0;
		while(lpFind[nIndex] != '\r')
		{
			if(lpFind[nIndex] != ' ')
			{
				if(nFind == 1)
				{
					lpNum[nSaveIndex] = lpFind[nIndex];
					nSaveIndex += 1;
					nIndex += 1;
				}
				else
				{
					nIndex += 1;						
				}
			}
			else
			{
				nIndex += 1;
				nFind++;
			}
		}

		if(lpNum[0] != 0)
			nRtn = atoi(lpNum);
	}
	return nRtn;
}


