#pragma once
#include <memory>
//ÿһ�д���һ����ֱ����Ŀ
struct Column {
	//vaild
	bool IsVaild;
	//�
	bool *Item_Array = nullptr;

	//���񼯺�
	bool *T_Array = nullptr;

	//�󲢼�
	bool CanIntersection(Column & src, Column &dest, int length);

	Column(int I_length, int T_length);
	Column(bool* itemArray, bool* tArray);
	Column();
};