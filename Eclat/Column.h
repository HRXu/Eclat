#pragma once
#include <memory>
//每一列代表一个垂直集条目
struct Column {
	//vaild
	bool IsVaild;
	//项集
	bool *Item_Array = nullptr;

	//事务集合
	bool *T_Array = nullptr;

	//求并集
	bool CanIntersectWith(Column & src, Column &dest, int length);

	Column(int I_length, int T_length);
	Column(bool* itemArray, bool* tArray);
	Column();
};