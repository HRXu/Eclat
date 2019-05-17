__kernel void ve_intersect(__global bool* A, __global bool* B, __global bool* C)
{  
    int idx=get_global_id(0);
    C[idx]=A[idx] & B[idx];
}																	 
__kernel void ve_union(__global bool* A, __global bool* B, __global bool* C)
{
	int idx=get_global_id(0);
	C[idx]=A[idx] | B[idx];
}

__kernel void Ex(__global bool* A_item,
				__global bool* A_T,
				__global bool* B_item,
				__global bool* B_T,
				__global int* param)
{
	//param[0] :res;
	int res=0;
	int item_count=param[1];
	int T_count=param[2];

	bool flag = false;

	int location = 0;
	for (int i = 0; i < item_count; i++)
	{
		switch (location)
		{
		case 0:
			if (A_item[i] != B_item[i])
				location = 1;
			break;
		case 1:
			if (A_item[i] != B_item[i])
				location = 2;
			break;
		case 2:
			if ((A_item[i] | B_item[i]))
				location = 3;
			break;
		case 3:
			break;
		}
		if (i == (length - 1) && location != 2) {
			param[0] = -1;
			return;
		}
	}


	for(int i=0;i<item_count;i++){
		B_item[i] |= A_item[i];
	}

	for(int i=0;i<T_count;i++){
		B_T[i] &= A_T[i];
		if(B_T[i])res++;
	}

	param[0]=res;
}