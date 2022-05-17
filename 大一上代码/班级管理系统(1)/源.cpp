#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
using namespace std;
ofstream ofs;
ifstream ifs;

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
//定义基础对象，便于调用统计学生数函数，又避免影响学生对象
Student readbase;


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

//主函数
int main()
{
	int p;            //定义菜单选项序号
	cout << "★☆★☆★☆★☆★☆★欢 迎 来 到 班 级 管 理 系 统 ！☆★☆★☆★☆★☆★☆" << endl;
	do
	{
		int k = 0;          //在接下来的每一种case中，每次调用统计学生总数的返回值都赋给k
		int q = 0;          //作用：参见case1，第233行
		Student* stu = new Student[1000];//定义动态数组，此数组是真正的学生对象数组，每个case结束前都要delete[]stu,打到重置此数组的目的，避免多次运行出现错误
		cout << "★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆\n";
		cout << "☆************************************************************************★\n";
		cout << "★                             班级信息管理系统                           ☆\n";
		cout << "☆                                                                        ★\n";
		cout << "★          1..录入（转入）学生                4.班级学生转出             ☆\n";
		cout << "☆                                                                        ★\n";
		cout << "★          2.查找学生信息                     5.年龄大小计算并排序       ☆\n";
		cout << "☆                                                                        ★\n";
		cout << "★          3.统计班级总人数                   6.判断星座                 ☆\n";
		cout << "☆                                                                        ★\n";
		cout << "★          7.找好友                           8.根据家乡寻找学生         ☆\n";
		cout << "☆************************************************************************★\n";
		cout << "★                               9.退出系统                               ☆\n";
		cout << "☆          ----------------------------------------------------          ★\n";
		cout << "☆************************************************************************★\n";
		cout << "★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆\n" << endl;
		cout << "请输入序号：";    cin >> p;
		if (p != 1 && p != 2 && p != 3 && p != 4 && p != 5 && p != 6 && p != 7 && p != 8 && p != 9)   //判断输入是否有效
		{
			cout << "输入无效！请重新输入！" << endl;
			system("pause");                                  //输入任意键继续
		}
		else
		{
			switch (p)
			{
			case 1:
				cout << "本次录入人数：";     cin >> q;
				k = readbase.total();
				//读入数据
				ifs.open("data.txt");
				for (int x = 0; x < k; x++)
				{
					stu[x].read();            //先读取数据，与新输入的合并
				}
				ifs.close();
				for (int x = k; x < k + q; x++)
				{
					stu[x].input();           //循环输入
				}
				ofs.open("data.txt", ios::out);
				for (int x = 0; x < k + q; x++)
				{
					stu[x].save();            //循环写入
				}
				ofs.close();
				delete[]stu;
				break;

			case 2:
			{
				string A;
				cout << "请输入该学生的姓名或学号：";    cin >> A;
				k = readbase.total();
				ifs.open("data.txt");                          //读入数据
				for (int x = 0; x < k; x++)
				{
					stu[x].read();
				}
				ifs.close();
				for (int x = 0; x < k; x++)
				{
					if (stu[x].rname() == A)                   //判断输入的是否为姓名
					{
						cout << "   姓名            学号       性别         班级      班内序号        生日        家乡   宿舍" << endl;
						stu[x].show();
						cout << "即将返回主菜单！" << endl;
						system("pause");
						break;
					}
					else if (A[1] > 47 && A[1] < 58)           //判断输入的是否为阿拉伯数字
					{
						if (stu[x].rnum() == stoi(A))          //将string A转化为整型并判断
						{
							cout << "   姓名            学号       性别         班级      班内序号        生日        家乡   宿舍" << endl;
							stu[x].show();
							cout << "即将返回主菜单！" << endl;
							system("pause");
							break;
						}
					}
					if (x == k - 1)
					{
						cout << "未找到该学生！即将返回主菜单！" << endl;
						system("pause");
					}
				}
				delete[]stu;
				break;
			}
			case 3:
				cout << "班级总人数：" << readbase.total() << endl;           //直接调用统计函数即可
				cout << "即将返回主菜单！" << endl;
				system("pause");
				break;

			case 4:
			{
				string B;
				cout << "请输入该学生的姓名或学号：" << endl;   cin >> B;
				k = readbase.total();
				//读入数据
				ifs.open("data.txt");
				for (int x = 0; x < k; x++)
				{
					stu[x].read();
				}
				ifs.close();
				for (int x = 0; x < k; x++)
				{
					if (stu[x].rname() == B)
					{
						cout << "请确认学生信息：" << endl;
						cout << "   姓名            学号       性别         班级      班内序号        生日        家乡   宿舍" << endl;
						stu[x].show();
						cout << "正确请输入yes，错误请输入no" << endl;
						string tof;
						cin >> tof;
						if (tof == "yes")
						{
							ofs.open("data.txt", ios::out);
							for (int t = 0; t < k; t++)
							{
								if (t != x)
								{
									stu[t].save();
								}
								else
									continue;
							}
							ofs.close();
							cout << "已完成！及将返回主菜单！" << endl;
							system("pause");
							break;
						}
					}
					else if (B[1] > 47 && B[1] < 58)
					{
						if (stu[x].rnum() == stoi(B))
						{
							cout << "请确认学生信息：" << endl;
							cout << "   姓名            学号       性别         班级      班内序号        生日        家乡   宿舍" << endl;
							stu[x].show();
							cout << "正确请输入yes，错误请输入no" << endl;
							string tof;
							cin >> tof;
							if (tof == "yes")
							{
								ofs.open("data.txt", ios::out);
								for (int t = 0; t < k; t++)
								{
									if (t != x)
									{
										stu[t].save();
									}
									else
										continue;
								}
								ofs.close();
								cout << "已完成！及将返回主菜单！" << endl;
								system("pause");
								break;
							}
							else
							{
								cout << "即将将回到主菜单，请重新选择！" << endl;
								system("pause");
								break;
							}
						}
					}
					if (x == k - 1)
					{
						cout << "未找到该学生！即将返回主菜单！" << endl;
						system("pause");
					}
				}
				delete[]stu;
				break;
			}
			case 5:
			{
				k = readbase.total();
				ifs.open("data.txt");                                     //读入数据
				for (int x = 0; x < k; x++)
				{
					stu[x].read();
				}
				ifs.close();
				int pos, bound;
				class Student hold;
				pos = k;
				while (pos)
				{
					bound = pos;
					pos = 0;
					for (int v = 0; v < bound; v++)
					{
						if (stu[v].birthymd() > stu[v + 1].birthymd())
						{
							hold = stu[v];
							stu[v] = stu[v + 1];
							stu[v + 1] = hold;
							pos = v;
						}
					}
				}
				cout << "年龄由大到小的学生顺序是：" << endl;
				cout << "姓名" << "\t" << "年龄" << endl;
				for (int x = 1; x < k + 1; x++)
				{
					cout << stu[x].rname() << "\t" << 2020 - stu[x].ryear() << endl;
				}
				cout << "排序完成！即将返回主菜单！" << endl;
				system("pause");
				delete[]stu;
				break;
			}

			case 6:
			{
				string C;
				cout << "请输入该学生的姓名或学号：";    cin >> C;
				k = readbase.total();
				ifs.open("data.txt");                                         //读入数据
				for (int x = 0; x < k; x++)
				{
					stu[x].read();
				}
				ifs.close();
				for (int x = 0; x < k; x++)
				{
					if (stu[x].rname() == C)
					{
						stu[x].fconstellation();
						cout << "该学生的星座是：" << stu[x].rcconstellation() << endl;
						cout << "即将返回主菜单！" << endl;
						system("pause");
						break;
					}
					else if (C[1] > 47 && C[1] < 58)
					{
						if (stu[x].rnum() == stoi(C))
						{
							stu[x].fconstellation();
							cout << "该学生的星座是：" << stu[x].rcconstellation() << endl;
							cout << "即将返回主菜单！" << endl;
							system("pause");
							break;
						}
					}
					if (x == k - 1)
					{
						cout << "未找到该学生！即将返回主菜单！" << endl;
						system("pause");
					}
				}
				delete[]stu;
				break;
			}
			case 7:
			{
				string D;
				cout << "请输入该学生的姓名或学号：";    cin >> D;
				int u;
				k = readbase.total();
				//读入数据
				ifs.open("data.txt");
				for (int x = 0; x < k; x++)
				{
					stu[x].read();
				}
				ifs.close();
				for (int x = 0; x < k; x++)
				{
					if (stu[x].rname() == D)
					{
						cout << "请输入好友类型：" << '\n' << "1.同家乡" << '\n' << "2.同星座" << '\n' << "3.同宿舍" << '\n' << "请输入序号" << endl;
						cin >> u;

						switch (u)
						{
						case 1:
						{
							cout << "和该学生家乡相同的有：" << endl;
							int w = 0;                                   //用于判断是否没有相同的人，case1、2、3中均使用类似变量
							for (int y = 0; y < k; y++)
							{
								if (y != x)
								{
									if (stu[y].rhometown() == stu[x].rhometown())
									{
										cout << stu[y].rname() << endl;
										w = w + 1;
									}
								}
								else
									continue;
								if (y == k - 1)
								{
									if (w == 0)
									{
										cout << "无!即将返回主菜单！" << endl;
										system("pause");
									}
									else
									{
										cout << "查找完毕！即将返回主菜单！" << endl;
										system("pause");
									}
								}
							}
							break;
						}
						case 2:
						{
							stu[x].fconstellation();
							cout << "和该学生同星座的有：" << endl;
							int w = 0;
							for (int y = 0; y < k; y++)
							{
								stu[y].fconstellation();
								if (y != x)
								{
									if (stu[y].rcconstellation() == stu[x].rcconstellation())
									{
										cout << stu[y].rname() << endl;
										w = w + 1;
									}
								}
								else
									continue;
								if (y == k - 1)
								{
									if (w == 0)
									{
										cout << "无!即将返回主菜单！" << endl;
										system("pause");
									}
									else
									{
										cout << "查找完毕！即将返回主菜单！" << endl;
										system("pause");
									}
								}
							}
							break;
						}
						case 3:
						{
							cout << "和该学生住同一宿舍的有：" << endl;
							int w = 0;
							for (int y = 0; y < k; y++)
							{
								if (y != x)
								{
									if (stu[y].rroom() == stu[x].rroom())
									{
										cout << stu[y].rname() << endl;
										w = w + 1;
									}
								}
								else
									continue;
								if (y == k - 1)
								{
									if (w == 0)
									{
										cout << "无!即将返回主菜单！" << endl;
										system("pause");
									}
									else
									{
										cout << "查找完毕！即将返回主菜单！" << endl;
										system("pause");
									}
								}
							}
							break;
						}
						}
						break;
					}
					else if (D[1] > 47 && D[1] < 58)
					{
						if (stu[x].rnum() == stoi(D))
						{
							cout << "请输入好友类型：" << '\n' << "1.同家乡" << '\n' << "2.同星座" << '\n' << "3.同宿舍" << '\n' << "请输入序号" << endl;
							cin >> u;

							switch (u)
							{
							case 1:
							{
								cout << "和该学生家乡相同的有：" << endl;
								int w = 0;
								for (int y = 0; y < k; y++)
								{
									if (y != x)
									{
										if (stu[y].rhometown() == stu[x].rhometown())
										{
											cout << stu[y].rname() << endl;
											w = w + 1;
										}
									}
									else
										continue;
									if (y == k - 1)
									{
										if (w == 0)
										{
											cout << "无!即将返回主菜单！" << endl;
											system("pause");
										}
										else
										{
											cout << "查找完毕！即将返回主菜单！" << endl;
											system("pause");
										}
									}
								}
								break;//内case 1
							}
							case 2:
							{
								stu[x].fconstellation();
								cout << "和该学生同星座的有：" << endl;
								int w = 0;
								for (int y = 0; y < k; y++)
								{
									stu[y].fconstellation();
									if (y != x)
									{
										if (stu[y].rcconstellation() == stu[x].rcconstellation())
										{
											cout << stu[y].rname() << endl;
											w = w + 1;
										}
									}
									else
										continue;
									if (y == k - 1)
									{
										if (w == 0)
										{
											cout << "无!即将返回主菜单！" << endl;
											system("pause");
										}
										else
										{
											cout << "查找完毕！即将返回主菜单！" << endl;
											system("pause");
										}
									}
								}
								break;//内case 2
							}
							case 3:
							{
								cout << "和该学生住同一宿舍的有：" << endl;
								int w = 0;
								for (int y = 0; y < k; y++)
								{
									if (y != x)
									{
										if (stu[y].rroom() == stu[x].rroom())
										{
											cout << stu[y].rname() << endl;
											w = w + 1;
										}
									}
									else
										continue;
									if (y == k - 1)
									{
										if (w == 0)
										{
											cout << "无!即将返回主菜单！" << endl;
											system("pause");
										}
										else
										{
											cout << "查找完毕！即将返回主菜单！" << endl;
											system("pause");
										}
									}
								}
								break;//内case 3
							}
							}
						}
						break;
					}
					if (x == k - 1)
					{
						cout << "未找到该学生！即将返回主菜单！" << endl;
						system("pause");
					}
				}
				delete[]stu;
				break;
			}
			case 8:
			{
				string E;
				cout << "请输入家乡地址：";    cin >> E;
				k = readbase.total();                                          //读入数据
				ifs.open("data.txt");
				for (int x = 0; x < k; x++)
				{
					stu[x].read();
				}
				ifs.close();
				cout << "家乡是" << E << "的学生有：" << endl;
				int w = 0;
				for (int x = 0; x < k; x++)
				{
					if (stu[x].rhometown() == E)
					{
						cout << stu[x].rname() << endl;
						w = w + 1;
					}
					if (x == k - 1)
					{
						if (w == 0)
						{
							cout << "无!即将返回主菜单！" << endl;
							system("pause");
						}
						else
						{
							cout << "查找完毕！即将返回主菜单！" << endl;
							system("pause");
						}
					}
				}
				break;
			}
			case 9:
				cout << "★☆★☆★☆★☆★☆★☆★☆★☆★☆再 见★☆★☆★☆★☆★☆★☆★☆★☆★☆";        //!!!∑(ﾟДﾟノ)ノ
				break;
			}
		}
	} while (p != 9);                     //do-while结构用于实现在一个命令行窗口内多次运行主菜单
}