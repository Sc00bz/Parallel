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

int main(int numArgs, const char *args[])
{
	hashAlgorithm hashAlgo;
	uint32_t      hashValue[8];
	// key = SHA256(SHA256("salt") || "password")
	uint32_t      key[8] = {0x702a8dcc, 0x982d62b0, 0xb955a490, 0xdd4e712c, 0xe90e9c1f, 0x9813ae48, 0x3ff0db4c, 0x398e27d7};
	uint64_t      offset = 0;
	uint64_t      count  = 1920;
	TIMER_TYPE    s;
	TIMER_TYPE    e;

	if (numArgs != 2)
	{
		printf("Supported hash algorithms:\n");
		HashFactory::printHashes();
		return 1;
	}
	if (HashFactory::getHashInstance(args[1], hashAlgo) != 0)
	{
		printf("Hash algorithm \"%s\" not found\n\nSupported hash algorithms:\n", args[1]);
		HashFactory::printHashes();
		return 1;
	}
	printf("Hash algorithm \"%s\"\n * Count must be a multiple of %u hashes\n * Output length of %u\n", args[1], hashAlgo.hashesPerCall, hashAlgo.hashLength);

	do
	{
		TIMER_FUNC(s);
		hashAlgo.func(hashValue, key, offset, count);
		TIMER_FUNC(e);
		printf("%0.0f H/s (%" PRIu64 " hashes, %0.6f seconds): %08x %08x %08x %08x\n",
			count / TIMER_DIFF(s, e),
			count,
			TIMER_DIFF(s, e),
			hashValue[0], hashValue[1], hashValue[2], hashValue[3],
			hashValue[4], hashValue[5], hashValue[6], hashValue[7]);
		count *= 2;
	} while (TIMER_DIFF(s, e) < 5);
	return 0;
}
