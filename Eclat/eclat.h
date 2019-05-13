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
		//商品数量
		int Item_Count;
		//事务数量
		int T_Count;
		//支持度阈值
		int Threshold;
		bool UseAccerlate;
		CL_Factory cl_factory;

		//缓存
		std::vector<Column> Buffer_A;
		std::vector<Column> Buffer_B;
	private:

		//flag
		//designate using buffer
		bool UsingA = true;

		//计算
		int Process();
		int Process_cl_ver();
		//输出
		void Display(const std::vector<Column>& buffer_src);

		void ClearBuffer(std::vector<Column>& Buffer);

		//求交集
		int Intersect(Column &col1,Column &col2,Column& dest,int length);
		int Intersect_cl_ver(Column & col1, Column & col2, Column & dest, int length);
};

