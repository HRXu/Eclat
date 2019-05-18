#pragma once
#include<map>
#include<cstdio>
#include<set>
#include<vector>
#include<cstdlib>
#include<fstream>
#include<algorithm>
#include"ECLAT_ReadBuffer.h"
struct tid {
	int id;
	std::vector<char> item_vector;
};
struct item
{
	char name;
	std::vector<int> t_vector;
};

struct vertical_item {
	std::set<char> item_set;
	std::set<int> t_set;
};

class ECLAT_STL
{
public:
	int Threshold;

	std::map<int, tid> m_horizonal;
	std::vector<vertical_item> v_buf_A;
	std::vector<vertical_item> v_buf_B;

	ECLAT_STL(int _threshold,const char* path);

	void display(std::vector<vertical_item> &m);

	void start();

private:
	void readin(std::map<int, tid>& horizonal, std::vector<vertical_item>& res, const char * path);
	void readin(std::vector<vertical_item>& res, const char * path);
	void intersection_item(vertical_item &item1, vertical_item & item2, std::vector<vertical_item>& res, int support_threshold);

};

