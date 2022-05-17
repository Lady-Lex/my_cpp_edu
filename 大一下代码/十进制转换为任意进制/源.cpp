#include<iostream>
using namespace std;

void Convert(int i, int b)
{
	if (i == 0)//µÝ¹é³ö¿Ú 
	{
		return;
	}
	a[cnt++] = i % b;
	Convert(i / b, b);
}