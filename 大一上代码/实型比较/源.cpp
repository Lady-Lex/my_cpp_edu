#include<iostream>
using namespace std;
void main()
{
	const float EPS = 1e-6;
    float a = 0.1, b = 0.0;
    for (int i = 0; i < 10; i++)
    {
	    b = b + 0.01;
	    cout << b << endl;
    }
    if (fabs(a - b) < EPS)
    {
        cout << "相等" << endl;
    }
    else
    {
        cout << "不相等" << endl;
    }
}

