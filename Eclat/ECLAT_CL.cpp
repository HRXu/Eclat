#include "ECLAT.h"
using namespace std;
int ECLAT::CL_Process()
{
	while (true)
	{
		if (UsingA) {
			int cnt = Buffer_A.size();
			if (cnt == 0)break;
			_CL_ProcessA(Buffer_A, Buffer_B, cnt);
		}
		else {
			int cnt = Buffer_B.size();
			if (cnt == 0)break;
			_CL_ProcessA(Buffer_B, Buffer_A, cnt);
		}
		UsingA = !UsingA;
	}
	return 0;
}
void ECLAT::_CL_ProcessA(vector<Column> &source, vector<Column> &destination, int cnt)
{
	ClearBuffer(destination);
	for (int i = 0; i < cnt; i++) {
		cl_factory.WriteBufferA(source[i].T_Array, this->T_Count);
		cl_factory.WriteBufferE(source[i].Item_Array, this->Item_Count);
		for (int j = i + 1; j < cnt; j++) {
			if (source[i].CanIntersectWith(source[j], this->Item_Count)) {
				Column* tmp = new Column(this->Item_Count, this->T_Count);

				cl_factory.WriteBufferB(source[j].T_Array, this->T_Count);
				cl_factory.WriteBufferF(source[j].Item_Array, this->Item_Count);
				int res = CL_Intersect(source[i], source[j], *tmp);
				if (res >= Threshold)
					destination.push_back(*tmp);
				else {
					delete[] tmp->Item_Array;
					delete[] tmp->T_Array;
					delete tmp;
				}
			}
		}
	}
	printf("Turn#:\n");
	Display(destination);
}
int ECLAT::CL_Intersect(Column & col1, Column & col2, Column & dest)
{
	cl_factory.Run(dest.Item_Array, Item_Count, dest.T_Array, T_Count);
	int res = 0;
	for (int i = 0; i < T_Count; i++) {
		res += dest.T_Array[i];
	}
	return res;
}