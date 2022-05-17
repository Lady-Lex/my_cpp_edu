#pragma once
#include<iostream>
#include<fstream>
using namespace std;
struct ArcNode
{
	int adjvex;                   //数据域:邻接顶点下标
	ArcNode* nextarc;             //指针域:指向下一条弧结点
};
struct VertexNode 
{
	char vertex;                  //数据域:顶点信息
	ArcNode* firstarc;            //指针域:指向第一条弧
};
const int MAXSIZE = 10;
class ALGraph
{
public:
	ALGraph(ifstream& fin);
	~ALGraph();
	void DFS(int v);               //深度优先遍历
	void BFS(int v);               //广度优先遍历
	bool Judge(int v = 0);         //判断是否为强连通有向图
private:
	VertexNode adjlist[MAXSIZE];   //结点
	int vNum,arcNum;              //顶点数目和弧的数目
};