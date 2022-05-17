#pragma once
#include<iostream>
#include<string>
using namespace std;

struct HNode
{
	int weight;                                     //结点全职
	int parent;                                     //双亲数组下标
	int LChild;                                     //左孩子数组下标
	int RChild;                                     //右孩子数组下标
};

struct HCode
{
	char data;                                      //存储节点内存
	string code;                                    //存储结点对应编码
};

class Huffman
{
private:
	HNode* HTree;                                   //哈夫曼树
	HCode* HCodeTable;                              //存储编码表
	int N;                                          //叶子结点数量
	void code(int i, string newcode);               //递归函数，对第i个结点编码
public:
	void CreateHTree(int a[],int n,char name[]);    //创建哈夫曼树
	void CreateCodeTable();                         //创建编码表
	void print(int *a,int b,int m);
	void Encode(char* s,string& d);                 //编码
	void Decode(char* s,char* d);                   //解码
	void SelectMin(int &x,int &y,int z,int i);
	~Huffman();
};