#pragma once
#include <memory>
//ÿһ�д���һ����ֱ����Ŀ
struct Column {
	//�
	char *Item_Array = nullptr;

	//���񼯺�
	char *T_Array = nullptr;

	//����󲢼�
	bool CanIntersectWith(Column & col, int length);

	Column(int I_length, int T_length);
	Column(char* itemArray, char* tArray);
	Column();
	//column����������Ҫfree ���飬�����������ֻ�ʹ��vector<Column>����ǰfree�����
};