#pragma once
#include <memory>
//ÿһ�д���һ����ֱ����Ŀ
struct Column {
	//vaild
	bool IsVaild;
	//�
	int *Item_Array = nullptr;

	//���񼯺�
	int *T_Array = nullptr;

	//�󲢼�
	bool CanIntersection(Column & src, Column &dest, int length);

	Column(int I_length, int T_length);
	Column(int* itemArray, int* tArray);
	Column();
};