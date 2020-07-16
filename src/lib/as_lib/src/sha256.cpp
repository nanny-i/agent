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
#include "as_string.h"
#include "as_sha256.h"


static void sha256_init(SHA256Context *ctx);
static int sha256_update(SHA256Context *ctx, unsigned char *message_array, int length);
static void sha256_process_msg_blk(SHA256Context *ctx);
static void sha256_pad_msg(SHA256Context *ctx);
static int sha256_final_digest(SHA256Context *ctx, unsigned char *digest, int digest_len);


/* 입력된 문자열의 sha256 digest 값을 구함 */
int get_sha256_digest(char *str, int str_len, unsigned char *digest, int digest_len)
{
	int nRetVal = 0;
	SHA256Context  ctx;
	if(str == NULL || str_len < 1 || digest == NULL || digest_len < ASI_SHA256_DIGEST_SIZE)
	{
		return -1;
	}
	memset(digest, 0, digest_len);

	sha256_init(&ctx);
	nRetVal = sha256_update(&ctx, (unsigned char *)str, str_len);
	if(nRetVal != 0)
	{
		nRetVal -= 10;
		return nRetVal;
	}
	nRetVal = sha256_final_digest(&ctx, digest, digest_len);
	if(nRetVal != 0)
	{
		nRetVal -= 20;
		return nRetVal;
	}
	return 0;
}

int get_sha256_hash(char *str, int str_len, char *hash, int hash_len)
{
	int nRetVal = 0;
	unsigned char acDigest[ASI_SHA256_DIGEST_SIZE+1] = {0,};
	SHA256Context ctx;

	if(str == NULL || str_len < 1 || hash == NULL || hash_len < ASI_SHA256_HASH_SIZE+1)
	{
		return -1;
	}
	memset(hash, 0x00, hash_len);
	do{
		sha256_init(&ctx);
		nRetVal = sha256_update(&ctx, (unsigned char *)str, str_len);
		if(nRetVal != 0)
		{
			nRetVal -= 10;
			break;
		}

		nRetVal = sha256_final_digest(&ctx, acDigest, ASI_SHA256_DIGEST_SIZE);
		if(nRetVal != 0)
		{
			nRetVal -= 20;
			break;
		}

		acDigest[ASI_SHA256_DIGEST_SIZE] = 0;

		nRetVal = conv_sha256_digest(acDigest, hash, hash_len);
		if(nRetVal != 0)
		{
			nRetVal -= 30;
			break;
		}
		nRetVal = 0;
	}while(FALSE);
	return nRetVal;
}


/* 특정 파일의 hash 값을 구함 */
int get_sha256_hash_from_file(char *path, char *hash, int hash_len)
{
	FILE *fp = NULL;
	int nRead = 0;
	int nRetVal = 0;
	char acBuf[4096] = { 0,};
	unsigned char acDigest[ASI_SHA256_DIGEST_SIZE+1] = {0,};
	SHA256Context ctx;

	if(path == NULL || hash == NULL || hash_len < ASI_SHA256_HASH_SIZE+1)
	{
		return -1;
	}

	memset(hash, 0x00, hash_len);

	fp = fopen(path, "r");
	if (fp == NULL)
	{
		return -2;
	}
	sha256_init(&ctx);
	while((nRead = fread(acBuf, 1, sizeof(acBuf), fp)) > 0)
	{
		nRetVal = sha256_update(&ctx, (unsigned char *)acBuf, nRead);
		if(nRetVal != 0)
		{
			fclose(fp);
			nRetVal -= 10;
			return nRetVal;
		}
	}

	nRetVal = sha256_final_digest(&ctx, acDigest, ASI_SHA256_DIGEST_SIZE);
	if(nRetVal != 0)
	{
		fclose(fp);
		nRetVal -= 20;
		return nRetVal;
	}

	nRetVal = conv_sha256_digest(acDigest, hash, hash_len);
	if(nRetVal != 0)
	{
		fclose(fp);
		nRetVal -= 30;
		return nRetVal;
	}

	fclose(fp);
	return 0;
}


/* hash1, hash2 digest 값을 비교하여 같으면 0, 틀리면 -1 리턴 */
int comp_sha256_digest(unsigned char *digest1, unsigned char *digest2)
{
	int  idx = 32;

	while (idx)
	{
		idx--;
		if (digest1[idx] == digest2[idx])
		{
			continue;
		}
		return -1;
	}
	return 0;
}


/* 입력된 hash digest를 문자열로 변환 */
int conv_sha256_digest(unsigned char *digest, char *hash, int hash_len)
{
	int i;
	char tmp[4] = {0,};

	if(digest == NULL || hash == NULL || hash_len < ASI_SHA256_HASH_SIZE+1)
	{
		return -1;
	}

	memset(hash, 0x00, hash_len);

	for (i=0; i<ASI_SHA256_DIGEST_SIZE; i++)
	{
		snprintf(tmp, 3, "%02X", digest[i]);
		tmp[3] = 0;
		if(i==0)
			strncpy(hash, tmp, 2);
		else
			strncat(hash, tmp, 2);
	}
	hash[ASI_SHA256_HASH_SIZE] = 0;
	return 0;
}


static void sha256_init(SHA256Context *ctx)
{
	ctx->Length_Low             = 0;
	ctx->Length_High            = 0;
	ctx->Message_Block_Index    = 0;

	ctx->Message_Digest[0]      = 0x6a09e667;
	ctx->Message_Digest[1]      = 0xbb67ae85;
	ctx->Message_Digest[2]      = 0x3c6ef372;
	ctx->Message_Digest[3]      = 0xa54ff53a;
	ctx->Message_Digest[4]      = 0x510e527f;
	ctx->Message_Digest[5]      = 0x9b05688c;
	ctx->Message_Digest[6]      = 0x1f83d9ab;
	ctx->Message_Digest[7]      = 0x5be0cd19;

	ctx->Computed   = 0;
	ctx->Corrupted  = 0;
}


static int sha256_update(SHA256Context *ctx, unsigned char *message_array, int length)
{
	if (ctx == NULL || message_array == NULL || length < 1)
	{
		ctx->Corrupted = 1;
		return -1;
	}

	if (ctx->Computed || ctx->Corrupted)
	{
		ctx->Corrupted = 1;
		return -2;
	}

	while (length-- && !ctx->Corrupted)
	{
		ctx->Message_Block[ctx->Message_Block_Index++] = (*message_array & 0xFF);
		ctx->Length_Low += 8;

		/* Force it to 32 bits */
		ctx->Length_Low &= 0xFFFFFFFF;
		if (ctx->Length_Low == 0)
		{
			ctx->Length_High++;
			/* Force it to 32 bits */
			ctx->Length_High &= 0xFFFFFFFF;
			if (ctx->Length_High == 0)
			{
				/* Message is too long */
				ctx->Corrupted = 1;
				return -3;
			}
		}
		if (ctx->Message_Block_Index == 64)
		{
			sha256_process_msg_blk(ctx);
		}
		message_array++;
	}
	return 0;
}



static void sha256_process_msg_blk(SHA256Context *ctx)
{

	int  t;									/* Loop counter */
	unsigned int  T1,T2;					/* Temporary word value */
	unsigned int  W[80];					/* Word sequence */
	unsigned int  A, B, C, D, E, F, G, H;	/* Word buffers */

	const unsigned int K[]  = {
		0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
		0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
		0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
		0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
		0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
		0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
		0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
		0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
		0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
		0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
		0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
		0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
		0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
		0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
		0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
		0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
	};

	for (t = 0; t < 16; t++) {
		W[t] = ((unsigned int) ctx->Message_Block[t * 4]) << 24;
		W[t] |= ((unsigned int) ctx->Message_Block[t * 4 + 1]) << 16;
		W[t] |= ((unsigned int) ctx->Message_Block[t * 4 + 2]) << 8;
		W[t] |= ((unsigned int) ctx->Message_Block[t * 4 + 3]);
	}

	for (t = 16; t < 64; t++) {
		W[t] = sig1(W[t-2]) + W[t-7] + sig0(W[t-15]) + W[t-16];
	}


	A = ctx->Message_Digest[0];
	B = ctx->Message_Digest[1];
	C = ctx->Message_Digest[2];
	D = ctx->Message_Digest[3];
	E = ctx->Message_Digest[4];
	F = ctx->Message_Digest[5];
	G = ctx->Message_Digest[6];
	H = ctx->Message_Digest[7];

	for (t = 0; t < 64; t++) {
		T1 = H + SIG1(E) + Ch(E,F,G) + K[t] + W[t];
		T2 = SIG0(A) + Maj(A,B,C);
		H = G;
		G = F;
		F = E;
		E = D + T1;
		D = C;
		C = B;
		B = A;
		A = T1 + T2;
	}

	ctx->Message_Digest[0] = (ctx->Message_Digest[0] + A) & 0xFFFFFFFF;
	ctx->Message_Digest[1] = (ctx->Message_Digest[1] + B) & 0xFFFFFFFF;
	ctx->Message_Digest[2] = (ctx->Message_Digest[2] + C) & 0xFFFFFFFF;
	ctx->Message_Digest[3] = (ctx->Message_Digest[3] + D) & 0xFFFFFFFF;
	ctx->Message_Digest[4] = (ctx->Message_Digest[4] + E) & 0xFFFFFFFF;
	ctx->Message_Digest[5] = (ctx->Message_Digest[5] + F) & 0xFFFFFFFF;
	ctx->Message_Digest[6] = (ctx->Message_Digest[6] + G) & 0xFFFFFFFF;
	ctx->Message_Digest[7] = (ctx->Message_Digest[7] + H) & 0xFFFFFFFF;

	ctx->Message_Block_Index = 0;
}


static void sha256_pad_msg(SHA256Context *ctx)
{
	if (ctx->Message_Block_Index > 55) {
		ctx->Message_Block[ctx->Message_Block_Index++] = 0x80;
		while(ctx->Message_Block_Index < 64) {
			ctx->Message_Block[ctx->Message_Block_Index++] = 0;
		}

		sha256_process_msg_blk(ctx);
		while(ctx->Message_Block_Index < 56) {
			ctx->Message_Block[ctx->Message_Block_Index++] = 0;
		}

	} else {

		ctx->Message_Block[ctx->Message_Block_Index++] = 0x80;
		while(ctx->Message_Block_Index < 56) {
			ctx->Message_Block[ctx->Message_Block_Index++] = 0;
		}
	}

	ctx->Message_Block[56] = (ctx->Length_High >> 24) & 0xFF;
	ctx->Message_Block[57] = (ctx->Length_High >> 16) & 0xFF;
	ctx->Message_Block[58] = (ctx->Length_High >> 8) & 0xFF;
	ctx->Message_Block[59] = (ctx->Length_High) & 0xFF;
	ctx->Message_Block[60] = (ctx->Length_Low >> 24) & 0xFF;
	ctx->Message_Block[61] = (ctx->Length_Low >> 16) & 0xFF;
	ctx->Message_Block[62] = (ctx->Length_Low >> 8) & 0xFF;
	ctx->Message_Block[63] = (ctx->Length_Low) & 0xFF;

	sha256_process_msg_blk(ctx);
}


static int sha256_final_digest(SHA256Context *ctx, unsigned char *digest, int digest_len)
{
	if(ctx == NULL || digest == NULL || digest_len < 1)
	{
		return -1;
	}
	if (ctx->Corrupted)
	{
		return -2;
	}
	if (!ctx->Computed)
	{
		sha256_pad_msg(ctx);
		ctx->Computed = 1;
	}

	memcpy(digest, ctx->Message_Digest, digest_len);
	return 0;
}
