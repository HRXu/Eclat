#pragma once
#include <memory>
//每一列代表一个垂直集条目
struct Column {
	//项集
	char *Item_Array = nullptr;

	//事务集合
	char *T_Array = nullptr;

	//检查求并集
	bool CanIntersectWith(Column & col, int length);

	Column(int I_length, int T_length);
	Column(char* itemArray, char* tArray);
	Column();
	//column析构函数不要free 数组，程序其他部分会使用vector<Column>，提前free会出错
};