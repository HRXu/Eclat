#include "ReadBuffer.h"
ReadBuffer::ReadBuffer()
{
	_b = new char[8];
	memset(_b, -1, sizeof(char) * 8);
	index = 0;
}

void ReadBuffer::Add(char c)
{
	_b[index] = c;
	index++;
}

int ReadBuffer::ToInt()
{
	int res = 0;
	for (int i = index - 1,int sc=1; i > 0; i--) {
		res += (_b[i] - '0')*sc;
		sc *= 10;
	}
	memset(_b, -1, sizeof(char) * 8);
	index = 0;
	return res;
}

ReadBuffer::~ReadBuffer()
{
	delete[] _b;
}
