#include<iostream>
using namespace std;
double max(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j)
{
	double M = a >= b ? a : b;
	M = b >= c ? b : c;
	M = c >= d ? c : d;
	M = d >= e ? d : e;
	M = e >= f ? e : f;
	M = f >= g ? f : g;
	M = g >= h ? g : h;
	M = h >= i ? h : i;
	M = i >= j ? i : j;
	return M;
}
double min(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j)
{
	double m = a <= b ? a : b;
	m = b <= c ? b : c;
	m = c <= d ? c : d;
	m = d <= e ? d : e;
	m = e <= f ? e : f;
	m = f <= g ? f : g;
	m = g <= h ? g : h;
	m = h <= i ? h : i;
	m = i <= j ? i : j;
	return m;
}
int main()
{
	double r[11];
	for (int i = 0; i < 11; i++)
		cin >> r[i];
	int M = max(r[0], r[1], r[2], r[3], r[4], r[5], r[6], r[7], r[8], r[9]);
	int m = min(r[0], r[1], r[2], r[3], r[4], r[5], r[6], r[7], r[8], r[9]);
	if
}