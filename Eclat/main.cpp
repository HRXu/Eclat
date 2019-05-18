#define _CRT_SECURE_NO_WARNINGS
#include "eclat.h"
#include "ECLAT_STL.h"
#include "ECLAT_Read.h"
using namespace std;

int main(int argc,char **args) 
{
	//ECLAT alg(true,2);
	//ECLAT_Read::ReadData(alg,ECLAT_Read::test);

	ECLAT alg(true, 30);
	ECLAT_Read::ReadData(alg, ECLAT_Read::kosarak_Slim);

	//ECLAT alg(false, 30);
	//ECLAT_Read::ReadData(alg, ECLAT_Read::kosarak_Slim);

	//ECLAT alg(false, 1000);
	//ECLAT_Read::ReadData(alg, ECLAT_Read::kosarak);

	alg.Start();
	printf("press any key to continue...");
	getchar();
	return 0;
}