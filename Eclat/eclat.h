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
	//项集
	char *Item_Array;
	int Item_Array_Length;
	//事务集合
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
		//名字与id的映射
		std::unordered_map<int, std::string> name_map;
		//商品数量
		int Item_Count;
		//事务数量
		int T_Count;
		//缓存矩阵A
		std::vector<Column> Buffer_A;
		//缓存矩阵B
		std::vector<Column> Buffer_B;
		//求交
		int Process(std::vector<Column>& buffer_src, std::vector<Column>& buffer_dest);
		//输出
		void Display(const std::vector<Column>& buffer_src);
};

