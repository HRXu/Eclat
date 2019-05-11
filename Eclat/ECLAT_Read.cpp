#include "ECLAT_Read.h"
using namespace std;

bool ECLAT_Read::ReadData(std::vector<Column>& buffer_src, DataSet _set)
{
	switch (_set)
	{
	case ECLAT_Read::chess:
		break;
	case ECLAT_Read::connect:
		break;
	case ECLAT_Read::kosarak:
		Read_Kosarak(buffer_src);
		break;
	case ECLAT_Read::kosarak2:
		break;
	case ECLAT_Read::mushroom:
		break;
	case ECLAT_Read::pumsb:
		break;
	case ECLAT_Read::pumsb_star:
		break;
	case ECLAT_Read::retail:
		break;
	default:
		break;
	}
	return false;
}

void ECLAT_Read::Read_Kosarak(std::vector<Column>& buffer_src)
{
	const int length=41270;//商品种类
	const int height=990002;//记录数

	int max = 0;
	ifstream fs;
	fs.open("../Ex/kosarak.dat", ios::in | ios::binary);
	char tmp;
	int location = 0;
	bool flag = true;
	ECLAT_ReadBuffer buff;

	//[Item,Record] map
	unordered_map<int, vector<int>> _map;
	//line number
	int line = 1;

	while (flag) {
		tmp = fs.get();
		if (tmp == -1)
			break;
		switch (location)
		{
		case 0:
			if (tmp == '\n') {
				//finish a line
				line++;
				location = 0;
			}
			else if (tmp == ' ');
			else {
				buff.Add(tmp);
				location = 1;
			}
			break;
		case 1:
			if (tmp == '\n') {
				//finish a nuumber
				//finish a line				
				_map[buff.ToInt()].push_back(line);

				line++;
				location = 0;
			}
			else if (tmp == ' ') {
				//finish a nuumber
				_map[buff.ToInt()].push_back(line);
				location = 2;
			}
			else {
				buff.Add(tmp);
				location = 1;
			}
			break;
		case 2:
			if (tmp == ' ');
			else if (tmp == '\n') {
				//finish a line
				line++;
				location = 0;
			}
			else {
				buff.Add(tmp);
				location = 1;
			}
			break;
		}
	}
	//close the file
	fs.close();

	//convert to a vertical form
	for (auto &it : _map) {
		int *item_Array = new int[length];
		memset(item_Array, 0, sizeof(int)*length);
		item_Array[it.first] = 1;
		int *t_Array = new int[height]; 
		memset(item_Array, 0, sizeof(int)*height);
		for (auto &it2 : it.second) {
			t_Array[it2] = 1;
		}
		buffer_src.push_back(Column(item_Array, t_Array));
	}
}

void ECLAT_Read::Read_kosarak2(std::vector<Column>& buffer_src, char * path)
{
}

void ECLAT_Read::Read_retail(std::vector<Column>& buffer_src, char * path)
{
}
