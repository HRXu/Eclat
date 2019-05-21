#include "ECLAT.h"
#define MEMSET_0(i,j,k) memset(i,0,sizeof(j)*k)
using namespace std;
void ECLAT::Start()
{
	if (UseAccerlate) {
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

	if (UseAccerlate) {
		cl_factory.Init();
		printf("please confirm the Device info\n");
		printf("Work size:%d\n", WORK_SIZE);
	}
	//getchar();
}

void ECLAT::Reduce()
{
}