#include<iostream>
#include<fstream>
#include<stack>
#include"ALGraph.h"
using namespace std;
ALGraph::ALGraph(ifstream& fin)
{
	fin >> vNum;
	fin >> arcNum;
	for (int k = 0; k < vNum; k++)
	{
		fin >> adjlist[k].vertex;                //初始化顶点
		adjlist[k].firstarc = NULL;             //初始化弧
	}
	for (int k = 0; k < arcNum; k++)
	{
		int i,j;
		fin >> i;
		fin >> j;                          //输入顶点和边的权值
		ArcNode* s = new ArcNode;
		s->adjvex = j;
		s->nextarc = adjlist[i].firstarc;      //头插法
		adjlist[i].firstarc = s;
	}
}
void ALGraph::DFS(int v)
{
	stack<ArcNode>s1;//初始化栈   
	bool visited[MAXSIZE] = { 0 };
	cout << adjlist[v].vertex;
	visited[v] = 1;                                 //输出顶点v，将该顶点的访问数组对应元素置为1   
	auto p= adjlist[v].firstarc;                    //初始化栈顶元素，将p指向初始顶点，将p入栈   
	while ((!s1.empty()) || p != nullptr)           //当栈中有元素或p不为空  
	{
		while (p)                                   //p不为空时
		{
			if (p && visited[p->adjvex])            //若p的邻接结点已被访问过
				p = p->nextarc;                     //p指向下一个弧结点
			else                                    //若未被访问过
			{
				cout << adjlist[p->adjvex].vertex;  //显示邻接结点的数据
				visited[p->adjvex] = 1;             //设置访问
				s1.push(*p);                        //压入栈
				p = adjlist[p->adjvex].firstarc;    //将p指向与p的邻接点相邻的第一个元素        
			}
		}
		if (!s1.empty())
		{
			p = &s1.top();
			s1.pop();
			p = p->nextarc;
		} //若栈不为空，则退栈并将退栈元素赋给p，使p指向p的下一个邻接点
	}
}
void ALGraph::BFS(int v)
{
	int queue[MAXSIZE];
	bool visited[MAXSIZE] = { 0 };
	int f = 0, r = 0;                           //生成一个空队列
	cout << adjlist[v].vertex;     visited[v] = 1;     queue[++r] = v;          //v入队
	while (f != r)
	{
		v = queue[++f];                         //队头元素出队
		ArcNode*p = adjlist[v].firstarc;
		while (p)
		{
			int j = p->adjvex;
			if (visited[j] == 0)
			{
				cout << adjlist[j].vertex;   visited[j] = 1;   queue[++r] = j;   //j入队
			}
			p = p->nextarc;
		}
	}
}
ALGraph::~ALGraph()
{
	int i = 0;
	while (i < vNum)
	{
		ArcNode* p = adjlist[i++].firstarc;      //得到第i个顶点对应的链表
		while (p)
		{
			ArcNode*q = p->nextarc;
			delete p;
			p = q;
		}
	}
}
bool ALGraph::Judge(int v)
{
	stack<ArcNode>s1;//初始化栈   
	bool visited[MAXSIZE] = { 0 };
	visited[v] = 1;                                 //输出顶点v，将该顶点的访问数组对应元素置为1   
	auto p = adjlist[v].firstarc;                    //初始化栈顶元素，将p指向初始顶点，将p入栈   
	while ((!s1.empty()) || p != nullptr)           //当栈中有元素或p不为空  
	{
		while (p)
		{
			if (p && visited[p->adjvex])
				p = p->nextarc;
			else
			{
				visited[p->adjvex] = 1;
				s1.push(*p);
				p = adjlist[p->adjvex].firstarc;      //将p指向与p的邻接点相邻的第一个元素        
			}
		}
		if (!s1.empty())
		{
			p = &s1.top();
			s1.pop();
			p = p->nextarc;
		} //若栈不为空，则退栈并将退栈元素赋给p，使p指向p的下一个邻接点
	}
	for (int i = 0; i < vNum; i++)
	{
		if (visited[i] == 1)
			continue;
		else 
			return false;
	}
	if (v < vNum)
		Judge(++v);
	else
        return true;
}