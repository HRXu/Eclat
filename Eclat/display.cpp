#include "display.h"

using namespace std;
void display(map<int, tid> &m) {
	for (auto &it : m) {
		printf("T%d: ", it.first);
		for (auto &it2 : it.second.item_vector) {
			printf("%c ", it2);
		}
		printf("\n");
	}
}

void display(vector<vertical_item> &m) {
	for (auto &it : m) {
		printf("{");

		int len = it.item_set.size();
		int i = 0;
		for (auto &it_i : it.item_set) {
			printf("%c%c", it_i,i!=len-1?',':'}');
			i++;
		}

		for (auto &it_t : it.t_set) {
			printf(" T%d", it_t);
		}
		printf("\n");
	}
}