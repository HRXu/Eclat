#pragma once
#include<iostream>
#include<map>
#include<cstdio>
#include<set>
#include<vector>
#include<cstdlib>
#include<algorithm>
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

class Eclat_A
{
public:
	Eclat_A();
	~Eclat_A();

	std::map<int, tid> m_horizonal;
	std::vector<vertical_item> v_vertical;
	std::vector<vertical_item> v_vertical2;

	void readin(std::map<int, tid>& horizonal, std::vector<vertical_item>& res);
	void intersection_item(vertical_item &item1, vertical_item & item2, std::vector<vertical_item>& res, int support_threshold);

	void display(std::map<int, tid> &m);
	void display(std::vector<vertical_item> &m);
};

