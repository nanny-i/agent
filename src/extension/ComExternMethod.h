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


#ifndef COM_GLOBAL_EXTERN_METHOD_H_15BE18C4_D543_413E_96F8_61C24AD45984
#define COM_GLOBAL_EXTERN_METHOD_H_15BE18C4_D543_413E_96F8_61C24AD45984

INT32			HexToMap(String strHexValue, TMapID& tValueMap, INT32 nMaxLen);
INT32			MapToHex(TMapID& tValueMap, String& strHexValue, INT32 nMaxLen);
INT32			HexToMap_64(String strHexValue, TMapID64& tValueMap, INT32 nMaxLen);
INT32			MapToHex_64(TMapID64& tValueMap, String& strHexValue, INT32 nMaxLen);

String			MapStrToStr(TMapStr& tStrMap, CHAR chCellTok = '/', CHAR chBlockTok = '|');
INT32			StrToMapStr(String strMapList, TMapStr& tStrMap, CHAR chCellTok = '/', CHAR chBlockTok = '|');

String			MapID_StrToStr(TMapIDStr& tIDMapStr, CHAR chCellTok = '/', CHAR chBlockTok = '|');
INT32			StrToMapID_Str(String strMapList, TMapIDStr& tIDMapStr, CHAR chCellTok = '/', CHAR chBlockTok = '|');

INT32			MaptoMapStr_64(TMapID64& tIDMap, TMapStr& tStrMap);
INT32			MapStrToMap_64(TMapStr& tStrMap, TMapID64& tIDMap);

INT32			CheckDumpFile(String &strPath, INT32 nRestDumpCount = 3);

INT32			RemoveDumpFiles();
INT32			RemoveSdeltemp();
INT32			RemoveInvenFiles();
void			DeletePrefixFiles(String strPath, LPCTSTR lpszPrefixed);

void			WriteLogA(char* fmt,...);


#endif //COM_GLOBAL_EXTERN_METHOD_H_15BE18C4_D543_413E_96F8_61C24AD45984