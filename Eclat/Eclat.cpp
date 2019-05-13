#include "ECLAT.h"
#define MEMSET_0(i,j,k) memset(i,0,sizeof(j)*k)
using namespace std;
void ECLAT::Start()
{
	if (UseAccerlate) {
		string s = "__kernel void vecadd(__global bool* A, __global bool* B, __global bool* C)\n"
			"{                                                                        \n"
			"    int idx=get_global_id(0);                                            \n"
			"    C[idx]=A[idx] & B[idx];                                              \n"
			"}                                                                        \n"
			;
		cl_factory.Init(cl_factory.platforms[0]);
		cl_factory.Complie(s, this->T_Count);
		this->Process_cl_ver();
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

int ECLAT::Process()
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
					if (Buffer_A[i].CanIntersectWith(Buffer_A[j], *tmp, this->Item_Count)) {
						int res=Intersect(Buffer_A[i],Buffer_A[j], *tmp, this->T_Count);
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


			for (int i = 0; i < cnt; i++) 
			{
				for (int j = i + 1; j < cnt; j++) 
				{
					Column* tmp = new Column(this->Item_Count, this->T_Count);

					if (Buffer_B[i].CanIntersectWith(Buffer_B[j], *tmp, this->Item_Count)) 
					{
						int res=Intersect(Buffer_B[i],Buffer_B[j], *tmp, this->T_Count);
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

int ECLAT::Process_cl_ver()
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
					if (Buffer_A[i].CanIntersectWith(Buffer_A[j], *tmp, this->Item_Count)) {
						int res = Intersect_cl_ver(Buffer_A[i], Buffer_A[j], *tmp, this->T_Count);
						if (res >= Threshold)
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
					if (Buffer_B[i].CanIntersectWith(Buffer_B[j], *tmp, this->Item_Count)) {
						int res = Intersect_cl_ver(Buffer_B[i], Buffer_B[j], *tmp, this->T_Count);
						if (res >= Threshold)
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
//Çó¼¯
int ECLAT::Intersect(Column & col1, Column & col2, Column & dest, int length)
{
	int res = 0;
	for (int i = 0; i < length; i++) {
		dest.T_Array[i] = col1.T_Array[i] & col2.T_Array[i];
		res += dest.T_Array[i];
	}
	return res;
}
int ECLAT::Intersect_cl_ver(Column & col1, Column & col2, Column & dest, int length)
{
	int res = 0;
	cl_factory.Run(col1.T_Array, col2.T_Array, dest.T_Array, length);
	for (int i = 0; i < length; i++) {
		//dest.T_Array[i] = this->T_Array[i] & src.T_Array[i];
		res += dest.T_Array[i];
	}
	return res;
}

