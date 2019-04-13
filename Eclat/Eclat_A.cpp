#include "Eclat_A.h"
#define READ_INT(i) int i;cin>>i
#define READ_CHAR(i) char i;cin>>i
using namespace std;

void Eclat_A::readin(std::map<int, tid>& horizonal, std::vector<vertical_item>& res)
{
	READ_INT(cnt);
	READ_INT(item_cnt);
	for (int i = 0; i < item_cnt; i++) {
		READ_CHAR(tmp);
	}
	cin >> this->threshold;

	map<char, item> vertical;
	for (int i = 0; i < cnt; i++)
	{
		tid &d = horizonal[i];
		d.id = i;
		READ_INT(k);
		d.item_vector.resize(k);
		for (int j = 0; j < k; j++)
		{
			READ_CHAR(tmp);
			d.item_vector[j] = tmp;
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

void Eclat_A::intersection_item(
	vertical_item & item1, 
	vertical_item & item2, 
	vector<vertical_item>& res, 
	int support_threshold)
{
	//Ç°k-1ÏîÒ»ÖÂ
	int len = item1.item_set.size() - 1;
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

void Eclat_A::display(std::map<int, tid>& m)
{
	for (auto &it : m) {
		printf("T%d: ", it.first);
		for (auto &it2 : it.second.item_vector) {
			printf("%c ", it2);
		}
		printf("\n");
	}
}

void Eclat_A::display(std::vector<vertical_item>& m)
{
	for (auto &it : m) {
		printf("{");

		int len = it.item_set.size();
		int i = 0;
		for (auto &it_i : it.item_set) {
			printf("%c%c", it_i, i != len - 1 ? ',' : '}');
			i++;
		}

		for (auto &it_t : it.t_set) {
			printf(" T%d", it_t);
		}
		printf("\n");
	}
}

void Eclat_A::start()
{
	readin(m_horizonal, v_vertical);
	display(m_horizonal);
	printf("\n");
	display(v_vertical);

	while (1) {
		v_vertical2.clear();
		for (int len = v_vertical.size(), i = 0; i < len; i++) {
			for (int j = i + 1; j < len; j++) {
				intersection_item(v_vertical[i], v_vertical[j], v_vertical2, this->threshold);
			}
		}
		printf("\n");
		display(v_vertical2);
		if (v_vertical2.size() == 0) {
			break;
		}

		v_vertical.clear();
		for (int len = v_vertical2.size(), i = 0; i < len; i++) {
			for (int j = i + 1; j < len; j++) {
				intersection_item(v_vertical2[i], v_vertical2[j], v_vertical, this->threshold);
			}
		}
		printf("\n");
		display(v_vertical);
		if (v_vertical.size() == 0) {
			break;
		}
	}

}

