/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Steve Thomas <steve AT tobtu DOT com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "parallelsha256.h"
#include "parallelsha256help.h"

// ***********************
// **** Compile flags ****
// ***********************
// Intel: icl /QxAVX
//        icc -xAVX
// MSVS:  /arch:AVX
// GCC:   -mavx

#ifdef ARC_x86

#ifndef _MSC_VER
union mem128
{
	__m128i  vec;
	uint32_t m128i_u32[4];
};
#endif

void ParallelSha256::calcAvx(void *hashOut, const void *key, uint64_t offset, uint64_t count)
{
	assert(count != 0);
	assert(count % (4 * SHA256_INTERLEAVE_AVX) == 0);

#ifdef _MSC_VER
	__m128i hash[8];

	PARALLEL_SHA256_FUNC_AVX(SHA256_INTERLEAVE_AVX)(hash, (const uint32_t*) key, offset, count, _mm_set_epi32(3,2,1,0));
#else
	mem128  hash[8];

	PARALLEL_SHA256_FUNC_AVX(SHA256_INTERLEAVE_AVX)(&(hash->vec), (const uint32_t*) key, offset, count, _mm_set_epi32(3,2,1,0));
#endif

	#define COLLAPSE_XOR(i) \
		((uint32_t*) hashOut)[i] = hash[i].m128i_u32[0] ^ hash[i].m128i_u32[1] ^ hash[i].m128i_u32[2] ^ hash[i].m128i_u32[3]

	COLLAPSE_XOR(0);
	COLLAPSE_XOR(1);
	COLLAPSE_XOR(2);
	COLLAPSE_XOR(3);
	COLLAPSE_XOR(4);
	COLLAPSE_XOR(5);
	COLLAPSE_XOR(6);
	COLLAPSE_XOR(7);

	#undef COLLAPSE_XOR
}

#endif
