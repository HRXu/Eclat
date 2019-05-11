#pragma once
#include "ECLAT_ReadBuffer.h"
#include <vector>
#include <fstream>
#include <unordered_map>
#include "Column.h"
class ECLAT_Read
{
public:
	enum DataSet {
		chess = 0,
		connect,
		kosarak,
		kosarak2,
		mushroom,
		pumsb,
		pumsb_star,
		retail
	};
	static bool ReadData(std::vector<Column>& buffer_src,DataSet _set);

private:
	static void Read_Kosarak(std::vector<Column>& buffer_src);
	static void Read_kosarak2(std::vector<Column>& buffer_src,char *path);
	static void Read_retail(std::vector<Column>& buffer_src,char *path);
};

