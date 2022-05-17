#include<iostream>
#include<iomanip>
using namespace std;
int& a()
{
    int m = 10;
    return m;
}
int main()
{
    int& p = a();
    cout << p << endl;
    cout << p << endl;
}