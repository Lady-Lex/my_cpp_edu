#include <iostream>
#include <vector>
#include <stack>
#include <string>
using namespace std;

class Solution 
{
public:
	void ConvertRes(stack<char>& s, __int64 n, int base);
	void ConvertIteration(stack<char>& s, __int64 n, int base);
};

int main()
{
	Solution sol;
	stack<char> s;
	int num = 0;//十进制
	int sys = 0;//转换后的进制
	cin >> num >> sys;
	sol.ConvertRes(s, num, sys);
	while (!s.empty())
	{
		cout << s.top();
		s.pop();
	}
	cout << endl;
	system("pause");
	return 0;
}

//递归实现
void Solution::ConvertRes(stack<char>& s, __int64 n, int base)
{
	const char digit[] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };//新进制下的数位
	if (n > 0)//直到n->0
	{
		s.push(digit[n % base]);//存入
		ConvertRes(s, n / base, base);//第二个参数十进制数更新，通过递归得到所有更高位
	}
}

//迭代实现
void Solution::ConvertIteration(stack<char>& s, __int64 n, int base)
{
	const char digit[] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };//新进制下的数位
	while (n > 0)
	{
		int remainder = int(n % base);
		s.push(digit[remainder]);
		n /= base;
	}
}