#include<iostream>
using namespace std;
//4.构建一个结构变量，求该日是该年的第几天
struct date
{
	int year;
	int month;
	int day;
};
int leapyear(int x);
int leapyear(int x)//判断是否为闰年
{
	if (((x % 4 == 0) && (x % 100 != 0)) || (x % 400 == 0))
		return 1;
	else
		return 0;
}
int calculate(date a)//计算一年中的第几天
{
	int sum = 0;
	int b[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	int i;
	for (i = 0; i < a.month - 1; i++)
		sum = sum + b[i];
	if (a.month > 2)
		sum = sum + a.day + leapyear(a.year);
	else
		sum = sum + a.day;
	return sum;
}

int main()
{
	date a;
	cout << "请输入年月日" << endl;
	cin >> a.year >> a.month >> a.day;
	int x;
	x = calculate(a);
	cout << "该日是一年中的第" << x << "天" << endl;
	return 0;
}