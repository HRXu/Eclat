#define _CRT_SECURE_NO_WARNINGS
#include "eclat.h"

using namespace std;
map<int,tid> m_horizonal;
vector<vertical_item> v_vertical;
vector<vertical_item> v_vertical2;

int main(int argc,char **args) {
	freopen(args[1], "r", stdin);

	readin( m_horizonal,v_vertical);
	display(m_horizonal);
	printf("\n");
	display(v_vertical);

	while (1) {
		v_vertical2.clear();
		for (int len = v_vertical.size(), i = 0; i < len; i++) {
			for (int j = i + 1; j < len; j++) {
				intersection_item(v_vertical[i], v_vertical[j], v_vertical2, 2);
			}
		}
		printf("\n");
		display(v_vertical2);
		if (v_vertical2.size() == 0) {
			break;
		}

		v_vertical.clear();
		for (int len = v_vertical2.size(), i = 0; i < len; i++) {
			for (int j = i + 1; j < len; j++) {
				intersection_item(v_vertical2[i], v_vertical2[j], v_vertical, 2);
			}
		}
		printf("\n");
		display(v_vertical);
		if (v_vertical.size() == 0) {	
			break;
		}
	}

	return 0;
}