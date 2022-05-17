//注：通讯录的个人信息被曝存在文本文件中，需要操作时，以单链表的形式对信息管理
#include<fstream>
#include<string>
#include<iomanip>
#include<ctime>
#include"Linklist.cpp"
#include"phonebook.cpp"
using namespace std;

PHONEBOOK readbase;

int main()
{
	int p;                                                                       //定义菜单选项序号
	LinkList<PHONEBOOK>List;
	cout << "★☆★☆★☆★☆★☆★欢 迎 来 到 通讯录 管 理 系 统 ！☆★☆★☆★☆★☆★☆" << endl;
	do
	{
		int k = 0;                                           //在接下来的每一种case中，每次调用统计学生总数的返回值都赋给k
		PHONEBOOK* pbook = new PHONEBOOK[1000];
		cout << "★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆\n";
		cout << "☆************************************************************************★\n";
		cout << "★                              通讯录管理系统                            ☆\n";
		cout << "☆                                                                        ★\n";
		cout << "★          1.头插法构造新通讯录               5.查询个人信息             ☆\n";
		cout << "☆                                                                        ★\n";
		cout << "★          2.尾插法构造新通讯录               6.获取当前人数             ☆\n";
		cout << "☆                                                                        ★\n";
		cout << "★          3.增加个人信息                     7.销毁通讯录               ☆\n";
		cout << "☆                                                                        ★\n";
		cout << "★          4.删除个人记录                     8.退出系统                 ☆\n";
		cout << "☆                                                                        ★\n";
		cout << "★************************************************************************☆\n";
		cout << "☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★\n" << endl;
		cout << "请输入序号：";    cin >> p;
		if (p != 1 && p != 2 && p != 3 && p != 4 && p != 5 && p != 6 && p != 7 && p != 8 && p != 9)   //判断输入是否有效
		{
			cout << "输入无效！请重新输入！" << endl;
			system("pause");                                                      //输入任意键继续
		}
		else
		{
			switch (p)
			{
			case 1:
			{
				k = readbase.total();
				ifs.open("data.txt");                                                    //读入数据
				for (int x = 0; x < k; x++)
				{
					pbook[x].read();            
				}
				ifs.close();
				List.setLinkList(pbook, k);
				//cout << List.GetLength() << endl;
				cout << "已用头插法初始化通讯录！" << endl;
				delete[]pbook;
				system("pause");
				break;
			}
			case 2:
			{
				k = readbase.total();
				ifs.open("data.txt");                                                    //读入数据
				for (int x = 0; x < k; x++)
				{
					pbook[x].read();
				}
				ifs.close();
				List.setLinkList(k, pbook);
				//cout << "已用尾插法初始化通讯录！" << endl;
				delete[]pbook;
				system("pause");
				break;
			}
			case 3:
			{
				int q = 0;                      //作用：参见case 1
				cout << "请输入插入到链表的第i个位置（1<=i<=" << List.GetLength()-1 << "）：" << endl;     cin >> q;
				pbook[0].input();          
				ofs.open("data.txt", ios_base::app);
				pbook[0].save();           
				ofs.close();
				List.Insert(q, pbook[k + 1]);
				delete[]pbook;
				system("pause");
				break;
			}
			case 4:
			{
				int i;
				cout << "请输入删除元素的位置（1<=i<=" << List.GetLength()-1 << "）：" << endl;
				cin >> i;
				List.Delete(i);
				k = readbase.total();
				ifs.open("data.txt"); 
				for (int x = 0; x < k; x++)
				{
					if (x < i - 1)
						pbook[x].read();
					if (x > i - 1)
						pbook[x - 1].read();
				}
				ifs.close();
				ofs.open("data.txt", ios::out);
				for (int x = 0; x < k-1; x++)
				{
					pbook[x].save();
				}
				ofs.close();
				system("pause");
				break;
			}
			case 5:
				int i;
				cout << "请输入要查询的用户的ID：";
				cin >> i;
				k = readbase.total();
				ifs.open("data.txt");                                                    //读入数据
				for (int x = 0; x < k; x++)
				{
					pbook[x].read();
				}
				ifs.close();
				for (int x = 0; x < k; x++)
				{
					if (pbook[x].GetID() == i)
					{
						pbook[x].print();
						break;
					}
					if (x == k - 1)
					{
						cout << "查无此人！" << endl;
					}
				}
				system("pause");
				break;
			case 6:
				cout << "链表的长度为：" << List.GetLength() << endl;
				system("pause");
				break;
			case 7:
				List.~LinkList();
				cout << "已销毁！" << endl;
				system("pause");
				break;
			case 8:
				cout << "★☆★☆★☆★☆★☆★☆★☆★☆★☆再 见★☆★☆★☆★☆★☆★☆★☆★☆★☆\n";        //!!!∑(ﾟДﾟノ)ノ
				break;
			}
		}
	} while (p != 8);
}