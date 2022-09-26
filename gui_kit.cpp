#include <iostream>
using namespace std;

class A
{
public:
	int d1;
	int show() { cout << "A" << endl; return 0; };
};
class B: public A
{
public:
	int d2;
	int show() { cout << "B" << endl; return 0; };
};
int main(void)
{
	A a;
	B b;

	cout << sizeof(int) << endl;
	cout << sizeof(a) << endl;
	cout << sizeof(b) << endl;

	A* pA;
	pA = &b;
	pA->show();
	
	system("pause");

	return 0;
}