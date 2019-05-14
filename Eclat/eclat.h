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
		//��ʼ�㷨����
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
		void Reduce();
	private:

		//flag
		//designate using buffer
		bool UsingA = true;

		//����
		int Process();
		void _ProcessA(std::vector<Column>& source, std::vector<Column>& destination,int cnt);
		int CL_Process();
		//���
		void Display(const std::vector<Column>& buffer_src);

		void ClearBuffer(std::vector<Column>& Buffer);

		//�󽻼�
		int Intersect(Column & col1, Column & col2, Column & dest);
		int CL_Intersect(Column & col1, Column & col2, Column & dest);
};

