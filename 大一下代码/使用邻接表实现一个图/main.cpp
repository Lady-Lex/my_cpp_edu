#include<iostream>
#include<fstream>
#include"ALGraph.h"
using namespace std;
ifstream ifs("data.txt");
int main()
{
	{
		ALGraph _Graph(ifs);
		while (true)
		{
			cout << "请选择需要的操作：" << endl << "1.图的建立" << endl << "2.深度优先遍历图" << endl << "3.广度优先遍历图" << endl 
				<< "4.图的销毁" << endl << "5.判断是否为强连通图" << endl;
			int p;
			cin >> p;
			if (p == 1)
				cout << "构建完成，请按任意键继续" << endl;
			if (p == 2)
			{
				cout << "请输入起始结点：" << endl;
				int n;
				cin >> n;
				_Graph.DFS(n);
				cout << endl;
			}
			if (p == 3)
			{
				cout << "请输入起始结点：" << endl;
				int a;
				cin >> a;
				_Graph.BFS(a);
				cout << endl;
			}
			if (p == 4)
			{
				cout << "析构中...." << endl;
				return 0;
			}
			if (p == 5)
			{
				if(_Graph.Judge())
					cout << "此图是强连通图。" << endl;
				else
					cout << "此图不是强连通图。" << endl;
			}
			system("pause");  
			system("cls");
		}
	}
}