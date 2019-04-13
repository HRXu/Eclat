#pragma once
#include<iostream>
#include<unordered_map>
#include<cstdio>
#include<vector>
#include<string>
#include<cstdlib>
#include<algorithm>
//每一列代表一个垂直集条目
struct Column {
	//vaild
	bool IsVaild;
	//项集
	int *Item_Array=nullptr;

	//事务集合
	int *T_Array=nullptr;


	bool CanIntersection(const Column &c1, const Column &c2);
	void Intersection(Column &src, Column &dest);
};

class Eclat {
	public:	
		void Start();
		//商品数量
		int Item_Count;
		//事务数量
		int T_Count;
		//缓存矩阵A
		int Threshold;
	private:
		//名字与id的映射
		std::string* Items;
		std::unordered_map<std::string, int> Name_map;
		std::vector<Column> Buffer_A;

		bool UsingA = true;
		//缓存矩阵B
		std::vector<Column> Buffer_B;
		//求交
		int Process(std::vector<Column>& buffer_src, std::vector<Column>& buffer_dest);
		//输出
		void Display(const std::vector<Column>& buffer_src);
		//
		void Readin();
};

