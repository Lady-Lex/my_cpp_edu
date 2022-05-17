#include<iostream>
#include<ctime>
#include<iomanip>
using namespace std;
int main()
{
	int N;
	cin >> N;
	int matrix[100][100];
	int tMatrix[100][100];
	int i, j;
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
		{
			cin >> matrix[i][j];
		}
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			tMatrix[i][j] = matrix[j][i];
			if (j < N - 1)
				cout << tMatrix[i][j] << " ";
			else
				cout << tMatrix[i][j];
		}
		cout << endl;
	}
}
