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
#include "as_seedx.h"

BYTE   g_crypt_key[16];
DWORD  g_round_key[32];


void seed_init(char *key, int key_len)
{
	memset(g_crypt_key, 0x00, sizeof(g_crypt_key));
	memset(g_round_key, 0x00, sizeof(g_round_key));

	memcpy(g_crypt_key, key, key_len);
	SeedEncRoundKey(g_round_key, g_crypt_key);
}


int seed_encrypt_len(int pdata_len)
{
	int  remain;

	if (pdata_len == 0) {
		return 0;
	}

	remain = pdata_len % SeedBlockSize;

	if (remain) {
		pdata_len += (24 - remain);
	} else {
		pdata_len += 8;
	}

	return pdata_len;
}


int seed_encrypt_data(char *pdata, int pdata_len, char **cdata, int *cdata_len)
{
	int   i;
	int   remain;
	int   loop_cnt;
	char  *cdata_first;

	if(pdata == NULL || pdata_len < 1 || cdata == NULL || cdata_len == NULL)
		return -1;

	loop_cnt  = pdata_len / SeedBlockSize;
	remain    = pdata_len % SeedBlockSize;

	if (remain)
	{
		*cdata_len = pdata_len + (24 - remain);
	}
	else
	{
		*cdata_len = pdata_len + 8;
	}

	if (*cdata == NULL)
	{
		*cdata = (char *) malloc(*cdata_len + 1);
	}

	if (*cdata == NULL)
	{
		return -2;
	}
	memset(*cdata, 0x00, *cdata_len + 1);

	cdata_first = *cdata;

	memcpy(*cdata, cdata_len, 4);
	*cdata += 4;

	memcpy(*cdata, &pdata_len, 4);
	*cdata += 4;

	memcpy(*cdata, pdata, pdata_len);

	for (i = 0; i < loop_cnt; i++)
	{
		SeedEncrypt((BYTE *) *cdata, g_round_key);
		*cdata += SeedBlockSize;
	}

	if (remain)
	{
		SeedEncrypt((BYTE *) *cdata, g_round_key);
	}

	*cdata = cdata_first;
	return 0;
}


int seed_decrypt_data(char *cdata, char **pdata, int *pdata_len)
{
	int   i;
	int   remain;
	int   loop_cnt;
	int   cdata_len;
	char  *pdata_first;

	if(cdata == NULL || pdata == NULL || pdata_len == NULL)
		return -1;	

	memcpy(&cdata_len, cdata, 4);
	cdata += 4;

	memcpy(pdata_len, cdata, 4);
	cdata += 4;

	loop_cnt  = *pdata_len / SeedBlockSize;
	remain    = *pdata_len % SeedBlockSize;

	if (*pdata == NULL)
	{
		*pdata = (char *) malloc(cdata_len - 7);
	}

	if (*pdata == NULL)
	{
		return -2;
	}
	memset(*pdata, 0x00, cdata_len - 7);

	memcpy(*pdata, cdata, cdata_len - 8);

	pdata_first = *pdata;

	for (i = 0; i < loop_cnt; i++)
	{
		SeedDecrypt((BYTE *) *pdata, g_round_key);
		*pdata += SeedBlockSize;
	}

	if (remain)
	{
		SeedDecrypt((BYTE *) *pdata, g_round_key);
	}

	*pdata = pdata_first;
	return 0;
}


