__kernel void Ex(
	__global char* A_item,
	__global char* A_T,
	__global char* B_item,
	__global char* B_T,
	__global int* param,
	const int T_Count,
	const int Item_Count
)
{
	//int gid = get_local_id(0);
	int gid = get_global_id(0);

	int location = 0;
	int s1 = 0;
	char _union;
	int index = gid*Item_Count;
	for (int i = 0; i < Item_Count; i++,index++)
	{
		_union = A_item[i] | B_item[index];
		switch (location)
		{
		case 0:
			if (A_item[i] != B_item[index]) {
				location = 1;
			}
			break;
		case 1:
			s1 += _union;
			break;
		}
		B_item[index] = _union;
	}
	if (s1 != 1) {
		param[gid] = -s1;
		return;
	}


	int res = 0;
	index = gid * T_Count;
	for (int i = 0; i < T_Count; i++, index++) {
		B_T[index] &= A_T[i];
		if (B_T[index])res++;
	}
	param[gid] = res;

}

