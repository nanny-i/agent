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

#ifndef _AS_SHA256_H_
#define _AS_SHA256_H_

#define ASI_SHA256_ENCODE_TO_STRING		1
#define ASI_SHA256_ENCODE_TO_FILE		2

#ifndef ASI_SHA256_DIGEST_SIZE
#define ASI_SHA256_DIGEST_SIZE			32
#endif

#ifndef ASI_SHA256_HASH_SIZE
#define ASI_SHA256_HASH_SIZE			64
#endif	

#define SHA256CircularShift(bits,word) \
	((((word) << (bits)) & 0xFFFFFFFF) | \
	 ((word) >> (32-(bits))))

#ifndef min
#define min( x, y ) ( ( x ) < ( y ) ? ( x ) : ( y ) ) 
#endif

#define S(x,n) ( ((x)>>(n)) | ((x)<<(32-(n))) ) 
#define R(x,n) ( (x)>>(n) ) 

#define Ch(x,y,z) ( ((x) & (y)) | (~(x) & (z)) ) 
#define Maj(x,y,z) ( ( (x) & (y) ) | ( (x) & (z) ) | ( (y) & (z) ) ) 

#define SIG0(x) ( S(x, 2) ^ S(x,13) ^ S(x,22) ) 
#define SIG1(x) ( S(x, 6) ^ S(x,11) ^ S(x,25) ) 
#define sig0(x) ( S(x, 7) ^ S(x,18) ^ R(x, 3) ) 
#define sig1(x) ( S(x,17) ^ S(x,19) ^ R(x,10) ) 


/* 
 * This structure will hold context information for the hashing
 * operation
 */
typedef struct SHA256Context
{
	unsigned int Message_Digest[8];		/* Message Digest (output) */

	unsigned int Length_Low;			/* Message length in bits */
	unsigned int Length_High;			/* Message length in bits */

	unsigned char Message_Block[ASI_SHA256_HASH_SIZE];	/* 512-bit message blocks */
	int Message_Block_Index;			/* Index into message block array */

	int Computed;						/* Is the digest computed? */
	int Corrupted;						/* Is the message digest corruped? */
} SHA256Context;


extern int get_sha256_digest(char *str, int str_len, unsigned char *digest, int digest_len);
extern int get_sha256_hash(char *str, int str_len, char *hash, int hash_len);
extern int get_sha256_hash_from_file(char *path, char *hash, int hash_len);
extern int comp_sha256_digest(unsigned char *digest1, unsigned char *digest2);
extern int conv_sha256_digest(unsigned char *digest, char *hash, int hash_len);


#endif /* _AS_SHA256_H_ */


