#pragma once
#include <memory>
class ECLAT_ReadBuffer
{
public:
	ECLAT_ReadBuffer();
	void Add(char c);
	int ToInt();
	~ECLAT_ReadBuffer();
private:
	char *_b;
	int index;
};

