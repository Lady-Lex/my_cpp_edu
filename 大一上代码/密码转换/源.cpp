#include<iostream>
using namespace std;
int main()
{
	int N;
	cin >> N;
	char* arr = new char[N];
	char* arr1 = new char[N];
	for (int k = 0; k < N ;k++)
		cin >> arr[k];
	int n;
	cin >> n;
	
	for (int i = 0; i < N;i++)
	{
		if ((char)n >= 65 + n)
		{
			arr1[i] = arr[i] - (char)n;
		    cout << arr1[i];
	     }
		else
		{
			char m = 90 - n + 1;
			arr1[i] = arr[i] + m;
			cout << arr1[i];
		}
	}
}