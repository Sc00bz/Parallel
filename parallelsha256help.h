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

#ifndef PARALLEL_SHA256_HELP_H
#define PARALLEL_SHA256_HELP_H

#include "common.h"

#ifndef ARC_x86
	// Non-x86... Yeah I got nothing
#else

#ifdef _WIN32
#ifdef __HAS_AVX512__
	#include <zmmintrin.h> // AVX512
#endif
	#include <immintrin.h> // AVX2 and older
	#include <ammintrin.h> // XOP
#else
	#include <x86intrin.h>
#endif

#define SHA256_FUNC_INIT_NORM        sha256FuncBroadcastInit
#define SHA256_FUNC_INIT_SSE2        sha256FuncInit         <__m128i, sha256Add128, sha2DoubleXor128, sha256Set128, sha256Rotr128,    sha256ShiftR128>
#define SHA256_FUNC_INIT_AVX         sha256FuncInit         <__m128i, sha256Add128, sha2DoubleXor128, sha256Set128, sha256Rotr128,    sha256ShiftR128>
#define SHA256_FUNC_INIT_AVX_B       sha256FuncBroadcastInit
#define SHA256_FUNC_INIT_AVX_XOP     sha256FuncInit         <__m128i, sha256Add128, sha2DoubleXor128, sha256Set128, sha256Rotr128XOP, sha256ShiftR128>
#define SHA256_FUNC_INIT_AVX_XOP_B   sha256FuncBroadcastInit
#define SHA256_FUNC_INIT_AVX2        sha256FuncInit         <__m256i, sha256Add256, sha2DoubleXor256, sha256Set256, sha256Rotr256,    sha256ShiftR256>
#define SHA256_FUNC_INIT_AVX2_B      sha256FuncBroadcastInit
#define SHA256_FUNC_INIT_AVX2_XOP    sha256FuncInit         <__m256i, sha256Add256, sha2DoubleXor256, sha256Set256, sha256Rotr256,    sha256ShiftR256>
#define SHA256_FUNC_INIT_AVX2_XOP_B  sha256FuncBroadcastInit
#ifdef __HAS_AVX512__
#define SHA256_FUNC_INIT_AVX512      sha256FuncInit         <__m512i, sha256Add512, sha2DoubleXor512, sha256Set512, sha256Rotr512,    sha256ShiftR512>
#define SHA256_FUNC_INIT_AVX512_B    sha256FuncBroadcastInit
#endif

#define SHA256_FUNC_NORM(INTERLEAVE)        sha256Func         <uint32_t, sha256Add32,  sha2Xor32,  sha2DoubleXor32,  sha2Ch32,     sha2Maj32,  sha256Set32,  sha256Rotr32,     sha256ShiftR32,  INTERLEAVE>
#define SHA256_FUNC_SSE2(INTERLEAVE)        sha256Func         <__m128i,  sha256Add128, sha2Xor128, sha2DoubleXor128, sha2Ch128,    sha2Maj128, sha256Set128, sha256Rotr128,    sha256ShiftR128, INTERLEAVE>
#define SHA256_FUNC_AVX(INTERLEAVE)         sha256Func         <__m128i,  sha256Add128, sha2Xor128, sha2DoubleXor128, sha2Ch128,    sha2Maj128, sha256Set128, sha256Rotr128,    sha256ShiftR128, INTERLEAVE>
#define SHA256_FUNC_AVX_B(INTERLEAVE)       sha256FuncBroadcast<__m128i,  sha256Add128, sha2Xor128, sha2DoubleXor128, sha2Ch128,    sha2Maj128, sha256Set128, sha256Rotr128,    sha256ShiftR128, INTERLEAVE>
#define SHA256_FUNC_AVX_XOP(INTERLEAVE)     sha256Func         <__m128i,  sha256Add128, sha2Xor128, sha2DoubleXor128, sha2Ch128Xop, sha2Maj128, sha256Set128, sha256Rotr128XOP, sha256ShiftR128, INTERLEAVE>
#define SHA256_FUNC_AVX_XOP_B(INTERLEAVE)   sha256FuncBroadcast<__m128i,  sha256Add128, sha2Xor128, sha2DoubleXor128, sha2Ch128Xop, sha2Maj128, sha256Set128, sha256Rotr128XOP, sha256ShiftR128, INTERLEAVE>
#define SHA256_FUNC_AVX2(INTERLEAVE)        sha256Func         <__m256i,  sha256Add256, sha2Xor256, sha2DoubleXor256, sha2Ch256,    sha2Maj256, sha256Set256, sha256Rotr256,    sha256ShiftR256, INTERLEAVE>
#define SHA256_FUNC_AVX2_B(INTERLEAVE)      sha256FuncBroadcast<__m256i,  sha256Add256, sha2Xor256, sha2DoubleXor256, sha2Ch256,    sha2Maj256, sha256Set256, sha256Rotr256,    sha256ShiftR256, INTERLEAVE>
#define SHA256_FUNC_AVX2_XOP(INTERLEAVE)    sha256Func         <__m256i,  sha256Add256, sha2Xor256, sha2DoubleXor256, sha2Ch256Xop, sha2Maj256, sha256Set256, sha256Rotr256,    sha256ShiftR256, INTERLEAVE>
#define SHA256_FUNC_AVX2_XOP_B(INTERLEAVE)  sha256FuncBroadcast<__m256i,  sha256Add256, sha2Xor256, sha2DoubleXor256, sha2Ch256Xop, sha2Maj256, sha256Set256, sha256Rotr256,    sha256ShiftR256, INTERLEAVE>
#ifdef __HAS_AVX512__
#define SHA256_FUNC_AVX512(INTERLEAVE)      sha256Func         <__m512i, sha256Add512, sha2Xor512, sha2DoubleXor512, sha2Ch512,    sha2Maj512, sha256Set512, sha256Rotr512,     sha256ShiftR512, INTERLEAVE>
#define SHA256_FUNC_AVX512_B(INTERLEAVE)    sha256FuncBroadcast<__m512i, sha256Add512, sha2Xor512, sha2DoubleXor512, sha2Ch512,    sha2Maj512, sha256Set512, sha256Rotr512,     sha256ShiftR512, INTERLEAVE>
#endif

#define PARALLEL_SHA256_FUNC_SSE2(INTERLEAVE)        parallelSha256Func         <__m128i, sha256Add128, sha256Sub128, sha256CmpGt128, sha2Xor128, sha256Set128, SHA256_FUNC_INIT_SSE2,       SHA256_FUNC_SSE2(INTERLEAVE),        4, INTERLEAVE>
#define PARALLEL_SHA256_FUNC_AVX(INTERLEAVE)         parallelSha256Func         <__m128i, sha256Add128, sha256Sub128, sha256CmpGt128, sha2Xor128, sha256Set128, SHA256_FUNC_INIT_AVX,        SHA256_FUNC_AVX(INTERLEAVE),         4, INTERLEAVE>
#define PARALLEL_SHA256_FUNC_AVX_B(INTERLEAVE)       parallelSha256FuncBroadcast<__m128i, sha256Add128, sha256Sub128, sha256CmpGt128, sha2Xor128, sha256Set128, SHA256_FUNC_INIT_AVX_B,      SHA256_FUNC_AVX_B(INTERLEAVE),       4, INTERLEAVE>
#define PARALLEL_SHA256_FUNC_AVX_XOP(INTERLEAVE)     parallelSha256Func         <__m128i, sha256Add128, sha256Sub128, sha256CmpGt128, sha2Xor128, sha256Set128, SHA256_FUNC_INIT_AVX_XOP,    SHA256_FUNC_AVX_XOP(INTERLEAVE),     4, INTERLEAVE>
#define PARALLEL_SHA256_FUNC_AVX_XOP_B(INTERLEAVE)   parallelSha256FuncBroadcast<__m128i, sha256Add128, sha256Sub128, sha256CmpGt128, sha2Xor128, sha256Set128, SHA256_FUNC_INIT_AVX_XOP_B,  SHA256_FUNC_AVX_XOP_B(INTERLEAVE),   4, INTERLEAVE>
#define PARALLEL_SHA256_FUNC_AVX2(INTERLEAVE)        parallelSha256Func         <__m256i, sha256Add256, sha256Sub256, sha256CmpGt256, sha2Xor256, sha256Set256, SHA256_FUNC_INIT_AVX2,       SHA256_FUNC_AVX2(INTERLEAVE),        8, INTERLEAVE>
#define PARALLEL_SHA256_FUNC_AVX2_B(INTERLEAVE)      parallelSha256FuncBroadcast<__m256i, sha256Add256, sha256Sub256, sha256CmpGt256, sha2Xor256, sha256Set256, SHA256_FUNC_INIT_AVX2_B,     SHA256_FUNC_AVX2_B(INTERLEAVE),      8, INTERLEAVE>
#define PARALLEL_SHA256_FUNC_AVX2_XOP(INTERLEAVE)    parallelSha256Func         <__m256i, sha256Add256, sha256Sub256, sha256CmpGt256, sha2Xor256, sha256Set256, SHA256_FUNC_INIT_AVX2_XOP,   SHA256_FUNC_AVX2_XOP(INTERLEAVE),    8, INTERLEAVE>
#define PARALLEL_SHA256_FUNC_AVX2_XOP_B(INTERLEAVE)  parallelSha256FuncBroadcast<__m256i, sha256Add256, sha256Sub256, sha256CmpGt256, sha2Xor256, sha256Set256, SHA256_FUNC_INIT_AVX2_XOP_B, SHA256_FUNC_AVX2_XOP_B(INTERLEAVE),  8, INTERLEAVE>
#ifdef __HAS_AVX512__
#define PARALLEL_SHA256_FUNC_AVX512(INTERLEAVE)      parallelSha256Func         <__m512i, sha256Add512, sha256Sub512, sha256CmpGt512, sha2Xor512, sha256Set512, SHA256_FUNC_INIT_AVX512,     SHA256_FUNC_AVX512(INTERLEAVE),     16, INTERLEAVE>
#define PARALLEL_SHA256_FUNC_AVX512_B(INTERLEAVE)    parallelSha256FuncBroadcast<__m512i, sha256Add512, sha256Sub512, sha256CmpGt512, sha2Xor512, sha256Set512, SHA256_FUNC_INIT_AVX512_B,   SHA256_FUNC_AVX512_B(INTERLEAVE),   16, INTERLEAVE>
#endif

__inline__ uint32_t sha256Add32 (uint32_t a, uint32_t b) { return a + b; }
__inline__ __m128i  sha256Add128(__m128i  a, __m128i  b) { return    _mm_add_epi32(a, b); }
__inline__ __m256i  sha256Add256(__m256i  a, __m256i  b) { return _mm256_add_epi32(a, b); }

__inline__ __m128i  sha256Sub128(__m128i  a, __m128i  b) { return    _mm_sub_epi32(a, b); }
__inline__ __m256i  sha256Sub256(__m256i  a, __m256i  b) { return _mm256_sub_epi32(a, b); }

__inline__ __m128i  sha256CmpGt128(__m128i  a, __m128i  b) { return    _mm_cmpgt_epi32(a, b); }
__inline__ __m256i  sha256CmpGt256(__m256i  a, __m256i  b) { return _mm256_cmpgt_epi32(a, b); }

__inline__ uint32_t sha2Xor32 (uint32_t a, uint32_t b) { return a ^ b; }
__inline__ __m128i  sha2Xor128(__m128i  a, __m128i  b) { return    _mm_xor_si128(a, b); }
__inline__ __m256i  sha2Xor256(__m256i  a, __m256i  b) { return _mm256_xor_si256(a, b); }

__inline__ uint32_t sha256Set32 (int a) { return a; }
__inline__ __m128i  sha256Set128(int a) { return    _mm_set1_epi32(a); }
__inline__ __m256i  sha256Set256(int a) { return _mm256_set1_epi32(a); }

__inline__ uint32_t sha256ShiftR32 (uint32_t a, int s) { return a >> s; }
__inline__ __m128i  sha256ShiftR128(__m128i  a, int s) { return    _mm_srli_epi32(a, s); }
__inline__ __m256i  sha256ShiftR256(__m256i  a, int s) { return _mm256_srli_epi32(a, s); }

// CH: (e & f) ^ (~e & g)
__inline__ uint32_t sha2Ch32    (uint32_t e, uint32_t f, uint32_t g) { return (e & f) ^ ((~e) & g); }
__inline__ __m128i  sha2Ch128   (__m128i  e, __m128i  f, __m128i  g) { return    _mm_xor_si128(   _mm_and_si128(e, f),    _mm_andnot_si128(e, g)); }
__inline__ __m256i  sha2Ch256   (__m256i  e, __m256i  f, __m256i  g) { return _mm256_xor_si256(_mm256_and_si256(e, f), _mm256_andnot_si256(e, g)); }
__inline__ __m128i  sha2Ch128Xop(__m128i  e, __m128i  f, __m128i  g) { return    _mm_cmov_si128(f, g, e); }
__inline__ __m256i  sha2Ch256Xop(__m256i  e, __m256i  f, __m256i  g) { return _mm256_cmov_si256(f, g, e); }

// MAJ: a ^ ((a ^ b) & (a ^ c)) or (a & b) ^ (a & c) ^ (b & c)
__inline__ uint32_t sha2Maj32    (uint32_t a, uint32_t b, uint32_t c) { return a ^ ((a ^ b) & (a ^ c)); }
__inline__ __m128i  sha2Maj128   (__m128i  a, __m128i  b, __m128i  c) { return    _mm_xor_si128(a,    _mm_and_si128(   _mm_xor_si128(a, b),    _mm_xor_si128(a, c))); }
__inline__ __m256i  sha2Maj256   (__m256i  a, __m256i  b, __m256i  c) { return _mm256_xor_si256(a, _mm256_and_si256(_mm256_xor_si256(a, b), _mm256_xor_si256(a, c))); }
__inline__ __m128i  sha2Maj128Xop(__m128i  a, __m128i  b, __m128i  c) { return    _mm_cmov_si128(a, b,    _mm_xor_si128(b, c)); }
__inline__ __m256i  sha2Maj256Xop(__m256i  a, __m256i  b, __m256i  c) { return _mm256_cmov_si256(a, b, _mm256_xor_si256(b, c)); }

__inline__ uint32_t sha2DoubleXor32 (uint32_t a, uint32_t b, uint32_t c) { return a ^ b ^ c; }
__inline__ __m128i  sha2DoubleXor128(__m128i  a, __m128i  b, __m128i  c) { return    _mm_xor_si128(a,    _mm_xor_si128(b, c)); }
__inline__ __m256i  sha2DoubleXor256(__m256i  a, __m256i  b, __m256i  c) { return _mm256_xor_si256(a, _mm256_xor_si256(b, c)); }

__inline__ uint32_t sha256Rotr32    (uint32_t a, int s) { return (a >> s) | (a << (32 - s)); }
__inline__ __m128i  sha256Rotr128   (__m128i  a, int s) { return    _mm_or_si128(   _mm_srli_epi32(a, s),    _mm_slli_epi32(a, (32 - s))); }
__inline__ __m256i  sha256Rotr256   (__m256i  a, int s) { return _mm256_or_si256(_mm256_srli_epi32(a, s), _mm256_slli_epi32(a, (32 - s))); }
__inline__ __m128i  sha256Rotr128XOP(__m128i  a, int s) { return _mm_roti_epi32(a, 32 - s); }

#ifdef __HAS_AVX512__
#define LUT_A 0xf0
#define LUT_B 0xcc
#define LUT_C 0xaa

__inline__ __m512i sha256Add512   (__m512i a, __m512i b) { return _mm512_add_epi32  (a, b); }
__inline__ __m512i sha256Sub512   (__m512i a, __m512i b) { return _mm512_sub_epi32  (a, b); }
__inline__ __m256i sha256CmpGt256 (__m512i a, __m512i b) { return _mm512_cmpgt_epi32(a, b); }
__inline__ __m512i sha256Set512   (int     a)            { return _mm512_set1_epi32 (a   ); }
__inline__ __m512i sha256ShiftR512(__m512i a, int s)     { return _mm512_srli_epi32 (a, s); }
__inline__ __m512i sha2Xor512     (__m512i a, __m512i b) { return _mm512_xor_si512  (a, b); }
__inline__ __m512i sha256Rotr512  (__m512i a, int s)     { return _mm512_ror_epi32  (a, s); }

__inline__ __m512i sha2Ch512       (__m512i e, __m512i f, __m512i g) { return _mm512_ternarylogic_epi32(e, f, g, ((LUT_A & LUT_B) ^ (~LUT_A & LUT_C))                  & 0xff); }
__inline__ __m512i sha2Maj512      (__m512i a, __m512i b, __m512i c) { return _mm512_ternarylogic_epi32(a, b, c, ((LUT_A & LUT_B) ^ (LUT_A & LUT_C) ^ (LUT_B & LUT_C)) & 0xff); }
__inline__ __m512i sha2DoubleXor512(__m512i a, __m512i b, __m512i c) { return _mm512_ternarylogic_epi32(a, b, c, (LUT_A ^ LUT_B ^ LUT_C)                               & 0xff); }

#undef LUT_A
#undef LUT_B
#undef LUT_C
#endif

#define SHA256_STEP_(a,b,c,d,e,f,g,h,x,k,i,j) \
		h[j] = \
			ADD32(ADD32(ADD32(ADD32( \
				h[j], \
				DOUBLE_XOR(ROTR32(e[j], 6), ROTR32(e[j], 11), ROTR32(e[j], 25))), \
				SHA2_CH(e[j], f[j], g[j])), \
				k), \
				x(i,j)); \
		d[j] = ADD32(d[j], h[j]); \
		h[j] = \
			ADD32(ADD32( \
				h[j], \
				DOUBLE_XOR(ROTR32(a[j], 2), ROTR32(a[j], 13), ROTR32(a[j], 22))), \
				SHA2_MAJ(a[j], b[j], c[j]));

#define SHA256_STEP(a,b,c,d,e,f,g,h,x,k,i) \
	if (INTERLEAVE > 0) { SHA256_STEP_(a,b,c,d,e,f,g,h,x,k,i,0); } \
	if (INTERLEAVE > 1) { SHA256_STEP_(a,b,c,d,e,f,g,h,x,k,i,1); } \
	if (INTERLEAVE > 2) { SHA256_STEP_(a,b,c,d,e,f,g,h,x,k,i,2); } \
	if (INTERLEAVE > 3) { SHA256_STEP_(a,b,c,d,e,f,g,h,x,k,i,3); }

#define SHA256_INIT(x, X) \
	if (INTERLEAVE > 0) { x[0] = X; } \
	if (INTERLEAVE > 1) { x[1] = X; } \
	if (INTERLEAVE > 2) { x[2] = X; } \
	if (INTERLEAVE > 3) { x[3] = X; }

#define SHA256_FINISH(out, i, x, X) \
	if (INTERLEAVE > 0) { out[i * INTERLEAVE + 0] = XOR(out[i * INTERLEAVE + 0], ADD32(x[0], X)); } \
	if (INTERLEAVE > 1) { out[i * INTERLEAVE + 1] = XOR(out[i * INTERLEAVE + 1], ADD32(x[1], X)); } \
	if (INTERLEAVE > 2) { out[i * INTERLEAVE + 2] = XOR(out[i * INTERLEAVE + 2], ADD32(x[2], X)); } \
	if (INTERLEAVE > 3) { out[i * INTERLEAVE + 3] = XOR(out[i * INTERLEAVE + 3], ADD32(x[3], X)); }

#define x(i,j)     w[(i % 16) * INTERLEAVE + j]

template <
	class TYPE,
	TYPE  ADD32     (TYPE, TYPE),
	TYPE  DOUBLE_XOR(TYPE, TYPE, TYPE),
	TYPE  SET32     (int),
	TYPE  ROTR32    (TYPE, int),
	TYPE  SHIFTR32  (TYPE, int)>
__inline__ void sha256FuncInit(TYPE partialW[9], const TYPE key[8])
{
//	partialW[-1] = ADD32(      offsetHi,                                                                            key[7]);
	// 0x80000000 + (ROT(320, 17) ^ ROT(320, 19) ^ (320 >> 10))
	partialW[ 0] = ADD32(              DOUBLE_XOR(ROTR32(key[0], 7), ROTR32(key[0], 18), SHIFTR32(key[0], 3)), SET32(0x80880000));
	partialW[ 1] = ADD32(      key[0], DOUBLE_XOR(ROTR32(key[1], 7), ROTR32(key[1], 18), SHIFTR32(key[1], 3)));
	partialW[ 2] = ADD32(      key[1], DOUBLE_XOR(ROTR32(key[2], 7), ROTR32(key[2], 18), SHIFTR32(key[2], 3)));
	partialW[ 3] = ADD32(      key[2], DOUBLE_XOR(ROTR32(key[3], 7), ROTR32(key[3], 18), SHIFTR32(key[3], 3)));
	partialW[ 4] = ADD32(      key[3], DOUBLE_XOR(ROTR32(key[4], 7), ROTR32(key[4], 18), SHIFTR32(key[4], 3)));
	partialW[ 5] = ADD32(ADD32(key[4], DOUBLE_XOR(ROTR32(key[5], 7), ROTR32(key[5], 18), SHIFTR32(key[5], 3))), SET32(320));
	partialW[ 6] = ADD32(      key[5], DOUBLE_XOR(ROTR32(key[6], 7), ROTR32(key[6], 18), SHIFTR32(key[6], 3)));
	partialW[ 7] = ADD32(      key[6], DOUBLE_XOR(ROTR32(key[7], 7), ROTR32(key[7], 18), SHIFTR32(key[7], 3)));
	partialW[ 8] = ADD32(      key[7], SET32(0x11002000)); // (ROT(0x80000000, 7) ^ ROT(0x80000000, 18) ^ (0x80000000 >> 3))
//	partialW[ 9] = 0x80000000 + 0;
//	partialW[10] = 0          + 0;
//	partialW[11] = 0          + 0;
//	partialW[12] = 0          + 0;
//	partialW[13] = 0          + 0x8050002a; // (ROT(320, 7) ^ ROT(320, 18) ^ (320 >> 3))
}

__inline__ void sha256FuncBroadcastInit(uint32_t partialW[9], const uint32_t key[8])
{
#define ROT(n, s) (((n) >> (s)) | ((n) << (32 - s)))

//	partialW[-1] = offsetHi                                                                    + key[7]     + 0;
	partialW[ 0] =              (ROT(key[0],     7) ^ ROT(key[0],     18) ^ (key[0]     >> 3)) + 0x80000000 + (ROT(320, 17) ^ ROT(320, 19) ^ (320 >> 10));
	partialW[ 1] = key[0]     + (ROT(key[1],     7) ^ ROT(key[1],     18) ^ (key[1]     >> 3)) + 0;
	partialW[ 2] = key[1]     + (ROT(key[2],     7) ^ ROT(key[2],     18) ^ (key[2]     >> 3)) + 0;
	partialW[ 3] = key[2]     + (ROT(key[3],     7) ^ ROT(key[3],     18) ^ (key[3]     >> 3)) + 0;
	partialW[ 4] = key[3]     + (ROT(key[4],     7) ^ ROT(key[4],     18) ^ (key[4]     >> 3)) + 0;
	partialW[ 5] = key[4]     + (ROT(key[5],     7) ^ ROT(key[5],     18) ^ (key[5]     >> 3)) + 320;
	partialW[ 6] = key[5]     + (ROT(key[6],     7) ^ ROT(key[6],     18) ^ (key[6]     >> 3));
	partialW[ 7] = key[6]     + (ROT(key[7],     7) ^ ROT(key[7],     18) ^ (key[7]     >> 3));
	partialW[ 8] = key[7]     + (ROT(0x80000000, 7) ^ ROT(0x80000000, 18) ^ (0x80000000 >> 3));
//	partialW[ 9] = 0x80000000 + 0;
//	partialW[10] = 0          + 0;
//	partialW[11] = 0          + 0;
//	partialW[12] = 0          + 0;
//	partialW[13] = 0          + 0x8050002a; // (ROT(320, 7) ^ ROT(320, 18) ^ (320 >> 3))

#undef ROT
}

template <
	class TYPE,
	TYPE  ADD32     (TYPE, TYPE),
	TYPE  XOR       (TYPE, TYPE),
	TYPE  DOUBLE_XOR(TYPE, TYPE, TYPE),
	TYPE  SHA2_CH   (TYPE, TYPE, TYPE),
	TYPE  SHA2_MAJ  (TYPE, TYPE, TYPE),
	TYPE  SET32     (int),
	TYPE  ROTR32    (TYPE, int),
	TYPE  SHIFTR32  (TYPE, int),
	int   INTERLEAVE>
__inline__ void sha256Func(TYPE *hashOut/*[8 * INTERLEAVE]*/, const TYPE key[8], const TYPE partialW[9], const TYPE *offsetLo/* [INTERLEAVE] */, const TYPE *offsetHi/* [INTERLEAVE] */)
{
#define x0(i,j)    offsetHi[j]
#define x1(i,j)    offsetLo[j]
#define x2(i,j)    key[0]
#define x3(i,j)    key[1]
#define x4(i,j)    key[2]
#define x5(i,j)    key[3]
#define x6(i,j)    key[4]
#define x7(i,j)    key[5]
#define x8(i,j)    key[6]
#define x9(i,j)    key[7]
#define x10(i,j)   SET32(0x80000000)
#define x11(i,j)   SET32(0)
#define x12(i,j)   SET32(0)
#define x13(i,j)   SET32(0)
#define x14(i,j)   SET32(0)
#define x15(i,j)   SET32(320)

	TYPE a[INTERLEAVE], b[INTERLEAVE], c[INTERLEAVE], d[INTERLEAVE];
	TYPE e[INTERLEAVE], f[INTERLEAVE], g[INTERLEAVE], h[INTERLEAVE];
	TYPE w[16 * INTERLEAVE];

	SHA256_INIT(a, SET32(0x6a09e667));
	SHA256_INIT(b, SET32(0xbb67ae85));
	SHA256_INIT(c, SET32(0x3c6ef372));
	SHA256_INIT(d, SET32(0xa54ff53a));
	SHA256_INIT(e, SET32(0x510e527f));
	SHA256_INIT(f, SET32(0x9b05688c));
	SHA256_INIT(g, SET32(0x1f83d9ab));
	SHA256_INIT(h, SET32(0x5be0cd19));

	SHA256_STEP(a,b,c,d,e,f,g,h, x0,SET32(0x428a2f98), 0);
	SHA256_STEP(h,a,b,c,d,e,f,g, x1,SET32(0x71374491), 1);
	SHA256_STEP(g,h,a,b,c,d,e,f, x2,SET32(0xb5c0fbcf), 2);
	SHA256_STEP(f,g,h,a,b,c,d,e, x3,SET32(0xe9b5dba5), 3);
	SHA256_STEP(e,f,g,h,a,b,c,d, x4,SET32(0x3956c25b), 4);
	SHA256_STEP(d,e,f,g,h,a,b,c, x5,SET32(0x59f111f1), 5);
	SHA256_STEP(c,d,e,f,g,h,a,b, x6,SET32(0x923f82a4), 6);
	SHA256_STEP(b,c,d,e,f,g,h,a, x7,SET32(0xab1c5ed5), 7);

	SHA256_STEP(a,b,c,d,e,f,g,h, x8,SET32(0xd807aa98), 8);
	SHA256_STEP(h,a,b,c,d,e,f,g, x9,SET32(0x12835b01), 9);
	SHA256_STEP(g,h,a,b,c,d,e,f,x10,SET32(0x243185be),10);
	SHA256_STEP(f,g,h,a,b,c,d,e,x11,SET32(0x550c7dc3),11);
	SHA256_STEP(e,f,g,h,a,b,c,d,x12,SET32(0x72be5d74),12);
	SHA256_STEP(d,e,f,g,h,a,b,c,x13,SET32(0x80deb1fe),13);
	SHA256_STEP(c,d,e,f,g,h,a,b,x14,SET32(0x9bdc06a7),14);
	SHA256_STEP(b,c,d,e,f,g,h,a,x15,SET32(0xc19bf174),15);

#define S7_18_3(x)   DOUBLE_XOR(ROTR32(x,  7), ROTR32(x, 18), SHIFTR32(x,  3))
#define S17_19_10(x) DOUBLE_XOR(ROTR32(x, 17), ROTR32(x, 19), SHIFTR32(x, 10))

#define NEXT_W_1(i) \
	if (INTERLEAVE > 0) { w[i * INTERLEAVE + 0] = ADD32(partialW[i - 1], S17_19_10(w[(i-2) * INTERLEAVE + 0])); } \
	if (INTERLEAVE > 1) { w[i * INTERLEAVE + 1] = ADD32(partialW[i - 1], S17_19_10(w[(i-2) * INTERLEAVE + 1])); } \
	if (INTERLEAVE > 2) { w[i * INTERLEAVE + 2] = ADD32(partialW[i - 1], S17_19_10(w[(i-2) * INTERLEAVE + 2])); } \
	if (INTERLEAVE > 3) { w[i * INTERLEAVE + 3] = ADD32(partialW[i - 1], S17_19_10(w[(i-2) * INTERLEAVE + 3])); }
#define NEXT_W_2(i) \
	if (INTERLEAVE > 0) { w[i * INTERLEAVE + 0] = ADD32(ADD32(partialW[i - 1], w[(i-7) * INTERLEAVE + 0]), S17_19_10(w[(i-2) * INTERLEAVE + 0])); } \
	if (INTERLEAVE > 1) { w[i * INTERLEAVE + 1] = ADD32(ADD32(partialW[i - 1], w[(i-7) * INTERLEAVE + 1]), S17_19_10(w[(i-2) * INTERLEAVE + 1])); } \
	if (INTERLEAVE > 2) { w[i * INTERLEAVE + 2] = ADD32(ADD32(partialW[i - 1], w[(i-7) * INTERLEAVE + 2]), S17_19_10(w[(i-2) * INTERLEAVE + 2])); } \
	if (INTERLEAVE > 3) { w[i * INTERLEAVE + 3] = ADD32(ADD32(partialW[i - 1], w[(i-7) * INTERLEAVE + 3]), S17_19_10(w[(i-2) * INTERLEAVE + 3])); }
#define NEXT_W_3(i,x) \
	if (INTERLEAVE > 0) { w[i * INTERLEAVE + 0] = ADD32(ADD32(x, w[(i-7) * INTERLEAVE + 0]), S17_19_10(w[(i-2) * INTERLEAVE + 0])); } \
	if (INTERLEAVE > 1) { w[i * INTERLEAVE + 1] = ADD32(ADD32(x, w[(i-7) * INTERLEAVE + 1]), S17_19_10(w[(i-2) * INTERLEAVE + 1])); } \
	if (INTERLEAVE > 2) { w[i * INTERLEAVE + 2] = ADD32(ADD32(x, w[(i-7) * INTERLEAVE + 2]), S17_19_10(w[(i-2) * INTERLEAVE + 2])); } \
	if (INTERLEAVE > 3) { w[i * INTERLEAVE + 3] = ADD32(ADD32(x, w[(i-7) * INTERLEAVE + 3]), S17_19_10(w[(i-2) * INTERLEAVE + 3])); }
#define NEXT_W_4(i,x) \
	if (INTERLEAVE > 0) { w[i * INTERLEAVE + 0] = ADD32(ADD32(ADD32(x, w[((i-7) % 16) * INTERLEAVE + 0]), S7_18_3(w[((i-15) % 16) * INTERLEAVE + 0])), S17_19_10(w[((i-2) % 16) * INTERLEAVE + 0])); } \
	if (INTERLEAVE > 1) { w[i * INTERLEAVE + 1] = ADD32(ADD32(ADD32(x, w[((i-7) % 16) * INTERLEAVE + 1]), S7_18_3(w[((i-15) % 16) * INTERLEAVE + 1])), S17_19_10(w[((i-2) % 16) * INTERLEAVE + 1])); } \
	if (INTERLEAVE > 2) { w[i * INTERLEAVE + 2] = ADD32(ADD32(ADD32(x, w[((i-7) % 16) * INTERLEAVE + 2]), S7_18_3(w[((i-15) % 16) * INTERLEAVE + 2])), S17_19_10(w[((i-2) % 16) * INTERLEAVE + 2])); } \
	if (INTERLEAVE > 3) { w[i * INTERLEAVE + 3] = ADD32(ADD32(ADD32(x, w[((i-7) % 16) * INTERLEAVE + 3]), S7_18_3(w[((i-15) % 16) * INTERLEAVE + 3])), S17_19_10(w[((i-2) % 16) * INTERLEAVE + 3])); }
#define NEXT_W(i) \
	if (INTERLEAVE > 0) { w[i * INTERLEAVE + 0] = ADD32(ADD32(ADD32(w[i * INTERLEAVE + 0], w[((i-7+16) % 16) * INTERLEAVE + 0]), S7_18_3(w[((i-15+16) % 16) * INTERLEAVE + 0])), S17_19_10(w[((i-2+16) % 16) * INTERLEAVE + 0])); } \
	if (INTERLEAVE > 1) { w[i * INTERLEAVE + 1] = ADD32(ADD32(ADD32(w[i * INTERLEAVE + 1], w[((i-7+16) % 16) * INTERLEAVE + 1]), S7_18_3(w[((i-15+16) % 16) * INTERLEAVE + 1])), S17_19_10(w[((i-2+16) % 16) * INTERLEAVE + 1])); } \
	if (INTERLEAVE > 2) { w[i * INTERLEAVE + 2] = ADD32(ADD32(ADD32(w[i * INTERLEAVE + 2], w[((i-7+16) % 16) * INTERLEAVE + 2]), S7_18_3(w[((i-15+16) % 16) * INTERLEAVE + 2])), S17_19_10(w[((i-2+16) % 16) * INTERLEAVE + 2])); } \
	if (INTERLEAVE > 3) { w[i * INTERLEAVE + 3] = ADD32(ADD32(ADD32(w[i * INTERLEAVE + 3], w[((i-7+16) % 16) * INTERLEAVE + 3]), S7_18_3(w[((i-15+16) % 16) * INTERLEAVE + 3])), S17_19_10(w[((i-2+16) % 16) * INTERLEAVE + 3])); }

	// 0
	if (INTERLEAVE > 0) { w[0 * INTERLEAVE + 0] = ADD32(ADD32(offsetHi[0], key[7]), S7_18_3(offsetLo[0])); }
	if (INTERLEAVE > 1) { w[0 * INTERLEAVE + 1] = ADD32(ADD32(offsetHi[1], key[7]), S7_18_3(offsetLo[1])); }
	if (INTERLEAVE > 2) { w[0 * INTERLEAVE + 2] = ADD32(ADD32(offsetHi[2], key[7]), S7_18_3(offsetLo[2])); }
	if (INTERLEAVE > 3) { w[0 * INTERLEAVE + 3] = ADD32(ADD32(offsetHi[3], key[7]), S7_18_3(offsetLo[3])); }
	SHA256_STEP(a,b,c,d,e,f,g,h,x,SET32(0xe49b69c1),16);
	// 1
	if (INTERLEAVE > 0) { w[1 * INTERLEAVE + 0] = ADD32(partialW[0], offsetLo[0]); }
	if (INTERLEAVE > 1) { w[1 * INTERLEAVE + 1] = ADD32(partialW[0], offsetLo[1]); }
	if (INTERLEAVE > 2) { w[1 * INTERLEAVE + 2] = ADD32(partialW[0], offsetLo[2]); }
	if (INTERLEAVE > 3) { w[1 * INTERLEAVE + 3] = ADD32(partialW[0], offsetLo[3]); }
	SHA256_STEP(h,a,b,c,d,e,f,g,x,SET32(0xefbe4786),17);
	NEXT_W_1( 2); SHA256_STEP(g,h,a,b,c,d,e,f,x,SET32(0x0fc19dc6),18);
	NEXT_W_1( 3); SHA256_STEP(f,g,h,a,b,c,d,e,x,SET32(0x240ca1cc),19);
	NEXT_W_1( 4); SHA256_STEP(e,f,g,h,a,b,c,d,x,SET32(0x2de92c6f),20);
	NEXT_W_1( 5); SHA256_STEP(d,e,f,g,h,a,b,c,x,SET32(0x4a7484aa),21);
	NEXT_W_1( 6); SHA256_STEP(c,d,e,f,g,h,a,b,x,SET32(0x5cb0a9dc),22);
	NEXT_W_2( 7); SHA256_STEP(b,c,d,e,f,g,h,a,x,SET32(0x76f988da),23);

	NEXT_W_2( 8);                    SHA256_STEP(a,b,c,d,e,f,g,h,x,SET32(0x983e5152),24);
	NEXT_W_2( 9);                    SHA256_STEP(h,a,b,c,d,e,f,g,x,SET32(0xa831c66d),25);
	NEXT_W_3(10, SET32(0x80000000)); SHA256_STEP(g,h,a,b,c,d,e,f,x,SET32(0xb00327c8),26);
	NEXT_W_3(11, SET32(         0)); SHA256_STEP(f,g,h,a,b,c,d,e,x,SET32(0xbf597fc7),27);
	NEXT_W_3(12, SET32(         0)); SHA256_STEP(e,f,g,h,a,b,c,d,x,SET32(0xc6e00bf3),28);
	NEXT_W_3(13, SET32(         0)); SHA256_STEP(d,e,f,g,h,a,b,c,x,SET32(0xd5a79147),29);
	NEXT_W_3(14, SET32(0x8050002a)); SHA256_STEP(c,d,e,f,g,h,a,b,x,SET32(0x06ca6351),30);
	NEXT_W_4(15, SET32(       320)); SHA256_STEP(b,c,d,e,f,g,h,a,x,SET32(0x14292967),31);

	NEXT_W( 0); SHA256_STEP(a,b,c,d,e,f,g,h,x,SET32(0x27b70a85),32);
	NEXT_W( 1); SHA256_STEP(h,a,b,c,d,e,f,g,x,SET32(0x2e1b2138),33);
	NEXT_W( 2); SHA256_STEP(g,h,a,b,c,d,e,f,x,SET32(0x4d2c6dfc),34);
	NEXT_W( 3); SHA256_STEP(f,g,h,a,b,c,d,e,x,SET32(0x53380d13),35);
	NEXT_W( 4); SHA256_STEP(e,f,g,h,a,b,c,d,x,SET32(0x650a7354),36);
	NEXT_W( 5); SHA256_STEP(d,e,f,g,h,a,b,c,x,SET32(0x766a0abb),37);
	NEXT_W( 6); SHA256_STEP(c,d,e,f,g,h,a,b,x,SET32(0x81c2c92e),38);
	NEXT_W( 7); SHA256_STEP(b,c,d,e,f,g,h,a,x,SET32(0x92722c85),39);

	NEXT_W( 8); SHA256_STEP(a,b,c,d,e,f,g,h,x,SET32(0xa2bfe8a1),40);
	NEXT_W( 9); SHA256_STEP(h,a,b,c,d,e,f,g,x,SET32(0xa81a664b),41);
	NEXT_W(10); SHA256_STEP(g,h,a,b,c,d,e,f,x,SET32(0xc24b8b70),42);
	NEXT_W(11); SHA256_STEP(f,g,h,a,b,c,d,e,x,SET32(0xc76c51a3),43);
	NEXT_W(12); SHA256_STEP(e,f,g,h,a,b,c,d,x,SET32(0xd192e819),44);
	NEXT_W(13); SHA256_STEP(d,e,f,g,h,a,b,c,x,SET32(0xd6990624),45);
	NEXT_W(14); SHA256_STEP(c,d,e,f,g,h,a,b,x,SET32(0xf40e3585),46);
	NEXT_W(15); SHA256_STEP(b,c,d,e,f,g,h,a,x,SET32(0x106aa070),47);

	NEXT_W( 0); SHA256_STEP(a,b,c,d,e,f,g,h,x,SET32(0x19a4c116),48);
	NEXT_W( 1); SHA256_STEP(h,a,b,c,d,e,f,g,x,SET32(0x1e376c08),49);
	NEXT_W( 2); SHA256_STEP(g,h,a,b,c,d,e,f,x,SET32(0x2748774c),50);
	NEXT_W( 3); SHA256_STEP(f,g,h,a,b,c,d,e,x,SET32(0x34b0bcb5),51);
	NEXT_W( 4); SHA256_STEP(e,f,g,h,a,b,c,d,x,SET32(0x391c0cb3),52);
	NEXT_W( 5); SHA256_STEP(d,e,f,g,h,a,b,c,x,SET32(0x4ed8aa4a),53);
	NEXT_W( 6); SHA256_STEP(c,d,e,f,g,h,a,b,x,SET32(0x5b9cca4f),54);
	NEXT_W( 7); SHA256_STEP(b,c,d,e,f,g,h,a,x,SET32(0x682e6ff3),55);

	NEXT_W( 8); SHA256_STEP(a,b,c,d,e,f,g,h,x,SET32(0x748f82ee),56);
	NEXT_W( 9); SHA256_STEP(h,a,b,c,d,e,f,g,x,SET32(0x78a5636f),57);
	NEXT_W(10); SHA256_STEP(g,h,a,b,c,d,e,f,x,SET32(0x84c87814),58);
	NEXT_W(11); SHA256_STEP(f,g,h,a,b,c,d,e,x,SET32(0x8cc70208),59);
	NEXT_W(12); SHA256_STEP(e,f,g,h,a,b,c,d,x,SET32(0x90befffa),60);
	NEXT_W(13); SHA256_STEP(d,e,f,g,h,a,b,c,x,SET32(0xa4506ceb),61);
	NEXT_W(14); SHA256_STEP(c,d,e,f,g,h,a,b,x,SET32(0xbef9a3f7),62);
	NEXT_W(15); SHA256_STEP(b,c,d,e,f,g,h,a,x,SET32(0xc67178f2),63);

	SHA256_FINISH(hashOut, 0, a, SET32(0x6a09e667));
	SHA256_FINISH(hashOut, 1, b, SET32(0xbb67ae85));
	SHA256_FINISH(hashOut, 2, c, SET32(0x3c6ef372));
	SHA256_FINISH(hashOut, 3, d, SET32(0xa54ff53a));
	SHA256_FINISH(hashOut, 4, e, SET32(0x510e527f));
	SHA256_FINISH(hashOut, 5, f, SET32(0x9b05688c));
	SHA256_FINISH(hashOut, 6, g, SET32(0x1f83d9ab));
	SHA256_FINISH(hashOut, 7, h, SET32(0x5be0cd19));

#undef x0
#undef x1
#undef x2
#undef x3
#undef x4
#undef x5
#undef x6
#undef x7
#undef x8
#undef x9
#undef x10
#undef x11
#undef x12
#undef x13
#undef x14
#undef x15

#undef S7_18_3
#undef S17_19_10
#undef NEXT_W_1
#undef NEXT_W_2
#undef NEXT_W_3
#undef NEXT_W
}

template <
	class TYPE,
	TYPE  ADD32     (TYPE, TYPE),
	TYPE  XOR       (TYPE, TYPE),
	TYPE  DOUBLE_XOR(TYPE, TYPE, TYPE),
	TYPE  SHA2_CH   (TYPE, TYPE, TYPE),
	TYPE  SHA2_MAJ  (TYPE, TYPE, TYPE),
	TYPE  SET32     (int),
	TYPE  ROTR32    (TYPE, int),
	TYPE  SHIFTR32  (TYPE, int),
	int   INTERLEAVE>
__inline__ void sha256FuncBroadcast(TYPE *hashOut/*[8 * INTERLEAVE]*/, const uint32_t key[8], const uint32_t partialW[9], const TYPE *offsetLo/* [INTERLEAVE] */, const TYPE *offsetHi/* [INTERLEAVE] */)
{
#define x0(i,j)    offsetHi[j]
#define x1(i,j)    offsetLo[j]
#define x2(i,j)    SET32(key[0])
#define x3(i,j)    SET32(key[1])
#define x4(i,j)    SET32(key[2])
#define x5(i,j)    SET32(key[3])
#define x6(i,j)    SET32(key[4])
#define x7(i,j)    SET32(key[5])
#define x8(i,j)    SET32(key[6])
#define x9(i,j)    SET32(key[7])
#define x10(i,j)   SET32(0x80000000)
#define x11(i,j)   SET32(0)
#define x12(i,j)   SET32(0)
#define x13(i,j)   SET32(0)
#define x14(i,j)   SET32(0)
#define x15(i,j)   SET32(320)

	TYPE a[INTERLEAVE], b[INTERLEAVE], c[INTERLEAVE], d[INTERLEAVE];
	TYPE e[INTERLEAVE], f[INTERLEAVE], g[INTERLEAVE], h[INTERLEAVE];
	TYPE w[16 * INTERLEAVE];

	SHA256_INIT(a, SET32(0x6a09e667));
	SHA256_INIT(b, SET32(0xbb67ae85));
	SHA256_INIT(c, SET32(0x3c6ef372));
	SHA256_INIT(d, SET32(0xa54ff53a));
	SHA256_INIT(e, SET32(0x510e527f));
	SHA256_INIT(f, SET32(0x9b05688c));
	SHA256_INIT(g, SET32(0x1f83d9ab));
	SHA256_INIT(h, SET32(0x5be0cd19));

	SHA256_STEP(a,b,c,d,e,f,g,h, x0,SET32(0x428a2f98), 0);
	SHA256_STEP(h,a,b,c,d,e,f,g, x1,SET32(0x71374491), 1);
	SHA256_STEP(g,h,a,b,c,d,e,f, x2,SET32(0xb5c0fbcf), 2);
	SHA256_STEP(f,g,h,a,b,c,d,e, x3,SET32(0xe9b5dba5), 3);
	SHA256_STEP(e,f,g,h,a,b,c,d, x4,SET32(0x3956c25b), 4);
	SHA256_STEP(d,e,f,g,h,a,b,c, x5,SET32(0x59f111f1), 5);
	SHA256_STEP(c,d,e,f,g,h,a,b, x6,SET32(0x923f82a4), 6);
	SHA256_STEP(b,c,d,e,f,g,h,a, x7,SET32(0xab1c5ed5), 7);

	SHA256_STEP(a,b,c,d,e,f,g,h, x8,SET32(0xd807aa98), 8);
	SHA256_STEP(h,a,b,c,d,e,f,g, x9,SET32(0x12835b01), 9);
	SHA256_STEP(g,h,a,b,c,d,e,f,x10,SET32(0x243185be),10);
	SHA256_STEP(f,g,h,a,b,c,d,e,x11,SET32(0x550c7dc3),11);
	SHA256_STEP(e,f,g,h,a,b,c,d,x12,SET32(0x72be5d74),12);
	SHA256_STEP(d,e,f,g,h,a,b,c,x13,SET32(0x80deb1fe),13);
	SHA256_STEP(c,d,e,f,g,h,a,b,x14,SET32(0x9bdc06a7),14);
	SHA256_STEP(b,c,d,e,f,g,h,a,x15,SET32(0xc19bf174),15);

#define S7_18_3(x)   DOUBLE_XOR(ROTR32(x,  7), ROTR32(x, 18), SHIFTR32(x,  3))
#define S17_19_10(x) DOUBLE_XOR(ROTR32(x, 17), ROTR32(x, 19), SHIFTR32(x, 10))

#define NEXT_W_1(i) \
	if (INTERLEAVE > 0) { w[i * INTERLEAVE + 0] = ADD32(SET32(partialW[i - 1]), S17_19_10(w[(i-2) * INTERLEAVE + 0])); } \
	if (INTERLEAVE > 1) { w[i * INTERLEAVE + 1] = ADD32(SET32(partialW[i - 1]), S17_19_10(w[(i-2) * INTERLEAVE + 1])); } \
	if (INTERLEAVE > 2) { w[i * INTERLEAVE + 2] = ADD32(SET32(partialW[i - 1]), S17_19_10(w[(i-2) * INTERLEAVE + 2])); } \
	if (INTERLEAVE > 3) { w[i * INTERLEAVE + 3] = ADD32(SET32(partialW[i - 1]), S17_19_10(w[(i-2) * INTERLEAVE + 3])); }
#define NEXT_W_2(i) \
	if (INTERLEAVE > 0) { w[i * INTERLEAVE + 0] = ADD32(ADD32(SET32(partialW[i - 1]), w[(i-7) * INTERLEAVE + 0]), S17_19_10(w[(i-2) * INTERLEAVE + 0])); } \
	if (INTERLEAVE > 1) { w[i * INTERLEAVE + 1] = ADD32(ADD32(SET32(partialW[i - 1]), w[(i-7) * INTERLEAVE + 1]), S17_19_10(w[(i-2) * INTERLEAVE + 1])); } \
	if (INTERLEAVE > 2) { w[i * INTERLEAVE + 2] = ADD32(ADD32(SET32(partialW[i - 1]), w[(i-7) * INTERLEAVE + 2]), S17_19_10(w[(i-2) * INTERLEAVE + 2])); } \
	if (INTERLEAVE > 3) { w[i * INTERLEAVE + 3] = ADD32(ADD32(SET32(partialW[i - 1]), w[(i-7) * INTERLEAVE + 3]), S17_19_10(w[(i-2) * INTERLEAVE + 3])); }
#define NEXT_W_3(i,x) \
	if (INTERLEAVE > 0) { w[i * INTERLEAVE + 0] = ADD32(ADD32(x, w[(i-7) * INTERLEAVE + 0]), S17_19_10(w[(i-2) * INTERLEAVE + 0])); } \
	if (INTERLEAVE > 1) { w[i * INTERLEAVE + 1] = ADD32(ADD32(x, w[(i-7) * INTERLEAVE + 1]), S17_19_10(w[(i-2) * INTERLEAVE + 1])); } \
	if (INTERLEAVE > 2) { w[i * INTERLEAVE + 2] = ADD32(ADD32(x, w[(i-7) * INTERLEAVE + 2]), S17_19_10(w[(i-2) * INTERLEAVE + 2])); } \
	if (INTERLEAVE > 3) { w[i * INTERLEAVE + 3] = ADD32(ADD32(x, w[(i-7) * INTERLEAVE + 3]), S17_19_10(w[(i-2) * INTERLEAVE + 3])); }
#define NEXT_W(i) \
	if (INTERLEAVE > 0) { w[i * INTERLEAVE + 0] = ADD32(ADD32(ADD32(w[i * INTERLEAVE + 0], w[((i-7) % 16) * INTERLEAVE + 0]), S7_18_3(w[((i-15) % 16) * INTERLEAVE + 0])), S17_19_10(w[((i-2) % 16) * INTERLEAVE + 0])); } \
	if (INTERLEAVE > 1) { w[i * INTERLEAVE + 1] = ADD32(ADD32(ADD32(w[i * INTERLEAVE + 0], w[((i-7) % 16) * INTERLEAVE + 1]), S7_18_3(w[((i-15) % 16) * INTERLEAVE + 0])), S17_19_10(w[((i-2) % 16) * INTERLEAVE + 1])); } \
	if (INTERLEAVE > 2) { w[i * INTERLEAVE + 2] = ADD32(ADD32(ADD32(w[i * INTERLEAVE + 0], w[((i-7) % 16) * INTERLEAVE + 2]), S7_18_3(w[((i-15) % 16) * INTERLEAVE + 0])), S17_19_10(w[((i-2) % 16) * INTERLEAVE + 2])); } \
	if (INTERLEAVE > 3) { w[i * INTERLEAVE + 3] = ADD32(ADD32(ADD32(w[i * INTERLEAVE + 0], w[((i-7) % 16) * INTERLEAVE + 3]), S7_18_3(w[((i-15) % 16) * INTERLEAVE + 0])), S17_19_10(w[((i-2) % 16) * INTERLEAVE + 3])); }

	// 0
	if (INTERLEAVE > 0) { w[0 * INTERLEAVE + 0] = ADD32(ADD32(offsetHi[0], SET32(key[7])), S7_18_3(offsetLo[0])); }
	if (INTERLEAVE > 1) { w[0 * INTERLEAVE + 1] = ADD32(ADD32(offsetHi[1], SET32(key[7])), S7_18_3(offsetLo[1])); }
	if (INTERLEAVE > 2) { w[0 * INTERLEAVE + 2] = ADD32(ADD32(offsetHi[2], SET32(key[7])), S7_18_3(offsetLo[2])); }
	if (INTERLEAVE > 3) { w[0 * INTERLEAVE + 3] = ADD32(ADD32(offsetHi[3], SET32(key[7])), S7_18_3(offsetLo[3])); }
	SHA256_STEP(a,b,c,d,e,f,g,h,x,SET32(0xe49b69c1),16);
	// 1
	if (INTERLEAVE > 0) { w[1 * INTERLEAVE + 0] = ADD32(partialW[0], offsetLo[0]); }
	if (INTERLEAVE > 1) { w[1 * INTERLEAVE + 1] = ADD32(partialW[0], offsetLo[1]); }
	if (INTERLEAVE > 2) { w[1 * INTERLEAVE + 2] = ADD32(partialW[0], offsetLo[2]); }
	if (INTERLEAVE > 3) { w[1 * INTERLEAVE + 3] = ADD32(partialW[0], offsetLo[3]); }
	SHA256_STEP(h,a,b,c,d,e,f,g,x,SET32(0xefbe4786),17);
	NEXT_W_1( 2); SHA256_STEP(g,h,a,b,c,d,e,f,x,SET32(0x0fc19dc6),18);
	NEXT_W_1( 3); SHA256_STEP(f,g,h,a,b,c,d,e,x,SET32(0x240ca1cc),19);
	NEXT_W_1( 4); SHA256_STEP(e,f,g,h,a,b,c,d,x,SET32(0x2de92c6f),20);
	NEXT_W_1( 5); SHA256_STEP(d,e,f,g,h,a,b,c,x,SET32(0x4a7484aa),21);
	NEXT_W_1( 6); SHA256_STEP(c,d,e,f,g,h,a,b,x,SET32(0x5cb0a9dc),22);
	NEXT_W_2( 7); SHA256_STEP(b,c,d,e,f,g,h,a,x,SET32(0x76f988da),23);

	NEXT_W_2( 8);                    SHA256_STEP(a,b,c,d,e,f,g,h,x,SET32(0x983e5152),24);
	NEXT_W_2( 9);                    SHA256_STEP(h,a,b,c,d,e,f,g,x,SET32(0xa831c66d),25);
	NEXT_W_3(10, SET32(0x80000000)); SHA256_STEP(g,h,a,b,c,d,e,f,x,SET32(0xb00327c8),26);
	NEXT_W_3(11, SET32(         0)); SHA256_STEP(f,g,h,a,b,c,d,e,x,SET32(0xbf597fc7),27);
	NEXT_W_3(12, SET32(         0)); SHA256_STEP(e,f,g,h,a,b,c,d,x,SET32(0xc6e00bf3),28);
	NEXT_W_3(13, SET32(         0)); SHA256_STEP(d,e,f,g,h,a,b,c,x,SET32(0xd5a79147),29);
	NEXT_W_3(14, SET32(0x8050002a)); SHA256_STEP(c,d,e,f,g,h,a,b,x,SET32(0x06ca6351),30);
	NEXT_W  (15);                    SHA256_STEP(b,c,d,e,f,g,h,a,x,SET32(0x14292967),31);

	NEXT_W( 0); SHA256_STEP(a,b,c,d,e,f,g,h,x,SET32(0x27b70a85),32);
	NEXT_W( 1); SHA256_STEP(h,a,b,c,d,e,f,g,x,SET32(0x2e1b2138),33);
	NEXT_W( 2); SHA256_STEP(g,h,a,b,c,d,e,f,x,SET32(0x4d2c6dfc),34);
	NEXT_W( 3); SHA256_STEP(f,g,h,a,b,c,d,e,x,SET32(0x53380d13),35);
	NEXT_W( 4); SHA256_STEP(e,f,g,h,a,b,c,d,x,SET32(0x650a7354),36);
	NEXT_W( 5); SHA256_STEP(d,e,f,g,h,a,b,c,x,SET32(0x766a0abb),37);
	NEXT_W( 6); SHA256_STEP(c,d,e,f,g,h,a,b,x,SET32(0x81c2c92e),38);
	NEXT_W( 7); SHA256_STEP(b,c,d,e,f,g,h,a,x,SET32(0x92722c85),39);

	NEXT_W( 8); SHA256_STEP(a,b,c,d,e,f,g,h,x,SET32(0xa2bfe8a1),40);
	NEXT_W( 9); SHA256_STEP(h,a,b,c,d,e,f,g,x,SET32(0xa81a664b),41);
	NEXT_W(10); SHA256_STEP(g,h,a,b,c,d,e,f,x,SET32(0xc24b8b70),42);
	NEXT_W(11); SHA256_STEP(f,g,h,a,b,c,d,e,x,SET32(0xc76c51a3),43);
	NEXT_W(12); SHA256_STEP(e,f,g,h,a,b,c,d,x,SET32(0xd192e819),44);
	NEXT_W(13); SHA256_STEP(d,e,f,g,h,a,b,c,x,SET32(0xd6990624),45);
	NEXT_W(14); SHA256_STEP(c,d,e,f,g,h,a,b,x,SET32(0xf40e3585),46);
	NEXT_W(15); SHA256_STEP(b,c,d,e,f,g,h,a,x,SET32(0x106aa070),47);

	NEXT_W( 0); SHA256_STEP(a,b,c,d,e,f,g,h,x,SET32(0x19a4c116),48);
	NEXT_W( 1); SHA256_STEP(h,a,b,c,d,e,f,g,x,SET32(0x1e376c08),49);
	NEXT_W( 2); SHA256_STEP(g,h,a,b,c,d,e,f,x,SET32(0x2748774c),50);
	NEXT_W( 3); SHA256_STEP(f,g,h,a,b,c,d,e,x,SET32(0x34b0bcb5),51);
	NEXT_W( 4); SHA256_STEP(e,f,g,h,a,b,c,d,x,SET32(0x391c0cb3),52);
	NEXT_W( 5); SHA256_STEP(d,e,f,g,h,a,b,c,x,SET32(0x4ed8aa4a),53);
	NEXT_W( 6); SHA256_STEP(c,d,e,f,g,h,a,b,x,SET32(0x5b9cca4f),54);
	NEXT_W( 7); SHA256_STEP(b,c,d,e,f,g,h,a,x,SET32(0x682e6ff3),55);

	NEXT_W( 8); SHA256_STEP(a,b,c,d,e,f,g,h,x,SET32(0x748f82ee),56);
	NEXT_W( 9); SHA256_STEP(h,a,b,c,d,e,f,g,x,SET32(0x78a5636f),57);
	NEXT_W(10); SHA256_STEP(g,h,a,b,c,d,e,f,x,SET32(0x84c87814),58);
	NEXT_W(11); SHA256_STEP(f,g,h,a,b,c,d,e,x,SET32(0x8cc70208),59);
	NEXT_W(12); SHA256_STEP(e,f,g,h,a,b,c,d,x,SET32(0x90befffa),60);
	NEXT_W(13); SHA256_STEP(d,e,f,g,h,a,b,c,x,SET32(0xa4506ceb),61);
	NEXT_W(14); SHA256_STEP(c,d,e,f,g,h,a,b,x,SET32(0xbef9a3f7),62);
	NEXT_W(15); SHA256_STEP(b,c,d,e,f,g,h,a,x,SET32(0xc67178f2),63);

	SHA256_FINISH(hashOut, 0, a, SET32(0x6a09e667));
	SHA256_FINISH(hashOut, 1, b, SET32(0xbb67ae85));
	SHA256_FINISH(hashOut, 2, c, SET32(0x3c6ef372));
	SHA256_FINISH(hashOut, 3, d, SET32(0xa54ff53a));
	SHA256_FINISH(hashOut, 4, e, SET32(0x510e527f));
	SHA256_FINISH(hashOut, 5, f, SET32(0x9b05688c));
	SHA256_FINISH(hashOut, 6, g, SET32(0x1f83d9ab));
	SHA256_FINISH(hashOut, 7, h, SET32(0x5be0cd19));

#undef x0
#undef x1
#undef x2
#undef x3
#undef x4
#undef x5
#undef x6
#undef x7
#undef x8
#undef x9
#undef x10
#undef x11
#undef x12
#undef x13
#undef x14
#undef x15

#undef S7_18_3
#undef S17_19_10
#undef NEXT_W_1
#undef NEXT_W_2
#undef NEXT_W_3
#undef NEXT_W
}

template <
	class TYPE,
	TYPE  ADD32     (TYPE, TYPE),
	TYPE  SUB32     (TYPE, TYPE),
	TYPE  CMPGT32   (TYPE, TYPE),
	TYPE  XOR       (TYPE, TYPE),
	TYPE  SET32     (int),
	void  SHA256_FUNC_INIT(TYPE*, const TYPE*),
	void  SHA256_FUNC(TYPE*, const TYPE*, const TYPE*, const TYPE*, const TYPE*),
	int   WIDTH,
	int   INTERLEAVE>
void parallelSha256Func(TYPE hashOut[8], const uint32_t *key, uint64_t offset, uint64_t count, TYPE CONST_3210)
{
	assert(count != 0);
	assert(count % (WIDTH * INTERLEAVE) == 0);

	TYPE curHash[8 * INTERLEAVE] = {SET32(0)};
	TYPE partialW[9];
	TYPE key_[8];
	TYPE offsetHi[INTERLEAVE];
	TYPE offsetLo[INTERLEAVE];

	key_[0] = SET32(key[0]);
	key_[1] = SET32(key[1]);
	key_[2] = SET32(key[2]);
	key_[3] = SET32(key[3]);
	key_[4] = SET32(key[4]);
	key_[5] = SET32(key[5]);
	key_[6] = SET32(key[6]);
	key_[7] = SET32(key[7]);

	SHA256_FUNC_INIT(partialW, key_);

	if (INTERLEAVE >= 1) { offsetHi[0] = SET32((uint32_t) (offset >> 32)); }
	if (INTERLEAVE >= 2) { offsetHi[1] = SET32((uint32_t) (offset >> 32)); }
	if (INTERLEAVE >= 3) { offsetHi[2] = SET32((uint32_t) (offset >> 32)); }
	if (INTERLEAVE >= 4) { offsetHi[3] = SET32((uint32_t) (offset >> 32)); }

	if (INTERLEAVE >= 1) { offsetLo[0] = ADD32(SET32((uint32_t) offset), CONST_3210); }
	if (INTERLEAVE >= 2) { offsetLo[1] = ADD32(SET32( 4), offsetLo[0]); }
	if (INTERLEAVE >= 3) { offsetLo[2] = ADD32(SET32( 8), offsetLo[0]); }
	if (INTERLEAVE >= 4) { offsetLo[3] = ADD32(SET32(12), offsetLo[0]); }

	if (INTERLEAVE >= 1) { offsetHi[0] = SUB32(offsetHi[0], CMPGT32(SET32((uint32_t) offset ^ 0x80000000), XOR(SET32(0x80000000), offsetLo[0]))); }
	if (INTERLEAVE >= 2) { offsetHi[1] = SUB32(offsetHi[1], CMPGT32(SET32((uint32_t) offset ^ 0x80000000), XOR(SET32(0x80000000), offsetLo[1]))); }
	if (INTERLEAVE >= 3) { offsetHi[2] = SUB32(offsetHi[2], CMPGT32(SET32((uint32_t) offset ^ 0x80000000), XOR(SET32(0x80000000), offsetLo[2]))); }
	if (INTERLEAVE >= 4) { offsetHi[3] = SUB32(offsetHi[3], CMPGT32(SET32((uint32_t) offset ^ 0x80000000), XOR(SET32(0x80000000), offsetLo[3]))); }

	count /= (WIDTH * INTERLEAVE);
	while (1)
	{
		SHA256_FUNC(curHash, key_, partialW, offsetLo, offsetHi);

		count--;
		if (count == 0)
		{
			break;
		}

		if (INTERLEAVE >= 1) { offsetLo[0] = ADD32(offsetLo[0], SET32(WIDTH * INTERLEAVE)); }
		if (INTERLEAVE >= 2) { offsetLo[1] = ADD32(offsetLo[1], SET32(WIDTH * INTERLEAVE)); }
		if (INTERLEAVE >= 3) { offsetLo[2] = ADD32(offsetLo[2], SET32(WIDTH * INTERLEAVE)); }
		if (INTERLEAVE >= 4) { offsetLo[3] = ADD32(offsetLo[3], SET32(WIDTH * INTERLEAVE)); }

		if (INTERLEAVE >= 1) { offsetHi[0] = SUB32(offsetHi[0], CMPGT32(SET32((WIDTH * INTERLEAVE) ^ 0x80000000), XOR(SET32(0x80000000), offsetLo[0]))); }
		if (INTERLEAVE >= 2) { offsetHi[1] = SUB32(offsetHi[1], CMPGT32(SET32((WIDTH * INTERLEAVE) ^ 0x80000000), XOR(SET32(0x80000000), offsetLo[1]))); }
		if (INTERLEAVE >= 3) { offsetHi[2] = SUB32(offsetHi[2], CMPGT32(SET32((WIDTH * INTERLEAVE) ^ 0x80000000), XOR(SET32(0x80000000), offsetLo[2]))); }
		if (INTERLEAVE >= 4) { offsetHi[3] = SUB32(offsetHi[3], CMPGT32(SET32((WIDTH * INTERLEAVE) ^ 0x80000000), XOR(SET32(0x80000000), offsetLo[3]))); }
	}


	#define COLLAPSE_XOR(i) \
		tmp = curHash[i * INTERLEAVE + 0]; \
		if (INTERLEAVE >= 2) { tmp = XOR(tmp, curHash[i * INTERLEAVE + 1]); } \
		if (INTERLEAVE >= 3) { tmp = XOR(tmp, curHash[i * INTERLEAVE + 2]); } \
		if (INTERLEAVE >= 4) { tmp = XOR(tmp, curHash[i * INTERLEAVE + 3]); } \
		hashOut[i] = tmp

	TYPE tmp;

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

template <
	class TYPE,
	TYPE  ADD32     (TYPE, TYPE),
	TYPE  SUB32     (TYPE, TYPE),
	TYPE  CMPGT32   (TYPE, TYPE),
	TYPE  XOR       (TYPE, TYPE),
	TYPE  SET32     (int),
	void  SHA256_FUNC_INIT(uint32_t*, const uint32_t*),
	void  SHA256_FUNC(TYPE*, const uint32_t*, const uint32_t*, const TYPE*, const TYPE*),
	int   WIDTH,
	int   INTERLEAVE>
void parallelSha256FuncBroadcast(TYPE hashOut[8], const uint32_t *key, uint64_t offset, uint64_t count, TYPE CONST_3210)
{
	assert(count != 0);
	assert(count % (WIDTH * INTERLEAVE) == 0);

	TYPE curHash[8 * INTERLEAVE] = {SET32(0)};
	TYPE offsetHi[INTERLEAVE];
	TYPE offsetLo[INTERLEAVE];
	uint32_t partialW[9];
	uint32_t key_[8];

	key_[0] = key[0];
	key_[1] = key[1];
	key_[2] = key[2];
	key_[3] = key[3];
	key_[4] = key[4];
	key_[5] = key[5];
	key_[6] = key[6];
	key_[7] = key[7];

	SHA256_FUNC_INIT(partialW, key_);

	if (INTERLEAVE >= 1) { offsetHi[0] = SET32((uint32_t) (offset >> 32)); }
	if (INTERLEAVE >= 2) { offsetHi[1] = SET32((uint32_t) (offset >> 32)); }
	if (INTERLEAVE >= 3) { offsetHi[2] = SET32((uint32_t) (offset >> 32)); }
	if (INTERLEAVE >= 4) { offsetHi[3] = SET32((uint32_t) (offset >> 32)); }

	if (INTERLEAVE >= 1) { offsetLo[0] = ADD32(SET32((uint32_t) offset), CONST_3210); }
	if (INTERLEAVE >= 2) { offsetLo[1] = ADD32(SET32( 4), offsetLo[0]); }
	if (INTERLEAVE >= 3) { offsetLo[2] = ADD32(SET32( 8), offsetLo[0]); }
	if (INTERLEAVE >= 4) { offsetLo[3] = ADD32(SET32(12), offsetLo[0]); }

	if (INTERLEAVE >= 1) { offsetHi[0] = SUB32(offsetHi[0], CMPGT32(SET32((uint32_t) offset ^ 0x80000000), XOR(SET32(0x80000000), offsetLo[0]))); }
	if (INTERLEAVE >= 2) { offsetHi[1] = SUB32(offsetHi[1], CMPGT32(SET32((uint32_t) offset ^ 0x80000000), XOR(SET32(0x80000000), offsetLo[1]))); }
	if (INTERLEAVE >= 3) { offsetHi[2] = SUB32(offsetHi[2], CMPGT32(SET32((uint32_t) offset ^ 0x80000000), XOR(SET32(0x80000000), offsetLo[2]))); }
	if (INTERLEAVE >= 4) { offsetHi[3] = SUB32(offsetHi[3], CMPGT32(SET32((uint32_t) offset ^ 0x80000000), XOR(SET32(0x80000000), offsetLo[3]))); }

	count /= (WIDTH * INTERLEAVE);
	while (1)
	{
		SHA256_FUNC(curHash, key_, partialW, offsetLo, offsetHi);

		count--;
		if (count == 0)
		{
			break;
		}

		if (INTERLEAVE >= 1) { offsetLo[0] = ADD32(offsetLo[0], SET32(WIDTH * INTERLEAVE)); }
		if (INTERLEAVE >= 2) { offsetLo[1] = ADD32(offsetLo[1], SET32(WIDTH * INTERLEAVE)); }
		if (INTERLEAVE >= 3) { offsetLo[2] = ADD32(offsetLo[2], SET32(WIDTH * INTERLEAVE)); }
		if (INTERLEAVE >= 4) { offsetLo[3] = ADD32(offsetLo[3], SET32(WIDTH * INTERLEAVE)); }

		if (INTERLEAVE >= 1) { offsetHi[0] = SUB32(offsetHi[0], CMPGT32(SET32((WIDTH * INTERLEAVE) ^ 0x80000000), XOR(SET32(0x80000000), offsetLo[0]))); }
		if (INTERLEAVE >= 2) { offsetHi[1] = SUB32(offsetHi[1], CMPGT32(SET32((WIDTH * INTERLEAVE) ^ 0x80000000), XOR(SET32(0x80000000), offsetLo[1]))); }
		if (INTERLEAVE >= 3) { offsetHi[2] = SUB32(offsetHi[2], CMPGT32(SET32((WIDTH * INTERLEAVE) ^ 0x80000000), XOR(SET32(0x80000000), offsetLo[2]))); }
		if (INTERLEAVE >= 4) { offsetHi[3] = SUB32(offsetHi[3], CMPGT32(SET32((WIDTH * INTERLEAVE) ^ 0x80000000), XOR(SET32(0x80000000), offsetLo[3]))); }
	}


	#define COLLAPSE_XOR(i) \
		tmp = curHash[i * INTERLEAVE + 0]; \
		if (INTERLEAVE >= 2) { tmp = XOR(tmp, curHash[i * INTERLEAVE + 1]); } \
		if (INTERLEAVE >= 3) { tmp = XOR(tmp, curHash[i * INTERLEAVE + 2]); } \
		if (INTERLEAVE >= 4) { tmp = XOR(tmp, curHash[i * INTERLEAVE + 3]); } \
		hashOut[i] = tmp

	TYPE tmp;

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

#undef x

#undef SHA256_INIT
#undef SHA256_FINISH
#undef SHA256_STEP
#undef SHA256_STEP_

#endif
#endif
