#include "ECLAT.h"
using namespace std;

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
