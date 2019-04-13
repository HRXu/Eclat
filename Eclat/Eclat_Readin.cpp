#include "eclat.h"
#define READ_INT(i) int i;cin>>i
#define MEMSET_0(i,j,k) memset(i,0,sizeof(j)*k)
using namespace std;
//���룬ת��Ϊ��ֱ��
void Eclat::Readin()
{
	cin >> this->T_Count>>this->Item_Count>>this->Threshold;

	this->Items = new string[Item_Count];
	for (int i = 0; i < Item_Count; i++)
	{
		cin >> this->Items[i];
		Name_map[this->Items[i]] = i;
	}

	//��������
	bool** matrix=new bool*[T_Count];
	for (int i = 0; i < Item_Count; i++) {
		matrix[i] = new bool[Item_Count];
		MEMSET_0(matrix[i], bool, Item_Count);
	}
	for (int i = 0; i < T_Count; i++)
	{
		READ_INT(j);
		for (int k = 0; k < j; k++)
		{
			string tmp;
			cin >> tmp;

			int d = Name_map[tmp];
			matrix[i][d] = true;
		}
	}

	//ת��Ϊ��ֱ��
	Buffer_A.resize(Item_Count);
	for (int i = 0; i < Item_Count; i++)
	{
		Buffer_A[i].Item_Array = new int[this->Item_Count];
		Buffer_A[i].T_Array = new int[this->T_Count];

		Buffer_A[i].Item_Array[i] = 1;
		for (int j = 0; j < T_Count; j++)
		{
			Buffer_A[i].T_Array[j] = matrix[j][i];
		}
	}


	//���տռ�
	for (int i = 0; i < T_Count; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
}

void Eclat::Display(const std::vector<Column>& buffer_src)
{
	for (auto &col : buffer_src) {
		if (!col.IsVaild) continue;
		printf("{");
		for (int i = 0; i < Item_Count; i++) {
			if (col.Item_Array[i] == 1) {
				printf("%d%c", i == Item_Count - 1 ? '}' : ',');
			}
		}
		printf(" ");
		for (int i = 0; i < T_Count; i++) {
			if (col.T_Array[i] == 1) {
				printf("T%d%c", i == Item_Count - 1 ? '\n' : ',');
			}
		}
	}
}
