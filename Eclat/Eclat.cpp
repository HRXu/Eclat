#include "ECLAT.h"
#define MEMSET_0(i,j,k) memset(i,0,sizeof(j)*k)
using namespace std;
void ECLAT::Start()
{
	if (UseAccerlate) {
		string s = "__kernel void ve_intersect(__global bool* A, __global bool* B, __global bool* C)\n"
			"{                                                                        \n"
			"    int idx=get_global_id(0);                                            \n"
			"    C[idx]=A[idx] & B[idx];                                              \n"
			"}                                                                  \n"
			;
		cl_factory.Init(cl_factory.platforms[0]);
		cl_factory.Complie(s, this->T_Count);
		this->CL_Process();
	}
	else {
		this->Process();
	}
}

ECLAT::ECLAT(bool isAccerlate, int threshold)
{
	this->UseAccerlate = isAccerlate;
	this->Threshold = threshold;
}

void ECLAT::Reduce()
{
}

int ECLAT::Process()
{
	while (true)
	{
		if (UsingA) {
			int cnt = Buffer_A.size();
			if (cnt == 0)break;
			_ProcessA(Buffer_A, Buffer_B,cnt);
		}
		else {
			int cnt = Buffer_B.size();
			if (cnt == 0)break;
			_ProcessA(Buffer_B, Buffer_A, cnt);
		}
		UsingA = !UsingA;
	}
	return 0;
}
void ECLAT::_ProcessA(vector<Column> &source, vector<Column> &destination,int cnt)
{
	ClearBuffer(destination);
	for (int i = 0; i < cnt; i++) {
		for (int j = i + 1; j < cnt; j++) {
			if (source[i].CanIntersectWith(source[j], this->Item_Count)) {
				Column* tmp = new Column(this->Item_Count, this->T_Count);
				int res = Intersect(source[i], source[j], *tmp);
				if (res >= Threshold)
					destination.push_back(*tmp);
				else {
					delete[] tmp->Item_Array;
					delete[] tmp->T_Array;
				}
				delete tmp;
			}
		}
	}
	printf("Turn#:\n");
	Display(destination);
}

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

		for (int j = i + 1; j < cnt; j++) {
			if (source[i].CanIntersectWith(source[j], this->Item_Count)) {
				Column* tmp = new Column(this->Item_Count, this->T_Count);

				cl_factory.WriteBufferB(source[j].T_Array, this->T_Count);
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

//�󽻲���
int ECLAT::Intersect(Column & col1, Column & col2, Column & dest)
{
	int res = 0;
	for (int i = 0; i < Item_Count; i++) {
		dest.Item_Array[i] = col1.Item_Array[i] | col2.Item_Array[i];
	}
	for (int i = 0; i < T_Count; i++) {
		dest.T_Array[i] = col1.T_Array[i] & col2.T_Array[i];
		res += dest.T_Array[i];
	}
	return res;
}
int ECLAT::CL_Intersect(Column & col1, Column & col2, Column & dest)
{
	int res = 0;
	for (int i = 0; i < Item_Count; i++) {
		dest.Item_Array[i] = col1.Item_Array[i] | col2.Item_Array[i];
	}

	cl_factory.Run(dest.T_Array,T_Count);
	for (int i = 0; i < T_Count; i++) {
		res += dest.T_Array[i];
	}
	return res;
}

