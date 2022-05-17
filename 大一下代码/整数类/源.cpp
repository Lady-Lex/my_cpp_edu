#include<iostream>
#include<vector>
using namespace std;

class Int
{
public:
	Int(const int N)
	{
		IntValueA = N;
	};
	Int(const int M, const int N)
	{
		IntValueA = M;
		IntValueB = N;
	};
	int GreatestcommonFactor();                       //求最大公因数函数
	int GreatestcommonFactor(int a, int b);           //求最大公因数函数
	int LeastcommonMultiple();                        //求最小公倍数函数
	void devideFactor();                              //因式分解函数
private:
	int IntValueA;
	int IntValueB;
};

int Int::GreatestcommonFactor()                       //求最大公因数函数
{
	int a = IntValueA;
	int b = IntValueB;
	if (b == 0)
		return a;
	return GreatestcommonFactor(b, a % b);
}

int Int::GreatestcommonFactor(int a, int b)           //求最大公因数函数
{
	if (b == 0)
		return a;
	return GreatestcommonFactor(b, a % b);
}

int Int::LeastcommonMultiple()                        //求最小公倍数函数 
{
	return IntValueA * IntValueB /GreatestcommonFactor(IntValueA, IntValueB);
}

void Int::devideFactor()                              //因式分解函数
{
	vector<int> vec;
	int cinVal = IntValueA;
	int factor = 2;
	int outerCycle = 0;
	int innerCycle = 0;
	cout << "输入的数值为:  " << cinVal << endl;
	for (factor; cinVal > 1 && factor <= sqrt((double)cinVal); factor++)
	{
		outerCycle++;
		while (cinVal > 1 && factor <= cinVal)
		{
			innerCycle++;
			if (cinVal % factor != 0)  break;
			vec.push_back(factor);
			cinVal = cinVal / factor;

		}
	}
	cout << "因式分解的结果为：";
	for (vector<int>::iterator iter = vec.begin(); iter != vec.end(); iter++)
	{
		if ((iter + 1) != vec.end())
		{
			cout << *iter << "*";
		}
		else
		{
			cout << *iter << endl;
		}
	}

}

int main()
{
	cout << "请选择将要执行的操作（填编号）：" << endl;
	cout << "1.求最大公因数" << endl;
	cout << "2.求最小公倍数" << endl;
	cout << "3.因式分解" << endl;
	int t;
	cin >> t;
	if (t == 1)
	{
		cout << "请输入两个整数：" << endl;
		int x, y;
		cin >> x >> y;
		Int t_int(x, y);
		cout << t_int.GreatestcommonFactor();
	}
	else if (t == 2)
	{
		cout << "请输入两个整数：" << endl;
		int x, y;
		cin >> x >> y;
		Int t_int(x, y);
		cout << t_int.LeastcommonMultiple();
	}
	else if (t == 3)
	{
		cout << "请输入一个整数：" << endl;
		int x;
		cin >> x;
		Int t_int(x);
		t_int.devideFactor();
	}
}
