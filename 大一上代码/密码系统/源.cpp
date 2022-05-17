#include <iostream>
using namespace std;
void main()
{
	int i;
	for (i = 0; i < 3; i++)
	{
		cout << "请输入6位数字的密码:";
		int n;
		cin >> n;
		if (n == 111111)
		{
			cout << "欢迎使用财会报表程序" << endl;
			break;
		}
		else if (i < 2)
			cout << "密码错误，重新输入! （剩余次数：" << 2 - i << "次！）" << endl;
	}
	if (i == 3)
		cout << "拒绝使用财会报表软件！" << endl;
}
