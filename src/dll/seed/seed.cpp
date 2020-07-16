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
#include "seed.h"
#include "SeedUtil.h"
#include "Seedx.h"

CSeedUtil* g_pSeed = NULL;

void __attribute__ ((constructor)) seed_init(void)
{
	g_pSeed = new CSeedUtil();
}

void __attribute__ ((destructor)) seed_fini(void)
{	
	if(g_pSeed)
		delete g_pSeed;
}

INT32 Set_Key(BYTE* lpKey)
{
	if(!g_pSeed)
		g_pSeed = new CSeedUtil();
	//vc_seed_init((char*)lpKey, 16);
	g_pSeed->Set_Key(lpKey, 16);

	return 0;
}

INT32 Make_Key(BYTE* lpKey)
{
    if(!g_pSeed)
        g_pSeed = new CSeedUtil();

	g_pSeed->Make_Key(lpKey);

	return 0;
}

INT32 Encrypt_Data(BYTE* lpData, INT32 nLen, BYTE** lpOutBuf, INT32& nOutLen)
{
    if(!g_pSeed)
        g_pSeed = new CSeedUtil();
	return g_pSeed->Encrypt_Data(lpData, nLen, lpOutBuf, (UINT32&)nOutLen);
}

INT32 Decrypt_Data(BYTE* lpData, BYTE** lpOutBuf, INT32& nOutLen)
{
    if(!g_pSeed)
        g_pSeed = new CSeedUtil();

	return g_pSeed->Decrypt_Data(lpData, lpOutBuf, (UINT32&)nOutLen);
}

INT32 Free_Buffer(BYTE* lpBuff)
{
	if(g_pSeed)
	{
		g_pSeed->FreeBuffer(lpBuff);
	}

	return 0;
}
