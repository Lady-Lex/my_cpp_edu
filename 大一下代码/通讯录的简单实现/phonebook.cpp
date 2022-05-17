#include<iostream>
#include<string>
#include"Linklist.cpp"
using namespace std;

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
	void print()                                                            //显示函数
	{
		cout << ID << '\t' << name << '\t' << ch << '\t' << phone << '\t' << addr << endl;
	}
	bool Judge(int n)
	{
		if (ID == n)
			return true;
		else
			return false;
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
