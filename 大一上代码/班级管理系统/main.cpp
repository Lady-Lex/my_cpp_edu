#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
#include"Student.h"
using namespace std;

ofstream ofs;
ifstream ifs;
Student readbase;
//主函数
int main()
{
	int p;            //定义菜单选项序号
	cout << "★☆★☆★☆★☆★☆★欢 迎 来 到 班 级 管 理 系 统 ！☆★☆★☆★☆★☆★☆" << endl;
	do
	{
		int k = 0;          //在接下来的每一种case中，每次调用统计学生总数的返回值都赋给k
		int q = 0;          //作用：参见case 1，第233行
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
			{
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
			}
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