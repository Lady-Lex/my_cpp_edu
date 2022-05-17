#include<iostream>
#include"Linklist.cpp"
#include"phonebook.cpp"
using namespace std;

int main()
{
	PHONEBOOK pbook[4] = { { 20181208,"Mary",'g',"13011221827","street A"},
					       { 20181127,"Tom",'b',"13934621123","street B"},
					       { 20181156,"John",'b',"1324579880","street S"},
					       { 20181133,"Lisa",'g',"1378001822","street C"} };
	PHONEBOOK record{ 20181209,"phoenix",'b', "15930209020","street A" };
	LinkList<PHONEBOOK>list;             //声明由通讯录构成的链表
	int p;                               //定义菜单选项序号
	cout << "★☆★☆★☆★☆★☆★欢 迎 来 到 通讯录 管 理 系 统 ！☆★☆★☆★☆★☆★☆" << endl;
	do
	{
		int q = 0;                      //作用：参见case 1
		cout << "★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆\n";
		cout << "☆************************************************************************★\n";
		cout << "★                              通讯录管理系统                            ☆\n";
		cout << "☆                                                                        ★\n";
		cout << "★          1.头插法构造新通讯录               5.查询个人信息             ☆\n";
		cout << "☆                                                                        ★\n";
		cout << "★          2.尾插法构造新通讯录               6.获取链表长度             ☆\n";
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
			system("pause");                                  //输入任意键继续
		}
		else
		{
			switch (p)
			{
			case 1:
			{  
			    LinkList<PHONEBOOK>list(pbook, 4);
			    cout << "已用头插法初始化通讯录！" << endl;
			    system("pause");
			    break;
			}
			case 2:
			{
				LinkList<PHONEBOOK>list(4, pbook);
				cout << "已用尾插法初始化通讯录！" << endl;
				system("pause");
				break;
			}
			case 3:
			{
				int i;
				cout << "请输入插入位置（0<=i<=" << list.GetLength() << "）：" << endl;
				cin >> i;
				list.Insert(i,record);
				system("pause");
				break;
			}
			case 4:
			{
				int i;
				cout << "请输入删除元素的位置（0<i<" << list.GetLength() << "）：" << endl;
				cin >> i;
				list.Delete(i);
				system("pause");
				break;
			}
			case 5:
				int i;
				cout << "请输入要查询的用户的ID：";
				cin >> i;
				for (int j = 0; j < 4; j++)
				{
					if (pbook[j].Judge(i))
					{
						pbook[j].print();
						break;
					}
					else if (record.Judge(i))
					{
						record.print();
						break;
					}
				};
				system("pause");
				break;
			case 6:
				cout << "链表的长度为：" << list.GetLength() << endl;
				break;
			case 7:
				list.~LinkList();
				cout << "已销毁！" << endl;
				break;
			case 8:
				cout << "★☆★☆★☆★☆★☆★☆★☆★☆★☆再 见★☆★☆★☆★☆★☆★☆★☆★☆★☆\n";        //!!!∑(ﾟДﾟノ)ノ
				break;
			}
		}
	} while (p != 8);
}