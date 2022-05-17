#include <iostream>
#include <cstring>
using namespace std;
int main() {
	//1.首先定义一个一维指针数组和二维数组
	char* name[5];
	char a[5][100];
	//2.键盘输入赋值
	for (int i = 0; i < 5; i++) 
	{
		cin >> a[i];
		name[i] = a[i];
	}
	//3.strcmp比较,以此为条件依据进行冒泡排序（条件语句+冒泡排序）
	//冒泡算法
	int pos, bound;
	pos = 4;
	while (pos)
	{
		bound = pos;
		pos = 0;
		for (int j = 0; j < bound; j++)
		{
			if (strcmp(name[j], name[j + 1]) > 0)
			{
				//以字符指针作为中间存储存字符串
				char* t = name[j];
				name[j] = name[j + 1];
				name[j + 1] = t;
				pos = j;
			}
		}
	}
	//4.输出
	for (int i = 0; i < 5; i++)
		cout << name[i] << endl;
	return 0;
}