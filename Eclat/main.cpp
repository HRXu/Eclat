#define _CRT_SECURE_NO_WARNINGS
//#define ENABLE_UX
#include "eclat.h"
#include "ECLAT_Read.h"
using namespace std;

int main(int argc,char **args) 
{
#ifdef ENABLE_UX
	ECLAT alg(true, 30);
	ECLAT_Read::UX();
#else
	ECLAT alg(true,2);
	ECLAT_Read::ReadData(alg,ECLAT_Read::test);

	//ECLAT alg(true, 30);
	//ECLAT_Read::ReadData(alg, ECLAT_Read::k1000);

	//ECLAT alg(false, 30);
	//ECLAT_Read::ReadData(alg, ECLAT_Read::k5000);

	//ECLAT alg(true, 30);
	//ECLAT_Read::ReadData(alg, ECLAT_Read::kosarak_Slim);

	//ECLAT alg(false, 30);
	//ECLAT_Read::ReadData(alg, ECLAT_Read::kosarak_Slim);

	//ECLAT alg(true, 30);
	//ECLAT_Read::ReadData(alg, ECLAT_Read::kosarak);
#endif



	alg.Start();
	printf("press any key to continue...");
	getchar();
	return 0;
}