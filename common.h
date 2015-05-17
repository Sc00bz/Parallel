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

#ifndef COMMON_H
#define COMMON_H

#include <assert.h>
#include "architecture.h"

#ifdef _WIN32
	#pragma warning(disable:4996)
#endif

#if defined(_MSC_VER) || defined(__INTEL_COMPILER)
	#define __inline__  __forceinline
#elif defined(__GNUC__)
	#define __inline__  __inline __attribute__((__always_inline__))
#else
	#define __inline__  inline
#endif

#define QUOTE_(x) #x
#define QUOTE(x)  QUOTE_(x)

#define __STDC_CONSTANT_MACROS
#define __STDC_FORMAT_MACROS
#define __STDC_LIMIT_MACROS
#include <inttypes.h>
#ifdef _WIN32
	#include <time.h>
	#include <windows.h>
	#define TIMER_TYPE                clock_t
	#define TIMER_FUNC(t)             t = clock()
	#define TIMER_DIFF(s,e)           ((e - s) / (double)CLOCKS_PER_SEC)

	#define WIN_ALIGN_16 __declspec(align(16))
	#define ALIGN_16
#else
	#include <sys/time.h>
	#include <unistd.h>
	//#include <fcntl.h>
	#define TIMER_TYPE                timeval
	#define TIMER_FUNC(t)             gettimeofday(&t, NULL)
	#define TIMER_DIFF(s,e)           ((e.tv_sec - s.tv_sec) + (e.tv_usec - s.tv_usec) / (double)1000000.0)

	#define WIN_ALIGN_16
	#define ALIGN_16 __attribute__((aligned(16)))
#endif

enum instructionSets
{
	IS_MMX      = 0x0001,
	IS_SSE      = 0x0002,
	IS_SSE2     = 0x0004,
	IS_SSE3     = 0x0008,
	IS_SSSE3    = 0x0010,
	IS_SSE41    = 0x0020,
	IS_SSE42    = 0x0040,
	IS_SSE4A    = 0x0080,
	IS_AVX      = 0x0100,
	IS_XOP      = 0x0200,
	IS_AVX2     = 0x0400,
	IS_AVX512F  = 0x0800,
	IS_AVX512DQ = 0x1000,
	IS_OS_YMM   = 0x2000,
	IS_OS_ZMM   = 0x4000
};

uint32_t getInstructionSets();
void reportError(const char *msg, ...);
void reportWarning(const char *msg, ...);

#endif
