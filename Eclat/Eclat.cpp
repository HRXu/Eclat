#include "eclat.h"
using namespace std;
void Eclat::Start()
{
	this->Readin();
}

int Eclat::Process(std::vector<Column>& buffer_src, std::vector<Column>& buffer_dest)
{
	while (true)
	{
		if (UsingA) {

		}
		else {

		}
	}
	return 0;
}



bool Column::CanIntersection(Column & src, Column &dest, int length)
{
	int *tmp = new int[length];
	for (int i = 0; i < length; i++)
	{
		tmp[length] = this->Item_Array[i] | src.Item_Array[i];
	}

	if (true) {

		return true;
	}
	delete[] tmp;
	return false;
}

void Column::Intersection(Column & src,Column &dest,int length)
{
	for (int i = 0; i < length; i++) {
		dest.T_Array[i] = this->T_Array[i] & src.T_Array[i];
	}
}
