#pragma once
#include <memory>
//每一列代表一个垂直集条目
struct Column {
	//vaild
	bool IsVaild;
	//项集
	int *Item_Array = nullptr;

	//事务集合
	int *T_Array = nullptr;

	//求并集
	bool CanIntersection(Column & src, Column &dest, int length);

	Column(int I_length, int T_length);
	Column(int* itemArray, int* tArray);
	Column();
};