#include<iostream>
using namespace std;
int main()
{
	//一、指向一维整型数组的指针
	int a[4] = { 1,2,3,4 };
	int(*p)[4] = &a;  //4是一维数组的大小
	//int(*p)[4] = a; //错！到这里，可见 指向数组的指针 是不同于 指向指针的指针 的特殊复合类型！
	//int** pa = a;   //错！a是a[0]的地址，此句相当于int**pa = &a[0]，显然错误！   
	//int* pa2 = a;   //正确！
	//int** pa = &a;  //错！错误原因见上
	cout << a << endl;
	cout << *p << endl;
	cout << **p << endl;


	//二、指向一维指针数组的指针
	int b = 10, c = 9;
	int* pb[2] = { &b,&c };
	int** ppb = pb;   //因为数组名pb就是pb[0]的地址，相当于int**ppb = &pb[0],而pb[0]就是个指针
	cout << b << endl;
	cout << pb << endl;
	cout << ppb << endl;
}