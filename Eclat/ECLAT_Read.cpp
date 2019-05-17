#include "ECLAT_Read.h"
using namespace std;

bool ECLAT_Read::ReadData(ECLAT& eclat, DataSet _set)
{
	switch (_set)
	{
	case ECLAT_Read::chess:
		break;
	case ECLAT_Read::connect:
		break;
	case ECLAT_Read::kosarak_Slim:
		eclat.Item_Count = 22036 + 1;
		eclat.T_Count = 80000+ 1;
		Read(eclat.Buffer_A,
			eclat.T_Count,
			eclat.Item_Count,
			"../Ex/data.txt");
		break;
	case ECLAT_Read::kosarak2:
		break;
	case ECLAT_Read::kosarak:
		eclat.Item_Count = 41270 + 1;
		eclat.T_Count = 990003 + 1;
		Read(eclat.Buffer_A,
			eclat.T_Count,
			eclat.Item_Count,
			"../Ex/kosarak.dat");
		break;
	case ECLAT_Read::mushroom:
		break;
	case ECLAT_Read::pumsb:
		break;
	case ECLAT_Read::pumsb_star:
		break;
	case ECLAT_Read::retail:
		break;
	case ECLAT_Read::test:
		eclat.Item_Count = 5 + 1;
		eclat.T_Count = 9 + 1;
		Read(eclat.Buffer_A,
			eclat.T_Count,
			eclat.Item_Count,
			"../Ex/test.txt");
		break;
	}

	return false;
}

void ECLAT_Read::Read(std::vector<Column>& buffer_src,
	int t_count, 
	int item_count,
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

	//convert to a vertical form
	for (auto &it : _map) {
		char *item_Array = new char[item_count];
		memset(item_Array, 0, sizeof(char)*item_count);
		item_Array[it.first] = 1;

		char *t_Array = new char[t_count];
		memset(t_Array, 0, sizeof(char)*t_count);
		for (auto &it2 : it.second) {
			t_Array[it2] = 1; 
		}
		buffer_src.push_back(Column(item_Array, t_Array));
	}
	_map.clear();
}