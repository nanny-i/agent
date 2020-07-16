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

#ifndef _AS_SEED_H_
#define _AS_SEED_H_


extern void seed_init(char *key, int key_len);
extern int seed_encrypt_len(int pdata_len);
extern int seed_encrypt_data(char *pdata, int pdata_len, char **cdata, int *cdata_len);
extern int seed_decrypt_data(char *cdata, char **pdata, int *pdata_len);


#endif /* _AS_SEED_H_ */


