#pragma once
#include<iostream>
#include<map>
#include<set>
#include<cstdio>
#include<vector>
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


void readin(std::map<int, tid>& horizonal, std::vector<vertical_item>& res);
void intersection_item(vertical_item &item1, vertical_item & item2, std::vector<vertical_item>& res, int support_threshold);