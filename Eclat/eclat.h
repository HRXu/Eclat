#pragma once
#include<iostream>
#include<unordered_map>
#include<cstdio>
#include<vector>
#include<string>
#include<cstdlib>
#include<algorithm>
#include"Cl_Factory.h"
//每一列代表一个垂直集条目
struct Column {
	//vaild
	bool IsVaild;
	//项集
	int *Item_Array=nullptr;

	//事务集合
	int *T_Array=nullptr;

	//求并集
	bool CanIntersection(Column & src, Column &dest, int length);


	Column(int I_length,int T_length);
	Column();
};

class Eclat {
	public:	
		void Start(bool isAccerlate);
		//商品数量
		int Item_Count;
		//事务数量
		int T_Count;
		//缓存矩阵A
		int Threshold;

		Cl_Factory cl_factory;
	private:
		//名字与id的映射
		std::string* Items;
		std::unordered_map<std::string, int> Name_map;
		std::vector<Column> Buffer_A;

		bool UsingA = true;
		//缓存矩阵B
		std::vector<Column> Buffer_B;
		//计算
		int Process();
		int Process_cl_ver();
		//输出
		void Display(const std::vector<Column>& buffer_src);
		//
		void Readin();

		void ClearBuffer(std::vector<Column>& Buffer);

		//求交集
		int Intersection(Column &col1,Column &col2,Column& dest,int length);
		int Intersection_cl_ver(Column & col1, Column & col2, Column & dest, int length);
};

