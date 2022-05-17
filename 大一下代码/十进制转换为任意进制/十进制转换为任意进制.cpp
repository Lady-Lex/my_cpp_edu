//最大支持36进制


#include<iostream>
#include<string>

using namespace std;

char digit[] = { '0','1','2','3', '4','5', '6','7', '8','9',
				 'A','B','C','D', 'E','F', 'G','H', 'I','J',
				 'K','L','M','N', 'O','P', 'Q','R', 'S','T',
				 'U','V','W','X', 'Y','Z' };


int main()
{
	unsigned int src, count;
	cout << "输入要转换的十进制数：";
	cin >> src;
	cout << endl;
	cout << "输入要转换进制：";
	cin >> count;
	cout << endl;
	//
	unsigned int  tmp, tmp_src = src;
	string res;
	while (tmp_src)
	{
		tmp = tmp_src % count;
		tmp_src /= count;
		res = digit[tmp] + res;
	}

	cout << "将十进制数 " << src << " 转换为 " << count << " 进制数为：" << res << endl;

	return 0;
}
