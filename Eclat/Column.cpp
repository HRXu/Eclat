#include "Column.h"
#define MEMSET_0(i,j,k) memset(i,0,sizeof(j)*k)
//检查是否能求交 求并集
bool Column::CanIntersectWith(Column & col, int length)
{
	int diff = 0;
	for (int i = 0; i < length; i++)
	{
		diff += Item_Array[i] ^ col.Item_Array[i];
	}
	if (diff != 2) {
		return false;
	}
	return true;
}


Column::Column(int I_length, int T_length)
{
	Item_Array = new bool[I_length];
	memset(Item_Array, 0, sizeof(bool)*I_length);
	T_Array = new bool[T_length];
	memset(T_Array, 0, sizeof(bool)*T_length);
}

Column::Column(bool * itemArray, bool * tArray)
{
	this->Item_Array = itemArray;
	this->T_Array = tArray;
}

Column::Column()
{
}
