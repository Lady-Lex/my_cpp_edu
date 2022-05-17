#include<iostream>
#include<string>
using namespace std;
int main()
{
	string str;
	cin >> str;
	int m,k=0;
	cin >> m;
	while (str[k] != '\0')
	{
		k = k + 1;
	}
	for (int i = m ; i < k; i++)
	{
		cout << str[i];
	}
	for (int i = 0; i < m; i++)
	{
		cout << str[i];
	}
}