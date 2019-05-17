__kernel void Ex(__global char* A_item,
				__global char* A_T,
				__global char* B_item,
				__global char* B_T,
				__global int* param)
{
	//param[0] :res;
	int res = 0;
	int item_count = param[1];
	int T_count = param[2];

	//int gid = get_local_id(0);
	int gid = get_global_id(0);

	if (gid == 0) {

		int location = 0;
		int s1 = 0;
		char _union;
		for (int i = 0; i < item_count; i++)
		{
			_union = A_item[i] | B_item[i];

			switch (location)
			{
			case 0:
				if (A_item[i] != B_item[i]) {
					location = 1;
				}
				break;
			case 1:
				s1 += _union;
				break;
			}
			B_item[i] = _union;
		}
		if (s1 != 1) {
			param[1] = -1;
			return;
		}
		param[1] = 1;
	}
	else {
		for (int i = 0; i < T_count; i++) {
			B_T[i] &= A_T[i];
			if (B_T[i])res++;
		}
		param[0] = res;
		param[2] = 2;
	}
}

