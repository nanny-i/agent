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

#ifndef _ASI_SQLITE_UTIL_SDK__
#define _ASI_SQLITE_UTIL_SDK__

extern "C" {
	int init_sqlite(char *pcLogMsg=NULL);
	void free_sqlite();
	int open_database(char *pcDBName, char *pcLogMsg=NULL);
	int create_database(char *pcDBName, char *pcLogMsg=NULL);
	int close_database(char *pcLogMsg=NULL);
	int query_execute(char *pcQuery, char *pcLogMsg=NULL);
	int is_table_exist(char *pcQuery, char *pcLogMsg=NULL);
	int query_next(char *pcLogMsg=NULL);
	int get_field_count();
	int get_field_type(int nIndex);
	int get_field_int(int nIndex);
	char *get_field_string(int nIndex);
	float get_field_float(int nIndex);
	int get_field_bytes(int nIndex);
	char *get_field_blob(int nIndex);
}

#endif /*_ASI_SQLITE_UTIL_SDK__*/
