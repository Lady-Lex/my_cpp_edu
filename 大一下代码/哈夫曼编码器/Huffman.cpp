#include<iostream>
#include"Head.h"
#include<iomanip>
using namespace std;

//输入参数a[]存储每种字符的权值，n为字符的种类:name为各个字符的内容。
void Huffman::CreateHTree(int a[],int n,char name[])
{
	N = n;
	HCodeTable = new HCode[N];
	HTree = new HNode[2 * N - 1];                                  
	//根据权重数组a[0..n-1]初始化哈夫曼树
	for (int i = 0; i < N; i++)
	{
		HTree[i].weight = a[i];
		HTree[i].LChild = HTree[i].RChild = HTree[i].parent = -1; HCodeTable[i].data = name[i];
	}
	int x = 0, y = 0;
	for (int i = n; i < 2 * N - 1; i++)                            //开始建哈夫曼树
	{
		SelectMin(x, y, 0, i);                                     //从1~i中选出两个权值最小的结点
		HTree[x].parent = HTree[y].parent = i;
		HTree[i].weight = HTree[x].weight + HTree[y].weight;
		HTree[i].LChild = x;
		HTree[i].RChild = y;
		HTree[i].parent = -1;
	}
}

void Huffman::code(int i,string newcode)                          //递归函数，对第i个结点编码
{
	if (HTree[i].LChild == -1)
	{
		HCodeTable[i].code = newcode;
		return;
	}
	code(HTree[i].LChild, newcode + "0");
	code(HTree[i].RChild, newcode + "1");
}

void Huffman::CreateCodeTable()                                   //生成编码表
{
	code(2 * N - 2,"");
	cout << "-------------------------" << endl;
	cout << "|  字符  " << "|" << "  哈夫曼编码  |" << endl;
	cout << "-------------------------" << endl;
	for (int i = 0; i < N; i++)
	{
		cout << "|   " << HCodeTable[i].data << "    |  " <<setw(7)<< HCodeTable[i].code << "     |" << endl;
	}
	cout << "-------------------------" << endl;
}

void Huffman::print(int* a, int b, int m)
{
	if (HTree[b].LChild == -1)
	{
		cout << setfill(' ') << setw(m + 1) << HCodeTable[b].data;
	}
	else
	{
		cout << setfill(' ') << setw(m + 1) << HTree[b].weight << endl;
		print(a, HTree[b].LChild, m + 1);
		print(a, HTree[b].RChild, m + 1);
	}
}


void Huffman::Encode(char* s,string& d)                               //s为原字符串,d为编码串
{
	while(*s != '\0')
	{
		for (int i = 0; i < N; i++)
		{
			if (HCodeTable[i].data == *s)
			{
				d = d + HCodeTable[i].code;
			}
		}
		s++;
	}
}

void Huffman::Decode(char* s,char* d)                               //s为编码串,d为解码后的字符串
{
	while (*s != '\0')
	{
		int parent = 2 * N - 2;                                     //根结点在HTree中的下标
		while (HTree[parent].LChild != -1)                          //如果不是叶子结点
		{
			if (*s == '0')
				parent = HTree[parent].LChild;
			else
				parent = HTree[parent].RChild;
			s++;
		}
		*d = HCodeTable[parent].data; 
		d++;
	}
	*d = '\0';
}

Huffman::~Huffman()
{
	delete[]HTree;
	delete[]HCodeTable;
}

void Huffman::SelectMin(int &x,int &y,int z,int j)
{
	int i;
	for (i = z; i < j; i++)
	{
		if (HTree[i].parent == -1)					//找出第一个有效权值x，并令y=x
		{
			x = y = i;
			//cout << "一开始x的值：" << x << "  " << HTree[x].weight << endl;
			break;
		}
	}
	//cout << "输出i：" << i << endl;
	for (; i < j; i++)
	{
		if (HTree[i].parent == -1)				//该权值未使用过
		{
			if (HTree[i].weight < HTree[x].weight)
			{
				y = x;
				x = i;
			}
			else if (x == y || HTree[i].weight < HTree[y].weight)
			{
				y = i;							//找第二个有效权值y
			}
		}
	}
	//cout << x << " " << y << endl;
}