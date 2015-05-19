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
#include "hashfactory.h"

using namespace std;

list<hashInfo*> *HashFactory::s_hashes = NULL;

uint32_t HashFactory::getHashInstance(const char *name, hashAlgorithm &hash)
{
	list<hashInfo*>::iterator it;

	if (HashFactory::s_hashes != NULL)
	{
		for (it = s_hashes->begin(); it != s_hashes->end(); ++it)
		{
			if ((*it)->name == name)
			{
				hash = (*it)->hash;
				return 0;
			}
		}
	}
	hash.func          = NULL;
	hash.hashLength    = 0;
	hash.hashesPerCall = 0;
	return 1;
}

uint32_t HashFactory::registerHash(const char *name, const char *comment, HASH_FUNC hashFunc, uint32_t hashLength, uint32_t hashesPerCall)
{
	hashInfo *hi = new hashInfo;

	hi->hash.func          = hashFunc;
	hi->hash.hashLength    = hashLength;
	hi->hash.hashesPerCall = hashesPerCall;
	hi->name               = name;
	hi->comment            = comment;
	if (HashFactory::s_hashes == NULL)
	{
		HashFactory::s_hashes = new list<hashInfo*>;
	}
	s_hashes->push_back(hi);
	return 1;
}

void HashFactory::printHashes()
{
	list<hashInfo*>::iterator it;
	char   *spaces;
	size_t  nameMaxLen    = 0;
	size_t  commentMaxLen = 0;
	size_t  maxLen;

	if (HashFactory::s_hashes != NULL)
	{
		for (it = s_hashes->begin(); it != s_hashes->end(); ++it)
		{
			if (nameMaxLen < (*it)->name.length())
				nameMaxLen = (*it)->name.length();
			if (commentMaxLen < (*it)->comment.length())
				commentMaxLen = (*it)->comment.length();
		}
		maxLen = nameMaxLen > commentMaxLen ? nameMaxLen : commentMaxLen;
		spaces = new char[maxLen + 1];
		for (size_t a = 0; a < maxLen; a++)
		{
			spaces[a] = ' ';
		}
		spaces[maxLen] = 0;
		for (it = s_hashes->begin(); it != s_hashes->end(); ++it)
		{
			printf(" * %s%s [%s]%s\n",
				(*it)->name.c_str(),    spaces + (maxLen - nameMaxLen    + (*it)->name.length()),
				(*it)->comment.c_str(), spaces + (maxLen - commentMaxLen + (*it)->comment.length()));
		}
		delete [] spaces;
	}
	printf("\n");
}
