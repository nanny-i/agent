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

#ifndef _AS_FILE_H_
#define _AS_FILE_H_

#define ASI_FLOCK_RETRY_MAX			10000
#define ASI_FLOCK_FMODE				0600

#define MBYTES	1048576
#define KBYTES	1024

#define RULE_SEP	'|'


extern int flock(LPCSTR pcPath);
extern void free_flock(int fd);
extern char *fgets_data_file(char *szString, int nCount, FILE *fp);
extern char *fgets_query_file(char *szString, int nCount, FILE *fp);
extern char *fgets_data_file_v1(char *szString, int nCount, FILE *fp);
extern int GetFileSize(int nFd, UINT32 *pdwFileLen);
extern int get_file_size(LPCSTR pcPath, UINT32 *pdwFileLen, UINT32 *pdwFileMode = NULL);
extern int is_file(LPCSTR pcPath);

extern BOOL ForceDirectories(LPCSTR pcDir, char *acLogMsg = NULL);
extern BOOL DirectoryExists(LPCSTR pcDirectory);
extern BOOL CreateDirectory(LPCSTR lpPathName, void* lpParam);
extern BOOL CopyFile(LPCSTR pszSrcFile, LPCSTR pszDstFile, BOOL bFailIfExists);
extern void MoveFileEx(LPCSTR szSourceFile, LPCSTR szTargetFile);
extern HMODULE LoadLibrary(LPCTSTR lpFileName);
extern void* GetProcAddress(HMODULE hModule, LPCTSTR lpProcName);
extern void FreeLibrary(HMODULE hModule);



#endif /* _AS_FILE_H_ */


