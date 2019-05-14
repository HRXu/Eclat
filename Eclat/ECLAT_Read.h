#pragma once
#include "ECLAT_ReadBuffer.h"
#include <vector>
#include <fstream>
#include <unordered_map>
#include "Column.h"
#include "ECLAT.h"
class ECLAT_Read
{
public:
	enum DataSet {
		chess = 0,
		connect,
		kosarak_Slim,
		kosarak2,
		mushroom,
		pumsb,
		pumsb_star,
		retail,
		test
	};
	static bool ReadData(ECLAT& eclat,DataSet _set);

private:
	static void Read(std::vector<Column>& buffer_src,
					int t_count, 
					int item_count,
					const char * path);
};

