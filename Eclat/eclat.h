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
		ECLAT(bool isAccerlate, int threshold);
		void Start();
		//��Ʒ����
		int Item_Count;
		//��������
		int T_Count;
		//֧�ֶ���ֵ
		int Threshold;
		bool UseAccerlate;
		CL_Factory cl_factory;

		//����
		std::vector<Column> Buffer_A;
		std::vector<Column> Buffer_B;
	private:

		//flag
		//designate using buffer
		bool UsingA = true;

		//����
		int Process();
		int Process_cl_ver();
		//���
		void Display(const std::vector<Column>& buffer_src);

		void ClearBuffer(std::vector<Column>& Buffer);

		//�󽻼�
		int Intersect(Column &col1,Column &col2,Column& dest,int length);
		int Intersect_cl_ver(Column & col1, Column & col2, Column & dest, int length);
};

