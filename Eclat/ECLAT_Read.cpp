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
	case ECLAT_Read::kosarak_Slim:
		Read_Kosarak_Slim(buffer_src);
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

void ECLAT_Read::Read_Kosarak_Slim(std::vector<Column>& buffer_src)
{
	const int length=6965+1;//商品种类
	const int height=4702;//记录数

	int max = 0;
	ifstream fs;
	fs.open("../Ex/data.txt", ios::in | ios::binary);

	char tmp;
	ECLAT_ReadBuffer buff;
	//[Item,Record] map
	unordered_map<int, vector<int>> _map;
	//line number
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

	//int bf;
	//while (!fs.eof())
	//{
	//	fs >> bf;
	//	_map[bf].push_back(line);
	//	tmp = fs.get();
	//	if (tmp == '\n') {
	//		line++;
	//	}
	//	else if (tmp == ' ') {
	//		continue;
	//	}
	//}


	//close the file
	fs.close();

	//convert to a vertical form
	for (auto &it : _map) {
		bool *item_Array = new bool[length];
		memset(item_Array, 0, sizeof(bool)*length);
		item_Array[it.first] = 1;

		bool *t_Array = new bool[height]; 
		memset(t_Array, 0, sizeof(bool)*height);
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
