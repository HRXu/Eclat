#include "ECLAT.h"
#define READ_INT(i) int i;cin>>i
#define MEMSET_0(i,j,k) memset(i,0,sizeof(j)*k)
using namespace std;

void ECLAT::ClearBuffer(std::vector<Column>& Buffer)
{
	for (auto &it : Buffer) {
		delete[] it.Item_Array;
		delete[] it.T_Array;
	}
	Buffer.clear();
}


void ECLAT::Display(const std::vector<Column>& buffer_src)
{
	for (auto &col : buffer_src) {
		printf("{");
		for (int i = 0; i < Item_Count; i++) {
			if (col.Item_Array[i] == 1) {
				printf("%d%c", i, i == Item_Count - 1 ? '\0' : ' ');
			}
			if (i == Item_Count - 1) {
				printf("} ");
			}
		}
		for (int i = 0; i < T_Count; i++) {
			if (col.T_Array[i] == 1) {
				printf("T%d%c",i, i == T_Count - 1 ? '\0' : ' ');
			}
			if (i == T_Count - 1) {
				printf("\n");
			}
		}
	}
}
