#include<iostream>
using namespace std;
class rectangle
{
public:
	void set(double L, double W);
	double garea();
private:
	double length;
	double width;
	double area;
};
void rectangle::set(double L, double W)
{
	length = L;
	width = W;
}
double rectangle::garea()
{
	area = length * width;
	return area;
}
double& bigger(double a1, double a2)
{
	if (a1 >= a2)
		return a1;
	else
		return a2;
}
int main()
{
	double L, W;
	cin >> L >> W;
    rectangle r[3];
	r[0].set(5.4,4.3);
	r[1].set(100, 20);
	r[2].set(L, W);
	double a = r[0].garea();
	double b = r[1].garea();
	double c = bigger(a,b);
	double d = r[2].garea();
	cout << bigger(c, d) << endl;
}