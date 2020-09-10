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
//---------------------------------------------------------------------------
#include "MemToken.h"

//---------------------------------------------------------------------------

#define MEMTOKEN_TYPE_BLOCK			0x00
#define MEMTOKEN_TYPE_UINT8			0x01
#define MEMTOKEN_TYPE_UINT16		0x02
#define MEMTOKEN_TYPE_UINT32		0x03
#define MEMTOKEN_TYPE_UINT64		0x04
#define MEMTOKEN_TYPE_STRING		0x05
#define MEMTOKEN_TYPE_PVOID			0x06

                                                   
MemToken::MemToken()
{
    buf = NULL ;
    pos = 0 ;
    bufLen = 0 ;
    nAllocMem      = FALSE ;
}
//-----------------------------------------------------------------------------------

MemToken::MemToken(INT32 aInitialSize )
{
    if( aInitialSize < 10 )
        aInitialSize = 10 ;

    pos = 0 ;
    bufLen = aInitialSize ;
    buf = new BYTE[aInitialSize] ;

    nAllocMem = TRUE ;
}
//-----------------------------------------------------------------------------------


MemToken::MemToken(PVOID pSrc, INT32 nLen)
{
    buf = (PBYTE)pSrc ;
    pos = 0 ;
    bufLen       = nLen ;
    nAllocMem      = FALSE ;
}
//-----------------------------------------------------------------------------------

void	MemToken::Clear()
{
	pos = 0;
	memset(buf, 0, bufLen);
	return;
}
//-----------------------------------------------------------------------------------

MemToken::~MemToken()
{
    if( nAllocMem )
    {
        delete[] buf; 		
    }

    buf = NULL ;
    pos = 0 ;
    bufLen = 0 ;
}
//-----------------------------------------------------------------------------------

void MemToken::Set(PVOID pSrc, INT32 nLen)
{
    if( nAllocMem )
    {
        delete[] buf; 
    }

    buf          = (PBYTE)pSrc ;
    pos          = 0 ;
    bufLen       = nLen ;
    nAllocMem    = FALSE ;
}
//-----------------------------------------------------------------------------------

void MemToken::Set(INT32 aInitialSize)
{
    if( nAllocMem )
    {
        delete[] buf ;
    }
    
    pos          = 0 ;
    bufLen       = aInitialSize ;
    buf          = new BYTE[aInitialSize] ;
    nAllocMem    = TRUE ;
}
//-----------------------------------------------------------------------------------

void MemToken::Release()
{
	if( nAllocMem )
	{
		delete[] buf; 		
	}

	buf = NULL ;
	pos = 0 ;
	bufLen = 0 ;
	nAllocMem = FALSE;
}
//-----------------------------------------------------------------------------------

void MemToken::Copy(PVOID pSrc, INT32 nLen)
{
	if( nAllocMem )
	{
		if(buf)	delete[] buf;
		buf = NULL;
	}

	if(nLen)
	{
		buf          = new BYTE[nLen + 1] ;
		memset(buf, 0, nLen + 1);
		memcpy(buf, pSrc, nLen);
	}
	pos          = nLen ;
	bufLen       = nLen ;
	nAllocMem    = TRUE ;
}
//-----------------------------------------------------------------------------------

void MemToken::SetCopy(PVOID pSrc, INT32 nLen)
{
	if( nAllocMem )
	{
		if(buf)	delete[] buf;
		buf = NULL;
	}

	if(nLen)
	{
		buf          = new BYTE[nLen + 1] ;
		memset(buf, 0, nLen + 1);
		memcpy(buf, pSrc, nLen);
	}
	pos          = 0 ;
	bufLen       = nLen ;
	nAllocMem    = TRUE ;
}
//-----------------------------------------------------------------------------------

BOOL MemToken::_TokenAdd(PVOID pSrc, INT32 nLen)
{
    PBYTE tbuf ;
    
    if( buf == NULL )
        return FALSE ;

    if( pos + nLen > bufLen )
    {
        if( nAllocMem )
        {
            while( pos + nLen > bufLen )
            {
                tbuf = new BYTE[bufLen*2] ;
                memcpy(tbuf, buf, bufLen) ;
                delete[] buf ;
                
                buf = tbuf ;
                bufLen *= 2 ;
                continue ;
            }
        }
        else
        {
            return FALSE ;
        }
    }

    memcpy(buf+pos, pSrc, nLen) ;	
    pos += nLen ;
    return TRUE ;    
}
//-----------------------------------------------------------------------------------

// 입력된 바이트 만큼을 뺀다
BOOL MemToken::_TokenDel(void *aDest, INT32 nLen)
{
    if( buf == NULL )
        return FALSE ;

    if( pos + nLen > bufLen )
        return FALSE ;

    memcpy(aDest, buf+pos, nLen) ;
    pos += nLen ;
    return TRUE ;    
}
//-----------------------------------------------------------------------------------

BOOL MemToken::_IsTokenType(UINT8 nType)
{
	if( buf == NULL )
		return FALSE ;

	if( pos + 1 > bufLen )
		return FALSE ;

	if(buf[pos] != nType)
		return FALSE;
	
	pos += 1 ;
	return TRUE ;    
}
//-----------------------------------------------------------------------------------

BOOL MemToken::_TokenAddType(UINT8 nType)
{
	if(!_TokenAdd(&nType, 1))
		return FALSE;
	return TRUE;
}
//-----------------------------------------------------------------------------------

BOOL MemToken::_TokenDelType(UINT8& nType)
{
	if(!_TokenDel(&nType, 1))
		return FALSE;
	return TRUE;
}
//-----------------------------------------------------------------------------------

BOOL MemToken::TokenSet_Block()
{
	if(!_TokenAddType(MEMTOKEN_TYPE_BLOCK))
		return FALSE;

	return TRUE;
}
//-----------------------------------------------------------------------------------

BOOL MemToken::TokenSkip_Block()
{
	UINT8 nType = 0;
	while(_TokenDelType(nType))
	{
		switch(nType)
		{
			case MEMTOKEN_TYPE_BLOCK:		return TRUE;	break;
			case MEMTOKEN_TYPE_UINT8:		pos += 1;		break;
			case MEMTOKEN_TYPE_UINT16:		pos += 2;		break;
			case MEMTOKEN_TYPE_UINT32:		pos += 4;		break;
			case MEMTOKEN_TYPE_UINT64:		pos += 8;		break;
			case MEMTOKEN_TYPE_STRING:
			case MEMTOKEN_TYPE_PVOID:
			{
				INT32 len = 0;
				if( !TokenDel_32( len ) )
					return FALSE;

				pos += len;
				break;
			}
			default:
			{
				return FALSE;
			}
		}
	}

	return (bufLen == pos ? TRUE : FALSE);
}
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------

BOOL MemToken::TokenAdd_8(INT8 pSrc)
{
	if(!_TokenAddType(MEMTOKEN_TYPE_UINT8))
		return FALSE;
	
	INT8 a = pSrc;
	if(!_TokenAdd(&a, 1))
		return FALSE;
	return TRUE;
}
//-----------------------------------------------------------------------------------

BOOL MemToken::TokenAdd_16(INT16 pSrc)
{
	if(!_TokenAddType(MEMTOKEN_TYPE_UINT16))
		return FALSE;
	
	INT16 a = ntohs(pSrc);
	if(!_TokenAdd(&a, 2))
		return FALSE;
	return TRUE;
}
//-----------------------------------------------------------------------------------

BOOL MemToken::TokenAdd_32(INT32 pSrc)
{
	if(!_TokenAddType(MEMTOKEN_TYPE_UINT32))
		return FALSE;

	INT32 a = ntohl(pSrc);
	if(!_TokenAdd(&a, 4))
		return FALSE;
	return TRUE;
}
//-----------------------------------------------------------------------------------

BOOL MemToken::TokenAdd_64(INT64 pSrc)
{
	if(!_TokenAddType(MEMTOKEN_TYPE_UINT64))
		return FALSE;

	if(!_TokenAdd(&pSrc, 8))
		return FALSE;
	return TRUE;
}

INT32  MemToken::Conver_Euckr(char *pSrcData, int nSrcLen, char **ppDstData)
{
	iconv_t it;
	INT32 nRetVal = 0;
	char *pDstData = NULL;
	char *pSrc = NULL;
	char *pDst = NULL;

	size_t nSrcStrLen = (size_t)nSrcLen;
	size_t nDstStrLen = nSrcLen*2+3;

	if(pSrcData == NULL || ppDstData == NULL || nSrcStrLen < 1)
		return -1;

	it = iconv_open(CHARSET_EUCKR, CHARSET_UTF8);
	if (it == (iconv_t)(-1))
	{
		return -2;
	}

	do{
		pDstData = (char *)malloc(nDstStrLen + 1);
		if(pDstData == NULL)
		{
			nRetVal = -4;
			break;
		}
		memset(pDstData, 0, nDstStrLen + 1);

		pSrc = pSrcData;
		pDst = pDstData;

		if(iconv(it, &pSrc, &nSrcStrLen, &pDst, &nDstStrLen) == (size_t)(-1))
		{
			nRetVal = -5;
			break;
		}

		nRetVal = 0;
	}while(FALSE);

	iconv_close(it);

	if(nRetVal == 0)
	{
		*ppDstData = pDstData;
	}
	else
	{
		safe_free(pDstData);
	}
	return nRetVal;
}

//-----------------------------------------------------------------------------------

BOOL MemToken::TokenAdd_String(String strSrc)
{
	char *pDstData = NULL;
	INT32 nRetVal = 0;
	INT32 nLen = 0;
	String strDstSrc;
	if(!_TokenAddType(MEMTOKEN_TYPE_STRING))
		return FALSE;
	strDstSrc = strSrc;

	nLen = strDstSrc.length();
	if(nLen > 0)
	{
		nRetVal = Conver_Euckr((char *)strDstSrc.c_str(), nLen, &pDstData);
		if(nRetVal == 0 && pDstData != NULL)
		{
			strDstSrc = SPrintf(pDstData);
			safe_free(pDstData);
		}
	}

	nLen = strDstSrc.length();
	if( !TokenAdd_32( nLen ) )
		return FALSE;

	if( !_TokenAdd( (PVOID)strDstSrc.c_str(), nLen) )
		return FALSE;
	return TRUE ;
}
//-----------------------------------------------------------------------------------

BOOL MemToken::TokenAdd_StringW(StringW pSrc)
{
	if(!_TokenAddType(MEMTOKEN_TYPE_PVOID))
		return FALSE;

	INT32 len = pSrc.length() * 2;
	if( !TokenAdd_32( len ) )
		return FALSE ;
	if( !_TokenAdd( (PVOID)pSrc.c_str(), len) )
		return FALSE ;

	return TRUE ;
}
//-----------------------------------------------------------------------------------


BOOL MemToken::TokenAdd_PVOID(PVOID pSrc, INT32 nLen)
{
	if(!_TokenAddType(MEMTOKEN_TYPE_PVOID))
		return FALSE;
	
	if( !TokenAdd_32( nLen ) )
		return FALSE ;
	if( !_TokenAdd( pSrc, nLen) )
		return FALSE ;

	return TRUE ;
}
//-----------------------------------------------------------------------------------

BOOL MemToken::TokenAdd_IDList(TListID& tIDList)
{
	TokenAdd_32(tIDList.size());
	TListIDItor begin, end;
	begin = tIDList.begin();	end = tIDList.end();
	for(begin; begin != end; begin++)
	{
		TokenAdd_32(*begin);
	}
	return 0;
}
//-----------------------------------------------------------------------------------

BOOL MemToken::TokenAdd_IDMap(TMapID& tIDMap)
{
	TokenAdd_32(tIDMap.size());
	TMapIDItor begin, end;
	begin = tIDMap.begin();	end = tIDMap.end();
	for(begin; begin != end; begin++)
	{
		TokenAdd_32(begin->first);
		TokenAdd_32(begin->second);
	}
	return 0;
}
//-----------------------------------------------------------------------------------

BOOL MemToken::TokenAdd_ID64Map(TMapID64& tID64Map)
{
	TokenAdd_64(tID64Map.size());
	TMapID64Itor begin, end;
	begin = tID64Map.begin();	end = tID64Map.end();
	for(begin; begin != end; begin++)
	{
		TokenAdd_64(begin->first);
		TokenAdd_64(begin->second);
	}
	return 0;
}
//-----------------------------------------------------------------------------------

BOOL MemToken::TokenAdd_IDMapList(TMapIDList& tIDMapList)
{
	TokenAdd_32(tIDMapList.size());
	TMapIDListItor begin, end;
	begin = tIDMapList.begin();	end = tIDMapList.end();
	for(begin; begin != end; begin++)
	{
		TokenAdd_32(begin->first);
		TokenAdd_IDList(begin->second);
	}
	return 0;
}
//-----------------------------------------------------------------------------------

BOOL MemToken::TokenAdd_IDMapStr(TMapIDStr& tIDStrMap)
{
	TokenAdd_32(tIDStrMap.size());
	TMapIDStrItor begin, end;
	begin = tIDStrMap.begin();	end = tIDStrMap.end();
	for(begin; begin != end; begin++)
	{
		TokenAdd_32(begin->first);
		TokenAdd_String(begin->second);
	}

	return 0;
}
//-----------------------------------------------------------------------------------

BOOL MemToken::TokenAdd_StringList(TListStr& tStrList)
{
	TokenAdd_32(tStrList.size());
	TListStrItor begin, end;
	begin = tStrList.begin();	end = tStrList.end();
	for(begin; begin != end; begin++)
	{
		TokenAdd_String(*begin);
	}
	return 0;
}
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------

BOOL MemToken::TokenDel_8(INT8& pSrc)
{
	if(!_IsTokenType(MEMTOKEN_TYPE_UINT8))
		return FALSE;
	
	INT8 a = 0;
	if(!_TokenDel(&a, 1))
		return FALSE;

	pSrc = a;
	return TRUE;
}
//-----------------------------------------------------------------------------------

BOOL MemToken::TokenDel_8(UINT8& pSrc)
{
	if(!_IsTokenType(MEMTOKEN_TYPE_UINT8))
		return FALSE;

	UINT8 a = 0;
	if(!_TokenDel(&a, 1))
		return FALSE;

	pSrc = a;
	return TRUE;
}
//-----------------------------------------------------------------------------------

BOOL MemToken::TokenDel_16(INT16& pSrc)
{
	if(!_IsTokenType(MEMTOKEN_TYPE_UINT16))
		return FALSE;

	INT16 a = 0;
	if(!_TokenDel(&a, 2))
		return FALSE;

	pSrc = ntohs(a);
	return TRUE;
}
//-----------------------------------------------------------------------------------

BOOL MemToken::TokenDel_16(UINT16& pSrc)
{
	if(!_IsTokenType(MEMTOKEN_TYPE_UINT16))
		return FALSE;

	INT16 a = 0;
	if(!_TokenDel(&a, 2))
		return FALSE;

	pSrc = ntohs(a);
	return TRUE;
}
//-----------------------------------------------------------------------------------

BOOL MemToken::TokenDel_32(INT32& pSrc)
{
	if(!_IsTokenType(MEMTOKEN_TYPE_UINT32))
		return FALSE;
	
	INT32 a = 0;
	if(!_TokenDel(&a, 4))
		return FALSE;

	pSrc = ntohl(a);
	return TRUE;
}
//-----------------------------------------------------------------------------------

BOOL MemToken::TokenDel_32(UINT32& pSrc)
{
	if(!_IsTokenType(MEMTOKEN_TYPE_UINT32))
		return FALSE;

	INT32 a = 0;
	if(!_TokenDel(&a, 4))
		return FALSE;

	pSrc = ntohl(a);
	return TRUE;
}
//-----------------------------------------------------------------------------------

BOOL MemToken::TokenDel_64(INT64& pSrc)
{
	if(!_IsTokenType(MEMTOKEN_TYPE_UINT64))
		return FALSE;
	
	if(!_TokenDel(&pSrc, 8))
		return FALSE;
	return TRUE;
}

//-----------------------------------------------------------------------------------

INT32  MemToken::Conver_Utf8(char *pSrcData, int nSrcLen, char **ppDstData)
{
	iconv_t it;
	INT32 nRetVal = 0;
	char *pDstData = NULL;
	char *pSrc = NULL;
	char *pDst = NULL;

	size_t nSrcStrLen = (size_t)nSrcLen;
	size_t nDstStrLen = nSrcLen*4+1;

	if(pSrcData == NULL || ppDstData == NULL || nSrcStrLen < 1)
		return -1;

	it = iconv_open(CHARSET_UTF8, CHARSET_EUCKR);
	if (it == (iconv_t)(-1))
	{
		return -2;
	}

	do{
		pDstData = (char *)malloc(nDstStrLen + 1);
		if(pDstData == NULL)
		{
			nRetVal = -4;
			break;
		}
		memset(pDstData, 0, nDstStrLen + 1);

		pSrc = pSrcData;
		pDst = pDstData;

		if(iconv(it, &pSrc, &nSrcStrLen, &pDst, &nDstStrLen) == (size_t)(-1))
		{
			nRetVal = -5;
			break;
		}

		nRetVal = 0;
	}while(FALSE);

	iconv_close(it);

	if(nRetVal == 0)
	{
		*ppDstData = pDstData;
	}
	else
	{
		safe_free(pDstData);
	}
	return nRetVal;
}


BOOL MemToken::TokenDel_64(UINT64& pSrc)
{
	if(!_IsTokenType(MEMTOKEN_TYPE_UINT64))
		return FALSE;

	if(!_TokenDel(&pSrc, 8))
		return FALSE;
	return TRUE;
}
//-----------------------------------------------------------------------------------

INT32 MemToken::TokenDel_String(String& strSrc)
{
	INT32 nLen = 0;
	INT32 nRetVal = 0;
	char* pszBuf = NULL;
	char* pszUtfBuf = NULL;
	if(!_IsTokenType(MEMTOKEN_TYPE_STRING))
		return 0;

	do{
		if( !TokenDel_32( nLen ) )
		{
			nRetVal = -1;
			break;
		}

		pszBuf = (char*)malloc(nLen + 1);
		if(pszBuf == NULL)
		{
			nRetVal = -2;
			break;
		}

		memset(pszBuf, 0, nLen+1);

		if( !_TokenDel( (PVOID)pszBuf, nLen) )
		{
			nRetVal = -3;
			break;
		}

		nRetVal = Conver_Utf8(pszBuf, nLen, &pszUtfBuf);
		if(nRetVal == 0 && pszUtfBuf != NULL)
		{
			strSrc = String(pszUtfBuf);
			safe_free(pszUtfBuf);
		}
		else
		{
			strSrc = String(pszBuf);
		}
		nRetVal = nLen;
	}while(FALSE);

	safe_free(pszBuf);

	return nRetVal;
}
//-----------------------------------------------------------------------------------

INT32 MemToken::TokenDel_StringW(StringW& pSrc)
{
	if(!_IsTokenType(MEMTOKEN_TYPE_PVOID))
		return FALSE;

	INT32 len = 0;
	if( !TokenDel_32( len ) )
		return -1 ;

	char* ppSrc = (char*)malloc(len + 2);
	if(!ppSrc)		return -1;

	memset(ppSrc, 0, len+2);

	if( !_TokenDel( (PVOID)ppSrc, len) )
	{
		free(ppSrc);
		return -1 ;
	}

	pSrc = StringW((PWCHAR)ppSrc);
	free(ppSrc);
	return len ;
}
//-----------------------------------------------------------------------------------

INT32 MemToken::TokenDel_char(LPSTR pSrc, INT32 nLen)
{
	if(!_IsTokenType(MEMTOKEN_TYPE_STRING))
		return FALSE;

    INT32 len = 0;
    if( !TokenDel_32( len ) )
        return -1 ;

	char* pszBuf = (char*)malloc(len + 1);
	if(!pszBuf)		return -1;

	memset(pszBuf, 0, len+1);

    if( !_TokenDel( (PVOID)pszBuf, len) )
	{
		free(pszBuf);
        return -1 ;
	}

	strncpy(pSrc, pszBuf, nLen - 1);
	free(pszBuf);

    return len ;
}
//-----------------------------------------------------------------------------------

INT32 MemToken::TokenDel_PVOID(PVOID* ppSrc, PUINT32 pLen)
{
	if(!_IsTokenType(MEMTOKEN_TYPE_PVOID))
		return FALSE;

	INT32 len = 0;
	if( !TokenDel_32( len ) )
		return -1 ;

	*ppSrc = (char*)malloc(len + 1);
	if(!*ppSrc)		return -1;

	memset(*ppSrc, 0, len+1);

	if( !_TokenDel( (PVOID)*ppSrc, len) )
	{
		free(*ppSrc);
		return -1 ;
	}

	if(pLen)	*pLen = len;

	return len ;
}
//-----------------------------------------------------------------------------------

INT32 MemToken::TokenDel_IDList(TListID& tIDList)
{
	UINT32 nRecvNum = 0;
	UINT32 nRecvID = 0;

	if(!TokenDel_32(nRecvNum))			goto INVALID_PKT;
	while(nRecvNum)
	{
		if(!TokenDel_32(nRecvID))		goto INVALID_PKT;

		tIDList.push_back(nRecvID);
		nRecvNum--;
	}
	return tIDList.size();

INVALID_PKT:
	return -1;
}
//-----------------------------------------------------------------------------------

INT32 MemToken::TokenDel_IDMap(TMapID& tIDMap)
{
	UINT32 nRecvNum = 0;
	UINT32 nRecvID = 0, nRecvValue = 0;

	if(!TokenDel_32(nRecvNum))				goto INVALID_PKT;
	while(nRecvNum)
	{
		if(!TokenDel_32(nRecvID))			goto INVALID_PKT;
		if(!TokenDel_32(nRecvValue))		goto INVALID_PKT;

		tIDMap[nRecvID] = nRecvValue;
		nRecvNum--;
	}
	return tIDMap.size();

INVALID_PKT:
	return -1;
}
//-----------------------------------------------------------------------------------

INT32 MemToken::TokenDel_ID64Map(TMapID64& tID64Map)
{
	UINT64 nRecvNum = 0;
	UINT64 nRecvID = 0, nRecvValue = 0;

	if(!TokenDel_64(nRecvNum))				goto INVALID_PKT;
	while(nRecvNum)
	{
		if(!TokenDel_64(nRecvID))			goto INVALID_PKT;
		if(!TokenDel_64(nRecvValue))		goto INVALID_PKT;

		tID64Map[nRecvID] = nRecvValue;
		nRecvNum--;
	}
	return tID64Map.size();

INVALID_PKT:
	return -1;
}
//-----------------------------------------------------------------------------------

INT32 MemToken::TokenDel_IDMapList(TMapIDList& tIDMapList)
{
	UINT32 nRecvNum = 0;
	UINT32 nRecvID = 0;
	TListID tRecvIDList;

	if(!TokenDel_32(nRecvNum))					goto INVALID_PKT;
	while(nRecvNum)
	{
		if(!TokenDel_32(nRecvID))				goto INVALID_PKT;
		if( TokenDel_IDList(tRecvIDList) < 0)	goto INVALID_PKT;

		tIDMapList[nRecvID] = tRecvIDList;
		tRecvIDList.clear();
		nRecvNum--;
	}
	return tIDMapList.size();

INVALID_PKT:
	return -1;
}
//-----------------------------------------------------------------------------------

INT32 MemToken::TokenDel_IDMapStr(TMapIDStr&	tIDStrMap)
{
	UINT32 nRecvNum = 0;
	UINT32 nRecvID = 0;
	String strRecvValue;

	if(!TokenDel_32(nRecvNum))
		goto INVALID_PKT;
	
	while(nRecvNum)
	{
		if(!TokenDel_32(nRecvID))					goto INVALID_PKT;
		if(TokenDel_String(strRecvValue) < 0)		goto INVALID_PKT;

		tIDStrMap[nRecvID] = strRecvValue;
		nRecvNum--;
	}
	return tIDStrMap.size();

INVALID_PKT:
	return -1;
}
//-----------------------------------------------------------------------------------

INT32 MemToken::TokenDel_StrList(TListStr& tStrList)
{
	UINT32 nRecvNum = 0;
	String strRecvValue;

	if(!TokenDel_32(nRecvNum))			goto INVALID_PKT;
	while(nRecvNum)
	{
		if(TokenDel_String(strRecvValue) < 0)		goto INVALID_PKT;

		tStrList.push_back(strRecvValue);
		nRecvNum--;
	}
	return tStrList.size();

INVALID_PKT:
	return -1;
}

//-----------------------------------------------------------------------------------

INT32 MemToken::TokenDel_StrMap(TMapStr& tStrMap)
{
	UINT32 nRecvNum = 0;
	String strKey, strValue;

	if(!TokenDel_32(nRecvNum))				goto INVALID_PKT;
	while(nRecvNum)
	{
		if( TokenDel_String(strKey) < 0)	goto INVALID_PKT;
		if( TokenDel_String(strValue) < 0)	goto INVALID_PKT;

		tStrMap[strKey] = strValue;
		nRecvNum--;
	}
	return tStrMap.size();

INVALID_PKT:
	return -1;
}
//-----------------------------------------------------------------------------------

BOOL	MemToken::TokenAdd_DPH(DB_PO_HEADER& tDPH)
{
	TokenAdd_32(tDPH.nID);
	TokenAdd_32(tDPH.nRegDate);
	TokenAdd_32(tDPH.nSeqNo);
	TokenAdd_String(tDPH.strName);
	TokenAdd_String(tDPH.strDescr);

	TokenAdd_32(tDPH.nAdminID);
	TokenAdd_32(tDPH.nSubAdminLock);
	TokenAdd_32(tDPH.nTargetLock);
	TokenAdd_32(tDPH.nPolicyID);
	TokenAdd_32(tDPH.nUnitID);
	TokenAdd_32(tDPH.nNotifyInfoID);
	TokenAdd_32(tDPH.nExtOption);
	TokenAdd_32(tDPH.nUsedMode);	
	return TRUE;
}
//-----------------------------------------------------------------------------------

INT32	MemToken::TokenDel_DPH(DB_PO_HEADER& tDPH)
{
	if (!TokenDel_32(tDPH.nID))					goto	INVALID_PKT;
	if (!TokenDel_32(tDPH.nRegDate))			goto 	INVALID_PKT;
	if (!TokenDel_32(tDPH.nSeqNo))				goto 	INVALID_PKT;
	if ( TokenDel_String(tDPH.strName) < 0)		goto	INVALID_PKT;
	if ( TokenDel_String(tDPH.strDescr) < 0)	goto	INVALID_PKT;
	if (!TokenDel_32(tDPH.nAdminID))			goto	INVALID_PKT;
	if (!TokenDel_32(tDPH.nSubAdminLock))		goto	INVALID_PKT;
	if (!TokenDel_32(tDPH.nTargetLock))			goto	INVALID_PKT;
	if (!TokenDel_32(tDPH.nPolicyID))			goto	INVALID_PKT;
	if (!TokenDel_32(tDPH.nUnitID))				goto	INVALID_PKT;
	if (!TokenDel_32(tDPH.nNotifyInfoID))		goto	INVALID_PKT;
	if (!TokenDel_32(tDPH.nExtOption))			goto	INVALID_PKT;
	if (!TokenDel_32(tDPH.nUsedMode))			goto	INVALID_PKT;

	return 1;

INVALID_PKT:
	return 0;
}
//-----------------------------------------------------------------------------------

PVOID MemToken::GetData()
{
    return buf ;
}
//-----------------------------------------------------------------------------------

INT32 MemToken::GetLength()
{
    return pos ;
}
//-----------------------------------------------------------------------------------
 
BOOL MemToken::IsMoreToken()
{
    if(pos == bufLen)
        return FALSE;
    return TRUE;
}
//-----------------------------------------------------------------------------------

PVOID   MemToken::GetRData()
{
	return buf+pos;
}
//-----------------------------------------------------------------------------------

INT32   MemToken::GetRLength()
{
	return bufLen - pos;
}
//-----------------------------------------------------------------------------------

MemToken&	EmptyToken(MemToken& Token)
{
	Token.Clear();
	return Token;
}
//-----------------------------------------------------------------------------------
