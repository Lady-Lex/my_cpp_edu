#include<iostream>
using namespace std;
class ttime
{
public:
	void set(int A, int B, int C);
	void show(int n);
	void show(float n);
private:
	int year;
	int month;
	int day;
};
void ttime::set(int A, int B, int C)
{
	year = A;
	month = B;
	day = C;
}
void ttime::show(int n)
{
	cout << year << '-' << month << '-' << day << endl;
}
void ttime::show(float n)
{
	cout << year << "Äê" << month << "ÔÂ" << day << "ÈÕ" << endl;
}
int main()
{
	int a, b, c;
	ttime tt;
	float d;
	cin >> a >> b >> c >> d;
	tt.set(a, b, c);
	if (d - (int)d == 0)
		tt.show((int)d);
	else
		tt.show(d);
}