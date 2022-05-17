#include<iostream>
using namespace std;
int main()
{
	int N;
	cin >> N;
	int* a = new int[N];
	int* b = new int[N];
	int n = 0;
	for (int i = 1; i <= N; i++)
	{
		a[i] = i;
		if (i % 2 != 0)
		{
			b[n] = a[i];
			n = n + 1;
		}
	}
	int j = 0;
	int sum = 0;
	while (j < n)
	{
		sum = sum + b[j];
		j = j + 1;
	}
	cout << sum << endl;
}
