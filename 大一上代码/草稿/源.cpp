#include <iostream>

using namespace std;

void main()
{

//数组及变量定义;

const int N = 80;

char buffer[N];

int k = 0;

const int NUM = 26;

int counts[NUM] = { 0 };

char letters[NUM];

int i = 0;

do //循环输入每一行字符
{
cout << "enter a string:\n";

cin.getline(buffer, N, '\n'); //获得一 行输入字符串

	k = 0;
	while (buffer[k] != '\0')//对 于输入的每一行字符，统计字符出现的次数
	{
		if (tolower(buffer[k]) >= 'a' && tolower(buffer[k]) <= 'z')
		{
			i = tolower(buffer[k]) - 'a';

			counts[i]++;//counts[tolower( buffer[k])- 'a']++; //用 此行可代替前两句
		}
		k++;
	}
} while (buffer[0] != '\0');
cout << "the statistics result:" <<endl;

for (i = 0; i < NUM; i++)//输出统计结果
{
	letters[i] = (char)('a' + i);
	if (counts[i] > 0)
		cout << letters[i] << " " << counts[i] << endl;
}
}