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

#ifndef PARALLEL_SHA256_H
#define PARALLEL_SHA256_H

#include "common.h"

#ifdef ARC_x86
#ifdef __HAS_AVX512__
#define SHA256_INTERLEAVE_AVX512    1
#endif
#define SHA256_INTERLEAVE_AVX2_XOP  1
#define SHA256_INTERLEAVE_AVX2      1
#define SHA256_INTERLEAVE_AVX_XOP   1
#define SHA256_INTERLEAVE_AVX       1
#define SHA256_INTERLEAVE_SSE2      1
#endif
#define SHA256_INTERLEAVE_NORM      1

class ParallelSha256
{
public:
#ifdef ARC_x86
#ifdef __HAS_AVX512__
	static void calcAvx512 (void *workOut, const void *key, uint64_t offset, uint64_t count);
#endif
	static void calcAvx2Xop(void *workOut, const void *key, uint64_t offset, uint64_t count);
	static void calcAvx2   (void *workOut, const void *key, uint64_t offset, uint64_t count);
	static void calcAvxXop (void *workOut, const void *key, uint64_t offset, uint64_t count);
	static void calcAvx    (void *workOut, const void *key, uint64_t offset, uint64_t count);
	static void calcSse2   (void *workOut, const void *key, uint64_t offset, uint64_t count);
#endif
	static void calcNorm   (void *workOut, const void *key, uint64_t offset, uint64_t count);

	static void init       (void *keyOut,  const void *password, size_t passwordLength, const void *salt, size_t saltLength);
	static void finish     (void *hashOut, size_t outLen, const void *work, const void *key);
	static void finishKdf  (void *keyOut,  size_t outLen, const void *work, const void *password, size_t passwordLength);

private:
	ParallelSha256() {}
	static uint32_t initCalc();

	static uint32_t s_inited;
};

#endif
