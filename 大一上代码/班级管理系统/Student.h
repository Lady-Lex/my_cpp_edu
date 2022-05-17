#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
using namespace std;
//定义学生类
class Student
{
private:                                 //封装数据，确保安全
	string name;
	long int num;
	string sex;
	long int cclass;
	int cnum;                            //班内序号
	int year;
	float month;
	float day;
	string hometown;
	string room;
	int constellation;                   //星座
	string cconstellation;
public:
	void input();
	void show();
	void save();
	void read();
	int total();
	void fconstellation();
	float birthday();
	double birthymd();

	//直接访问函数族
	long int rnum()
	{
		return num;
	}
	string rname()
	{
		return name;
	}
	int ryear()
	{
		return year;
	}
	string rhometown()
	{
		return hometown;
	}
	string rroom()
	{
		return room;
	}
	string rcconstellation()
	{
		return cconstellation;
	}
};