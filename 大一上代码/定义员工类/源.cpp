#include<iostream>
using namespace std;
class staff
{public:
	staff(int I, char N[20], int A, int S, char P[30]);
	void display();
private:
	int id;
	char name[20];
	int age;
	int salary;
	char position[30];
};
staff::staff(int I, char N[20], int A, int S, char P[30])
{
	id = I;
	name[20] = N[20];
	age = A;
	salary = S;
	position[30] = P[30];
}
void staff::display()
{
	cout << id << ' ' << name[20] << ' ' << age << ' ' << salary << ' ' << position[30] << endl;
}
int main()
{
	int I;
	char N[20];
	int A;
	int S;
	char P[30];
	cin >> I >> N[20] >> A >> S >> P[30];
	staff s(int I, char N[20], int A, int S, char P[30]);
}