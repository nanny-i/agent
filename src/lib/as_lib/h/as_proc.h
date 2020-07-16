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

#ifndef _AS_PROC_H_
#define _AS_PROC_H_


#define ASI_PROC_EXIST				1
#define ASI_PROC_NOT_EXIST			2


struct proc_info {
	pid_t	ppid;
	char	name[MAX_PROC_PATH];
};
typedef struct proc_info proc_info_t;


extern int get_proc_info_by_pid(int pid, proc_info_t *pProcInfo);

extern int check_proc_exist_by_pid_file(const char *acPidPath, const char *acProcName);

extern int check_proc_exist_by_name(const char *acProcName, int nExceptPid);

extern int make_pid_file(const char *acPidPath, const char *acProcName, pid_t pid);


#endif /* _AS_PROC_H_ */


