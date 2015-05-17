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

#include "hashfactory.h"
#include "parallelsha256.h"
#include "parallelsha256help.h"

uint32_t ParallelSha256::inited = ParallelSha256::initCalc();

#ifdef ARC_x86

void ParallelSha256::calcSse2(void *hashOut, const void *key, uint64_t offset, uint64_t count)
{
	assert(count != 0);
	assert(count % (4 * SHA256_INTERLEAVE_SSE2) == 0);

	__m128i hash[8];

	PARALLEL_SHA256_FUNC_SSE2(SHA256_INTERLEAVE_SSE2)(hash, (const uint32_t*) key, offset, count, _mm_set_epi32(3,2,1,0));

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

void ParallelSha256::calcNorm(void *hashOut, const void *key, uint64_t offset, uint64_t count)
{
	assert(count != 0);
	assert(count % SHA256_INTERLEAVE_NORM == 0);

	uint32_t curHash[8 * SHA256_INTERLEAVE_NORM] = {0};
	uint32_t partialW[9];
	uint32_t key_[8];
	uint32_t offsetHi[SHA256_INTERLEAVE_NORM];
	uint32_t offsetLo[SHA256_INTERLEAVE_NORM];

	key_[0] = ((uint32_t*) key)[0];
	key_[1] = ((uint32_t*) key)[1];
	key_[2] = ((uint32_t*) key)[2];
	key_[3] = ((uint32_t*) key)[3];
	key_[4] = ((uint32_t*) key)[4];
	key_[5] = ((uint32_t*) key)[5];
	key_[6] = ((uint32_t*) key)[6];
	key_[7] = ((uint32_t*) key)[7];

	SHA256_FUNC_INIT_NORM(partialW, key_);

	if (SHA256_INTERLEAVE_NORM >= 1) { offsetLo[0] = (uint32_t) offset + 0; }
	if (SHA256_INTERLEAVE_NORM >= 2) { offsetLo[1] = (uint32_t) offset + 1; }
	if (SHA256_INTERLEAVE_NORM >= 3) { offsetLo[2] = (uint32_t) offset + 2; }
	if (SHA256_INTERLEAVE_NORM >= 4) { offsetLo[3] = (uint32_t) offset + 3; }

	if (SHA256_INTERLEAVE_NORM >= 1) { offsetHi[0] = (uint32_t) ((offset + 0) >> 32); }
	if (SHA256_INTERLEAVE_NORM >= 2) { offsetHi[1] = (uint32_t) ((offset + 1) >> 32); }
	if (SHA256_INTERLEAVE_NORM >= 3) { offsetHi[2] = (uint32_t) ((offset + 2) >> 32); }
	if (SHA256_INTERLEAVE_NORM >= 4) { offsetHi[3] = (uint32_t) ((offset + 3) >> 32); }

	count /= SHA256_INTERLEAVE_NORM;
	while (1)
	{
		SHA256_FUNC_NORM(SHA256_INTERLEAVE_NORM)(curHash, key_, partialW, offsetLo, offsetHi);

		count--;
		if (count == 0)
		{
			break;
		}

		if (SHA256_INTERLEAVE_NORM >= 1) { offsetLo[0] += SHA256_INTERLEAVE_NORM; if (offsetLo[0] < SHA256_INTERLEAVE_NORM) { offsetHi[0]++; } }
		if (SHA256_INTERLEAVE_NORM >= 2) { offsetLo[1] += SHA256_INTERLEAVE_NORM; if (offsetLo[1] < SHA256_INTERLEAVE_NORM) { offsetHi[1]++; } }
		if (SHA256_INTERLEAVE_NORM >= 3) { offsetLo[2] += SHA256_INTERLEAVE_NORM; if (offsetLo[2] < SHA256_INTERLEAVE_NORM) { offsetHi[2]++; } }
		if (SHA256_INTERLEAVE_NORM >= 4) { offsetLo[3] += SHA256_INTERLEAVE_NORM; if (offsetLo[3] < SHA256_INTERLEAVE_NORM) { offsetHi[3]++; } }
	}

	#define COLLAPSE_XOR(i) \
		tmp = curHash[i * SHA256_INTERLEAVE_NORM + 0]; \
		if (SHA256_INTERLEAVE_NORM >= 2) { tmp ^= curHash[i * SHA256_INTERLEAVE_NORM + 1]; } \
		if (SHA256_INTERLEAVE_NORM >= 3) { tmp ^= curHash[i * SHA256_INTERLEAVE_NORM + 2]; } \
		if (SHA256_INTERLEAVE_NORM >= 4) { tmp ^= curHash[i * SHA256_INTERLEAVE_NORM + 3]; } \
		((uint32_t*) hashOut)[i] ^= tmp

	uint32_t tmp;

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

uint32_t ParallelSha256::initCalc()
{
#ifdef ARC_x86
#ifdef __HAS_AVX512__
	if ((getInstructionSets() & (IS_AVX512DQ | IS_OS_ZMM)) == (IS_AVX512DQ | IS_OS_ZMM))
	{
		return HashFactory::registerHash("sha256", QUOTE(SHA256_INTERLEAVE_AVX512) "xAVX512",     ParallelSha256::calcAvx512,  32, 16 * SHA256_INTERLEAVE_AVX512);
	}
	else
#endif
	if ((getInstructionSets() & (IS_AVX2 | IS_OS_YMM | IS_XOP)) == (IS_AVX2 | IS_OS_YMM | IS_XOP))
	{
		return HashFactory::registerHash("sha256", QUOTE(SHA256_INTERLEAVE_AVX2_XOP) "xAVX2_XOP", ParallelSha256::calcAvx2Xop, 32,  8 * SHA256_INTERLEAVE_AVX2_XOP);
	}
	else if ((getInstructionSets() & (IS_AVX2 | IS_OS_YMM)) == (IS_AVX2 | IS_OS_YMM))
	{
		return HashFactory::registerHash("sha256", QUOTE(SHA256_INTERLEAVE_AVX2) "xAVX2",         ParallelSha256::calcAvx2,    32,  8 * SHA256_INTERLEAVE_AVX2);
	}
	else if ((getInstructionSets() & (IS_AVX | IS_XOP)) == (IS_AVX | IS_XOP))
	{
		return HashFactory::registerHash("sha256", QUOTE(SHA256_INTERLEAVE_AVX_XOP) "xAVX_XOP",   ParallelSha256::calcAvxXop,  32,  4 * SHA256_INTERLEAVE_AVX_XOP);
	}
	else if ((getInstructionSets() & IS_AVX) == IS_AVX)
	{
		return HashFactory::registerHash("sha256", QUOTE(SHA256_INTERLEAVE_AVX) "xAVX",           ParallelSha256::calcAvx,     32,  4 * SHA256_INTERLEAVE_AVX);
	}
	else if ((getInstructionSets() & IS_SSE2) == IS_SSE2)
	{
		return HashFactory::registerHash("sha256", QUOTE(SHA256_INTERLEAVE_SSE2) "xSSE2",         ParallelSha256::calcSse2,    32,  4 * SHA256_INTERLEAVE_SSE2);
	}
#endif
	return HashFactory::registerHash("sha256", QUOTE(SHA256_INTERLEAVE_NORM) "xScalar",       ParallelSha256::calcNorm,    32,  1 * SHA256_INTERLEAVE_NORM);
}
