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

#ifndef _FILE_INFO_H__
#define _FILE_INFO_H__


extern "C"{

INT32 ASIFI_GetFileDescription(char *pcFileName, char *pcFileDescr, INT32 nLength);
INT32 ASIFI_GetFileVersion(char *pcFileName, char *pcFileVersion, INT32 nLength);
INT32 ASIFI_GetFileSpecialValue(char *pcFileName, char *pcFileKey, char *pcFileValue, INT32 nLength);
INT32 ASIFI_GetFileLanguage(char *pcFileName, INT32& nLanguageType);
INT32 ASIFI_GetFileElfMagic(char *pcFileName, INT32& nElfMagic);
INT32	ASIFI_GetFileElfType(char *pcFileName, INT32& nElfType);

}

#endif /*_FILE_INFO_H__*/