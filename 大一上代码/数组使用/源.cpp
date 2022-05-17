#include<iostream>
#include<stdio.h>
using namespace std;
int main()
{
	int arr[100];
	int i;
	for (i = 0; i < 100; i++)
		arr[i] = i + 1;
	int j = 0;
	while (j < 100)
	{
		for (int k = 0; k < 10; k++)
		{
			if (k < 9)
				cout << arr[j] << " ";
			else
				cout << arr[j];
			j = j + 1;
		}
		cout << endl;
	}
	int n = 0;
	int f = 0;
	int arr1[100];
	for (int a = 0; a < 100; a++)
	{
		f = 0;
		for (int m = 1; m <= a / 2; m++)
		{
			if (a % m == 0)
				f = f + 1;
		}
		if ((f == 1) || (a == 2))
		{
			arr1[n] = arr[a];
			n = n + 1;
		}
	}
	int x = 0;
	while (x < n)
	{
		for (int y = 0; y < 10; y++)
		{
			if (y < 9)
				cout << arr1[x] << " ";
			else
				cout << arr1[x];
			x = x + 1;
			if (x >= n) break;
		}
		cout << endl;
	}
}