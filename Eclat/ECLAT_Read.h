#pragma once
#include "ECLAT_ReadBuffer.h"
#include <vector>
#include <fstream>
#include <map>
#include "Column.h"
#include "ECLAT.h"
class ECLAT_Read
{
public:
	enum DataSet {
		kosarak_Slim,
		kosarak2,
		kosarak,
		test,
		k1000,
		k5000,
	};
	static bool ReadData(ECLAT& eclat,DataSet _set);
	static void UX();
private:
	static void Read(std::vector<Column>& buffer_src,
					int t_count, 
					int item_count,
					const char * path);
};

