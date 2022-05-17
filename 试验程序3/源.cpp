#include<iostream>
#include<fstream>
#include<memory>
using namespace std;
ifstream book;
int main()
{
	book.open("data.txt");
    int q ;
	book >> q;
	cout << q;
	book.close();
}