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

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "common.h"
#ifdef _WIN32
	#include <intrin.h>
#endif

uint32_t getInstructionSets()
{
#ifdef ARC_x86
	static uint32_t ret = 0xffffffff;

	if (ret == 0xffffffff)
	{
		uint32_t ecx_1;
		uint32_t edx_1;
		uint32_t ebx_7;
		uint32_t ecx_0x80000001;
		uint32_t edx_0x80000001;

#ifdef _WIN32
		int cpuInfo[4];

		__cpuid(cpuInfo, 1);
		ecx_1 = (uint32_t) (cpuInfo[2]);
		edx_1 = (uint32_t) (cpuInfo[3]);
		__cpuid(cpuInfo, 7);
		ebx_7 = (uint32_t) (cpuInfo[1]);
		__cpuid(cpuInfo, 0x80000001);
		ecx_0x80000001 = (uint32_t) (cpuInfo[2]);
		edx_0x80000001 = (uint32_t) (cpuInfo[3]);
#else
		asm(
			"movl   $1,%%eax\n\t"
			"xor    %%ecx,%%ecx\n\t"
			"cpuid\n\t"
			"movl   %%ecx,%0\n\t"
			"movl   %%edx,%1\n\t"
			"movl   $7,%%eax\n\t"
			"xor    %%ecx,%%ecx\n\t"
			"cpuid\n\t"
			"movl   %%ebx,%2\n\t"
			"movl   $2147483649,%%eax\n\t"
			"xor    %%ecx,%%ecx\n\t"
			"cpuid"
			: "=m"(ecx_1), "=m"(edx_1), "=m"(ebx_7), "=c"(ecx_0x80000001), "=d"(edx_0x80000001) // output
			: // input
			: "eax", "ebx"); // used
#endif
		ret = 0;
		if (edx_1          & (1 << 23)) { ret |= IS_MMX;      }
		if (edx_1          & (1 << 25)) { ret |= IS_SSE;      }
		if (edx_1          & (1 << 26)) { ret |= IS_SSE2;     }
		if (ecx_1          & (1 <<  0)) { ret |= IS_SSE3;     }
		if (ecx_1          & (1 <<  9)) { ret |= IS_SSSE3;    }
		if (ecx_1          & (1 << 19)) { ret |= IS_SSE41;    }
		if (ecx_1          & (1 << 20)) { ret |= IS_SSE42;    }
		if (ecx_0x80000001 & (1 <<  6)) { ret |= IS_SSE4A;    }
		if (ecx_1          & (1 << 28)) { ret |= IS_AVX;      }
		if (ecx_0x80000001 & (1 << 11)) { ret |= IS_XOP;      }
		if (ebx_7          & (1 <<  5)) { ret |= IS_AVX2;     }
		if (ebx_7          & (1 << 16)) { ret |= IS_AVX512F;  }
		if (ebx_7          & (1 << 17)) { ret |= IS_AVX512DQ; }

		// OSXSAVE (XGETBV)
		if ((ret & IS_AVX) && (ecx_1 & (1 << 27)))
		{
#ifdef _WIN32
			unsigned long long xcr = _xgetbv(_XCR_XFEATURE_ENABLED_MASK);
#else
			uint32_t xcr;
			asm(
				"xor   %%ecx,%%ecx\n\t"
				"xgetbv"
				: "=a"(xcr) // output
				: // input
				: "ecx", "edx"); // used
#endif
			if ((xcr & 0x06) == 0x06) { ret |= IS_OS_YMM; }
			if ((xcr & 0xe6) == 0xe6) { ret |= IS_OS_ZMM; }

			if ((ret & (IS_AVX512F | IS_OS_ZMM)) == (IS_AVX512F | IS_OS_ZMM))
			{
				reportWarning("Your OS does not support ZMM registers, but your CPU has AVX512.");
			}
			else if ((ret & (IS_AVX | IS_AVX2 | IS_OS_YMM)) == (IS_AVX | IS_AVX2 | IS_OS_YMM))
			{
				reportWarning("Your OS does not support YMM registers, but your CPU has AVX and AVX2.");
			}
			else if ((ret & (IS_AVX | IS_OS_YMM)) == (IS_AVX | IS_OS_YMM))
			{
				reportWarning("Your OS does not support YMM registers, but your CPU has AVX.");
			}
		}
#ifdef ARC_x86_32
		if ((edx_1 & (1 << 30)) || (edx_0x80000001 & (1 << 29)) || (ecx_0x80000001 & (1 << 6))) // x86_64, long_mode, long_mode_intel
		{
			reportWarning("Your CPU can run 64 bit which runs faster than the 32 bit code you are currently running.");
		}
#endif
	}
	return ret;
#else
	return 0;
#endif
}

void reportError(const char *msg, ...)
{
	va_list args;
	char *format = new char[strlen(msg) + 9]; // 9 == sizeof("Error: \n")

	sprintf(format, "Error: %s\n", msg);
	va_start(args, msg);
	vfprintf(stderr, format, args);
	va_end(args);
	delete [] format;
}

void reportWarning(const char *msg, ...)
{
	va_list args;
	char *format = new char[strlen(msg) + 11]; // 11 == sizeof("Warning: \n")

	sprintf(format, "Warning: %s\n", msg);
	va_start(args, msg);
	vfprintf(stderr, format, args);
	va_end(args);
	delete [] format;
}
