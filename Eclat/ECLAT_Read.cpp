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
		eclat.Item_Count = 6959 + 1;
		eclat.T_Count = 4702 + 1;
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
	case ECLAT_Read::test:
		eclat.Item_Count = 5 + 1;
		eclat.T_Count = 9 + 1;
		break;
	}
	Read(eclat.Buffer_A, eclat.T_Count, eclat.Item_Count);
	return false;
}

void ECLAT_Read::Read(std::vector<Column>& buffer_src,int t_count,int item_count)
{

	int max = 0;
	ifstream fs;
	fs.open("../Ex/test.txt", ios::in | ios::binary);

	char tmp;
	ECLAT_ReadBuffer buff;
	//[Item,Record] map
	unordered_map<int, vector<int>> _map;

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
		bool *item_Array = new bool[item_count];
		memset(item_Array, 0, sizeof(bool)*item_count);
		item_Array[it.first] = 1;

		bool *t_Array = new bool[t_count];
		memset(t_Array, 0, sizeof(bool)*t_count);
		for (auto &it2 : it.second) {
			t_Array[it2] = 1;
		}
		buffer_src.push_back(Column(item_Array, t_Array));
	}
}