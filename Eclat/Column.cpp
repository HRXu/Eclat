#include "Column.h"
#define MEMSET_0(i,j,k) memset(i,0,sizeof(j)*k)
//检查是否能求交 求并集
bool Column::CanIntersectWith(Column & col, int length)
{
	int location = 0;
	int s1 = 0;
	for (int i = 0; i < length; i++)
	{
		switch (location)
		{
		case 0:
			if (Item_Array[i] != col.Item_Array[i]) {
				location = 1;
			}
			break;
		case 1:
			if (Item_Array[i] | col.Item_Array[i])
				s1++;
			break;
		}
	}
	if (s1 != 1) {
		return false;
	}


	return true;
}


Column::Column(int I_length, int T_length)
{
	Item_Array = new char[I_length];
	memset(Item_Array, 0, sizeof(char)*I_length);
	T_Array = new char[T_length];
	memset(T_Array, 0, sizeof(char)*T_length);
}

Column::Column(char * itemArray, char * tArray)
{
	this->Item_Array = itemArray;
	this->T_Array = tArray;
}

Column::Column()
{
}
