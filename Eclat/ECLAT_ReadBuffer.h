#pragma once
#include <memory>
class ReadBuffer
{
public:
	ReadBuffer();
	void Add(char c);
	int ToInt();
	~ReadBuffer();
private:
	char *_b;
	int index;
};

