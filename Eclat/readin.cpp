#include "readin.h"
#define READ_INT(i) int i;cin>>i
#define READ_CHAR(i) char i;cin>>i
using namespace std;



void readin(map<int,tid>& horizonal, vector<vertical_item>& res) {
	READ_INT(cnt);

	map<char, item> vertical;
	for (int i = 0; i < cnt; i++)
	{
		tid &d=horizonal[i];
		d.id = i;
		READ_INT(k);
		d.item_vector.resize(k);
		for (int j = 0; j < k; j++)
		{
			READ_CHAR(tmp);
			d.item_vector[j]=tmp;
			vertical[tmp].t_vector.push_back(i);
		}
	}

	res.resize(vertical.size());

	int i = 0;
	for (auto &it : vertical) {
		res[i].item_set.insert(it.first);
		for (auto &it2 : it.second.t_vector) {
			res[i].t_set.insert(it2);
		}
		i++;
	}
}

void intersection_item(vertical_item &item1, vertical_item & item2,
				vector<vertical_item>& res,
				int support_threshold//支持度阈值
){
	//前k-1项一致
	int len = item1.item_set.size()-1;
	int i = 0;
	auto b1 = item1.item_set.begin();
	auto b2 = item2.item_set.begin();
	for (int i = 0; i < len; i++, b1++, b2++) {
		if (*b1 != *b2)return;
	}



	vertical_item tmp;
	for (auto &it1 : item1.item_set) {
		tmp.item_set.insert(it1);
	}
	for (auto &it2 : item2.item_set) {
		tmp.item_set.insert(it2);
	}

	auto _end2 = item2.t_set.end();
	for (auto &it1 : item1.t_set) {
		if (item2.t_set.find(it1) != _end2) tmp.t_set.insert(it1);
	}

	if (tmp.t_set.size() < support_threshold)return;
	res.push_back(tmp);
}