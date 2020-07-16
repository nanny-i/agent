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

#ifndef _AS_SYSINFO_H_
#define _AS_SYSINFO_H_

#define SYS_DMI_PATH		"/sys/class/dmi/id/"
#define LINUX_UBUNTU_NAME 	"Ubuntu"


#define PATH_MAX_PARTS   	32
#define PATH_SEP_LENGTH		1


extern int get_cpu_core_num();
extern int get_cpu_type(char *cpu_type, int len);
extern int get_cpu_speed();
extern int get_bios_date(char *pcBiosDate, int nMaxLen);
extern int get_total_mem();
extern int get_total_disk_size();
extern int get_netiface_count();
extern int get_system_name(char *acSystemName, int nMaxLen);
extern void get_os_info(char *acOsName, int nMaxLen, UINT64 *pddwOsID, UINT32 *pdwOsType);



#endif /* _AS_SYSINFO_H_ */


