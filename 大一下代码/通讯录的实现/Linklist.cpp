#ifndef _LINKLIST_CPP
#define _LINKLIST_CPP
#include<iostream>
using namespace std;

template<class T>                                                   //结点结构
struct Node
{
	T data;
	struct Node<T>* next;
};

template <class T>
class LinkList
{
public:
	LinkList()                                                      //无参构造函数
	{
		front = new Node <T>;
		front->next = NULL;
	}
	void setLinkList(T a[], int n);                                         //头插法：有参构造函数,使用含有n个元素的数组a初始化单链表
	void setLinkList(int n, T a[]);                                         //尾插法：有参构造函数,使用含有n个元素的数组a初始化单链表
	~LinkList();                                                    //析构函数
	void PrintList();                                               //按次序遍历线性表中的各个数据元素
	int GetLength();                                                //获取线性表的长度
	Node<T>* Get(int i);                                            //获取线性表第i个位置上的元素结点地址
	int Locate(T x);                                                //查找线性表中值为x的元素,找到后返回其位置
	void Insert(int i, T x);                                        //在线性表的第i个位置上插入值为x的新元素
	T Delete(int i);                                                //删除线性表第 1个元素，并将该元素返回
private:
	Node<T>* front;                                                 //头指针
};

template<class T>
void LinkList<T>::setLinkList(T a[], int n)                                 //头插法建立单链表
{
	front = new Node<T>;
	front->next = nullptr;                                          //构造空单链表
	for (int i = n - 1; i >= 0; i--)
	{
		auto s = new Node <T>;                                      //①建立新结点
		s->data = a[i];                                             //②将a[i]写入新结点的数据域
		s->next = front->next;                                      //③修改新结点的指针域
		front->next = s;                                            //④修改头结点的指针域，将新结点加入链表中
	}
}

template <class T>
void LinkList<T>::setLinkList(int n, T a[])                                 //尾插法建立单链表
{
	front = new Node<T>;
	auto r = front;                                                 //建立尾指针
	for (int i = 0; i < n; i++)
	{
		auto s = new Node<T>;                                       //①建立新结点
		s->data = a[i];                                             //②将a[i]写入新结点的数据域
		r->next = s;                                                //③将新结点加入链表中
		r = s;                                                      //④修改尾指针
		r->next = nullptr;                                          //终端结点的指针域设为空
	}
}

template <class T>
LinkList<T>:: ~LinkList()                                           //析构函数
{
	auto p = front;                                                 //初始化工作指针p
	while (p)                                                       //要释放的结点存在
	{
		front = p;                                                  //暂存要释放的结点
		p = p->next;                                                //移动工作指针
		delete front;                                               //释放结点
	}
}

template < class T >
Node<T>* LinkList<T>::Get(int i)                                    //获取线性表第i个位置上的元素
{
	auto p = front->next;                                           //初始化工作指针
	int j = 1;                                                      //初始化计数器
	while (p && j != i)                                             //两个条件都满足，则继续循环
	{
		p = p->next;                                                //工作指针后移
		j++;
	}
	return p;                                                     //查找到第i个元素返目地址，或未找到元素返回0
}

template <class T>
int LinkList <T>::Locate(T x)                                       //查找线性表中值为x的元素，找到后返回其位置
{
	auto p = front->next;                                           //初始化工作指针
	int j = 1;
	while (p)
	{
		if (p->data == x)
			return j;                                               //找到被查元素,返回位置
		p = p->next;
		j++;
	}
	return -1;                                                     //若找不到，返回错误标识-1
}

template <class T>
void LinkList <T>::Insert(int i, T x)                               //在线性表的第i个位置上插入值为x的新元
{
	auto p = front;                                                 //初始化工作指针
	if (i != 1)
		p = Get(i - 1);                                        //若不是在第一个位置插入，得到第i一个元素的地址
	if (p)
	{
		auto s = new Node<T>;                                       //建立新结点
		s->data = x;
		s->next = p->next;
		p->next = s;                                                //将新结点插入p所指结点的后面
	}
	else throw"插入位置错误";
}

template <class T>
T LinkList<T>::Delete(int i)                                        //删除线性表第1个元素，并将该元素返回
{
	auto p = front;                                                 //初始化工作指针
	if (i != 1)p = Get(i - 1);                                      //若不是在第一个位置插入，得到第i-1个元素的地址
	auto q = p->next;
	p->next = q->next;
	T x = q->data;
	delete q;
	return x;
}

template <class T>
int LinkList<T>::GetLength()                                        //获取链表长度
{
	auto p = front;
	int i = 0;
	while (p != nullptr)
	{
		p = p->next;
		i++;
	}
	return i;
}

template <class T>
void LinkList<T>::PrintList()
{
	auto p = front->next;
	while (p != nullptr)
	{
		p->data.print();
		p = p->next;
	}
	cout << endl;
}
#endif