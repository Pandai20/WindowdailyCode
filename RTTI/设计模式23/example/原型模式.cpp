#include <iostream>
using namespace std;

#include <String>

class MyString
{
public:
	virtual MyString* Clone() = 0;
	virtual void print_str() = 0;
};

class Hello : public MyString
{
private:
	int len;
	string str;
public:
	Hello()
	{
		this->len = 5;
		this->str = "Hello";
	}
	virtual MyString* Clone()
	{
		Hello* temp = new Hello;
		*temp = *this;
		return temp;
	}
	virtual void print_str()
	{
		cout << "len:" << len << "   str:" << str << endl;
	}
};

int main()
{
	MyString* h1 = new Hello;
	h1->print_str();
	MyString* h2 = h1->Clone();
	h2->print_str();

	delete h1;
	delete h2;

	system("pause");
	return 0;
}