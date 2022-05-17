#include<iostream>
using namespace std;
double trans(double x)
{
	double y;
	y = (x - 32) / 1.8;
	return y;
}
int main()
{
	double F,C;
	cin >> F;
	C = trans(F);
	cout << C << endl;
}
