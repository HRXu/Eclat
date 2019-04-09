#pragma once
#include<iostream>
#include<unordered_map>
#include<cstdio>
#include<vector>
#include<cstdlib>
#include<algorithm>
struct Column {
	//vaild
	bool IsVaild;
	//�
	char *Item_Array;
	int Item_Array_Length;
	//���񼯺�
	char *T_Array;
	int T_Array_Length;

	bool CanIntersection(const Column &c1, const Column &c2);
	void Intersection(Column &src, Column &dest);
};

class Eclat {
	public:	
		Eclat(std::string path);
		void Start();

	private:
		//������id��ӳ��
		std::unordered_map<int, std::string> name_map;
		//��Ʒ����
		int Item_Count;
		//��������
		int T_Count;
		//�������A
		std::vector<Column> Buffer_A;
		//�������B
		std::vector<Column> Buffer_B;
		//��
		int Process(std::vector<Column>& buffer_src, std::vector<Column>& buffer_dest);
		//���
		void Display(const std::vector<Column>& buffer_src);
};

