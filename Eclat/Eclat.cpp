#include "eclat.h"
#define MEMSET_0(i,j,k) memset(i,0,sizeof(j)*k)
using namespace std;
void Eclat::Start()
{
	this->Readin();
	this->Process();
}

int Eclat::Process()
{
	while (true)
	{
		if (UsingA) {
			int cnt = Buffer_A.size();
			if (cnt == 0) break;
			ClearBuffer(Buffer_B);

			for (int i = 0; i < cnt; i++) {
				for (int j = i + 1; j < cnt; j++) {			
					Column* tmp = new Column(this->Item_Count, this->T_Count);
					if (Buffer_A[i].CanIntersection(Buffer_A[j], *tmp, this->Item_Count)) {
						int res=Buffer_A[i].Intersection(Buffer_A[j], *tmp, this->T_Count);
						if(res>=Threshold)
							Buffer_B.push_back(*tmp);
					}
					//else {
					//	delete[] tmp->Item_Array;
					//	delete[] tmp->T_Array;
					//	delete tmp;
					//}
				}
			}

			Display(Buffer_B);
		}
		else {
			int cnt = Buffer_B.size();
			if (cnt == 0) break;
			ClearBuffer(Buffer_A);


			for (int i = 0; i < cnt; i++) {
				for (int j = i + 1; j < cnt; j++) {
					Column* tmp = new Column(this->Item_Count, this->T_Count);
					if (Buffer_B[i].CanIntersection(Buffer_B[j], *tmp, this->Item_Count)) {
						int res=Buffer_B[i].Intersection(Buffer_B[j], *tmp, this->T_Count);
						if(res>=Threshold)
							Buffer_A.push_back(*tmp);
					}
					//else {
					//	delete[] tmp->Item_Array;
					//	delete[] tmp->T_Array;
					//	delete tmp;
					//}
				}
			}

			Display(Buffer_A);
		}
		UsingA = !UsingA;
	}
	return 0;
}



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
		tmp[i]=Item_Array[i] | src.Item_Array[i];
	}
	if (diff != 2) {
		delete[] tmp;
		return false;
	}
	dest.Item_Array = tmp;
	return true;
}

int Column::Intersection(Column & src,Column &dest,int length)
{
	int res = 0;
	for (int i = 0; i < length; i++) {
		dest.T_Array[i] = this->T_Array[i] & src.T_Array[i];
		res += dest.T_Array[i];
	}
	return res;
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
