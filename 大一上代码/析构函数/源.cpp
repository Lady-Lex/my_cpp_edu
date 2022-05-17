#include <iostream>
using namespace std;
class obj
{
private:
	int data;
public:
	obj(int i = 0)
	{
		data = i; cout << "构造\n";
	}
	obj(obj& o)
	{
		data = o.data;
		cout << "拷贝构造\n";
	}
	~obj() 
	{ 
		cout << "析构\n"; 
	}
	int getdata(void)             //分清是用的哪个复制函数
	{
		return data;
	}
};
obj getobj(obj o)
{
	cout << "in getobj\n";
	return o;
}
void main()
{
	obj o2;
	getobj(o2);
	//cout << o1.getdata();
	//cout << endl;
}