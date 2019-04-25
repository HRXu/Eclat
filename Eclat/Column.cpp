#include "Eclat.h"
#define MEMSET_0(i,j,k) memset(i,0,sizeof(j)*k)
bool Column::CanIntersection(Column & src, Column &dest, int length)
{
	int *tmp = new int[length];
	MEMSET_0(tmp, int, length);

	int diff = 0;
	for (int i = 0; i < length; i++)
	{
		if (Item_Array[i] != src.Item_Array[i]) {
			diff++;
		}
		tmp[i] = Item_Array[i] | src.Item_Array[i];
	}
	if (diff != 2) {
		delete[] tmp;
		return false;
	}
	dest.Item_Array = tmp;
	return true;
}


Column::Column(int I_length, int T_length)
{
	Item_Array = new int[I_length];
	memset(Item_Array, 0, sizeof(int)*I_length);
	T_Array = new int[T_length];
	memset(T_Array, 0, sizeof(int)*T_length);
}

Column::Column()
{
}
