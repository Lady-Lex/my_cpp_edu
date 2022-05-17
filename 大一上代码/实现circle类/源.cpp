#include<iostream>
using namespace std;
const float PI = 3.14;
class circle
{ public:
	float r(float R);
	float C(float R);
	float S(float R);
  private:
	  float Radius;
};

float circle::r(float R)
{
	Radius = R;
	return Radius;
}
float circle::C(float n)
{
	float C = 2 * PI * Radius;
	return C;
}
float circle::S(float n)
{
	float S = PI * Radius * Radius;
	return S;
}
int main()
{
	float r;
	cin >> r;
	circle a;
	a.r(r);
	a.C(1);
	a.S(1);
	cout << a.C(r) <<' '<< a.S(r) << endl;
}