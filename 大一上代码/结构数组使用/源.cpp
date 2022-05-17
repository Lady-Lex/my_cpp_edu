#include<iostream>
#include<iomanip>
using namespace std;
struct student
{
	char name[20];
	char sex[10];
	int age;
	char num[10];
};
int main()
{
	student p[5];
	for (int i = 0; i <= 4; i++)
	{
		cin >> p[i].name >> p[i].sex >> p[i].age >> p[i].num;
	}
	for (int i = 0; i <= 4; i++)
	{
		cout << setiosflags(ios::left) << setw(10) << p[i].name << setw(10)
			<< p[i].sex << setw(10) << p[i].age << setw(10) << p[i].num << endl;
	}
	return 0;
}