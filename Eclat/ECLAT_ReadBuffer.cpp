#include "ECLAT_ReadBuffer.h"
ECLAT_ReadBuffer::ECLAT_ReadBuffer()
{
	_b = new char[8];
	memset(_b, -1, sizeof(char) * 8);
	index = 0;
}

void ECLAT_ReadBuffer::Add(char c)
{
	_b[index] = c;
	index++;
}

int ECLAT_ReadBuffer::ToInt()
{
	int res = 0;
	for (int i = index - 1, sc=1; i >= 0; i--) {
		res += (_b[i] - '0')*sc;
		sc *= 10;
	}
	memset(_b, -1, sizeof(char) * 8);
	index = 0;
	return res;
}

ECLAT_ReadBuffer::~ECLAT_ReadBuffer()
{
	delete[] _b;
}
