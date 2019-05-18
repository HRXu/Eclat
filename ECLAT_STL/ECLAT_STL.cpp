#include "ECLAT_STL.h"
using namespace std;

//unfinish
void ECLAT_STL::readin(				   
	std::vector<vertical_item>& res,
	const char *path)
{
	int max = 0;
	ifstream fs;
	fs.open(path, ios::in | ios::binary);

	char tmp;
	ECLAT_ReadBuffer buff;
	//[Item,Record] map
	map<int, vector<int>> _map;
	//line 
	int line = 1;

	while (true) {
		tmp = fs.get();
		if (tmp == -1)
			break;
		if (tmp == '\n') {
			//finish a nuumber
			//finish a line				
			_map[buff.ToInt()].push_back(line);
			line++;
		}
		else if (tmp == ' ') {
			//finish a nuumber
			_map[buff.ToInt()].push_back(line);
		}
		else {
			buff.Add(tmp);
		}
	}

	//close the file
	fs.close();

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

void ECLAT_STL::intersection_item(
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


ECLAT_STL::ECLAT_STL(int _threshold, const char * path)
{
	readin(v_buf_A, path);
	this->Threshold = _threshold;
}

void ECLAT_STL::display(std::vector<vertical_item>& m)
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

void ECLAT_STL::start()
{
	display(v_vertical);

	while (1) {
		v_vertical2.clear();
		for (int len = v_vertical.size(), i = 0; i < len; i++) {
			for (int j = i + 1; j < len; j++) {
				intersection_item(v_vertical[i], v_vertical[j], v_vertical2, this->Threshold);
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
				intersection_item(v_vertical2[i], v_vertical2[j], v_vertical, this->Threshold);
			}
		}
		printf("\n");
		display(v_vertical);
		if (v_vertical.size() == 0) {
			break;
		}
	}
}

