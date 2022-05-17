#include<iostream>
using namespace std;
class A
{
public:
    void foo()
    {
        cout << "1" << endl;
    }
};

class B : public A
{
public:
    void foo()     //¸²¸ÇÁËA::foo(int d);  
    {
        cout << "2" << endl;
        A::foo();
    }
};

int main()
{
    B *b;
    b = new B;
    b->foo(); 
    return 0;
}