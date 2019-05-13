#define _CRT_SECURE_NO_WARNINGS
#include "eclat.h"
#include "Eclat_A.h"
#include "ECLAT_Read.h"
using namespace std;

int main(int argc,char **args) {
	/*freopen(args[1], "r", stdin);
	Eclat alg;
	alg.Start(true);*/

	ECLAT alg;
	ECLAT_Read::ReadData(alg.Buffer_A,ECLAT_Read::kosarak_Slim);
	return 0;
}