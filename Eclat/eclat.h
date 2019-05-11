#pragma once
#include<iostream>
#include<unordered_map>
#include<cstdio>
#include<vector>
#include<string>
#include<cstdlib>
#include<algorithm>
#include"Column.h"
#include"CL_Factory.h"

class ECLAT {
	public:	
		void Start(bool isAccerlate);
		//��Ʒ����
		int Item_Count;
		//��������
		int T_Count;
		int Threshold;

		CL_Factory cl_factory;

		//����
		std::vector<Column> Buffer_A;
		std::vector<Column> Buffer_B;
	private:
		//������id��ӳ��
		std::string* Items;
		std::unordered_map<std::string, int> Name_map;

		//flag
		//designate using buffer
		bool UsingA = true;

		//����
		int Process();
		int Process_cl_ver();
		//���
		void Display(const std::vector<Column>& buffer_src);

		void Readin();

		void ClearBuffer(std::vector<Column>& Buffer);

		//�󽻼�
		int Intersection(Column &col1,Column &col2,Column& dest,int length);
		int Intersection_cl_ver(Column & col1, Column & col2, Column & dest, int length);
};

