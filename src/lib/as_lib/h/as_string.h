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

#ifndef _AS_STRING_H_
#define _AS_STRING_H_

extern char *strndup(char *str, int len);
extern int strlcat(char *dst, char *src, int siz);
extern void replace_char_in_str(char *str, char s, char d);
extern void remove_char_in_str(String &strRemove, char cRem);
extern LPSTR DelLastChar(String& strInput, char cDelChar);
extern int count_rule_data(char *pString, char cDelimiter, int *pnCount);
extern String SPrintf(const char* fmt,...);
extern StringW	WPrintf(const wchar_t* fmt,...);
extern int count_rule_data(char *pString, char cDelimiter, int *pnCount);
extern String _strlwr(const char *str);
extern LPTSTR FormatString(LPTSTR lpBuf, LPTSTR fmt,...);
extern void ReverseLPTSTR(LPTSTR lpInput);
extern String ConvertAnsiString(StringW strInputW);
extern StringW ConvertWideString(String strInput);
extern String ReverseStr(String strInput);
extern LPTSTR ConvertLPTSTR(String& strValue);
extern String&	EmptyStr(String& strValue);
extern LPTSTR FindReverChar(LPCTSTR lpSrc, CHAR chFind);
extern CHAR GetToken(String& strValue, CHAR chDefTok, CHAR chFindTok);
extern String ConvertIP(UINT32 nIP);
extern UINT32 ConvertHost(LPCTSTR lpAddress);
extern String ConvertDateTime(UINT32 nTime, UINT32 nFormat);
extern INT32 StrMatchSpec(LPCTSTR pszTarget, LPCTSTR pszSpec);
extern LPTSTR strcat_ext(LPTSTR lpTarget, LPCTSTR lpSource, UINT32 nTarSize);
extern UINT32 strlen_ext(LPCTSTR lpValue);
extern void	sprintf_ext(UINT32 nTarSize, char *lpTarget, const char *fmt,...);
extern String QueryToMem(String& strValue);
extern String MemToQuery(String strValue);
extern String PathUnixToWin(String& strValue);
extern String PathWinToUnix(String strValue);




#endif /* _AS_STRING_H_ */


