#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
#include"Student.h"
using namespace std;

extern ofstream ofs;
extern ifstream ifs;
//定义基础对象，便于调用统计学生数函数，又避免影响学生对象
extern Student readbase;

//1.输入（input）函数（充当构造函数的作用）
void Student::input()
{
	cout << "\t请输入姓名：";       cin >> name;
	cout << "\t请输入学号：";       cin >> num;
	cout << "\t请输入性别：";       cin >> sex;
	cout << "\t请输入班级：";       cin >> cclass;
	cout << "\t请输入班内序号：";   cin >> cnum;
	cout << "\t请输入生日：";       cin >> year >> month >> day;
	cout << "\t请输入家乡：";       cin >> hometown;
	cout << "\t请输入宿舍：";       cin >> room;
}

//2.show函数
void Student::show()
{
	cout << name << "\t" << num << "\t" << sex << "\t" << cclass << "\t" << cnum << "\t" << year << "年" << month << "月" << day << "日" << "\t" << hometown << "\t" << room
		<< endl;
}

//3.读取数据函数
void Student::read()
{
	ifs >> name >> num >> sex >> cclass >> cnum >> year >> month >> day >> hometown >> room;
}

//4.保存数据函数
void Student::save()
{
	ofs << name << "\t" << num << "\t" << sex << "\t" << cclass << "\t" << cnum << "\t" << year << "\t" << month << "\t" << day << "\t" << hometown << "\t" << room << endl;
}

//5.统计班内学生总数函数
int Student::total()                       //返回值为学生总数
{
	Student* base = new Student[1000];     //动态申请
	int k = 0;                             //统计总数的变量
	ifs.open("data.txt");
	for (int x = 0; x < 100; x++)
	{
		base[x].read();
		if (base[x].name == "\0")          //计数终止条件
			break;
		k = k + 1;
	}
	ifs.close();
	return k;
	delete[]base;
}

//6.生日数据转换函数（只包含月和日，用于判断星座）
float Student::birthday()
{
	float M = month;
	float D = day;
	float B = M + 0.01 * D;
	return B;
}

//7.生日数据转换函数(含年份，用于比较年龄大小）
double Student::birthymd()
{
	double Y = year;
	double M = month;
	double D = day;
	double R = Y + 0.01 * M + 0.0001 * D;
	return R;
}

//8.求星座函数
void Student::fconstellation()
{
	enum econstellation { 白羊座, 金牛座, 双子座, 巨蟹座, 狮子座, 处女座, 天秤座, 天蝎座, 射手座, 摩羯座, 水瓶座, 双鱼座 };
	readbase.total();
	econstellation s = 白羊座;             //初始化枚举变量
	string ch;
	float A;
	A = birthday();
	if (A > 3.20 && A < 4.21)
	{
		s = 白羊座; ch = "白羊座";
	}
	else if (A > 4.20 && A < 5.22)
	{
		s = 金牛座; ch = "金牛座";
	}
	else if (A > 5.21 && A < 6.22)
	{
		s = 双子座; ch = "双子座";
	}
	else if (A > 6.21 && A < 7.23)
	{
		s = 巨蟹座; ch = "巨蟹座";
	}
	else if (A > 7.22 && A < 8.24)
	{
		s = 狮子座; ch = "狮子座";
	}
	else if (A > 8.23 && A < 9.24)
	{
		s = 处女座; ch = "处女座";
	}
	else if (A > 9.23 && A < 10.24)
	{
		s = 天秤座; ch = "天秤座";
	}
	else if (A > 10.23 && A < 11.23)
	{
		s = 天蝎座; ch = "天蝎座";
	}
	else if (A > 11.22 && A < 12.22)
	{
		s = 射手座; ch = "射手座";
	}
	else if (A > 12.21 && A < 12.32 || A>1.0 && A < 1.21)
	{
		s = 摩羯座; ch = "摩羯座";
	}
	else if (A > 1.20 && A < 2.20)
	{
		s = 水瓶座; ch = "水瓶座";
	}
	else if (A > 2.19 && A < 3.21)
	{
		s = 双鱼座; ch = "双鱼座";
	}
	constellation = s;                     //学生类中星座的值由这里赋值
	cconstellation = ch;
}