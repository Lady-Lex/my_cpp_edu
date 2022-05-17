#include<fstream>
#include<string>
#include<iomanip>
#include"Linklist.cpp"
using namespace std;
static ofstream ofs;
static ifstream ifs;

class PHONEBOOK
{
private:
	int ID;
	string name;
	char ch;
	string phone;
	string addr;
public:
	PHONEBOOK() {}                                                           //默认构造函数
	PHONEBOOK(int id, const char* m_name, char m_ch, const char* m_phone, const char* m_addr) //有参构造函数
	{
		ID = id;
		name = m_name;
		ch = m_ch;
		phone = m_phone;
		addr = m_addr;
	}
	void input()
	{
		cout << "请输入姓名：";       cin >> name;
		cout << "请输入ID号：";       cin >> ID;
		cout << "请输入性别：";       cin >> ch;
		cout << "请输入电话：";       cin >> phone;
		cout << "请输入住址：";       cin >> addr;
	}
	void print()                                                            //显示函数
	{
		cout << name << '\t' << ID << '\t' << ch << '\t' << phone << '\t' << addr << endl;
	}
	int GetID()
	{
		return ID;
	}
	void read()
	{
		ifs >> name >> ID >> ch >> phone >> addr;
	}
	void save()
	{
		ofs << name << '\t' << ID << '\t' << ch << '\t' << phone << '\t' << addr << endl;
	}
	int total()                                //返回值为人数
	{
		auto base = new PHONEBOOK[1000];       //动态申请
		int k = 0;                             //计数器
		ifs.open("data.txt");
		for (int x = 0; x < 100; x++)
		{
			base[x].read();
			if (base[x].name == "\0")          //计数终止条件
				break;
			k = k + 1;
		}
		ifs.close();
		//cout << k;
		return k;
		delete[]base;
	}
	bool operator == (PHONEBOOK& p)
	{
		if (p.ID == ID)
			return true;
		return false;
	}
	PHONEBOOK& operator =(PHONEBOOK& p)
	{
		ID = p.ID;
		name = p.name;
		ch = p.ch;
		phone = p.phone;
		addr = p.addr;
		return*this;
	}
};
