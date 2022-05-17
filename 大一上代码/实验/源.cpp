#include<iostream>
using namespace std;

int main()
{
	int b = 1;
	int c = b++ * b++;
	cout << c << endl;
	cout << b++ << b << b++ << b << endl;
	cout << b << endl;
}