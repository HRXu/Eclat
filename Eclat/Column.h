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

	//����󲢼�
	bool CanIntersectWith(Column & col, int length);

	Column(int I_length, int T_length);
	Column(bool* itemArray, bool* tArray);
	Column();
	//column����������Ҫfree ���飬�����������ֻ�ʹ��vector<Column>����ǰfree�����
};