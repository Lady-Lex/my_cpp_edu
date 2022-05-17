#include<iostream>
using namespace std;
int main()
{
	int n;
	cin >> n;
	while ( n != 1)
	{
		if (n % 2 == 0)
		{
			n = n / 2;
			cout << 2 * n << '/' << '2' << '=' << n << endl;
		}
		else
		{
			cout << n;
			n = n * 3 + 1;
			cout << "*3+1=" << n << endl;
		}
	}
}