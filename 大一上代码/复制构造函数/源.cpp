#include<iostream>
#include<iomanip>
using namespace std;
class a
{
public:
	a(int m);
	a(a& n);
private:
	int b;
};
a::a(int m)
{
	b = m;
	cout << "构造" << endl;
}
a::a(a& n)
{
	b = n.b;
	cout << "复制构造" << endl;
}
a somefunc(a A)
{
	return A;
	cout << "return对象" << endl;
}
int main()
{
	a s(10);
	a t = a(s);
	cout << endl;
	a x = somefunc(s);
}