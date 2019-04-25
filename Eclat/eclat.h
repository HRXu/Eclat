#pragma once
#include<iostream>
#include<unordered_map>
#include<cstdio>
#include<vector>
#include<string>
#include<cstdlib>
#include<algorithm>
#include"Cl_Factory.h"
//ÿһ�д���һ����ֱ����Ŀ
struct Column {
	//vaild
	bool IsVaild;
	//�
	int *Item_Array=nullptr;

	//���񼯺�
	int *T_Array=nullptr;

	//�󲢼�
	bool CanIntersection(Column & src, Column &dest, int length);


	Column(int I_length,int T_length);
	Column();
};

class Eclat {
	public:	
		void Start(bool isAccerlate);
		//��Ʒ����
		int Item_Count;
		//��������
		int T_Count;
		//�������A
		int Threshold;

		Cl_Factory cl_factory;
	private:
		//������id��ӳ��
		std::string* Items;
		std::unordered_map<std::string, int> Name_map;
		std::vector<Column> Buffer_A;

		bool UsingA = true;
		//�������B
		std::vector<Column> Buffer_B;
		//����
		int Process();
		int Process_cl_ver();
		//���
		void Display(const std::vector<Column>& buffer_src);
		//
		void Readin();

		void ClearBuffer(std::vector<Column>& Buffer);

		//�󽻼�
		int Intersection(Column &col1,Column &col2,Column& dest,int length);
		int Intersection_cl_ver(Column & col1, Column & col2, Column & dest, int length);
};

