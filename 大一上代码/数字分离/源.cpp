#include<iostream>
using namespace std;
int a1, a2, b1, b2, c1, c2, d1, d2;
int fun(int x,int y)  //函数一
{
	double z = x / y;
	return (int)z;
}
int g(int x, int y)  //函数二
{
	int z = x % y;
	return z;
}
int di(int x)  //函数三
{
	a1 = fun(x, 10000); a2 = g(x, 10000);
	b1 = fun(a2, 1000); b2 = g(a2, 1000);
	c1 = fun(b2, 100); c2 = g(b2, 100);
	d1 = fun(c2, 10); d2 = g(c2, 10);
	return a1, b1, c1, d1, d2;
}
int main()
{
	int m,n;
	cin >> m;
	di(m);
	int s[5];
	s[0] = a1; s[1] = b1; s[2] = c1; s[3] = d1; s[4] = d2;
	for (int i = 0; i < 5; i++)
	{
		if (s[i] == 0) continue;
		else
			for(int j=i;j<5;j++)
		    {
			    if (j != 4)
				   cout << s[j] << " ";
			    else
				   cout << s[j] << endl;
		    }
		break;
	}
}